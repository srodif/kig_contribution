// locus_imp.cc
// Copyright (C)  2003  Dominique Devriese <devriese@kde.org>

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

#include "locus_imp.h"

#include "bogus_imp.h"

LocusImp::~LocusImp()
{
  delete mhier;
}

bool LocusImp::inherits( int type ) const
{
  return type == ID_LocusImp ? true : Parent::inherits( type );
}

ObjectImp* LocusImp::transform( const Transformation& ) const
{
  return new InvalidImp;
}

void LocusImp::draw( KigPainter& p ) const
{

}
