 

/************************************************************************************************************************************************************************
   - Author           : BEE MB
   - Profession       : (Developer) MEGA DAS owner
   - Main purpose     : Industrial Application
   - Copyright holder : No copyrights
   - Date             : 23/03/2017
 * ***********************************************************************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------------------|
  This code allows you to know the disctance between an Ultrasonic sensor and an object                                           |
  I used two Ultrasonic sensors so you can place them in two different sides to know if there is any object near to your Robot    |
  You can add more Ultrasonic sensors and follow the same steps two be sure that you are getting the desired information          |
  ---------------------------------------------------------------------------------------------------------------------------------|*/
//Start :
//define the pins that we will use for the first ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin1 9                                   //pin number 9 in arduino MEGA2560
#define echoPin1 8                                   // we'll use this pin to read the signal from the first sensor
#define LED_first_ping 22                            // I/O digital or analogique ( we will use pin 22 to command an LED (on/off))
//----------------------------------------------------------------------------------------------------------------------

//define the pins that we will use for the second ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin2 11
#define echoPin2 10
#define LED_second_ping 24
//----------------------------------------------------------------------------------------------------------------------

//define the pins that we will use for the third ultrasonic sensor
//----------------------------------------------------------------------------------------------------------------------
#define trigPin3 13
#define echoPin3 12
#define LED_third_ping 26
//----------------------------------------------------------------------------------------------------------------------

//used variables
//----------------------------------------------------------------------------------------------------------------------
double duration, distance, UltraSensor1, UltraSensor2, UltraSensor3; //we'll use these variable to store and generate data
float x0, y0, z0, x1, y1, z1, x2, y2, z2;
char data;
String SerialData = "";
double CentreX, CentreY, CentreZ, Px, Py, Pz, Qx, Qy, Qz, Rx, Ry, Rz, PQx, PQy, PQz, PRx, PRy, PRz;
float PQPR, SQPQ, SQPR, cangle, angle;
float UltraSensor1S, UltraSensor1T, UltraSensor2S,UltraSensor2T, UltraSensor3S, UltraSensor3T;
float average1, average2, average3;
float opp, tangle, fdistance;
//float C0, C1, C2, Plane, Final;
//----------------------------------------------------------------------------------------------------------------------

//Make the setup of your pins
//----------------------------------------------------------------------------------------------------------------------
void setup()
{ // START SETUP FUNCTION
  Serial.begin (9600);                              // we will use the serial data transmission to display the distance value on the serial monitor

  // setup pins first sensor
  pinMode(trigPin1, OUTPUT);                        // from where we will transmit the ultrasonic wave
  pinMode(echoPin1, INPUT);                         //from where we will read the reflected wave
  
  //setup pins second sensor
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  //setup pins third sensor
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);

  x0 = 0;
  y0 = 0;
  //z0 = 0;
  x1 = 0;
  y1 = 3;
  //z1 =5;
  x2 = 0;
  y2 = -3;
 // z2 = 5;





}// END SETUP FUNCTION

