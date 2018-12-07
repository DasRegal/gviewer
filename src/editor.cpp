#include <QtWidgets>

#include "inc/editor.h"

EditorWindow::EditorWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);
}
