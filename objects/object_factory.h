// object_factory.h
// Copyright (C)  2002  Dominique Devriese <devriese@kde.org>

// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
// 02111-1307, USA.

#ifndef KIG_OBJECTS_OBJECT_FACTORY_H
#define KIG_OBJECTS_OBJECT_FACTORY_H

#include "common.h"

class ObjectFactory
{
  static ObjectFactory* s;
public:

  static ObjectFactory* instance();

  RealObject* fixedPoint( const Coordinate& c );

  RealObject* sensiblePoint( const Coordinate& c,
                         const KigDocument& d,
                         const KigWidget& w
    );

  void redefinePoint( RealObject* point, const Coordinate& c,
                      const KigDocument& d, const KigWidget& w );

  RealObject* locus( const Objects& parents );

  RealObject* label( const QString& s, const Coordinate& loc );
};

#endif
