#include <QApplication>
#include "ui/MainWindow.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("He Thong Dieu Phoi Lich Chay Tau");
    app.setOrganizationName("PBL2");

    MainWindow window;
    window.show();

    return app.exec();
}
