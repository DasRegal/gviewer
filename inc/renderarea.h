#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include "line.h"

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    RenderArea(QWidget *parent = 0);

public slots:
    void DrawLines(std::vector<Line::sLine> line);

protected:
    void paintEvent(QPaintEvent *event);
    std::vector<Line::sLine> lines_;
};

#endif // RENDERAREA_H
