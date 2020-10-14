#ifndef _BEEP_H
#define _BEEP_H
#include"global.h"
sbit beep=P1^5;	

//function statement

void beepStart();
void beepStop();
void beeP(uint us);
//
void beeP(uint ms)
{
    beepStart();
    delay(ms*100);
    beepStop();
}
void beepStart()
{
    beep=0;
}
void beepStop(){
    beep=1;
}
#endif