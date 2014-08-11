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
// Copyright 2012-2013 Gregoire Athanase, gathanase@gmail.com
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#include "ironmine.hpp"

#include "gfx/tile.hpp"
#include "gfx/tilesarray.hpp"
#include "game/resourcegroup.hpp"
#include "game/gamedate.hpp"
#include "city/helper.hpp"
#include "events/showinfobox.hpp"

using namespace gfx;
using namespace constants;

class IronMine::Impl
{
public:
  unsigned int lowWorkerWeeksNumber;
};

IronMine::IronMine() : Factory(Good::none, Good::iron, building::ironMine, Size(2) ),
  _d( new Impl )
{
  setPicture( ResourceGroup::commerce, 54 );

  _animationRef().load( ResourceGroup::commerce, 55, 6 );
  _animationRef().setDelay( 5 );
  _fgPicturesRef().resize( 2 );
}

bool IronMine::canBuild( PlayerCityPtr city, TilePos pos, const TilesArray& aroundTiles ) const
{
  bool is_constructible = WorkingBuilding::canBuild( city, pos, aroundTiles );
  bool near_mountain = false;  // tells if the factory is next to a mountain

  Tilemap& tilemap = city->tilemap();
  TilesArray perimetr = tilemap.getRectangle( pos + TilePos( -1, -1 ), pos + TilePos(3, 3), Tilemap::checkCorners );

  foreach( it, perimetr ) { near_mountain |= (*it)->getFlag( Tile::tlRock ); }

  const_cast< IronMine* >( this )->_setError( near_mountain ? "" : "##iron_mine_need_mountain_near##" );

  return (is_constructible && near_mountain);
}

void IronMine::timeStep(const unsigned long time)
{
  Factory::timeStep( time );

  if( GameDate::isWeekChanged() )
  {
    if( numberWorkers() < maximumWorkers() / 3 )
    {
      _d->lowWorkerWeeksNumber++;
    }
    else
    {
      _d->lowWorkerWeeksNumber = std::max<int>( 0, _d->lowWorkerWeeksNumber-1 );
    }

    if( _d->lowWorkerWeeksNumber > 8 &&  _d->lowWorkerWeeksNumber > (unsigned int)math::random( 42 ) )
    {
      collapse();

      events::GameEventPtr e = events::ShowInfobox::create( "##iron_mine_collapse##", "##iron_mine_collpase_by_low_support##");
      e->dispatch();
    }
  }
}

void IronMine::save(VariantMap& stream) const
{
  Factory::save( stream );
  VARIANT_SAVE_ANY_D( stream, _d, lowWorkerWeeksNumber );
}

void IronMine::load(const VariantMap& stream)
{
  Factory::load( stream );
  VARIANT_LOAD_ANY_D( _d, lowWorkerWeeksNumber, stream );
}
