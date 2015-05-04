/*
 *      play.c
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

#include "drawscreen.h"
#include "gui.h"
#include "play.h"
#include "loadfile.h"
#include <emscripten.h>
#include <unistd.h>
int main_loop_running=1;

void Tank_Move(Uint8 direction)
{
    if(cur_stat.orientation!=direction)
    {
        cur_stat.orientation=direction;
        switch(direction)
        {
            case UP:
                cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=2;
                break;
            case DOWN:
                cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=4;
                break;
            case LEFT:
                cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=5;
                break;
            case RIGHT:
                cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=3;
                break;
        }
    }
    else
    {
        switch(direction)
        {
            case UP:
                if(!isObstacle(cur_stat.blocks[cur_stat.tank_x-1] \
                 [cur_stat.tank_y].main) && !isObstacle(cur_stat.blocks \
                  [cur_stat.tank_x-1][cur_stat.tank_y].top) && \
                   cur_stat.tank_x>0)
                {
                    Make_Undo();
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
                    cur_stat.tank_x--;
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=2;
                    Increase_Moves();
                }
                break;
            case DOWN:
                if(!isObstacle(cur_stat.blocks[cur_stat.tank_x+1] \
                 [cur_stat.tank_y].main) && !isObstacle(cur_stat.blocks \
                  [cur_stat.tank_x+1][cur_stat.tank_y].top) && \
                   cur_stat.tank_x<15)
                {
                    Make_Undo();
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
                    cur_stat.tank_x++;
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=4;
                    Increase_Moves();
                }
                break;
            case LEFT:
                if(!isObstacle(cur_stat.blocks[cur_stat.tank_x] \
                 [cur_stat.tank_y-1].main) && !isObstacle(cur_stat.blocks \
                  [cur_stat.tank_x][cur_stat.tank_y-1].top) && \
                   cur_stat.tank_y>0)
                {
                    Make_Undo();
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
                    cur_stat.tank_y--;
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=5;
                    Increase_Moves();
                }
                break;
            case RIGHT:
                if(!isObstacle(cur_stat.blocks[cur_stat.tank_x] \
                 [cur_stat.tank_y+1].main) && !isObstacle(cur_stat.blocks \
                  [cur_stat.tank_x][cur_stat.tank_y+1].top) && \
                   cur_stat.tank_y<15)
                {
                    Make_Undo();
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
                    cur_stat.tank_y++;
                    cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=3;
                    Increase_Moves();
                }
                break;
        }
        Check_Ride();
        Check_Ice_Ride(&cur_stat.tank_x,&cur_stat.tank_y);
        
        if(cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==9)
        {
            Draw_Update();
            Redraw();
            Game_Pause("You fell into Water");
        }
		
        if(Check_Line_Of_Fire())
        {
            Draw_Update();
            Redraw();
            Shoot_Laser(2);
			
            Game_Pause("An Anti-Tank Hit you");
        }
        if(cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==6)
        {
            Draw_Update();
            Redraw();
            Game_Pause("You Won");
        }
        
    }
    Draw_Update();
    Redraw();
}

void Shoot_Laser(Uint8 on)
{
    int resume = 0;
    if (main_loop_running) {
        emscripten_pause_main_loop();
        resume = 1;
        main_loop_running = 0;
    }

    Uint8 i,flag,tank=0;
	if(on==1)
		tank=1;
	
	while(!(i=Laser_isObstacle(tank)))
	{ 
		
		for(i=0;i<2;i++)
		{
			switch(laser_shot.dir)
			{
				case UP:
					laser_shot.x-=config_file.tile_size/2;
				break;
				case DOWN:
					laser_shot.x+=config_file.tile_size/2;
				break;
				case LEFT:
					laser_shot.y-=config_file.tile_size/2;
				break;
				case RIGHT:
					laser_shot.y+=config_file.tile_size/2;
				break;
			}
			Draw_Laser_Shot();
			//SDL_Delay(20);
			emscripten_sleep(20);
			Clear_Laser_Shot();
			if(i==0)
			{
				flag=Check_Mirrors(&(laser_shot.x),&(laser_shot.y),&(laser_shot.dir));
				if(flag>0)
				{
					Draw_Laser_Shot();
                                        //SDL_Delay(20);
					emscripten_sleep(20);
					Clear_Laser_Shot();
					break;
				}
			}
		}   
		if(flag==2)
			break;
	}
	laser_shot.running=0;
	if(on==1)
	{
		Check_Ride();
		
		if(Check_Line_Of_Fire())
		{
                        Draw_Update();
			Redraw();
			Shoot_Laser(2);
			Game_Pause("An Anti-Tank Hit you");
		}
	}
	Check_Ice_Ride(&(laser_shot.r_x),&(laser_shot.r_y));

    if (resume)
        emscripten_resume_main_loop();
}

int Shoot_Laser_AntiTank()
{
	Uint8 flag,i;
	for(i=0;i<2;i++)
	{ 
		if(laser_shot.running)
		{
			if(i==0)
			{
				flag=Laser_isObstacle(2);
				if(flag==2)
				{
					laser_shot.running=0;
					return 0;
				}
				else
					flag=!flag;
			}
			else
				flag=1;
			
			
			if(flag)
			{
				switch(laser_shot.dir)
				{
					case UP:
						laser_shot.x-=config_file.tile_size/2;
					break;
					case DOWN:
						laser_shot.x+=config_file.tile_size/2;
					break;
					case LEFT:
						laser_shot.y-=config_file.tile_size/2;
					break;
					case RIGHT:
						laser_shot.y+=config_file.tile_size/2;
					break;
				}
			}
			else
				laser_shot.running=0;
		}
		Draw_Laser_Shot();
		emscripten_sleep(20);
		Clear_Laser_Shot();
		if(i==0)
		{
			flag=Check_Mirrors(&(laser_shot.x),&(laser_shot.y) \
				,&(laser_shot.dir));
			if(flag>0)
			{
				Draw_Laser_Shot();
				emscripten_sleep(20);
				Clear_Laser_Shot();
				break;
			}
		}
	}
	return 1;
}

void Find_Laser_Pos()
{
	switch(laser_shot.dir)
    {
        case UP:
        laser_shot.x=laser_shot.r_x*config_file.tile_size;
        laser_shot.y=laser_shot.r_y*config_file.tile_size+config_file.tile_size/2-2;
        break;
        case DOWN:
        laser_shot.x=laser_shot.r_x*config_file.tile_size+config_file.tile_size/2;
        laser_shot.y=laser_shot.r_y*config_file.tile_size+config_file.tile_size/2-2;
        break;
        case LEFT:
        laser_shot.x=laser_shot.r_x*config_file.tile_size+config_file.tile_size/2-2;
        laser_shot.y=laser_shot.r_y*config_file.tile_size;
        break;
        case RIGHT:
        laser_shot.x=laser_shot.r_x*config_file.tile_size+config_file.tile_size/2-2;
        laser_shot.y=laser_shot.r_y*config_file.tile_size+config_file.tile_size/2;
        break;
    }
}

void Object_Move(Uint8 x,Uint8 y,Uint8 dir)
{
    Uint8 r_x=x,r_y=y;
    switch(dir)
    {
        case UP:
		if(r_x>0)
			r_x--;
		else
			return;
        break;
        case DOWN:
        r_x++;
        break;
        case LEFT:
        if(r_y>0)
			r_y--;
		else
			return;
        break;
        case RIGHT:
        r_y++;
        break;
    }
    if(!isObstacle(cur_stat.blocks[r_x][r_y].top) &&\
        r_x<=15 && r_y<=15 && !isObstacle(cur_stat.blocks[r_x][r_y].main))
    {
        cur_stat.blocks[r_x][r_y].top=cur_stat.blocks[x][y].top;
        cur_stat.blocks[x][y].top=0;
        Check_Wormhole(&r_x,&r_y);
        Check_Ice_Ride(&r_x,&r_y);
     }
    if(cur_stat.blocks[r_x][r_y].main==9)
    { 
        if(cur_stat.blocks[r_x][r_y].top==14)
            cur_stat.blocks[r_x][r_y].main=19;
        cur_stat.blocks[r_x][r_y].top=0;
    }
}

void Check_Ride()
{
    Uint8 dir,flag=1,cond;
    Uint8 x[255],y[255],m=0,n,t;
    laser_shot.running=0;
    int resume = 0;
    if (main_loop_running) {
        emscripten_pause_main_loop();
        resume = 1;
        main_loop_running = 0;
    }


	
    while((cond=((cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==24 \
        || cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==27 \
        || cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==30 \
        || cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main==33) \
		 && flag))||laser_shot.running)
    {
                Draw_Update();
		Redraw();
		Check_Line_Of_Fire();
		t=Shoot_Laser_AntiTank();
		if(cond && t)
		{
			x[m]=cur_stat.tank_x;
			y[m]=cur_stat.tank_y;
			m++;
			
			dir=cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top;
			switch(cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].main)
			{
				case 24:
					if(!isObstacle(cur_stat.blocks[cur_stat.tank_x-1] \
					 [cur_stat.tank_y].main) && !isObstacle(cur_stat.blocks \
					  [cur_stat.tank_x-1][cur_stat.tank_y].top) && \
					   cur_stat.tank_x>0)
					{
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
						cur_stat.tank_x--;
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=dir;
					}
					else
						flag=0;
					break;
				case 30:
					if(!isObstacle(cur_stat.blocks[cur_stat.tank_x+1] \
					 [cur_stat.tank_y].main) && !isObstacle(cur_stat.blocks \
					  [cur_stat.tank_x+1][cur_stat.tank_y].top) && \
					   cur_stat.tank_x<15)
					{
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
						cur_stat.tank_x++;
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=dir;
					}
					else
						flag=0;
					break;
				case 33:
					if(!isObstacle(cur_stat.blocks[cur_stat.tank_x] \
					 [cur_stat.tank_y-1].main) && !isObstacle(cur_stat.blocks \
					  [cur_stat.tank_x][cur_stat.tank_y-1].top) && \
					   cur_stat.tank_y>0)
					{
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
						cur_stat.tank_y--;
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=dir;
					}
					else
						flag=0;
					break;
				case 27:
					if(!isObstacle(cur_stat.blocks[cur_stat.tank_x] \
					 [cur_stat.tank_y+1].main) && !isObstacle(cur_stat.blocks \
					  [cur_stat.tank_x][cur_stat.tank_y+1].top) && \
					   cur_stat.tank_y<15)
					{
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=0;
						cur_stat.tank_y++;
						cur_stat.blocks[cur_stat.tank_x][cur_stat.tank_y].top=dir;
					}
					else
						flag=0;
					break;
			}
			
			if(flag)
			{
				for(n=0;n<m;n++)
				{
					if(cur_stat.tank_x==x[n] && cur_stat.tank_y==y[n])
					{
						Game_Pause("You got stuck in an infinite loop");
						flag=0;
						laser_shot.running=0;
					}
				}
			}
			Check_Wormhole(&cur_stat.tank_x,&cur_stat.tank_y);
		}
    }

    if (resume)
        emscripten_resume_main_loop();
    
}

Uint8 Next_Rotating_Mirror(Uint8 pos)
{
    switch(pos)
    {
        case 47:
        return 48;
        break;
        case 48:
        return 49;
        break;
        case 49:
        return 50;
        break;
        case 50:
        return 47;
        break;
    }
    return 0;
}

Uint8 isObstacle(Uint8 type)
{
    if((type>=12 && type <=23 && type!=19)||(type>=36 &&type<=45)|| \
        (type>=47 && type<=50)||(type>=52 && type<=54) || \
            (type>=2 && type<=5))
        return 1;
    else
        return 0;
}

Uint8 Laser_isObstacle(Uint8 tank)
{
    int r_x=laser_shot.x/config_file.tile_size,r_y=laser_shot.y/config_file.tile_size;
    Uint8 m,t=0;
	
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
    if(r_x<0 || r_x>15 || r_y<0 || r_y>15)
        return 1;
    m=cur_stat.blocks[r_x][r_y].main;
    while(t<2)
    {
        if(t==1)
            m=cur_stat.blocks[r_x][r_y].top;
        t++;
        switch(m)
        {
            case 12:
            case 13:
            case 52:
            case 53:
            case 54:
            return 1;
            break;
            case 16:
            if(laser_shot.dir==DOWN)
                cur_stat.blocks[r_x][r_y].top=54;
            else
                Object_Move(r_x,r_y,laser_shot.dir);
            return 1;
            break;
            case 36:
            if(laser_shot.dir==LEFT)
                cur_stat.blocks[r_x][r_y].top=52;
            else
                Object_Move(r_x,r_y,laser_shot.dir);
            return 1;
            break;
            case 39:
            if(laser_shot.dir==UP)
                cur_stat.blocks[r_x][r_y].top=12;
            else
                Object_Move(r_x,r_y,laser_shot.dir);
            return 1;
            break;
            case 42:
            if(laser_shot.dir==RIGHT)
                cur_stat.blocks[r_x][r_y].top=53;
            else
                Object_Move(r_x,r_y,laser_shot.dir);
            return 1;
            break;
            case 15:
                cur_stat.blocks[r_x][r_y].main=1;
            return 1;
            break;
            case 14:
                Object_Move(r_x,r_y,laser_shot.dir);
            return 1;
            break;
            case 20:
            if(laser_shot.dir==UP || laser_shot.dir==LEFT)
            {
                Object_Move(r_x,r_y,laser_shot.dir);
                return 1;
            }
            break;
            case 21:
            if(laser_shot.dir==UP || laser_shot.dir==RIGHT)
            {
                Object_Move(r_x,r_y,laser_shot.dir);
                return 1;
            }
            break;
            case 22:
            if(laser_shot.dir==DOWN || laser_shot.dir==RIGHT)
            {
                Object_Move(r_x,r_y,laser_shot.dir);
                return 1;
            }
            break;
            case 23:
            if(laser_shot.dir==DOWN || laser_shot.dir==LEFT)
            {
                Object_Move(r_x,r_y,laser_shot.dir);
                return 1;
            }
            break;
            case 2 ... 5:
			if(tank==1)
				Game_Pause("You killed yourself");
			else if(tank==2)
				Game_Pause("An Anti-Tank Hit you");
            return 2;
            break;
        }
    }
    return 0;
}

Uint8 Check_Line_Of_Fire()
{
    Uint8 i,j,k,hit,flag,dir;
	
    for(i=0;i<16;i++)
    {
        for(j=0;j<16;j++)
        {
            hit=1;
			flag=0;
            switch(cur_stat.blocks[i][j].top)
            {
                case 16:
				dir=UP;
                if(cur_stat.tank_y==j && cur_stat.tank_x<i)
                {
                    for(k=cur_stat.tank_x+1;k<i;k++)
                    {
                        if(isObstacle(cur_stat.blocks[k][j].main) || \
                         isObstacle(cur_stat.blocks[k][j].top))
                            hit=0;
                    }
					flag=1;
                }
                break;
                case 36:
				dir=RIGHT;
                if(cur_stat.tank_x==i && cur_stat.tank_y>j)
                {
                    for(k=cur_stat.tank_y-1;k>j;k--)
                    {
                        if(isObstacle(cur_stat.blocks[i][k].main) || \
                         isObstacle(cur_stat.blocks[i][k].top))
                            hit=0;
                    }
					flag=1;
                }
                break;
                case 39:
				dir=DOWN;
                if(cur_stat.tank_y==j && cur_stat.tank_x>i)
                {
                    for(k=cur_stat.tank_x-1;k>i;k--)
                    {
                        if(isObstacle(cur_stat.blocks[k][j].main) || \
                         isObstacle(cur_stat.blocks[k][j].top))
                            hit=0;
                    }
					flag=1;
                }
                break;
                case 42:
				dir=LEFT;
                if(cur_stat.tank_x==i && cur_stat.tank_y<j)
                {
                    for(k=cur_stat.tank_y+1;k<j;k++)
                    {
                        if(isObstacle(cur_stat.blocks[i][k].main) || \
                         isObstacle(cur_stat.blocks[i][k].top))
                            hit=0;
                    }
					flag=1;
                }
                break;
            }
			if(hit && flag && !laser_shot.running)
			{
				laser_shot.r_x=i;
				laser_shot.r_y=j;
				laser_shot.dir=dir;
				Find_Laser_Pos();
				laser_shot.running=1;
				return 1;
			}
        }
    }
    return 0;
}

void Check_Wormhole(Uint8 *x,Uint8 *y)
{
    Uint8 i,j,m,n,dir,wormhole[2][2];
    
    dir=cur_stat.blocks[*x][*y].top;
    for(m=63;m<71;m++)
    {
        n=0;
        for(i=0;i<16;i++)
        {
            for(j=0;j<16;j++)
            {
                if(m==cur_stat.blocks[i][j].main)
                {
                    wormhole[n][0]=i;
                    wormhole[n][1]=j;
                    n++;
                }
            }
        }
        if(n>0)
        {
            if(wormhole[0][0]==*x && wormhole[0][1]==*y && \
                !isObstacle(cur_stat.blocks[wormhole[1][0]][wormhole[1][1]].top))
            {
                cur_stat.blocks[*x][*y].top=0;
                *x=wormhole[1][0];
                *y=wormhole[1][1];
                cur_stat.blocks[*x][*y].top=dir;
            }
            else if(wormhole[1][0]==*x && wormhole[1][1]==*y && \
                !isObstacle(cur_stat.blocks[wormhole[0][0]][wormhole[0][1]].top))
            {
                cur_stat.blocks[*x][*y].top=0;
                *x=wormhole[0][0];
                *y=wormhole[0][1];
                cur_stat.blocks[*x][*y].top=dir;
            }
        }
    }
    
}

Uint8 Check_Mirrors(unsigned int *x,unsigned int *y,Uint8 *dir)
{
    int r_x=*x/config_file.tile_size,r_y=*y/config_file.tile_size;
    Uint8 t,m;
    t=cur_stat.blocks[r_x][r_y].top;
    m=cur_stat.blocks[r_x][r_y].main;
    switch(*dir)
    {
        case UP:
        if(t==22 || m==49)
        {
            *dir=RIGHT;
            *x=r_x*config_file.tile_size+config_file.tile_size/2-2;
            *y=r_y*config_file.tile_size+config_file.tile_size/2;
            return 1;
        }
        else if(t==23 || m==50)
        {
            *dir=LEFT;
            *x=r_x*config_file.tile_size+config_file.tile_size/2-2;
            *y=r_y*config_file.tile_size;
            return 1;
        }
        else if(m==47 || m==48)
        {
            cur_stat.blocks[r_x][r_y].main=Next_Rotating_Mirror(m);
            return 2;
        }
        break;
        case DOWN:
        if(t==20 || m==47)
        {
            *dir=LEFT;
            *x=r_x*config_file.tile_size+config_file.tile_size/2-2;
            *y=r_y*config_file.tile_size;
            return 1;
        }
        else if(t==21 || m==48)
        {
            *dir=RIGHT;
            *x=r_x*config_file.tile_size+config_file.tile_size/2-2;
            *y=r_y*config_file.tile_size+config_file.tile_size/2;
            return 1;
        }
        else if(m==49 || m==50)
        {
            cur_stat.blocks[r_x][r_y].main=Next_Rotating_Mirror(m);
            return 2;
        }
        break;
        case LEFT:
        if(t==22 || m==49)
        {
            *dir=DOWN;
            *x=r_x*config_file.tile_size+config_file.tile_size/2;
            *y=r_y*config_file.tile_size+config_file.tile_size/2-2;
            return 1;
        }
        else if(t==21 || m==48)
        {
            *dir=UP;
            *x=r_x*config_file.tile_size;
            *y=r_y*config_file.tile_size+config_file.tile_size/2-2;
            return 1;
        }
        else if(m==47 || m==50)
        {
            cur_stat.blocks[r_x][r_y].main=Next_Rotating_Mirror(m);
            return 2;
        }
        break;
        case RIGHT:
        if(t==20 || m==47)
        {
            *dir=UP;
            *x=r_x*config_file.tile_size;
            *y=r_y*config_file.tile_size+config_file.tile_size/2-2;
            return 1;
        }
        else if(t==23 || m==50)
        {
            *dir=DOWN;
            *x=r_x*config_file.tile_size+config_file.tile_size/2;
            *y=r_y*config_file.tile_size+config_file.tile_size/2-2;
            return 1;
        }
        else if(m==49 || m==48)
        {
            cur_stat.blocks[r_x][r_y].main=Next_Rotating_Mirror(m);
            return 2;
        }
        break;
    }
    return 0;
}

void Check_Ice_Ride(Uint8 *r_x,Uint8 *r_y)
{
    Uint8 flag=1,b,x,y,cond;
	
	laser_shot.running=0;
    b=cur_stat.blocks[*r_x][*r_y].main;

    int resume = 0;
    if (main_loop_running) {
        emscripten_pause_main_loop();
        resume = 1;
        main_loop_running = 0;
    }

    while((cond=((b==56 || b==57) && flag))||laser_shot.running)
    {
        x=*r_x;
        y=*r_y;
        Redraw();
        Check_Line_Of_Fire();
		Shoot_Laser_AntiTank();
		if(cond)
		{
			switch(cur_stat.orientation)
			{
				case UP:
					if(!isObstacle(cur_stat.blocks[*r_x-1] \
					 [*r_y].main) && !isObstacle(cur_stat.blocks \
					  [*r_x-1][*r_y].top) && \
					   *r_x>0)
					{
						(*r_x)--;
						cur_stat.blocks[*r_x][*r_y].top=cur_stat.blocks[x][y].top;
						cur_stat.blocks[x][y].top=0;
					}
					else
						flag=0;
					break;
				case DOWN:
					if(!isObstacle(cur_stat.blocks[*r_x+1] \
					 [*r_y].main) && !isObstacle(cur_stat.blocks \
					  [*r_x+1][*r_y].top) && \
					   *r_x<15)
					{
						(*r_x)++;
						cur_stat.blocks[*r_x][*r_y].top=cur_stat.blocks[x][y].top;
						cur_stat.blocks[x][y].top=0;
					}
					else
						flag=0;
					break;
				case LEFT:
					if(!isObstacle(cur_stat.blocks[*r_x] \
					 [*r_y-1].main) && !isObstacle(cur_stat.blocks \
					  [*r_x][*r_y-1].top) && \
					   *r_y>0)
					{
						(*r_y)--;
						cur_stat.blocks[*r_x][*r_y].top=cur_stat.blocks[x][y].top;
						cur_stat.blocks[x][y].top=0;
					}
					else
						flag=0;
					break;
				case RIGHT:
					if(!isObstacle(cur_stat.blocks[*r_x] \
					 [*r_y+1].main) && !isObstacle(cur_stat.blocks \
					  [*r_x][*r_y+1].top) && \
					   *r_y<15)
					{
						
						(*r_y)++;
						cur_stat.blocks[*r_x][*r_y].top=cur_stat.blocks[x][y].top;
						cur_stat.blocks[x][y].top=0;
					}
					else
						flag=0;
					break;
			}
			if(b==57)
				cur_stat.blocks[x][y].main=9;
			b=cur_stat.blocks[*r_x][*r_y].main;
			
			Check_Wormhole(r_x,r_y);
		}
    }
    if (resume)
        emscripten_resume_main_loop();
}

void Undo()
{
    if(undo_count>0)
    {
        undo_index--;
        if(undo_index<0)
            undo_index=9;
        cur_stat=undo_stat[undo_index];
        undo_count--;
    }
}

void Make_Undo()
{
    if(undo_index==10)
        undo_index=0;
    undo_stat[undo_index++]=cur_stat;
    if(undo_count<10)
        undo_count++;
}
    
void Increase_Moves()
{
    cur_stat.moves++;
    Draw_SideBar();
    Check_Wormhole(&cur_stat.tank_x,&cur_stat.tank_y);
}
