#include "EventStep.h"
#include "ArrowSpawner.h"
#include "ArrowBox.h"

Arrow::Arrow() {
	setType("Arrow");
	box = NULL;
	float speed = (float)(0.125 * ArrowSpawner::getBeatsPerSecond());
	setVelocity(df::Vector(0, speed));
	miss = RM.getSound("miss");
	registerInterest(df::STEP_EVENT);
}

int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {

		// If Arrow gets too low, deletes it
		if (getPosition().getY() > (box->getPosition().getY() + box->getBox().getVertical() - 1.5)) {
			miss->play();
			box->popArrow();
			WM.markForDelete(this);
			return 1;
		}
	}
	return 0;
}