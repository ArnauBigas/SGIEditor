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

#include <QGLWidget>

class ViewportWidget : public QGLWidget {
public:
    ViewportWidget(QWidget* parent = 0);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
};

#endif /* VIEWPORTWIDGET_H */

