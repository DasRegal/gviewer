#include <QtWidgets>

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
