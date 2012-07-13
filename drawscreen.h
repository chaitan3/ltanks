/*
 *      drawscreen.h
 *      
 *      Copyright 2009 Chaitanya Talnikar<chaitukca@gmail.com>
 *      
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 3 of the License.
 *      
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      
 *      You should have received a copy of the GNU General Public License
 *       along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/*

Obj			BitM	Description
---     	----    -----------

0 			1		Dirt
1 			2		Tank Up ( Primary )
-			3		Tank Right
-			4		Tank Down
-			5		Tank left
2			6		Base ( Primary)
-			7		Base Alt ( animation )
-			8		Base Alt2
3			9		Water ( Primary )
-			10		Water Alt
-			11		Water Alt 2
-       	12  	Blown Up Anti Tank (down)
4			13		Solid Block NOT movable
5			14		Movable Block
6			15		Bricks
7			16		Anti-Tank Gun Up
-			17		Anti-Tank Alt
-			18		Anti-Tank Alt 2
-			19	    Movable block after pushing into water
11			20		Mirror Up-Lt
12			21		Mirror Up-Rt
13			22		Mirror Dn-Rt
14			23		Mirror Dn-Lt
15			24		One Way Up (Primary)
-			25		One Way Up Alt
-			26		One Way Up Alt2
16			27		One Way Rt (Primary)
-			28		One Way Rt Alt
-			29		One Way Rt Alt2
17			30		One Way Dn (Primary)
-			31		One Way Dn Alt
-			32		One Way Dn Alt2
18			33		One Way Lt (Primary)
-			34		One Way Lt Alt
-			35		One Way Lt Alt2
8 	      	36      Anti-Tank facing right
- 	      	37
- 	      	38
9       	39      Anti-Tank facing down
-       	40
-       	41
10      	42      Anti-Tank facing left
-       	43
-       	44
19      	45      Crystal Block
-       	46      Crystal when hit by tank
20			47		Roto Mirror Up-Lt
21			48		Roto Mirror Up-Rt
22			49		Roto Mirror Dn-Rt
23			50		Roto Mirror Dn-Lt
-       	51      Crystal when hit by Anti-tank
-       	52      Blown Up Anti Tank (right)
-       	53      Blown Up Anti Tank (left)
-       	54      Blown Up Anti Tank (up)
24			56		Ice
25			57		Thin Ice
01dddddx	55		Worm Hole / Tunnel

*/

#ifndef DRAWSCREEN_H
#define DRAWSCREEN_H

#include<SDL/SDL_ttf.h>
#include "play.h"

void Load_Level(int );
Uint8 Load_Next_Level();
Uint8 Load_Previous_Level();  
void Draw_Update();
void Redraw();
void Draw_Laser_Shot();
void Clear_Laser_Shot();
void Draw_Tile(Uint8 ,Uint8 );

struct Block {
    Uint8 main;
    Uint8 top;
};

struct CurrentStatus{
    int cur_level;
    struct Block blocks[16][16];
    Uint8 tank_x,tank_y;
    Uint8 orientation;
    unsigned int moves;
    unsigned int shots;
};

struct Screen{
    SDL_Surface *screen;
    TTF_Font *font;
};

extern struct CurrentStatus cur_stat,undo_stat[10];
extern struct Screen scr;
extern int undo_index;
extern Uint8 undo_count;
extern struct LaserShot laser_shot;
#endif

