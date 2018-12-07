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
    QToolBar *fileToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    fileMenu->addAction(openAct);
    fileToolBar->addAction(openAct);
}
