#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include "scale.h"

SDL_Surface * Scale(SDL_Surface *bmp,unsigned int size_y)
{
    unsigned int i,size_x=(bmp->w*size_y)/bmp->h;
    SDL_Surface *resized1,*resized2;
    
    
    resized1=SDL_CreateRGBSurface(SDL_SWSURFACE,size_x,size_y,24,0,0,0,0);
    resized2=SDL_CreateRGBSurface(SDL_SWSURFACE,size_x,size_y,24,0,0,0,0);
    
    for(i=0;i<bmp->h;i++)
       Scale_Actual(bmp->pixels + bmp->pitch*i, resized1->pixels + \
        resized1->pitch*i, bmp->w,size_x,3);
       
    SDL_BlitSurface(resized1,NULL,resized2,NULL);
    
    for(i=0;i<resized1->w;i++)
       Scale_Actual(resized2->pixels + i*3,resized1->pixels + i*3,bmp->h, \
       size_y,resized1->pitch);
        
    SDL_FreeSurface(resized2);
    return resized1;
}
void Scale_Actual(void *bmp,void *resized,unsigned int orig,unsigned int size,unsigned int pitch)
{
    unsigned int i;
    if(orig==1)
    {
        for(i=0;i<size;i++)
            Copy_Pixel(bmp,resized+i*pitch);
    }
    else
    {
        if(orig%2==0)
        {
            if(size%2==0)
            {
                Scale_Actual(bmp,resized,orig/2,size/2,pitch);
                Scale_Actual(bmp + (orig/2)*pitch, resized + (size/2)*pitch, \
                    orig/2, size/2,pitch);
            }
            else
            {
                Add_Pixels(bmp + ((orig/2)-1)*pitch, bmp + (orig/2)*pitch, \
                    resized + (size/2)*pitch);
                Scale_Actual(bmp,resized,orig/2,size/2,pitch);
                Scale_Actual(bmp + (orig/2)*pitch, resized + ((size/2)+1)*pitch, \
                    orig/2,size/2,pitch);
            }
        }
        else
        {
            if(size%2==0)
            {
                Add_Pixels(bmp + (orig/2-1)*pitch,bmp + (orig/2)*pitch \
                    ,resized + (size/2-1)*pitch);
                Add_Pixels(bmp + (orig/2)*pitch,bmp + (orig/2+1)*pitch, \
                    resized + (size/2)*pitch);
                Scale_Actual(bmp,resized,orig/2,size/2-1,pitch);
                Scale_Actual(bmp + (orig/2+1)*pitch, resized + (size/2+1)*pitch, \
                    orig/2, size/2-1,pitch);
            }
            else
            {
                Copy_Pixel(bmp + (orig/2)*pitch,resized + (size/2)*pitch);
                Scale_Actual(bmp,resized,orig/2,size/2,pitch);
                Scale_Actual(bmp + ((orig/2)+1)*pitch, resized + ((size/2)+1)*pitch, \
                    orig/2,size/2,pitch);
            }
        }
    }
}

void Copy_Pixel(void *src,void *dest)
{
    *(Uint8 *)(dest)=*(Uint8 *)(src);
    *(Uint8 *)(dest+1)=*(Uint8 *)(src+1);
    *(Uint8 *)(dest+2)=*(Uint8 *)(src+2);
}
void Add_Pixels(void *src1,void *src2,void *dest)
{
    
    *(Uint8 *)(dest)=(*(Uint8 *)(src1)+*(Uint8 *)(src2))/2;
    *(Uint8 *)(dest+1)=(*(Uint8 *)(src1+1)+*(Uint8 *)(src2+1))/2;
    *(Uint8 *)(dest+2)=(*(Uint8 *)(src1+2)+*(Uint8 *)(src2+2))/2;
}
