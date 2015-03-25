/*
 *      drawscreen.c
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

#include "loadfile.h"
#include "drawscreen.h"
#include "play.h"

void Load_Level(int lvl)
{
    
    Uint8 i,j;
    
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            switch(level[lvl].grid[i][j])
            {
                case 0:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 1:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=2;
                    cur_stat.tank_x=i;
                    cur_stat.tank_y=j;
                    break;
                case 2:
                    cur_stat.blocks[i][j].main=6;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 3:
                    cur_stat.blocks[i][j].main=9;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 4:
                    cur_stat.blocks[i][j].main=13;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 5:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=14;
                    break;
                case 6:
                    cur_stat.blocks[i][j].main=15;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 7:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=16;
                    break;
                case 8:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=36;
                    break;
                case 9:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=39;
                    break;
                case 10:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=42;
                    break;
                case 11:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=20;
                    break;    
                case 12:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=21;
                    break;
                case 13:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=22;
                    break;
                case 14:
                    cur_stat.blocks[i][j].main=1;
                    cur_stat.blocks[i][j].top=23;
                    break;
                case 15:
                    cur_stat.blocks[i][j].main=24;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 16:
                    cur_stat.blocks[i][j].main=27;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 17:
                    cur_stat.blocks[i][j].main=30;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 18:
                    cur_stat.blocks[i][j].main=33;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 19:
                    cur_stat.blocks[i][j].main=45;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 20:
                    cur_stat.blocks[i][j].main=47;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 21:
                    cur_stat.blocks[i][j].main=48;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 22:
                    cur_stat.blocks[i][j].main=49;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 23:
                    cur_stat.blocks[i][j].main=50;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 24:
                    cur_stat.blocks[i][j].main=56;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 25:
                    cur_stat.blocks[i][j].main=57;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 64:
                    cur_stat.blocks[i][j].main=63;
                    cur_stat.blocks[i][j].top=55;
                    break;
                case 66:
                    cur_stat.blocks[i][j].main=64;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 68:
                    cur_stat.blocks[i][j].main=65;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 70:
                    cur_stat.blocks[i][j].main=66;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 72:
                    cur_stat.blocks[i][j].main=67;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 74:
                    cur_stat.blocks[i][j].main=68;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 76:
                    cur_stat.blocks[i][j].main=69;
                    cur_stat.blocks[i][j].top=0;
                    break;
                case 78:
                    cur_stat.blocks[i][j].main=70;
                    cur_stat.blocks[i][j].top=0;
                    break;
            }
        }
    }
    cur_stat.orientation=UP;
    cur_stat.moves=0;
    cur_stat.shots=0;
    for(i=0;i<10;i++)
        undo_stat[i].cur_level=-1;
    cur_stat.cur_level=lvl;
    undo_count=0;
    undo_index=0;
	laser_shot.running=0;
}

void Draw_Update()
{
    int i,j;
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
            Draw_Tile(i,j);
    }
}

void Redraw()
{
    SDL_UpdateTexture(scr.texture, NULL, scr.screen->pixels, scr.screen->pitch);
    SDL_RenderClear(scr.renderer);
    SDL_RenderCopy(scr.renderer, scr.texture, NULL, NULL);
    SDL_RenderPresent(scr.renderer);
}

void Draw_Laser_Shot()
{
    SDL_Rect dest;
    Uint8 bit;
    
	if(laser_shot.running)
	{
		dest.x=laser_shot.y;
		dest.y=laser_shot.x;
		
		if(laser_shot.dir==UP || laser_shot.dir==DOWN)
			bit=60;
		else
			bit=61;
				
		SDL_BlitSurface(Bitmaps[bit],NULL,scr.screen,&dest);
		
		//SDL_UpdateRect(scr.screen,dest.x,dest.y,Bitmaps[bit]->w,Bitmaps[bit]->h);
	}
    Redraw();
}

void Clear_Laser_Shot()
{
	SDL_Rect dest;
	int r_x,r_y;
	if(laser_shot.running)
	{
		r_x=laser_shot.x/config_file.tile_size;
		r_y=laser_shot.y/config_file.tile_size;
		dest.w=config_file.tile_size;
		dest.h=config_file.tile_size;
		Draw_Tile(r_x,r_y);
		dest.x=r_y*config_file.tile_size;
		dest.y=r_x*config_file.tile_size;
		//SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
		switch(laser_shot.dir)
		{
			case UP:
			r_x--;
			break;
			case DOWN:
			r_x++;
			break;
			case LEFT:
			r_y--;
			break;
			case RIGHT:
			r_y++;
			break;
		}
		if(r_x>=0 && r_x<=15 && r_y>=0 && r_y<=15)
		{
			Draw_Tile(r_x,r_y);
			dest.x=r_y*config_file.tile_size;
			dest.y=r_x*config_file.tile_size;
		}
		//SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
	}	
    Redraw();
}

void Draw_Tile(Uint8 i,Uint8 j)
{
    long int pitch,pitch_t;
    unsigned int x=0;
    Uint8 r,g,b,bpp,bpp_t,m,n;
    SDL_Rect dest;
            
    dest.x=config_file.tile_size*j;
    dest.y=config_file.tile_size*i;
    SDL_BlitSurface(Bitmaps[cur_stat.blocks[i][j].main-1], NULL, scr.screen, \
        &dest);
        
    if(cur_stat.blocks[i][j].top>0)
    {
        SDL_LockSurface(scr.screen);
        pitch=Mask[cur_stat.blocks[i][j].top-1]->pitch;
        pitch_t=scr.screen->pitch;
        bpp=Mask[cur_stat.blocks[i][j].top-1]->format->BytesPerPixel;
        bpp_t=scr.screen->format->BytesPerPixel;
        
        for(m=0;m<config_file.tile_size;m++)
        {
            for(n=0;n<config_file.tile_size;n++)
            {
                r=*(Uint8 *) (Mask[cur_stat.blocks[i][j].top-1]->pixels \
                +n*pitch +m*bpp);
                
                g=*(Uint8 *) (Mask[cur_stat.blocks[i][j].top-1]->pixels \
                +n*pitch +m*bpp+1);
        
                b=*(Uint8 *) (Mask[cur_stat.blocks[i][j].top-1]->pixels \
                +n*pitch +m*bpp+2);
                if(r==0 && g==0 && b==0)
                {
                    *(Uint8 *) (scr.screen->pixels +(n+dest.y)*pitch_t \
                        +(m+dest.x)*bpp_t)=*(Uint8 *) \
                        (Bitmaps[cur_stat.blocks[i][j].top-1]->pixels \
                        +n*pitch +m*bpp);
                    
                    *(Uint8 *) (scr.screen->pixels +(n+dest.y)*pitch_t \
                        +(m+dest.x)*bpp_t+1)=*(Uint8 *) \
                        (Bitmaps[cur_stat.blocks[i][j].top-1]->pixels \
                        +n*pitch +m*bpp+1);
                    
                    *(Uint8 *) (scr.screen->pixels +(n+dest.y)*pitch_t \
                        +(m+dest.x)*bpp_t+2)=*(Uint8 *) \
                        (Bitmaps[cur_stat.blocks[i][j].top-1]->pixels \
                        +n*pitch +m*bpp+2);
                }
                else if(r==255 && g==255 && b==255)
                    x++;
            }
        }
        SDL_UnlockSurface(scr.screen);
    }
    if(x==config_file.tile_size*config_file.tile_size)
        SDL_BlitSurface(Bitmaps[cur_stat.blocks[i][j].top-1], NULL, scr.screen, \
            &dest);
}

Uint8 Load_Next_Level()
{
    int x;
    x=cur_stat.cur_level;
    do
    {
        cur_stat.cur_level++;
        if(cur_stat.cur_level>=numlevels-1)
        {
            cur_stat.cur_level=x;
            return 0;
        }
        if(config_file.difficulty>0)
        {
            if(level[cur_stat.cur_level].difficulty==config_file.difficulty)
                return 1;
        }
        else
            return 1;
    }while(1);
}

Uint8 Load_Previous_Level()
{
    int x;
    x=cur_stat.cur_level;
    do
    {
        cur_stat.cur_level--;
        if(cur_stat.cur_level<0)
        {
            cur_stat.cur_level=x;
            return 0;
        }
        if(config_file.difficulty>0)
        {
            if(level[cur_stat.cur_level].difficulty==config_file.difficulty)
                return 1;
        }
        else
            return 1;
    }while(1);
}
