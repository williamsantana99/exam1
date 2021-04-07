#include "mbed.h"
#include "uLCD_4DGL.h"

InterruptIn up(PC_0);
InterruptIn down(PC_1);
InterruptIn sel(PC_2);

//EventQueue eventQueue;

AnalogOut aout(PA_4);

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

float s=1.0;
float slew=1.0;


void plus(){
   if(s==1){
     s=1;
   }
   else {
     s=s*2;
   }
}

void sub(){
   if(s==0.125){
     s=0.125;
   }
   else{
     s=s*0.5;  
   }
}

void check(){
   slew=s;
}

int main(void){
    
   
    int sample=slew*8*5;
    
    up.rise(plus);
    down.rise(sub);
    sel.rise(check);
    
    //Thread eventThread(osPriorityNormal);
    //eventThread.start(callback(&eventQueue::dispatch_forever));
    
    //eventQueue.call(&print);
    
    
    while(1){

        uLCD.text_width(4); //4X size text
        uLCD.text_height(4);
        uLCD.locate(1,2);
        uLCD.printf("%3f",s);  

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