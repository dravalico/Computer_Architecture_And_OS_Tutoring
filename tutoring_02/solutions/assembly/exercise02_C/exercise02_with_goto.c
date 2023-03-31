#include <stdio.h>

int main(int argc, char * argv[])
{
  int R0 = 0;
  int R1 = 10;
  int R2 = 0;
loop:
  if (R2 == R1) {
    goto end_loop;
  }
  R2 = R2 + 1;
  R0 = R0 + R2;
  goto loop;
end_loop:
  printf("R0 = %d\n", R0);
  return 0;
}
