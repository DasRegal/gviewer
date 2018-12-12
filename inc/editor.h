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
    float getValParam(const QString &line, QString param, bool *ok = nullptr, QString instr = "G1");

    QPlainTextEdit *textEdit;
};

#endif // EDITOR_H
