#include <stdio.h>

void weight_count(float weight, float height) {
  float body_count = weight / (height * height);
  if (body_count < 18 && body_count >= 0)
    printf("t=%f Lower weight!", body_count);
  else if (body_count >= 18 && body_count < 25)
    printf("t=%f Standard weight!", body_count);
  else if (body_count >= 25 && body_count < 27)
    printf("t=%f Higher weight!", body_count);
  else if (body_count > 27)
    printf("t=%f Too fat!", body_count);
}

int main(void) {
  float weight, height;
  printf("Please enter h,w:");
  scanf("%f,%f", &height, &weight);
  weight_count(weight, height);

  return 0;
}
