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

#ifndef __CAESARIA_JSON_PARSER_H_INCLUDE__
#define __CAESARIA_JSON_PARSER_H_INCLUDE__

#include "variant.hpp"
#include <string>

/**
 * \enum JsonToken
 */
enum JsonToken
{
        JsonTokenNone = 0,
        JsonTokenCurlyOpen = 1,
        JsonTokenCurlyClose = 2,
        JsonTokenSquaredOpen = 3,
        JsonTokenSquaredClose = 4,
        JsonTokenColon = 5,
        JsonTokenComma = 6,
        JsonTokenString = 7,
        JsonTokenNumber = 8,
        JsonTokenTrue = 9,
        JsonTokenFalse = 10,
        JsonTokenNull = 11,
        JsonTokenCommentOpen = 12,
        JsonTokenCommentClose = 13,
        JsonTokenObjectName = 14
};

/**
 * \class Json
 * \brief A JSON data parser
 *
 * Json parses a JSON data into a QVariant hierarchy.
 */
class Json
{
public:
  /**
   * Parse a JSON string
   *
   * \param json The JSON data
   */
  static Variant parse(const std::string& json);

   /**
    * Parse a JSON string
    *
    * \param json The JSON data
    * \param success The success of the parsing
    */
   static Variant parse(const std::string &json, bool &success);

   /**
   * This method generates a textual JSON representation
   *
   * \param data The JSON data generated by the parser.
   * \param success The success of the serialization
   */
   static std::string serialize(const Variant &data, const std::string& tab);

   /**
   * This method generates a textual JSON representation
   *
   * \param data The JSON data generated by the parser.
   * \param success The success of the serialization
   *
   * \return ByteArray Textual JSON representation
   */
   static std::string serialize(const Variant &data, bool &success, const std::string& tab);

   static std::string lastParsedObject();

 private:
   /**
    * Parses a value starting from index
    *
    * \param json The JSON data
    * \param index The start index
    * \param success The success of the parse process
    *
    * \return Variant The parsed value
    */
   static Variant parseValue(const std::string &json, int &index,
                                                      bool &success);

   /**
    * Parses an object starting from index
    *
    * \param json The JSON data
    * \param index The start index
    * \param success The success of the object parse
    *
    * \return Variant The parsed object map
    */
   static Variant parseObject(const std::string &json, int &index,
                                                              bool &success);

   /**
    * Parses an array starting from index
    *
    * \param json The JSON data
    * \param index The starting index
    * \param success The success of the array parse
    *
    * \return Variant The parsed variant array
    */
   static VariantList parseArray(const std::string &json, int &index,
                                 bool &success);

   /**
    * Parses a string starting from index
    *
    * \param json The JSON data
    * \param index The starting index
    * \param success The success of the string parse
    *
    * \return QVariant The parsed string
    */
   static void parseString(const std::string &json, int &index, bool &success, std::string& str);
   
   static Variant parseObjectName(const std::string &json, int &index, bool &success, char limiters=':' );

   static void parseComment(const std::string &json, int &index, bool &success);

   /**
    * Parses a number starting from index
    *
    * \param json The JSON data
    * \param index The starting index
    *
    * \return QVariant The parsed number
    */
   static Variant parseNumber(const std::string &json, int &index);

   /**
    * Get the last index of a number starting from index
    *
    * \param json The JSON data
    * \param index The starting index
    *
    * \return The last index of the number
    */
   static int lastIndexOfNumber(const std::string &json, int index);

   /**
    * Skip unwanted whitespace symbols starting from index
    *
    * \param json The JSON data
    * \param index The start index
    */
   static void eatWhitespace(const std::string &json, int &index);

   /**
    * Check what token lies ahead
    *
    * \param json The JSON data
    * \param index The starting index
    *
    * \return int The upcoming token
    */
   static int lookAhead(const std::string &json, int index);

   /**
    * Get the next JSON token
    *
    * \param json The JSON data
    * \param index The starting index
    *
    * \return int The next JSON token
    */
   static int nextToken(const std::string &json, int &index);
};

#endif //__CAESARIA_JSON_PARSER_H_INCLUDE__
