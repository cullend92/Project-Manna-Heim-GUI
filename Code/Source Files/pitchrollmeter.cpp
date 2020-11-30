/*  pitchrollmeter.cpp
 *  Implementation file for the PitchRollMeter class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *                  Main Window sub-component
 *                      Pitch & Roll Meter element
 *
 *  Author: Daniel Cullen
 */

#include "pitchrollmeter.h"
#include <QPixmap>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QFont>
#include <QBrush>
#include <QtMath>
#include <QPointF>

// Background constants:
#define BACKGROUND_LENGTH 1000 // Background length
#define BACKGROUND_HEIGHT 500  // Background height
#define INLAY_OFFSET 25        // Vertical & horizontal offset of inlay from background

// pitch & roll circle constants:
#define CIRCLE_BRECT_WIDTH 210 // Width of pitch & roll circles bounding rect
#define CIRCLE_PRIMARY_OFFSET 40 // Vertical & horizontal offset of pitch & roll circles

// Tick mark constants:
#define TICK_MARK_LENGTH 15
#define TICK_MARK_WIDTH 5
#define TICK_MARK_OFFSET 10 // Distance between pitch & roll circle and indicator marks

#define TEXT_HORZ_OFFSET 40 // Text horizontal offset from circle center
#define TEXT_VERT_OFFSET 20 // Text vertical offset from circle center
#define TEXT_FONT_SIZE 30

PitchRollMeter::PitchRollMeter(QGraphicsItem *parent) : QGraphicsItemGroup(parent)
{
    initializeBackground();
    initializeCircles();
    initializeIndicatorMarks();
    initializeText();
}

void PitchRollMeter::setPitch(qreal value)
{
    pitchCircleItem->setRotation(3*value);
}

void PitchRollMeter::setRoll(qreal value)
{
    rollCircleItem->setRotation(3*value);
}

QRectF PitchRollMeter::boundingRect() const
{
    return QRectF(0, 0, BACKGROUND_LENGTH, BACKGROUND_HEIGHT);
}

void PitchRollMeter::initializeBackground()
{
    QGraphicsRectItem *background = new QGraphicsRectItem(this);
    QGraphicsRectItem *inlay = new QGraphicsRectItem(this);

    background->setRect(0, 0, BACKGROUND_LENGTH, BACKGROUND_HEIGHT);
    background->setBrush(QBrush(Qt::gray));
    this->addToGroup(background);

    inlay->setRect(INLAY_OFFSET, INLAY_OFFSET, BACKGROUND_LENGTH - 2*INLAY_OFFSET, BACKGROUND_HEIGHT - 2*INLAY_OFFSET);
    inlay->setBrush(QBrush(Qt::lightGray));
    this->addToGroup(inlay);
}

void PitchRollMeter::initializeCircles()
{
    rollOffset.setX(CIRCLE_PRIMARY_OFFSET);
    rollOffset.setY(CIRCLE_PRIMARY_OFFSET);
    rollCenter = rollOffset + QPointF(CIRCLE_BRECT_WIDTH, CIRCLE_BRECT_WIDTH);
    rollCircleItem = new QGraphicsPixmapItem(this);
    rollCircleItem->setPixmap(QPixmap(":/VCC_Images/Roll_Circle"));
    rollCircleItem->setOffset(rollOffset);
    rollCircleItem->setTransformOriginPoint(rollCenter);
    this->addToGroup(rollCircleItem);

    pitchOffset.setX(BACKGROUND_LENGTH/2 + CIRCLE_PRIMARY_OFFSET);
    pitchOffset.setY(CIRCLE_PRIMARY_OFFSET);
    pitchCenter = pitchOffset + QPointF(CIRCLE_BRECT_WIDTH, CIRCLE_BRECT_WIDTH);
    pitchCircleItem = new QGraphicsPixmapItem(this);
    pitchCircleItem->setPixmap(QPixmap(":/VCC_Images/Pitch_Circle"));
    pitchCircleItem->setOffset(pitchOffset);
    pitchCircleItem->setTransformOriginPoint(pitchCenter);
    this->addToGroup(pitchCircleItem);
}

