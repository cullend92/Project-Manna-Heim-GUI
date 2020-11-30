/*  command.h
 *  Header file for the Command class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Command Module component
 *                  Command sub-component
 *
 *  Author: Daniel Cullen
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <QString>
#include <Qt>
#include <QByteArray>
#include "VCC_DataTypes.h"

class Command
{
public:
    Command(MannaheimCommandType t, QString n, int k, Qt::KeyboardModifier mod,  QByteArray pData, bool isBound = false)
        : type(t), name(n), key(k), modifier(mod), packetizedData(pData), isBoundToKey (isBound) {}

    bool isPressed();
    QByteArray getPacketizedData() const;
    QString debugString();

private:
    MannaheimCommandType type;
    QString name;
    int key;
    Qt::KeyboardModifier modifier;
    QByteArray packetizedData;
    bool isBoundToKey;
};

#endif // COMMAND_H
