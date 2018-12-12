#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>

class QPlainTextEdit;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow();

    void loadFile(const QString &fileName);
    void calculate(const QString &gcode);

private slots:
    void open();
    void calc();

private:
    void createActions();

    QPlainTextEdit *textEdit;
};

#endif // EDITOR_H
