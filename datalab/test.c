#include <stdint.h>
#include <stdio.h>
#include "bits.h"

#define SIZE_OF_ARRAY(A) (sizeof(A) / sizeof(A[0]))
typedef unsigned char byte;
typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, int len) {
  int i;
  for (i = 0; i < len; i++)
    printf(" %.2x", start[i]);  // line:data:show_bytes_printf
  printf("\n");
}

#define DELTA sizeof(int)
void test_bug() {
  // sizeof return unsigned number, so i will always larger then 0
  for (int i = 10; i - DELTA >= 0; i -= DELTA) {
    printf("loop...\n");
  }
}

void ieee_float() {
  printf("---------ieee float test start-----------\n");
  float fa = 15213;
  printf("normalized: %f\n", fa);
  show_bytes((byte_pointer)&fa, sizeof(float));
  int ia = (int)fa;
  printf("cast 15213f to int: %d\n", ia);
  show_bytes((byte_pointer)&ia, sizeof(int));

  float fb = +0;
  float fc = 1.0 / 0.0;
  float fd = 1.0 / -0.0;
  printf("unnormalized: %f\n", fb);
  show_bytes((byte_pointer)&fb, sizeof(float));
  printf("positive inf: %f\n", fc);
  show_bytes((byte_pointer)&fc, sizeof(float));

  printf("negative inf: %f\n", fd);
  show_bytes((byte_pointer)&fd, sizeof(float));
  printf("is pos inf eq neg inf: %d\n", fc == fd);

  float fe = fc - fc;
  printf("nan: %f\n", fe);
  show_bytes((byte_pointer)&fe, sizeof(float));
  // float min_dnomal = __FLT32_DENORM_MIN__;
  float ff = (3.14 + 1e127) - 1e127;
  float fg = 3.14 + (1e10 - 1e10);
  printf("(3.14 +1e127) - 1e127 = %f\n", ff);
  printf("3.14 + (1e10 - 1e10) =  %f\n", fg);
  printf("---------ieee float test end-----------\n");
}

// passed
int test_bitXor() {
  printf("4 xor 5 = %d\n", bitXor(4, 5));
  printf("4 xor 4 = %d\n", bitXor(4, 4));
  printf("-2147483648 xor -2147483648 = %d\n",
         bitXor(-2147483648, -2147483648));
}

// passed
int test_conditional() {
  printf("2 ? 4 : 5 = %d\n", conditional(2, 4, 5));
  printf("0 ? 4 : 5 = %d\n", conditional(0, 4, 5));
}

// passed
int test_logicalNeg() {
  int a = 2;
  int b = 0;
  printf("!%d = %d\n", a, logicalNeg(a));
  printf("!%d = %d\n", b, logicalNeg(b));
}

// passed
int test_isLessOrEqual() {
  printf("is 4 <= 5? %s\n", isLessOrEqual(4, 5) ? "Yes" : "No");
  printf("is 4 <= 4? %s\n", isLessOrEqual(4, 4) ? "Yes" : "No");
  printf("is 4 <= 2? %s\n", isLessOrEqual(4, 2) ? "Yes" : "No");
  printf("is -2147483648 <= 2147483647? %s\n",
         isLessOrEqual(-2147483648, 2147483647) ? "Yes" : "No");
}

int main() {
  test_bitXor();
  test_conditional();
  test_logicalNeg();
  test_isLessOrEqual();

  printf("is tmax: %d\n", isTmax(2147483647));
  printf("is tmax: %d\n", isTmax(100));
  printf("is all odd bits: %d\n", allOddBits(0xAAAAAAA0));
  printf("negete of -1: %d\n", negate(-1));
  printf("is digit %d: %d\n", 1, isAsciiDigit(1));
  printf("is digit %c: %d\n", 'A', isAsciiDigit('A'));
  printf("is digit %s: %d\n", "'1'", isAsciiDigit('1'));
}