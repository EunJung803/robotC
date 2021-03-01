#pragma config(Sensor, S1, c1, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S2, c2, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Sensor, S3, c3, sensorEV3_Color, modeEV3Color_Color)
#pragma config(Motor, motorB, lm, tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor, motorC, rm, tmotorEV3_Large, PIDControl, encoder)

#define DIFF 10

typedef struct
{
    int x; //row
    int y; //column
} redPatch;

int nMotorSpeedSetting = 35, vertex = 0, count = 0, row = 0, val;
int score = 0;
int S[6][6], road[6][6];
redPatch redpatches[6];
int target_y = 4, target_x = 4, nowxpos = 4, nowypos = 4, robotx = 4, roboty = 4, nowDirect = 1;

void go(){
    val = 6;
    if (getColorName(c2) == 5){ //Sensoring Red in scanning
        if (row % 2 == 0){                      // scanning Left to Right
            S[row][count] = 1; //check the Red Patch in array
        }
        else{ // scan opposite Direction
            S[row][4 - count] = 1;
        }
        playTone(440, 20);
        sleep(100);
    }
    else if (getColorName(c2) == 2)
    { //Sensoring blue in scanning
        if (row % 2 == 0){
            S[row][count] = -1;
        }
        else{
            S[row][4 - count] = -1;
        }
        playTone(440, 20);
        sleep(100);
    }
    if (getColorName(c2) == 1){ // //Sensoring black in scanning
        setMotorSpeed(lm, nMotorSpeedSetting - val);
        setMotorSpeed(rm, nMotorSpeedSetting + val);
    }
    else{
        setMotorSpeed(lm, nMotorSpeedSetting + val);
        setMotorSpeed(rm, nMotorSpeedSetting - val);
    }
    if (getColorName(c1) == 4 || getColorName(c3) == 4){ // counting column of robot Position
        vertex++;
    }
    else{
        vertex = 0;
    }
    if (vertex == 1){
        count++;
    }
}

void turnLeft(){
    setMotorSpeed(lm, 30);
    setMotorSpeed(rm, 30); // move front to match the line and robot's center body
    sleep(150);
    while (getColorName(c1) > 4){ // wait for the left sensor pass the line
        setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
        sleep(10);
    }
    while (getColorName(c2) > 4){ // wait for the center sensor match to the line side
        setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
        sleep(5);
    }
    sleep(150);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void turnRight(){
    setMotorSpeed(lm, 25);
    setMotorSpeed(rm, 25); // move front to match the line and robot's center body
    sleep(130);
    while (getColorName(c3) > 4){ // wait for the right sensor pass the line
        setMotorSpeed(lm, nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, -nMotorSpeedSetting * 6 / 10);
        sleep(10);
    }
    while (getColorName(c2) > 4){ // wait for the center sensor match to the line side
        setMotorSpeed(lm, nMotorSpeedSetting * 6 / 10);
        setMotorSpeed(rm, -nMotorSpeedSetting * 6 / 10);
        sleep(5);
    }
    sleep(80);
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
    sleep(200);
    count = 0;
}

void turnBack(){
	setMotorSpeed(lm, 30);
  setMotorSpeed(rm, 30); // move front to match the line and robot's center body
  sleep(150);
  while (getColorName(c1) > 4){ // wait for the left sensor pass the line
      setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
      sleep(5);
  }
  while (getColorName(c2) > 4){ // wait for the center sensor match to the line side
      setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
      sleep(5);
  }
  while (getColorName(c1) > 4){ // wait for the left sensor pass the line
      setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
      sleep(5);
  }
  while (getColorName(c2) > 4){ // wait for the center sensor match to the line side
      setMotorSpeed(lm, -nMotorSpeedSetting * 6 / 10);
      setMotorSpeed(rm, nMotorSpeedSetting * 6 / 10);
      sleep(5);
  }
  sleep(150);
  setMotorSpeed(lm, 0);
  setMotorSpeed(rm, 0);
  sleep(200);
  count = 0;
}

void stopMotor(){
    setMotorSpeed(lm, 0);
    setMotorSpeed(rm, 0);
}

void goOneBlock(){
	while(getColorName(c1) != 1 || getColorName(c3) != 1){
		if(getColorName(c1) != 1){
			setMotorSpeed(lm, nMotorSpeedSetting);
		}
		if(getColorName(c1) != 1){
			setMotorSpeed(rm, nMotorSpeedSetting);
		}
		sleep(5);
	}
	stopMotor();
	sleep(1000);
}

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
                sleep(400);	//200
                turnRight2(); // turn agian
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
                turnLeft2();
            }
            row++;
            count = 0; // reset scaning, position
            setMotorSpeed(lm, -20);
            setMotorSpeed(rm, -20);
            sleep(200);
        }
    }
}

void printMap(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (S[i][j] == 0){
                displayStringAt(i, j, "+");
            }
            else if (S[i][j] == 1){
                displayStringAt(i, j, "O");
            }
            else if (S[i][j] == -1){
                displayStringAt(i, j, "X");
            }
        }
    }
    sleep(1500);
}

void redpatch_list(){
    int index = 0;
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            if (S[i][j] == 1){
                redpatches[index].x = j;
                redpatches[index].y = i;
                index++;
            }
        }
    }
    redpatches[index].x = 0;
    redpatches[index].y = 0;
}

