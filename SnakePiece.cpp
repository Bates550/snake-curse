#include <stdlib.h>
#include <ncurses.h>
#include "SnakePiece.h"
using namespace std;

/* SnakePiece.cpp implements the SnakePiece class.
 */

SnakePiece::SnakePiece() {
  next = NULL;
  nextDir = Direction::E;
}

SnakePiece::SnakePiece(const Direction::Enum ndir) {
  next = NULL;
  nextDir = ndir;
}

SnakePiece::SnakePiece(SnakePiece* nxt, const Direction::Enum ndir) {
  next = nxt;
  nextDir = ndir;
}

SnakePiece* SnakePiece::getNext() const {
  return next;
}

SnakePiece* SnakePiece::getNext(const int num) const {
  SnakePiece* travel;  
  int i;

  for (i = 0; i < num; ++i)
    travel = travel->getNext();

  return travel;
}

Direction::Enum SnakePiece::getNextDir() const {
  return nextDir;
}

void SnakePiece::setNext(SnakePiece* nxt) {
  next = nxt;
}

void SnakePiece::setNextDir(const Direction::Enum dir) {
  nextDir = dir;
}

void SnakePiece::printSnakePiece(WINDOW *win, int y, int x) {
  printSnakePiece(win, y, x, PieceType::BODY);
}

void SnakePiece::printSnakePiece(WINDOW *win, int y, int x, const PieceType::Enum piece) {
 switch (piece) {
 case PieceType::HEAD:
   switch (nextDir) {
   case Direction::N:
     mvwprintw(win, y, x, "A");
     break;
   case Direction::E:
     mvwprintw(win, y, x, ">");
     break;
   case Direction::S:
     mvwprintw(win, y, x, "V");
     break;
   case Direction::W:
     mvwprintw(win, y, x, "<");
     break;
   }
   break;
   // not valid for PieceType::TAIL due to insufficient nextDir data.
 case PieceType::TAIL:
   break;
 case PieceType::BODY:
   mvwprintw(win, y, x, "#");
   break;
 }
}

void SnakePiece::printSnakePiece(WINDOW *win, int y, int x, PieceType::Enum piece,  Direction::Enum dir) {
 switch (piece) {
 case PieceType::HEAD:
   switch (nextDir) {
   case Direction::N:
     mvwprintw(win, y, x, "A");
     break;
   case Direction::E:
     mvwprintw(win, y, x, ">");
     break;
   case Direction::S:
     mvwprintw(win, y, x, "V");
     break;
   case Direction::W:
     mvwprintw(win, y, x, "<");
     break;
   }
   break;
 case PieceType::TAIL:
   if (dir == Direction::N || dir == Direction::S)
     mvwprintw(win, y, x, "|");
   else
     mvwprintw(win, y, x, "-");
   break;
 case PieceType::BODY:
   mvwprintw(win, y, x, "#");
   break;
 }
}

void SnakePiece::unprintSnakePiece(WINDOW *win, int y, int x) {
  mvwprintw(win, y, x, " ");
}
