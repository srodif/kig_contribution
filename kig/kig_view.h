/**
 This file is part of Kig, a KDE program for Interactive Geometry...
 Copyright (C) 2002  Dominique Devriese
 
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


#ifndef KIG_VIEW_H
#define KIG_VIEW_H

#include <qwidget.h>

#include <kdebug.h>
#include <kpopupmenu.h>
#include <kparts/part.h>

#include <vector>

#include "../objects/object.h"
//#include "../misc/coordinates.h"

class KigDocument;

class KigView
  : public QWidget, public KXMLGUIClient
{
  Q_OBJECT
public:
  KigView( KigDocument* inDoc, QWidget* parent = 0, const char* name = 0, bool inIsKiosk = false);
  ~KigView();

  void drawScreen( QPaintDevice* d );

  void startMovingSos( const QPoint& );

public slots:
  void startKioskMode();
  void endKioskMode();

  // this is connected to KigDocument::suggestRect, check that signal 
  // out for an explanation...
  void recenterScreen();
  // ...
  void zoomIn();
  void zoomOut();
  // ...

signals:
  void endKiosk();
signals:
  void setStatusBarText(const QString&);

protected:
  void displayText(QString s = QString::null) { tbd = s; emit setStatusBarText(s); if (tbd) drawTbd(); };

  KigDocument* document;
  // what the cursor currently looks like
  QPoint plc; // point last clicked
  QPoint pmt; // point moved to
  Objects oco; // objects clicked on
  QString tbd; // text being displayed
  // if a user clicks on a selected point, this can either be for
  // moving or for deselecting.  We first assume it's for deselecting,
  // until he moves far enough away from the place he clicked.  Then
  // we set this variable to true.
  bool isMovingObjects;
  bool isDraggingRect;

protected:
  // we reimplement these from QWidget to suit our needs
  void mousePressEvent (QMouseEvent* e);
  void mouseMoveEvent (QMouseEvent* e);
  void mouseReleaseEvent (QMouseEvent* e);
  void paintEvent (QPaintEvent* e);
  void resizeEvent(QResizeEvent*);

protected:
  // drawing: i tried to optimise this as much as possible, using ideas
  // from kgeo
  // we keep a picture ( stillPix ) of what the still objects look like,
  // and on moving,  we only draw the other on a copy of this pixmap.
  // furthermore,  on drawing the other, we only draw what is in
  // document->sos->getSpan()
  // another thing: it turns out that working on the pixmaps isn't
  // that slow, but working on the widget is.  So we try to reduce the
  // amount of work we spend on the widget. (i got this idea from the
  // kgeo, all credits for this should go to marc.bartsch@web.de) : objects
  // have a getObjectOverlay function,
  // in which they specify some rects which they occupy.  We only
  // bitBlt those rects onto the widget. This is only done on moving,
  // since that's where speed matters most... 

  // redraw the stillPix (the grid and such...
  void redrawStillPix();
  // this means bitBlting "curPix" on "this"
  void updateWidget( bool needRedraw = false);
  // this means bitBlting "stillPix" on "curPix"
  void updateCurPix();
  // draw a single object (on p)
  void drawObject(const Object* o, KigPainter& p);
  // draw these objects (on p)
  void drawObjects(const Objects& os, KigPainter& p);
  // draw the Text Being Displayed (on curPix)
  // @ref displayText()
  void drawTbd();
  // draw the rect being dragged for selecting objects... (on curPix)
  // @ref isDraggingRect
  void drawRect();
  // draw the grid... (on stillPix)
  void drawGrid( KigPainter& p );
  // draw the obc preliminarily... (i.e. before it's entirely
  // constructed) (on curPix)
  void drawPrelim(); 

public slots:
  // redraw everything...
  void updateAll()
  {
    redrawStillPix();
    updateCurPix();
    updateWidget();
  };
  // update one object on the screen...
  void updateObject(const Object* o)
  {
    {
      KigPainter p( this, &stillPix );
      drawObject(o, p);
    }
    {
      KigPainter p( this, &curPix );
      drawObject(o, p);
    };
    updateWidget();
  };
  // update a few objects...
  void updateObjects(const Objects& o)
  {
    {
      KigPainter p( this, &stillPix );
      drawObjects(o, p);
    }
    {
      KigPainter p( this, &curPix );
      drawObjects(o, p);
    };
    updateWidget();
  };

public:
  // the part of the document we're currently showing, this is
  // calculated from KigDocument::suggestedRect, together with our
  // showOffset and scale...
  Rect showingRect();
  Rect matchScreenShape( const Rect& r );
  double pixelWidth();

  QPoint toScreen( const Coordinate p );
  inline QRect toScreen( const Rect r )
  {
    return QRect( toScreen( r.bottomLeft()), toScreen( r.topRight() ) ).normalize();
  };

  Coordinate fromScreen( const QPoint& p );
  inline Rect fromScreen( const QRect& r )
  {
    return Rect( fromScreen(r.topLeft()), fromScreen(r.bottomRight() ) ).normalized();
  };

protected:
  QPixmap stillPix; // What Do the Still Objects Look Like
  QPixmap curPix; // temporary, gets bitBlt'd (copied) onto the widget
		  // (to avoid flickering)
  std::vector<QRect> overlay, oldOverlay;

  void appendOverlay( const QRect& r )
  {
    overlay.push_back(r);
  }

  friend class KigPainter;

protected:
  QDialog* kiosk;
  KPopupMenu* kiosKontext;
  KigView* kioskView;
  bool isKiosk;

  /**
   * what part of the document are we showing...
   */
  Rect mViewRect;

  void setupActions();
};
#endif
