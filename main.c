#include <stdio.h>
#include <time.h>
#include "splashscreen.h" //header file containing the function for splashscreen
#include "delay.h"        //header file containing delay function
#include "login.h"        //header file containing the function for login
#include "menu.h"         //header file containing the menu of item and purchasing system
void openImageDeliveryGuy(void);

int main(void)
{
    splashscreen(); // splashscreen that is shown at the start of the program
    // getch();
    delay(4);      // the splashscreen will stay for 4 seconds
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
