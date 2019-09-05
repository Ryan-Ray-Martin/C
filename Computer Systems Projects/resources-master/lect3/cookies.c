#include <stdio.h>

#include "cookie_helpers.h"

int main(){

  int amtDoughInBowl = 12;
  int numSlotsOnTray = 12;

  /*
  int i;

  for(i = 0; i < numSlotsOnTray; i++){
    printf("Scoop dough from bowl and put on the tray in slot %d\n", i);
  }
  */

  putCookiesOnSheet(numSlotsOnTray); 

  printf("Put the tray in the oven\n");

  int timeLeft = 5;

  while (timeLeft > 0){
    printf("Wait for the timer to go off\n");
    timeLeft--;
  }

  printf("Take the tray out of the oven\n");

  int numCookiesEaten = 0;

  if (numCookiesEaten < 5){
    printf("Take a cookie off the tray and eat it\n");
  }
  //else{

  printf("Take the cookies off the tray and put them in the cookie jar\n");
  //}

  printf("All done!! \n");

}


