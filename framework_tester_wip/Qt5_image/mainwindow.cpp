#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QScreen>

int randint(int low, int high)
{
    return low + std::rand() % (high - low);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    brush = QBrush("#000000");
    img = QImage("noise.png");
    width = QGuiApplication::primaryScreen()->geometry().width();
    height = QGuiApplication::primaryScreen()->geometry().height();
    setFixedSize(width, height);
    setGeometry(0, 0, width, height);
    setWindowFlags(Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        pressed = true;
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
    {
        pressed = false;
        repaint();
    }
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paint();
}

void MainWindow::drawRects(QPainter *painter)
{
    if (pressed)
    {
        painter->drawImage(QRect(0, 0, width, height), img);
    }
}


void MainWindow::paint()
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if(pressed){
        drawRects(&painter);
    }
}
