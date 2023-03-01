#pragma once

#include "Object.h"
#include "Event.h"

class Boss : public df::Object {
	public:
	Boss(std::string boss, int newSlowdown);
};
