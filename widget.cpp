#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->r = 100;

    this->setMinimumHeight(204);
    this->setMinimumWidth(204);
    this->setMaximumHeight(204);
    this->setMaximumWidth(204);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);


    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(1000);
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *e)
{

    time = QTime::currentTime();
    QPainter painter(this);
    // 反走样
    painter.setRenderHint(QPainter::Antialiasing, true);
    //设置画刷为黑色
    painter.setBrush(Qt::black);

    // 平移坐标系原点至中心点
    painter.translate(this->r+1 , this->r+1);
    //绘制表盘
    painter.drawEllipse(-this->r,-this->r,this->r * 2 ,this->r * 2 );
    //设置画笔颜色
    QPen pen(QColor(255, 255, 255));
    // 设置画笔颜色
    painter.setPen(pen);
    // 绘制分钟
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(this->r - 5, 0, this-> r , 0);
        painter.rotate(6.0);
    }
    pen.setWidth(2);
    painter.setPen(pen);
    //绘制时
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(this->r - 10, 0, this->r , 0);
        painter.rotate(30.0);
    }
    //绘制时针和分针
    //时
    painter.save();
    painter.rotate(-180);
    painter.rotate( 30.0 * ((time.hour()  + time.minute() / 60.0) ));
    painter.drawLine(-0,-8,0,this->r - 60);
    painter.restore();
    //分
    painter.save();
    painter.rotate(-180);
    painter.rotate( 6.0 * (time.minute()));
    painter.drawLine(-0,-8,0,this->r / 2);
    painter.restore();
    //秒
    painter.save();
    painter.rotate(-180);
    painter.rotate( 6.0 * time.second());
    pen.setWidth(1);
    painter.setPen(pen);
    painter.drawLine(-0,-8,0,this->r - 30);
    painter.restore();
    //中心位置绘制一个圆 360 60 6 1
    painter.setBrush(Qt::white);
    painter.drawEllipse(-2,-2,4,4);
    painter.setBrush(Qt::gray);
    painter.drawEllipse(-2,-2,4,4);
    //绘制小时文本
    QFont font = painter.font();
    font.setBold(true);
    painter.setFont(font);
    int pointSize = font.pointSize();
    int nHour = 0;
    for (int i = 0; i < 12; ++i) {
        nHour = i + 3;
        if (nHour > 12)
            nHour -= 12;
        painter.drawText(textRectF(this->r*0.75, pointSize, i * 30), Qt::AlignCenter, QString::number(nHour));
    }
}
QRectF Widget::textRectF(double radius, int pointSize, double angle)
{
    QRectF rectF;
    rectF.setX(radius*qCos(angle*M_PI/180.0) - pointSize*2);
    rectF.setY(radius*qSin(angle*M_PI/180.0) - pointSize/2.0);
    rectF.setWidth(pointSize*4);
    rectF.setHeight(pointSize);
    return rectF;
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    this->startX = event->x();
    this->startY = event->y();
    this->isPressed = true;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    int moveX = event->x() -  this->startX;
    int moveY = event->y() -  this->startY;
    if(isPressed)
        this->move(this->x()+moveX,this->y()+moveY);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    this->startX = 0;
    this->startY = 0;
    this->isPressed = false;
}
