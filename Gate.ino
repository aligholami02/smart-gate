#include <Arduino.h> 
#include <TM1637Display.h> 
#include <Servo.h> 

#define CLK 2 // پین CLK 
#define DIO 3 // پین DIO 

const int trigPin = 9; // تعیین پین ارسال پالس 
const int echoPin = 10; // تعیین پین دریافت پالس 
const int ledPin = 13; // تعیین پین LED 
const int redledPin = 4; // تعیین پین LED 
const int servoPin = 5; // پین سرو موتور 

long duration; 
int distance; 
int counter = 1; 

void setup() { 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(ledPin, OUTPUT); // تنظیم پین LED به عنوان خروجی 
  myServo.attach(servoPin); // اتصال سرو موتور به پین مشخص 
  Serial.begin(9600); // شروع ارتباط با سریال 
  display.setBrightness(0x0a); // تنظیم نور صفحه نمایش 
  display.showNumberDec(counter, false); // نمایش مقدار اولیه شمارنده 
} 


void loop() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 

  duration = pulseIn(echoPin, HIGH); 
  distance = duration * 0.034 / 2; 

  Serial.println(distance); // نمایش فاصله در پورت سریال 
myServo.write(180); 

  if (distance <= 6){ 
    digitalWrite(ledPin, HIGH); // روشن کردن LED 
    counter--; // کاهش شمارنده 
    myServo.write(90); // حرکت سرو موتور به زاویه 90 درجه 
    delay(3000); // تاخیر برای حرکت سرو موتور به مدت 3 ثانیه 
    myServo.write(0); // بازگشت سرو موتور به زاویه 0 درجه 
  }  
  else if (distance >= 7 && distance <= 15) { 
      counter++; // افزایش شمارنده 
     digitalWrite(redledPin, HIGH); 
      delay(3000); 
      digitalWrite(redledPin, LOW); 
      delay(200); // خاموش کردن LED بعد از تاخیر 
  } else { 
    digitalWrite(ledPin, LOW); // خاموش کردن LED 
  } 

  if (counter <= 0) { 
      digitalWrite(redledPin, HIGH); // چشمک زدن LED برای 5 ثانیه 
      delay(250); 
      digitalWrite(redledPin, LOW); 
      delay(250); 
      counter = 0; // بازنشانی شمارنده بعد از چشمک زدن 
   } 

  display.showNumberDec(counter, false); // نمایش شمارنده 

  delay(10); // تاخیر برای خواندن داده‌ها و نمایش 
} 