/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViewportWidget.h
 * Author: arnaubigas
 *
 * Created on March 23, 2016, 12:20 PM
 */

#ifndef VIEWPORTWIDGET_H
#define VIEWPORTWIDGET_H

#include <QOpenGLWidget>
#include <QTimer>
#include <SGIEngine/World.h>

class ViewportWidget : public QOpenGLWidget {
public:
    ViewportWidget(QWidget* parent = 0);
    void setupCamera();
    World* world = 0;
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    
    bool eventFilter(QObject* object, QEvent* event) override;
    
private:
    Camera* camera = 0;
    QTimer timer;
    int lastX;
    int lastY;
    bool active = false;
};

#endif /* VIEWPORTWIDGET_H */

