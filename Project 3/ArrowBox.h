#pragma once

#include "Object.h"
#include "Event.h"
#include "Arrow.h"

class ArrowBox : public df::Object {
	private:
	Direction dir;
	df::Box topBig;
	df::Box topSmall;
	df::Box bottomBig;
	df::Box bottomSmall;
	Arrow* arrow;
	bool floatComp(std::string comp, float f1, float f2);

	public:
	ArrowBox(df::Vector pos, Direction d);
	int eventHandler(const df::Event* p_e) override;
};