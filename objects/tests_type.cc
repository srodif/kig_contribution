// tests_type.cc
// Copyright (C)  2004  Dominique Devriese <devriese@kde.org>

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

#include "tests_type.h"

#include "line_imp.h"
#include "point_imp.h"
#include "bogus_imp.h"

static const ArgsParser::spec argsspecAreParallel[] =
{
  { AbstractLineImp::stype(), I18N_NOOP( "Is this line parallel ?" ) },
  { AbstractLineImp::stype(), I18N_NOOP( "Parallel to this line ?" ) }
};

AreParallelType::AreParallelType()
  : ArgsParserObjectType( "AreParallel",
                         argsspecAreParallel, 2 )
{
}

AreParallelType::~AreParallelType()
{
}

const AreParallelType* AreParallelType::instance()
{
  static const AreParallelType t;
  return &t;
}

ObjectImp* AreParallelType::calc( const Args& parents, const KigDocument& ) const
{
  if ( ! margsparser.checkArgs( parents ) ) return new InvalidImp;
  const LineData& l1 = static_cast<const AbstractLineImp*>( parents[0] )->data();
  const LineData& l2 = static_cast<const AbstractLineImp*>( parents[1] )->data();

  if ( l1.isParallelTo( l2 ) )
    return new TestResultImp( i18n( "These lines are parallel." ) );
  else
    return new TestResultImp( i18n( "These lines are not parallel." ) );

}

const ObjectImpType* AreParallelType::resultId() const
{
  return TestResultImp::stype();
}

static const ArgsParser::spec argsspecAreOrthogonal[] =
{
  { AbstractLineImp::stype(), I18N_NOOP( "Is this line orthogonal ?" ) },
  { AbstractLineImp::stype(), I18N_NOOP( "Orthogonal to this line ?" ) }
};

AreOrthogonalType::AreOrthogonalType()
  : ArgsParserObjectType( "AreOrthogonal",
                         argsspecAreOrthogonal, 2 )
{
}

AreOrthogonalType::~AreOrthogonalType()
{
}

const AreOrthogonalType* AreOrthogonalType::instance()
{
  static const AreOrthogonalType t;
  return &t;
}

ObjectImp* AreOrthogonalType::calc( const Args& parents, const KigDocument& ) const
{
  if ( ! margsparser.checkArgs( parents ) ) return new InvalidImp;
  const LineData& l1 = static_cast<const AbstractLineImp*>( parents[0] )->data();
  const LineData& l2 = static_cast<const AbstractLineImp*>( parents[1] )->data();

  if ( l1.isOrthogonalTo( l2 ) )
    return new TestResultImp( i18n( "These lines are orthogonal." ) );
  else
    return new TestResultImp( i18n( "These lines are not orthogonal." ) );

}

const ObjectImpType* AreOrthogonalType::resultId() const
{
  return TestResultImp::stype();
}

static const ArgsParser::spec argsspecAreCollinear[] =
{
  { PointImp::stype(), I18N_NOOP( "Check collinearity of this point" ) },
  { PointImp::stype(), I18N_NOOP( "and this second point" ) },
  { PointImp::stype(), I18N_NOOP( "with this third point" ) }
};

AreCollinearType::AreCollinearType()
  : ArgsParserObjectType( "AreCollinear",
                         argsspecAreCollinear, 3 )
{
}

AreCollinearType::~AreCollinearType()
{
}

const AreCollinearType* AreCollinearType::instance()
{
  static const AreCollinearType t;
  return &t;
}

ObjectImp* AreCollinearType::calc( const Args& parents, const KigDocument& ) const
{
  if ( ! margsparser.checkArgs( parents ) ) return new InvalidImp;
  const Coordinate& p1 = static_cast<const PointImp*>( parents[0] )->coordinate();
  const Coordinate& p2 = static_cast<const PointImp*>( parents[1] )->coordinate();
  const Coordinate& p3 = static_cast<const PointImp*>( parents[2] )->coordinate();

  if ( areCollinear( p1, p2, p3 ) )
    return new TestResultImp( i18n( "These points are collinear." ) );
  else
    return new TestResultImp( i18n( "These points are not collinear." ) );
}

const ObjectImpType* AreCollinearType::resultId() const
{
  return TestResultImp::stype();
}
