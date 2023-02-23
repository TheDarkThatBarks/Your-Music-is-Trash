#pragma once

#include "Object.h"
#include "Event.h"

class ArrowBox : public df::Object {
	private:
	df::Box topBig;
	df::Box topSmall;
	df::Box bottomBig;
	df::Box bottomSmall;

	public:
	ArrowBox(df::Vector pos);
	int eventHandler(const df::Event* p_e) override;
};