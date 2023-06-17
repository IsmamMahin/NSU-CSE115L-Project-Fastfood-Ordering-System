#include<stdio.h>
#include<time.h>
#include"splashscreen.h"      //header file containing the function for splashscreen
#include"delay.h"             //header file containing delay function
#include"login.h"             //header file containing the function for login
#include"menu.h"              //header file containing the menu of item and purchasing system

int main(void)
{
    splashscreen();           //splashscreen that is shown at the start of the program
    //getch();
    delay(4);                 //the splashscreen will stay for 4 seconds
    system("cls");            //splashscreen will get cleared
    login();                  //login process
    system("cls");
    menu();                   //buying process of the items
    system("cls");
    printf("Hello world!");
    return 0;
}
