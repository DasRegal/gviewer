#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include "line.h"

class RenderArea;

class Plotter : public QWidget
{
    Q_OBJECT

public:
    Plotter();
    void DrawLines(std::vector<Line::sLine> lines);

private:
    RenderArea *renderArea;
};

#endif // PLOTTER_H
