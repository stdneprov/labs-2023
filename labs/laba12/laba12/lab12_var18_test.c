#include <assert.h>

#include "lab12_var18.h"

int main() {
  printf("Testing function %s\n", "amount of digits");
  assert(amount_of_digits(0) == 1);
  assert(amount_of_digits(1) == 1);
  assert(amount_of_digits(1234) == 4);
  assert(amount_of_digits(1234567890) == 10);
  printf("passed\n");

  printf("Testing function %s\n", "change_2nd_and_prelast");
  assert(change_2nd_and_prelast(0) == 0);
  assert(change_2nd_and_prelast(1) == 1);
  assert(change_2nd_and_prelast(12) == 21);
  assert(change_2nd_and_prelast(123) == 123);
  assert(change_2nd_and_prelast(1234) == 1324);
  assert(change_2nd_and_prelast(1234567890) == 1934567820);
  printf("passed\n");
}