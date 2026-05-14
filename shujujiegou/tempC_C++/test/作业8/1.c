#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int pot1[2];
  int pot2[2];
  double area;
} Rectangle;

Rectangle *sortRecFun(Rectangle *Rec, int n);

int main(void) {
  int num = 0;
  if (fscanf(stdin, "%d", &num) != 1)
    return -1;

  Rectangle *arrRec = (Rectangle *)calloc(sizeof(Rectangle), num);
  Rectangle *copyArrRec = (Rectangle *)calloc(sizeof(Rectangle), num);
  if (arrRec == NULL || copyArrRec == NULL) {
    return -1;
  }

  double sumArea = 0.0;
  double avgArea = 0.0;

  for (int i = 0; i < num; i++) {
    if (fscanf(stdin, "%d %d %d %d", &arrRec[i].pot1[0], &arrRec[i].pot1[1],
               &arrRec[i].pot2[0], &arrRec[i].pot2[1]) != 4)
      return -1;
    arrRec[i].area = abs(arrRec[i].pot2[0] - arrRec[i].pot1[0]) *
                     abs(arrRec[i].pot2[1] - arrRec[i].pot1[1]);
    sumArea += arrRec[i].area;
  }

  // for (int i = 0; i < num; i++) {
  //   fprintf(stdout, "%d,%d,%d,%d,area=%.1lf\n", arrRec[i].pot1[0],
  //           arrRec[i].pot1[1], arrRec[i].pot2[0], arrRec[i].pot2[1],
  //           arrRec[i].area);

  //}
  memcpy(copyArrRec, arrRec, sizeof(Rectangle) * num);
  Rectangle *sortRec = sortRecFun(copyArrRec, num);
  for (int i = 0; i < num; i++) {
    fprintf(stdout, "%d,%d,%d,%d,area=%.1lf\n", sortRec[i].pot1[0],
            sortRec[i].pot1[1], sortRec[i].pot2[0], sortRec[i].pot2[1],
            sortRec[i].area);
  }

  avgArea = sumArea / num;
  fprintf(stdout, "%.1lf\n", avgArea);

  free(sortRec);
  free(copyArrRec);
  free(arrRec);
  return EXIT_SUCCESS;
}

Rectangle *sortRecFun(Rectangle *Rec, int n) {

  for (int gap = n / 2; gap > 0; gap /= 2) {
    for (int i = gap; i < n; i += 1) {
      Rectangle temp = Rec[i];

      int j;
      for (j = i; j >= gap && Rec[j - gap].area < temp.area; j -= gap)
        Rec[j] = Rec[j - gap];
      Rec[j] = temp;
    }
  }
  Rectangle *retRec = (Rectangle *)calloc(sizeof(Rectangle), n);
  memcpy(retRec, Rec, sizeof(Rectangle) * n);

  return retRec;
}
