/*  main.cpp
 *  Main file for the Vulcan Command Center.
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *
 *  Author: Daniel Cullen
 */

#include "vulcancommandcenter.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen ss(QPixmap(":/VCC_Images/VULCAN_IMAGE_PNG"));
    ss.setWindowFlag(Qt::WindowStaysOnTopHint);
    ss.show();
    QTimer::singleShot(1000, &ss, SLOT(close()));
    VulcanCommandCenter VCC;
    return a.exec();
}
