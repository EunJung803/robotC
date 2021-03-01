#pragma config(Sensor, S1, c1, sensorEV3_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm ,tmotorEV3_Large, PIDControl, encoder)

#define THRESHOLD 40

task main(){
    int v = 30, error = 0, sum = 0, diff = 0, last_error = 0;
    float Kp = 1.8, Kd = 100, Ki = Kp * Kp / (4*Kd);

    while(1){
        sleep(1);
        error = getColorReflected(c1) - getColorReflected(c3);
        sum = sum+error;
        diff = error - last_error;
        setMotorSpeed(lm,v+(error * Kp + sum * Ki + diff * Kd));
        setMotorSpeed(rm,v-(error * Kp + sum * Ki + diff * Kd));
        last_error = error;
    }
}
