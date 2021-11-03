// SPDX-FileCopyrightText: 2004 Pino Toscano <toscano.pino@tiscali.it>

// SPDX-License-Identifier: GPL-2.0-or-later

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
  QString exportToStatement() const override;
  QString menuEntryName() const override;
  QString menuIcon() const override;
  void run( const KigPart& part, KigWidget& w ) override;
};

#endif
