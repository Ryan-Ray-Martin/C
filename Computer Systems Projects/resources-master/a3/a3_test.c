#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "a3.h"

Name name1;
Name name2;
Name name3;
Name name4;

void init() {
  srand(time(NULL));

  name1.first = "Alyssa";
  name1.middle = "Mary";
  name1.last = "Antle";
  name1.age = 18;

  name2.first = "BeN";
  name2.middle = "ivan";
  name2.last = "bitDiDdle";
  name2.age = 32;

  name3.first = "Cassie";
  name3.middle = "Maria";
  name3.last = "Charstrup";
  name3.age = 64;

  name4.first = "Daniel";
  name4.last = "Diamond";
  name4.age = 42;
}


void start_test(const char *test) {
  static int count = 1;
  printf("Test #%d: %s\n\n", count++, test);
}

void end_test() {
  printf("\n--------------------------------\n\n");
}


void test_big() {
  start_test("Print Big");

  big(&name1);
  printf("\n");
  big(&name2);
  printf("\n");
  big(&name4);
  printf("\n");

  end_test();
}

void test_last() {
  start_test("Print Last");

  last(&name2);
  last(&name4);

  end_test();
}

void test_reg() {
  start_test("Print Reg");

  reg(&name3);
  reg(&name4);

  end_test();
}

void test_mid() {
  start_test("Print Mid");

  mid(&name4);
  mid(&name1);

  end_test();
}

void test_small() {
  start_test("Print Small");

  small(&name4);
  small(&name2);

  end_test();
}

void test_formatName() {
  start_test("Print formatName");

  formatName(&name1, 'B');
  formatName(&name1, 'L');
  formatName(&name1, 'r');
  formatName(&name1, 'M');
  formatName(&name1, 'S');

  formatName(&name4, 'B');
  formatName(&name4, 'l');
  formatName(&name4, 'R');
  formatName(&name4, 'm');
  formatName(&name4, 'S');

  end_test();
}

int test_fillName() {
  char dest[100] = {0};
  fillName(&name1, 'b', dest);
  printf("fillName result: %s\n", dest);
}

int test_listByName() {

}

int test_listByAge() {
  Name* names[4];

  names[0] = &name1;
  names[1] = &name2;
  names[2] = &name3;
  names[3] = &name4;

  listByAge(names, 4, 'm');
}

int main(void) {
  init();

  test_big();
  test_last();
  test_reg();
  test_mid();
  test_small();
  test_formatName();

  printf("More tests will be added; feel free to add your own!\n");

  return EXIT_SUCCESS;
}



