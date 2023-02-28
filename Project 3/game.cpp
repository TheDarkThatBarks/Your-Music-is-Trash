#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "ArrowBox.h"
#include "Arrow.h"
#include "ArrowSpawner.h"
#include "Combometer.h"
#include "Player.h"
#include "Boss.h"

int main(int argc, char* argv[]) {

    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 0;
    }

    // Show splash screen.
    df::splash();

    // Creates ArrowBoxes
    RM.loadSprite("sprites/arrow-box-sprite.txt", "arrow-box");
    ArrowBox* up = new ArrowBox(df::Vector(20, 10), UP);
    ArrowBox* down = new ArrowBox(df::Vector(30, 10), DOWN);
    ArrowBox* left = new ArrowBox(df::Vector(10, 10), LEFT);
    ArrowBox* right = new ArrowBox(df::Vector(40, 10), RIGHT);

    // Loads Arrow sprites
    RM.loadSprite("sprites/left-arrow-sprite.txt", "left-arrow");
    RM.loadSprite("sprites/right-arrow-sprite.txt", "right-arrow");
    RM.loadSprite("sprites/up-arrow-sprite.txt", "up-arrow");
    RM.loadSprite("sprites/down-arrow-sprite.txt", "down-arrow");

    // Loads Player and Boss Sprites
    RM.loadSprite("sprites/player-sprite.txt", "player");
    RM.loadSprite("sprites/boss3-sprite.txt", "boss1");

    // Creates Player and Boss
    new Player();
    new Boss();

    // Creates ArrowSpawner
    new ArrowSpawner(up, down, left, right, "music/Stage1-Song.txt");

    // Creates combOmeter(TM)
    new Combometer();

    // Plays music
    RM.loadMusic("music/Stage1-song.wav", "stage1");
    RM.getMusic("stage1")->play();

    GM.run();

    // Shut everything down.
    GM.shutDown();
}