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