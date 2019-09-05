#include <stdio.h>

void putCookiesOnSheet(int x) {

  int i;

  for(i = 0; i < x; i++){
    printf("Scoop dough from bowl and put on the tray in slot %d\n", i);
  }

  return; 
}

