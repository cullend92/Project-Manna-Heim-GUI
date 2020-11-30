/*  communicationsmodule.h
 *  Header file for the CommunicationsModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Communications Module component
 *
 *  Author: Daniel Cullen
 */

#ifndef COMMUNICATIONSMODULE_H
#define COMMUNICATIONSMODULE_H

#include <QObject>
#include <QVector>
#include <QByteArray>
#include <QString>
#include <QAbstractSocket>
#include "VCC_DataTypes.h"
class QTcpServer;
class QTcpSocket;
class QHostAddress;

class CommunicationsModule : public QObject
{
    Q_OBJECT
public:
    explicit CommunicationsModule(QObject *parent = nullptr);
    ~CommunicationsModule();

private:
    int port;
    QHostAddress *address;
    bool isPaused;
    QTcpServer *server;
    QTcpSocket *socket;
    bool downloading;
    QByteArray currentData;

    bool findStartTag(MannaheimDataType &type, int &index, const QByteArray &data);
    bool findStopTag(int &index, const QByteArray &data);

private slots:
    void handleIncomingConnection();
    void handleIncomingData();
    void handleIncomingCommands(QVector<QByteArray> data);
    void socketDisconnected();
    void acceptConnections();
    void rejectConnections();
    void disconnect();
    void reset();

signals:
    void dataAvailable(MannaheimDataType type, QByteArray data);
    void logData(QString str);
    void socketStateChanged(QAbstractSocket::SocketState state);
    void serverStateChanged(ServerStatus);
    void connectionIsActive();
    void connectionIsInactive();
    void socketError(QAbstractSocket::SocketError);
};

#endif // COMMUNICATIONSMODULE_H
