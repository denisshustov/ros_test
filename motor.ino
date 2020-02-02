  #include <Wire.h>
#include <Adafruit_MotorShield.h>

#include <ArduinoHardware.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotorBack = AFMS.getMotor(1);
Adafruit_DCMotor *myMotorTurn = AFMS.getMotor(2);
Adafruit_DCMotor *myMotorForward = AFMS.getMotor(4);
int speed = 255;
int startSpeed = 100;

ros::NodeHandle nh;

void messageCb( const geometry_msgs::Twist& msg){
  //speed_ang = msg.angular.z;
  //speed_lin = msg.linear.x;

  char str[5];
  
  nh.loginfo("Receive linear.x = ");
  nh.loginfo(itoa(msg.linear.x, str, 2));
  
  nh.loginfo("Receive angular.z = ");
  nh.loginfo(itoa(msg.angular.z, str, 2));

  if(msg.linear.x == 0)
  {
    Stop();
    return;
  }
  else if(msg.linear.x > 0)
  {
    RunForward();
  }
  else if(msg.linear.x < 0)
  {
    RunBack();
  }

  if(msg.angular.z > 0)
  {
    TurnRight();
  }
  else if(msg.angular.z < 0)
  {
    TurnLeft();
  }

  for (uint8_t i=100; i<255; i++) {
    myMotorForward->setSpeed(i);
    myMotorBack->setSpeed(i);
    delay(10);
  }
  //delay(100);
  //Stop();
};

ros::Subscriber<geometry_msgs::Twist> sub("cmd_vel", &messageCb );


void setup() {
  Serial.begin(9600);  
  while (!Serial);
  //Serial.println("Serial OK");
  AFMS.begin(); 
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  myMotorBack->setSpeed(startSpeed);
  myMotorTurn->setSpeed(speed);//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  myMotorForward->setSpeed(startSpeed);

  nh.initNode();
  nh.subscribe(sub);
  //Serial.println("INIT OK");

  nh.loginfo("Motor init ok");
}
void Stop()
{
  myMotorForward->run(RELEASE);
  myMotorBack->run(RELEASE);
  myMotorTurn->run(RELEASE);
  //Serial.println("STOP");
}

void RunForward()
{ 
  myMotorBack->run(BACKWARD);
  myMotorForward->run(FORWARD);
  //Serial.println("FORWARD");
}
void RunBack()
{
  myMotorBack->run(FORWARD);
  myMotorForward->run(BACKWARD);
  //Serial.println("BACKWARD");
}

void TurnLeft()
{
  myMotorTurn->run(FORWARD);
 // Serial.println("LEFT");
}
void TurnRight()
{
  myMotorTurn->run(BACKWARD);
  //Serial.println("RIGHT");
}


void loop() {
  nh.spinOnce();
  delay(20);
  
  //counter++;  
  
}
