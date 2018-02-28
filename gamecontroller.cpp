#include <QEvent>
#include <QGraphicsScene>
#include <QKeyEvent>
#include <QDateTime>
#include <QDebug>

#include "constants.h"
#include "gamecontroller.h"
#include "food.h"
#include "snake.h"
#include "mainwindow.h"
#include "wall.h"

Gamecontroller::Gamecontroller(QGraphicsScene &scene, MainWindow *parent):
    p(parent),
    scene(scene),
    snake(new Snake(*this)),
    wall(new Wall(*this)),
    point(0),
    maxpoint(0)
{
    timer.start(1000/33);

    int x,y;
    x = (int) (qrand() % 100) / 10;
    x*=10;
    y = (int) (qrand() % 100) / 10;
    y*=10;

    Food *a1 = new Food(x,y);
    scene.addItem(snake);
    scene.addItem(wall);
    scene.addItem(a1);
    scene.installEventFilter(this);

    resume();
}

Gamecontroller::~Gamecontroller()
{}

void Gamecontroller::pause()
{
    disconnect(&timer, SIGNAL(timeout()),&scene, SLOT(advance()));
}

void Gamecontroller::resume()
{
    connect(&timer,SIGNAL(timeout()),&scene,SLOT(advance()));
}

bool Gamecontroller::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *) event);
        return true;
    } else {
        return QObject::eventFilter(object,event);
    }
}

void Gamecontroller::handleKeyPressed(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            if (snake->getMoveDirection()!=Snake::MoveRight){
                snake->setMoveDirection(Snake::MoveLeft);
            }
            break;
        case Qt::Key_Right:
            if (snake->getMoveDirection()!=Snake::MoveLeft){
                snake->setMoveDirection(Snake::MoveRight);
            }
            break;
        case Qt::Key_Up:
            if (snake->getMoveDirection()!=Snake::MoveDown){
                snake->setMoveDirection(Snake::MoveUp);
            }
            break;
        case Qt::Key_Down:
            if (snake->getMoveDirection()!=Snake::MoveUp){
                snake->setMoveDirection(Snake::MoveDown);
            }
            break;
        case Qt::Key_Space:
            if (snake->getMoveDirection()==Snake::NoMove){
                snake->setMoveDirection(previous);
            } else {
                previous = snake->getMoveDirection();
                snake->setMoveDirection(Snake::NoMove);
            }

    }
}

void Gamecontroller::snakeAteFood(Snake *snake, Food *food)
{
    scene.removeItem(food);
    delete food;

    point +=1;
    addNewFood();
}

void Gamecontroller::addNewFood()
{
    int x,y;

    do {
        x = (int) (qrand() % (MAP_SIZE-10)) / 10;
        x*=10;
        y = (int) (qrand() % (MAP_SIZE-10)) / 10;
        y*=10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5,y + 5))));

    Food *food = new Food(x,y);
    scene.addItem(food);
}

void Gamecontroller::snakeAteItself(Snake *snake)
{
    QTimer::singleShot(0,this,SLOT(gameOver()));
}

void Gamecontroller::snakeHitWall(Snake *snake, Wall *wall)
{
    QTimer::singleShot(0,this,SLOT(gameOver()));
}

void Gamecontroller::gameOver()
{
    pause();
    if (point > maxpoint) maxpoint = point;
    p->showpoint(point,maxpoint);

    /*QDateTime n2 = QDateTime::currentDateTime();
    QDateTime now;
    do{   now=QDateTime::currentDateTime();   } while(n2.secsTo(now)<=0.6);*/

    scene.clear();
    point = 0;

    resume();
    snake = new Snake(*this);
    scene.addItem(snake);
    wall = new Wall(*this);
    scene.addItem(wall);
    addNewFood();
}

void Gamecontroller::changehard()
{
    snake->changespeed(1);
}

void Gamecontroller::changemiddle()
{
    snake->changespeed(3);
}

void Gamecontroller::changeeasy()
{
    snake->changespeed(4);
}
