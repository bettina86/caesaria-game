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
// Copyright 2012-2013 Dalerank, dalerankn8@gmail.com

#include "cityservice_culture.hpp"
#include "objects/construction.hpp"
#include "city/statistic.hpp"
#include "core/safetycast.hpp"
#include "core/position.hpp"
#include "objects/house.hpp"
#include "objects/entertainment.hpp"
#include "objects/house_level.hpp"
#include "gfx/tile.hpp"
#include "core/time.hpp"
#include "game/gamedate.hpp"
#include "objects/religion.hpp"
#include "objects/education.hpp"
#include "objects/constants.hpp"
#include "objects/theater.hpp"
#include "cityservice_factory.hpp"
#include "city/states.hpp"

namespace city
{

REGISTER_SERVICE_IN_FACTORY(CultureRating,culture)

namespace coverage
{
enum { levelNumber = 6 };
struct Point {
  double coverage;
  int points;
};
typedef Point Points[ levelNumber ];
static const Points religion =  { {1.0,30}, {0.86,22}, {0.71,14}, {0.51,9}, {0.31,3}, {0.0,0} };
static const Points theatres =  { {1.0,25}, {0.86,18}, {0.71,12}, {0.51,8}, {0.31,3}, {0.0,0} };
static const Points libraries = { {1.0,20}, {0.86,14}, {0.71,8},  {0.51,4}, {0.31,2}, {0.0,0} };
static const Points schools =   { {1.0,15}, {0.86,10}, {0.71,6},  {0.51,4}, {0.31,1}, {0.0,0} };
static const Points academies = { {1.0,10}, {0.86,7},  {0.71,4},  {0.51,2}, {0.31,1}, {0.0,0} };

/**
 * Part of culture rating
 */
template<class T, class WhatFind=object::Type>
struct SubRating
{
  const Points& intervals;
  WhatFind whatFind;
  int coverage;
  int value;
  int objects_n;
  int visitors;

  SubRating( const Points& points, WhatFind otype)
    : intervals(points), whatFind(otype), coverage(0), value(0)
  {}

  int coverage2rating( float value )
  {
    for( int i=0; i < coverage::levelNumber; i++ )
    {
      if( value >= intervals[ i ].coverage )
      {
        return (int) (intervals[ i ].points * value);
      }
    }

    return 0;
  }

  virtual float calcCoverage( PlayerCityPtr rcity )
  {
    visitors = 0;
    unsigned int population = rcity->states().population;
    if (population == 0)
    {
      return 0;
    }
    /** buildings which we need check **/

    auto objects = rcity->statistic()
                          .objects
                          .find<T>( whatFind );

    objects_n = objects.size();

    objects.for_each( [this](SmartPtr<T> r){ visitors += r->currentVisitors(); } );

    float coverage = visitors / (float)population;

    return coverage;
  }

  void update( PlayerCityPtr rcity )
  {
    /** current coverage in percents **/
    float coveragePercent = calcCoverage( rcity );

    value = 0;
    /** get points of culture for current coverage **/
    coveragePercent = math::clamp<float>(coveragePercent, 0.f, 1.0f );
    coverage = (int) (coveragePercent * 100);
    value = coverage2rating( coveragePercent );
  }
};

}//end namespace coverage

class CultureRating::Impl
{
public:
  DateTime lastDate;
  int culture;
  coverage::SubRating<Temple,object::Group> religion;
  coverage::SubRating<Theater> theaters;
  coverage::SubRating<Library> libraries;
  coverage::SubRating<School> schools;
  coverage::SubRating<Academy> academies;
  float hippodromeCoverage;

  int collegePoints;

  Impl() : religion(coverage::religion,object::group::religion),
           theaters(coverage::theatres,object::theater),
           libraries(coverage::libraries,object::library),
           schools(coverage::schools,object::school),
           academies(coverage::academies,object::academy)
           {}
};

CultureRating::CultureRating( PlayerCityPtr city )
  : Srvc( city, defaultName() ), _d( new Impl )
{
  _d->lastDate = game::Date::current();
  _d->culture = 0;
}

void CultureRating::timeStep(const unsigned int time )
{
  if( !game::Date::isMonthChanged() )
    return;

  if( _d->lastDate.monthsTo( game::Date::current() ) > 0 )
  {
    _d->lastDate = game::Date::current();

    _d->religion.update( _city() );
    _d->theaters.update( _city() );
    _d->libraries.update( _city() );
    _d->schools.update( _city() );
    _d->academies.update( _city() );

    _d->culture = ( _d->culture + _d->religion.value + _d->theaters.value +
                    _d->libraries.value + _d->schools.value + _d->academies.value ) / 2;
  }
}

VariantMap CultureRating::save() const
{
  VariantMap ret = Srvc::save();
  VARIANT_SAVE_ANY_D( ret, _d, lastDate )
  VARIANT_SAVE_ANY_D( ret, _d, culture  )

  return ret;
}

void CultureRating::load(const VariantMap &stream)
{
  Srvc::load( stream );

  VARIANT_LOAD_TIME_D( _d, lastDate, stream )
  VARIANT_LOAD_ANY_D ( _d, culture,  stream )
}

int CultureRating::value() const {  return _d->culture; }

int CultureRating::coverage( Coverage type) const
{
  switch( type )
  {
  case covSchool: return _d->schools.coverage * 100;
  case covLibrary: return _d->libraries.coverage * 100;
  case covAcademy: return _d->academies.coverage * 100;
  case covReligion: return _d->religion.coverage * 100;
  case covTheatres: return _d->theaters.coverage * 100;
  default: return 0;
  }
}

int CultureRating::objects_n(CultureRating::Coverage type) const
{
  switch( type )
  {
  case covSchool: return _d->schools.objects_n;
  case covLibrary: return _d->libraries.objects_n;
  case covAcademy: return _d->academies.objects_n;
  case covReligion: return _d->religion.objects_n;
  case covTheatres: return _d->theaters.objects_n;
  default: return 0;
  }
}

std::string CultureRating::defaultName() { return TEXT(CultureRating); }

}//end namespace city
