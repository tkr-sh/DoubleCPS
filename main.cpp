#include <iostream>
#include <Windows.h>
#include <time.h>


int main(){
    /*
    clock_t t => a clock for time
    bool double_click => If the double_click is enable
    float cps => Your cps
    int marge => A margin of error of marge% to look more natural
    float wait => The time that you are going to wait
    int temp_clock => A temporary clock
    int min => If the time between 2 clicks is too high, don't click
    */
    clock_t t;
    bool double_click = false;
    float cps = 6.5;
    int marge = 5;//%
    float wait;
    int temp_clock;
    int min = 50;
    t = clock();

    for(;;){
        if (GetAsyncKeyState(VK_MENU)){
            double_click = !double_click;
            printf("Click");
            Sleep(500);
        }
        if ((GetKeyState(VK_LBUTTON) & 0x8000) != 0 && double_click){
            if (clock() - t > 1000){ // If the time waited is more than 1 sec
                wait = 500/cps + rand()%(int)(1000/cps * marge/100) - (500/cps * marge/100);
            } else {
                temp_clock = clock();
                wait = (temp_clock-t)/2 + rand()%(int)((temp_clock - t) * marge/100) - ( ( ( temp_clock - t )/2 ) * marge/100 ); ;
            }

            t = clock();
            
            Sleep(wait);
            mouse_event((wait>min)?MOUSEEVENTF_LEFTDOWN:MOUSEEVENTF_LEFTUP,0,0,0,0);
            mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

        }

    }

    return 0;
}