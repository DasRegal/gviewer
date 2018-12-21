#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include "inc/line.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);
    void DrawLines(std::vector<Line::sLine> line);

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // RENDERAREA_H
