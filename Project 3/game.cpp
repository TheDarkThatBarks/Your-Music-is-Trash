#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "GameStart.h"

void loadResources();

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }
    LM.setFlush(false);

    // Show splash screen.
    df::splash();

    loadResources();
    new GameStart();

    GM.run();

    // Shut everything down.
    GM.shutDown();
}

void loadResources() {
    RM.loadSprite("sprites/arrow-box-sprite.txt", "arrow-box");

    RM.loadSprite("sprites/left-arrow-sprite.txt", "left-arrow");
    RM.loadSprite("sprites/up-arrow-sprite.txt", "up-arrow");
    RM.loadSprite("sprites/down-arrow-sprite.txt", "down-arrow");
    RM.loadSprite("sprites/right-arrow-sprite.txt", "right-arrow");

    RM.loadSprite("sprites/player-sprite.txt", "player");

    RM.loadSprite("sprites/boss1-sprite.txt", "boss1");
    RM.loadSprite("sprites/boss2-sprite.txt", "boss2");
    RM.loadSprite("sprites/boss3-sprite.txt", "boss3");

    RM.loadSprite("sprites/game-start-sprite.txt", "game-start");

    RM.loadMusic("music/Stage1-song.wav", "stage1");
    RM.loadMusic("music/Stage2-song.wav", "stage2");
    RM.loadMusic("music/Stage3-song.wav", "stage3");

    RM.loadMusic("music/TitleScreen-music.wav", "start-music");

    RM.loadSound("sounds/correct.wav", "correct");
    RM.loadSound("sounds/miss.wav", "miss");
    RM.loadSound("sounds/select1.wav", "select1");
    RM.loadSound("sounds/select2.wav", "select2");
}