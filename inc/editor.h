#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class QPlainTextEdit;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow();

    QPlainTextEdit *textEdit;
};

#endif // EDITOR_H
