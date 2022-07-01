#include "mainwindow.h"
#include "test.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    test::test_noise testnoise;
//    testnoise.test_itrace_noise();
    test::test_capaitance testcapitance;
    testcapitance.test_itrace_capaitance();

    w.show();
    return a.exec();
}
