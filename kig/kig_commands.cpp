/**
 This file is part of Kig, a KDE program for Interactive Geometry...
 Copyright (C) 2002  Dominique Devriese <devriese@kde.org>

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 USA
**/

#include "kig_commands.h"
#include "kig_commands.moc"

#include "kig_part.h"

#include "../modes/mode.h"
#include "../objects/object_imp.h"

AddObjectsCommand::AddObjectsCommand(KigDocument* inDoc, const Objects& inOs)
  : KigCommand( inDoc,
		inOs.size() == 1 ?
                ObjectImp::addAStatement( inOs.front()->imp()->id() ) :
                i18n( "Add %1 objects" ).arg( os.size() ) ),
    undone(true),
    os (inOs)
{
}

AddObjectsCommand::AddObjectsCommand( KigDocument* inDoc, Object* o )
    : KigCommand ( inDoc, ObjectImp::addAStatement( o->imp()->id() ) ),
      undone( true )
{
  os.push_back( o );
};

void AddObjectsCommand::execute()
{
  for ( Objects::iterator i = os.begin(); i != os.end(); ++i )
  {
    (*i)->calc();
    document->_addObject(*i);
  }
  undone = false;
  document->mode()->objectsAdded();
};

void AddObjectsCommand::unexecute()
{
  for ( Objects::iterator i = os.begin(); i != os.end(); ++i )
  {
    document->_delObject(*i);
  };
  undone=true;
  document->mode()->objectsRemoved();
};

AddObjectsCommand::~AddObjectsCommand()
{
  if (undone) delete_all( os.begin(), os.end() );
}

RemoveObjectsCommand::RemoveObjectsCommand(KigDocument* inDoc, const Objects& inOs)
  : KigCommand(inDoc,
	       inOs.size() == 1 ?
               ObjectImp::removeAStatement( inOs.front()->imp()->id() ) :
               i18n( "Remove %1 objects" ).arg( inOs.size()) ),
    undone( false ),
    os( inOs )
{
  Objects tmp;
  // we delete the children too
  for (Objects::iterator i = os.begin(); i != os.end(); ++i )
    tmp |= (*i)->children();
  os |= tmp;
}

RemoveObjectsCommand::RemoveObjectsCommand( KigDocument* inDoc, Object* o)
  : KigCommand( inDoc, ObjectImp::removeAStatement( o->imp()->id() ) ),
    undone( false )
{
  os.push_back( o );
}

RemoveObjectsCommand::~RemoveObjectsCommand()
{
  if (!undone) delete_all(os.begin(), os.end() );
}

void RemoveObjectsCommand::execute()
{
  for ( Objects::iterator i = os.begin(); i != os.end(); ++i )
  {
    document->_delObject(*i);
  };
  undone=false;
  document->mode()->objectsRemoved();
}

void RemoveObjectsCommand::unexecute()
{
  for ( Objects::iterator i = os.begin(); i != os.end(); ++i )
  {
    (*i)->calc();
    document->_addObject(*i);
  };
  undone = true;
  document->mode()->objectsAdded();
}

void MoveCommand::execute()
{
}

void MoveCommand::unexecute()
{
}
