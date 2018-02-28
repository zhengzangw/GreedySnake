#ifndef WALL_H
#define WALL_H

#include <QGraphicsItem>
#include "gamecontroller.h"

class Wall : public QGraphicsItem
{
public:
     Wall(Gamecontroller &controller);

     QRectF boundingRect() const;
     void paint(QPainter *painter,const QStyleOptionGraphicsItem *, QWidget *);

     QPainterPath shape() const;
};

#endif // WALL_H
