#include "Unit.h"
#include "Gamefield.h"
#include "UnitMovementFinishedEvent.h"

/**
 * Attack the provided target (unit)
 * updates health of target and ap of attacking unit
 *
 * \param target unit that will be attacked
 */
void Unit::attack(std::shared_ptr<Unit> target, bool cover)
{
	this->m_state = STATES::UNITSTATE::SHOOTING;

	if (cover)
	{
		if (target->changeHP((m_dmg * 0.9f)))
		{
			this->levelUp();
		}
	}

	else {
		if (target->changeHP(m_dmg)) {
			this->levelUp();
		}
	}


	updateAP(m_apCostAttack);

}

/**
 * Attack the provided target(headquarter)
 * changes health of headquarter and ap of attacking unit
 *
 * \param target headquarter that will be attacked
 */
void Unit::attack(std::shared_ptr<Headquarter> target)
{
	this->m_state = STATES::UNITSTATE::SHOOTING;
	target->changeHP(m_dmg);
	updateAP(m_apCostAttack);
}

/**
 * change the hp of the current unit
 * raises deathevent if unit is at or below zero health after health change
 * returns booleans if unit died
 * \param damage the amount of dmg dealt
 */
bool Unit::changeHP(int damage)
{

	m_currentHP -= damage;

	if (m_currentHP <= 0)
	{
		EventBus::instance().publish(new DeathEvent(this->getptr()));
		return true;
	}
	else
	{
		return false;
	}
}

/**
 * Reset ap of the unit to its base value
 *
 */
void Unit::resetAP()
{
	m_currentAP = m_ap;
}

/**
 * update the unit & its sprite.
 *
 */
void Unit::update() {
	if (m_state == STATES::UNITSTATE::RUNNING) {
		move();
	}
	m_state = m_sprite->render(m_state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP(), this->getLevel());

}

/**
 * update the state of the unit, takes current hp into account
 *
 * \param state
 */
void Unit::update(STATES::UNITSTATE state)
{
	m_state = m_sprite->render(state);
	m_spriteHealthBar->render(this->getHp(), this->getCurrentHP(), this->getLevel());
}

void Unit::setState(STATES::UNITSTATE state)
{
	this->m_state = state;
}

void Unit::setLastingState(STATES::UNITSTATE state)
{
	this->getSprite()->setDefaultState(state);
}

STATES::UNITSTATE Unit::getLastingState()
{
	return this->getSprite()->getDefaultState();
}

STATES::UNITSTATE Unit::getState()
{
	return this->m_state;
}

/**
 * removes the provided amount of ap from a unit
 *
 * \param cost amount of ap to be removed
 */
void Unit::updateAP(int cost)
{
	m_currentAP -= cost;
}

void Unit::levelUp()
{
	this->m_level++;
	if (this->m_level > 3)
	{
		this->m_level = 3;
	}

	//adds 10% to each value for every level
	this->m_hp = m_hp * (1.0f + (((float)m_level - 1) / 10.0f));
	this->m_currentHP = m_currentHP * (1.0f + (((float)m_level - 1) / 10.0f));
	this->m_dmg = m_dmg * (1.0f + (((float)m_level - 1) / 10.0f));
	this->m_range = m_range * (1.0f + (((float)m_level - 1) / 10.0f));
}

/**
 * moves the unit to target tile
 *
 */
void Unit::setTargetCoordinates(int x, int y)
{
	this->m_targetX = x;
	this->m_targetY = y;

	this->setState(STATES::UNITSTATE::RUNNING);
}

/**
 * moves the unit to target tile
 *
 */
void Unit::move()
{

	int currentX = this->getSprite()->getX();
	int currentY = this->getSprite()->getY();


	int distanceY = 0;
	int distanceX = 0;
	if (m_targetX < currentX) {
		distanceX = this->m_targetX / 64 - currentX / 64 - 1;
	}
	else {
		distanceX = this->m_targetX / 64 - currentX / 64;
	}
	if (m_targetY < currentY) {
		distanceY = (this->m_targetY) / 64 - currentY / 64 - 1;
	}
	else {
		distanceY = (this->m_targetY) / 64 - currentY / 64;
	}

	int newX = currentX;
	int newY = currentY;

	//walk x-axis
	if (distanceX > 0) {
		newX = currentX + m_speed + CTimer::Get()->GetElapsed();
	}
	else if (distanceX < 0) {
		newX = currentX + (m_speed + CTimer::Get()->GetElapsed()) * -1;
	}
	//walk y-axis
	else if (distanceY > 0) {
		newY = currentY + m_speed + CTimer::Get()->GetElapsed();
	}
	else if (distanceY < 0) {
		newY = currentY + (m_speed + CTimer::Get()->GetElapsed()) * -1;
	}
	else {
		//Ziel erreicht
		EventBus::instance().publish(new UnitMovementFinishedEvent(this->getptr()));

		std::shared_ptr<FieldTile> tmp = Gamefield::instance().findTileByUnit(this->getptr());
		if (tmp->hasCopse()) {
			tmp->removeCorpse();
		}
		else {
			tmp->refreshTile();
		}

		return;
	}
	//set the Sprite to new postion
	m_sprite->setPos(newX, newY);
	m_spriteHealthBar->setPos(newX, newY);

	//refresh tiles passed by
	if (m_targetY < currentY && distanceX == 0) {
		currentY += 64;
	}
	if (m_targetX < currentX) {
		currentX += 64;
	}

	if (currentX > (2*64-1) && currentX < (20*64) ) {
	
		std::shared_ptr<FieldTile> tmp = Gamefield::instance().getFieldTileFromXY(currentX, currentY);

		if (tmp) {
			tmp->refreshTile();
		}
	}
	else {
		std::shared_ptr<FieldTile> tmp = Gamefield::instance().getSpawnTileFromXY(this->getColorRed(), currentX, currentY);
		if (tmp) {
			tmp->refreshTile();
		}
	}
}

