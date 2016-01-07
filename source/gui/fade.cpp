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

#include "fade.hpp"

namespace gui
{

Fade::Fade(Widget* parent, int alpha, const Rect& rect )
  : Label( parent, rect.width() > 0 ? rect : Rect( Point( 0, 0), parent->size() ),
           "", false, gui::Label::bgSimpleBlack )
{
  setAlpha( alpha );
}

Fade::~Fade(){}

}//end namespace gui