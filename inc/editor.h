#ifndef EDITOR_H
#define EDITOR_H

#include <QMainWindow>
#include "inc/glob_state.h"

class QPlainTextEdit;

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow();

    void LoadFile(const QString &fileName);
    void Calculate(const QString &gcode);

private slots:
    void Open();
    void Calc();

private:
    void  CreateActions();
    std::optional<float> GetValParam(const QString &line, QString param, QString instr = "G1");
    void  Parser(const QString &line);
    std::optional<GlobState::systemType_t> GetSystemType(const QString &line);

    GlobState globState_;
    QPlainTextEdit *textEdit;
};

#endif // EDITOR_H
