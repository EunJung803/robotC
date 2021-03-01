#pragma config(Sensor, S1, c1, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define DIFF 10

int nMotorSpeedSetting = 20, vertex = 0, count = 0, row = 0, val, r = 0, c = 0, i, j, f, e;
int score = 0;
int d[7];
int S[5][5] = {{0,1,0,1,0}, {0,-1,0,-1,-1}, {0,1,0,0,0}, {0,0,0,-1,1}, {0,0,-1,1,0}};
int dt[5][5] = {{2,2,1,1,0}, {2,1,1,0,0}, {2,2,1,1,1,}, {0,0,0,0,1}, {0,0,0,1,0}};
int J[5][5] = {};

void go()
{
    val = 5;
    int temp=0;
    if(getColorName(c2) == 5){
    	temp = 5;
    	displayBigTextLine(1,"%d",temp);
    	//playSound(soundBeepBeep);
    }
    else if(getColorName(c2) == 2) {
    	temp = 2;
    	displayBigTextLine(1,"%d",temp);
    	//playSound(soundBeepBeep);
    }

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
    if (row == 1)
    {
        if (getColorName(c1) == 1)
        {
            vertex++;
        }
        else
            vertex = 0;
    }
    else if(row == 3)
    {
    	if (getColorName(c1) == 1)
        {
            vertex++;
            sleep(200);
        }
        else
            vertex = 0;
    }
    else if(row == 4)
    {
    	if (getColorName(c1) == 1)
        {
            vertex++;
            sleep(200);
        }
        else
            vertex = 0;
    }
    else	//row == 2
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
        setMotorSpeed(lm, -nMotorSpeedSetting * 4 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 4 / 10);
    }
    while (getColorName(c3) > 4)
    {
        setMotorSpeed(lm, -nMotorSpeedSetting * 4 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 4 / 10);
    }
    while (getColorName(c2) > 4)
    {
        setMotorSpeed(lm, nMotorSpeedSetting * 4 / 10);
        setMotorSpeed(rm, -nMotorSpeedSetting * 4 / 10);
    }
    sleep(180);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void turnRight()
{
    setMotorSpeed(lm, 25);
    setMotorSpeed(rm, 25);
    sleep(250);
    while (getColorName(c3) > 4)
    {
        setMotorSpeed(lm, nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, -nMotorSpeedSetting * 6 / 10);
        sleep(10);
    }
    while (getColorName(c2) > 4)
    {
        setMotorSpeed(lm, nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, -nMotorSpeedSetting * 6 / 10);
    }
    sleep(80);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void goUp()
{
    r--;
    row++;
    turnRight();
    count = 0;
    while (true)
    {
        go();
        if (count == 1)
        {
            sleep(300);
            turnLeft();
            break;
        }
    }
}

void goLeft()
{
    c--;
    count = 0;
    while (true)
    {
        go();
        if (count == 1)
        {
            setMotorSpeed(lm, 30);
            setMotorSpeed(rm, 30);
            sleep(400);
            break;
        }
    }
}

void stopMotor()
{
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
}
/*
void completeSearch()
{
    while (true)
    {
        go();
        if (count == 4)
        { // if robot is end of column
            if (row == 4)
            { // all grid scanning complete
                return;
            }
            if (row % 2 == 0)
            { // move backward
                setMotorSpeed(lm, 40);
                setMotorSpeed(rm, 35);
                for (int i = 0; i < 4; i++)
                { //prevent patch unrecognizable error during rotation
                    if (getColorName(c2) == 5)
                    { // scan Red patch

                        if (row % 2 == 0)
                        { // same as go() Logic
                            S[row][count] = 1;

                        }
                        else
                        {
                            S[row][4 - count] = 1;

                        }
                        //playTone(440, 20);
                        sleep(80);
                    }
                    else if (getColorName(c2) == 2)
                    { //scan Blue patch

                        if (row % 2 == 0)
                        {
                            S[row][count] = -1;

                        }
                        else
                        {
                            S[row][4 - count] = -1;

                        }
                        //playTone(440, 20);
                        sleep(80);
                    }
                    else
                    {
                        sleep(90);
                    }
                }
                turnRight();
            }
            else
            { // if robot is middle of line
            		setMotorSpeed(lm, 40);
                setMotorSpeed(rm, 35);
                for (int i = 0; i < 3; i++)
                { // Same Logic
                    if (getColorName(c2) == 5)
                    {

                        if (row % 2 == 0)
                        {
                            S[row][count] = 1;

                        }
                        else
                        {
                            S[row][4 - count] = 1;

                        }
                        //playTone(440, 20);
                        sleep(80);
                    }
                    else if (getColorName(c2) == 2)
                    {

                        if (row % 2 == 0)
                        {
                            S[row][count] = -1;

                        }
                        else
                        {
                            S[row][4 - count] = -1;

                        }
                        //playTone(440, 20);
                        sleep(80);
                    }
                    else
                    {
                        sleep(90);
                    }
                }
                turnLeft();
            }
            if (row % 2 == 0)
            {
                while (getColorName(c3) == 6)
                { // move next column(black col line)
                    go();
                }
                setMotorSpeed(lm, 35);
                setMotorSpeed(rm, 30);
                sleep(400);
                turnRight(); // turn agian
            }
            else
            {
                while (getColorName(c1) == 6)
                {
                    go();
                }
                setMotorSpeed(lm, 30);
                setMotorSpeed(rm, 35);
                sleep(400);
                turnLeft();
            }
            row++;
            count = 0; // reset scaning, position
            setMotorSpeed(lm, -20);
            setMotorSpeed(rm, -20);
            sleep(200);
        }
    }
}*/

void printMap()
{
		char map[6][6];

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (S[i][j] == 0)
            {
                map[i][j] = '+';
            }
            else if (S[i][j] == 1)
            {
                map[i][j] = 'O';
            }
            else if (S[i][j] == -1)
            {
                map[i][j] = 'X';
            }
        }
    }
    for(int i = 0; i < 5; i++)
    	for(int j = 0; j < 5; j++)
    		displayStringAt( (i+j)*10, 100-(i+1)*10, "%c", map[i][j] );
    sleep(5000);
}




