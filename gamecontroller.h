#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QMessageBox>

#include "snake.h"

class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;

class Gamecontroller : public QObject
{
    Q_OBJECT
public:
    Gamecontroller(QGraphicsScene &scene, QWidget *parent=0);
    ~Gamecontroller();

    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);

    void changehard();
    void changemiddle();
    void changeeasy();


public slots:
    void pause();
    void resume();
    void gameOver();

protected:
    bool eventFilter(QObject *object, QEvent *event);

private:
    void handleKeyPressed(QKeyEvent *event);
    void addNewFood();

    QTimer timer;
    QGraphicsScene &scene;

    Snake *snake;

    Snake::Direction previous = Snake::NoMove;
};

#endif // GAMECONTROLLER_H
