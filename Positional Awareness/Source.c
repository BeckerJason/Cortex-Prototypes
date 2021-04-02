typedef struct
{
	float xval;
	float yval;
	float angle;
}TPositionRecord;
TPositionRecord initial;





//Positional Awareness Code
void MoveToPosition(float Xf, float Yf, int speed,int MoveSpeed, int time, int adir_overide)
{
	float gyros=SensorValue[in7]*0.973/10;
	int fullRotation = (360); //12.56 inches in distance with 4 inch wheel
	float oneFoot = (.955*fullRotation); //oneFoot = 12 inches or 343.95
	float tile = 2 * oneFoot;
	float Angle;
	int adir;
	float HypDist = sqrt(pow((Xf - initial.xval), 2) + pow((Yf - initial.yval), 2));
	if (HypDist>0)
	{
		Angle = acos((Xf - initial.xval) / HypDist)*(180/PI);
	}
	else{Angle =0;}
	float turnAngle = gyros - Angle;

	writeDebugStreamLine("Distance %f",HypDist);
	writeDebugStreamLine("Angle %f",Angle);
	//cout << "Turn Angle" << turnAngle << endl;

	if (Yf - initial.yval >= 0)
	{
		if(turnAngle > 0)
		{adir=1;
			//TURN RIGHT
			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}

			//WAIT TO OVERTURN AND THEN COMPENSATE LEFT
			wait1Msec(time);
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}


			//WAIT TO OVERTURN AND THEN COMPENSATE RIGHT
			wait1Msec(time);

			adir=1;

			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}

			//BRAKE
			motor[LM] = -adir*10*se.mult;
			motor[L1] = -adir*10*se.mult;
			motor[RM] = adir*10*se.mult;
			motor[R1] = adir*10*se.mult;
			wait1Msec(100);
			//STOP
			motor[LM] = 0;
			motor[L1] = 0;
			motor[RM] = 0;
			motor[R1] =0;
			//		right
			//		motor[LM] = adir*100*se.mult;
			//motor[L1] = adir*100*se.mult;
			//motor[RM] = -adir*100*se.mult;
			//motor[R1] = -adir*100*se.mult;
			//Turn(1,Angle);//turn right
		}
		else if (turnAngle < 0 )
		{//TURN LEFT
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			//WAIT TO OVERTURN AND THEN COMPENSATE RIGHT
			wait1Msec(time);

			adir=1;

			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			//WAIT THEN COMPENSATE LEFT
			wait1Msec(time);
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}


			motor[LM] = -adir*10*se.mult;
			motor[L1] = -adir*10*se.mult;
			motor[RM] = adir*10*se.mult;
			motor[R1] = adir*10*se.mult;
			wait1Msec(200);
			motor[LM] = 0;
			motor[L1] = 0;
			motor[RM] = 0;
			motor[R1] =0;
			//Turn(-1,Angle);// turn left
		}
		else
		{
			writeDebugStreamLine("Nope");
			Turn(0,Angle);
		}

	}
	else if(Yf - initial.yval < 0){
		turnAngle = 360 - turnAngle;
		writeDebugStreamLine("Turn Angle %f",turnAngle);

		if(turnAngle > 0)
		{adir=1;
			//TURN RIGHT
			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}

			//WAIT TO OVERTURN AND THEN COMPENSATE LEFT
			wait1Msec(time);
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}


			//WAIT TO OVERTURN AND THEN COMPENSATE RIGHT
			wait1Msec(time);

			adir=1;

			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}

			//BRAKE
			motor[LM] = -adir*10*se.mult;
			motor[L1] = -adir*10*se.mult;
			motor[RM] = adir*10*se.mult;
			motor[R1] = adir*10*se.mult;
			wait1Msec(100);
			//STOP
			motor[LM] = 0;
			motor[L1] = 0;
			motor[RM] = 0;
			motor[R1] =0;
		}
		else if (turnAngle < 0 )
		{	//TURN LEFT
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult;
				motor[L1] = adir*speed*se.mult;
				motor[RM] = -adir*speed*se.mult;
				motor[R1] = -adir*speed*se.mult;
			}
			//WAIT TO OVERTURN AND THEN COMPENSATE RIGHT
			wait1Msec(time);

			adir=1;

			writeDebugStreamLine("Right");
			while (SensorValue[gyro]*0.973/10< Angle&&SensorValue[gyro]>0)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/2;
				motor[L1] = adir*speed*se.mult/2;
				motor[RM] = -adir*speed*se.mult/2;
				motor[R1] = -adir*speed*se.mult/2;
			}
			//WAIT THEN COMPENSATE LEFT
			wait1Msec(time);
			adir=-1;
			writeDebugStreamLine("Left");
			while ((SensorValue[gyro]*0.973/10+360) %360 >Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}
			while (SensorValue[gyro]*0.973/10< Angle)
			{
				motor[LM] = adir*speed*se.mult/3;
				motor[L1] = adir*speed*se.mult/3;
				motor[RM] = -adir*speed*se.mult/3;
				motor[R1] = -adir*speed*se.mult/3;
			}


			motor[LM] = -adir*10*se.mult;
			motor[L1] = -adir*10*se.mult;
			motor[RM] = adir*10*se.mult;
			motor[R1] = adir*10*se.mult;
			wait1Msec(200);
			motor[LM] = 0;
			motor[L1] = 0;
			motor[RM] = 0;
			motor[R1] =0;
			//Turn(-1,Angle);// turn left
		}
		else
		{			writeDebugStreamLine("Nope");
			Turn(0,Angle);

		}

	}

	/*	move(distance);
	correctionX = inX;
	correctionY = inY;
	gyro = angle;
	cout << "Turn Angle" << turnAngle << endl;

	cout << "correctionX "<<correctionX << endl;
	cout << "correctionY "<<correctionY << endl;
	cout << "Robot Angle" << gyro << endl;

	*/

	writeDebugStreamLine("X%f   Y%f   H%f   TA%f   SV %f    ",(Xf - initial.xval),(Yf - initial.yval), HypDist, turnAngle,gyros);



	//MOVE
	speed = MoveSpeed;
	int dir;
	int count = tile*HypDist;			//Determines the encoder count of the travel distance
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
		wait1Msec(100);
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
