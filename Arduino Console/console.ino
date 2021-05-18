
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//===================================================
// variabile
  int pointer = 2;
  unsigned long last_time;
  boolean btn;
  boolean butt_flag = 0;
  boolean btn_press  = 0;

  //================================================
  //voriabile ping pong
  int velx =-5;     //viteza x
  int vely =3;      //viteza y
  int posx = random(35,70);     //pozitia x
  int posy = random(15 , 38);   //pozitia y
  byte r = 1;            // raza cercului
  int y1 = 22;          // jucator inceput liniei
  int y2 = 42;          //jucator sfirsitul liniei    
  int score = 0;        //scoru jucatorului          
  



void setup() {
  Serial.begin(115200);
  pinMode(3,INPUT);
  pinMode( A2, INPUT_PULLUP);
  pinMode(1,INPUT_PULLUP);
  
  randomSeed(analogRead(0));

  
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  

}

void loop() {
Serial.println(velx);
  
  
  
    display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // ================================================
  //elemente menu
  display.println(
    F(
      "\n"
      " Ping Pong\n"
      " Dino Game\n"
      " 3D Game\n"
      " Python\n"
      " Flapy Bird\n"
        
));


  //====================================================
  //pozitia cursor
  

  int val;
  val = analogRead(3);          // read the input pin
if (millis() - last_time > 150){
    last_time = millis();
      if (val >= 700){
    pointer = constrain(pointer + 1 ,1,8);
}
  if (val <= 300){
    pointer = constrain(pointer - 1 ,1,8);
}
if (pointer == 8){
    pointer = 1;
  }
if (pointer <= 1){
    pointer = 1;
  }

    }
  // ===================================================
  //cursor
  display.setCursor(0, pointer * 8.5);
  display.print(F(">"));


  //=====================================================
  // btn value
  btn = !digitalRead(A2);
  if (btn == 1 && butt_flag == 0){
    butt_flag = 1;
    btn_press = !btn_press;
    
}
  if (btn == 0 && butt_flag == 1){
    butt_flag = 0;
}
  

  //=====================================================
  //btn_press intrarea in elementul meniului cu indexul pointer
  if (btn_press == 1){
    switch(pointer){
        case 2: playPingPong();
          break;
        case 3 : playDinoGame();
          break;
        case 4: play3DGAME();
          break;
        case 5 :  playPython();
          break;
        case 6 :  playFlapyBird();
          break;   
      
      
      }    
}

  //=====================================================
  //scoate imaginea pe display
  display.display(); 
}

//===========================================================================
//===========================================================================
//===========================================================================
//FUNCTIILE CU JOCURI

 void playPingPong(){
  

  for (;;){
  display.clearDisplay(); // clear display
//==================================
//ball
  posx += velx;
  posy += vely;

  if (posx >= 126 || posx <= 2)
    velx = -velx;
  if (posy >= 64 || posy <= 0)
    vely = -vely;

//===================================
//jucatorul 
  display.drawLine(1, y1, 1, y2, WHITE);

  //==========================================
  //calculam pozitia jucatorului
  
  int val;
  val = analogRead(3);
  
  if (val <=300 ){
      int ok = 1;
      if (y1 <= 1 ){
          y1 = 3;
          y2 = 23;
          ok = 0;
        }
        if(ok){
          y1 = y1 - 3;
          y2= y2 - 3;
        }
    }

  if (val >=700 ){
      int ok = 1;
      if (y2 >=63 ){
          y1 = 42;
          y2 = 62;
          ok = 0;
        }
        if(ok){
          y1=y1+3.5;
          y2=y2+3.5;
        }
    }
  //===========================================
  // desenam concurentul 
  int cy1,cy2;
  cy1 = posy - 10;
  cy2 = posy + 10;
  display.drawLine(127, cy1, 127, cy2, WHITE);

    //========================================
  //calcularea scorului
 if (posx<= 3){
  if (posy>=y1 && posy<=y2){
      score++;
    }
}
  display.setTextSize(0.5);
  display.setTextColor(WHITE);
  display.setCursor(63, 0);
  // Display static text
  display.println(score);


  //======================================
  // ecranul de pierdere

if (posx <= 3 ){
    if (posy<=y1 && posy>=0){
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.print(F(
    "You Lose \n"
    "Score: " 
    ));
    display.print(score);
  display.display();
  delay(2000);
  score= 0;
  }
  }

if (posx <= 3 ){
    if (posy>=y2 &&posy<=64){
  
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.print(F(
    "You Lose \n"
    "Score: " 
    ));
    display.print(score);
  display.display(); 
  delay(2000);
  score = 0;
  }
  }
  

  //=======================================
   //cercul
  display.fillCircle(posx, posy, r*2, WHITE);


  
  display.display(); // update display
  }
}
 void playDinoGame(){}
 void play3DGAME(){}
 void playPython(){}
 void playFlapyBird(){}
 
