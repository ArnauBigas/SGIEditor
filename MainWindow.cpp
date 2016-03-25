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
#include <QTreeWidgetItem>
#include <SGIEngine/RenderEngine.h>
#include <SGIEngine/WorldObject.h>

#include "MainWindow.h"
#include "GameDialog.h"

MainWindow* instance;

MainWindow* MainWindow::getInstance(){
    return instance;
}

MainWindow::MainWindow() {
    instance = this;
    RenderEngine::init("SGI Editor");
    file = menuBar()->addMenu("&File");
    makeNew = file->addAction("&New");
    open = file->addAction("&Open");
    save = file->addAction("&Save");
    connect(makeNew, &QAction::triggered, this, &showGameDialog);
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

void MainWindow::updateAvailableObjects(){
    std::map<std::string, WorldObject*>& objs = getWorldObjectMap();
    for(std::pair<std::string, WorldObject*> obj : objs){
        int firstLimit = obj.first.find_first_of(":");
        int lastLimit = obj.first.find_first_of(":", firstLimit + 1);
        std::string type = obj.first.substr(0, firstLimit);
        std::string domain = obj.first.substr(firstLimit + 1, lastLimit - firstLimit - 1);
        std::string objName = obj.first.substr(lastLimit+1);
        if (type == "prop") {
            QList<QTreeWidgetItem*> domainList = props->findItems(QString::fromUtf8(domain.data(), domain.size()), Qt::MatchContains|Qt::MatchRecursive, 0);
            QTreeWidgetItem* domainItem;
            if(domainList.isEmpty()){
                domainItem = new QTreeWidgetItem;
                domainItem->setText(0, QString::fromUtf8(domain.data(), domain.size()));
                props->addTopLevelItem(domainItem);
            } else {
                domainItem = domainList[0];
            }
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, QString::fromUtf8(objName.data(), objName.size()));
            domainItem->addChild(item);
        } else if (type == "wall") {
            QList<QTreeWidgetItem*> domainList = walls->findItems(QString::fromUtf8(domain.data(), domain.size()), Qt::MatchContains|Qt::MatchRecursive, 0);
            QTreeWidgetItem* domainItem;
            if(domainList.isEmpty()){
                domainItem = new QTreeWidgetItem;
                domainItem->setText(0, QString::fromUtf8(domain.data(), domain.size()));
                walls->addTopLevelItem(domainItem);
            } else {
                domainItem = domainList[0];
            }
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, QString::fromUtf8(objName.data(), objName.size()));
            domainItem->addChild(item);
        } else if (type == "floor") {
            QList<QTreeWidgetItem*> domainList = floors->findItems(QString::fromUtf8(domain.data(), domain.size()), Qt::MatchContains|Qt::MatchRecursive, 0);
            QTreeWidgetItem* domainItem;
            if(domainList.isEmpty()){
                domainItem = new QTreeWidgetItem;
                domainItem->setText(0, QString::fromUtf8(domain.data(), domain.size()));
                floors->addTopLevelItem(domainItem);
            } else {
                domainItem = domainList[0];
            }
            QTreeWidgetItem* item = new QTreeWidgetItem;
            item->setText(0, QString::fromUtf8(objName.data(), objName.size()));
            domainItem->addChild(item);
        }
    }
}