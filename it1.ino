/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 12
 * LCD Enable pin to digital pin 11
 * LCD D4 pin to digital pin 5
 * LCD D5 pin to digital pin 4
 * LCD D6 pin to digital pin 3
 * LCD D7 pin to digital pin 2
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//initialize the button variables
int leftBtn = 10;
int rightBtn = 9;
int upBtn = 13;
int downBtn = 8;

//state variables for the buttons
int leftState = 0;
int rightState = 0;
int upState = 0;
int downState =0;

//sets up the days and hours need for days
int days[7] = {0,0,0,0,0,0,0};

//int to track the day
int day = 1;

//basic Strings
String dayStd = "Day: ";
String dayAsStr = String(day);
String f = dayStd + dayAsStr;
String hours = "Hours: ";
String hourVar = String(days[day - 1]);
String bottom = hours + hourVar;

//time variables
long startTime = millis();
long dayLength = 60;

//led variables
//this is to test the time functions and opening and closing time
int greenLED = 7;
int redLED = 6;
    
//temperature values
int temp = 0;
int timeOpen = 0;
int previousDay = 0;


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

void setup() {
  
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print(f);
  //lcd.write(" Day: " + "day");
  //set cursor to bottom line;
  lcd.setCursor(0, 1);
  lcd.print(bottom);
  
  //Set up the buttons
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(leftBtn, INPUT);
  pinMode(rightBtn, INPUT);
  pinMode(upBtn, INPUT);
  pinMode(downBtn, INPUT);
  
  
  //time setup
  
  //LED setup
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  //setup the simulation representative
  closed();
  
  
  
}


void loop() {
  //redundancy is good
  if(day > 7)day = 1;
  if(day < 0) day = 7;
  
  //check state of the buttons
  readStates();
  
  
  
  //check left button
  if(leftState == HIGH){
    //lcd.clear();
    //set the cursor to the top line
    lcd.setCursor(0,0);
    
    day--;
    if(day == 0){
      tempOut(temp);
    }else if(day < 0) {
    	day = 7;
    	//print out what we want
    	outLCD();
    }else{
      outLCD();
    }
    
    
    
  }
  
  
  //check right button
  if(rightState == HIGH){
    //lcd.clear();
    lcd.setCursor(0,0);
    
    day++;
   	if(day > 7){
       	day = 0;
      	//reset the str variables for printing
    }
    if(day == 0){
     tempOut(temp);
    }else{
      outLCD();
    }
    
    
   

  }
  
  
  //check up button
  if(upState == HIGH){
 
    if(day != 0){
    	days[day - 1] ++;
    	if(days[day - 1] > 24)days[day - 1] =24;
    	outLCD();
    }else{
      temp++;
      tempOut(temp);
    }
    
  }
  
  
  //check down button
  if(downState == HIGH){
    if(day != 0){
    	days[day - 1] --;
    	if(days[day - 1] < 0)days[day - 1] =0;
   
    	outLCD();
    }else{
    	temp--;
      	tempOut(temp);
    }
    
  }
  
  //delay at the end of loop
  delay(250);
  
  //timeChecker();
  
  
  //////////////////////////////////////////////////////////
  //Now start the part where we control the motors and shade
  //////////////////////////////////////////////////////////
  
}



//////////////////////////////////////////////////////////////


//////////////////////////////////
//Functions start here going down--------------------------------------
//////////////////////////////////


//function that prints out the updated version for LCD
void outLCD(){
	lcd.clear();
  
  	dayAsStr = String(day);
	f = dayStd + dayAsStr;
    //print the new str
    lcd.print(f);
  
  
  	lcd.setCursor(0,1);
  	hourVar = String(days[day - 1]);
	bottom = hours + hourVar;
  
  	lcd.print(bottom);
}

//for temp
void tempOut(int temp){
	lcd.clear();
  
  	
  	String temper = "Max Temperature:";
  	
	String out = temper;
    //print the new str
    lcd.print(temper);
  
  
  	lcd.setCursor(0,1);
  	String tempStr = String(temp);
  	String tempStd = " F";
	bottom = tempStr + tempStd;
  
  	lcd.print(bottom);
}

//function that reads the states of the buttons and updates them.
void readStates(){
	leftState = digitalRead(leftBtn);
  	rightState = digitalRead(rightBtn);
  	upState = digitalRead(upBtn);
  	downState = digitalRead(downBtn);
}

//function that checks time and determines if we still need sunlight
void timeChecker(bool state, int openTime){
  long currentTime = millis();
  long totalElapsed = (currentTime - startTime)/1000;
}

//returns whether or not the system should be open
bool shouldBeOpen(int openTime){
  if(openTime < days[day]){
    return true;
  }
  return false;
}

//function that returns how long the system has been in its current state either on or off
int timeElapsed(int start){
  return millis() - start;
  
}

 
//function that simulates an open orientation with the 
//shadecloth retracted, using LEDs
void open(){
  digitalWrite(greenLED, HIGH);
  digitalWrite(redLED, LOW);
}

//function that simulates a closed orientation with the
//shadecloth over the plants, using LEDs
void closed(){
  digitalWrite(redLED, HIGH);
  digitalWrite(greenLED, LOW);
}

//checks whether or not the current state is open
bool isOpen(){
  digitalRead(greenLED);
}

//function that tells us what day it is 1-7
int getDay(){
	int currentTime = (millis()- startTime)/1000;
  	int day = (currentTime / 60) + 1;
  	return day;
}

void doWork(int pDay){
    int currentDay = getDay();
  	if(currentDay != pDay){
    	timeOpen = 0;
    }
  	float sTime = millis();
    
    

    if(timeOpen < days[currentDay] && !isOpen()){
        open();
    }else{
        close(); //just put this to avoid error, not logical yet, need to check
    }

    

    



}