/*
  MeggyJr_Blink.pde
 
 Example file using the The Meggy Jr Simplified Library (MJSL)
  from the Meggy Jr RGB library for Arduino
   
 Blink a damned LED.
   
   
 
 Version 1.25 - 12/2/2008
 Copyright (c) 2008 Windell H. Oskay.  All right reserved.
 http://www.evilmadscientist.com/
 
 This library is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this library.  If not, see <http://www.gnu.org/licenses/>.
 	  
 */

 
 
 
 

/*
 * Adapted from "Blink,"  The basic Arduino example.  
 * http://www.arduino.cc/en/Tutorial/Blink
 */

#include <MeggyJrSimple.h>    // Required code, line 1 of 2.
int heading = 0; // possible values are 0, 1, 2, 3
int xApple = random (8);
int yApple = random (8);
int marker = 4;

struct Point
{
  int xPlayer; // coordinates of player dot
  int yPlayer;
};

Point p1 = {3, 4};
Point p2 = {4, 4};
Point p3 = {5, 4};

Point snakeArray[64] = {p1, p2, p3};

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
  Serial.begin(9600);
}


void loop()                     // run over and over again
{
  /*
  Draw Player
  Display Slate
  Check Buttons
  Update direction if a button is pressed
  Update player based on direction
  Correct for wrap
  */
  ClearSlate();
  drawApple();
  drawSnake();
  DisplaySlate();
  delay(300);
  directions();
  checkApple();
  updateSnake();
  moveHead();

}

void drawSnake()
{
  for(int i = 0; i < marker; i++)
  {
    DrawPx(snakeArray[i].xPlayer, snakeArray[i].yPlayer, Blue);
  }
}

void directions()
{
  CheckButtonsPress();
  if(Button_Left)
  {
    heading = 3;
  }
  if(Button_Right)
  {
    heading = 1;
  }
  if(Button_Down)
  {
    heading = 2;
  }
  if(Button_Up)
  {
    heading = 0;
  }
}

void moveHead()
{
  if(heading == 0)
  {
    if(snakeArray[0].yPlayer < 7)
    {
      snakeArray[0].yPlayer = snakeArray[0].yPlayer + 1;
    }
    else
    snakeArray[0].yPlayer = 0;
  }
  if(heading == 1)
  {
    if(snakeArray[0].xPlayer < 7)
    {
      snakeArray[0].xPlayer = snakeArray[0].xPlayer + 1;
    }
    else
    snakeArray[0].xPlayer = 0;
  }
  if(heading == 2)
  {
    if(snakeArray[0].yPlayer > 0)
    {
      snakeArray[0].yPlayer = snakeArray[0].yPlayer - 1;
    }
    else
    snakeArray[0].yPlayer = 7;
  } 
  if(heading == 3)
  {
    if(snakeArray[0].xPlayer > 0)
    {
      snakeArray[0].xPlayer = snakeArray[0].xPlayer - 1;
    }
    else
    snakeArray[0].xPlayer = 7;
  } 
}

void drawApple()
{
  DrawPx(xApple, yApple, Red);
}

void checkApple()
{
  if (xApple == snakeArray[0].xPlayer) 
  {
    if (yApple == snakeArray[0].yPlayer)
    {
      xApple = random (8);
      yApple = random (8);
      marker = marker + 1;
      drawApple();
    }
  }
}

void updateSnake()
{
  for(int i = marker - 1; i > 0; i--)
  {
    snakeArray[i] = snakeArray[i - 1];
  }
}
