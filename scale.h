#ifndef SCALE_H
#define SCALE_H

SDL_Surface * Scale(SDL_Surface *,unsigned int );
void Scale_Actual(void *,void *,unsigned int ,unsigned int ,unsigned int );
void Copy_Pixel(void *,void *);
void Add_Pixels(void *,void *,void *);

#endif
