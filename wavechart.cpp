#include "wavechart.h"
#include "ui_wavechart.h"
#include<QPainter>
#include<QPen>
waveChart::waveChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::waveChart)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: black;");
}

waveChart::~waveChart()
{
    delete ui;
}

void waveChart::paintEvent(QPaintEvent *)
{
    int leftMargin = 30;
    int rightMargin = 20;
    int upMargin = 20;
    int bottomMargin = 30;

    QPoint upLeft(leftMargin, upMargin);
    QPoint upRight(this->width()-rightMargin, upMargin);
    QPoint bottomLeft(bottomMargin, this->height()-leftMargin);
    QPoint bottomRight(this->width()-rightMargin, this->height()-bottomMargin);

    QPainter painter(this);
    painter.setPen(QPen(Qt::white, 2));
    painter.drawLine(upLeft, bottomLeft);
    painter.drawLine(bottomLeft, bottomRight);

    painter.setPen(QPen(Qt::gray, 1, Qt::DashLine));
    if (this->width()>300)
    {
        painter.drawLine((upLeft+upRight)/2, (bottomLeft+bottomRight)/2);
        if (this->width()>800)
        {
            painter.drawLine(upLeft+(upRight-upLeft)/4, bottomLeft+(bottomRight-bottomLeft)/4);
            painter.drawLine(upLeft+(upRight-upLeft)*3/4, bottomLeft+(bottomRight-bottomLeft)*3/4);
        }
    }
    if (this->height()>300)
    {
        painter.drawLine((upLeft+bottomLeft)/2, (upRight+bottomRight)/2);
        if (this->height()>800)
        {
            painter.drawLine(upLeft+(bottomLeft-upLeft)/4, upRight+(bottomRight-upRight)/4);
            painter.drawLine(upLeft+(bottomLeft-upLeft)*3/4, upRight+(bottomRight-upRight)*3/4);
        }
    }

    //painter.drawText(5, 30, QString("YMax"));
    painter.setPen(QPen(Qt::green, 1));
    int chartWidth = this->width()-leftMargin-rightMargin;
    int chartHeight = this->height()-upMargin-bottomMargin;
    int yMax = 100;
    int xMax = this->xList.size();
    QPainterPath path;
    QPointF tmp;
    tmp.setX(leftMargin);
    tmp.setY(upMargin+chartHeight*(yMax-this->xList[0])/yMax);
    path.moveTo(tmp);
    for (int i = 1; i < xMax-1; i++)
    {
        tmp.setX(leftMargin+chartWidth*i/xMax);
        tmp.setY(upMargin+chartHeight*(yMax-this->xList[i])/yMax);
        path.lineTo(tmp);
    }
    painter.drawPath(path);
}
