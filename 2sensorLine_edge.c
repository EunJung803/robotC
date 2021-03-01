#pragma config(Sensor, S1,     c1,             sensorEV3_Color)
#pragma config(Sensor, S2,     c2,             sensorEV3_Color)
#pragma config(Sensor, S3,     c3,             sensorEV3_Color)
#pragma config(Motor,  motorB,          lm,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rm,            tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

int calcBound2()
{
   int bound;
   int black = 0;
   int white = 0;

   for(int i=0 ; i < 5; i++)
   {
      black += getColorReflected(c1);
      black += getColorReflected(c3);
      sleep(10);
   }

   setMotorSpeed(lm, 10);
   setMotorSpeed(rm, 10);
   sleep(500);
   setMotorSpeed(lm, 0);
   setMotorSpeed(rm, 0);

   for(int i=0 ; i < 5; i++)
   {
      white += getColorReflected(c1);
      white += getColorReflected(c3);
      sleep(10);
   }

   bound = (white/10 + black/10)/2;

   return bound;
}

void move2cross(int gray)
{
   while(1)
   {
      int left = getColorReflected(c1);
      int right = getColorReflected(c3);

      if(left>=gray && right>=gray)
      {
         setMotorSpeed(lm, 20);
         setMotorSpeed(rm, 20);
      }
      else if(left>=gray && right<gray)
      {
         setMotorSpeed(lm, 30);
         setMotorSpeed(rm, -10);
      }
      else if(left<gray && right>=gray)
      {
         setMotorSpeed(lm, -10);
         setMotorSpeed(rm, 30);
      }
      else
      {
         setMotorSpeed(lm, 0);
         setMotorSpeed(rm, 0);
         break;
      }
   }
}

void align(int gray)
{
	int left = getColorReflected(c1);
	int right = getColorReflected(c3);

	while(left < gray && right < gray)
	{
		setMotorSpeed(lm, 5);
		setMotorSpeed(rm, 5);
		left = getColorReflected(c1);
		right = getColorReflected(c3);
	}

	while(left <= gray || right <= gray)
	{
		if(left <= gray)
		{
			setMotorSpeed(lm, 5);
			setMotorSpeed(rm, 0);
		}
		else
		{
			setMotorSpeed(lm, 0);
			setMotorSpeed(rm, 5);
		}
		left = getColorReflected(c1);
		right = getColorReflected(c3);
	}
	setMotorSpeed(lm, 0);
	setMotorSpeed(rm, 0);
	sleep(1000);
}

task main()
{
   int gray = calcBound2();
   move2cross(gray);
   align(gray);
   move2cross(gray);

   /*
   int cnt = 0;
   while(1)
   {
      move2cross(gray);
      cnt++;
      if(cnt == 4)
      {
      	 displayBigTextLine(1, "%d", cnt);
      	 sleep(5000);
         return;
      }
      else
      {
         setMotorSpeed(lm, 30);
         setMotorSpeed(rm, 30);
         sleep(200);
      }
   }
   displayBigTextLine(1, "%d", cnt);
   sleep(5000);
   */
}
