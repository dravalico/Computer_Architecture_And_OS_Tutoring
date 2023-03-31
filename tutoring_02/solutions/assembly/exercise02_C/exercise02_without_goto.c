#include <stdio.h>

int main(int argc, char * argv[])
{
  int R0 = 0;
  int R1 = 10;
  int R2 = 0;
  while (R2 != R1) {
    R2 = R2 + 1;
    R0 = R0 + R2;
  }
  printf("R0 = %d\n", R0);
  return 0;
}
