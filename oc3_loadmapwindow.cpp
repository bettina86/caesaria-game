// This file is part of openCaesar3.
//
// openCaesar3 is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// openCaesar3 is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with openCaesar3.  If not, see <http://www.gnu.org/licenses/>.

#include "oc3_loadmapwindow.hpp"
#include "oc3_label.hpp"
#include "oc3_pushbutton.hpp"
#include "oc3_gui_paneling.hpp"
#include "oc3_resourcegroup.hpp"
#include "oc3_sdl_facade.hpp"
#include "oc3_gfx_engine.hpp"
#include "oc3_listbox.hpp"

class LoadMapWindow::Impl
{
public:
  Picture *bgPicture;
  Label* lbTitle;
  ListBox* files;
  PushButton* btnExit;
  PushButton* btnHelp;
};

LoadMapWindow::LoadMapWindow( Widget* parent, const Rect& rect, int id )
: Widget( parent, id, rect ), _d( new Impl )
{
  // create the title
  _d->lbTitle = new Label( this, Rect( 16, 10, getWidth()-16, 10 + 30 ), "", true );
  _d->lbTitle->setFont( FontCollection::instance().getFont(FONT_3) );
  _d->lbTitle->setTextAlignment( alignCenter, alignCenter );

  _d->btnExit = new PushButton( this, Rect( 472, getHeight() - 39, 496, getHeight() - 15 ) );
  GuiPaneling::configureTexturedButton( _d->btnExit, ResourceGroup::panelBackground, ResourceMenu::exitInfBtnPicId, false);
  
  _d->btnHelp = new PushButton( this, Rect( 14, getHeight() - 39, 38, getHeight() - 15 ) );
  GuiPaneling::configureTexturedButton( _d->btnHelp, ResourceGroup::panelBackground, ResourceMenu::helpInfBtnPicId, false);

  CONNECT( _d->btnExit, onClicked(), this, LoadMapWindow::deleteLater );

  _d->files = new ListBox( this, Rect( 10, _d->lbTitle->getBottom(), getWidth() - 10, _d->btnHelp->getTop() - 5 ), -1, true, true, false ); 

  SdlFacade &sdlFacade = SdlFacade::instance();
  _d->bgPicture = &sdlFacade.createPicture( getWidth(), getHeight() );

  // draws the box and the inner black box
  GuiPaneling::instance().draw_white_frame(*_d->bgPicture, 0, 0, getWidth(), getHeight() );
  GfxEngine::instance().load_picture(*_d->bgPicture);
}

LoadMapWindow::~LoadMapWindow()
{

}

void LoadMapWindow::draw( GfxEngine& engine )
{
  engine.drawPicture( getBgPicture(), getScreenLeft(), getScreenTop() );
  Widget::draw( engine );
}

Picture& LoadMapWindow::getBgPicture()
{
  return *_d->bgPicture;
}

bool LoadMapWindow::isPointInside( const Point& point ) const
{
  //resolve all screen for self using
  return getParent()->getAbsoluteRect().isPointInside( point );
}

bool LoadMapWindow::onEvent( const NEvent& event)
{
  return Widget::onEvent( event );
}

void LoadMapWindow::setTitle( const std::string& title )
{
  _d->lbTitle->setText( title );
}
