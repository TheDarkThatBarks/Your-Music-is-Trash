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

	public:
	ArrowBox(df::Vector pos, Direction d);
	int eventHandler(const df::Event* p_e) override;
};