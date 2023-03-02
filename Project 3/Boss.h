#pragma once

#include "Object.h"

class Boss : public df::Object {
	public:
	Boss(std::string boss, int newSlowdown);
};