//write the code in the loop function
void loop()
{
  UltraSensor1=0;
  UltraSensor2=0;
  UltraSensor3=0;
  // START THE LOOP FUNCTION   

  for (int i = 0; i<10; i++) {  
    SonarSensor(trigPin1, echoPin1);              // look bellow to find the difinition of the SonarSensor function

   if(distance>=UltraSensor1+0.5)
   {
    UltraSensor1T = UltraSensor1S;
    UltraSensor1S = UltraSensor1;
  UltraSensor1 = distance;                       // store the distance in the first variable
   }
   else if(distance>=UltraSensor1S)
   {
    UltraSensor1T = UltraSensor1S;
    UltraSensor1S=distance;
   }
   else if(distance>=UltraSensor1T)
   {
        UltraSensor1T=distance;
   }
   average1=(UltraSensor1+UltraSensor1S+UltraSensor1T)/3; 
   x0 = average1 ;
   delay(70);
  
  }
                      
 for (int i = 0;i<10; i++) {
    SonarSensor(trigPin2, echoPin2);              // call the SonarSensor function again with the second sensor pins

  if(distance>=UltraSensor2+0.5)
   {
    UltraSensor2T = UltraSensor2S;
    UltraSensor2S = UltraSensor2;
  UltraSensor2 = distance;                       // store the distance in the second variable
   }
   else if(distance>=UltraSensor2S)
   {
    UltraSensor2T = UltraSensor2S;
    UltraSensor2S=distance;
   }
   else if(distance>=UltraSensor2T)
   {
    UltraSensor2T=distance;
   }
   average2=(UltraSensor2+UltraSensor2S+UltraSensor2T)/3;
   x1 = average2;
   delay(70);
  }
  
  fdistance = (x0+x1)/2;
  /*
  SonarSensor(trigPin3, echoPin3);              // call the SonarSensor function again with the second sensor pins
  UltraSensor3 = distance;                      // store the new distance in the second variable
  x2 = UltraSensor3;

  while (Serial.available())
  {
    delay(10);
    data = Serial.read();
    SerialData += data;
  }

*/
  // display the distances on the serial monitor for the first sensor
  //----------------------------------------------------------------------------------------------------------------------
  Serial.println();
  Serial.println();
  Serial.print("distance measured by the first sensor: ");
  Serial.print(x0);
  Serial.println(" cm");
  Serial.print(x0);
  Serial.print(",0");
  Serial.println();
  //----------------------------------------------------------------------------------------------------------------------

  //display the distance on the serial monitor for the second sensor
  //----------------------------------------------------------------------------------------------------------------------
  Serial.print("distance measured by the second sensor: ");
  Serial.print(x1);
  Serial.println(" cm");
  Serial.print(x1);
  Serial.print(",3");
  Serial.println();
  //---------------------------------------------------------------------------------------------------------------------
/*
  //display the distance on the serial monitor for the third sensor
  //----------------------------------------------------------------------------------------------------------------------
  Serial.print("distance measured by the third sensor: ");
  Serial.print(UltraSensor3);
  Serial.println(" cm");
  Serial.print(x2);
  Serial.print(",-3");
  Serial.println();
  //----------------------------------------------------------------------------------------------------------------------

*/
  Serial.print("The distance to the surface is");
  Serial.println(fdistance);
  opp = 0;
  CentreX = 0;
  CentreY = 0;
  CentreZ = 3.333;   // Center of the three sensors, will be used in the final equation
  
  /*Px = x0;
  Py = 0;
                    Pz = 0; //Vector P where sensor 1 detects
  
  Qx = x1;
  Qy = 3;
                      Qz = 5; // Vector Q where sensor 2 detects

  
  Rx = x2;
  Ry = -3;
                      Rz = 5; //Vector R where sensor 3 detects

  PQx = x1 - x0;
  PQy = 3;
                     PQz = 5;    //Defining PQ in its individual parts

  PRx = x2 - x0;
  PRy = -3;
                         PRz = 5;  //Defining PR in its individual parts
  */
  opp = (x0-x1); //??????
  tangle = (opp/5)*(180/3.14);

  angle = atan(tangle);

  Serial.print("The current angle of the surface is:");
  Serial.println(tangle);

  if((-30>=tangle)||(30<=tangle))
  {
    Serial.println("The system has exceeded it's maximum range, the arm should begin rotation");
  }
  else{
    Serial.println("Current trajectory is fine, continue on the same path");
  }


  
 






  
 //SQPQ = sqrt(pow(x1-x0,2)+9);
  //SQPR = sqrt(pow(x2-x0,2)+9);
  //C1 = -(5*x1) + (5*x2);
  //C2 = (6*x0) - (3*x1) - (3*x2); //Plane = C0(x-X0) + C1(y-YO) + C2(z-Z0) note (X0,Y0,Z0) = (x0,0,0)  //Cross product of PQ and PR
 // cangle = PQPR/(SQPQ*SQPR);
 // angle = acos(cangle);
 /* Serial.print("PQPR is:");
  Serial.println(PQPR);
  Serial.print("SQPQ is:");
  Serial.println(SQPQ);
  Serial.print("SQPR is:");
  Serial.println(SQPR);
  Serial.print("cangle is:");
  Serial.println(cangle);
  Serial.print("angle is:");
  Serial.println(angle);
  
  if ((angle>=80)&&(angle<=90)) {
  
  Serial.print("The allignment is fine, the system will continue as normal");
  }
  else{
  Serial.println("There is an obscure allignment, the system will now proceed to rotate");
  }
  */
  /*Plane = abs(C0*(x0));//abs(C0*(CentreX-x0)+C1*(CentreY-y0)+C2*(CentreZ-z0));
  Serial.print("C0 is:");
  Serial.println(C0);
  Serial.print("C1 is:");
  Serial.println(C1);
  Serial.print("C2 is:");
  Serial.println(C2);
  Serial.print("The value of the the plane is:");
  Serial.println(Plane);
  
  Final  = (Plane-C2*CentreZ)/(sqrt(pow(C0,2)+pow(C1,2)+pow(C2,2)));
  Serial.print("The average distance of the sensors to the plane is:");
  Serial.print(Final);
  Serial.println("cm");
  */
  delay(2000);
}//END LOOP FUNTION

// SonarSensor function used to generate and read the ultrasonic wave
void SonarSensor(int trigPinSensor, int echoPinSensor) //it takes the trigPIN and the echoPIN
{
  //START SonarSensor FUNCTION
  //generate the ultrasonic wave
  //----------------------------------------------------------------------------------------------------------------------
  digitalWrite(trigPinSensor, LOW);// put trigpin LOW
  delayMicroseconds(2);// wait 2 microseconds
  digitalWrite(trigPinSensor, HIGH);// switch trigpin HIGH
  delayMicroseconds(10); // wait 10 microseconds
  digitalWrite(trigPinSensor, LOW);// turn it LOW again
  delayMicroseconds(50);
  //----------------------------------------------------------------------------------------------------------------------

  //read the distance
  //----------------------------------------------------------------------------------------------------------------------
  duration = pulseIn(echoPinSensor, HIGH);//pulseIn funtion will return the time on how much the configured pin remain the level HIGH or LOW; in this case it will return how much time echoPinSensor stay HIGH
  distance = (duration / 2) / 29.1; // first we have to divide the duration by two
}// END SonarSensor FUNCTION

/****************************----------------------- END PROGRAM -----------------------****************************/
