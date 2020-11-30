/*  VCC_dataType.h
 *  Header file for VCC data types methods
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              VCC data types component
 *
 *  Author: Daniel Cullen
 */

#ifndef VCC_DATATYPES_H
#define VCC_DATATYPES_H

#include <QAbstractSocket>
#include <QString>

enum ServerStatus {
    IDLE,
    LISTENING,
    PAUSED
};

enum MannaheimDataType {
    CAMERA,
    PITCH,
    ROLL,
    NONE
};

enum MannaheimCommandType {
    driveForward,
    driveReverse,
    turnLeft,
    turnRight,
    cameraPanLeft,
    cameraPanRight,
    cameraPanUp,
    cameraPanDown,
    deployShelter,
    retractShelter,
    shelterMotorOneExtend,
    shelterMotorTwoExtend,
    shelterMotorOneRetract,
    shelterMotorTwoRetract,
    NO_COMMAND
};

QString socketStateString(QAbstractSocket::SocketState state);
QString serverStateString(ServerStatus status);

#endif // VCC_DATATYPES_H
