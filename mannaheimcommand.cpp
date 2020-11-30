#include "mannaheimcommand.h"
#include <QByteArray>
#include <Windows.h>
#pragma comment(lib, "User32.lib")

AbstractMannaheimCommand::AbstractMannaheimCommand(Qt::Key k, Qt::KeyboardModifier mod)
{
    key = k;
    modifier = mod;
}

#define KEY_IS_PRESSED_MASK 0x8000
bool AbstractMannaheimCommand::isPressed()
{
    return (GetAsyncKeyState(key) & KEY_IS_PRESSED_MASK);
}

QByteArray MannaheimCommand_DriveForward::packetize() {
    return QByteArray();
}

QByteArray MannaheimCommand_DriveReverse::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_DriveLeft::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_DriveRight::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_CameraPanUp::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_CameraPanDown::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_CameraPanLeft::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_CameraPanRight::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterAutoDeploy::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterAutoRetract::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterMotor1Extend::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterMotor1Retract::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterMotor2Extend::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_ShelterMotor2Retract::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_SetOperatingMode_Driving::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_SetOperatingMode_ShelterControl::packetize() {
    return QByteArray();
}
QByteArray MannaheimCommand_SetOperatingMode_ImpactEvent::packetize() {
    return QByteArray();
}
