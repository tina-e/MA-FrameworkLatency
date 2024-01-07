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
    width = QGuiApplication::primaryScreen()->geometry().width();
    height = QGuiApplication::primaryScreen()->geometry().height();
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
    for(int i = 0; i < 1000; i++)
    {
        int w = randint(100, 500);
        int h = randint(100, 500);
        int x = randint((int) width/6, width - w);
        int y = randint(0, height - h);
        int r = randint(0, 255);
        int g = randint(0, 255);
        int b = randint(0, 255);
        brush = QBrush(QColor(r, g, b));
        painter->setBrush(brush);
        painter->drawRect(x, y, w, h);
    }
    brush = QBrush(Qt::white);
    painter->setBrush(brush);
    painter->drawRect(0, 0, 300, 300);
}


void MainWindow::paint()
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);

    if(pressed){
        drawRects(&painter);
    }
}
