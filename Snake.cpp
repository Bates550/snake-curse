#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "Snake.h"
using namespace std;

/* Snake.cpp implements the Snake class
 */

/* Constructors */

Snake::Snake() {
  head = new SnakePiece;
  addTail(Direction::E, 2);
  pos_x = 0;
  pos_y = 0;
  speed = 1;
  length = 3;
}

Snake::Snake(const int posy, const int posx, const int spd, const int len, const Direction::Enum dir) {
  direction = dir;
  Direction::Enum ndir;
  switch(dir) {
  case Direction::N:
    ndir = Direction::S;
    break;
  case Direction::E:
    ndir = Direction::W;
    break;
  case Direction::S:
    ndir = Direction::N;
    break;
  case Direction::W:
    ndir = Direction::E;
    break;
  }

  head = new SnakePiece(ndir);
  addTail(ndir, len-1);

  // If posy < 0, set pos_x to default of 0.
  if (posy < 0)
    pos_y = 0;
  else 
    pos_y = posy;

  // If posx < 0, set pos_y to default of 0
  if (posx < 0)
    pos_x = 0;
  else 
    pos_x = posx;

  // If spd <= 0, set speed to default of 1.
  if (spd <= 0)  
    speed = 1;
  else 
    speed = spd;

  // If len <= 0, set length to default of 3.
  if (len <= 1)
    length = 3;
  else
    length = len;
}

Snake::~Snake() {
  SnakePiece* current = head;
  while (current != NULL) {
    SnakePiece* next = current->getNext();
    delete current;
    current = next;
  }
  head = NULL;
}

/* Getters */

SnakePiece* Snake::getHead() const {
  return head;
}

Direction::Enum Snake::getDirection() const {
  return direction;
}

int Snake::getSpeed() const {
  return speed;
}

int Snake::getLength() const {
  return length;
}

int Snake::getPos_y() const {
  return pos_y;
}

int Snake::getPos_x() const {
  return pos_x;
}

/* Setters */

void Snake::setSpeed(const int spd) {
  speed = spd;
}

/* Operations */

void Snake::addTail() {
  SnakePiece *travel;
  Direction::Enum newNdir;

  for (travel = head; travel->getNext(2) != NULL; travel = travel->getNext())
    ;

  newNdir = travel->getNextDir();
  SnakePiece *newTail = new SnakePiece(newNdir);
  travel = travel->getNext();
  travel->setNext(newTail);
  travel->setNextDir(newNdir);
  ++length;
}

void Snake::addTail(const Direction::Enum dir) {
  SnakePiece* travel;
  SnakePiece* newTail = new SnakePiece(dir); 

  // Traverse to last SnakePiece (i.e. the tail)
  for (travel=head; travel->getNext() != NULL; travel=travel->getNext())
    ;
  
  // Set last SnakePiece to point at the newTail and set nextDir to 
  // the direction of the newTail.
  travel->setNext(newTail);
  travel->setNextDir(dir);
  ++length;
}

void Snake::addTail(const Direction::Enum dir, const int num) {
  int i = 0;
  
  while (i < num) {
    addTail(dir);
    ++i;
  }
}

void Snake::printSnake(WINDOW *win) {
  printSnake(win, pos_y, pos_x);
}

void Snake::printSnake(WINDOW *win, int y, int x) {
  SnakePiece *travel = head->getNext();
  Direction::Enum ndir;
  int pieceCount;

  head->printSnakePiece(win, y, x, PieceType::HEAD);
  switch (head->getNextDir()) {
  case Direction::N:
    --y;
    break;
  case Direction::E:
    ++x;
    break;
  case Direction::S:
    ++y;
    break;
  case Direction::W:
    --x;
    break;
  }
  for (pieceCount = 1; pieceCount < length - 1; ++pieceCount) {
    travel->printSnakePiece(win, y, x, PieceType::BODY);
    ndir = travel->getNextDir();
    switch (ndir) {
    case Direction::N:
      --y;
      break;
    case Direction::E:
      ++x;
      break;
    case Direction::S:
      ++y;
      break;
    case Direction::W:
      --x;
      break;
    }
    travel = travel->getNext();
  }
  travel->printSnakePiece(win, y, x, PieceType::TAIL, ndir);
  move(LINES-1, 0);
}

void Snake::unprintSnake(WINDOW *win) {
  unprintSnake(win, pos_y, pos_x);
}

void Snake::unprintSnake(WINDOW *win, int y, int x) {
  SnakePiece *travel = head;
  int pieceCount;

  for (pieceCount = 0; pieceCount < length; ++pieceCount) {
    travel->unprintSnakePiece(win, y, x);
    switch (travel->getNextDir()) {
    case Direction::N:
      --y;
      break;
    case Direction::E:
      ++x;
      break;
    case Direction::S:
      ++y;
      break;
    case Direction::W:
      --x;
      break;
    }
    travel = travel->getNext();
  }
}

void Snake::printCrudeSnake() {
  int i;
  printf(">*)");
  for (i = 0; i < length-2; ++i) 
    printf("( )");
  printf("(>");
}

void Snake::advance(WINDOW *win, Food &food, const Direction::Enum dir) {
  direction = dir;  
  SnakePiece *travel = head->getNext();
  Direction::Enum temp1, temp2 = head->getNextDir();
  int stage = 0;

  switch (dir) {
  case Direction::N:
    --pos_y;
    head->setNextDir(Direction::S);
    if (food.getPos_y() == pos_y && food.getPos_x() == pos_x) {
      addTail(Direction::S);
      food.newPos(stdscr, getPos_y(), getPos_x());
      food.printFood(stdscr);
    }
    break;
  case Direction::E:
    ++pos_x;
    head->setNextDir(Direction::W);
    if (food.getPos_y() == pos_y && food.getPos_x() == pos_x) {
      addTail(Direction::W);
      food.newPos(stdscr, getPos_y(), getPos_x());
      food.printFood(stdscr);
    }
    break;
  case Direction::S:
    ++pos_y;
    head->setNextDir(Direction::N);
    if (food.getPos_y() == pos_y && food.getPos_x() == pos_x) {
      addTail(Direction::N);
      food.newPos(stdscr, getPos_y(), getPos_x());
      food.printFood(stdscr);
    }
    break;
  case Direction::W:
    --pos_x;
    head->setNextDir(Direction::E);
    if (food.getPos_y() == pos_y && food.getPos_x() == pos_x) {
      addTail(Direction::E);
      food.newPos(stdscr, getPos_y(), getPos_x());
      food.printFood(stdscr);
    }
    break;
  }
  temp1 = travel->getNextDir();
  travel->setNextDir(temp2);

  for (travel = travel->getNext(); travel->getNext() != NULL; travel = travel->getNext()) {
    if (stage % 2 == 0) {
      temp2 = travel->getNextDir();
      travel->setNextDir(temp1);
    } 
    else {
      temp1 = travel->getNextDir();
      travel->setNextDir(temp2);
    }
    ++stage;
  }
}
