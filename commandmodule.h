/*  commandmodule.h
 *  Header file for the CommandModule class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Command Module component
 *
 *  Author: Daniel Cullen
 */

#ifndef COMMANDMODULE_H
#define COMMANDMODULE_H

#include <QObject>
#include <QVector>
#include <QByteArray>

class QTimer;
class Command;

class CommandModule : public QObject
{
    Q_OBJECT
public:
    explicit CommandModule(QObject *parent = nullptr);
    ~CommandModule();

private:
    QVector<Command *> commands;
    QTimer* keyboardScanTimer;
    QTimer* cameraFrameTimer;
    bool connectionIsActive;

    void loadCommands();
    void clearCommands();

private slots:
    void scanKeyboard();
    void requestCameraFrame();
    void activateConnection();
    void deactivateConnection();

signals:
    void commandsReadyToSend(QVector<QByteArray>);
};

#endif // COMMANDMODULE_H
