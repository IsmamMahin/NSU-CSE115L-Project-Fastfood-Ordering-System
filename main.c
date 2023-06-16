#include<stdio.h>
#include<time.h>
#include"splashscreen.h"      //header file containing the function for splashscreen
#include"delay.h"             //header file containig delay function
#include"login.h"             //header file containig the function for login;
int main(void)
{
    splashscreen();           //splashscreen that is shown at the start of the program
    delay(4);                 //the splashscreen will stay for 4 seconds
    system("cls");            //splashscreen will get cleared
    login();
    printf("Hello world!");
    return 0;
}
