#include <QtWidgets>
#include <QDebug>
#include <vector>
#include <optional>

#include "inc/editor.h"
#include "inc/glob_state.h"

EditorWindow::EditorWindow()
    : textEdit(new QPlainTextEdit)
{
    setCentralWidget(textEdit);

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

std::optional<float> EditorWindow::GetValParam(const QString &line, QString param, QString instr)
{
    // Example:
    // "G1 X100 Y200.03 F300"
    // RegExp "G1.*Y\s*(\d+\.{0,1}\d+)" for Y
    QString rxString = QString("%1.*%2\\s*(\\d+\\.{0,1}\\d+)").arg(instr, param);
    QRegExp rx(rxString);
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

void EditorWindow::Parser(const QString &line)
{
    std::optional<GlobState::systemType_t> systemType = GetSystemType(line);
    if (systemType)
    {
        globState_.SetSystemType(*systemType);
    }

    std::optional<float> val = GetValParam(line, "X");
    if (val)
    {
        globState_.SetGlobX(*val, globState_.GetSystemType());
    }

    val = GetValParam(line, "Y");
    if (val)
    {
        globState_.SetGlobY(*val, globState_.GetSystemType());
    }

    val = GetValParam(line, "Z");
    if (val)
    {
        globState_.SetGlobZ(*val, globState_.GetSystemType());
    }
}

void EditorWindow::Calc()
{
    QString gcode = textEdit->toPlainText();
    if (!gcode.isEmpty())
        Calculate(gcode);
}

void EditorWindow::Calculate(const QString &gcode)
{
    QString s(gcode);
    QTextStream text(&s);

    typedef struct
    {
        uint countPoint;
        bool isCompleteLine;
        bool isDraw;

    }  formatLine_t;

    formatLine_t xPoint{.countPoint = 0, .isCompleteLine = false, .isDraw = true};
    formatLine_t yPoint{.countPoint = 0, .isCompleteLine = false, .isDraw = true};
    formatLine_t zPoint{.countPoint = 0, .isCompleteLine = false, .isDraw = true};



    while(!text.atEnd())
    {

        QString line = text.readLine();
        Parser(line);

    }
}
