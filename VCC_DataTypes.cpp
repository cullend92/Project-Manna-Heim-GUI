/*  VCC_dataType.cpp
 *  Implementation file for VCC data types methods
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              VCC data types component
 *
 *  Author: Daniel Cullen
 */

#include "VCC_DataTypes.h"

QString socketStateString(QAbstractSocket::SocketState state)
{
    switch (state) {
        case QAbstractSocket::ConnectedState:
            return "Connected";

        case QAbstractSocket::UnconnectedState:
            return "Unconnected";

        case QAbstractSocket::HostLookupState:
            return "Host Lookup";

        case QAbstractSocket::ConnectingState:
            return "Connecting";

        case QAbstractSocket::BoundState:
            return "Bound";

        case QAbstractSocket::ClosingState:
            return "Closing";

        case QAbstractSocket::ListeningState:
            return "Listening";
    }
}

QString serverStateString(ServerStatus status)
{
    switch (status) {
        case IDLE:
            return "Idle";

        case LISTENING:
            return "Listening";

        case PAUSED:
            return "Paused";
    }
}
