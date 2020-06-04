#include <IRremote.h>

#define IR 8
#define rele 3
#define sensor 6
#define timer_led 13

int work, TIME, chek, time_chek;
long timer;

IRrecv irrecv(IR);
decode_results res;

void setup(){

    Serial.begin (9600);
    pinMode(IR, INPUT);
    pinMode(rele, OUTPUT);
    pinMode(sensor, INPUT);
    pinMode(timer_led, OUTPUT);
    digitalWrite(12,HIGH);
    irrecv.enableIRIn();
}

void loop(){

    if (digitalRead (sensor) == 1){
        if (chek == work && chek == 0){
            work = 1;
        }else if(chek == work && chek == 1){
            work = 0;
        }
        time_chek++;
    }else{
        time_chek = 0;
        chek = work;
    }

    rele_v();

    if (work > 1){work = 0;}
    if (time_chek == 500){
        TIME++;
        timer = millis();
    }
    if (TIME > 1){TIME = 0;}
    if (TIME == 1){timer_v();}
    if (irrecv.decode(&res)){ir_v();}
}


void timer_v(){

    if (millis() - timer > 300000){
        work = 0;
        TIME = 0;
    }
}

void rele_v(){
  
    digitalWrite (rele, chek);
}


void ir_v(){

    switch (res.value){
        case 16738455:
            work++;
        break;
        case 16756815:
            TIME++;
            timer = millis();
        break;
    }
    irrecv.resume();
}