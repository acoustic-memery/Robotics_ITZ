#include "lcdFunctions.h"
#include "main.h"

void preAuton(){
lcdSetBacklight(uart1, true);

  int selection = 1;
     int autoId[] = {1, 2, 3, 4};

       int counter = 1;

       while (selection == 1) {
       lcdPrint(uart1, 2, "<      OK      >");


           if (lcdReadButtons(uart1) == 4) {
               counter++;

           } else if (lcdReadButtons(uart1) == 1) {
               counter--;

  }

           if (autoId[counter] == 1) {
               lcdPrint(uart1, 1, "LOAD: POST RS");
           } else if (autoId[counter] == 2) {
               lcdPrint(uart1, 1, "LOAD: MG LS RED");
           } else if (autoId[counter] == 3) {
               lcdPrint(uart1, 1, "LOAD: MG RS BLUE");
           }
           else if (autoId[counter] == 4) {
             lcdPrint(uart1, 1, "LOAD: POST LS");
           }


           if (lcdReadButtons(uart1) == 2) {
               if (autoId[counter] == 1) {
                   program = 1;
           selection = 2;
                   break;
               } else if (autoId[counter] == 2) {
                   program = 2;
           selection = 2;

           break;
               } else if (autoId[counter] == 3) {
                   program = 3;
           selection = 2;

                   break;
               }
               else if (autoId[counter] == 4) {
                 program = 4;
                 selection = 2;
               }
               else {
                   continue;
               }

           }
delay(250);
         }
lcdClear(uart1);
if (program == 1) {
 lcdPrint(uart1, 1, "POST RS CONFIRMED");
}
else if (program == 2) {
 lcdPrint(uart1, 1, "MOGO LS CONFIRMED");
}
else if (program == 3) {
 lcdPrint(uart1, 1, "MOGO RS CONFIRMED");
}
else if (program == 4) {
  lcdPrint(uart1, 1, "POST LS CONFIRMED");
}
delay(1000);
}

void driveLcd () {
 lcdPrint(uart1, 1, "lift is %d", encoderGet(liftEnc));

  if (lcdReadButtons(uart1) == 2){
    encoderReset(liftEnc);
  }

  //lcdPrint(uart1, 2, "gyro is %d", gyroGet(mainGyro));
    lcdPrint(uart1, 2, "chainbar is %d", analogRead(2));
}
