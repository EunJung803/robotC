#pragma config(Sensor, S1, c1, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define DIFF 10

int nMotorSpeedSetting = 10, vertex = 0, count = 0, row = 0, val, r = 0, c = 0, i, j, f, e;
int score = 0;
int S[6][6], dt[6][6], d[6], J[6][6];

void go()
{
    val = 5;

    if (getColorName(c2) == 1)
    {
        setMotorSpeed(lm, nMotorSpeedSetting - val);
        setMotorSpeed(rm, nMotorSpeedSetting + val);
    }
    else
    {
        setMotorSpeed(lm, nMotorSpeedSetting + val);
        setMotorSpeed(rm, nMotorSpeedSetting - val);
    }
    if (row % 2 == 1 || row == 4)
    {
        if (getColorName(c1) == 1)
        {
            vertex++;
        }
        else
            vertex = 0;
    }
    else
    {
        if (getColorName(c3) == 1)
        {
            vertex++;
        }
        else
            vertex = 0;
    }
    if (vertex == 1)
    {
        count++;
        playSound(soundBeepBeep);
    }
}
void turnLeft()
{
    setMotorSpeed(lm, 25);
    setMotorSpeed(rm, 25);
    sleep(180);
    while (getColorName(c1) > 4)
    {
        setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
        sleep(10);
    }
    while (getColorName(c2) > 4)
    {
        setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
    }
    sleep(180);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}
task main()
{

	    while (getButtonPress(1) == 0)
    {
        sleep(10);
    }
    while(true){
    		go();
    		if(getColorName(c1) < 4) {
    			turnLeft;
    		}
    }
}
