//left top corner = 1,6
//bottom right corner = 23, 28
#include <stdio.h>
#include <string.h>

void rectangle(unsigned char background_color, unsigned char line_color, int left, int top, int right, int bottom){
    fill_bitmap(background_color);
    int x,y;
    //top
    x = 1;
    y = 6;
    while(x<=23){
        draw_pixel(line_color, x, y);
        x++;
    }
    //right
    x = 23;
    y = 6;
    while(y<=28){
        draw_pixel(line_color, x, y);
        y++;
    }
    //bottom
    x = 23;
    y = 28;
    while(x>=1){
        draw_pixel(line_color, x, y);
        x--;
    }
    //left
    x = 1;
    y = 28;
    while(y>=6){
        draw_pixel(line_color, x, y);
        y--;
    }
}
int main(){
    rectangle(0x80, 0x2f, 1, 6, 23, 28);
    return 0;
}