#include "ArrowBox.h"
#include "EventStep.h"
#include "LogManager.h"
#include "WorldManager.h"

Arrow::Arrow() {
	setType("Arrow");
	//dir = UP;
	//box = new ArrowBox();
	box = NULL;
	setVelocity(df::Vector(0, 0.25));
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