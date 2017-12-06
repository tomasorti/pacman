#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "cmdline_options.h"
#include "constants.h"
#include "game.h"
#include "ghost_figur.h"
#include "pacman_figur.h"
#include "menu_main.h"
#include "highscore.h"

#define VERSION 1.0

void getCommandLine(int argc, char *argv[]);
void cleanUp();
void highscore();

int main(int argc, char *argv[]) {

    srand((unsigned int)time(0)); // init randomize

    getCommandLine(argc, argv);
    
    if (Screen::getInstance()->hasSDLInitErrorOccured())
        return EXIT_FAILURE;

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

void getCommandLine(int argc, char *argv[]) {

    CommandLineOptions::set(argc, argv);
    if (CommandLineOptions::exists("h", "help")) {
        std::cout << "This game is a Pacman clone (version " << VERSION << ")."              << std::endl
                  << "Usage: pacman [options]"                                               << std::endl
                  << std::endl
                  << "Options:"                                                              << std::endl
                  << "  -h, --help         Display this help message and quit."              << std::endl
                  << "  -f, --fullscreen   Start the game in fullscreen mode."               << std::endl
                  << "  --noscaling        Do not try to scale the game in fullscreen mode." << std::endl
                  << "  --nocentering      Do not center the game in fullscreen mode."       << std::endl
                  << "  -s, --nosound      Start with sound switched off."                   << std::endl
                  << "  -m, --nomusic      Start with music switched off."                   << std::endl
                  << "  -v, --version      Print version number and quit."                   << std::endl
                  << "  --name=...         Provide the player's name."                       << std::endl
                  << "  --highscore=...    Define path to highscore file."                   << std::endl
                  << "  --hs-key=...       Highscore encryption key (hexadecimal)."          << std::endl
                  << std::endl;
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
