/*  communicationsmodule.cpp
 *  Implementation file for the CommunicationsModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Communications Module component
 *
 *  Author: Daniel Cullen
 */

#include "communicationsmodule.h"
#include <QByteArray>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QPixmap>

#define COMMS_DEBUG

CommunicationsModule::CommunicationsModule(QObject *parent) : QObject(parent)
{
    port = 80;
    address = new QHostAddress("172.30.50.189");
    server = new QTcpServer(this);
    socket = nullptr;
    isPaused = false;
    downloading = false;
    connect(server, SIGNAL(newConnection()), this, SLOT(handleIncomingConnection()));
}

CommunicationsModule::~CommunicationsModule()
{
    delete address;
    if (socket != nullptr)
        socket->deleteLater();
    if (server != nullptr)
        server->deleteLater();
}

bool CommunicationsModule::findStartTag(MannaheimDataType &type, int &index, const QByteArray &data)
{
    static const QByteArray startTag("START_");
    static const QByteArray cameraTag("CAMERA_FRAME");
    static const QByteArray pitchTag("PITCH");
    static const QByteArray rollTag("ROLL");

    if (!data.contains(startTag))
        return false;

    if (data.contains(cameraTag)) {
        type = CAMERA;
        index = data.indexOf(cameraTag) + cameraTag.size();
        return true;
    }

    if (data.contains(pitchTag)) {
        type = PITCH;
        index = data.indexOf(pitchTag) + pitchTag.size();
        return true;
    }

    if (data.contains(rollTag)) {
        type = ROLL;
        index = data.indexOf(rollTag) + rollTag.size();
        return true;
    }

    return false;
}

bool CommunicationsModule::findStopTag(int &index, const QByteArray &data)
{
    static const QByteArray stopTag("STOP");

    if (!data.contains(stopTag))
        return false;

    index = data.indexOf(stopTag) - 1;
    return true;
}

void CommunicationsModule::handleIncomingConnection()
{
    if (socket != nullptr) {
        socket->abort();
        delete socket;
    }

    socket = server->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(handleIncomingData()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(socketDisconnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SIGNAL(socketError(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SIGNAL(socketStateChanged(QAbstractSocket::SocketState)));
    emit socketStateChanged(socket->state());
    emit connectionIsActive();
    emit logData("Connection opened.");
}

void CommunicationsModule::handleIncomingData()
{
    static MannaheimDataType dataType = NONE;
    int startIndex = 0;
    int stopIndex = 0;
    QByteArray temp = socket->readAll();

    if (!downloading) {
        if (findStartTag(dataType, startIndex, temp)) {
            if (findStopTag(stopIndex, temp)) {
                emit dataAvailable(dataType, temp.mid(startIndex, stopIndex-startIndex));
            }
            else {
                currentData += temp.mid(startIndex);
                downloading = true;
            }
        }
    }
    else {
        if (findStopTag(stopIndex, temp)) {
            currentData += temp.mid(0, stopIndex);
            emit dataAvailable(dataType, currentData);
            downloading = false;
            currentData.clear();
        }
        else
            currentData += temp;
    }
    //emit logData(temp);
}

void CommunicationsModule::handleIncomingCommands(QVector<QByteArray> data)
{
    if(socket != nullptr) {
        if (socket->isValid()) {
            for (int i = 0; i < data.size(); i++) {
                socket->write(data[i]);
                emit logData("Sending: " + QString(data[i]));
            }
        }
        else
            emit logData("ERROR: No Connection.");
    }
    else
        emit logData("ERROR: No Socket.");
}

void CommunicationsModule::socketDisconnected()
{
    emit logData("Disconnected");
    emit connectionIsInactive();
}

void CommunicationsModule::acceptConnections()
{
    if (isPaused) {
        server->resumeAccepting();
        isPaused = false;
        return;
    }
    server->listen(*address, port);
    emit serverStateChanged(LISTENING);
    emit logData(QString("Server listening on port " + QString::number(port)));
}

void CommunicationsModule::rejectConnections()
{
    if (server->isListening())
        server->pauseAccepting();
    isPaused = true;
    emit serverStateChanged(PAUSED);
    emit logData("Server paused.");
}

void CommunicationsModule::disconnect()
{
    if (socket != nullptr) {
        socket->close();
        emit connectionIsInactive();
        emit socketStateChanged(QAbstractSocket::UnconnectedState);
        emit logData("Socket closed.");
    }
}

void CommunicationsModule::reset()
{
    if (server != nullptr)
        delete server;
    server = new QTcpServer(this);
    emit serverStateChanged(IDLE);
    emit logData("Server reset.");
}
