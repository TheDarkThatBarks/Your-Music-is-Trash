#pragma once

#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
	private:
	df::Music* music;
	df::Music* levelMusic;
	int level;
	int combo1;
	int combo2;
	int combo3;
	/*ViewObject combo1;
	ViewObject combo2;
	ViewObject combo3;*/
	void start(int l);
	int draw() override;
	void createCombos();

	public:
	GameStart();
	void stop();
	void playMusic();
	int eventHandler(const df::Event* p_e) override;
};