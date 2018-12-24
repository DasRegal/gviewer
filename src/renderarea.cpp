#include <QtGui>
#include <QWidget>

#include "../inc/renderarea.h"
#include "../inc/line.h"
#include "../inc/point.h"

class QSpinBox;

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);
    for (Line::sLine line : lines_)
    {
        if (line.isVisible)
        {
            Point start = line.start;
            Point end = line.end;
            painter.drawLine(start.GetX(), start.GetY(), end.GetX(), end.GetY());
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(palette().dark().color());
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

void RenderArea::DrawLines(std::vector<Line::sLine> lines)
{
    lines_ = lines;
    update();
}
