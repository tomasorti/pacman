#ifndef MENU_ABOUT_H
#define MENU_ABOUT_H
#include "menu.h"

class MenuAbout : public Menu {
	public:
		MenuAbout(Screen *screen);
		~MenuAbout();
		void draw();
	private:
		enum Entries {BACK};
		int handleSelection();
		SDL_Surface *idea, *coding, *coding2;
};
#endif