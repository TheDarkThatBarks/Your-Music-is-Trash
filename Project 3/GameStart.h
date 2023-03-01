#pragma once

#include "ViewObject.h"
#include "Music.h"

class GameStart : public df::ViewObject {
	private:
	df::Music* music;
	df::Music* levelMusic;
	void start(int level);
	int draw() override;

	public:
	GameStart();
	void stop();
	int eventHandler(const df::Event* p_e) override;
	void playMusic();
};