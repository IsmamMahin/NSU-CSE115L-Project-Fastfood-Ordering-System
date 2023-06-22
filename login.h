// Making a login screen which has both signup and signin functionality and takes info from files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

extern char customer[50];

struct login
{
    char first_name[100];
    char last_name[100];
    char username[100];
    char password[20];
};

void signup(void);

void signin(void);

void hidePassword(char *password);

void login(void)
{
    int n = 2;
    do
    {
        if (!(n == 1 || n == 2))
        {
            printf("\n\n\n");
            printf("\tWrong input! Try again\n");
        }
        printf("\n\n\n");
        printf("\tPress '1' to signup.\n");
        printf("\tPress '2' to sign in.\n");
        printf("\n\tEnter choice: ");
        scanf("%d", &n);
    } while (!(n == 1 || n == 2));
    system("CLS");
    if (n == 1)
    {
        signup();
    }
    else
    {
        signin();
    }
}
void signup(void)
{
    FILE *log;
    log = fopen("login.txt", "a");
    struct login l;
    printf("\n\n\n");
    printf("\tEnter your first name: ");
    scanf("%s", l.first_name);
    printf("\tEnter your last name: ");
    scanf("%s", l.last_name);
    printf("\tEnter username: ");
    scanf("%s", l.username);
    while (1)
    {
        printf("\tEnter password(Atleast 8 characters): ");
        hidePassword(l.password);
        if (strlen(l.password) < 8)
        {
            printf("\tPassword cannot be less than 8 characters. Try again.");
            getch();
            memset(l.password, 0, sizeof(l.password));
            system("cls");
            printf("\n\n\n");
            printf("\tEnter your first name: %s\n", l.first_name);
            printf("\tEnter your last name: %s\n", l.last_name);
            printf("\tEnter username: %s\n", l.username);
            continue;
        }
        else
            break;
    }
    fprintf(log, "%s %s %s %s\n", l.first_name, l.last_name, l.username, l.password);
    fclose(log);
    system("CLS");
    printf("\n\n\n");
    printf("\tSignup successful!!!\n");
    signin();
}
#ifdef _WIN32
void hidePassword(char *password)
{
    int index = 0;
    char ch;

    while (1)
    {
        ch = getch();
        if (ch == '\r')
        {
            break;
        }
        else if (ch == '\b' && index > 0)
        {
            printf("\b \b");
            index--;
        }
        else if (ch != '\b')
        {
            password[index] = ch;
            index++;
            printf("*");
        }
    }

    password[index] = '\0';
    printf("\n");
}
#else
void hidePassword(char *password)
{
    struct termios old, new;
    tcgetattr(fileno(stdin), &old);
    new = old;
    new.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), TCSANOW, &new);

    fgets(password, 20, stdin);
    password[strcspn(password, "\n")] = 0;

    tcsetattr(fileno(stdin), TCSANOW, &old);
    printf("\n");
}
#endif
void signin(void)
{
    char username[100];
    char password[20];
    FILE *log;
    struct login logInfo[100];
    log = fopen("login.txt", "r");
    int count = 0;
    while (fscanf(log, "%s %s %s %s", &logInfo[count].first_name, &logInfo[count].last_name, &logInfo[count].username, &logInfo[count].password) == 4)
    {
        count++;
    }
    int s = -1;
    do
    {
        printf("\n\n\n");
        printf("\tEnter Username: ");
        scanf("%s", username);
        printf("\tEnter Password: ");
        hidePassword(password);
        fseek(log, 0, SEEK_SET);
        for (int i = 0; i < count; i++)
        {
            if (strcmp(username, logInfo[i].username) == 0 && strcmp(password, logInfo[i].password) == 0)
            {
                printf("\n\n\n");
                printf("\tLogin successful!\n");
                printf("\n\tWelcome %s %s\n", logInfo[i].first_name, logInfo[i].last_name);
                strcpy(customer, logInfo[i].first_name);
                strcat(customer, " ");
                strcat(customer, logInfo[i].last_name);
                getch();
                s = 0;
                break;
            }
        }
        if (s == -1)
        {
            system("CLS");
            printf("Incorrect ID or password! Please try again\a\n");
        }
    } while (s == -1);
    fclose(log);
}