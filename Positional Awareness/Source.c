
typedef struct
{
	int hval;
	int xval;
	int yval;
}TPositionRecord;
TPositionRecord initial;

//	initial.xval=0;
//initial.yval=0;
task main()
{
MoveToPosition(40,25,127,127,20,0);

}



	//Solve For the Hyp

void MoveToPosition(int Xf, int Yf, int speed,int MoveSpeed, int time, int adir_overide)
{
	int fullRotation = (360); //12.56 inches in distance with 4 inch wheel
	int oneFoot = (.955*fullRotation); //oneFoot = 12 inches or 343.95
	int tile = 2 * oneFoot;


	HypDist = sqrt(pow((Xf - initial.xval), 2) + pow((Yf - initial.yval), 2));
	if (Xf - initial.xval > 0 && Yf - initial.yval > 0) { Angle = acos((Xf - initial.xval) / HypDist); }
	else if (Xf - initial.xval < 0 && Yf - initial.yval > 0) { Angle = 180 - acos((Xf - initial.xval) / HypDist); }
	else if (Xf - initial.xval < 0 && Yf - initial.yval < 0) { Angle = 180 + acos((Xf - initial.xval) / HypDist); }
	else if (Xf - initial.xval > 0 && Yf - initial.yval < 0) { Angle = 360 - acos((Xf - initial.xval) / HypDist); }
	else if (Xf - initial.xval > 0 && Yf - initial.yval == 0) { Angle = 0; }
	else if (Xf - initial.xval < 0 && Yf - initial.yval == 0) { Angle = 180; }
	else if (Xf - initial.xval == 0 && Yf - initial.yval > 0) { Angle = 90; }
	else if (Xf - initial.xval == 0 && Yf - initial.yval < 0) { Angle = 270; }
	else {}

	//Solve For The Angle
	/*if (Angle - SensorValue[gyro] > 0) {adir = 1;}
	else if (Angle - SensorValue[gyro] < 0) { adir = -1; }
	else {}*/

	int deg = Angle - SensorValue[gyro];

	//Turn
	int adir;
		if (deg > 0) { adir = 1; }
		else if (deg < 0) { adir = -1; }
		else {}


		if (adir_overide>0){adir=adir*-1}	//Overider that allows robot to reive backwards (to be tested)
		else {}

		while ((abs(SensorValue[in7]) / 10) < abs(deg))
		{
			if ((abs(SensorValue[in7]) / 10) < (abs(deg) - 30))
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			else if ((abs(SensorValue[in7]) / 10) < (abs(deg) - 15))
			{
				motor[LM] = adir*speed*se.mult / 2;
				motor[L1] = adir*speed*se.mult / 2;
				motor[RM] = -adir*speed*se.mult / 2;
				motor[R1] = -adir*speed*se.mult / 2;
			}
			else
			{
				motor[LM] = adir*speed*se.mult / 3;
				motor[L1] = adir*speed*se.mult / 3;
				motor[RM] = -adir*speed*se.mult / 3;
				motor[R1] = -adir*speed*se.mult / 3;
			}
		}
		wait1Msec(time);
		while (abs(SensorValue[in7]) / 10 > abs(deg))
		{
			motor[LM] = -adir*speed*se.mult / 2;
			motor[L1] = -adir*speed*se.mult / 2;
			motor[RM] = adir*speed*se.mult / 2;
			motor[R1] = adir*speed*se.mult / 2;
		}
		wait1Msec(time);
		while (abs(SensorValue[in7]) / 10 < abs(deg))
		{
			motor[LM] = adir*speed*se.mult / 3;
			motor[L1] = adir*speed*se.mult / 3;
			motor[RM] = -adir*speed*se.mult / 3;
			motor[R1] = -adir*speed*se.mult / 3;
		}
		//motor[LM] = -adir*10*se.mult;
		//		motor[L1] = -adir*10*se.mult;
		//		motor[RM] = adir*10*se.mult;
		//		motor[R1] = adir*10*se.mult;
		//wait1Msec(100);
		motor[LM] = 0;
		motor[L1] = 0;
		motor[RM] = 0;
		motor[R1] = 0;


//MOVE
		speed = MoveSpeed;

		int cout = tile*HypeDist;			//Determines the encoder count of the travel distance
		if (adir_overide > 0) { dir = -1; }	//sets direction of robot movement based on overide
		else { dir = 1; }
		SensorValue[Renc] = 0;
		SensorValue[Lenc] = 0;
		if (dir == 1)
		{
			while (abs(SensorValue[Lenc])<count)
			{
				if (abs(SensorValue[Lenc])>abs(SensorValue[Renc]) + 5)
				{
					motor[LM] = speed*se.mult*.8;
					motor[L1] = speed*se.mult*.8;
					motor[RM] = speed*se.mult;
					motor[R1] = speed*se.mult;
				}
				else if (abs(SensorValue[Lenc])<abs(SensorValue[Renc]) - 5)
				{
					motor[LM] = speed*se.mult;
					motor[L1] = speed*se.mult;
					motor[RM] = speed*se.mult*.8;
					motor[R1] = speed*se.mult*.8;
				}
				else
				{
					motor[LM] = speed*se.mult;
					motor[L1] = speed*se.mult;
					motor[RM] = speed*se.mult;
					motor[R1] = speed*se.mult;
				}
			}
			motor[LM] = -speed*se.mult / 4;
			motor[L1] = -speed*se.mult / 4;
			motor[RM] = -speed*se.mult / 4;
			motor[R1] = -speed*se.mult / 4;
			wait1Msec(200);
		}

		else if (dir == -1)
		{
			while (abs(SensorValue[Lenc])<count)
			{
				if (abs(SensorValue[Lenc])>abs(SensorValue[Renc]) - 5)
				{
					motor[LM] = -speed*se.mult*.8;
					motor[L1] = -speed*se.mult*.8;
					motor[RM] = -speed*se.mult;
					motor[R1] = -speed*se.mult;
				}


				else if (abs(SensorValue[Lenc])<abs(SensorValue[Renc]) + 5)
				{
					motor[LM] = -speed*se.mult;
					motor[L1] = -speed*se.mult;
					motor[RM] = -speed*se.mult*.8;
					motor[R1] = -speed*se.mult*.8;
				}
				else
				{
					motor[LM] = -speed*se.mult;
					motor[L1] = -speed*se.mult;
					motor[RM] = -speed*se.mult;
					motor[R1] = -speed*se.mult;
				}

			}
			motor[LM] = speed*se.mult / 4;
			motor[L1] = speed*se.mult / 4;
			motor[RM] = speed*se.mult / 4;
			motor[R1] = speed*se.mult / 4;
			wait1Msec(100);
		}
		else {}
		motor[LM] = 0;
		motor[L1] = 0;
		motor[RM] = 0;
		motor[R1] = 0;


		initial.xval = Xf;//set new X and Y values
		initial.yval = Yf;

}
