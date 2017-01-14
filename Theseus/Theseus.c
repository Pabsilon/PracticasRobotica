/*
Created by Pablo Mac-Veigh, for our Robotics class of 2016-2017.

This project uses the standard MIT license.

Using WiringPi, we're enabling a basic robot to follow black lines or to find it's way out of maze.
For the maze, we'll use the left hand (or right hand) algorithm, wich will be decided upon watching the maze.
For the black line following, we still have to work on it

*/
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>

//CONSTANT DECLARATION BLOCK

//Engine Block
//Engine Gpios
#define LENGINE_GPIO 1
#define RENGINE_GPIO 2
//Engine frequencies.
#define LENGINE_FORWARD_FAST 17
#define LENGINE_FORWARD_SLOW 16
#define ENGINE_STOP 15
#define RENGINE_FORWARD_SLOW 14
#define RENGINE_FORWARD_FAST 13
//Opposite frequencies.
#define LENGINE_BACKWARDS_FAST RENGINE_FORWARD_FAST
#define LENGINE_BACKWARDS_SLOW RENGINE_FORWARD_SLOW
#define RENGINE_BACKWARDS_FAST LENGINE_FORWARD_FAST
#define RENGINE_BACKWARDS_SLOW LENGINE_FORWARD_SLOW

//Light Sensor Blocks
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
	//wiringPi initialization, necessary.
	wiringPiSetup();
	//PwmCreation, necesarry for each GPIO in order to send signals.
	//The wiringPi documentation says each softPwmCreate uses 0.5% of the CPU, so it should be safe
	softPwmCreate(LENGINE_GPIO,0,200);
	softPwmCreate(RENGINE_GPIO,0,200);
	//We try to fast forward
	forward_fast();

	/*
	INTRODUCE MAIN BODY OF THE THESSEUS ROVER PROGRAMMING HERE
	*/

	while(1){
	}
}
