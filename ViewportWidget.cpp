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
#include <QMouseEvent>
#include <QKeyEvent>
#include <sstream>
#include <SGIEngine/Logger.h>

#include "ViewportWidget.h"
#include "MainWindow.h"

#define clamp(x, min, max) (x < max ? x > min ? x : min : max)

ViewportWidget::ViewportWidget(QWidget* parent) : QOpenGLWidget(parent) {
    QSurfaceFormat glFormat;
    glFormat.setVersion(3, 2);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    glFormat.setSwapInterval(1);
    glFormat.setDepthBufferSize(24);
    glFormat.setSwapBehavior(QSurfaceFormat::DoubleBuffer);
    setFormat(glFormat);
    connect(&timer, &QTimer::timeout, this, &ViewportWidget::paintGL);
        timer.setInterval(16);
    timer.start();
}

void ViewportWidget::setupCamera(){
    camera = new Camera(world, new DeferredRendering(defaultFramebufferObject(), "final"));
    camera->resize(this->width(), this->height());
    world->addCamera(camera);
}

void ViewportWidget::initializeGL() {
    glewExperimental = true;
    GLenum err = glewInit();
    if (err != GLEW_NO_ERROR) {
        fprintf(stderr, "GLEW Init Error: %s\n", glewGetErrorString(err));
    }
    
    //Clear error buffer
    err = glGetError();

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glEnable(GL_SCISSOR_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    err = glGetError();
    if (err != GL_NO_ERROR) {
        Logger::error << "there was an error while initializing OpenGL:" << std::endl;
        Logger::error << err << std::endl;
    }
    
    glClearColor(0.f, 0.f, 0.f, 0.f);
}

void ViewportWidget::paintGL() {
    if(world != 0){
        if(active){
            camera->yaw += (QCursor::pos().x() - lastX);
            camera->pitch -= (QCursor::pos().y() - lastY);
            camera->yaw = fmod(camera->yaw, 360);
            camera->pitch = clamp(camera->pitch, -89.9f, 89.9f);
            QCursor::setPos(mapToGlobal(QPoint(width()/2, height()/2)));
            lastX = QCursor::pos().x();
            lastY = QCursor::pos().y();
        }
        makeCurrent();
        world->renderWorld();
        
        std::stringstream ss;
        ss << "X: " << camera->position.x << "; ";
        ss << "Y: " << camera->position.y << "; ";
        ss << "Z: " << camera->position.z << "; ";
        ss << "Pitch: " << camera->pitch << "; ";
        ss << "Yaw: " << camera->yaw << "; ";
        MainWindow::getInstance()->position->setText(ss.str().c_str());
    }
}

void ViewportWidget::resizeGL(int width, int height){
    if(camera != 0){
        camera->resize(width, height);
    }
}

bool ViewportWidget::eventFilter(QObject* object, QEvent* event){
    if(camera == 0) return false;
    if (event->type() == QEvent::MouseButtonPress){
        grabMouse();
        grabKeyboard();
        setCursor(Qt::BlankCursor);
        setMouseTracking(true);
        active = true;
    } else if(event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        float motionX = 0;
        float motionY = 0;
        float motionZ = 0;
        float movSpeed = 1.0f;

        switch(keyEvent->key()){
            case Qt::Key_W:
                motionX++;
                break;
            case Qt::Key_S:
                motionX--;
                break;
            case Qt::Key_A:
                motionZ--;
                break;
            case Qt::Key_D:
                motionZ++;
                break;
            case Qt::Key_Space:
            case Qt::Key_F:
                motionY++;
                break;
            case Qt::Key_C:
                motionY--;
                break;
            case Qt::Key_Escape:
                releaseKeyboard();
                releaseMouse();
                setCursor(Qt::ArrowCursor);
                setMouseTracking(false);
                active = false;
                break;
        }

        glm::vec3 mov = glm::normalize(glm::vec3(
            xTrig(motionX, motionZ, camera->yaw),
            motionY,
            zTrig(motionX, motionZ, camera->yaw))) * movSpeed;

        if (glm::isnan(mov.x) || glm::isnan(mov.y) || glm::isnan(mov.z)) mov = glm::vec3(0.f, 0.f, 0.f);

        camera->position += mov;
    }
    return false;
}