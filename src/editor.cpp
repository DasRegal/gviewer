#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <optional>

#include "inc/editor.h"
#include "inc/glob_state.h"
#include "inc/plotter.h"
#include "inc/renderarea.h"

EditorWindow::EditorWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);
    Plotter plotter;
    CreateActions();
}

void EditorWindow::CreateActions()
{
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    QToolBar *commonToolBar = addToolBar(tr("File"));

    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/images/open.png"));
    QAction *openAct = new QAction(openIcon, tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, &QAction::triggered, this, &EditorWindow::Open);
    fileMenu->addAction(openAct);
    commonToolBar->addAction(openAct);

    QMenu *calcMenu = menuBar()->addMenu(tr("&Calc"));

    const QIcon calcIcon = QIcon::fromTheme("gcode-calc", QIcon(":/images/calc.png"));
    QAction *calcAct = new QAction(calcIcon, tr("Calc"), this);
    calcAct->setStatusTip(tr("Calculate view"));
    connect(calcAct, &QAction::triggered, this, &EditorWindow::Calc);
    calcMenu->addAction(calcAct);
    commonToolBar->addAction(calcAct);
}

void EditorWindow::Open()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty())
        LoadFile(fileName);
}

void EditorWindow::LoadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
       return;
    }

    QTextStream in(&file);
    textEdit->setPlainText(in.readAll());
}

std::optional<float> EditorWindow::GetValParam(const QString &line, QString param)
{
    // Example:
    // "G1 X100 Y200.03 F300"
    // RegExp "G[01].*Y\s*(-{0,1}\d*\.{0,1}\d+)" for Y
    QString rxString = QString("G[01].*%2\\s*(-{0,1}\\d*\\.{0,1}\\d+)").arg(param);
    QRegExp rx(rxString);
    rx.setPatternSyntax(QRegExp::RegExp);
    if (rx.indexIn(line) != -1)
        return std::optional<float>{rx.cap(1).toFloat()};
    else
        return std::nullopt;
}

std::optional<GlobState::systemType_t> EditorWindow::GetSystemType(const QString &line)
{
    QRegExp rx("*G90*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if (rx.exactMatch(line))
    {
        return std::optional<GlobState::systemType_t>{GlobState::ABS};
    }

    rx.setPattern("*G91*");
    if (rx.exactMatch(line))
    {
        return std::optional<GlobState::systemType_t>{GlobState::REL};
    }

    return std::nullopt;
}

std::optional<bool> EditorWindow::IsLineDraw(const QString &line)
{
    QRegExp rx("*G1*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if (rx.exactMatch(line))
    {
        return std::optional<bool>{ true };
    }

    rx.setPattern("*G0*");
    if (rx.exactMatch(line))
    {
        return std::optional<bool>{ false };
    }

    return std::nullopt;
}

void EditorWindow::Parser(const QString &line)
{
    std::optional<GlobState::systemType_t> systemType = GetSystemType(line);
    if (systemType)
    {
        globState_.SetSystemType(*systemType);
        return;
    }

    bool isModify = false;
    GlobState::formatLine_t formatLine;
    globState_.GetFormatLine(&formatLine);

    Point point;
    if (globState_.IsListEmpty())
    {
        point.SetX(0.0);
        point.SetY(0.0);
        point.SetZ(0.0);

        formatLine.line.start = point;

    }
    else
    {
        point.SetX(globState_.GetGlobX());
        point.SetY(globState_.GetGlobY());
        point.SetZ(globState_.GetGlobZ());

        formatLine.line.start = point;
    }

    std::optional<float> val = GetValParam(line, "X");
    if (val)
    {
        globState_.SetGlobX(*val, globState_.GetSystemType());
        isModify = true;
    }

    val = GetValParam(line, "Y");
    if (val)
    {
        globState_.SetGlobY(*val, globState_.GetSystemType());
        isModify = true;
    }

    val = GetValParam(line, "Z");
    if (val)
    {
        globState_.SetGlobZ(*val, globState_.GetSystemType());
        isModify = true;
    }

    std::optional<bool > isDraw = IsLineDraw(line);
    if (isDraw != std::nullopt)
    {
        formatLine.line.isVisible = *isDraw;
    }

    point.SetX(globState_.GetGlobX());
    point.SetY(globState_.GetGlobY());
    point.SetZ(globState_.GetGlobZ());
    formatLine.line.end = point;

    globState_.AddLineToList(formatLine);
    globState_.SetFormatLine(formatLine);
}

void EditorWindow::Calc()
{
    plotter.show();
    QString gcode = textEdit->toPlainText();
    if (!gcode.isEmpty())
        Calculate(gcode);
}

void EditorWindow::Calculate(const QString &gcode)
{
    QString s(gcode);
    QTextStream text(&s);

    while(!text.atEnd())
    {
        QString line = text.readLine();
        Parser(line);
    }

    plotter.DrawLines(globState_.GetList());
}
