#pragma once

#include <vector>
#include <queue>
#include "Object.h"
#include "Event.h"
#include "ArrowBox.h"

class ArrowSpawner : public df::Object {
	private:
	ArrowBox* up;
	ArrowBox* down;
	ArrowBox* left;
	ArrowBox* right;
	static int beatsPerSecond;
	std::queue<std::vector<Direction>> arrows;

	public:
	ArrowSpawner(ArrowBox* l, ArrowBox* u, ArrowBox* d, ArrowBox* r, std::string songFile);
	static int getBeatsPerSecond();
	int eventHandler(const df::Event* p_e) override;
};