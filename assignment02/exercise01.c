#include <stdio.h>
#include <math.h>


int main(void){
  int n[3] = {10, 50, 1025};
  int k[3];
  for(int i = 0; i < 3; i++) {
    k[i] = floor(log2(n[i]));
    printf("%d >> %d\n", n[i], k[i]);
  }
  return 0;
}
