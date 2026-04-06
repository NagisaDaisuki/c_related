#ifndef RENDERER_H
#define RENDERER_H

#include "color.h"
#include "timer.h"
#include <ncurses.h>

typedef struct {
  ThemeColors colors;
  WINDOW *win;
} Renderer;

void renderer_init(Renderer *r, const ThemeColors *colors);
void renderer_draw(const Renderer *r, const Timer *t);
void renderer_cleanup(Renderer *r);

#endif
