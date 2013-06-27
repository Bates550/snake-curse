#include <stdio.h>
#include <ncurses.h>
#include "Snake.h"
using namespace std;

typedef struct _win_border_struct {
  chtype ls, rs, ts, bs, tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct {
  int startx, starty;
  int height, width;
  WIN_BORDER border;
} WIN;

void init_win_params(WIN *p_win);
void print_win_params(WIN *p_win);
void create_box(WIN *win, bool flag);

int main(int argc, char* argv[]) {

  WIN win;
  int ch;
  Snake charlie(5, 5, 1, 3, Direction::W);
  Food doug;

  initscr();
  start_color();
  keypad(stdscr, TRUE);
  noecho();
  init_pair(1, COLOR_MAGENTA, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_GREEN);
  init_pair(3, COLOR_BLACK, COLOR_GREEN);

  init_win_params(&win);
  print_win_params(&win);
 
  printw("Press q to quit");

  doug.newPos(stdscr, charlie.getPos_y(), charlie.getPos_x());
  doug.printFood(stdscr);

  halfdelay(10);
  while ((ch = getch()) != 'q') {
    switch (ch) {
    case KEY_LEFT:
      charlie.unprintSnake(stdscr);    
      charlie.advance(stdscr, doug, Direction::W); 
      charlie.printSnake(stdscr);
      break;
    case KEY_RIGHT:
      charlie.unprintSnake(stdscr);    
      charlie.advance(stdscr, doug, Direction::E);
      charlie.printSnake(stdscr);
      break;
    case KEY_UP:
      charlie.unprintSnake(stdscr);    
      charlie.advance(stdscr, doug, Direction::N);
      charlie.printSnake(stdscr);
      break;
    case KEY_DOWN:
      charlie.unprintSnake(stdscr);    
      charlie.advance(stdscr, doug, Direction::S);
      charlie.printSnake(stdscr);
      break;
    default:
      charlie.unprintSnake(stdscr);
      charlie.advance(stdscr, doug, charlie.getDirection());
      charlie.printSnake(stdscr);
    }
  }
  endwin();
  return 0;
}

void init_win_params(WIN *p_win) {
  p_win->height = 30;
  p_win->width = 50;
  p_win->starty = (LINES - p_win->height) / 2;
  p_win->startx = (COLS - p_win->width) / 2;

  p_win->border.ls = '|';
  p_win->border.rs = '|';
  p_win->border.ts = '-';
  p_win->border.bs = '-';
  p_win->border.tl = '+';
  p_win->border.tr = '+';
  p_win->border.bl = '+';
  p_win->border.br = '+';
}

void print_win_params(WIN *p_win) {
#ifdef _DEBUG
  mvprintw(25, 0, "%d %d %d %d", p_win->startx, p_win->starty, 
	   p_win->width, p_win->height);
  refresh();
#endif
}

void create_box(WIN *p_win, bool flag) {
  int i, j;
  int x, y, w, h;

  x = p_win->startx;
  y = p_win->starty;
  w = p_win->width;
  h = p_win->height;

  if (flag == TRUE) {
    mvaddch(y, x, p_win->border.tl);
    mvaddch(y, x + w, p_win->border.tr);
    mvaddch(y + h, x, p_win->border.bl);
    mvaddch(y + h, x + w, p_win->border.br);
    mvhline(y, x + 1, p_win->border.ts, w - 1);
    mvhline(y + h, x + 1, p_win->border.bs, w - 1);
    mvvline(y + 1, x, p_win->border.ls, h - 1);
    mvvline(y + 1, x + w, p_win->border.rs, h - 1);
  }
  else 
    for (j = y; j <= y + h; ++j)
      for (i = x; i <= x + w; ++i)
	mvaddch(j, i, ' ');
  move(LINES-1, 0);
  refresh();
}
