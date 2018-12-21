#include <QtGui>
#include <QGridLayout>

#include "inc/plotter.h"
#include "inc/renderarea.h"

Plotter::Plotter()
{
    renderArea = new RenderArea;
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    setLayout(mainLayout);

    setWindowTitle(tr("Graph"));
}

void Plotter::DrawLines(std::vector<Line::sLine> lines)
{
    renderArea->DrawLines(lines);
}
