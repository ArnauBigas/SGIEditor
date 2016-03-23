/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MainWindow.cpp
 * Author: arnaubigas
 * 
 * Created on March 23, 2016, 11:54 AM
 */

#include <QMenuBar>
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QHeaderView>

#include "MainWindow.h"

MainWindow::MainWindow() {
    file = menuBar()->addMenu("&File");
    makeNew = file->addAction("&New");
    open = file->addAction("&Open");
    save = file->addAction("&Save");
    
    QWidget *mainContainer = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QVBoxLayout *layout3 = new QVBoxLayout;
    QWidget *layout2Container = new QWidget;
    QWidget *layout3Container = new QWidget;
    objectProperties = new QTableWidget;
    toolbar = new QMenuBar;
    toolbar->setObjectName("toolbar");
    toolbar->addAction("Add World Object");
    toolbar->addAction("Add Wall");
    toolbar->addAction("Add Floor/Ceiling");
    layout->addWidget(toolbar);
    toolbar->setMaximumHeight(26);
    viewport = new ViewportWidget;
    availableObjects = new QListWidget;
    worldObjects = new QTreeWidget;
    layout2->addWidget(availableObjects);
    layout2->addWidget(viewport, 1);
    layout3->addWidget(worldObjects);
    layout3->addWidget(objectProperties);
    objectProperties->setAlternatingRowColors(true);
    objectProperties->setColumnCount(2);
    objectProperties->setRowCount(8);
    objectProperties->setHorizontalHeaderLabels({"Property", "Value"});
    objectProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    objectProperties->verticalHeader()->hide();
    objectProperties->horizontalHeader()->setStretchLastSection(true);
    worldObjects->setHeaderLabel("World Objects");
    layout2->addWidget(layout3Container);
    layout3Container->setLayout(layout3);
    layout2Container->setLayout(layout2);
    layout->addWidget(layout2Container);
    mainContainer->setLayout(layout);
    setCentralWidget(mainContainer);
    statusBar()->addPermanentWidget(new QLabel("Objects: 0"));
    
    setWindowTitle("SGI Editor");
    setMinimumSize(160, 160);
    resize(480, 320);    
    show();
}