void PitchRollMeter::initializeIndicatorMarks()
{
    QGraphicsRectItem *tempPitchMark;
    QGraphicsRectItem *tempRollMark;
    QPointF rollTickMarkOrigin;
    QPointF pitchTickMarkOrigin;
    qreal theta_d = 0; // Rotation angle of tick mark, degrees
    qreal theta_r = 0; // Rotation angle of tick mark, radians
    qreal rollMarkOffsetX = 0;
    qreal rollMarkOffsetY = 0;
    qreal pitchMarkOffsetX = 0;
    qreal pitchMarkOffsetY = 0;

    for (int i = -15; i <= 15; i++) {
        theta_d = 3*i;
        theta_r = qDegreesToRadians(theta_d);

        // Roll indicators:
        tempRollMark = new QGraphicsRectItem(this);
        rollMarkOffsetX = (CIRCLE_BRECT_WIDTH+TICK_MARK_OFFSET)*qCos(theta_r);
        rollMarkOffsetY = (CIRCLE_BRECT_WIDTH+TICK_MARK_OFFSET)*qSin(theta_r);
        rollTickMarkOrigin = rollCenter + QPointF(rollMarkOffsetX, -rollMarkOffsetY);
        tempRollMark->setRect(QRectF(rollTickMarkOrigin, QSizeF(TICK_MARK_LENGTH, TICK_MARK_WIDTH)));
        tempRollMark->setTransformOriginPoint(rollTickMarkOrigin);
        tempRollMark->setRotation(-theta_d);
        if (i <= -10 || i >= 10)
            tempRollMark->setBrush(Qt::red);
        else if (i <= -5 || i >= 5)
            tempRollMark->setBrush(Qt::yellow);
        else if (i != 0)
            tempRollMark->setBrush(Qt::green);
        else
            tempRollMark->setBrush(Qt::white);
        this->addToGroup(tempRollMark);

        // Pitch indicators:
        tempPitchMark = new QGraphicsRectItem(this);
        pitchMarkOffsetX = (CIRCLE_BRECT_WIDTH+TICK_MARK_OFFSET+TICK_MARK_LENGTH)*qCos(theta_r);
        pitchMarkOffsetY = (CIRCLE_BRECT_WIDTH+TICK_MARK_OFFSET+TICK_MARK_LENGTH)*qSin(theta_r);
        pitchTickMarkOrigin = pitchCenter + QPointF(-pitchMarkOffsetX, -pitchMarkOffsetY);
        tempPitchMark->setRect(QRectF(pitchTickMarkOrigin, QSizeF(TICK_MARK_LENGTH, TICK_MARK_WIDTH)));
        tempPitchMark->setTransformOriginPoint(pitchTickMarkOrigin);
        tempPitchMark->setRotation(theta_d);
        if (i <= -10 || i >= 10)
            tempPitchMark->setBrush(Qt::red);
        else if (i <= -5 || i >= 5)
            tempPitchMark->setBrush(Qt::yellow);
        else if (i != 0)
            tempPitchMark->setBrush(Qt::green);
        else
            tempPitchMark->setBrush(Qt::white);
        this->addToGroup(tempPitchMark);
    }
}

void PitchRollMeter::initializeText()
{
    QGraphicsSimpleTextItem *rollText = new QGraphicsSimpleTextItem(this);
    QGraphicsSimpleTextItem *pitchText = new QGraphicsSimpleTextItem(this);

    pitchText->setText("Pitch");
    pitchText->setFont(QFont("Times", TEXT_FONT_SIZE));
    this->addToGroup(pitchText);
    pitchText->setX(pitchCenter.x() - TEXT_HORZ_OFFSET);
    pitchText->setY(pitchCenter.y() + TEXT_VERT_OFFSET);

    rollText->setText("Roll");
    rollText->setFont(QFont("Times", TEXT_FONT_SIZE));
    this->addToGroup(rollText);
    rollText->setX(rollCenter.x() - TEXT_HORZ_OFFSET);
    rollText->setY(rollCenter.y() + TEXT_VERT_OFFSET);
}
