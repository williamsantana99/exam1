#include "mbed.h"
#include "uLCD_4DGL.h"

DigitalIn up(PC_0);
DigitalIn down(PC_1);
DigitalIn confirm(PC_2);

AnalogOut aout(PA_4);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;



int main(void){

    float slew=0.25;
    int sample=slew*8*5;
    int i;
    float k;
    float h;

    while(1){
        for(int i=0; i<sample; i++){
            float k=float(0.9*(i*1.0/(sample*1.0)));            
            aout=k;            
            ThisThread::sleep_for(2ms);
        }
    

        for(int i=0; i<24*5-(2*sample); i++){
            aout=0.9;
            ThisThread::sleep_for(2ms);
        }

        for(int i=0; i<sample; i++){
            float j=float(i*1.0/(sample*1.0));
            aout=0.9*(1.0-j);
            ThisThread::sleep_for(2ms);
        }
    
    }

}
