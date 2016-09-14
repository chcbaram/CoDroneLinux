//----------------------------------------------------------------------------
//    프로그램명   : arduino_util 관련 함수
//
//    만든이		: 
//
//    날  짜		:
//    
//    최종 수정	:
//
//    MPU_Type	:
//
//    파일명		: arduino_util.cpp
//----------------------------------------------------------------------------


#define ARDUINO_UTIL_LOCAL
#include "variant.h"



UARTClass Serial((char *)"/dev/ttyUSB0");
//UARTClass Serial((char *)"/dev/ttyACM0");
ConsolSerial Serial1;

uint32_t DDRC;
uint32_t PORTC;
uint32_t DDRD;
uint32_t PORTD;

//-- 내부 변수 
//



//-- 내부 함수
//



/*---------------------------------------------------------------------------
	TITLE : delay
	WORK  :
	ARG   : void
	RET   : void
---------------------------------------------------------------------------*/
void delay(int delay_ms)
{
    unsigned long ms = delay_ms;


    usleep(ms*1000);
}


/*---------------------------------------------------------------------------
	TITLE : mills
	WORK  :
	ARG   : void
	RET   : void
---------------------------------------------------------------------------*/
uint32_t millis( void )
{
    struct timeval ts;

    gettimeofday(&ts, NULL);
    return ( ts.tv_sec * 1000 + ts.tv_usec / 1000L );
}


/*---------------------------------------------------------------------------
	TITLE : micros
	WORK  :
	ARG   : void
	RET   : void
---------------------------------------------------------------------------*/
uint32_t micros( void )
{
    struct timeval ts;

    gettimeofday(&ts, NULL);
    return ( ts.tv_sec * 1000 + ts.tv_usec );
}

void digitalWrite( int num, uint8_t mode )
{

}


uint8_t digitalRead( int num )
{
	return 0;
}