int go_target(int x, int y, int rc){ //0: Row first 1: Col first
    if (x == target_x && y == target_y){
        road[y][x] = 1;
        return 5;
    }
    if (S[y][x] == -1 || S[y][x] == 3){ // the point is blue patch or arrive point
        road[y][x] = 0;
        return 0;
    }
    if (rc){ //check Col first{
        if (x != target_x){ // not Arrive yet
            int oneXStep = go_target(x + ((target_x - x) / abs(target_x - x)), y, 1);
            if (oneXStep == 0){ // meet blue patch
                road[y][x] = 0;
                return 0;
            }
            else{
                road[y][x] = 1;
                return 1;
            }
        }
        else if (y != target_y){ // arrive
            int oneYStep = go_target(x, y + ((target_y - y) / abs(target_y - y)), 1);
            if (oneYStep == 0){ // meet blue patch
                road[y][x] = 0;
                return 0;
            }
            else{
                road[y][x] = 1;
                return 1;
            }
        }
    }
    else{ //check Row first{
        if (y != target_y){ // not Arrive yet
            int oneYStep = go_target(x, y + ((target_y - y) / abs(target_y - y)), 0);
            if (oneYStep == 0){ // meet blue patch
                road[y][x] = 0;
                return 0;
            }
            else{
                road[y][x] = 1;
                return 1;
            }
        }
        else if (x != target_x){ // arrive
            int oneXStep = go_target(x + ((target_x - x) / abs(target_x - x)), y, 0);
            if (oneXStep == 0){ // meet blue patch
                road[y][x] = 0;
                return 0;
            }
            else{
                road[y][x] = 1;
                return 1;
            }
        }
		}
		return 0;
}

void set_target(int now_x, int now_y){
    int distance = 100, dist, index = 0;
    for (int i = 0; i < 5; i++){
        dist = abs(redpatches[i].x - now_x) + abs(redpatches[i].y - now_y);
        index = (dist > distance) ? index : i;
        distance = (dist > distance) ? distance : dist;
    }
    target_y = redpatches[index].y;
    target_x = redpatches[index].x;
    redpatches[index].x = 100;
    redpatches[index].y = 100;
    if (target_x == 100){
        target_y = 0;
        target_x = 0;
    }
    else{
    	score = score+5;
    }
}

void clearArry(){
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 5; j++){
            road[i][j] = 0;
        }
    }
}

void avoidBluePatch(){
    while (go_target(nowypos, nowxpos, 0) == 0 && go_target(nowypos, nowxpos, 1) == 0){
        road[nowxpos][nowypos] = 1;
        if (S[nowxpos][++nowypos] >= 0){}
        else if (S[++nowxpos][nowypos] >= 0){}
        else if (S[nowxpos][--nowypos] >= 0){}
        else if (S[--nowxpos][nowypos] >= 0){}
        road[nowxpos][nowypos] = 1;
    }
}

void composeDirection(int new_direct)
{
    if (abs(nowDirect - new_direct) == 2){
        turnBack();
    }
    else if (nowDirect - new_direct == -1 || nowDirect - new_direct == 3){
        turnRight();
    }
    else if (nowDirect - new_direct == 1 || nowDirect - new_direct == -3){
        turnLeft();
    }
    nowDirect = new_direct;
    goOneBlock();
    score = score-1;
}

void moveRobot()
{
    int sum = 0;
    while (true){
        road[roboty][robotx] = 0;
        if (road[roboty - 1][robotx] == 1 && roboty >= 0){
            composeDirection(1);
            roboty--;
            sum++;
        }
        else if (road[roboty][robotx + 1] == 1 && robotx < 5){
            composeDirection(2);
            robotx++;
            sum++;
        }
        else if (road[roboty + 1][robotx] == 1 && roboty < 5){
            composeDirection(3);
            roboty++;
            sum++;
        }
        else if (road[roboty][robotx - 1] == 1 && robotx >= 0){
            composeDirection(4);
            robotx--;
            sum++;
        }
        if (sum == 0){
            break;
        }
        else{
            sum = 0;
        }
    }
}

void getroad()
{
    int sideUp, Upside;
    for (int i = 0; i < 6; i++){
        set_target(target_x, target_y);
        sideUp = go_target(nowypos, nowxpos, 0);
        if (!sideUp){
            Upside = go_target(nowypos, nowxpos, 1);
        }
        if (!sideUp && !Upside){
            avoidBluePatch();
        }
        if (S[nowxpos][nowypos] == 1){
            road[nowxpos][nowypos] = 1;
        }
        else{
            road[nowxpos][nowypos] = 1;
        }
        moveRobot();
        nowxpos = target_y;
        nowypos = target_x;
        clearArry();
    }
}

task main(){
	while( getButtonPress(1) == 0){sleep(10);}
	completeSearch();
	printMap();
	setMotorSpeed(lm,20);
	setMotorSpeed(rm,20);
	sleep(1000);
	setMotorSpeed(lm,20);
	setMotorSpeed(rm,-20);
	sleep(1650);
	while( getButtonPress(1) == 0){sleep(10);}
	redpatch_list();
	getroad();
	while (getButtonPress(1) == 0)
  {
      sleep(10);
  }
   displayBigTextLine(1, "final score is %d", score);
    sleep(5000);
}
