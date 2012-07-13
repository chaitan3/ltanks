/*
 *      play.h
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

#ifndef PLAY_H
#define PLAY_H

#define UP      1
#define DOWN    2
#define LEFT    3
#define RIGHT   4

void Tank_Move(Uint8 );
void Shoot_Laser(Uint8);
int Shoot_Laser_AntiTank();
void Object_Move(Uint8 ,Uint8 ,Uint8 );
void Check_Ride();
void Check_Ice_Ride(Uint8 *,Uint8 *);
Uint8 Check_Line_Of_Fire();
void Check_Wormhole(Uint8 *,Uint8 *);
Uint8 Check_Mirrors(unsigned int *,unsigned int *,Uint8 *);
Uint8 Next_Rotating_Mirror(Uint8 );
Uint8 isObstacle(Uint8 );
Uint8 Laser_isObstacle(Uint8 );
void Undo();
void Make_Undo();
void Increase_Moves();
void Find_Laser_Pos();

struct LaserShot {
	Uint8 r_x;
	Uint8 r_y;
	unsigned int x;
	unsigned int y;
	Uint8 dir;
	Uint8 running;
};

#endif
