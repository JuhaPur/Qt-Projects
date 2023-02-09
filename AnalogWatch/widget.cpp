#include "widget.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QPainter>
#include <QPen>
#include <QtMath>

Widget::Widget(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, QOverload<>::of(&Widget::update));
        timer->start(1000);

        setWindowTitle(tr("Analog Clock"));
        resize(300, 300);
}

void Widget::paintEvent(QPaintEvent *)
{

    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);

       int side = qMin(width(), height());
       QTime time = QTime::currentTime().addSecs(offset);




    QPainter painter(this);
    //painter = new QPainter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.translate(width() / 2, height() / 2);
       painter.scale(side / 200.0, side / 200.0);

       painter.setPen(Qt::NoPen);
       painter.setBrush(hourColor);

       painter.save();
       painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
       painter.drawConvexPolygon(hourHand, 3);
       painter.restore();

       painter.setPen(hourColor);

           for (int i = 0; i < 12; ++i) {
               painter.drawLine(88, 0, 96, 0);
               painter.rotate(30.0);
           }

       painter.setPen(Qt::NoPen);
       painter.setBrush(minuteColor);

          painter.save();
          painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
          painter.drawConvexPolygon(minuteHand, 3);
          painter.restore();

          painter.setPen(minuteColor);

              for (int j = 0; j < 60; ++j) {
                  if ((j % 5) != 0)
                      painter.drawLine(92, 0, 96, 0);
                  painter.rotate(6.0);
              }

              QColor dateColor(0, 0, 0);
              QColor jtn(206, 205, 205);

              //painter.setPen(Qt::NoPen);
              //painter.setBrush(dateColor);
              painter.setBrush(jtn);
              painter.setPen(dateColor);
              QDateTime datetime = QDateTime::currentDateTime().addDays(dateOffset);
              setDate(&painter, datetime.date().day(), datetime.date().month());



}

void Widget::setDate(QPainter *painter, int day, int month)
{
    // Draw the frame for the date and month
    const QRect rectangle(-20, 30, 50, 30);
    painter->drawRect(rectangle);
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    QString dateString;
    if (day < 10 && month < 10){
        dateString = QString("0%1.0%2").arg(QString::number(day), QString::number(month));
    }else if(month < 10){
        dateString = QString("%1.0%2").arg(QString::number(day), QString::number(month));
    }else if (day < 10){
        dateString = QString("0%1.%2").arg(QString::number(day), QString::number(month));
    }else{
        dateString = QString("%1.%2").arg(QString::number(day), QString::number(month));
    }

    painter->drawText(rectangle, 0, dateString);

}

void Widget::setOffset(int newOffset){
    offset = newOffset;
}

int Widget::getOffset() const
{
    return offset;
}

void Widget::setDateOffset(int newDateOffset){
    dateOffset = newDateOffset;
}

int Widget::getDateOffset()const{
    return dateOffset;
}
