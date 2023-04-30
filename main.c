#include<stdio.h>
#include<unistd.h>
#include<dos.h>
#include<time.h>
#include"splashscreen.h"      //header file containing the function for splashscreen
#include"delay.h"             //header file containig delay function
int main(void)
{
    splashscreen();           //splashscreen that is shown at the start of the program
    delay(4);                 //the splashscreen will stay for 4 seconds
    system("cls");            //splashscreen will get cleared
    printf("Hello world!");
    return 0;
}
