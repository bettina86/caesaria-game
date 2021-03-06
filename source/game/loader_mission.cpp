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

#include "loader_mission.hpp"
#include "gfx/tile.hpp"
#include "core/exception.hpp"
#include "gfx/picture.hpp"
#include "core/position.hpp"
#include "objects/objects_factory.hpp"
#include "game.hpp"
#include "core/saveadapter.hpp"
#include "loader.hpp"
#include "game/player.hpp"
#include "city/victoryconditions.hpp"
#include "city/build_options.hpp"
#include "objects/metadata.hpp"
#include "game/funds.hpp"
#include "world/empire.hpp"
#include "city/city.hpp"
#include "vfs/path.hpp"
#include "settings.hpp"
#include "core/variant_map.hpp"
#include "events/postpone.hpp"
#include "gamedate.hpp"
#include "core/logger.hpp"
#include "world/emperor.hpp"
#include "religion/pantheon.hpp"
#include "core/locale.hpp"
#include "city/terrain_generator.hpp"
#include "events/fishplace.hpp"
#include "city/config.hpp"
#include "freeplay_finalizer.hpp"

using namespace religion;
using namespace events;

namespace game
{

namespace loader
{

static const int currentVesion = 1;

GAME_LITERALCONST(climate)
GAME_LITERALCONST(map)
GAME_LITERALCONST(random)

class Mission::Impl
{
public:
  std::string restartFile;
  bool needFinalizeMap;
};

Mission::Mission()
 : _d(new Impl)
{
  _d->needFinalizeMap = false;
}

bool Mission::load(const std::string& filename, Game& game)
{
  VariantMap vm = config::load(filename);
  _d->restartFile = filename;

  if (currentVesion == vm[TEXT(version)].toInt())
  {
    std::string mapToLoad = vm[ literals::map ].toString();
    Variant vClimate = vm.get( literals::climate );

    if (vClimate.isValid()) {
      ClimateType type = game::climate::central;

      if (vClimate.type() == Variant::String) {
        type = game::climate::fromString( vClimate.toString() );
      } else {
        type = (ClimateType)vClimate.toInt();
      }

      game::climate::initialize( type );
    }

    PlayerCityPtr city = game.city();

    if (mapToLoad == literals::random) {
      terrain::Generator targar;
      terrain::Generator::Params params;
      params.load(vm[literals::random].toMap());
      targar.create(game, params);

      city->setCameraPos(game.city()->getBorderInfo(PlayerCity::roadEntry).epos());
      city::development::Options bopts;
      bopts = game.city()->buildOptions();
      bopts.setAvailable(true);
      city->setBuildOptions(bopts);
      _d->needFinalizeMap = true;
    } else {
      _d->needFinalizeMap = false;
      game::Loader mapLoader;

      if (!vfs::Path(mapToLoad).exist()) {
        Logger::error("Cant find map {} for mission {}", mapToLoad, filename);
        return false;
      }

      mapLoader.load(mapToLoad, game);

      city::development::Options options;
      options.load( vm.get("buildoptions").toMap());
      city->setBuildOptions(options);
    }

    std::string cityName = vm.get("city.name").toString();

    if (!cityName.empty()) {
      city->setName( cityName );
    }

    city->treasury().resolveIssue(econ::Issue(econ::Issue::donation, vm.get("funds").toInt()));

    Logger::debug( "GameLoaderMission: load city options ");
    city->setOption(PlayerCity::adviserEnabled, vm.get( TEXT(adviserEnabled), 1 ) );
    city->setOption(PlayerCity::fishPlaceEnabled, vm.get( TEXT(fishPlaceEnabled), 1 ) );
    city->setOption(PlayerCity::collapseKoeff, vm.get( TEXT(collapseKoeff), 100 ) );
    city->setOption(PlayerCity::fireKoeff, vm.get( TEXT(fireKoeff), 100 ) );
    city->setOption(PlayerCity::warfNeedTimber, vm.get( TEXT(warfNeedTimber), 1 ) );
    city->setOption(PlayerCity::claypitMayFloods, vm.get( TEXT(claypitMayCollapse), 1 ) );
    city->setOption(PlayerCity::minesMayCollapse, vm.get( TEXT(minesMayCollapse), 1 ) );
    city->setOption(PlayerCity::riversideAsWell, vm.get( TEXT(riversideAsWell), 1 ) );
    city->setOption(PlayerCity::soldiersHaveSalary, vm.get( TEXT(soldiersHaveSalary), 1 ) );
    city->setOption(PlayerCity::housePersonalTaxes, vm.get( TEXT(housePersonalTaxes), 1 ) );
    city->setOption(PlayerCity::cutForest2timber, vm.get( TEXT(cutForest2timber), 1 ) );
    city->setOption(PlayerCity::forestGrow, vm.get( TEXT(forestGrow), 1 ) );
    city->setOption(PlayerCity::forestFire, vm.get( TEXT(forestFire), 1 ) );
    city->setOption(PlayerCity::destroyEpidemicHouses, vm.get( TEXT(destroyEpidemicHouses), 1 ) );
    city->setOption(PlayerCity::ironInRocks, vm.get( TEXT(ironInRocks), 1 ) );

    game::Date::instance().init( vm[ "date" ].toDateTime() );

    VariantMap vm_events = vm.get( "events" ).toMap();
    for (const auto& item : vm_events) {
      events::dispatch<PostponeEvent>(item.first, item.second.toMap());
    }

    game.empire()->setCitiesAvailable(false);
    Logger::debug( "GameLoaderMission: load empire state" );
    game.empire()->load(vm.get("empire").toMap());

    city::VictoryConditions winConditions;
    Variant winOptions = vm.get("win");
    Logger::warningIf(winOptions.isNull(), "GameLoaderMission: cannot load mission win options from file " + filename);

    winConditions.load(winOptions.toMap());
    city->setVictoryConditions(winConditions);

    game.empire()->emperor().updateRelation(city->name(), 50);

    VariantMap fishpointsVm = vm.get("fishpoints").toMap();
    for (const auto& item : fishpointsVm) {
      events::dispatch<ChangeFishery>(item.second.toTilePos(), ChangeFishery::add);
    }

    std::string missionName = vfs::Path(filename).baseName().removeExtension();
    Locale::addTranslation(missionName);
    SETTINGS_SET_VALUE(lastTranslation, Variant(missionName));

    //reseting divinities festival date
    DivinityList gods = rome::Pantheon::instance().all();
    for (const auto god : gods)
      rome::Pantheon::doFestival(god->name(), 0);

    freeplay::Finalizer finalizer(city);
    if (city->getOption(PlayerCity::ironInRocks) > 0) {
      int ironQty = vm.get(TEXT(ironInRocks.qty), 10000);
      finalizer.resetIronCovery(ironQty);
    }

    auto player = city->mayor();
    world::GovernorRank::Level level = vm.get("player.rank", 0).toEnum<world::GovernorRank::Level>();
    const world::GovernorRank& rank = world::EmpireHelper::getRank(level);
    player->setRank(rank.level);
    player->setSalary(rank.salary);

    return true;
  }

  return false;
}

bool Mission::isLoadableFileExtension( const std::string& filename )
{
  return vfs::Path( filename ).isMyExtension( ".mission" );
}

int Mission::climateType(const std::string& filename) { return -1; }
std::string Mission::restartFile() const { return _d->restartFile; }

bool Mission::finalizeMap() const { return _d->needFinalizeMap; }

}//end namespace loader

}//end namespace game
