#include "Arrow.h"
#include "EventCollision.h"
#include "LogManager.h"

Arrow::Arrow(Direction d) {
	setType("Arrow");
	setSprite("arrow");
	dir = d;
	setVelocity(df::Vector(0, 0.25));
}

int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		return 0;
	}
	return -1;
}