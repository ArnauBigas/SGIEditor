#include <QDialog>
#include <QComboBox>
#include <SGIEngine/Utility.h>
#include <QStringList>
#include <QGridLayout>
#include <QPushButton>
#include <iostream>
#include <SGIEngine/ResourceEngine.h>

#include "GameDialog.h"
#include "MainWindow.h"

QDialog* dialog = 0;
QComboBox* combo = 0;
std::vector<std::string> gameDirs;

void acceptFunc(){
    dialog->close();
    setResourceLocation("games/"+gameDirs[combo->currentIndex()]+"/");
    MainWindow::getInstance()->viewport->makeCurrent();
    loadAllResources();
    MainWindow::getInstance()->updateAvailableObjects();
    MainWindow::getInstance()->viewport->world = new World();
    MainWindow::getInstance()->viewport->world->addObject(getWorldObject("prop:vanilla:blaster"));
    MainWindow::getInstance()->viewport->setupCamera();
}

void showGameDialog(){
    if(dialog == 0 && combo == 0){
        dialog = new QDialog;
        QGridLayout* layout = new QGridLayout(dialog);
        combo = new QComboBox(dialog);
        QPushButton* accept = new QPushButton("Accept", dialog);
        dialog->connect(accept, &QPushButton::clicked, dialog, &acceptFunc);
        QPushButton* cancel = new QPushButton("Cancel", dialog);
        dialog->connect(cancel, &QPushButton::clicked, dialog, &QDialog::close);
        layout->addWidget(combo, 0, 0, 1, 2);
        layout->addWidget(accept, 1, 0);
        layout->addWidget(cancel, 1, 1);
        dialog->setLayout(layout);
    }
    combo->clear();
    gameDirs = getSubDirectories("games/");
    QStringList games;
    for(std::string s : gameDirs){
        rapidjson::Document doc;
        if(readJsonFile("games/"+s+"/gameInfo.json", doc)){
            games << doc["name"].GetString();
        } else {
            games << s.c_str();
        }
    }
    combo->addItems(games);
    dialog->exec();
}