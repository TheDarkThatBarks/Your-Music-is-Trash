#include "ArrowBox.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "ArrowSpawner.h"
#include "GameManager.h"

Arrow::Arrow() {
	setType("Arrow");
	box = NULL;
	float speed = (float)(0.125 * ArrowSpawner::getBeatsPerSecond());
	setVelocity(df::Vector(0, speed));
	registerInterest(df::STEP_EVENT);
}

int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		if (getPosition().getY() > (box->getPosition().getY() + box->getBox().getVertical() - 1.5)) {
			box->popArrow();
			WM.markForDelete(this);
			return 1;
		}
	}
	return 0;
}