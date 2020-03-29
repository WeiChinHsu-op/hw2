#include "mbed.h"


Serial pc( USBTX, USBRX );
AnalogIn Ain(A0);
AnalogOut Aout(DAC0_OUT);
DigitalIn  Switch(SW2);
DigitalOut redLED(LED1);
DigitalOut greenLED(LED2);

int sample = 2000;
float a ;
float ADCdata[2000];
float ADCdata1;
float ADCdata2;
float ADCdata3;
int countpeak = 0;
int hundred, tenten, lastww;
char table[3] = {0x00,0x00,0x00};
BusOut display(D6, D7, D9, D10, D11, D5, D4, D8);


int main(){

    for (int i = 0; i < sample; i++){
        
        ADCdata[i] = Ain;
        wait(1./sample);
    }
    for (int i = 0; i < sample; i++){
        pc.printf("%1.3f\r\n", ADCdata[i]);
        wait(0.01);
    }
    
    for(int i=0; i<2000 ; i=i+1){
        if(i==0){
            ADCdata1 = Ain;
            wait(0.0005);
            ADCdata2 = Ain;
            wait(0.0005);
            ADCdata3 = Ain;
        }
        else{
            wait(0.0005);
            ADCdata1 = ADCdata2;
            ADCdata2 = ADCdata3;
            ADCdata3 = Ain;
        }

        if(ADCdata2>ADCdata1 && ADCdata2>ADCdata3)
        countpeak++;
    
    }
    /*while(1){
        pc.printf("%d\r\n", countpeak);
    }*/
    hundred = countpeak/100;
    tenten = (countpeak/10)%10;
    lastww = countpeak%10;

    for (int i=0;i<3;i=i+1){
        if(i==0){
            switch (hundred)
            {
            case 1:
                table[i]=0x06;
                break;
            
            case 2:
                table[i]=0x5B;
                break;

            case 3:
                table[i]=0x4F;
                break;

            case 4:
                table[i]=0x66;
                break;

            case 5:
                table[i]=0x6D;
                break;

            case 6:
                table[i]=0x7D;
                break;
            
            case 7:
                table[i]=0x07;
                break;

            case 8:
                table[i]=0x7F;
                break;

            case 9:
                table[i]=0x6F;
                break;
            
            case 0:
                table[i]=0x3F;
                break;

            default:
                table[i]=0x00;
                break;
            }
        }
        else if(i==1){
            switch (tenten)
            {
            case 1:
                table[i]=0x06;
                break;
            
            case 2:
                table[i]=0x5B;
                break;

            case 3:
                table[i]=0x4F;
                break;

            case 4:
                table[i]=0x66;
                break;

            case 5:
                table[i]=0x6D;
                break;

            case 6:
                table[i]=0x7D;
                break;
            
            case 7:
                table[i]=0x07;
                break;

            case 8:
                table[i]=0x7F;
                break;

            case 9:
                table[i]=0x6F;
                break;
            
            case 0:
                table[i]=0x3F;
                break;

            default:
                table[i]=0x00;
                break;
            }
        }
        else if(i==2){
            switch (lastww)
            {
            case 1:
                table[i]=0x86;
                break;
            
            case 2:
                table[i]=0xDB;
                break;

            case 3:
                table[i]=0xCF;
                break;

            case 4:
                table[i]=0xE6;
                break;

            case 5:
                table[i]=0xED;
                break;

            case 6:
                table[i]=0xFD;
                break;
            
            case 7:
                table[i]=0x87;
                break;

            case 8:
                table[i]=0xFF;
                break;

            case 9:
                table[i]=0xEF;
                break;

            case 0:
                table[i]=0xBF;
                break;

            default:
                table[i]=0x00;
                break;
            }
        }
        else{
            i = i;
        }
    }

     while(1){
        for(float i=0; i<2; i+=0.05 ){
            Aout = 0.5 + 0.5*sin(i*3.14159);
            wait(1./(40*countpeak*1.4));
        }
        if( Switch == 0 ){
            greenLED = 1;
            redLED = 0;
            for (int i = 0; i<3; i = i+1){
                display = table[i];
                wait(1);
            }
        }
        else{
            redLED = 1;
            greenLED = 0;
            display = 0x00;
        }
    }
    
}








