#include "Arduino.h"
#include "CoDrone.h" // 코드론을 사용하기 위한 헤더파일


void setup()
{
  CoDrone.begin(115200);                  // 드론 플러그의 통신 개시 (115200bps)

  CoDrone.AutoConnect(NearbyDrone);    // 최근에 연결한 드론과 같은 어드레스 주소의 드론을 연결

  CoDrone.DroneModeChange(Flight);        // 드론을 플라이트 모드로 설정합니다. (비행형)

  // 2초간 드론을 띄운후 착륙하기
  if (PAIRING == true)                    // 연결(페어링)이 성공한 경우에만 실행
  {
	  /*
	  CoDrone.roll = 0;
	  CoDrone.pitch = 0;

	  CoDrone.Control();
	  delay(100);

	  CoDrone.FlightEvent(TakeOff);         // 이륙
	  delay(2000);                          // 대기 시간
	  CoDrone.FlightEvent(Landing);         // 서서히 착륙
	  */
  }
}

void loop()
{
    CoDrone.Request_DroneAttitude();
    delay(100);

    Serial1.print("R : ");
    Serial1.print(CoDrone.attitudeRoll);
    Serial1.print("\t");
    Serial1.print("P :");
    Serial1.print(CoDrone.attitudePitch);
    Serial1.print("\t");
    Serial1.print("Y : ");
    Serial1.print(CoDrone.attitudeYaw);
    Serial1.println(" ");

}


/*
void setup(void)
{
	Serial.begin(115200);
	Serial1.begin(115200);
}

void loop( void )
{
	static unsigned long tTime;

	if( micros()-tTime > 500*1000 )
	{
		tTime = micros();

		Serial1.print("Tick ");
		Serial1.println(micros());
	}
	//Serial1.println(micros());

	if( Serial.available())
	{
		Serial1.write(Serial.read());
	}
}
*/
