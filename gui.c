#include<string.h>
#include<SDL/SDL.h>
#include<SDL/SDL_ttf.h>
#include "drawscreen.h"
#include "gui.h"
#include "play.h"
#include "loadfile.h"

void Draw_SideBar()
{
    Uint8 i;
    SDL_Surface *fnt;
    SDL_Color text_color={255,255,255},bg_color={0,0,0};
    SDL_Rect dest;
    char buff[20],diff[10]="";
    
    switch(level[cur_stat.cur_level].difficulty)
    {
        case 1:
        strcpy(diff,"Kids");
        break;
        case 2:
        strcpy(diff,"Easy");
        break;
        case 4:
        strcpy(diff,"Medium");
        break;
        case 8:
        strcpy(diff,"Hard");
        break;
        case 16:
        strcpy(diff,"Deadly");
        break;
        default:
        break;
    }
    
	dest.x=config_file.scaled_size;
	dest.y=0;
    SDL_BlitSurface(Bitmaps[70],NULL,scr.screen,&dest);
    
    sprintf(buff,"%d - %s",cur_stat.cur_level+1,diff);
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+36+Center_Text_Width(buff,118);
    dest.y=68;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    strncpy(buff,level[cur_stat.cur_level].name,13);
    i=12;
    while(buff[i]!=' ')
    {
        if(i>0)
            i--;
        else
            break;
    }
    if(i==0)
    {
        buff[13]='\0';
        i=12;
    }
    else
        buff[i+1]='\0';
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+40+Center_Text_Width(buff,110);
    dest.y=167;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    
    strncpy(buff,level[cur_stat.cur_level].name+i+1,14);
    buff[14]='\0';
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+40+Center_Text_Width(buff,110);
    dest.y=188;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    strncpy(buff,level[cur_stat.cur_level].author,13);
    i=12;
    while(buff[i]!=' ')
    {
        if(i>0)
            i--;
        else
            break;
    }
    if(i==0)
    {
        buff[13]='\0';
        i=12;
    }
    else
        buff[i+1]='\0';
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+40+Center_Text_Width(buff,110);
    dest.y=255;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    
    strncpy(buff,level[cur_stat.cur_level].author+i+1,14);
    buff[14]='\0';
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+40+Center_Text_Width(buff,110);
    dest.y=280;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    sprintf(buff,"%d",cur_stat.moves);
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+16+Center_Text_Width(buff,69);
    dest.y=380;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    
    sprintf(buff,"%d",cur_stat.shots);
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=config_file.scaled_size+100+Center_Text_Width(buff,72);
    dest.y=380;
    SDL_BlitSurface(fnt,NULL,scr.screen,&dest);
    SDL_FreeSurface(fnt);
    for(i=0;i<6;i++)
    {
        dest.x=gui_button[i].x;
        dest.y=gui_button[i].y;
        SDL_BlitSurface(gui_button[i].button,NULL,scr.screen,&dest);
    }
	dest.x=config_file.scaled_size;
	dest.y=0;
    SDL_UpdateRect(scr.screen,dest.x,dest.y,188,512);
}

