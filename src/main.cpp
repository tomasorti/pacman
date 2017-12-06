#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "cmdline_options.h"
#include "constants.h"
#include "screen.h"
#include "game.h"
#include "ghost_figur.h"
#include "pacman_figur.h"
#include "menu_main.h"
#include "highscore.h"

#define VERSION 1.0

void setCommandLine(int argc, char *argv[]);
void cleanUp();
void highscore();

int main(int argc, char *argv[]) {

    srand((unsigned int)time(0)); // init randomize

    setCommandLine(argc, argv);

    Screen* screen = Screen::getInstance();
    if (screen->hasSDLInitErrorOccured())
        return EXIT_FAILURE;

    screen->fontFilename = CommandLineOptions::getValue("", "font");
    
    while (MenuMain::getInstance()->show()) {

        Game* game = Game::getInstance();        
        game->start();
        if (game->isGameOver()) {
            // do not load() here, this has been done at the time the game was over
            highscore();
        }
    }

    cleanUp();
    return EXIT_SUCCESS;
}

void setCommandLine(int argc, char *argv[]) {

    CommandLineOptions::set(argc, argv);
    if (CommandLineOptions::exists("h", "help")) {
        CommandLineOptions::printHelp();
        exit(EXIT_SUCCESS);
    }
    else if (CommandLineOptions::exists("v", "version")) {
        std::cout << "pacman version " << VERSION << std::endl;
        exit(EXIT_SUCCESS);
    }   
}

void highscore() {

    HighscoreList* highscoreList = HighscoreList::getInstance();
    if (!highscoreList->isReadonly()) {

        highscoreList->show(true, true);  // player name alterable, last entry highlighted
        if (highscoreList->getIdxLastInsertedEntry() >= 0) {
            HighscoreEntry *entry = highscoreList->getEntry(highscoreList->getIdxLastInsertedEntry());
            entry = new HighscoreEntry(std::string(entry->getPlayerName()), entry->getScore(), entry->getLevel());
            highscoreList->load();
            highscoreList->insertEntry(entry);
            highscoreList->save();
        }
        highscoreList->show(false, true);
    }    
}

void cleanUp() {

    Game::cleanUpInstance();
    MenuMain::cleanUpInstance();
    Labyrinth::cleanUpInstance();
    Pacman::cleanUpInstance();
    Ghost::cleanUpGhostArray();
    Sounds::cleanUpInstance();
    Screen::cleanUpInstance();
    HighscoreList::cleanUpInstance();
    CommandLineOptions::cleanUp();    
}
