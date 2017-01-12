#include <wiringPi.h>
#include <softPwm.h>

int main(){
	wiringPiSetup();
	softPwmCreate(1,0,200);
	softPwmWrite(1,17);
	while(1){
	}
}