void Draw_LoadBox()
{
    int lvl;
    char lvl_str[5]="0",buff[100];
    SDL_Event event;
    Uint8 flag=1,i=0;
    
    SDL_Surface *fnt,*pause;
    SDL_Color bg_color={0,0,0},text_color={255,255,255};
    SDL_Rect dest;
    
    pause=SDL_CreateRGBSurface(SDL_SWSURFACE,256,128,24,0,0,0,0);
    
    sprintf(buff,"Enter Level Number: (1-%d)",numlevels-1);
    fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
    dest.x=Center_Text_Width(buff,256);
    dest.y=10;
    SDL_BlitSurface(fnt,NULL,pause,&dest);
    SDL_FreeSurface(fnt);
    
    dest.x=gui_button[6].x-(config_file.scaled_size-256)/2;
    dest.y=gui_button[6].y-(config_file.scaled_size-128)/2;
    SDL_BlitSurface(gui_button[6].button,NULL,pause,&dest);
    
    dest.x=(config_file.scaled_size-256)/2;
    dest.y=(config_file.scaled_size-128)/2;
    dest.w=256;
    dest.h=128;
    SDL_BlitSurface(pause,NULL,scr.screen,&dest);
	
    SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
    
    while(flag)
    {
        SDL_Delay(10);
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT && \
                    GUI_Left_Mouse_Click(event.button.x,event.button.y)==6)
                    flag=0;
            }
            else if(event.type==SDL_KEYDOWN)
            {	
                switch(event.key.keysym.sym)
                {
                    case SDLK_0:
                    if (i<4)
                    {
                        lvl_str[i++]='0';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_1:
                    if (i<4)
                    {
                        lvl_str[i++]='1';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_2:
                    if (i<4)
                    {
                        lvl_str[i++]='2';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_3:
                    if (i<4)
                    {
                        lvl_str[i++]='3';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_4:
                    if (i<4)
                    {
                        lvl_str[i++]='4';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_5:
                    if (i<4)
                    {
                        lvl_str[i++]='5';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_6:
                    if (i<4)
                    {
                        lvl_str[i++]='6';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_7:
                    if (i<4)
                    {
                        lvl_str[i++]='7';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_8:
                    if (i<4)
                    {
                        lvl_str[i++]='8';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_9:
                    if (i<4)
                    {
                        lvl_str[i++]='9';
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_BACKSPACE:
                    if(i>0)
                    {
                        i--;
                        lvl_str[i]='\0';
                    }
                    break;
                    case SDLK_ESCAPE:
                    case SDLK_RETURN:
                    flag=0;
                    break;
                    default:
                    break;
                }
                SDL_FreeSurface(pause);
				pause=SDL_CreateRGBSurface(SDL_SWSURFACE,256,128,24,0,0,0,0);
				
                fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
                dest.x=Center_Text_Width(buff,256);
                dest.y=10;
                SDL_BlitSurface(fnt,NULL,pause,&dest);
                SDL_FreeSurface(fnt);
    
                fnt=TTF_RenderText_Shaded(scr.font,lvl_str,text_color,bg_color);
                dest.x=Center_Text_Width(lvl_str,256);
                dest.y=40;
                SDL_BlitSurface(fnt,NULL,pause,&dest);
                SDL_FreeSurface(fnt);
                
                dest.x=gui_button[6].x-(config_file.scaled_size-256)/2;
				dest.y=gui_button[6].y-(config_file.scaled_size-128)/2;
				SDL_BlitSurface(gui_button[6].button,NULL,pause,&dest);
                
				dest.x=(config_file.scaled_size-256)/2;
				dest.y=(config_file.scaled_size-128)/2;
				dest.w=256;
				dest.h=128;
				SDL_BlitSurface(pause,NULL,scr.screen,&dest);
                SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
            }

        }
    }
    SDL_FreeSurface(pause);
    
    lvl=atoi(lvl_str);
    if(lvl<numlevels && lvl>0)
    {
        Load_Level(lvl-1);
        Redraw();
        Draw_SideBar();
    }
    else
        Unload();
}

void Show_Hint()
{
    Uint8 flag=1,i,pos,pos_t=0;
    char buff[50];
    SDL_Event event;
    
    SDL_Surface *fnt,*pause;
    SDL_Color bg_color={0,0,0},text_color={255,255,255};
    SDL_Rect dest;
    
    pause=SDL_CreateRGBSurface(SDL_SWSURFACE,256,260,24,0,0,0,0);
    
    fnt=TTF_RenderText_Shaded(scr.font,"Hint:",text_color,bg_color);
    dest.x=Center_Text_Width("Hint:",256);
    dest.y=10;
    SDL_BlitSurface(fnt,NULL,pause,&dest);
    SDL_FreeSurface(fnt);
    
    for(i=0;i<9 && flag;i++)
    {
        strncpy(buff,level[cur_stat.cur_level].hint+pos_t,32);
		buff[32]='\0';
		if(strlen(buff)<32)
			flag=0;
		else
		{
			pos=31;
			while(buff[pos]!=' ')
				pos--;
			pos++;
			buff[pos]='\0';
			pos_t+=pos;
		}
			
        fnt=TTF_RenderText_Shaded(scr.font,buff,text_color,bg_color);
        dest.x=Center_Text_Width(buff,256);
        dest.y=40+i*20;
        SDL_BlitSurface(fnt,NULL,pause,&dest);
        SDL_FreeSurface(fnt);
    }
    
    dest.x=gui_button[7].x-(config_file.scaled_size-256)/2;
    dest.y=gui_button[7].y-(config_file.scaled_size-260)/2;
    SDL_BlitSurface(gui_button[7].button,NULL,pause,&dest);
    
    dest.x=(config_file.scaled_size-256)/2;
    dest.y=(config_file.scaled_size-260)/2;
    dest.w=256;
    dest.h=128;
    SDL_BlitSurface(pause,NULL,scr.screen,&dest);
    SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
    
	flag=1;
    while(flag)
    {
        SDL_Delay(10);
        while(SDL_PollEvent(&event))
        {
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT && \
                    GUI_Left_Mouse_Click(event.button.x,event.button.y)==7)
                    flag=0;
            }
            else if(event.type==SDL_KEYDOWN)
            {	
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_RETURN:
                    case SDLK_SPACE:
                    case SDLK_h:
                    flag=0;
                    break;
                    default:
                    break;
                }
            }

        }
    }
    Redraw();
    SDL_FreeSurface(pause);
}

void Game_Pause(char *str)
{
    SDL_Event event;
    Uint8 flag=1,i;
    
    SDL_Surface *fnt,*pause;
    SDL_Color bg_color={0,0,0},text_color={255,255,255};
    SDL_Rect dest;
    
    Redraw();
    pause=SDL_CreateRGBSurface(SDL_SWSURFACE,256,128,24,0,0,0,0);
    
    fnt=TTF_RenderText_Shaded(scr.font,str,text_color,bg_color);
    dest.x=Center_Text_Width(str,256);
    dest.y=10;
    SDL_BlitSurface(fnt,NULL,pause,&dest);
    SDL_FreeSurface(fnt);
    
    for(i=8;i<12;i++)
    {
        dest.x=gui_button[i].x-(config_file.scaled_size-256)/2;
        dest.y=gui_button[i].y-(config_file.scaled_size-128)/2;
        SDL_BlitSurface(gui_button[i].button,NULL,pause,&dest);
    }
    dest.x=(config_file.scaled_size-256)/2;
    dest.y=(config_file.scaled_size-128)/2;
    dest.w=256;
    dest.h=128;
    SDL_BlitSurface(pause,NULL,scr.screen,&dest);
    SDL_UpdateRect(scr.screen,dest.x,dest.y,dest.w,dest.h);
    
    while(flag)
    {
        SDL_Delay(10);
        while(SDL_PollEvent(&event))
		{
            if(event.type==SDL_MOUSEBUTTONDOWN)
            {
                if(event.button.button==SDL_BUTTON_LEFT)
                {
                    switch(GUI_Left_Mouse_Click(event.button.x,event.button.y))
                    {
                        case 8:
                        Undo();
                        Redraw();
                        Draw_SideBar();
                        flag=0;
                        break;
                        case 9:
                        Load_Level(cur_stat.cur_level);
                        Redraw();
                        Draw_SideBar();
                        flag=0;
                        break;
                        case 10:
                        if(Load_Next_Level())
                        {
                            Load_Level(cur_stat.cur_level);
                            Redraw();
                            Draw_SideBar();
                            flag=0;
                            break;
                        }
                        else
                        {
                            SDL_FreeSurface(pause);
                            Unload();
                        }
                        
                        case 11:
                        SDL_FreeSurface(pause);
                        Unload();
                        flag=0;
                        break;
                        default:
                        break;
                    }
                 }   
            }
			else if(event.type==SDL_KEYDOWN)
			{	
				switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        SDL_FreeSurface(pause);
                        Unload();
                        break;
                    case SDLK_BACKSPACE:
                        Undo();
                        Redraw();
                        Draw_SideBar();
                        flag=0;
                        break;
                    case SDLK_RETURN:
                        Load_Level(cur_stat.cur_level);
                        Redraw();
                        Draw_SideBar();
                        flag=0;
                        break;
                    case SDLK_n:
                    if(Load_Next_Level())
                    {
                        Load_Level(cur_stat.cur_level);
                        Redraw();
                        Draw_SideBar();
                        flag=0;
                        break;
                    }
                    else
                    {
                        SDL_FreeSurface(pause);
                        Unload();
                    }
                        
                    default:
                        break;
				}
			}	
			if(event.type==SDL_QUIT)
			{
                SDL_FreeSurface(pause);
                Unload();
			}
        }
    }
    SDL_FreeSurface(pause);
} 

int Center_Text_Width(char *text,int width)
{
    int w,h;
    TTF_SizeText(scr.font,text,&w,&h);
    return (width-w)/2;
}

int Center_Text_Height(char *text,int height)
{
    int w,h;
    TTF_SizeText(scr.font,text,&w,&h);
    return (height-h)/2;
}

void Load_SideBar_Buttons()
{
    Uint8 i;
    SDL_Surface *fnt;
    SDL_Color text_color={0,0,0},button_Color={120,120,120};
    Uint32 button_color;
    SDL_Rect dest;
    
    button_color=SDL_MapRGB(scr.screen->format,120,120,120);

    for(i=0;i<NUM_BUTTONS;i++)
    {
        gui_button[i].w=(188-(4*PADDING_X))/2;
        gui_button[i].h=27-(2*PADDING_Y);
        gui_button[i].button=SDL_CreateRGBSurface(SDL_SWSURFACE \
            ,gui_button[i].w,gui_button[i].h,24,0,0,0,0);
        SDL_FillRect(gui_button[i].button,NULL,button_color);
        switch(i)
        {
            case 0:
            strcpy(gui_button[i].text,"Hint");
            break;
            case 1:
            strcpy(gui_button[i].text,"Load Level");
            break;
            case 2:
            strcpy(gui_button[i].text,"Undo");
            break;
            case 3:
            strcpy(gui_button[i].text,"Restart");
            break;
            case 4:
            strcpy(gui_button[i].text,"<<Level");
            break;
            case 5:
            strcpy(gui_button[i].text,"Level>>");
            break;
            case 6:
            strcpy(gui_button[i].text,"OK");
            break;
            case 7:
            strcpy(gui_button[i].text,"OK");
            break;
            case 8:
            strcpy(gui_button[i].text,"Undo");
            break;
            case 9:
            strcpy(gui_button[i].text,"Restart");
            break;
            case 10:
            strcpy(gui_button[i].text,"Next Level");
            break;
            case 11:
            strcpy(gui_button[i].text,"Quit");
            break;
        }
        if(i<6)
        {
            gui_button[i].x=config_file.scaled_size + (i%2) * \
				(PADDING_X*2 + gui_button[i].w) + PADDING_X;
            gui_button[i].y=430+((i/2) * (PADDING_Y*2 + gui_button[i].h)) + PADDING_Y;
        }
        else if(i==6)
        {
            gui_button[i].x=(config_file.scaled_size-256)/2+86;
            gui_button[i].y=(config_file.scaled_size-128)/2+72+PADDING_Y;
        }
        else if(i==7)
        {
            gui_button[i].x=(config_file.scaled_size-256)/2+86;
            gui_button[i].y=220+(config_file.scaled_size-260)/2+PADDING_Y;
        }
        if(i>7)
        {
            gui_button[i].x=17+(config_file.scaled_size-256)/2+ \
			((i-8)%2) * (PADDING_X*2+ 34 + gui_button[i].w) + PADDING_X;
            gui_button[i].y=42+(config_file.scaled_size-128)/2+ \
			(((i-8)/2) * (PADDING_Y*2+ 20 + gui_button[i].h)) + PADDING_Y;
        }
        
        fnt=TTF_RenderText_Shaded(scr.font,gui_button[i].text \
            ,text_color,button_Color);
        dest.x=Center_Text_Width(gui_button[i].text,gui_button[i].w);
        dest.y=Center_Text_Height(gui_button[i].text,gui_button[i].h);
        SDL_BlitSurface(fnt,NULL,gui_button[i].button,&dest);
        SDL_FreeSurface(fnt);
    }
}

Uint8 GUI_Left_Mouse_Click(int x,int y)
{
    Uint8 i;
    for(i=0;i<NUM_BUTTONS;i++)
    {
        if(x>=gui_button[i].x && x<=gui_button[i].x+gui_button[i].w && \
            y>=gui_button[i].y && y<=gui_button[i].y+gui_button[i].h)
            return i;
    }
    return NUM_BUTTONS;
}
