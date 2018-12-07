#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class QPlainTextEdit;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow();

private:
    void createActions();

    QPlainTextEdit *textEdit;
};

#endif // EDITOR_H
