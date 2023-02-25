#include "Arrow.h"
#include "EventCollision.h"
#include "LogManager.h"

Arrow::Arrow() {
	setType("Arrow");
	dir = UP;
	setVelocity(df::Vector(0, 0.25));
}

Direction Arrow::getDir() const {
	return dir;
}

void Arrow::setDir(Direction d) {
	dir = d;
}

int Arrow::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_c_e = dynamic_cast <const df::EventCollision*> (p_e);
		return 0;
	}
	return -1;
}