#include "color.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char *run_matugen(const char *source_color) {
  FILE *fp;
  char *json;
  size_t len = 0;
  size_t cap = 4096;
  int c;

  char cmd[256];
  snprintf(cmd, sizeof(cmd),
           "matugen color hex \"%s\" -m dark -j hex 2>/dev/null", source_color);

  fp = popen(cmd, "r");
  // popen pipe()： 在内存里建了一根单向的水管（管道）。
  // fork()： 直接克隆出一个子进程。
  // exec()： 在子进程里静悄悄地打开一个 Bash 终端（/bin/sh -c），并执行了 cmd
  // 这个命令。
  // 最后，它把这根水管的一头交给你，另一头接在那个命令的输出上。这就意味着，你可以像读普通文本文件一样，直接把
  // Linux 终端命令的输出结果读进你的 C++ 变量里！

  if (!fp) {
    return NULL;
  }

  json = malloc(cap);
  if (!json) {
    pclose(fp);
    return NULL;
  }

  while ((c = fgetc(fp)) != EOF) {
    if (len + 1 >= cap) {
      cap *= 2;
      char *tmp = realloc(json, cap);
      if (!tmp) {
        free(json);
        pclose(fp);
        return NULL;
      }
      json = tmp;
    }
    json[len++] = (char)c;
  }
  json[len] = '\0';
  pclose(fp);

  return json;
}

int find_color_value(const char *json, const char *key, char *out) {
  char pattern[64];
  snprintf(pattern, sizeof(pattern), "\"%s\"", key);

  const char *p = strstr(json, pattern);
  if (!p)
    return -1;

  p = strstr(p, "\"dark\"");
  if (!p)
    return -1;

  p = strstr(p, "\"color\"");
  if (!p)
    return -1;

  p = strchr(p, '#');
  if (!p)
    return -1;

  int i = 0;
  while (*p && *p != '"' && i < 7) {
    out[i++] = *p++;
  }
  out[i] = '\0';

  return 0;
}

int load_colors_from_matugen(ThemeColors *colors, const char *source_color) {
  char *json = run_matugen(source_color);
  if (!json) {
    fprintf(stderr, "Failed to run matugen\n");
    return -1;
  }

  int ret = 0;

  if (find_color_value(json, "primary", colors->primary) != 0)
    strcpy(colors->primary, "#ffb59c");
  if (find_color_value(json, "on_primary", colors->on_primary) != 0)
    strcpy(colors->on_primary, "#55200b");
  if (find_color_value(json, "background", colors->background) != 0)
    strcpy(colors->background, "#1a110f");
  if (find_color_value(json, "on_background", colors->on_background) != 0)
    strcpy(colors->on_background, "#f1dfd9");
  if (find_color_value(json, "surface", colors->surface) != 0)
    strcpy(colors->surface, "#1a110f");
  if (find_color_value(json, "on_surface", colors->on_surface) != 0)
    strcpy(colors->on_surface, "#f1dfd9");
  if (find_color_value(json, "primary_container", colors->accent) != 0)
    strcpy(colors->accent, "#72351f");

  free(json);
  return ret;
}
