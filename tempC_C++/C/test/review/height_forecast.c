#include <stdalign.h>
#include <stdio.h>

static inline float man_adult(float faHeight, float moHeight);
static inline float woman_adult(float faHeight, float moHeight);
static inline float sports(float adult);
static inline float diet(float adult);
void forecast_height();

int main(void) {
  forecast_height();
  return 0;
}

static inline float man_adult(float faHeight, float moHeight) {
  return (float)(faHeight + moHeight) * 0.54;
}
static inline float woman_adult(float faHeight, float moHeight) {
  return (float)(faHeight * 0.923 + moHeight) / 2;
}
static inline float sports(float adult) { return adult * 1.02; }
static inline float diet(float adult) { return adult * 1.015; }

void forecast_height() {
  char sex, isSports, isDiet;
  sex = isDiet = isSports = ' ';

  float faHeight, moHeight, Height;
  faHeight = moHeight = Height = 0.0;

  if (scanf(" %c", &sex) != 1)
    return;
  if (scanf("%f", &faHeight) != 1)
    return;
  if (scanf("%f", &moHeight) != 1)
    return;
  if (scanf(" %c", &isSports) != 1)
    return;
  if (scanf(" %c", &isDiet) != 1)
    return;

#if 0
#define DEBUG
#endif

#ifdef DEBUG
  printf("fa: %f\n", faHeight);
  printf("mo: %f\n", moHeight);
  Height = man_adult(faHeight, moHeight);
  printf("Before addon: %f\n", Height);
  Height = sports(Height);
  printf("add sports: %f\n", Height);
  Height = diet(Height);
  printf("add sports: %f\n", Height);
#endif
  if (sex == 'M' || sex == 'm') {
    Height = man_adult(faHeight, moHeight);
    if (isSports == 'Y' || isSports == 'y')
      Height = sports(Height);
    if (isDiet == 'Y' || isDiet == 'y')
      Height = diet(Height);
  } else if (sex == 'F' || sex == 'f') {
    Height = woman_adult(faHeight, moHeight);
    if (isSports == 'Y' || isSports == 'y')
      Height = sports(Height);
    if (isDiet == 'Y' || isDiet == 'y')
      Height = diet(Height);
  }
  printf("%f(cm)\n", Height);
}
