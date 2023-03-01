#pragma once

#include <vector>
#include <queue>
#include "Object.h"
#include "Event.h"
#include "ArrowBox.h"
#include "Combometer.h"
#include "CombometerMax.h"

class ArrowSpawner : public df::Object {
	private:
	ArrowBox* up;
	ArrowBox* down;
	ArrowBox* left;
	ArrowBox* right;
	static int beatsPerSecond;
	std::queue<std::vector<Direction>> arrows;
	static Combometer *combo;
	static CombometerMax *comboMax;

	public:
	ArrowSpawner(ArrowBox* l, ArrowBox* u, ArrowBox* d, ArrowBox* r, std::string songFile);
	static int getBeatsPerSecond();
	static Combometer *getCombo();
	static void setCombo(Combometer* newCombo);
	static CombometerMax *getComboMax();
	static void setComboMax(CombometerMax *newCombo);
	int eventHandler(const df::Event* p_e) override;
};