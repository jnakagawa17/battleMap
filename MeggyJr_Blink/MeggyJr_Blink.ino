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
int hover = 6;
int paused = 0;
int savedState = 0;
int lightsHover = 0;
int placeHolder = 0;
int section = 0;
int availabilityCounter = 0; 

int lightsToggle[2] = {0, 0};

int choice[6] = {1, 2, 3, 1, 2, 3};

int selected[2] = {0, 10};

int defended[6] = {0, 0, 0, 0, 0, 0};

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

Point attackButton = {7, 6};
Point healButton = {7, 4};
Point defenseButton = {7, 2};

Class t1 = {0, 0, 0, 0, {0, 7}};
Class t2 = {0, 0, 0, 0, {0, 4}};
Class t3 = {0, 0, 0, 0, {0, 1}};
Class t4 = {0, 0, 0, 0, {4, 7}};
Class t5 = {0, 0, 0, 0, {4, 4}};
Class t6 = {0, 0, 0, 0, {4, 1}};

Class Locations[6] = {t1, t2, t3, t4, t5, t6};

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
    initializeButtons();
    DisplaySlate();
    gameState = 3;
  }
  if (gameState == 3)
  {
    selector();
    redisplay();
    updateHealth();
    blinker();
    checkLights();
    rotate();
    DisplaySlate();
    delay(500);
    endTurn(); 
  }
  if (gameState == 4)
  {
    resetDefense();
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

void initializeButtons()
{
  DrawPx(attackButton.x, attackButton.y, Red);
  DrawPx(healButton.x, healButton.y, Green);
  DrawPx(defenseButton.x, defenseButton.y, Blue); 
}

void selector()
{ 
  if (section == 0)
  {
    CheckButtonsDown();
    if (Button_Up)
    {
      hover = hover - 1;
      if (hover < 6)
      {
        hover = hover + 1;
      }
    }
    if (Button_Down)
    {
      hover = hover + 1;
      if (hover > 8)
      {
        hover = hover - 1;
      }
    }  
    if (Button_A)
    {
      if (hover == 6)
      {
        section = 3;
        hover = 3;
      }
      if (hover == 7)
      {
        section = 5;
        hover = 0;
      }
      if (hover == 8)
      {
        section = 7;
        hover = 0;
      }
    }
  }
  if (section == 2)
  {
    CheckButtonsDown();
    if (Button_Up)
    {
      hover = hover - 1;
      if (hover == 2)
      {
        hover = 3;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover + 1;
        if (Locations[hover].health < 1)
        {
          hover = hover - 2;
        }
      }
    }
    if (Button_Down)
    {
      hover = hover + 1;
      if (hover > 5)
      {
        hover = hover - 1;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover - 1;
        if (Locations[hover].health < 1)
        {
          hover = hover + 2;
        }
      }
    }  
    if(Button_A)
    {  
      if (hover > 2)
      {
        selected[1] = hover;
        attackCalculations();
      }
    }
    if (Button_B)
    {
      section = 1;
      hover = 6;
    }
  }
  if (section == 4)
  {
    CheckButtonsDown();
    if (Button_Up)
    {
      hover = hover - 1;
      if (hover < 0)
      {
        hover = hover + 1;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover + 1;
        if (Locations[hover].health < 1)
        {
          hover = hover - 2;
        }
      }
    }
    if (Button_Down)
    {
      hover = hover + 1;
      if (hover == 3)
      {
        hover = hover - 1;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover - 1;
        if (Locations[hover].health < 1)
        {
          hover = hover + 2;
        }
      }
    }  
    if(Button_A)
    {  
      if (hover < 3)
      {
        selected[0] = hover;
      }
      if (hover > 2)
      {
        selected[1] = hover;
      }
    }
    if (Button_B)
    {
      section = 1;
      hover = 6;
    }
  }
  if (section == 6)
  {
    CheckButtonsDown();
    if (Button_Up)
    {
      hover = hover - 1;
      if (hover < 0)
      {
        hover = hover + 1;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover + 1;
        if (Locations[hover].health < 1)
        {
          hover = hover - 2;
        }
      }
    }
    if (Button_Down)
    {
      hover = hover + 1;
      if (hover == 3)
      {
        hover = hover - 1;
      }
      if (Locations[hover].health < 1)
      {
        hover = hover - 1;
        if (Locations[hover].health < 1)
        {
          hover = hover + 2;
        }
      }
    }  
    if(Button_A)
    {  
      if (hover < 3)
      {
        selected[0] = hover;
      }
      if (hover > 2)
      {
        selected[1] = hover;
      }
    }
    if (Button_B)
    {
      section = 1;
      hover = 6;
    }
  }
  if (section == 1)
  {
    section = 0;
  }
  if (section == 3)
  {
    section = 2;
  }
  if (section == 5)
  {
    section = 4;
  }
  if (section == 7)
  {
    section = 6;
  }
}

void blinker()
{  
  if (hover < 3)
  {
    if (lightsHover == 0)
    {
      if (choice[hover] == 1)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Green);
        lightsHover = 1;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Green);  
        lightsHover = 1;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Green);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Green);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Green);
        lightsHover = 1;
      }
    }
    if (lightsHover == 2)
    {
      if (choice[hover] == 1)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0); 
        lightsHover = 3;
      }
      if (choice[hover] == 2)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);    
        lightsHover = 3;
      }
      if (choice[hover] == 3)
      {
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
        DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
        DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0); 
        lightsHover = 3;
      }
    }
  }
  if (hover > 2)
  {
    if (hover < 6)
    {
      if (lightsHover == 0)
      {
        if (choice[hover] == 1)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Red);
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Red);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Red);
          lightsHover = 1;
        }
        if (choice[hover] == 2)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, Red);
          lightsHover = 1;
        }
        if (choice[hover] == 3)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, Red);
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, Red);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, Red);
          lightsHover = 1;
        }
      }
      if (lightsHover == 2)
      {
        if (choice[hover] == 1)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0);
          lightsHover = 3;
        }
        if (choice[hover] == 2)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y, 0);
          lightsHover = 3;
        }
        if (choice[hover] == 3)
        {
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y, 0);
          DrawPx(Locations[hover].p1.x, Locations[hover].p1.y - 1, 0);
          DrawPx(Locations[hover].p1.x + 1, Locations[hover].p1.y - 1, 0);
          lightsHover = 3;
        }
      }
    }
    if (hover == 6)
    {
      if (lightsHover == 0)
      {
        Serial.print("in lights 0"); 
        DrawPx(attackButton.x, attackButton.y, Red); 
        lightsHover = 1;
      }
      if (lightsHover == 2)
      {
        Serial.print("in lights 2"); 
        DrawPx(attackButton.x, attackButton.y, 0); 
        lightsHover = 3;
      }
    }
    if (hover == 7)
    {
      if (lightsHover == 0)
      {
        DrawPx(healButton.x, healButton.y, Green); 
        lightsHover = 1;
      }
      if (lightsHover == 2)
      {
        DrawPx(healButton.x, healButton.y, 0); 
        lightsHover = 3;
      }
    }
    if (hover == 8)
    {
      if (lightsHover == 0)
      {
        DrawPx(defenseButton.x, defenseButton.y, Blue); 
        lightsHover = 1;
      }
      if (lightsHover == 2)
      {
        DrawPx(defenseButton.x, defenseButton.y, 0); 
        lightsHover = 3;
      }
    }
  }
  if (lightsHover == 1)
  {
    lightsHover = 2;
  }
  if (lightsHover == 3)
  {
    lightsHover = 0;
  }  
}

