#ifndef FIGUR_H
#define FIGUR_H
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "screen.h"
#include "labyrinth.h"

class Figur {
	public:
		// constructor and destructor
		Figur(int init_x, int init_y, float init_v, 
		      Screen *screen, Labyrinth *labyrinth);
		virtual ~Figur();

		// direction
		enum Direction{LEFT, UP, RIGHT, DOWN};
		
		// position of the figure
		int x, y; 
		
		// last x and y values (important when checking whether pills have been eaten)
		int last_x, last_y; 
		
		// four directions of movement
		void move_left(float ms, float max_step = 999);
		void move_up(float ms, float max_step = 999);
		void move_right(float ms, float max_step = 999);
		void move_down(float ms, float max_step = 999);
		
		// wrapper for the directional movement functions
		void move(float ms, Direction direction);

		// abstract draw method
		virtual void draw() = 0;

		// add an update rectangle to the screen
		virtual void addUpdateRect() = 0;

		// sets the speed of the figure
		void set_speed(float v);
		
		// returns the speed
		float get_speed() const;
		
		// has the figure moved? (needed for performance tuning)
		bool was_moving();
		
		// parking figur
		void parking();
		
		// returns the direction
		Direction get_direction() const;
		
		// sets the direction of movement
		void set_direction(Direction direction);

		// start/stop the figure
		void set_stop(int stop);

		// return the surface, must be implemented by subclasses
		virtual SDL_Surface* get_Surface() const = 0;  // makes the class abstract

		// reset the figure
		virtual void reset();

		// hunting or hunted
		enum Hunter {GHOST, PACMAN, NONE};
		virtual Hunter get_hunter() const;
		virtual void set_hunter(Hunter hunter);

		virtual bool touched() { return false; }

		                        
		//helper functions
		int less(int a, int b);
		int greater(int a, int b);

		// sets the figure's visibility (e.g. for pacman after eating a ghost or a fruit)
		void setVisibility(bool v);

	protected:
		float cur_y;
		float cur_x;
		int wechsel_x;
		int wechsel_y;
		int wechsel_rate;
		float dx, dy;
		Direction direction;
		int intelligence;
		float least(float a, float b);
		int initial_x;
		int initial_y;
		float initial_v;
		float last_speed;
		SDL_Surface *LoadSurface(const char *filename, int transparent_color);
		Labyrinth *labyrinth;
		Screen *screen;
		Hunter hunter;
		int visible;
};
#endif
