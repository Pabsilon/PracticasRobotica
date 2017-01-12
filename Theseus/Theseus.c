#include <wiringPi.h>
#include <softPwm.h>

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

int main(){
	wiringPiSetup();
	softPwmCreate(LENGINE_GPIO,0,200);
	softPwmCreate(RENGINE_GPIO,0,200);
	foward_fast();
	while(1){
	}
}

void forward_fast(){
	pthread_t left;
	pthread_t right;
	pthread_create(left,NULL,softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST));
	pthread_create(right,NULL,softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST));
}