#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constants.h"
#include "gamecontroller.h"

#include <QGraphicsView>
#include <QTimer>

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    scene(new QGraphicsScene(this)),
    view(new QGraphicsView(scene,this)),
    game(new Gamecontroller(*scene,this))
{
    setWindowTitle(tr("GreedySnake"));

    aboutAction = new QAction(tr("&About..."),this);
    aboutAction->setStatusTip(tr("View information about this game."));
    connect(aboutAction,&QAction::triggered,this,&MainWindow::showabout);

    pauseAction = new QAction(tr("&Pause"),this);
    pauseAction->setStatusTip(tr("Pause"));
    pauseAction->setShortcut(QKeySequence::Redo);
    connect(pauseAction,&QAction::triggered,game,&Gamecontroller::pause);

    QMenu *General = menuBar()->addMenu(tr("General"));
    General->addAction(aboutAction);
    General->addAction(pauseAction);

    statusBar();

    setCentralWidget(view);
    resize(600,600);

    initScene();
    initSceneBackground();

    QTimer::singleShot(0,this,SLOT(adjustViewSize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::adjustViewSize()
{
    view->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);
}

void MainWindow::initScene()
{
    scene->setSceneRect(-100,-100,200,200);
}

void MainWindow::initSceneBackground()
{
    QPixmap bg(TILE_SIZE, TILE_SIZE);

    QPainter p(&bg);
    QPen pen(QColor("#33FFDD"), 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    p.setBrush(QBrush("#CCFF99"));
    p.setPen(QPen(pen));
    p.drawRect(0,0,TILE_SIZE,TILE_SIZE);

    view->setBackgroundBrush(QBrush(bg));
}

void MainWindow::showabout()
{
    QMessageBox::information(this, tr("Information"),tr("This is a trival game. Just enjoy it!"));
}
