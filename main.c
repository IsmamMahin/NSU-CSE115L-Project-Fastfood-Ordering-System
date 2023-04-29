#include<stdio.h>
#include<unistd.h>
#include<dos.h>
#include"splashscreen.h"
int main(void)
{
    splashscreen();
    sleep(4);
    system("cls");
    printf("Hello world!");
    return 0;
}