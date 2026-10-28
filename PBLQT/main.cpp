#include <QApplication>
#include <QDir>
#include <QFileInfo>
#include "ui/MainWindow.h"

void setProjectFolder()
{
    QDir folder(QApplication::applicationDirPath());

    while (true)
    {
        if (QFileInfo::exists(folder.filePath("data/trains.dat")))
        {
            QDir::setCurrent(folder.absolutePath());
            return;
        }

        if (!folder.cdUp())
            return;
    }
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("He Thong Dieu Phoi Lich Chay Tau");
    app.setOrganizationName("PBL2");

    setProjectFolder();

    MainWindow window;
    window.show();

    return app.exec();
}
