#pragma once

#include "Object.h"
#include "Event.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Arrow : public df::Object {
	private:
	Direction dir;

	public:
	Arrow(df::Vector pos, Direction d);
	int eventHandler(const df::Event* p_e) override;
};