void updateHealth()
{
  Serial.print(selected[1]);  
  Serial.print("updateHealth");  
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
  Serial.print(selected[1]);  
  Serial.print("redisplay");  
  for (int i = 0; i < 3; i++)
  {
    if (ReadPx(0, 7 - (3 * i)) == 0)
    {
      if (selected[0] != i)
      {
        if (Locations[i].health > 0)
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
  }
  for (int i = 3; i < 6; i++)
  {
    if (ReadPx(3, 16 - (3 * i)) == 0)
    {
      if (selected[1] != i)
      {
        if (Locations[i].health > 0)
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
  for (int i = 1; i < 4; i++)
  {
    if (ReadPx(7, 2 * i) == 0)
    {
      if (hover != 9 - i)
      {
        if (i == 3)
        {
          DrawPx(7, 2 * i, Red);
        }
        if (i == 2)
        {
          DrawPx(7, 2 * i, Green);
        }
        if (i == 1)
        {
          DrawPx(7, 2 * i, Blue);
        }
      }
    }
  }
  DisplaySlate(); 
}

void checkLights()
{
  Serial.print(selected[1]);  
  Serial.print("checkLights");  
  for (int i = 0; i < 2; i++)
  {
    if (selected[i] < 7)
    {
      if (ReadPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y) == 0)
      {
        lightsToggle[i] = 0;
      }
      else
      {
        lightsToggle[i] = 2;
      }
    }
  }
}

void rotate()
{ 
  for (int i = 0; i < 2; i++)
  {
    if (selected[i] < 7)
    { 
      if (selected[i] != hover)
      {
        if (selected[i] < 3)
        {
          if (lightsToggle[i] == 0)
          { 
            if (choice[selected[i]] == 1)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Green);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, Green);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, Green);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, Green);
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 2)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Green);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, Green);  
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 3)
            { 
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Green);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, Green);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, Green);
              lightsToggle[i] = 1;
            }
          }
          if (lightsToggle[i] == 2)
          {
            if (choice[selected[i]] == 1)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, 0);
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 2)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, 0);  
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 3)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, 0);
              lightsToggle[i] = 1;
            }
          }
        }
        if (selected[i] > 2)
        {
          if (lightsToggle[i] == 0)
          {
            if (choice[selected[i]] == 1)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Red);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, Red);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, Red);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, Red);
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 2)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Red);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, Red);  
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 3)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, Red);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, Red);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, Red);
              lightsToggle[i] = 1;
            }
          }
          if (lightsToggle[i] == 2)
          {
            if (choice[selected[i]] == 1)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, 0);
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 2)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y, 0);  
              lightsToggle[i] = 1;
            }
            if (choice[selected[i]] == 3)
            {
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y, 0);
              DrawPx(Locations[selected[i]].p1.x, Locations[selected[i]].p1.y - 1, 0);
              DrawPx(Locations[selected[i]].p1.x + 1, Locations[selected[i]].p1.y - 1, 0);
              lightsToggle[i] = 1;
            }
          }
        }
      }
    }
    if (lightsToggle[i] == 1)
    {
      lightsToggle[i] = 2;
    }
    if (lightsToggle[i] == 3)
    {
      lightsToggle[i] = 0;
    } 
  }
}

