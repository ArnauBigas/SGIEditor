/* 
 * File:   main.cpp
 * Author: TheArni
 *
 * Created on March 22, 2016
 */

#include <QApplication>
#include <QFile>
#include "MainWindow.h"

int main (int argc, char **argv) {
    QApplication app(argc, argv);
    
    QFile file("style.css");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    
    app.setStyleSheet(styleSheet);

    MainWindow window;

    return app.exec();
}