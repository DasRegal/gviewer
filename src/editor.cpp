#include <QtWidgets>
#include <QDebug>
#include <vector>

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

float EditorWindow::GetValParam(const QString &line, QString param, bool *ok, QString instr)
{
    float res = 0.0;
    // Example:
    // "G1 X100 Y200.03 F300"
    // RegExp "G1.*Y\s*(\d+\.{0,1}\d+)" for Y
    QString rxString = QString("%1.*%2\\s*(\\d+\\.{0,1}\\d+)").arg(instr, param);
    QRegExp rx(rxString);
    if (rx.indexIn(line) != -1)
    {
        res = rx.cap(1).toFloat();
        *ok = true;
    }
    else
        *ok = false;
    return res;
}

GlobState::systemType_t EditorWindow::GetSystemType(const QString &line, bool *ok)
{
    *ok = false;
    GlobState::systemType_t sysType = GlobState::ABS;

    QRegExp rx("*G90*");
    rx.setPatternSyntax(QRegExp::Wildcard);
    if (rx.exactMatch(line))
    {
        sysType = GlobState::ABS;
        *ok = true;
        return sysType;
    }

    rx.setPattern("*G91*");
    if (rx.exactMatch(line))
    {
        sysType = GlobState::REL;
        *ok = true;
        return sysType;
    }
    return sysType;
}

void EditorWindow::Parser(const QString &line)
{
    bool ok = false;
    GlobState::systemType_t sysTypeTemp;

    sysTypeTemp = GetSystemType(line, &ok);
    if (ok)
    {
        globState_.SetSystemType(sysTypeTemp);
    }

    float x = GetValParam(line, "X", &ok);
    if (ok)
    {
        globState_.SetGlobX(x, globState_.GetSystemType());
    }
    float y = GetValParam(line, "Y", &ok);
    if (ok)
    {
        globState_.SetGlobY(y, globState_.GetSystemType());
    }
    float z = GetValParam(line, "Z", &ok);
    if (ok)
    {
        globState_.SetGlobZ(z, globState_.GetSystemType());
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
