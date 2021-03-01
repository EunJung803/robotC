#pragma config(Sensor, S1, ts, sensorEV3_Touch)
#pragma config(Sensor, S2, gs, sensorEV3_Gyro, modeEV3Gyro_RateAndAngle)
#pragma config(Sensor, S3, cs, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S4, ss, sensorEV3,Ultrasonic)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm ,tmotorEV3_Large, PIDControl, encoder)

#define Black 1
#define Blue 2
#define Green 3
#define Yellow 4
#define Red 5
#define White 6
#define Brown 7


int color,finish_line, speed = 40, start_bool = 0, dist;
int blackCount = 0, dist50=0, moveBack10=0;
float t;

int convert(float dist){
    return (int)(360.0 * dist / 17.58);
}

void go(int s){
    setMotorSpeed(lm,s);
    setMotorSpeed(rm,s);
}

void pointTurn(){
    int gyroBefore, gyroGap=0,endingDegree;
    gyroBefore = getGyroDegrees(gs);

    while(gyroGap < 90){
        gyroGap = getGyroDegrees(gs) - gyroBefore;
        setMotorSpeed(lm,speed);
        setMotorSpeed(rm,-speed);
    }

    endingDegree = convert((float)blackCount*10.0);
    resetMotorEncoder(lm);
    while(getMotorEncoder(lm) < endingDegree){
        go(speed);
    }
gyroGap=0;
    gyroBefore = getGyroDegrees(gs);
    while(gyroGap < 90){
        gyroGap = getGyroDegrees(gs) - gyroBefore;
        setMotorSpeed(lm,speed);
        setMotorSpeed(rm,-speed);
    }
    go(speed*2);
    sleep(700);
    color = getColorName(cs);
}

void playingSound(){
    int num, i;
    num = (blackCount == 0) ? 1 : blackCount;
    for(i=0; i<num; i++){
        playSound(soundBeepBeep);
    }
}

task main(){
    while(getTouchValue(ts)==0){}
    while(getTouchValue(ts)==1){}

    while(1){
        color = getColorName(cs);
        dist = getUSDistance(ss);
        go(speed);
        if(!start_bool && (color == (Black||Green||Yellow||Brown))){

            start_bool++;
            clearTimer(T1);
            finish_line = color;
            setLEDColor(ledGreen);
            sleep(700);
            color = getColorName(cs);
        }

        if(color == Black){
            blackCount++;
            if(blackCount < 10){
                sleep(700);
                color = getColorName(cs);
            }
        }

        if(color == finish_line || blackCount == 10){
            t = time1[T1];
            go(0);
            displayBigTextLine(1,"record = %.2fsec", t/1000);
        }

        if(color == Blue){
            playingSound();
        }

        if(color == Red){
            speed = speed/2;
            pointTurn();
            speed = speed*2;
        }

        if(dist < 50){
            if(!dist50){
                dist50 = dist++;
                playSound(soundBeepBeep);
                speed = speed/2;
            }
            if(dist < 10){
                moveBack10 = (-1)* convert(20.0);
                resetMotorEncoder(lm);
                while(getMotorEncoder(lm) > moveBack10){
                    go(-speed);
                }
                pointTurn();
                dist50 = dist50--;
            speed = speed*2;
                dist = getUSDistance(ss);
            }
        }
    }
}
