#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "Food.h"

#define GLINES 20
#define GCOLS 50

Food::Food() {
  srand(time(NULL));
  pos_y = rand() % GLINES;
  pos_x = rand() % GCOLS;
  eaten = false;
}

Food::Food(int y, int x) {
  srand(time(NULL));
  pos_y = y;
  pos_x = x;
  eaten = false;
}

int Food::getPos_x() const {
  return pos_x;
}

int Food::getPos_y() const {
  return pos_y;
}

bool Food::getEaten() const {
  return eaten;
}

void Food::setPos_x(const int posx) {
  pos_x = posx;
}

void Food::setPos_y(const int posy) {
  pos_y = posy;
}

void Food::setEaten(const bool gone) {
  eaten = gone;
}

void Food::printFood(WINDOW *win) {
  mvwprintw(win, pos_y, pos_x, "o");
}

void Food::printFood(WINDOW *win, int y, int x) {
  mvwprintw(win, y, x, "o");
}

void Food::unprintFood(WINDOW *win) {
  mvwprintw(win, pos_y, pos_x, " ");
}

void Food::unprintFood(WINDOW *win, int y, int x) {
  mvwprintw(win, y, x, " ");
}

void Food::newPos(WINDOW *win, int y, int x) {
  do
    pos_y = rand() % GLINES; 
  while (y == pos_y); 
  do 
    pos_x = rand() % GCOLS;
  while (x == pos_x);
}
