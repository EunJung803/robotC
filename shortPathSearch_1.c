#pragma config(Sensor,S1,c1,sensorEV3_Color)
#pragma config(Sensor,S2,c2,sensorEV3_Color)
#pragma config(Sensor,S3,c3,sensorEV3_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define DIFF 10

int nMotorSpeedSetting =33, vertex=0, count=0, row = 0, val;

void go(){
    val = 7;

    if(getColorName(c2) == 1){
        setMotorSpeed(lm, nMotorSpeedSetting - val);
        setMotorSpeed(rm, nMotorSpeedSetting + val);
    }
    else{
        setMotorSpeed(lm, nMotorSpeedSetting+ val);
        setMotorSpeed(rm, nMotorSpeedSetting- val);
    }
    if(row % 2 == 1 || row == 4){
    	if(getColorName(c1) == 1) {
        	vertex++;
      }
      else vertex = 0;
    }
    else{
    	if(getColorName(c3) == 1) {
        	vertex++;
      }
      else vertex = 0;
    }
    if(vertex == 1){
        count++;
        playSound(soundBeepBeep);
    }
}

void turnLeft(){
    setMotorSpeed(lm, 30);
    setMotorSpeed(rm, 30);
    sleep(150);
    while(getColorName(c1) > 4){
        setMotorSpeed(lm, -nMotorSpeedSetting*6/10);
        setMotorSpeed(rm, nMotorSpeedSetting*6/10);
        sleep(10);
    }
    while(getColorName(c2) > 4){
        setMotorSpeed(lm, -nMotorSpeedSetting*6/10);
        setMotorSpeed(rm, nMotorSpeedSetting*6/10);
    }
    sleep(150);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void turnRight(){
    setMotorSpeed(lm, 25);
    setMotorSpeed(rm, 25);
    sleep(130);
    while(getColorName(c3) > 4){
        setMotorSpeed(lm, nMotorSpeedSetting*6/10);
        setMotorSpeed(rm, -nMotorSpeedSetting*6/10);
        sleep(10);
    }
    while(getColorName(c2) > 4){
        setMotorSpeed(lm, nMotorSpeedSetting*6/10);
        setMotorSpeed(rm, -nMotorSpeedSetting*6/10);
    }
    sleep(80);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void stopMotor(){
    setMotorSpeed(lm,0);
    setMotorSpeed(rm,0);
}


task main()
{
    while(getButtonPress(1) == 0){sleep(10);}
    while(true)
    {
    	go();
    	if(count == 5)
    	{
    		if(row == 4) break;
    		if(row % 2 == 0)
    		{
    			setMotorSpeed(lm, 35);
    			setMotorSpeed(rm, 30);
    			sleep(400);
    			turnRight();

    		}
    		else
    		{
    			sleep(300);
    			turnLeft();
    		}
    		if(row % 2 == 0)
    		{
    			while(getColorName(c3) == 6) go();
    			setMotorSpeed(lm, 35);
    			setMotorSpeed(rm, 30);
    			sleep(400);
    			turnRight();
    		}
    		else
    		{
    			while(getColorName(c1) == 6) go();
    			setMotorSpeed(lm, 30);
    			setMotorSpeed(rm, 35);
    			sleep(400);
    			turnLeft();
    		}
    		row++;
    		count = 0;
    	}
    }
    //playTone(240, 20);
    sleep(200);
    stopMotor();
    while(getButtonPress(1) == 0){sleep(10);}

}
