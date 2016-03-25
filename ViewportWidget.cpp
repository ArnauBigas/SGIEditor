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
#include <SGIEngine/ResourceEngine.h>

#include "ViewportWidget.h"

ViewportWidget::ViewportWidget(QWidget* parent)
    : QGLWidget(parent) {
    QGLFormat glFormat;
    glFormat.setVersion( 3, 3 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( true );
    setFormat(glFormat);
}

void ViewportWidget::initializeGL() {
    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_NO_ERROR) {
        fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(err));
    }
    glClearColor(0.f, 0.f, 0.f, 0.f);
}

void ViewportWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void ViewportWidget::resizeGL(int width, int height){
    
}