#include "wall.h"
#include "constants.h"
#include <QPainter>

Wall::Wall(Gamecontroller &controller)
{
    setData(GD_Type,GO_Wall);
}

QRectF Wall::boundingRect() const
{
    return QRect(-MAP_SIZE,-MAP_SIZE,MAP_SIZE*2,MAP_SIZE*2);
}

void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    //painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(),QColor("#ffbbcb"));

    painter->restore();
}

QPainterPath Wall::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    QList<QPointF> wall_left,wall_right;


    for (int i=-MAP_SIZE;i<=MAP_SIZE;i++){
        wall_left << QPointF(-MAP_SIZE,i);
    }

    for (int i=-MAP_SIZE;i<=MAP_SIZE;i++){
        wall_left << QPointF(i,-MAP_SIZE);
    }

    foreach (QPointF p, wall_left) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x()+1,itemp.y()+1,SNAKE_SIZE-1.3,SNAKE_SIZE-1.3));
    }

    for (int i=-MAP_SIZE;i<=MAP_SIZE;i++){
        wall_right << QPointF(MAP_SIZE,i);
    }

    for (int i=-MAP_SIZE;i<=MAP_SIZE;i++){
        wall_right << QPointF(i,MAP_SIZE);
    }

    foreach (QPointF p, wall_right) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x()+1,itemp.y()+1,SNAKE_SIZE,SNAKE_SIZE));
    }



    return path;

}
