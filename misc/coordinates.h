#ifndef COORDINATES_H
#define COORDINATES_H

#include "../objects/point.h"

class CoordinateSystem
{
public:
  CoordinateSystem() {};
  virtual ~CoordinateSystem() {};
  virtual Point FromScreen (const QPoint& pt, const QRect& r) const = 0;
  virtual QPoint toScreen (const Point& pt, const QRect& r) const = 0;
  virtual void drawGrid ( QPainter& p ) = 0;
};

class EuclideanCoords
  : public CoordinateSystem
{
public:
  EuclideanCoords( int minX, int minY, int width, int height );
  ~EuclideanCoords() {};
  virtual Point fromScreen (const QPoint& pt, const QRect& r) const;
  virtual QPoint toScreen (const Point& pt, const QRect& r) const;
  virtual void drawGrid ( QPainter& p );
protected:
  int mMinX;
  int mMinY;
  int mWidth;
  int mHeight;
};

#endif
