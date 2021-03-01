#pragma config(Sensor, S1,     rts,            sensorEV3_Touch)
#pragma config(Sensor, S2,     lts,            sensorEV3_Touch)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

task main()
{
		int a;
		while(1)
		{
			a = getTouchValue(rts) + getTouchValue(lts) * 2;
			switch(a)
			{
				case 1:
						setMotorSpeed(lm, 20);
						setMotorSpeed(rm, 0);
						break;

				case 2:
						setMotorSpeed(lm, 0);
						setMotorSpeed(rm, 20);
						break;

				case 3:
						setMotorSpeed(lm, 20);
						setMotorSpeed(rm, 20);
						break;

				default:
						setMotorSpeed(lm, 0);
						setMotorSpeed(rm, 0);
						break;
			}
		}
}