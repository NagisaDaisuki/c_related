#ifndef COLOR_H
#define COLOR_H

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  char primary[8];
  char on_primary[8];
  char background[8];
  char on_background[8];
  char surface[8];
  char on_surface[8];
  char accent[8];
} ThemeColors;

int load_colors_from_matugen(ThemeColors *colors, const char *source_color);

#ifdef __cplusplus
}
#endif

#endif
