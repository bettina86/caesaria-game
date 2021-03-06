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
// Copyright 2012-2014 Dalerank, dalerankn8@gmail.com

#ifndef _CAESARIA_CIRCUS_CHARIOTER_H_INCLUDE_
#define _CAESARIA_CIRCUS_CHARIOTER_H_INCLUDE_

#include "walker.hpp"
#include "objects/predefinitions.hpp"

class CircusCharioter : public Walker
{
  WALKER_MUST_INITIALIZE_FROM_FACTORY
public:  
  static WalkerPtr create(PlayerCityPtr city );
  virtual ~CircusCharioter();
  virtual void getPictures(gfx::Pictures &oPics);
  virtual void timeStep(const unsigned long time);

protected:
  CircusCharioter( PlayerCityPtr city, HippodromePtr circus=nullptr );
  virtual void _reachedPathway();
  virtual void _changeDirection();

private:
  void _addToCircus(HippodromePtr circus );

  class Impl;
  ScopedPtr<Impl> _d;
};

#endif //_CAESARIA_CIRCUS_CHARIOTER_H_INCLUDE_
