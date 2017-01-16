/*
Created by Pablo Mac-Veigh and Javier Sésé, for our Robotics class of 2016-2017.

This project uses the standard MIT license.

Using WiringPi, we're enabling a basic robot to follow black lines or to find it's way out of maze.
For the maze, we'll use the left hand (or right hand) algorithm, wich will be decided upon watching the maze.
For the black line following, we still have to work on it

*/

#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <softPwm.h>
#include <stdio.h>
#include <time.h>

//CONSTANT DECLARATION BLOCK
//TODO: UPDATE GPIO PIN NUMBERS

//Engine Block
//Engine Gpios
#define LENGINE_GPIO 4
#define RENGINE_GPIO 1
//Engine frequencies.
#define LENGINE_FORWARD_FAST 17
#define ENGINE_STOP 15
#define RENGINE_FORWARD_FAST 13
//Opposite frequencies.
#define LENGINE_BACKWARDS_FAST 13
#define RENGINE_BACKWARDS_FAST 17

//Light Sensor Block
#define LS_GPIO 0
#define RS_GPIO 2

//Proximity Sensor Block
#define SENSOR_CENTER 0
#define SENSOR_SIDE 1
#define SENSOR_SPICHANNEL 0
#define SENSOR_CHANNELCONFIG 8

//Sensor dinstances Block
#define SENSOR_ACCEPTABLE_MIN 350
#define SENSOR_ACCEPTABLE_MAX 450
#define SENSOR_CENTER_TURN_DISTANCE 300
#define SENSOR_CENTER_COLLISION_DISTANCE 650

static int myFd;

void loadSPIDriver(){
	system("gpio load spi");
}

void spiSetup(int spiChannel){
	myFd=wiringPiSPISetup (spiChannel, 1000000);
}

void waitFor (unsigned int seconds){
	unsigned int retTime = time(0) + seconds;
	while(time(0) < retTime);
}

int myAnalogRead(int spiChannel,int channelConfig,int analogChannel){
	if (analogChannel<0 || analogChannel>7){
		return -1;
	}
	unsigned char buffer[3] = {1};
	buffer[1] = (channelConfig+analogChannel) <<4;
	wiringPiSPIDataRW(spiChannel, buffer, 3);
	return ( (buffer[1] & 3 ) <<8)+buffer[2];
}

int readProximity(int i){
	return myAnalogRead(SENSOR_SPICHANNEL,SENSOR_CHANNELCONFIG,i);
}

void forward_fast(){
//	printf("Going Forward Fast.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST);
}

void backwards_fast(){
//	printf("Going Backwards Fast.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_FAST);
}

void hard_stop(){
//	printf("Hard Stopping.\n");
	softPwmWrite(LENGINE_GPIO,ENGINE_STOP);
	softPwmWrite(RENGINE_GPIO,ENGINE_STOP);
}

void hard_left(){
//	printf("Doing Hard Left. \n");
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST);
}

void hard_right(){
//	printf("Doing Hard Right. \n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_FAST);
}

void move_right(){
//	printf("Moving Right.\n");
	softPwmWrite(LENGINE_GPIO,LENGINE_FORWARD_FAST);
	softPwmWrite(RENGINE_GPIO,ENGINE_STOP);
}

void move_left(){
//	printf("Moving Left.\n");
	softPwmWrite(LENGINE_GPIO,ENGINE_STOP);
	softPwmWrite(RENGINE_GPIO,RENGINE_FORWARD_FAST);
}

void backwards_left(){
	softPwmWrite(LENGINE_GPIO,LENGINE_BACKWARDS_FAST);
	softPwmWrite(RENGINE_GPIO,ENGINE_STOP);
}

void backwards_right(){
	softPwmWrite(LENGINE_GPIO,ENGINE_STOP);
	softPwmWrite(RENGINE_GPIO,RENGINE_BACKWARDS_FAST);
}


