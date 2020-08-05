#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <chrono>
#include <algorithm>
#include <sstream>
#include <vector>
#include <execution>
#include <fstream>


int main(int argc, char *argv[])
{

	QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
