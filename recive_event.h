#include "stdint.h"

#include <RGBmatrixPanel.h>
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>

#define CLK 15
#define OE 14  //13
#define LAT 19
#define A 12
#define B 16
#define C 17
#define D 18
#define mw 32
#define mh 32
#define NUMMATRIX (mw * mh)              //電光掲示板の面積
#define setBrightness(x) fillScreen(15)  // no-op, no brightness on this board
//#define clear()          fillScreen(0)
#define show() swapBuffers(true)
#define Color(x, y, z) Color444(x / 16, y / 16, z / 16)
#define LED_BLACK 0
//#define clear()   fillScreen(0)

RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);



uint8_t cR = 0;
uint8_t cG = 0;
uint8_t cB = 0;
int ccR = 0;
int ccG = 0;
int ccB = 0;
int pixelX = 0;
int pixelY = 0;
int pixelcount = 0;
//uint16_t xx = "0x";
String xx = "0x";
uint16_t WHITE = 0xffffff;
uint16_t BLACK = 0x000000;
uint16_t red = 0xfff000;                    //限界
uint16_t green = matrix.Color333(0, 7, 0);  //満タン
uint16_t Yellow = 0xffff00;                 //半分*/
uint16_t Blue = 0x0000ff;
uint16_t orange = 0xffa00;
uint16_t rightgreen = matrix.Color333(3, 3, 0);  //満タン
int16_t tx = 0;
int16_t ty = 0;
const char frag = 'h';
char Buf[50];
uint16_t num = 0;


uint16_t car_sample[21][32]{
  { 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE, 0, 0, 0, 0 },
  { 0, 0, 0, WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE, 0, 0, 0 },
  { 0, 0, WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE, 0, 0 },
  { 0, WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE, 0 },
  { WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE },
  { WHITE, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, Blue, WHITE },
  { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE },
  { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE },
  { WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE },
  { 0, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, 0 },
  { 0, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, 0 },
  { 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, Yellow, Yellow, Yellow, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0 },
  { 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0 },
  { 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0 },
  { 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0 },
  { 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0 },
  { 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0 },
  { 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, 0, 0, 0, 0, WHITE, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, WHITE, WHITE, WHITE, WHITE, 0, 0, 0, 0, 0 },

};



uint16_t Image_Buffer[32][32] = {
  //カメラ画像を格納する配列
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },



};







 



void receiveEvent(int howMany) {

  while (WireSlave.available())  // loop through all but the last byte
  {

    //ヘッダの文字が出たらその処理を始める
    //その処理をしてみるのはどう？

    if (WireSlave.read() == frag) {
      cR = WireSlave.read();  //uint8_t型のRed値を読み取り color565
      cG = WireSlave.read();  //uint8_t型のGreen値を読み取り color565
      cB = WireSlave.read();  //uint8_t型のBlue値を読み取り color565
      ccR = cR;
      ccG = cG;
      ccB = cB;
      int tx =  WireSlave.read(); 
      int ty =  WireSlave.read(); 


      

      //////////////受け取ったそれぞれのRGB値をいじるところ/////////////////////

      //rgbを文字列につなげる
      //int rgb_set = RGB.toInt();             //intに変換
      String r = String(cR);     
      String g = String(cG);     
      String b = String(cB);
      String rgb = r + g + b;
      uint16_t rgb_set = rgb.toInt(); //10進数
  

      String rgb_16x = String(rgb_set,HEX); 
      rgb_16x.toCharArray(Buf, 50);//bufに入っている
      //rgb.toCharArray(Buf, 50);//bufに入っている
      num = rgb_16x.toInt();

      //char* y = Buf;
     
      //sscanf(Buf, "%x", num);
      


      //uint16_t rgbtest = rgb_16x.toInt();//ここで値が変
      //uint16_t bb = Buf.toInt();
    

  
    Serial.print("rgb = ");  //デバック用
    Serial.println(rgb);       //デバック用
    Serial.print("rgbset = ");          //デバック用
    Serial.println(rgb_set);             //デバック用
    Serial.print("rgb_16x = "); //文字列16進数         //デバック用
    Serial.println(rgb_16x);             //デバック用
    Serial.print("Buf = "); //char 16進数         //デバック用
    Serial.println(Buf);   
    Serial.print("u = ");   //int 16進数       //デバック用
    Serial.println(num);   
 

      //////////////////////////////////////////////////////////////////////////

      ///////////////受け取ったそれぞれのRGB値をカラーコードに変換し、32*32の配列に入れる///////////////


      //Image_Buffer[ty][tx] = Buf ;
        /*Serial.print("Image_Buffer[");
          Serial.print(ty);
          Serial.print("][");
          Serial.print(tx);
          Serial.print("]=");
          Serial.println(Image_Buffer[ty][tx]);*/
      //Image_Buffer[pixelY][pixelX] = matrix.Color444(cR, cG, cB);  //配列の各ピクセルのからコードを格納
      //Image_Buffer[pixelY][pixelX] = ;  //配列の各ピクセルのからコードを格納
      //Serial.print("matrix.color444 = ");                        //デバック用
      //Serial.println( matrix.Color444(cR, cG, cB));                 //デバック用
      //matrix.drawRGBBitmap(0, 0, Image_Buffer[0], 32, 32);  //LEDmatrixPanelにカメラ画像を表示

      /////////////////////////////////////////////////////////////////////////////////////////////////

      pixelcount++;

      if (pixelcount % 1024 == 0) {
        for (int j = 0; j < 32; j++) {
          for (int i = 0; i < 32; i++) {

            /////////////デバック用////////////////////////

            /*Serial.print("Image_Buffer[");
          Serial.print(j);
          Serial.print("][");
          Serial.print(i);
          Serial.print("]=");
          Serial.println(Image_Buffer[i][j]);*/


            ///////////////////////////////////////////////
          }
        }
        pixelY = 0;
        pixelX = 0;
        pixelcount = 0;
        //matrix.drawRGBBitmap(0, 0, Image_Buffer[0], 32, 32);  //LEDmatrixPanelにカメラ画像を表示

      } else if (pixelcount % 32 == 0) {

        pixelY++;
        pixelX = 0;

      } else {
        pixelX++;
      }
    }
  }
}






