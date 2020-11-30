/*  mainwindow.h
 *  Header file for the MainWindow class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *                  Main Window subcomponent
 *
 *  Author: Daniel Cullen
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QAbstractSocket>
#include "VCC_DataTypes.h"

class QGraphicsScene;
class QResizeEvent;
class PitchRollMeter;
class QGraphicsPixmapItem;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setPitch(qreal pitch);
    void setRoll(qreal roll);
    void setPixmap(QPixmap pmap);
    void setServerState(ServerStatus);
    void setSocketState(QAbstractSocket::SocketState state);
    void setConnectionStatus(bool status);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *cameraModel;
    PitchRollMeter *inclinometer;
    QGraphicsPixmapItem *currentFrame;

private slots:
    void resizeEvent(QResizeEvent *);
    void addToLog(QString str);

signals:
    void acceptNewConnections();
    void rejectNewConnections();
    void disconnect();
    void reset();
};

#endif // MAINWINDOW_H
