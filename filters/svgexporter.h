// Copyright (C)  2004  Pino Toscano <toscano.pino@tiscali.it>

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

#ifndef KIG_FILTERS_SVGEXPORTER_H
#define KIG_FILTERS_SVGEXPORTER_H

#include "exporter.h"

class QString;
class KigPart;
class KigWidget;

/**
 * Export to Scalable Vector Graphics (SVG)
 */
class SVGExporter
  : public KigExporter
{
public:
  ~SVGExporter();
  QString exportToStatement() const;
  QString menuEntryName() const;
  QString menuIcon() const;
  void run( const KigPart& part, KigWidget& w );
};

#endif