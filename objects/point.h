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


#ifndef POINT_H
#define POINT_H

#include <qpoint.h>
#include <qrect.h>
#include <qcolor.h>

#include <cmath>

#include "object.h"
#include "../misc/coordinate.h"

class Point
: public Object
{
 public:
  Point() {};
  Point(double inX, double inY) : mC( inX, inY ) { complete = true;};
  Point(const Coordinate& p) : mC( p ) { complete = true; };
  Point(const Point& p) : Object(p), mC( p.getCoord() ) {};
  Point* copy() { return new Point (*this); };

  std::map<QCString,double> getParams();
  void setParams( const std::map<QCString,double>& m);

  // type identification
  virtual QCString vBaseTypeName() const { return sBaseTypeName();};
  static QCString sBaseTypeName() { return I18N_NOOP("point"); };
  virtual QCString vFullTypeName() const { return sFullTypeName(); };
  static QCString sFullTypeName() { return "Point"; };

  // general members
  virtual bool contains (const Coordinate& o, const double fault ) const;
  virtual void draw (KigPainter& p,bool showSelection = true) const;
  virtual void drawPrelim( KigPainter &, const Coordinate& ) const {};
  virtual bool inRect(const Rect& r) const { return r.contains( mC ); };
  // passing arguments
  virtual QString wantArg(const Object*) const { return 0; };
  virtual bool selectArg( Object *) { return true; }; // no args
  virtual void unselectArg( Object *) {}; // no args
  // no args => no parents
  virtual Objects getParents() const { return Objects();};
  // looks
  QColor getColor() { return Qt::black; };
  void setColor(const QColor&) {};
  //moving
  virtual void startMove(const Coordinate&);
  virtual void moveTo(const Coordinate&);
  virtual void stopMove();
//   void cancelMove();
  virtual void calc(){};

  const Coordinate& getCoord() const { return mC; };
protected:
  Coordinate mC;
  Coordinate pwwlmt; // point where we last moved to
public:
  double getX() const { return mC.x;};
  double getY() const { return mC.y;};
  void setX (const double inX) { mC.x = inX; };
  void setY (const double inY) { mC.y = inY; };

};

// midpoint of two other points
class MidPoint
  :public Point
{
public:
  MidPoint() :p1(0), p2(0) {};
  ~MidPoint(){};
  MidPoint(const MidPoint& m);

  MidPoint* copy() { return new MidPoint(*this); };

  virtual QCString vFullTypeName() const { return sFullTypeName(); };
  static QCString sFullTypeName() { return "MidPoint"; };

  QString wantArg(const Object* o) const;
  bool selectArg( Object* );
  void unselectArg (Object*);
  Objects getParents() const { Objects tmp; tmp.append(p1); tmp.append(p2); return tmp; };

  std::map<QCString,double> getParams();
  void setParams( const std:: map<QCString,double>& /*m*/);

  void startMove(const Coordinate&);
  void moveTo(const Coordinate&);
  void stopMove();
  void cancelMove();
  void calc();
protected:
  enum { howmMoving, howmFollowing } howm; // how are we moving
  Point* p1;
  Point* p2;
};

class Curve;

// this is a point which is constrained to a Curve, which means it's
// always on the curve, moving it doesn't cause it to move off it.
// ( this is very related to locuses, check locus.h and locus.cpp for
// more info...)
// it still needs lots of work...
class ConstrainedPoint
  : public Point
{
public:
  ConstrainedPoint(Curve* inC, const Coordinate& inPt);
  ConstrainedPoint(const double inP);
  ConstrainedPoint();
  ~ConstrainedPoint() {};
  ConstrainedPoint( const ConstrainedPoint& c);
  
  ConstrainedPoint* copy() { return new ConstrainedPoint(*this); };
  
  virtual QCString vFullTypeName() const { return sFullTypeName(); };
  static QCString sFullTypeName() { return "ConstrainedPoint"; };

  QString wantArg(const Object*) const;
  bool selectArg( Object* );
  void unselectArg (Object*) {};
  Objects getParents() const;

  void startMove(const Coordinate&) {};
  void moveTo(const Coordinate& pt);
  void stopMove() {};
  void cancelMove() {};
  void calc();

  double getP() { return p; };
  void setP(double inP) { p = inP; };

  std::map<QCString,double> getParams();
  void setParams( const std::map<QCString,double>& m);
protected:
  double p;
  Curve* c;
};

#endif // POINT_H
