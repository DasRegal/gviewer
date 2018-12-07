#include "inc/editor.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("G-code viewer");

    EditorWindow editorWin;
    editorWin.show();
    return app.exec();
}
