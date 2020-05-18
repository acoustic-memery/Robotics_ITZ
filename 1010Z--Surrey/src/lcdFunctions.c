#include "lcdFunctions.h"
#include "main.h"

void preAuton(){
lcdSetBacklight(uart1, true);

  int selection = 1;
     int autoId[] = {1, 2, 3, 4, 5};

       int counter = 1;

       while (selection == 1) {
       lcdPrint(uart1, 2, "<      OK      >");


           if (lcdReadButtons(uart1) == 4) {
               counter++;

           } else if (lcdReadButtons(uart1) == 1) {
               counter--;

  }

           if (autoId[counter] == 1) {
               lcdPrint(uart1, 1, "LOAD: POST RED"); //program 1
           } else if (autoId[counter] == 2) {
               lcdPrint(uart1, 1, "LOAD: MG LS RED"); //program 2
           } else if (autoId[counter] == 3) {
               lcdPrint(uart1, 1, "LOAD: MG RS BLUE"); //program 3
           }
           else if (autoId[counter] == 4) {
             lcdPrint(uart1, 1, "LOAD: POST BLUE"); //program 4
           }
           else if (autoId[counter] == 5){
              lcdPrint(uart1, 1, "LOAD: POST SINGLE"); //program 5
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
               else if (autoId[counter] == 5) {
                 program = 5;
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
else if (program == 4) {
  lcdPrint(uart1, 1, "POST SINGLE CONFIRMED");
}
delay(1000);
}

void driveLcd (void*parameter) {
     int caseType[] = {1, 2, 3, 4, 5, 6};
     int display = 1;

while (1){
  if (lcdReadButtons(uart1) == 4) {
      display++;

  } else if (lcdReadButtons(uart1) == 1) {
      display--;
    }

    if(caseType[display] == 1){
         lcdPrint(uart1, 2, "lift is %d", analogRead(4));

    }
    else if (caseType[display] == 2){
      lcdPrint(uart1, 1, "gyro is %d", gyroGet(mainGyro));

       if (lcdReadButtons(uart1) == 2){
         gyroReset(mainGyro);
       }
    }
    else if (caseType[display] == 3)  {

    lcdPrint(uart1, 1, " left drive  %d", encoderGet(driveEncLeft));

       if (lcdReadButtons(uart1) == 2){
         encoderReset(driveEncLeft);

       }
         }
      else if (caseType[display] == 4) {
        lcdPrint(uart1, 1, " Cpot is  %d", analogRead(2));

      }
      else if (caseType[display] == 5) {
        lcdPrint(uart1, 1, "CBar is %d", encoderGet(chainEnc));

      }
      if (lcdReadButtons(uart1) == 2){
        encoderReset(chainEnc);

      }
      else if (caseType[display] == 6) {
        lcdPrint(uart1, 1, "Mogo is %d", encoderGet(mogoEnc));

      }
      if (lcdReadButtons(uart1) == 2){
        encoderReset(mogoEnc);

      }



  delay(250);
}

}
/*
void robotStatus () {
  int caseType [] {1, 2, 3, 4, 5};
  int display = 1;


}
*/
