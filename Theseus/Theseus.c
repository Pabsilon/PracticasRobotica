#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

//BLOQUE DE DECLARACION DE CONSTANTES

//Bloque de Motores:
//GPIOS
#define LENGINE_GPIO 1
#define RENGINE_GPIO 2
//FRECUENCIAS
#define LENGINE_FORWARD_FAST 17
#define LENGINE_FORWARD_SLOW 16
#define ENGINE_STOP 15
#define RENGINE_FORWARD_SLOW 14
#define RENGINE_FORWARD_FAST 13
#define LENGINE_BACKWARDS_FAST RENGINE_FORWARD_FAST
#define LENGINE_BACKWARDS_SLOW RENGINE_FORWARD_SLOW
#define RENGINE_BACKWARDS_FAST LENGINE_FORWARD_FAST
#define RENGINE_BACKWARDS_SLOW LENGINE_FORWARD_SLOW


#define LS_GPIO 3
#define RS_GPIO 4

void forward_fast(){
	printf("Going Forward Fast.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST);
}

void backwards_fast(){
	printf("Going Backwards Fast.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_FAST);
}

void forward_slow(){
	printf("Going Forward Slow.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_SLOW);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_SLOW);
}

void backwards_slow(){
	printf("Going Backwards Slow.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_SLOW);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_SLOW);
}

void hard_stop(){
	printf("Hard Stopping.\n");
	softPwmWrite(LENGINE_GPIO,ENGINE_STOP);
	softPwmWrite(RENGINE_GPIO,ENGINE_STOP);
}

void hard_left(){
	printf("Doing Hard Left. \n");
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST);
}

void hard_right(){
	printf("Doing Hard Right. \n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_FAST);
	}

int main(){
	wiringPiSetup();
	softPwmCreate(LENGINE_GPIO,0,200);
	softPwmCreate(RENGINE_GPIO,0,200);
	forward_fast();
	while(1){
	}
}
