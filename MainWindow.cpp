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
#include <QDialog>
#include <QComboBox>
#include <SGIEngine/Utility.h>
#include <QStringList>

#include "MainWindow.h"

static void showNewDialog(){
    QDialog dialog;
    QGridLayout layout;
    QComboBox combo;
    QPushButton accept("Accept");
    QPushButton cancel("Cancel");
    std::vector<std::string> gameDirs = getSubDirectories("games/");
    QStringList games;
    for(std::string s : gameDirs){
        rapidjson::Document doc;
        if(readJsonFile("games/"+s+"/gameInfo.json", doc)){
            games << doc["name"].GetString();
        } else {
            games << s.c_str();
        }
    }
    combo.addItems(games);
    layout.addWidget(&combo, 0, 0, 1, 2);
    layout.addWidget(&accept, 1, 0);
    layout.addWidget(&cancel, 1, 1);
    dialog.setLayout(&layout);
    dialog.exec();
}

MainWindow::MainWindow() {
    file = menuBar()->addMenu("&File");
    makeNew = file->addAction("&New");
    open = file->addAction("&Open");
    save = file->addAction("&Save");
    connect(makeNew, &QAction::triggered, this, &showNewDialog);
    QWidget *mainContainer = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    QHBoxLayout *layout2 = new QHBoxLayout;
    QVBoxLayout *layout3 = new QVBoxLayout;
    QVBoxLayout *layout4 = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout3->setContentsMargins(0, 0, 0, 0);
    layout4->setContentsMargins(0, 0, 0, 0);
    QWidget *layout2Container = new QWidget;
    QWidget *layout3Container = new QWidget;
    QWidget *layout4Container = new QWidget;
    objectProperties = new QTableWidget;
    toolbar = new QMenuBar;
    toolbar->setObjectName("toolbar");
    toolbar->addAction("Add World Object");
    toolbar->addAction("Add Wall");
    toolbar->addAction("Add Floor/Ceiling");
    layout->addWidget(toolbar);
    props = new QTreeWidget;
    props->setHeaderLabel("Props");
    walls = new QTreeWidget;
    walls->setHeaderLabel("Walls");
    floors = new QTreeWidget;
    floors->setHeaderLabel("Floors");
    layout3->addWidget(props);
    layout3->addWidget(walls);
    layout3->addWidget(floors);
    layout3Container->setLayout(layout3);
    layout2->addWidget(layout3Container);
    viewport = new ViewportWidget;
    layout2->addWidget(viewport, 1);
    worldObjects = new QTreeWidget;
    layout4->addWidget(worldObjects);
    layout4->addWidget(objectProperties);
    objectProperties->setAlternatingRowColors(true);
    objectProperties->setColumnCount(2);
    objectProperties->setRowCount(8);
    objectProperties->setHorizontalHeaderLabels({"Property", "Value"});
    objectProperties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    objectProperties->verticalHeader()->hide();
    objectProperties->horizontalHeader()->setStretchLastSection(true);
    worldObjects->setHeaderLabel("World Objects");
    layout2->addWidget(layout4Container);
    layout4Container->setLayout(layout4);
    layout2Container->setLayout(layout2);
    layout->addWidget(layout2Container);
    mainContainer->setLayout(layout);
    setCentralWidget(mainContainer);
    statusBar()->addPermanentWidget(new QLabel("Objects: 0"));
    
    setWindowTitle("SGI Editor");
    setMinimumSize(800, 600);
    resize(1280, 720);    
    show();
}

