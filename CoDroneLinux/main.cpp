#include "main.h"



extern void setup();
extern void loop();


void show( void );
void run( char *pUartPort );



//-- main
//
int main(int argc, char **argv)
{
	bool Ret;

	if( argc < 2 )
	{
		printf("Option \n");
		printf(" show \n");
		printf(" run \n");
	}
	else
	{
		if( strcmp(argv[1], "arduino") == 0 )
		{
			setup();
			while(1)
			{
				loop();
			}
		}


		Ret = Joy_Open("/dev/input/js0");

		if( Ret == false )
		{
			printf("Joy_Open Fail\n");
			return -1;
		}

		if( strcmp(argv[1], "show") == 0 )
		{
			show();
		}
		else
		if( strcmp(argv[1], "run") == 0 )
		{
			if( argc < 3 )
			{
				printf("Add Uart Port..\n");
				return -1;
			}
			else
			{
				run( argv[2] );
			}
		}
	}
    


	return 0;
}




/*---------------------------------------------------------------------------
	TITLE : show
	WORK  :
	ARG   : void
	RET   : void
---------------------------------------------------------------------------*/
void show( void )
{
	bool Ret;
	JOY_OBJ Joy;

	while(1)
	{
		Ret = Joy_Update();


		if( Ret == true )
		{
			Joy = Joy_Read();

			Serial1.println("test");
			printf("Event: type %d, time %d, number %d, value %d\n", Joy.js_type, Joy.js_time, Joy.js_number, Joy.js_value);
		}

	}	
}










/*---------------------------------------------------------------------------
	TITLE : show
	WORK  :
	ARG   : void
	RET   : void
---------------------------------------------------------------------------*/
void run( char *pUartPort )
{
	bool Ret;
	JOY_OBJ Joy;
	uint32_t tTime;
	uint32_t tTimeSend;
	bool Fly = false;

	while(1)
	{
		Ret = Joy_Update();

		if( Ret == true )
		{
			Joy = Joy_Read();

			//printf("Run: type %d, time %d, number %d, value %d\n", Joy.js_type, Joy.js_time, Joy.js_number, Joy.js_value);
			//printf("Axis %d, %d \n", Joy.AxisValue[0], Joy.AxisValue[1] );
			//printf("Axis %f, %f, %f, %f \n", Joy.fRoll, Joy.fPitch, Joy.fYaw, Joy.fThrutle );

			if( Joy.ButtonValue[0] == true )
			{
				printf("RESET_YAW\n");
				Fly = true;
			}

			if( Joy.ButtonValue[1] == true )
			{
				printf("STOP\n");
				Fly = false;
			}			

			if( Joy.ButtonValue[2] == true )
			{
				printf("AB MODE\n");
				Fly = false;
			}			

			if( Joy.ButtonValue[3] == true )
			{
				printf("RC MODE\n");
				Fly = false;
			}			

		}

		if( (millis() - tTime) > 1000 )
		{
			tTime = millis();

			//printf("Fly:%d, Battery:%d \n", DF_Ret.Flight, DF_Ret.Battery);
		}

		if( (millis() - tTimeSend) > 100 )
		{
			tTimeSend = millis();

			//if( Fly == true )
			//	DF_SendPacket( Joy.fRoll*100, Joy.fPitch*100, Joy.fYaw*100, Joy.fThrutle*100, 0x00 );
			//else
			//	DF_SendPacket( Joy.fRoll*100, Joy.fPitch*100, Joy.fYaw*100, Joy.fThrutle*100, STOP );
		}
	}		
}

