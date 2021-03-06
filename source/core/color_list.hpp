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

#ifndef __CAESARIA_COLORLIST_H_INCLUDED__
#define __CAESARIA_COLORLIST_H_INCLUDED__

#include "color.hpp"
#include <map>

class ColorList
{
public:
#define __DEFINE_COLOR(a) static const NColor a;
__DEFINE_COLOR( clear )
__DEFINE_COLOR( red )
__DEFINE_COLOR( caesarRed )
__DEFINE_COLOR( blue )
__DEFINE_COLOR( green )
__DEFINE_COLOR( show )
__DEFINE_COLOR( ghost)
__DEFINE_COLOR( whitesmoke)
__DEFINE_COLOR( floralwhite)
__DEFINE_COLOR( oldlace)
__DEFINE_COLOR( linen)
__DEFINE_COLOR( antiqueWhite)
__DEFINE_COLOR( papayaWhip)
__DEFINE_COLOR( blanchedAlmond)
__DEFINE_COLOR( bisque)
__DEFINE_COLOR( peachPuff)
__DEFINE_COLOR( navajoWhite)
__DEFINE_COLOR( moccasin)
__DEFINE_COLOR( cornsilk)
__DEFINE_COLOR( ivory)
__DEFINE_COLOR( lemonChiffon)
__DEFINE_COLOR( seashell)
__DEFINE_COLOR( honeydew)
__DEFINE_COLOR( mintCream)
__DEFINE_COLOR( azure)
__DEFINE_COLOR( aliceBlue)
__DEFINE_COLOR( lavender)
__DEFINE_COLOR( lavenderBlush)
__DEFINE_COLOR( mistyRose)
__DEFINE_COLOR( white)
__DEFINE_COLOR( black)
__DEFINE_COLOR( darkSlateGray)
__DEFINE_COLOR( dimGrey)
__DEFINE_COLOR( slateGrey)
__DEFINE_COLOR( lightSlateGray)
__DEFINE_COLOR( grey)
__DEFINE_COLOR( lightGray)
__DEFINE_COLOR( midnightBlue)
__DEFINE_COLOR( navyBlue)
__DEFINE_COLOR( cornflowerBlue)
__DEFINE_COLOR( darkSlateBlue)
__DEFINE_COLOR( slateBlue)
__DEFINE_COLOR( mediumSlateBlue)
__DEFINE_COLOR( lightSlateBlue)
__DEFINE_COLOR( mediumBlue)
__DEFINE_COLOR( royalBlue)
__DEFINE_COLOR( skyBlue)
__DEFINE_COLOR( paleTurquoise)
__DEFINE_COLOR( cyan)
__DEFINE_COLOR( mediumAquamarine)
__DEFINE_COLOR( darkGreen)
__DEFINE_COLOR( darkSeaGreen)
__DEFINE_COLOR( paleGreen)
__DEFINE_COLOR( limeGreen)
__DEFINE_COLOR( darkKhaki)
__DEFINE_COLOR( paleGoldenrod)
__DEFINE_COLOR( yellow)
__DEFINE_COLOR( gold)
__DEFINE_COLOR( rosyBrown)
__DEFINE_COLOR( indianRed)
__DEFINE_COLOR( sienna)
__DEFINE_COLOR( peru)
__DEFINE_COLOR( wheat)
__DEFINE_COLOR( sandyBrown)
__DEFINE_COLOR( tan)
__DEFINE_COLOR( chocolate)
__DEFINE_COLOR( firebrick)
__DEFINE_COLOR( brown)
__DEFINE_COLOR( salmon)
__DEFINE_COLOR( orange)
__DEFINE_COLOR( darkOrange)
__DEFINE_COLOR( coral)
__DEFINE_COLOR( tomato)
__DEFINE_COLOR( orangeRed)
__DEFINE_COLOR( hotPink)
__DEFINE_COLOR( deepPink)
__DEFINE_COLOR( pink)
__DEFINE_COLOR( maroon)
__DEFINE_COLOR( magenta)
__DEFINE_COLOR( violet)
__DEFINE_COLOR( orchid)
__DEFINE_COLOR( purple)
__DEFINE_COLOR( snow)
__DEFINE_COLOR( dodgerBlue)
__DEFINE_COLOR( steelBlue)
__DEFINE_COLOR( slateGray)
__DEFINE_COLOR( aquamarine)
__DEFINE_COLOR( seaGreen)
__DEFINE_COLOR( springGreen)
__DEFINE_COLOR( chartreuse)
__DEFINE_COLOR( plum)
__DEFINE_COLOR( thistle)

static const NColor& find( const std::string& name );
private:
  static void _createColors();
};

#endif //__CAESARIA_COLOR_H_INCLUDED__
