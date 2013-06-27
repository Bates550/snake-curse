#ifndef SNAKEPIECE_H
#define SNAKEPIECE_H

/* SnakePiece.h declares the SnakePiece class, which is essentially a Node
 * of the linked list that is the Snake class. SnakePieces have a pointer 
 * to the next SnakePiece and the direction to the next SnakePiece. The
 * direction is of the type Direction::Enum as defined in Enum.h.
 * INCLUDES:
 * <stdlib.h>
 * <ncurses.h>
 * "SnakePiece.h"
 */

#include "Enum.h"

class SnakePiece {
 public:

  /* Constructors */

  // No-arg constructor sets next to NULL.
  SnakePiece();

  // Creates a SnakePiece with next pointing to NULL and sets nextDir to dir.
  SnakePiece(const Direction::Enum dir);

  // Creates a SnakePiece with next pointing to nxt and sets nextDir to dir.
  SnakePiece(SnakePiece* nxt, const Direction::Enum dir);

  /* Getters */

  SnakePiece* getNext() const;

  // Returns the numth SnakePiece after the current (e.g. example.getNext() is
  // equivalent to example.getNext(1). 
  SnakePiece* getNext(const int num) const;

  Direction::Enum getNextDir() const ;  

  /* Setters */

  void setNext(SnakePiece* nxt); 
 
  // Pass Direction::N, ::E, ::S, or ::W for dir. 
  void setNextDir(const Direction::Enum dir);

  /* Operations */

  // Prints a BODY  SnakePiece to *win at y, x. 
  void printSnakePiece(WINDOW *win, int y, int x);

  // Prints a HEAD or BODY SnakePiece to *win at y, x. Pass 
  //PieceType::HEAD or ::BODY for piece. If PieceType::TAIL is passed, the method will do nothing.
  void printSnakePiece(WINDOW *win, int y, int x, const PieceType::Enum piece);

  // Prints a HEAD, TAIL, or BODY SnakePiece to *win at y, x oriented in the dir direction.
  // Should be used exclusively for printing TAIL SnakePieces as they don't have a meaningful 
  // nextDir so we must specify which direction for them to print.
  void printSnakePiece(WINDOW *win, int y, int x, const PieceType::Enum piece, const Direction::Enum dir);

  // Prints a ' ' to *win at y, x. 
  void unprintSnakePiece(WINDOW *win, int y, int x);

 private:
  SnakePiece* next;
  Direction::Enum nextDir;
};

#endif
