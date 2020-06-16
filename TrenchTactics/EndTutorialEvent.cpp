#include "EndTutorialEvent.h"


/**
 * specialised constructor to create the EndTutorialEvent object.
 *
 * \param sX the start x-coordinate of the tutorial window
 * \param eX the end x-coordinate of the tutorial window
  * \param sY the start y-coordinate of the tutorial window
 * \param eY the end y-coordinate of the tutorial window
 */
EndTutorialEvent::EndTutorialEvent(int sX, int eX, int sY, int eY)
{
    this->startX = sX;
    this->endX = eX;
    this->startY = sY;
    this->endY = eY;

}
