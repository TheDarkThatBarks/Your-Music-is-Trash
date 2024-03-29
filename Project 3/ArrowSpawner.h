#pragma once

#include <queue>
#include <vector>
#include "Event.h"
#include "Object.h"
#include "ArrowBox.h"
#include "Combometer.h"
#include "CombometerMax.h"
#include "GameStart.h"

class ArrowSpawner : public df::Object {
	private:
	ArrowBox* up;
	ArrowBox* down;
	ArrowBox* left;
	ArrowBox* right;
	static float beatsPerSecond;
	std::queue<std::vector<Direction>> arrows;
	static Combometer* combo;
	static CombometerMax* comboMax;
	static GameStart* gameStart;

	public:
	ArrowSpawner(ArrowBox* l, ArrowBox* u, ArrowBox* d, ArrowBox* r, std::string songFile);
	static float getBeatsPerSecond();
	static Combometer* getCombo();
	static void setCombo(Combometer* newCombo);
	static CombometerMax* getComboMax();
	static void setComboMax(CombometerMax* newCombo);
	static void setGameStart(GameStart* newGameStart);
	int eventHandler(const df::Event* p_e) override;
};