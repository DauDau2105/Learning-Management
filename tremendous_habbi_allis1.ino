#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int startButton = 8;  
const int pauseButton = 9;  
const int ledPin = 12;      
const int buzzerPin = 7;   

const int initialCountdownTime = 5;
int currentTime = initialCountdownTime;

bool running = false;    
bool paused = false;     
bool alarmActivated = false;  

unsigned long previousMillis = 0;  

void setup() {
  pinMode(startButton, INPUT_PULLUP);
  pinMode(pauseButton, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();
  displayTime();
}

void loop() {
  handleButtons();

  
  if (running && !paused && !alarmActivated) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= 1000) { 
      previousMillis = currentMillis;
      currentTime--;  
      
      if (currentTime <= 0) {
        currentTime = 0;        
        running = false;        
        alarmActivated = true;  
      }
      displayTime();
    }
  }


  if (alarmActivated) {
    digitalWrite(ledPin, HIGH);  
    tone(buzzerPin, 1000);         
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time's Up!");
  } else {
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
}


void handleButtons() {
  if (digitalRead(startButton) == LOW) {
    running = true;
    paused = false;
    alarmActivated = false;    
    currentTime = initialCountdownTime;
    previousMillis = millis(); 
    lcd.clear();
    displayTime();
    delay(250); 
  }

  if (digitalRead(pauseButton) == LOW) {
    if (running) {
      paused = !paused;
    }
    delay(250); 
  }
}
void displayTime() {
  lcd.setCursor(0, 0);
  lcd.print("Countdown      ");  
  lcd.setCursor(3, 1);
  lcd.print("00:");
  if (currentTime < 10) {
    lcd.print("0");
  }
  lcd.print(currentTime);
}
