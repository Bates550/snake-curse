#ifndef SNAKE_H
#define SNAKE_H

/* Snake.h declares the Snake class which is essentially a linked list class
 * with SnakePiece nodes and only the necessary functionality. 
 * INCLUDES:
 * <stdlib.h>
 * <stdio.h>
 * <ncurses.h>
 * "SnakePiece.h"
 * "Snake.h"
 * "Food.h"
 */

#include "Enum.h"
#include "SnakePiece.h"
#include "Food.h"

class Snake {
 public:

  /* Constructors */

  // No-arg constructor creates a Snake with a head and two SnakePieces.
  // Sets speed to 1, length to 3, and nextDir to E for all SnakePieces.
  // Sets pos_y and pos_y to 0.
  Snake();

  // Creates a Snake with a head and len-1 SnakePieces. Sets pos_x to posx, 
  // pos_y to posy, speed to spd, and nextDir to the opposite of dir so that 
  // the Snake is facing the dir direction.
  // If an int < 0 is passed for posy, pos_y will be set to default of 0.
  // If an int < 0 is passed for posx, pos_x will bet set to default of 0.
  // If an int <= 0 is passed for spd, speed will be set to default of 1.
  // If an int <= 1 is passed for len, speed will be set to default of 3.
  // If an invalid direction is passed for dir, nextDir will be set to 
  // default of E for all SnakePieces.
  Snake(const int posy, const int posx, const int spd, const int len, const Direction::Enum dir);

  ~Snake();

  /* Getters */

  SnakePiece* getHead() const;

  Direction::Enum getDirection() const;

  int getSpeed() const;

  int getLength() const;

  int getPos_y() const;

  int getPos_x() const;

  /* Setters */

  void setSpeed(const int spd);

  /* Operations */

  // Adds a SnakePiece to the end of the Snake in the direction of nextDir of the second
  // to last SnakePiece (i.e. the last BODY piece) and increments length. The added
  // SnakePiece has its direction set
  void addTail();

  // Adds a SnakePiece to the end of the Snake in the dir direction and increments length.
  // The added SnakePiece has its direction set to dir as well. 
  void addTail(const Direction::Enum dir);

  // Adds num SnakePieces to the end of the Snake in the dir direction and adds num to length.
  // All of the added SnakePieces have their direction set to dir, so this method can only 
  // be used to create a straight line of SnakePieces.
  void addTail(const Direction::Enum dir, const int num);

  // Prints the Snake to *win at its current position
  void printSnake(WINDOW *win);

  // Prints the Snake to *win with it's head at y, x
  void printSnake(WINDOW *win, int y, int x); 

  // Prints ' ' for all SnakePieces to "unprint" (i.e. delete from the window) the Snake on *win.
  void unprintSnake(WINDOW *win);

  // "Unprints" the Snake on *win starting at y, x. 
  void unprintSnake(WINDOW *win, int y, int x);
  
  // Prints a crude representation of the Snake on one line.
  void printCrudeSnake();

  // Advances the head SnakePiece in the dir direction and changes pos_x and pos_y and the 
  // nextDir of the head to the opposite direction of dir. The nextDir of the SnakePiece 
  // following the head is stored in one of two temp variables. For each following SnakePiece, 
  // nextDir of the next SnakePiece is held in one of the temps before it is assigned the 
  // nextDir of the current SnakePiece. 
  // If Snake advances onto a piece of food, addTail() is called and the Snake grows 1 SnakePiece.
  void advance(WINDOW *win, Food &food, const Direction::Enum dir);

 private: 
  SnakePiece* head;
  Direction::Enum direction;
  int pos_y;
  int pos_x;
  int speed;
  int length;
};

#endif
