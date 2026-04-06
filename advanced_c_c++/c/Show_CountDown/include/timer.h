#ifndef TIMER_H
#define TIMER_H

#include <time.h>

typedef struct {
  time_t start_time;
  int duration_secs;
  int remaining_secs;
  int paused;
  time_t paused_time;
} Timer;

void timer_init(Timer *t, int minutes);
void timer_update(Timer *t);
int timer_is_done(const Timer *t);
void timer_pause(Timer *t);
void timer_resume(Timer *t);

#endif
