#include "init.h"
#include <QApplication>
#include <QStyleFactory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Init w;
    w.show();
    w.setWindowTitle("uGDL");

    QApplication::setStyle(QStyleFactory::create("Fusion"));
       QPalette p;
       p = qApp->palette();
       p.setColor(QPalette::Window, QColor(53,53,53));
       p.setColor(QPalette::Button, QColor(53,53,53));
       p.setColor(QPalette::Highlight, QColor(142,45,197));
       p.setColor(QPalette::ButtonText, QColor(255,255,255));
       qApp->setPalette(p);

    return a.exec();
}
