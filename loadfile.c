/*
 *      loadfile.c
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

#include<stdlib.h>
#include "common.h"
#include "loadfile.h"
#include "gui.h"
#include "drawscreen.h"
#include "scale.h"
#include "bmp_loader.h"

void Load_Levels()
{
    FILE *lvl;
    char b='\0';
    int i,j;
    
    lvl=fopen(config_file.level_file,"rb");
    if(lvl==NULL)
    {
        printf("Unable to load Level file: %s\n",config_file.level_file);
        exit(1);
    }
    
    while(b!=EOF)
    {
        i=0;j=0;
        level=realloc(level,sizeof(struct levels)*(numlevels+1));
        do
        {
            
            level[numlevels].grid[j][i]=(int)fgetc(lvl);
            j++;
            if (j%16==0)
            {
                j=0;
                i++;
            }
        }while(i<16);
        
        fread(level[numlevels].name,sizeof(char),31,lvl);
        fread(level[numlevels].hint,sizeof(char),256,lvl);
        fread(level[numlevels].author,sizeof(char),31,lvl);
        level[numlevels].difficulty=(int)fgetc(lvl);
        for(i=0;level[numlevels].hint[i]!='\0';i++)
        {
            if(level[numlevels].hint[i]==13 || level[numlevels].hint[i]==10)
                level[numlevels].hint[i]=' ';
        }
        b=fgetc(lvl);
        numlevels++;
    }
    fclose(lvl);
}

void Load_Bitmaps(SDL_RWops *game,SDL_RWops *mask)
{
    SDL_Surface *BMP_File,*Mask_File,*Laser_File,*tmp;
    SDL_Rect src;
    Uint8 i=0,bpp,m,n;
    Uint8 r,g,b;
    Uint32 color[8];
    long int pitch;
    
    src.w=32;
    src.h=32;
    
	tmp=SDL_CreateRGBSurface(SDL_SWSURFACE,32,32,24,0,0,0,0);
    BMP_File=IMG_LoadBMP_RW(game);
    if(BMP_File==NULL)
    {
        printf("Unable to load BMP File : %s\n",SDL_GetError());
        exit(1);
    }
    Mask_File=IMG_LoadBMP_RW(mask);
    if(Mask_File==NULL)
    {
        printf("Unable to load Mask File : %s\n",SDL_GetError());
        exit(1);
    }
    for(i=0;i<60;i++)
    {
        src.x=32*(i%10);
        src.y=32*(i/10);
        
			Bitmaps[i]=SDL_CreateRGBSurface(SDL_SWSURFACE,config_file.tile_size \
			,config_file.tile_size,24,0,0,0,0);
			Mask[i]=SDL_CreateRGBSurface(SDL_SWSURFACE,config_file.tile_size \
			,config_file.tile_size,24,0,0,0,0);
			SDL_BlitSurface(BMP_File,&src,Bitmaps[i],NULL);
			SDL_BlitSurface(Mask_File,&src,Mask[i],NULL);
    }
    SDL_FreeSurface(BMP_File);
    SDL_FreeSurface(Mask_File);
    SDL_FreeSurface(tmp);
	
    color[0]=SDL_MapRGB(Bitmaps[0]->format,255,0,0);
    color[1]=SDL_MapRGB(Bitmaps[0]->format,255,255,0);
    color[2]=SDL_MapRGB(Bitmaps[0]->format,255,255,255);
    color[3]=SDL_MapRGB(Bitmaps[0]->format,0,255,255);
    color[4]=SDL_MapRGB(Bitmaps[0]->format,0,0,255);
    color[5]=SDL_MapRGB(Bitmaps[0]->format,255,0,255);
    color[6]=SDL_MapRGB(Bitmaps[0]->format,120,120,120);
    color[7]=SDL_MapRGB(Bitmaps[0]->format,120,255,0);
    
    Bitmaps[60]=SDL_CreateRGBSurface(SDL_SWSURFACE,6, \
		config_file.tile_size/2,24,0,0,0,0);
    SDL_FillRect_wBorder(Bitmaps[60],NULL,color[0]);
    
    Bitmaps[61]=SDL_CreateRGBSurface(SDL_SWSURFACE,config_file.tile_size/2 \
		,6,24,0,0,0,0);
    SDL_FillRect_wBorder(Bitmaps[61],NULL,color[0]);
    
    Bitmaps[70]=SDL_CreateRGBSurface(SDL_SWSURFACE,188,512,24,0,0,0,0);
    Laser_File=SDL_LoadBMP("data/sidebar.bmp");
    if(Laser_File==NULL)
    {
        printf("Unable to load sidebar.bmp: %s\n",SDL_GetError());
        exit(1);
    }
    SDL_BlitSurface(Laser_File,NULL,Bitmaps[70],NULL);
    SDL_FreeSurface(Laser_File);
    
    
    pitch=Mask[54]->pitch;
    bpp=Mask[54]->format->BytesPerPixel;
    for(i=62;i<70;i++)
    {
        Bitmaps[i]=SDL_CreateRGBSurface(SDL_SWSURFACE,config_file.tile_size \
			,config_file.tile_size,24,0,0,0,0);
        SDL_FillRect(Bitmaps[i],NULL,color[i-62]);
        
        SDL_LockSurface(Bitmaps[i]);
        for(m=0;m<config_file.tile_size;m++)
        {
            for(n=0;n<config_file.tile_size;n++)
            {
                r=*(Uint8 *) (Mask[54]->pixels \
                +n*pitch +m*bpp);
                
                g=*(Uint8 *) (Mask[54]->pixels \
                +n*pitch +m*bpp+1);
            
                b=*(Uint8 *) (Mask[54]->pixels \
                +n*pitch +m*bpp+2);
                
                if(r==0 && g==0 && b==0)
                {
                    *(Uint8 *) (Bitmaps[i]->pixels +n*pitch \
                        +m*bpp)=*(Uint8 *) (Bitmaps[54]->pixels \
                        +n*pitch +m*bpp);
                    
                    *(Uint8 *) (Bitmaps[i]->pixels +n*pitch \
                        +m*bpp+1)=*(Uint8 *) (Bitmaps[54]->pixels \
                        +n*pitch +m*bpp+1);
                    
                    *(Uint8 *) (Bitmaps[i]->pixels +n*pitch \
                        +m*bpp+2)=*(Uint8 *) (Bitmaps[54]->pixels \
                        +n*pitch +m*bpp+2);
                }
            }
        }
        SDL_UnlockSurface(Bitmaps[i]);
    }
}

void Load_LTG()
{
    FILE *ltg;
    struct LTGheader header;
    unsigned long int size,buffsize;
    void *buff=NULL;
	SDL_RWops *game,*mask;
    
    ltg=fopen(config_file.ltg_file,"rb");
    if(ltg==NULL)
    {
        printf("Unable to load LTG file %s\n",config_file.ltg_file);
        exit(1);
    }
    
    fseek(ltg,0,SEEK_END);
    size=ftell(ltg);
    fseek(ltg,0,SEEK_SET);
    
    fread(&header,sizeof(char),sizeof(struct LTGheader),ltg);
    
	
    buff=realloc(buff,size-sizeof(struct LTGheader));
    
    fread(buff,sizeof(char),size-sizeof(struct LTGheader),ltg);
    
	buffsize=header.maskoffset - sizeof(struct LTGheader);
	game=SDL_RWFromMem(buff,buffsize);
	
	
    fseek(ltg,header.maskoffset,SEEK_SET);
	mask=SDL_RWFromMem(buff + buffsize,size - header.maskoffset);
		
    fclose(ltg);
    Load_Bitmaps(game,mask);
	
	SDL_FreeRW(game);
	SDL_FreeRW(mask);
    free(buff);
}

void Load_Config()
{
    FILE *f;
    char b,buff[100];
    Uint8 i;
    
    f=fopen("ltanks.conf","r");
    if(f!=NULL)
    {
        while((b=fgetc_nw(f))!='=')
        {
            if(b==EOF)
                break;
        }
        i=0;
        while((b=fgetc_nw(f))!='\n')
            buff[i++]=b;
        buff[i]='\0';
        strcpy(config_file.level_file,buff);
        
        while((b=fgetc(f))!='=')
        {
            if(b==EOF)
                break;
        }
        i=0;
        while((b=fgetc_nw(f))!='\n')          
            buff[i++]=b;
        buff[i]='\0';
        strcpy(config_file.ltg_file,buff);
        
        i=0;
        while((b=fgetc(f))!='=')
        {
            if(b==EOF)
                break;
        }
        while((b=fgetc_nw(f))!='\n')
        {
            if(b==EOF)
                break;
            buff[i++]=b;
        }
        buff[i]='\0';
        if(strcmp(buff,"all")==0)
            config_file.difficulty=0;
        else if(strcmp(buff,"kids")==0)
            config_file.difficulty=1;
        else if(strcmp(buff,"easy")==0)
            config_file.difficulty=2;
        else if(strcmp(buff,"medium")==0)
            config_file.difficulty=4;
        else if(strcmp(buff,"hard")==0)
            config_file.difficulty=8;
        else if(strcmp(buff,"deadly")==0)
            config_file.difficulty=16;
        
        while((b=fgetc_nw(f))!='=')
        {
            if(b==EOF)
                break;
        }
        i=0;
        while((b=fgetc_nw(f))!='\n')
        {
            if(b!=EOF)
                buff[i++]=b;
            else
                break;
        }
        buff[i]='\0';
        sscanf(buff,"%u",&config_file.scaled_size);
        if(i==0)
			config_file.scaled_size=512;
			
        fclose(f);
    }
    else
    {
        printf("Unable to Load Config File : ltanks.conf\n");
        exit(1);
    }
}

char fgetc_nw(FILE *f)
{
    char a;
	do
	{
		a=fgetc(f);
	}while(a==' '||a=='\t');
	return a;
}
void Unload()
{
    Uint8 i;
    
    free(level);
    for(i=0;i<NUM_BUTTONS;i++)
        SDL_FreeSurface(gui_button[i].button);
    for(i=0;i<71;i++)
    {
        SDL_FreeSurface(Bitmaps[i]);
        if(i<60)
            SDL_FreeSurface(Mask[i]);
    }
    
    TTF_CloseFont(scr.font);
    TTF_Quit(); 
    SDL_Quit();
   
    exit(0);
}

void SDL_FillRect_wBorder(SDL_Surface *surf,SDL_Rect *rect,Uint32 color)
{
	int i;
	Uint8 border[3]={0,0,0},bpp=surf->format->BytesPerPixel;
	long int pitch=surf->pitch;
	
	SDL_FillRect(surf,rect,color);
	for(i=0;i<surf->w;i++)
		Copy_Pixel(&border,surf->pixels+i*bpp);
	for(i=0;i<surf->w;i++)
		Copy_Pixel(&border,surf->pixels + pitch*(surf->h-1) + i*bpp);
	for(i=0;i<surf->h;i++)
		Copy_Pixel(&border,surf->pixels+i*pitch);
	for(i=0;i<surf->h;i++)
		Copy_Pixel(&border,surf->pixels + bpp*(surf->w-1) + i*pitch);
	
}