void attackCalculations()
{
  if (selected[1] < 6)
  {
    placeHolder = Locations[selected[1]].health - Locations[selected[0]].attack + Locations[selected[1]].defense; 
    if (placeHolder < Locations[selected[1]].health)
    {
      Locations[selected[1]].health = placeHolder; 
    }
  }
  selected[0] = selected[0] + 1; 
  selected[1] = 10;
  section = 0;
  hover = 6;
}

void defenseCalculations()
{
  Locations[selected[0]].defense = Locations[selected[0]].defense + 2;
  defended[selected[0]] = 1;
  selected[0] = selected[0] + 1; 
  selected[1] = 10;
  section = 0;
  hover = 6; 
}

void attackAnimation()
{

}

void healingCalculations()
{
  Locations[selected[0]].health = Locations[selected[0]].health + 1;
  if (choice[selected[0]] == 1)
  {
    if (Locations[selected[0]].health > 8)
    {
      Locations[selected[0]].health = 8;
    }
  }
  if (choice[selected[0]] == 2)
  {
    if (Locations[selected[0]].health > 4)
    {
      Locations[selected[0]].health = 4;
    }
  }
  if (choice[selected[0]] == 3)
  {
    if (Locations[selected[0]].health > 6)
    {
      Locations[selected[0]].health = 6;
    }
  }
  selected[0] = selected[0] + 1; 
  selected[1] = 10;
  section = 0;
  hover = 6;
}

void endTurn()
{
  if (selected[0] == 4)
  {
    gameState = 4;
    alterDefense();
  }
}

void resetDefense()
{
  for (int i = 0; i < 3; i++)
  {
    if (defended[i] == 1)
    {
      Locations[i].defense = Locations[i].defense - 2;
    }
  }
}

void alterDefense()
{
  for (int i = 3; i < 6; i++)
  {
    if (defended[i] == 1)
    {
      Locations[i].defense = Locations[i].defense - 2;
    }
  }
}

