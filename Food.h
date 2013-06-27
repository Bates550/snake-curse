#ifndef FOOD_H
#define FOOD_H

/* Food.h declares the Food class 
 */

#include <stdlib.h>
#include <time.h>

class Food {
 public:

  /* Constructors */
  
  // Sets the random seed w/ time and creates a piece of Food at a random y, x.
  Food();

  // Sets the random seed w/ time and creates a piece of Food at y, x.
  Food(int y, int x);

  /* Getters */

  int getPos_x() const;

  int getPos_y() const;

  bool getEaten() const;

  /* Setters */

  void setPos_x(const int posx);

  void setPos_y(const int posy);

  void setEaten(const bool gone);

  /* Operations */

  // Prints the Food at posY, posX.
  void printFood(WINDOW *win);

  // Prints the Food at y, x.
  void printFood(WINDOW *win, int y, int x);

  // Prints a " " at posY, posX.
  void unprintFood(WINDOW *win);

  // Prints a " " at y, x.
  void unprintFood(WINDOW *win, int y, int x);

  // DOES NOT CHECK TO SEE IF POSITION IS OCCUPIED BY SNAKE. MUST IMPLEMENT. 
  // Randomly generates a new position and updates posY, posX to assume it. 
  void newPos(WINDOW *win, int y, int x);
  
 private:
  int pos_y;
  int pos_x;
  bool eaten;
};

#endif
