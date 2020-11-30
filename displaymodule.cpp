/*  displaymodule.cpp
 *  Implementation file for the DisplayModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *
 *  Author: Daniel Cullen
 */

#include "displaymodule.h"

DisplayModule::DisplayModule(QObject *parent) : QObject(parent)
{
    connect(&mw, SIGNAL(acceptNewConnections()), this, SIGNAL(acceptNewConnections()));
    connect(&mw, SIGNAL(rejectNewConnections()), this, SIGNAL(rejectNewConnections()));
    connect(&mw, SIGNAL(disconnect()), this, SIGNAL(disconnect()));
    connect(&mw, SIGNAL(reset()), this, SIGNAL(reset()));
    connect(this, SIGNAL(addToLog(QString)), &mw, SLOT(addToLog(QString)));
    mw.showMaximized();
}

void DisplayModule::handleIncomingData(MannaheimDataType type, QByteArray data)
{
    switch (type) {
    case CAMERA:
        if (currentFrame.loadFromData(data))
            mw.setPixmap(currentFrame);
        else
            emit addToLog("Warning: Bad image data.");
        break;

    case PITCH:
        mw.setPitch(data.toInt());
        break;

    case ROLL:
        mw.setRoll(data.toInt());
        break;

    case NONE:
        emit addToLog("Unrecognized Data received: " + QString(data));
    }
}

void DisplayModule::handleNewSocketStatus(QAbstractSocket::SocketState state)
{
    mw.setSocketState(state);
}

void DisplayModule::handleNewServerStatus(ServerStatus status)
{
    mw.setServerState(status);
}

void DisplayModule::activateConnection()
{
    mw.setConnectionStatus(true);
}

void DisplayModule::deactivateConnection()
{
    mw.setConnectionStatus(false);
}
