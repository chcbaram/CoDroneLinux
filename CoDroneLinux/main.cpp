#include "main.h"
#include "Arduino.h"
#include "CoDrone.h" // 코드론을 사용하기 위한 헤더파일


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

	printf("Connect CoDrone..\n");
  CoDrone.begin(115200);  // sets up the connection to the drone using the bluetooth module at 115200bps (bits per second)
  CoDrone.AutoConnect(NearbyDrone);    // finds and connects to a drone that is nearby
  CoDrone.DroneModeChange(Flight); // Changes the drone so that it is now in flight mode

  CoDrone.LedColor(EyeNone, Green, 7);

  printf("OK..\n");

	while(1)
	{
		Ret = Joy_Update();

		if( Ret == true )
		{
			Joy = Joy_Read();

			//printf("Run: type %d, time %d, number %d, value %d\n", Joy.js_type, Joy.js_time, Joy.js_number, Joy.js_value);
			//printf("Axis %d, %d \n", Joy.AxisValue[0], Joy.AxisValue[1] );
			printf("Axis R %f, P %f, Y %f, T %f \n", Joy.fRoll, Joy.fPitch, Joy.fYaw, Joy.fThrutle );


      if( Joy.ButtonValue[6] == true )
      {
        CoDrone.LedColor(EyeNone, Green, 7);
        delay(100);
      }
      if( Joy.ButtonValue[8] == true )
      {
        CoDrone.LedColor(EyeMix, Green, 7);
        delay(100);
      }

			if( Joy.ButtonValue[1] == true )
			{
				printf("STOP\n");
				CoDrone.FlightEvent(Stop);
			}

     if( Joy.ButtonValue[10] == true )
      {
        printf("Landing\n");
        CoDrone.FlightEvent(Landing);
      }

     if( Joy.ButtonValue[11] == true )
      {
        printf("TakeOff\n");
        CoDrone.FlightEvent(TakeOff);
      }
		}


	  // PAIRING is set to true in AutoConnect if they connect together
	  if (PAIRING == true)  // Check to see that we are paired before trying to fly
	  {
	    YAW       = Joy.fYaw     * 100;
	    THROTTLE  = Joy.fThrutle * 100;
	    ROLL      = Joy.fRoll    * 100;
	    PITCH     = Joy.fPitch   * 100;

	    CoDrone.Control(SEND_INTERVAL); // sends the values to the codrone, it will make sure that SEND_INTERVAL (~50ms) time has passed before it sends again
	  }
	}		
}