/* Line Following Routine 

It tries to go forward until one of the two sensors, placed at left and right in the front,
decets that a black line has been crossed. At this point, Thesseus will turn, stopping the wheel
on the side of the sensor that crossed it.
This is really rudimentary and should be worked on.

*/
void followLine(){
	int left = 0;
	int right = 0;
	while ((digitalRead(LS_GPIO))&&(digitalRead(RS_GPIO))){
		forward_fast();
	}
	while (!digitalRead(LS_GPIO)){
		move_left();
		printf("SENSOR IZQUIERO PISA NEGRO \n");
		if (left==0){
			left=1;
		}
	}
	if(left==1){
		//waitFor(1);
	} 
	while (!digitalRead(RS_GPIO)){
		move_right();
		printf("SENSOR DERECHO PISA NEGRO \n");
		if (right==0){
			right=1;
		}
	}
	if (right==1){
		//waitFor(1);
	}
	left=0;
	right=0;
	followLine();

}

//We will try to solve a maze using the left hand algorithm.

//This robot doesn't collide with walls on it's left and always tries to stay at the same distante from it.
void solveMaze(){
	//If we are inside the acceptable limits from the wall, we advance in a straight line.
	while (SENSOR_ACCEPTABLE_MAX>readProximity(SENSOR_SIDE)&&readProximity(SENSOR_SIDE)>SENSOR_ACCEPTABLE_MIN){
		forward_fast();


		//TODO :  if (sensor_center)>sensor_center_turn_distance) while (sensor_center)>sensor_center_turn_distance+100)

		//If we detect a wall in front of us (the range of detection is smaller than the robot, so we wouldn't really miss any left hand turns
		while (readProximity(SENSOR_CENTER)>SENSOR_CENTER_TURN_DISTANCE&&(readProximity(SENSOR_CENTER)<SENSOR_CENTER_COLLISION_DISTANCE)){
			move_right();
		}
		//If we find ourselves too close to a wall, we go backwards in the opposite direction.
		while(readProximity(SENSOR_CENTER)>SENSOR_CENTER_COLLISION_DISTANCE){
			backwards_left();
		}
	}
	//If we are going straight, and we leave the acceptable limits from the right
	while ((SENSOR_ACCEPTABLE_MAX>readProximity(SENSOR_SIDE)&&readProximity(SENSOR_SIDE)<SENSOR_ACCEPTABLE_MIN)){
		move_left();
		//If we find an object in our path while correcting we turn to the right
		if (readProximity(SENSOR_CENTER)>SENSOR_CENTER_TURN_DISTANCE&&(readProximity(SENSOR_CENTER)<SENSOR_CENTER_COLLISION_DISTANCE)){
			move_right();
		}
		//Same as  before, we go backwards in the oposite direction
		while(readProximity(SENSOR_CENTER)>SENSOR_CENTER_COLLISION_DISTANCE){
			backwards_left();
		}
	}
	//If we leave the acceptable limits from the left
	while (SENSOR_ACCEPTABLE_MAX< readProximity(SENSOR_SIDE)&&readProximity(SENSOR_SIDE)>SENSOR_ACCEPTABLE_MIN){
		move_right();
		while(readProximity(SENSOR_CENTER)>SENSOR_CENTER_COLLISION_DISTANCE){
			backwards_left();
		}
	}
	//Recursive call to keep the engines going.
	solveMaze();

}

int main(){
	//wiringPi initialization, necessary.
	wiringPiSetup();
	//SPI driver, for the distance sensors.
	loadSPIDriver();
	//Yet another call for the spi
	spiSetup(0);
	//PwmCreation, necesarry for each GPIO in order to send signals.
	//The wiringPi documentation says each softPwmCreate uses 0.5% of the CPU, so it should be safe
	softPwmCreate(LENGINE_GPIO,0,200);
	softPwmCreate(RENGINE_GPIO,0,200);
	//followLine()
	solveMaze();
}
