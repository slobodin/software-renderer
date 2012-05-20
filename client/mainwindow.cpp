/*
 * mainwindow.cpp
 *
 *      Author: flamingo
 *      E-mail: epiforce57@gmail.com
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_image(0)
{
    ui->setupUi(this);

    m_controller = new ClientController;
    m_image = new QImage(m_controller->deviceWidth(), m_controller->deviceHeight(), QImage::Format_RGB888);
    sptr(rend::RenderDevice) device = make_shared<rend::RenderDeviceQt>(m_image);

    m_controller->setDevice(device);

    connect(&m_rendererTimer, SIGNAL(timeout()), this, SLOT(rendererUpdate()));
    m_rendererTimer.start(0);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_controller;
}

void MainWindow::paintEvent(QPaintEvent *pe)
{
    QPainter widgetPaiter(this);

    if (m_image)
    {
        m_mutex.lock();
        widgetPaiter.drawImage(0, 0, *m_image);
        m_mutex.unlock();
    }
}

void MainWindow::rendererUpdate()
{
    m_mutex.lock();
    m_controller->update();
    m_mutex.unlock();
}
