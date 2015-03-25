/*
 *      main.c
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

#include "common.h"
#include "loadfile.h"
#include "drawscreen.h"
#include "play.h"
#include "gui.h"

struct levels *level=NULL;
struct CurrentStatus cur_stat,undo_stat[10];
struct Screen scr;
struct Config config_file;
struct GUIButton gui_button[NUM_BUTTONS];
struct LaserShot laser_shot;
SDL_Surface *Bitmaps[71],*Mask[60];
int numlevels=0,undo_index;
Uint8 undo_count;

int main(int argc,char **argv)
{
    SDL_Event event;
    
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        printf("Unable to Initialise SDL: %s\n",SDL_GetError());
        exit(1);
    }
    if(TTF_Init()==-1)
    {
        printf("Unable to Initialise SDL_ttf: %s\n",TTF_GetError());
        exit(1);
    }
    
    config_file.difficulty=0;
    Load_Config();
		
	config_file.tile_size=32;
        int w = 512+188;
        int h = 512;
	
        SDL_Window* window = SDL_CreateWindow("LTanks", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, \
                             w, h, 0);
        scr.renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_RenderSetLogicalSize(scr.renderer, w, h);
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        scr.screen = SDL_CreateRGBSurface(0, w, h, 32,
                                        0x00FF0000,
                                        0x0000FF00,
                                        0x000000FF,
                                        0xFF000000);
        scr.texture = SDL_CreateTexture(scr.renderer,
                                            SDL_PIXELFORMAT_ARGB8888,
                                            SDL_TEXTUREACCESS_STREAMING,
                                            w, h);
        
    if(scr.renderer==NULL)
    {
        printf("Unable to Draw Screen: %s\n",SDL_GetError());
        exit(1);
    }
    scr.font=TTF_OpenFont("data/font.ttf",12);
    
    Load_SideBar_Buttons();      
    Load_Levels();
    Load_LTG();
    
    cur_stat.cur_level=-1;
    if(Load_Next_Level())
        Load_Level(cur_stat.cur_level);
    
    Draw_SideBar();
    Draw_Update();
    Redraw();
    
    while(1)
    {
        SDL_Delay(10);
        while(SDL_PollEvent(&event))
		{
			if(event.type==SDL_KEYDOWN)
			{	
				switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        Unload();
                    case SDLK_UP:
                        Tank_Move(UP);
                        break;
                    case SDLK_DOWN:
                        Tank_Move(DOWN);
                        break;
                    case SDLK_LEFT:
                        Tank_Move(LEFT);
                        break;
                    case SDLK_RIGHT:
                        Tank_Move(RIGHT);
                        break;
                    case SDLK_SPACE:
                        Make_Undo();
                        cur_stat.shots++;
                        Draw_SideBar();
                        Draw_Update();
                        Redraw();
                                laser_shot.r_x=cur_stat.tank_x;
				laser_shot.r_y=cur_stat.tank_y;
				laser_shot.dir=cur_stat.orientation;
				Find_Laser_Pos();
				laser_shot.running=1;
                        Shoot_Laser(1);
                        Draw_Update();
			Redraw();
                        break;
                    case SDLK_BACKSPACE:
                        Undo();
                        Draw_SideBar();
                        Redraw();
                        break;
                    case SDLK_RETURN:
                        Load_Level(cur_stat.cur_level);
                        Draw_SideBar();
                        Draw_Update();
                        Redraw();
                        break;
                    case SDLK_h:
                        Show_Hint();
                        break;
                    case SDLK_l:
                        Draw_LoadBox();
                        break;   
                    case SDLK_n:
                        if(Load_Next_Level())
                        {
                            Load_Level(cur_stat.cur_level);
                            Draw_SideBar();
                            Draw_Update();
                            Redraw();
                        }
                        break;
                    case SDLK_p:
                        if(Load_Previous_Level())
                        {
                            Load_Level(cur_stat.cur_level);
                            Draw_SideBar();
                            Draw_Update();
                            Redraw();
                        }
                        break;
                    default:
                        break;
				}
			}	
            else if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    switch(GUI_Left_Mouse_Click(event.button.x,event.button.y))
                    {
                        case 0:
                        Show_Hint();
                        break;
                        case 1:
                        Draw_LoadBox();
                        break;
                        case 2:
                        Undo();
                        Draw_SideBar();
                        Draw_Update();
                        Redraw();
                        break;
                        case 3:
                        Load_Level(cur_stat.cur_level);
                        Draw_SideBar();
                        Draw_Update();
                        Redraw();
                        break;
                        case 4:
                         if(Load_Previous_Level())
                        {
                            Load_Level(cur_stat.cur_level);
                            Draw_SideBar();
                            Draw_Update();
                            Redraw();
                        }
                        break;
                        case 5:
                        
                        if(Load_Next_Level())
                        {
                            Load_Level(cur_stat.cur_level);
                            Draw_SideBar();
                            Draw_Update();
                            Redraw();
                        }
                        break;
                        default:
                        break;
                    }
                }
            }
			else if(event.type==SDL_QUIT)
			{
                Unload();
			}
        }
    }
}
