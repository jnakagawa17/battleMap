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
int gameState = 2;
int hover = 0;
int paused = 0;
int savedState = 0;
int lights = 0;

int choice[6] = {1, 2, 3, 1, 2, 3};

int selected[2] = {9, 9};

struct Point
{
  int x; // coordinates of a dot
  int y;
};

struct Class
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
};

struct Space
{
  Point p1;
  Point p2;
  Point p3;
  Point p4;
};

Class t1 = {0, 0, 0, 0, {0, 7}};
Class t2 = {0, 0, 0, 0, {0, 4}};
Class t3 = {0, 0, 0, 0, {0, 1}};
Class t4 = {0, 0, 0, 0, {3, 7}};
Class t5 = {0, 0, 0, 0, {3, 4}};
Class t6 = {0, 0, 0, 0, {3, 1}};

Class Locations[6] = {t1, t2, t3, t4, t5, t6};

int field[6];
/*
struct Light
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
  Point p2;
};

struct Special
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
  Point p2;
  Point p3;
};

Light l1 = {8, 6, 3, 1, {0, 7}, {1, 7}};
Light l2 = {8, 6, 3, 1, {0, 4}, {1, 4}};
Light l3 = {8, 6, 3, 1, {0, 1}, {1, 1}};
Light l4 = {8, 6, 3, 1, {3, 7}, {4, 7}};
Light l5 = {8, 6, 3, 1, {3, 4}, {4, 4}};
Light l6 = {8, 6, 3, 1, {3, 1}, {4, 1}};

Special s1 = {8, 6, 3, 1, {0, 7}, {0, 6}, {1, 6}};
Special s2 = {8, 6, 3, 1, {0, 3}, {0, 4}, {1, 3}};
Special s3 = {8, 6, 3, 1, {0, 0}, {0, 1}, {1, 0}};
Special s4 = {8, 6, 3, 1, {3, 6}, {4, 7}, {4, 6}};
Special s5 = {8, 6, 3, 1, {3, 3}, {4, 3}, {4, 4}};
Special s6 = {8, 6, 3, 1, {3, 0}, {4, 0}, {4, 1}};


Light scoutLocation[6] = {l1, l2, l3, l4, l5, l6};

Special mageLocations[6] = {s1, s2, s3, s4, s5, s6};
*/

void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
  Serial.begin(9600);
}

void loop()                     // run over and over again
{
  if (gameState == 2)
  {
    initializeLocations();
    initializeStats();
    initializeHealth();
    DisplaySlate();
    gameState = 3;
  }
  if (gameState == 3)
  {
    Serial.print("Entered gamestate 3");
    selector();
    redisplay();
    updateHealth();
    blinker();
    DisplaySlate();
    delay(500);
  }
}

void initializeLocations()
{
  for (int i = 0; i < 3; i++)
  {
    if (choice[i] == 1)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Green);
      DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Green);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Green);
    }
    if (choice[i] == 2)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Green);
    }    
    if (choice[i] == 3)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
      DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Green);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Green);
    }  
  }
  for (int i = 3; i < 6; i++)
  {
    if (choice[i] == 1)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y, Red);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
      DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Red);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Red);
    }
    if (choice[i] == 2)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y, Red);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
    }    
    if (choice[i] == 3)
    {
      DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Red);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
      DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Red);
    }  
  }
}

void initializeStats()
{
  for (int i = 0; i < 6; i++)
  {
    if (choice[i] == 1)
    {
      Locations[i].health = 8;
      Locations[i].defense = 4;
      Locations[i].attack = 2;
      Locations[i].availability = 1;
    }
    if (choice[i] == 2)
    {
      Locations[i].health = 4;
      Locations[i].defense = 1;
      Locations[i].attack = 5;
      Locations[i].availability = 1;
    }    
    if (choice[i] == 3)
    {
      Locations[i].health = 6;
      Locations[i].defense = 3;
      Locations[i].attack = 3;
      Locations[i].availability = 1;
    }  
  }
}

