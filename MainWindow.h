/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.h
 * Author: arnaubigas
 *
 * Created on March 23, 2016, 11:54 AM
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTableWidget>
#include "ViewportWidget.h"

class MainWindow : public QMainWindow {
public:
    MainWindow();
private:
    //Menu stuff
    QMenu* file;
    QAction* makeNew;
    QAction* open;
    QAction* save;
    
    //Main toolbar
    QMenuBar* toolbar;

    //Main window stuff
    QTreeWidget* props;
    QTreeWidget* walls;
    QTreeWidget* floors;
    QTreeWidget* worldObjects;
    QTableWidget* objectProperties;
    ViewportWidget* viewport;
};

#endif /* MAINWINDOW_H */

