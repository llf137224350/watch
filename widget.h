#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>
#include <QPen>
#include <QtMath>
#include <QTime>
#include <QTimer>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *e);
private:
    int r;
    int startX,startY;
    bool isPressed;

    QTime time;
    //绘制时间
    QRectF textRectF(double radius, int pointSize, double angle);
};

#endif // WIDGET_H
