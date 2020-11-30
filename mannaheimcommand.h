#ifndef MANNAHEIMCOMMAND_H
#define MANNAHEIMCOMMAND_H

#include <Qt>
#include <QByteArray>

class AbstractMannaheimCommand
{
public:
    AbstractMannaheimCommand(Qt::Key k, Qt::KeyboardModifier mod);

private:
    Qt::Key key;
    Qt::KeyboardModifier modifier;

    virtual QByteArray packetize() = 0;
    bool isPressed();
};


class MannaheimCommand_DriveForward : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_DriveForward(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    QByteArray packetize();
};

class MannaheimCommand_DriveReverse : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_DriveReverse(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_DriveLeft : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_DriveLeft(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_DriveRight : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_DriveRight(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_CameraPanLeft : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_CameraPanLeft(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_CameraPanRight : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_CameraPanRight(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_CameraPanUp : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_CameraPanUp(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_CameraPanDown : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_CameraPanDown(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterAutoDeploy : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterAutoDeploy(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterAutoRetract : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterAutoRetract(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterMotor1Extend : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterMotor1Extend(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterMotor2Extend : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterMotor2Extend(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterMotor1Retract : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterMotor1Retract(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_ShelterMotor2Retract : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_ShelterMotor2Retract(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_SetOperatingMode_Driving : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_SetOperatingMode_Driving(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_SetOperatingMode_ShelterControl : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_SetOperatingMode_ShelterControl(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};

class MannaheimCommand_SetOperatingMode_ImpactEvent : public AbstractMannaheimCommand
{
public:
    MannaheimCommand_SetOperatingMode_ImpactEvent(Qt::Key k, Qt::KeyboardModifier mod) : AbstractMannaheimCommand(k, mod) {}
private:
    virtual QByteArray packetize();
};


#endif // MANNAHEIMCOMMAND_H
