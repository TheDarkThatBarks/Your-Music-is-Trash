#include "Arrow.h"
#include "EventCollision.h"

Arrow::Arrow() {
	setType("Arrow");
	setSprite("arrow.sprite");
	dir = UP;
	setVelocity(df::Vector(0, 1));
}

int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		return 0;
	}
	return -1;
}