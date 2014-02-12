/*
 *      loadfile.h
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

#ifndef LOADFILE_H
#define LOADFILE_H

#include "common.h"

void Load_Levels();
void Load_Bitmaps(SDL_RWops *,SDL_RWops*);
void Load_LTG();
void Load_Config();
char fgetc_nw(FILE *);
void SDL_FillRect_wBorder(SDL_Surface *,SDL_Rect *,Uint32 );
void Unload();

struct levels{
    Uint8 grid[16][16];
    char author[31];
    char hint[256];
    char name[31];
    Uint8 difficulty;
};

struct LTGheader	
{
	char name[40];		
	char author[30];	
	char info[245];		
	char id[5];			
	Uint32 maskoffset;
};

struct Config 
{
    char ltg_file[100];
    char level_file[100];
    Uint8 difficulty;
    unsigned int scaled_size;
	unsigned int tile_size;
	Uint8 scaling;
};

extern int numlevels;
extern struct levels *level;
extern SDL_Surface *Bitmaps[71],*Mask[60];
extern struct Config config_file;
#endif
