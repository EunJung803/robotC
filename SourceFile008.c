#pragma config(Sensor, S1,     ts,             sensorEV3_Touch)
#pragma config(Sensor, S2,     gs,             sensorEV3_Gyro)
#pragma config(Sensor, S3,     cs,             sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4,     ss,             sensorEV3_Ultrasonic)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7

int color, finish_line, speed = 40, start_val = 0, distance;
int black_count = 0;
float t;

void go(int s) //go
{
   setMotorSpeed(lm, s);
   setMotorSpeed(rm, s);
}

void sound_out() { //sound playing function
	if(black_count == 0){
		playSound(soundBeepBeep);
	  sleep(700);
  }
	else {
		for(int i = 0; i <= black_count; i++)
		{
			playSound(soundBeepBeep);
			sleep(700);
	  }
	}
}

int convert(float dist) //convert function for encoding
{
	return (int)(360.0 * dist / 17.58);
}

void black_go() //counted black num -> go forward
{
	int encoder = convert(black_count * 10);
	resetMotorEncoder(lm);
	while(getMotorEncoder(lm) < encoder)
	{
		go(speed);
	}
}

void pointTurn() { //point turn function
	while(getGyroDegrees(gs) < 90) { //clockwise 90 degree point turn
		setMotorSpeed(lm, speed/2);
		setMotorSpeed(rm, -(speed/2));
	}
	sleep(500);
}

void finish(){ //end
    go(0);
    t = time1[T1];
    displayBigTextLine(1,"record = %.2fsec", t/1000);
    sleep(5000);
}

task main()
{
   while(getTouchValue(ts) == 0){ }
   while(getTouchValue(ts) == 1){ }

   while(1)
   {
     color = getColorName(cs);
     distance = getUSDistance(ss);

     go(speed);

     if(!start_val && (color == (Black||Green||Yellow||Brown)))
     {
       start_val++;
       color = getColorName(cs);

       if(finish_line == 0) {
         finish_line = color;
         clearTimer(T1);
         setLEDColor(ledGreen);
         sleep(700);
       }

       if(color == finish_line){
	       go(0);
	       finish();
	       break;
	     }
     }

     if(color == Black) {
       black_count++;
       if(black_count < 10) {
         color = getColorName(cs);
       }
     }

     if(color == finish_line || black_count == 10){
       finish();
       break;
     }

     if(color == Blue) {
       sound_out();
     }

     if(color == Red){
       go(speed/2);
       pointTurn();
       black_go();
       pointTurn();
       go(speed);
       sleep(1000);
     }

     if(distance < 50) {
       playSound(soundBeepBeep);
       sleep(700);
       go(speed/2);
       sleep(1000);

       distance = getUSDistance(ss);

       if(distance < 10) {
       go(-(speed/2));
       sleep(1000);
       int encoder = (-1) * convert(20.0);
       resetMotorEncoder(lm);
       while(getMotorEncoder(lm) > encoder)
       {
         go(-speed/2);
       }
       pointTurn();
       black_go();
       pointTurn();
       go(speed);
       sleep(1000);
       }
     }

   }

}