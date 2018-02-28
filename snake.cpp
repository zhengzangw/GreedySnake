#include "snake.h"
#include "gamecontroller.h"
#include "constants.h"

#include <QPainter>

Snake::Snake(Gamecontroller &controller,int SP) :
    head(0,0),
    growing(7),
    speed(SP),
    moveDirection(NoMove),
    controller(controller)
{}

QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail){
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF t1 = mapFromScene(QPointF(minX,minY));
    QPointF br = mapFromScene(QPointF(maxX,maxY));

    QRectF bound = QRectF(t1.x() , t1.y() , br.x()-t1.x()+SNAKE_SIZE , br.y()-t1.y()+SNAKE_SIZE);

    return bound;
}

QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0.5,0.5,SNAKE_SIZE, SNAKE_SIZE));

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x()+0.5,itemp.y()+0.5,SNAKE_SIZE,SNAKE_SIZE));
    }

    return path;
}

void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), QColor("#fffcb2"));
    painter->restore();
}

void Snake::moveLeft()
{
    head.rx() -= SNAKE_SIZE;
    //if (head.rx() < -MAP_SIZE) {
    //    head.rx() = MAP_SIZE;
    //}
}

void Snake::moveRight()
{
    head.rx() += SNAKE_SIZE;
    //if (head.rx() > MAP_SIZE) {
    //    head.rx() = -MAP_SIZE;
    //}
}

void Snake::moveUp()
{
    head.ry() -= SNAKE_SIZE;
    //if (head.ry() < -MAP_SIZE) {
    //    head.ry() = MAP_SIZE;
    //}
}

void Snake::moveDown()
{
    head.ry() += SNAKE_SIZE;
    //if (head.ry() > MAP_SIZE) {
    //    head.ry() = -MAP_SIZE;
    //}
}

void Snake::handleCollisions()
{
    QList<QGraphicsItem *> collisions = collidingItems();

    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_Food){
            controller.snakeAteFood(this,(Food *)collidingItem);
            growing += 1;
        }
        if (collidingItem->data(GD_Type) == GO_Wall){
            controller.snakeHitWall(this,(Wall *)collidingItem);
        }
    }

    if (tail.contains(head)){
        controller.snakeAteItself(this);
    }

}

void Snake::advance(int step)
{
    if (!step) {
        return;
    }
    if (tickCounter++ % speed != 0){
        return;
    }
    if (moveDirection == NoMove) {
        return;
    }

    if (growing > 0) {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;
    }

    switch(moveDirection){
    case MoveLeft:
         moveLeft();
         break;
    case MoveRight:
         moveRight();
         break;
    case MoveUp:
         moveUp();
         break;
    case MoveDown:
         moveDown();
         break;
    case NoMove:
         break;
    }
    controller.statechanged();
    setPos(head);
    handleCollisions();
}

void Snake::setMoveDirection(Direction direction)
{
    moveDirection = direction;
}

Snake::Direction Snake::getMoveDirection()
{
    return moveDirection;
}

void Snake::changespeed(int x)
{
    speed = x;
}

int Snake::getSpeed()
{
    return speed;
}
