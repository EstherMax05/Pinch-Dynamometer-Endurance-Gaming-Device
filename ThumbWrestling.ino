#define _ACTIVATESERIAL #define _USEINTERRUPT
#define PIN_BUTTON P1_4 // the number of the pushbutton pin
int FSR_Pin = P6_0; int LED = P1_3;
int LEDbrightness; int FSR_Pinn = P6_2; int LEDD = P1_5; int LEDbrightnesss; int array1[1000]; int array2[1000]; int Play1;
// analog pin for 1st fsr
// Red LED that changes brightness player1 (PWM pin)
// storage for red LED brightness map ie, duty cycle
// analog pin for 2nd fsr
// Green LED change brightness player2 (PWM pin)
// storage for green LED brightness map ie, duty cycle // store fsr values from player1
// store fsr values from player2
// average values from array1
// average values from array2
// array that stores the points when player1 wins a round // array that stores the points when player2 wins a round
int Play2;
int winarray1[3];
int winarray2[3];
#include <LiquidCrystal.h> // include lcd library
#define DEBOUNCE 300 //debounce
LiquidCrystal lcd(P3_3, P3_4, P2_2, P2_3, P2_4, P2_5); //define lcd
long int now ;
long int lastpress ;
int presscount ;
volatile int update_count ;
void setup() {
// put your setup code here, to run once:
lcd.begin(16, 2);
#ifdef _ACTIVATESERIAL Serial.begin(9600);
#endif
pinMode(PIN_BUTTON, INPUT_PULLUP) ; pinMode(LED, OUTPUT);
lastpress=0; presscount=0; update_count=0;
#ifdef _USEINTERRUPT
attachInterrupt(PIN_BUTTON, inc_button_count, FALLING) ;
#endif
for (int i =0; i < 1000; i++) {
array1[i] = 0; // array for collecting player one's FSR
array2[i] = 0; // array for collecting player two's FSR }
Play1 = 0; //average FSR initial value Play2 = 0; // average FSR initial value
for (int i =0; i < 3; i++) {
winarray1[i] = 0; //array for counting points accumulated each round by player 1
}
for (int i =0; i < 3; i++) {
winarray2[i] = 0; // array for counting points accumulated each round by player 2
} }
void loop() {
// reset winarrays to 0 before going through the game
for (int i =0; i < 3; i++) {
winarray1[i] = 0; //array for counting points accumulated each round by player 1
}
for (int i =0; i < 3; i++) {
winarray2[i] = 0; // array for counting points accumulated each round by player 2
}
//Initially show this before button is pressed... Indicating start of game
if (presscount == 0) {
lcd.setCursor(0, 0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1);

lcd.print("Game ON!! ");
}
now = millis() ;
//Button stuff
#ifndef _USEINTERRUPT
if (digitalRead(PIN_BUTTON) == LOW) update_count=1 ; #endif
if (update_count>0) {
update_count=0 ;
if ((now-lastpress)>DEBOUNCE) {
presscount++ ; // count the number button presses lcd.clear();
lastpress=now ;
} }
/////////////Round 1\\\\\\\\\\\\\\\\ // printing Game stuff
if (presscount == 1) //Upon one buttonpress, print round 1 {
lcd.setCursor(0,0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("Round 1 "); Time = millis()/1000;
//obtain fsr for game round 1
//array1
for (int i=0; i<1000; i++)
{
array1[i] = analogRead(FSR_Pin); //obtain a set of analog values
for player 1 (red led) }
long int sum1 = 0; //intialize sum1 for (int i=0; i<1000; i++)
{
sum1 = sum1 + array1[i]; //sum of array for player 1
}
Play1 = sum1/1000; //average of array for player a

//array2
for (int i=0; i<1000; i++)
{
array2[i] = analogRead(FSR_Pinn); //Player 2 (greenled) obtain a
set of analog values 1000 for robustness ish }
long int sum2 = 0; //intialize sum2 for (int i = 0; i < 1000; i++)
{
sum2 = sum2 + array2[i]; //sum of array for player 2
}
Play2 = sum2/1000; //average of array for player 2
// Just for kicks
LEDbrightness = map(Play1, 0, 4095, 0, 255); // used by analogWrite
(0-255) with map, Energia maxes at 4095
analogWrite(LED, LEDbrightness); // LED gets brighter the harder you
press
LEDbrightnesss = map(Play2, 0, 4095, 0, 255); // used by analogWrite (0-255) with map, Energia maxes at 4095
analogWrite(LEDD, LEDbrightnesss); // LED gets brighter the harder you }
if (presscount == 2) //press the button once again to end round {
//print out stuff for user to know the end of the round is here lcd.setCursor(0,0);
lcd.print("Round 1 OVER ");
lcd.setCursor(0,1);
lcd.print("Results Loading");
delay(1000); }
while (presscount == 2) //show results for round 1 {
long int Now = millis(); //Just so the interupt can work to release from the while loop
if (Play1>Play2) // if player 1 wins {
lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print(" * ");
winarray1[0] = 1; // points to be stored if player wins
press

}
else if (Play1<Play2) //if player 2 wins {
lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print(" * ");
winarray2[0] = 1; // points to be stored if player wins
}
else if (Play1 == Play2); // if they tie {
lcd.setCursor(0,0); lcd.print("Player1||Player2"); lcd.setCursor(0,1);
lcd.print(" * * ");
}
attachInterrupt(PIN_BUTTON, inc_button_count, FALLING) ; if (update_count>0)
{
update_count=0 ;
if ((Now-lastpress)>DEBOUNCE) {
presscount++ ; lcd.clear(); lastpress=Now ;
} }
} // end of while loop
//////////////////Round 2\\\\\\\\\\\\\\\\\\\\\
//print out stuff for user to know the start of round 2 is here
if (presscount == 3) {
lcd.setCursor(0, 0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("Round 2 ");
//obtainfsr to start game //array1
for (int i=0; i<1000; i++) {
array1[i] = analogRead(FSR_Pin); //obtain a set of analog values for player 1 (red led)
}

long int sum1 = 0; //intialize sum1 for (int i=0; i<1000; i++)
{
sum1 = sum1 + array1[i]; //sum of array for player 1
}
Play1 = sum1/1000; //average of array for player a
//array2
for (int i=0; i<1000; i++)
{
array2[i] = analogRead(FSR_Pinn); //Player 2 (greenled) obtain a
set of analog values 1000 for robustness ish }
long int sum2 = 0; //intialize sum2 for (int i = 0; i < 1000; i++)
{
sum2 = sum2 + array2[i]; //sum of array for player 2
}
Play2 = sum2/1000; //average of array for player 2 // Just for kicks
LEDbrightness = map(Play1, 0, 4095, 0, 255); // used by analogWrite (0-255) with map, Energia maxes at 4095
analogWrite(LED, LEDbrightness); // LED gets brighter the harder you
press
LEDbrightnesss = map(Play2, 0, 4095, 0, 255); // used by analogWrite (0-255) with map, Energia maxes at 4095
analogWrite(LEDD, LEDbrightnesss); // LED gets brighter the harder you }
if (presscount == 4) //press the button once again to end round 2 //print out stuff for user to know the end of the round is here
{
lcd.setCursor(0,0); lcd.print("Round 2 OVER "); delay(1000);
}
while (presscount == 4) {
long int Now = millis();
if (Play1>Play2)
{
lcd.setCursor(0,0); lcd.print("Player1||Player2"); lcd.setCursor(0,1);
press

lcd.print(" * ");
winarray1[1] = 1; // points to be stored if player wins }
else if (Play1<Play2)
{
lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print(" * ");
winarray2[1] = 1; // points to be stored if player wins
}
else if (Play1 == Play2); {
lcd.setCursor(0,0); lcd.print("Player1||Player2"); lcd.setCursor(0,1); lcd.print(" * * ");
}
attachInterrupt(PIN_BUTTON, inc_button_count, FALLING) ; if (update_count>0)
{
update_count=0 ;
if ((Now-lastpress)>DEBOUNCE) {
presscount++ ; lcd.clear(); lastpress=Now ;
} }
/////////////Round 3\\\\\\\\\\\\\\\\
//print out stuff for user to know the start of round 3
if (presscount == 5) {
lcd.setCursor(0, 0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("Round 3 - FINALE");
//get fsr for round 3 //array1
for (int i=0; i<1000; i++) {
}
array1[i] = analogRead(FSR_Pin); //obtain a set of analog values

for player 1 (red led) }
long int sum1 = 0; //intialize sum1 for (int i=0; i<1000; i++)
{
sum1 = sum1 + array1[i]; //sum of array for player 1
}
Play1 = sum1/1000; //average of array for player a
//array2
for (int i=0; i<1000; i++)
{
array2[i] = analogRead(FSR_Pinn); //Player 2 (greenled) obtain a
set of analog values 1000 for robustness ish }
long int sum2 = 0; //intialize sum2 for (int i = 0; i < 1000; i++)
{
sum2 = sum2 + array2[i]; //sum of array for player 2
}
Play2 = sum2/1000; //average of array for player 2
// Just for kicks
LEDbrightness = map(Play1, 0, 4095, 0, 255); // used by analogWrite
(0-255) with map, Energia maxes at 4095
analogWrite(LED, LEDbrightness); // LED gets brighter the harder you
press
LEDbrightnesss = map(Play2, 0, 4095, 0, 255); // used by analogWrite (0-255) with map, Energia maxes at 4095
analogWrite(LEDD, LEDbrightnesss); // LED gets brighter the harder you }
if (presscount == 6) //press the button once again to end round 3 // Indicate that the round 3 is over
{
lcd.setCursor(0,0); lcd.print("Round 3 OVER "); delay(1000);
}
if (presscount == 6) {
if (Play1>Play2) {
press

lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print(" * ");
winarray1[2] = 1; // points to be stored if player wins }
else if (Play1<Play2) {
lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print(" * ");
winarray2[2] = 1; // points to be stored if player wins
}
else if (Play1 == Play2); {
winarray1[2] = 1; // points to be stored if player wins lcd.setCursor(0,0);
lcd.print("Player1||Player2");
lcd.setCursor(0,1);
lcd.print("****************"); }
delay(1000);
int sum = winarray1[2]+winarray1[1]+winarray1[0]; //sum of player 1 points accumulated per round
int suma = winarray2[2]+winarray2[1]+winarray2[0]; //sum of player 2 points accumulated per round
if (sum>suma) {
lcd.setCursor(0, 0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("PLAYER 1 WINS!!!");
} else {
lcd.setCursor(0, 0); lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("PLAYER 2 WINS!!!");
}
else if (sum == suma) {
lcd.setCursor(0, 0);

}
lcd.print("Thumb Wrestling!"); lcd.setCursor(0,1); lcd.print("TIE!!! Try Again");
}
delay(3000);
presscount = 0; // reset presscount to zero and restart the loop
}
void inc_button_count() {
update_count=1 ; }