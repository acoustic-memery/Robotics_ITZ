#include "main.h"
#include "lcdFunctions.h"

void init(){
  lcdSetBacklight(uart1, true);
  int selection = 1;

  while(selection == 1){
  lcdPrint(uart1, 1, "Test--------Auto");
  lcdPrint(uart1, 2, "  ^          ^  ");

  if (lcdReadButtons(uart1) == 4) {
      program = 1;
      selection = 2;


  } else if (lcdReadButtons(uart1) == 1) {
      program = 2;
      selection = 3;


}

delay(50);

}
if (selection == 3){
  lcdClear(uart1);
  lcdPrint(uart1, 1, "driving confirmed");

}
else if (selection == 2){
  lcdClear(uart1);
  lcdPrint(uart1, 1, "programming confirmed");

}

  delay(1000);

}

void autoOutput(void*parameter){
  while(1){
    int caseType[] = {1, 2, 3};
    int display = 1;

while (1){
 if (lcdReadButtons(uart1) == 4) {
     display++;

 } else if (lcdReadButtons(uart1) == 1) {
     display--;
   }


   if(caseType[display] == 1){

  lcdPrint(uart1, 1, "mogo is %d", analogRead(2));

   }
   else if (caseType[display] == 2){
     lcdPrint(uart1, 1, "gyro is %d", gyroGet(mainGyro));

      if (lcdReadButtons(uart1) == 2){
        gyroReset(mainGyro);
      }

   }
   else if (caseType[display] == 3)  {

   lcdPrint(uart1, 1, " left drive  %d", encoderGet(driveEncLeft));
  lcdPrint(uart1, 2, "right drive %d", encoderGet(driveEncRight));
      if (lcdReadButtons(uart1) == 2){
        encoderReset(driveEncLeft);
        encoderReset(driveEncRight);
      }


     }

delay(150);



}

  }
}
