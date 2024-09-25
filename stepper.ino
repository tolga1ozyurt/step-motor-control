        /*************************************
                    Tolga Kaan Özyurt
                  Stepper Motor Driving
      Waveshare Motor Driver Shield and Arudino Uno
        *************************************/

#include "DEV_Config.h"
#include "Motor.h"
#include <AccelStepper.h>


void motor1_rot();
void motor2_rot();
void gotoAngle();

int button = 13;
int buttonState = 1;
int angle, lastAngle, totalAngle, startPos;
int i;
String str;

void setup(){

System_Init();
//Motor_Init(MOTOR_DEV_1, 0);
DEV1_Init();
pinMode(button, INPUT);


}

void loop() {
  

      double sensorValue = analogRead(A0)  / 2.8299;//pot kontrolü için
      motor1_rot(sensorValue); 
      if(int(sensorValue) > 0)
      {
      lastAngle = sensorValue;
      totalAngle += lastAngle;
      startPos = totalAngle % 360;
      }
      

    if (Serial.available())
    {
                  
      angle = Serial.parseInt();
      lastAngle = angle;
      totalAngle += lastAngle;
      startPos = totalAngle % 360;
      //str = Serial.readStringUntil('\n');

      motor1_rot(angle);
     // motor2_rot(angle);
    }

      buttonState = digitalRead(button);
      if(buttonState == HIGH)
{
     i= i - (angle % 360); // starting position algorithm , the "i" angle will always be pointing the starting position
     Serial.print("i = ");
     Serial.println(i);
     motor1_rot(-startPos); //son girilen açıyı terse götürmek için "i", başlangıç pozisyonuna dönmek için "-startPos" u kullan
     i = 0;
    startPos=0;
    angle=0;
    lastAngle=0;
} 

          Serial.print("Distance from starting point: ");
          Serial.println(startPos);
          Serial.print("Pot angle: ");
          Serial.println(sensorValue);
          Serial.print("last angle: ");
          Serial.println(lastAngle);
          Serial.print("total angle: ");
          Serial.println(totalAngle);
          Serial.println(" ");
          delay(400);

         

}



void motor1_rot(int angle){

      if(angle<0)
      {
        sMotor1.L2 = MOTOR1_A;
		    sMotor1.L1 = MOTOR1_B;
	    	sMotor1.L4 = MOTOR2_A;
	    	sMotor1.L3 = MOTOR2_B;  
        angle = angle - (2 * angle);
      }else{
        sMotor1.L1 = MOTOR1_A;
		    sMotor1.L2 = MOTOR1_B;
	    	sMotor1.L3 = MOTOR2_A;
	    	sMotor1.L4 = MOTOR2_B;
        
      }
        Motor_Trun(MOTOR_DEV_1, angle);
}

void motor2_rot(int angle){

      if(angle<0)
      {
        sMotor2.L2 = MOTOR3_A;
		    sMotor2.L1 = MOTOR3_B;
	    	sMotor2.L4 = MOTOR4_A;
	    	sMotor2.L3 = MOTOR4_B;
        angle = angle - (2 * angle);

      }else{
        sMotor2.L1 = MOTOR3_A;
		    sMotor2.L2 = MOTOR3_B;
	    	sMotor2.L3 = MOTOR4_A;
	    	sMotor2.L4 = MOTOR4_B;
        
      }
        Motor_Trun(MOTOR_DEV_2, angle);

}

void gotoAngle(double sensorValue, int lasAngle, int startPos){ 

//in progress
  

}

