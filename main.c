#include <stdio.h>
#include <time.h>
#include <windows.h>
#include "splashscreen.h" //header file containing the function for splashscreen
#include "login.h"        //header file containing the function for login
#include "menu.h"         //header file containing the menu of item and purchasing system

void openImageDeliveryGuy(void);
void music(void);
void beep(int, int);

int main(void)
{
    system("COLOR B0");
    splashscreen(); // splashscreen that is shown at the start of the program
    music(); //Adds a music during splashscreen
    system("cls"); // splashscreen will get cleared
    login();       // login process
    system("cls");
    menu(); // buying process of the items
    system("cls");
    openImageDeliveryGuy();//opening an image which contains image of delivery guy
    return 0;
}

void openImageDeliveryGuy(void)
{
#ifdef _WIN32
    char command[] = "start eren.png"; // Windows
#elif __linux__
    char command[] = "xdg-open eren.png"; // Linux
#elif __APPLE__
    char command[] = "open eren.png"; // macOS
#else
#error "Unsupported operating system"
#endif
    system(command);
}

void beep(int frequency, int duration) {
    #ifdef _WIN32
        // Windows implementation
        Beep(frequency, duration);
    #else
        // Unix-like implementation
        printf("\033[10;%d]\a", frequency);
        usleep(duration * 1000);
        printf("\033[10;0]\a");
    #endif
}

void music(void)
{
    // Define the melody
    int melody[] = {
        659, 783, 880, 987, 880, 783, 659, 587, 523, 523, 523, 659, 783, 880, 987, 880, 783, 659, 698, 659, 587
    };
    int duration[] = {
        250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 500
    };

    // Calculate the size of the melody array
    int size = sizeof(melody) / sizeof(melody[0]);

    // Play the melody structure
    for (int i = 0; i < size; i++) {
        beep(melody[i], duration[i]);
    }
}
