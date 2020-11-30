/*  mainwindow.cpp
 *  Implementation file for the MainWindow class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *                  Main Window sub-component
 *
 *  Author: Daniel Cullen
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pitchrollmeter.h"
#include <QGraphicsScene>
#include <QResizeEvent>
#include <QIcon>
#include <QTransform>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QAbstractSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Perform initial ui setup:
    ui->setupUi(this);
    ui->cameraView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cameraView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->cameraView->setRenderHint(QPainter::Antialiasing);

    // Create objects:
    cameraModel = new QGraphicsScene(this);
    inclinometer = new PitchRollMeter();
    currentFrame = new QGraphicsPixmapItem();

    // Set view/scene connections:
    ui->cameraView->setScene(cameraModel);
    cameraModel->addItem(inclinometer);
    cameraModel->addItem(currentFrame);
    inclinometer->setScale(0.5);
    inclinometer->setTransform(QTransform().translate(-cameraModel->width()/2, cameraModel->height()/2));
    currentFrame->setTransform(QTransform().translate(-cameraModel->width()/2, -cameraModel->height()/2));

    // Configure main window:
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("Vulcan Command Center");
    setWindowIcon(QIcon(":/VCC_Images/VULCAN_LOGO_PNG.png"));

    // Set button connecions:
    connect(ui->acceptConnectionsButton, SIGNAL(clicked()), this, SIGNAL(acceptNewConnections()));
    connect(ui->rejectConnectionsButton, SIGNAL(clicked()), this, SIGNAL(rejectNewConnections()));
    connect(ui->disconnectButton, SIGNAL(clicked()), this, SIGNAL(disconnect()));
    connect(ui->resetButton, SIGNAL(clicked()), this, SIGNAL(reset()));
}

MainWindow::~MainWindow()
{
    delete cameraModel;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    qreal scale = inclinometer->scale();
    qreal viewWidth = ui->cameraView->width();
    qreal veiwHeight = ui->cameraView->height();
    qreal meterWidth = inclinometer->boundingRect().width();
    qreal meterHeight = inclinometer->boundingRect().height();

    cameraModel->setSceneRect(-viewWidth/2, -veiwHeight/2, viewWidth, veiwHeight);
    inclinometer->setTransform(QTransform().translate(-meterWidth/2*scale, veiwHeight/2 - meterHeight*scale));
    currentFrame->setTransform(QTransform().translate(-viewWidth/2, -veiwHeight/2));
}

void MainWindow::setPitch(qreal pitch)
{
    inclinometer->setPitch(pitch);
}

void MainWindow::setRoll(qreal roll)
{
    inclinometer->setRoll(roll);
}

void MainWindow::setPixmap(QPixmap pmap)
{
    currentFrame->setPixmap(pmap);
}

void MainWindow::setServerState(ServerStatus status)
{
    ui->serverStatus_display->setText(serverStateString(status));
}

void MainWindow::setSocketState(QAbstractSocket::SocketState state)
{
    ui->socketStatus_display->setText(socketStateString(state));
}

void MainWindow::setConnectionStatus(bool status)
{
    if (status)
        ui->connectionStatus_display->setText("ACTIVE");
    else
        ui->connectionStatus_display->setText("INACTIVE");
}

void MainWindow::addToLog(QString str)
{
    ui->networkLog->append(str);
}
