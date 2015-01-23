// This file is part of CaesarIA.
//
// CaesarIA is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CaesarIA is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CaesarIA.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2015 Dalerank, dalerankn8@gmail.com

#include "addon_manager.hpp"
#include "core/smartlist.hpp"
#include "core/predefinitions.hpp"
#include "core/logger.hpp"

#ifdef CAESARIA_PLATFORM_WIN
#include <windows.h>
typedef HINSTANCE addon_lib_t;
#else
#include <dlfcn.h>
typedef void* addon_lib_t;
#endif

namespace addons
{

PREDEFINE_CLASS_SMARTLIST(Addon, List)

typedef void (*addonInitFunctor)(const GameInfo& gameInfo);
typedef void (*addonGetVersionFunctor)(const GameInfo& gameInfo);

class Addon::Impl
{
public:
  addon_lib_t library;
  bool isOpened;
  addonInitFunctor funcInit;
  addonGetVersionFunctor funcGetVersion;

  template<class T>
  T initFunction( const char* funcName )
  {
# ifdef CAESARIA_PLATFORM_WIN
  return (T)::GetProcAddress(library, funcName);
# else
  return (T)::dlsym(library, funcName);
# endif
  }
};

Addon::Addon() : _d( new Impl )
{
  _d->isOpened = false;
  _d->funcInit = 0;
  _d->funcGetVersion = 0;
}

Addon::~Addon()
{
# ifdef CAESARIA_PLATFORM_WIN
  ::FreeLibrary(_d->library);
# else
  ::dlclose(_d->library);
# endif
}

bool Addon::open(vfs::Path path)
{
# ifdef CAESARIA_PLATFORM_WIN
  _d->library = ::LoadLibraryA(path.toString().c_str());
# else
  _d->library = ::dlopen(path.toString().c_str(), RTLD_LAZY);
# endif

  if( _d->library != 0 )
  {
    _d->isOpened = true;
    _d->funcInit = _d->initFunction<addonInitFunctor>( "initialize" );
    _d->funcGetVersion = _d->initFunction<addonGetVersionFunctor>( "getVersion" );
  }

  return _d->isOpened;
}

void Addon::initialize()
{
  GameInfo gameInfo;
  if( _d->isOpened && _d->funcInit )
  {
    _d->funcInit( gameInfo );
  }
}

unsigned int Addon::level() const
{
  return 0;
}

class Manager::Impl
{
public:
  AddonList addons;
};

Manager::~Manager()
{

}

void Manager::load(vfs::Directory folder)
{
  vfs::Entries flist = folder.getEntries();
  flist = flist.filter( vfs::Entries::file | vfs::Entries::extFilter, ".addon" );

  foreach( it, flist )
  {
    load( it->fullpath, true );
  }
}

void Manager::load(vfs::Path path, bool ls)
{
  AddonPtr addon( new Addon() );
  addon->drop();

  Logger::warning( "Try load addon " + path.toString() );
  bool isOpen = addon->open( path );

  if( isOpen )
  {
    _d->addons << addon;
  }

   Logger::warning( "Addon " + path.toString() + ( isOpen ? "load succefully" : "not loaded") );

}

void Manager::initAll()
{
  foreach( it, _d->addons )
  {
    (*it)->initialize();
  }
}

Manager::Manager() : _d( new Impl )
{

}

}