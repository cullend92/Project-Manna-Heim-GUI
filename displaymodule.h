/*  displaymodule.h
 *  Header file for the DisplayModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *
 *  Author: Daniel Cullen
 */

#ifndef DISPLAYMODULE_H
#define DISPLAYMODULE_H

#include <QObject>
#include <QPixmap>
#include <QAbstractSocket>
#include "mainwindow.h"
#include "VCC_DataTypes.h"

class DisplayModule : public QObject
{
    Q_OBJECT
public:
    explicit DisplayModule(QObject *parent = nullptr);

private:
    MainWindow mw;
    QPixmap currentFrame;

private slots:
    void handleIncomingData(MannaheimDataType type, QByteArray data);
    void handleNewSocketStatus(QAbstractSocket::SocketState state);
    void handleNewServerStatus(ServerStatus status);
    void activateConnection();
    void deactivateConnection();

signals:
    void acceptNewConnections();
    void rejectNewConnections();
    void disconnect();
    void reset();
    void addToLog(QString);
};

#endif // DISPLAYMODULE_H
