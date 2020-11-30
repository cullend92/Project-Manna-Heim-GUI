/*  command.cpp
 *  Implementation file for the Command class
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
#include "command.h"
#include <Windows.h>
#pragma comment(lib, "User32.lib")

bool Command::isPressed()
{
    if (!isBoundToKey)
        return false;

    #define KEY_IS_PRESSED_MASK 0x8000
    bool keyIsPressed = false;
    bool modIsPressed = false;

    keyIsPressed = GetAsyncKeyState(key) & KEY_IS_PRESSED_MASK;

    if ( (GetAsyncKeyState(VK_SHIFT) & KEY_IS_PRESSED_MASK) && (modifier == Qt::ShiftModifier) )
        modIsPressed = true;

    if ( (GetAsyncKeyState(VK_CONTROL) & KEY_IS_PRESSED_MASK) && (modifier == Qt::ControlModifier) )
        modIsPressed = true;

    if ( (GetAsyncKeyState(VK_MENU) & KEY_IS_PRESSED_MASK) && (modifier == Qt::AltModifier) )
        modIsPressed = true;

    // If no modifier is defined, consider key pressed regardless of which modifiers are/are not pressed.
    if (modifier == Qt::NoModifier)
        modIsPressed = true;

    return (keyIsPressed && modIsPressed);
}

QByteArray Command::getPacketizedData() const
{
    return packetizedData;
}

QString Command::debugString()
{
    return name;
}
