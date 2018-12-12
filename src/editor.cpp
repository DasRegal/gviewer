#include <QtWidgets>
#include <QDebug>

#include "inc/editor.h"

EditorWindow::EditorWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);

    createActions();
}

void EditorWindow::createActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *commonToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &EditorWindow::open);
    fileMenu->addAction(openAct);
    commonToolBar->addAction(openAct);

    QMenu *calcMenu = menuBar()->addMenu(tr("&Calc"));

    const QIcon calcIcon = QIcon::fromTheme("gcode-calc", QIcon(":/images/calc.png"));
    QAction *calcAct = new QAction(calcIcon, tr("Calc"), this);
    calcAct->setStatusTip(tr("Calculate view"));
    connect(calcAct, &QAction::triggered, this, &EditorWindow::calc);
    calcMenu->addAction(calcAct);
    commonToolBar->addAction(calcAct);
}

void EditorWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        loadFile(fileName);
}

void EditorWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
       return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
}

float EditorWindow::getValParam(const QString &line, QString param, bool *ok, QString instr)
{
    float res = 0.0;
    // Example:
    // "G1 X100 Y200.03 F300"
    // RegExp "G1.*Y\s*(\d+\.{0,1}\d+)" for Y
    QString rxString = QString("%1.*%2\\s*(\\d+\\.{0,1}\\d+)").arg(instr, param);
    QRegExp rx(rxString);
    if (rx.indexIn(line) != -1)
    {
        res = rx.cap(1).toFloat();
        *ok = true;
    }
    else
        *ok = false;
    return res;
}

void EditorWindow::calc()
{
    QString gcode = textEdit->toPlainText();
    if (!gcode.isEmpty())
        calculate(gcode);
}

void EditorWindow::calculate(const QString &gcode)
{
    QString s(gcode);
    QTextStream text(&s);
    while(!text.atEnd())
    {
        bool ok = false;
        QString line = text.readLine();
        float x = getValParam(line, "X", &ok);
        if (ok)
            qDebug() << x;
    }
}