void initializeHealth()
{
  if (choice[hover] == 1)
  {
    SetAuxLEDs(255); 
  }
  if (choice[hover] == 2)
  {
    SetAuxLEDs(15); 
  }    
  if (choice[hover] == 3)
  {
    SetAuxLEDs(63); 
  }  
}

void selector()
{
  CheckButtonsDown();
  if (Button_Right)
  {
    hover = hover + 3;
    if (hover > 5)
    {
      hover = hover - 3;
    }
  }
  if (Button_Left)
  {
    hover = hover - 3;
    if (hover < 0)
    {
      hover = hover + 3;
    }
  }
  if (Button_Up)
  {
    hover = hover - 1;
    if (hover < 0)
    {
      hover = hover + 1;
    }
    if (hover == 2)
    {
      hover = 4;
    }
  }
  if (Button_Down)
  {
    hover = hover + 1;
    if (hover > 5)
    {
      hover = hover - 1;
    }
    if (hover == 3)
    {
      hover = 3;
    }
  }  
  CheckButtonsDown();
  if(Button_A)
  {
    if (hover < 3)
    {
      selected[0] = hover;
    }
    if (hover > 2)
    {
      selected[0] = hover;
    }
  }
}

void blinker()
{
  Serial.print("Entered blinker");
  if (hover < 3)
  {
    if (lights == 0)
    {
      Serial.print("Entered lights true");
      if (choice[hover] == 1)
      {
       Serial.print("Entered hover is 1");
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Green);
        lights = 1;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Green);  
        lights = 1;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Green);
        lights = 1;
      }
    }
    if (lights == 2)
    {
    Serial.print("lights false");
      if (choice[hover] == 1)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0); 
        lights = 3;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);    
        lights = 3;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0); 
        lights = 3;
      }
    }
  }
  if (hover > 2)
  {
    if (lights == 0)
    {
      if (choice[hover] == 1)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Red);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Red);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Red);
        lights = 1;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Red);
        lights = 1;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Red);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Red);
        lights = 1;
      }
    }
    if (lights == 2)
    {
      if (choice[hover] == 1)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0);
        lights = 3;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
        lights = 3;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0);
        lights = 3;
      }
    }
  }
  if (lights == 1)
  {
    Serial.print("true to false");    
    lights = 2;
  }
  if (lights == 3)
  {
    Serial.print("false to true");   
    lights = 0;
  }  
}

void updateHealth()
{
  if (Locations[hover].health == 1)
  {
    SetAuxLEDs(1); 
  }
  if (Locations[hover].health == 2)
  {
    SetAuxLEDs(3); 
  }
  if (Locations[hover].health == 3)
  {
    SetAuxLEDs(7); 
  }
  if (Locations[hover].health == 4)
  {
    SetAuxLEDs(15); 
  }
  if (Locations[hover].health == 5)
  {
    SetAuxLEDs(31); 
  }
  if (Locations[hover].health == 6)
  {
    SetAuxLEDs(63); 
  }
  if (Locations[hover].health == 7)
  {
    SetAuxLEDs(127); 
  }
  if (Locations[hover].health == 8)
  {
    SetAuxLEDs(225); 
  }  
}

void redisplay()
{
  for (int i = 0; i < 3; i++)
  {
    if (ReadPx(0, 3 * i + 1) == 0)
    {
      if (selected[0] != i)
      {
        if (choice[i] == 1)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Green);
          DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Green);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Green);
        }
        if (choice[i] == 2)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Green);
        }    
        if (choice[i] == 3)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y, Green);
          DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Green);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Green);
        }          
      }
    }
  }
  for (int i = 3; i < 6; i++)
  {
    if (ReadPx(3, 3 * i - 8) == 0)
    {
      if (selected[1] != i)
      {
        if (choice[i] == 1)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y, Red);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
          DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Red);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Red);
        }
        if (choice[i] == 2)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y, Red);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
        }    
        if (choice[i] == 3)
        {
          DrawPx(Locations[i].p1.x, Locations[i].p1.y - 1, Red);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y, Red);
          DrawPx(Locations[i].p1.x + 1, Locations[i].p1.y - 1, Red);
        }          
      } 
    }
  }
}
