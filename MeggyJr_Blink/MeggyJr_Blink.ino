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

struct Point
{
  int x; // coordinates of a dot
  int y;
};

struct Heavy
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
  Point p2;
  Point p3;
  Point p4;
};

Heavy t1 = {8, 6, 3, 1, {0, 7}, {0, 6}, {1, 7}, {1, 6}};
Heavy t2 = {8, 6, 3, 1, {0, 3}, {0, 4}, {1, 3}, {1, 4}};
Heavy t3 = {8, 6, 3, 1, {0, 0}, {0, 1}, {1, 0}, {1, 1}};
Heavy t4 = {8, 6, 3, 1, {3, 7}, {3, 6}, {4, 7}, {4, 6}};
Heavy t5 = {8, 6, 3, 1, {3, 3}, {3, 4}, {4, 3}, {4, 4}};
Heavy t6 = {8, 6, 3, 1, {3, 0}, {3, 1}, {4, 0}, {4, 1}};

Heavy tankLocations[6] = {t1, t2, t3, t4, t5, t6};

struct Light
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
  Point p2;
};

Light l1 = {8, 6, 3, 1, {0, 7}, {1, 7}};
Light l2 = {8, 6, 3, 1, {0, 4}, {1, 4}};
Light l3 = {8, 6, 3, 1, {0, 1}, {1, 1}};
Light l4 = {8, 6, 3, 1, {3, 7}, {4, 7}};
Light l5 = {8, 6, 3, 1, {3, 4}, {4, 4}};
Light l6 = {8, 6, 3, 1, {3, 1}, {4, 1}};

Light scoutLocation[6] = {l1, l2, l3, l4, l5, l6};

struct Special
{
  int health;
  int defense;
  int attack;
  int availability; 
  Point p1;
  Point p2;
  Point p3;
  Point p4;
};

Special t1 = {8, 6, 3, 1, {0, 7}, {0, 6}, {1, 7}, {1, 6}};
Special t2 = {8, 6, 3, 1, {0, 3}, {0, 4}, {1, 3}, {1, 4}};
Special t3 = {8, 6, 3, 1, {0, 0}, {0, 1}, {1, 0}, {1, 1}};
Special t4 = {8, 6, 3, 1, {3, 7}, {3, 6}, {4, 7}, {4, 6}};
Special t5 = {8, 6, 3, 1, {3, 3}, {3, 4}, {4, 3}, {4, 4}};
Special t6 = {8, 6, 3, 1, {3, 0}, {3, 1}, {4, 0}, {4, 1}};

Heavy tankLocations[6] = {t1, t2, t3, t4, t5, t6};


void setup()                    // run once, when the sketch starts
{
  MeggyJrSimpleSetup();      // Required code, line 2 of 2.
}

void loop()                     // run over and over again
{
  

}


