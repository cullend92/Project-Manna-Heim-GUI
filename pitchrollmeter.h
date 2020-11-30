/*  pitchrollmeter.h
 *  Header file for the PitchRollMeter class
 *
 *  Team Vulcan
 *  Project Manna-Heim
 *      Dovahkiin System
 *          Vulcan Command Center subsystem
 *              Display Module component
 *                  Main Window sub-component
 *                      Pitch & Roll meter element
 *
 *  Author: Daniel Cullen
 */

#ifndef PITCHROLLMETER_H
#define PITCHROLLMETER_H
#include <QGraphicsItemGroup>
#include <QPixmap>
#include <QPointF>

class PitchRollMeter : public QGraphicsItemGroup
{
public:
    PitchRollMeter(QGraphicsItem *parent = nullptr);

    void setPitch(qreal value);
    void setRoll(qreal value);

    QRectF boundingRect() const override;

private:
    QGraphicsPixmapItem *rollCircleItem;
    QPointF rollOffset;
    QPointF rollCenter;

    QGraphicsPixmapItem *pitchCircleItem;
    QPointF pitchOffset;
    QPointF pitchCenter;

    void initializeBackground();
    void initializeCircles();
    void initializeIndicatorMarks();
    void initializeText();
};

#endif // PITCHROLLMETER_H
