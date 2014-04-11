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

#include "layerdamage.hpp"
#include "objects/constants.hpp"
#include "objects/house.hpp"
#include "objects/house_level.hpp"
#include "game/resourcegroup.hpp"
#include "layerconstants.hpp"
#include "city/helper.hpp"
#include "core/event.hpp"
#include "tilemap_camera.hpp"

using namespace constants;

namespace gfx
{

static const char* damageLevelName[] = { "##very_low_damage_risk##", "##low_damage_risk##",
                                         "##some_damage_risk##", "##very_high_damage_risk##",
                                         "##extreme_damage_risk##" };

int LayerDamage::getType() const
{
  return citylayer::damage;
}

std::set<int> LayerDamage::getVisibleWalkers() const
{
  std::set<int> ret;
  ret.insert( walker::engineer );
  return ret;
}

void LayerDamage::drawTile( Engine& engine, Tile& tile, Point offset)
{
  Point screenPos = tile.mapPos() + offset;

  tile.setWasDrawn();

  if( tile.overlay().isNull() )
  {
    //draw background
    engine.drawPicture( tile.picture(), screenPos );
  }
  else
  {
    bool needDrawAnimations = false;
    TileOverlayPtr overlay = tile.overlay();
    int damageLevel = 0;
    switch( overlay->type() )
    {
      //fire buildings and roads
    case construction::road:
    case construction::plaza:
    case building::collapsedRuins:
    case building::engineerPost:
    case building::burningRuins:
      needDrawAnimations = true;
      drawTilePass( engine, tile, offset, Renderer::ground );
      drawTilePass( engine, tile, offset, Renderer::foreground );
      break;

      //houses
    case building::house:
      {
        HousePtr house = ptr_cast<House>( overlay );
        damageLevel = (int)house->getState( Construction::damage );
        needDrawAnimations = (house->getSpec().level() == 1) && house->getHabitants().empty();

        city::Helper helper( _city() );
        drawArea( engine, helper.getArea( overlay ), offset, ResourceGroup::foodOverlay, OverlayPic::inHouseBase );
      }
      break;

      //other buildings
    default:
      {
        BuildingPtr building = ptr_cast<Building>( overlay );
        if( building.isValid() )
        {
          damageLevel = (int)building->getState( Construction::damage );
        }

        city::Helper helper( _city() );
        drawArea( engine, helper.getArea( overlay ), offset, ResourceGroup::foodOverlay, OverlayPic::base );
      }
      break;
    }

    if( needDrawAnimations )
    {
      registerTileForRendering( tile );
    }
    else if( damageLevel >= 0 )
    {
      drawColumn( engine, screenPos, damageLevel );
    }
  }
}

LayerPtr LayerDamage::create( Camera& camera, PlayerCityPtr city)
{
  LayerPtr ret( new LayerDamage( camera, city ) );
  ret->drop();

  return ret;
}

void LayerDamage::handleEvent(NEvent& event)
{
  if( event.EventType == sEventMouse )
  {
    switch( event.mouse.type  )
    {
    case mouseMoved:
    {
      Tile* tile = _camera()->at( event.mouse.pos(), false );  // tile under the cursor (or NULL)
      std::string text = "";
      if( tile != 0 )
      {
        ConstructionPtr constr = ptr_cast<Construction>( tile->overlay() );
        if( constr != 0 )
        {
          int damageLevel = math::clamp<int>( constr->getState( Construction::damage ), 0, 100 );
          if( damageLevel > 0 )
          {
            text = damageLevelName[ damageLevel / 20 ];
          }
        }
      }

      _setTooltipText( text );
    }
    break;

    default: break;
    }
  }

  Layer::handleEvent( event );
}

LayerDamage::LayerDamage( Camera& camera, PlayerCityPtr city)
  : Layer( &camera, city )
{
  _loadColumnPicture( 15 );
}

}//end namespace gfx
