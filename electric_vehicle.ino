
#include <LiquidCrystal.h>// include the library code
/**********************************************************/
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(5, 6, 10, 11, 12, 13);
/*********************************************************/

//Initialize Rotary Encoder variables
const int clkPin = 2; //the clk attach to pin2
const int dtPin = 3; //the dt attach to pin3
const int swPin = 4 ;//the number of the button
const int initialValue = 900;

int encoderVal = initialValue;

// button
int button = 0; //input Pin  
int val = 0; //var for reading pin status 


// motor 
int STBY = 7;  //standby

int PWMA = 1; //speed control
int AIN1 = 9; //direction
int AIN2 = 8; //direction

/****************************************************/
void setup() {

//Setup LCD
  lcd.begin(16, 2);  // set up the LCD's number of columns and rows:
  resetDisplay();


  //Setup Rotary Encoder
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);

 //motor control
 pinMode(button, INPUT);
 pinMode(STBY, OUTPUT);
 pinMode(AIN1, OUTPUT);
 pinMode(AIN2, OUTPUT);



}
/*********************************************************/
void loop (){
  int change = getEncoderTurn();

  if(change != 0) {
    encoderVal = encoderVal + change;
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(0,1);
    lcd.print(encoderVal);
  }
    
    
  if(digitalRead(swPin) == LOW)//if button pull down
  {
    resetDisplay();
    encoderVal = initialValue;
  }

  checkForButton();

  }

 /********************************************************/
 void resetDisplay() { 
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Centimeters: ");
  lcd.setCursor(0,1);
  lcd.print(encoderVal);
}
/************************************************************/
void checkForButton() {
 int distance = encoderVal/.0125;
  val = digitalRead(button); //read input value

if (val == LOW) {

  move (1, 255, 1); //motor 1, full speed, left
  delay(distance); //time); // go for __ milleseconds
  stop(); //stop
} else {
  stop();
  }
  
  
}
/************************************************************/
int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(clkPin);//read the value of clkPin to newA
  int newB = digitalRead(dtPin);//read the value of dtPin to newB
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}
/*****************************************************************/ 
void move(int motor, int speed, int direction) {
  digitalWrite(STBY, HIGH); //disable standby

  boolean inPin1 = LOW;
  boolean inPin2 = HIGH;

  if(direction == 1){
    inPin1 = HIGH;
    inPin2 = LOW;
  }

 if(motor == 1){
  digitalWrite(AIN1, inPin1);
  digitalWrite(AIN2, inPin2);
  analogWrite(PWMA, speed);
 }
 
}

void stop(){
//enable standby
  digitalWrite(STBY, LOW);
}


