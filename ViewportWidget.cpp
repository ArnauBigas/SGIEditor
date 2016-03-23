/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ViewportWidget.cpp
 * Author: arnaubigas
 * 
 * Created on March 23, 2016, 12:20 PM
 */

#include <GL/glew.h>

#include "ViewportWidget.h"

ViewportWidget::ViewportWidget(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent) {
    
}

void ViewportWidget::initializeGL() {
    glClearColor(0.f, 0.f, 0.f, 0.f);
}

void ViewportWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewportWidget::resizeGL(int width, int height){
    
}

QSize ViewportWidget::minimumSizeHint() const
{
    return QSize(50, 50);
}