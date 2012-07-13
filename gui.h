#ifndef GUI_H
#define GUI_H

#define PADDING_X 5
#define PADDING_Y 3
#define NUM_BUTTONS 12

void Draw_SideBar();
void Game_Pause(char *);
void Show_Hint();
void Draw_LoadBox();
int Center_Text_Width(char *,int );
int Center_Text_Height(char *,int );
void Load_SideBar_Buttons();
Uint8 GUI_Left_Mouse_Click(int ,int );

struct GUIButton {
    int x;
    int y;
    int w;
    int h;
    char text[10];
    SDL_Surface *button;
};
extern struct GUIButton gui_button[NUM_BUTTONS];
#endif
