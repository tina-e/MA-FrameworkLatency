#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPen>
#include <QScreen>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    width = 100;
    height = 100;
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
    if (e->button() == Qt::LeftButton)
    {
        click();
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
    {
        release();
        repaint();
    }
}

void MainWindow::click()
{
    brush = QBrush(Qt::white);
}

void MainWindow::release()
{
    brush = QBrush(Qt::black);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    paint();
}

void MainWindow::paint()
{
    QPainter painter(this);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);
    painter.drawRect(0, 0, width, height);
}
