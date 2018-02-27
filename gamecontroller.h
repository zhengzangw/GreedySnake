#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QTimer>

class QGraphicsScene;
class QKeyEvent;

class Snake;
class Food;
class Wall;

class Gamecontroller : public QObject
{
    Q_OBJECT
public:
    Gamecontroller(QGraphicsScene &scene, QObject *parent=0);
    ~Gamecontroller();

    void snakeAteFood(Snake *snake, Food *food);
    void snakeHitWall(Snake *snake, Wall *wall);
    void snakeAteItself(Snake *snake);

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
};

#endif // GAMECONTROLLER_H
