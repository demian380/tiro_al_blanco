#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

long tiempo;

long tiempoAnterior;

int tiempoLimite;

int puntaje;

int secuencia;

Servo servo_4;

Servo servo_5;

void setup()
{
  lcd.init();
lcd.backlight();
  pinMode(13,OUTPUT);
  tiempo=0;

  tiempoAnterior=0;

  tiempoLimite=30;

  puntaje=0;

  secuencia=1;

  servo_4.attach(4);
  servo_5.attach(5);
    lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando");
  servo_4.write(10);
  servo_5.write(90);
  digitalWrite(13,HIGH);
  tone(7, 660, 500);
  delay(700);
  
  tone(7, 741, 900);
  delay(1300);
  digitalWrite(13,LOW);

  Serial.begin(9600);
  pinMode(2,INPUT);

}


void loop()
{


        Serial.println("pulse el boton para comenzar");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pulse el boton");
    lcd.setCursor(0, 1);
    lcd.print("para comenzar:");
    while (digitalRead(2) == 1) {
     }
    Serial.println("Juego Iniciado");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Juego iniciado");
    while (tiempoLimite >= 0) {
      tiempo = millis();
      if (tiempo - tiempoAnterior >= 1000) {
        Serial.println(tiempoLimite);
        lcd.setCursor(0, 1);
        lcd.print("Tiempo:");
        if (tiempoLimite < 10) {
          lcd.setCursor(10, 1);
          lcd.print(tiempoLimite);
          lcd.setCursor(9, 1);
          lcd.print(0);

        } else {
          lcd.setCursor(9, 1);
          lcd.print(tiempoLimite);

        }
        tiempoAnterior = tiempo;
        tiempoLimite = tiempoLimite - 1;

      }
      if (analogRead(A0) >= 950) {
        digitalWrite(13,HIGH);
        tone(7, 741, 400);
        servo_4.write(70);
        if (secuencia == 1) {
          servo_5.write(10);

        } else {
          servo_5.write(150);

        }
        delay(500);
        digitalWrite(13,LOW);
        puntaje = puntaje + 1;
        secuencia = secuencia + 1;

      }
      if (analogRead(A1) >= 950) {
        digitalWrite(13,HIGH);
        tone(7, 741, 400);
        servo_5.write(70);
        if (secuencia == 2) {
          servo_4.write(150);

        } else {
          servo_4.write(10);

        }
        delay(500);
        digitalWrite(13,LOW);
        puntaje = puntaje + 1;
        if (secuencia == 4) {
          secuencia = 1;

        } else {
          secuencia = secuencia + 1;

        }

      }
     }
    tiempoLimite = 30;
    secuencia = 1;
    Serial.println("juego finalizado:");
    Serial.println(puntaje);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Juego finalizado");
    lcd.setCursor(0, 1);
    lcd.print("Puntaje:");
    lcd.setCursor(10, 1);
    lcd.print(puntaje);
    servo_4.write(10);
    servo_5.write(70);
    delay(5000);
    puntaje = 0;


}
