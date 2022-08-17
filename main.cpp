#include "mbed.h"
#include "TextLCD.h"
#include "Keypad.h"
#include "HCSR04.h"
#include <stdio.h>
TextLCD my_lcd(PTE20, PTE21, PTE22, PTE23, PTE29, PTE30, TextLCD::LCD16x2);
Keypad kpad(PTA12, PTD4, PTA2, PTA1, PTC9, PTC8, PTA5, PTA4);
HCSR04 sensor(PTC13, PTC12);


long distance_2;
long distance;
    
PwmOut led_red(PTD2);
PwmOut led_green(PTD5);


PwmOut ledGreen(LED_GREEN);
PwmOut ledRed(LED_RED);
PwmOut ledBlue(LED_BLUE);


int main() {


ledBlue = 1;
ledGreen = 1;
ledRed = 1;

my_lcd.printf("Enter The Dist:");
my_lcd.locate(0,1);
char key;
int released = 1;
char inputArray[16];
int i = 0 ;
int dig1;





while(i<16){
    key = kpad.ReadKey(); //read the current key pressed
    if(key == '\0')
    released = 1; //set the flag when all keys are released
    if((key != '\0') && (released == 1)) { //if a key is pressed AND previous key was released
    if (key == 'A'){
          sscanf(inputArray, "%d%", &dig1);
          while(1) {


                long distance = sensor.distance(CM); 
                 wait(1.0);
                long distance_2 = sensor.distance(CM);

                    if (distance<distance_2) {
                         ledBlue=0; 
                         ledGreen=1;
                         ledRed=1;

                        }
                    else if (distance>distance_2) {
                         ledGreen=0;
                         ledRed=0;
                        ledBlue=1; 

                        }
                    else {
                         ledGreen=1;
                         ledRed=1;
                         ledBlue=1; 
        }
                 my_lcd.cls();  
                  my_lcd.printf("CM  %d  \n",distance);

         
                  my_lcd.locate(0,1);

                 if ((distance > 0  ) &&(distance<=dig1)) { 
                 
                                       
                    if ((distance >=(dig1/3)  ) &&(distance<=((dig1+dig1)/3))){
                     led_green=0;
                         led_red=1;
                         wait(0.05f);
                         led_red=0.8;
                         wait(0.05f);
                         led_red=0.6;    
                         wait(0.05f);
                         led_red=0.4;
                         wait(0.05f);
                         led_red=0.2;
                         wait(0.05f);
                         
                         
                         }
                     else if ((distance > 0  ) &&(distance<(dig1/3))) {
                         led_red=1;
                         led_green=0;
                         }
                    else {
                        my_lcd.printf("Very close!!");
                    led_red=0;
                    led_green=1;
                     }
                     }
                    
                 else if ((distance > 0  )  &&(distance>=dig1))
                 {
                my_lcd.printf("Not Close  :((");
                led_red=0;
                led_green=0;
                }        
        }
    }  

    
    else{
    my_lcd.printf("%c", key);
    }
    

    inputArray[i] = key;
    i++;
    released = 0; //clear the flag to indicate that key is still pressed
    }
    }
}
