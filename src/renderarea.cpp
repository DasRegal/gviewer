#include <QtGui>
#include <QWidget>

#include "inc/renderarea.h"
#include "inc/line.h"
#include "inc/point.h"

class QSpinBox;

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QRect rect(10, 20, 80, 60);

    QPainterPath path;
    path.moveTo(20, 80);
    path.lineTo(20, 30);
    path.cubicTo(80, 0, 50, 50, 80, 80);

    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::DrawLines(std::vector<Line::sLine> lines)
{
    QPainter painter(this);
    painter.save();
    for (Line::sLine line : lines)
    {
        if (line.isVisible)
        {
            Point start = line.start;
            Point end = line.end;
            painter.drawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());
        }
    }
    painter.restore();
}
