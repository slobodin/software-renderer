/*
 * mainwindow.h
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QMutex>
#include "clientcontroller.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    // renderer client-side
    ClientController *m_controller;
    QTimer m_rendererTimer;
    QImage *m_image;
    QMutex m_mutex;

    void paintEvent(QPaintEvent *pe);

public slots:
    void rendererUpdate();
};

#endif // MAINWINDOW_H
