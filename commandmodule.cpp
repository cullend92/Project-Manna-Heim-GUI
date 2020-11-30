/*  commandmodule.cpp
 *  Implementation file for the CommandModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Command Module component
 *
 *  Author: Daniel Cullen
 */

#include "commandmodule.h"
#include "command.h"
#include <QTimer>
#include <QByteArray>
#include <Windows.h>

CommandModule::CommandModule(QObject *parent) : QObject(parent)
{
    loadCommands();
    connectionIsActive = false;
    keyboardScanTimer = new QTimer(this);
    cameraFrameTimer = new QTimer(this);
    connect(keyboardScanTimer, SIGNAL(timeout()), this, SLOT(scanKeyboard()));
    connect(cameraFrameTimer, SIGNAL(timeout()), this, SLOT(requestCameraFrame()));
#define MSECS_PER_KEYBOARD_SCAN 50 // 50ms per keyboard scan
    keyboardScanTimer->start(MSECS_PER_KEYBOARD_SCAN);
#define MSECS_PER_CAMERA_FRAME 33 // Target ~30 fps (33.3 ms per frame)
    cameraFrameTimer->start(MSECS_PER_CAMERA_FRAME);
}

CommandModule::~CommandModule()
{
    clearCommands();
    delete keyboardScanTimer;
    delete cameraFrameTimer;
}

void CommandModule::loadCommands()
{
    if (!commands.isEmpty())
        clearCommands();

    commands.append(new Command(driveForward, "Forward", Qt::Key_W, Qt::NoModifier, QByteArray("Forward"), true));
    commands.append(new Command(driveReverse, "Reverse", Qt::Key_S, Qt::NoModifier, QByteArray("Backward"), true));
    commands.append(new Command(turnLeft, "Turn Left", Qt::Key_A, Qt::NoModifier, QByteArray("Left"), true));
    commands.append(new Command(turnRight, "Turn Right", Qt::Key_D, Qt::NoModifier, QByteArray("Right"), true));
    commands.append(new Command(cameraPanUp, "Pan Up", VK_UP, Qt::NoModifier, QByteArray("CamTiltPos"), true));
    commands.append(new Command(cameraPanDown, "Pan Down", VK_DOWN, Qt::NoModifier, QByteArray("CamTiltNeg"), true));
    commands.append(new Command(cameraPanLeft, "Pan Left", VK_LEFT, Qt::NoModifier, QByteArray("CamPanNeg"), true));
    commands.append(new Command(cameraPanRight, "Pan Right", VK_RIGHT, Qt::NoModifier, QByteArray("CamPanPos"), true));
    commands.append(new Command(deployShelter, "Deploy Shelter", Qt::Key_Z, Qt::NoModifier, QByteArray("Deploy"), true));
    commands.append(new Command(retractShelter, "Retract Shelter", Qt::Key_C, Qt::NoModifier, QByteArray("Retract"), true));
    commands.append(new Command(shelterMotorOneExtend, "Shelter Motor 1 - Extend", Qt::Key_I, Qt::NoModifier, QByteArray("DeployOne"), true));
    commands.append(new Command(shelterMotorOneRetract, "Shelter Motor 1 - Retract", Qt::Key_K, Qt::NoModifier, QByteArray("RetractOne"), true));
    commands.append(new Command(shelterMotorTwoExtend, "Shelter Motor 2 - Extend", Qt::Key_O, Qt::NoModifier, QByteArray("DeployTwo"), true));
    commands.append(new Command(shelterMotorTwoRetract, "Shelter Motor 2 - Retract", Qt::Key_L, Qt::NoModifier, QByteArray("RetractTwo"), true));
}

void CommandModule::clearCommands()
{
    if (commands.isEmpty())
        return;

    for (int i = 0; i < commands.size(); i++) {
        delete commands[i];
    }
    commands.clear();
}

void CommandModule::scanKeyboard()
{
    if (!connectionIsActive)
        return;

    QVector<QByteArray> temp;
    for(int i = 0; i < commands.size(); i++) {
        if (commands[i]->isPressed()) {
            temp.append(commands[i]->getPacketizedData());
        }
    }
    if (!temp.isEmpty())
        emit commandsReadyToSend(temp);
}

void CommandModule::requestCameraFrame()
{
    if (!connectionIsActive)
        return;

    QVector<QByteArray> temp;
    temp.append(QByteArray("Cam"));
    emit commandsReadyToSend(temp);
}

void CommandModule::activateConnection()
{
    connectionIsActive = true;
}

void CommandModule::deactivateConnection()
{
    connectionIsActive = false;
}