task main()
{
    while (getButtonPress(1) == 0)
    {
        sleep(10);
    }

    /*
    completeSearch();
    setMotorSpeed(lm, 20);
    setMotorSpeed(rm, 20);
    sleep(1000);
    turnRight();
    turnRight();
    sleep(1000);
		*/
    printMap();
    sleep(5000);

    for(int i = 0; i < 5; i++)
    	for(int j = 0; j < 5; j++)
    		displayStringAt( (i+j)*10, 100-(i+1)*10, "%d", dt[i][j] );
    sleep(5000);

    count = row = 0;
    /*
    for (f = 4; f >= 0; f--)
    {
        for (e = 4; e >= 0; e--)
        {

            if (e == 4 && f == 4)
            {
                dt[e][f] = S[e][f];
            }
            else if (f == 4)
            {
                dt[e][f] = dt[e + 1][f] + S[e][f];
            }

            else
            {
                dt[e][f] = -10;
                for (i = 0; i <= 4; i++)
                {
                    d[i] = dt[i][f + 1];
                    if (i > e)
                    {
                        for (j = i; j >= e; j--)
                            d[i] += S[j][f];
                    }
                    else if (i == e)
                    {
                        d[i] += S[i][f];
                    }

                    if (dt[e][f] < d[i])
                    {
                        dt[e][f] = d[i];
                        J[e][f] = i;
                    }
                }
            }
        }
    }*/

    row = 0;
    r = c = 4;
    d[0] = 0;
    for (i = 0; i <= 4; i++)
    {
        d[i + 1] = J[d[i]][i];
    }

    // we made
    /*
    for (c = 4; c <= 0; c--)
    {
        if (S[r][c] == 1)
        {
            score++;
        }
        else if (S[r][c] == -1)
        {
            score--;
        }

        while (r != d[c])
        {
            goUp();
            r--;
            if (S[r][c] == 1)
            {
                score++;
            }
            else if (S[r][c] == -1)
            {
                score--;
            }
        }
        goLeft();
    }*/

    // original code

    for (i = 4; i > 0; i--)
    {
        if (r > d[i])
        {
            while (r > d[i])
            {
                goUp();
                if (S[r][c] == 1)
				        {
				            score++;
				        }
				        else if (S[r][c] == -1)
				        {
				            score--;
				        }
            }
            goLeft();
        }
        else if (r == d[i])
        {
            goLeft();
            if (S[r][c] == 1)
		        {
		            score++;
		        }
		        else if (S[r][c] == -1)
		        {
		            score--;
		        }
		    }
    }

    playTone(240, 20);
    sleep(200);
    stopMotor();
    while (getButtonPress(1) == 0)
    {
        sleep(10);
    }
    displayBigTextLine(1, "final score is %d", score);
    sleep(5000);
}
