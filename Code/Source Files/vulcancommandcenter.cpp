/*  vulcancommandcenter.cpp
 *  Implementation file for the VulcanCommandCenter class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *
 *  Author: Daniel Cullen
 */

#include "vulcancommandcenter.h"
#include "commandmodule.h"
#include "communicationsmodule.h"
#include "displaymodule.h"
#include "VCC_DataTypes.h"
#include <QPixmap>
#include <QAbstractSocket>
#include <QString>
#include <QVector>
#include <QByteArray>

VulcanCommandCenter::VulcanCommandCenter(QObject *parent) : QObject(parent)
{
    commandModule = new CommandModule(this);
    communicationsModule = new CommunicationsModule(this);
    displayModule = new DisplayModule(this);
    createConnections();
}

VulcanCommandCenter::~VulcanCommandCenter()
{
    commandModule->deleteLater();
    communicationsModule->deleteLater();
    displayModule->deleteLater();
}

void VulcanCommandCenter::createConnections()
{
    connect(communicationsModule, SIGNAL(dataAvailable(MannaheimDataType, QByteArray)),
            displayModule, SLOT(handleIncomingData(MannaheimDataType, QByteArray)));

    connect(communicationsModule, SIGNAL(socketStateChanged(QAbstractSocket::SocketState)),
            displayModule, SLOT(handleNewSocketStatus(QAbstractSocket::SocketState)));

    connect(communicationsModule, SIGNAL(logData(QString)),
            displayModule, SIGNAL(addToLog(QString)));

    connect(communicationsModule, SIGNAL(serverStateChanged(ServerStatus)),
            displayModule, SLOT(handleNewServerStatus(ServerStatus)));

    connect(communicationsModule, SIGNAL(dataAvailable(MannaheimDataType, QByteArray)),
            displayModule, SLOT(handleIncomingData(MannaheimDataType, QByteArray)));

    connect(communicationsModule, SIGNAL(connectionIsActive()),
            commandModule, SLOT(activateConnection()));

    connect(communicationsModule, SIGNAL(connectionIsInactive()),
            commandModule, SLOT(deactivateConnection()));

    connect(communicationsModule, SIGNAL(connectionIsActive()),
            displayModule, SLOT(activateConnection()));

    connect(communicationsModule, SIGNAL(connectionIsInactive()),
            displayModule, SLOT(deactivateConnection()));

    connect(displayModule, SIGNAL(acceptNewConnections()),
            communicationsModule, SLOT(acceptConnections()));

    connect(displayModule, SIGNAL(rejectNewConnections()),
            communicationsModule, SLOT(rejectConnections()));

    connect(displayModule, SIGNAL(disconnect()),
            communicationsModule, SLOT(disconnect()));

    connect(displayModule, SIGNAL(reset()),
            communicationsModule, SLOT(reset()));

    connect(commandModule, SIGNAL(commandsReadyToSend(QVector<QByteArray>)),
            communicationsModule, SLOT(handleIncomingCommands(QVector<QByteArray>)));
}
