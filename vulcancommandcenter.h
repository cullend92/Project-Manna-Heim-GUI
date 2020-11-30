/*  vulcancommandcenter.h
 *  Header file for the VulcanCommandCenter class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *
 *  Author: Daniel Cullen
 */

#ifndef VULCANCOMMANDCENTER_H
#define VULCANCOMMANDCENTER_H
#include <QObject>

class CommandModule;
class CommunicationsModule;
class DisplayModule;

class VulcanCommandCenter : public QObject
{
    Q_OBJECT
public:
    explicit VulcanCommandCenter(QObject *parent = nullptr);
    ~VulcanCommandCenter();

private:
    CommandModule *commandModule;
    CommunicationsModule *communicationsModule;
    DisplayModule *displayModule;

    void createConnections();
};

#endif // VULCANCOMMANDCENTER_H
