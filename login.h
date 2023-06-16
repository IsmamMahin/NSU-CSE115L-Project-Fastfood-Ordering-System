// Making a login screen which has both signup and signin functionality and takes info from files
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
struct login
{
    char first_name[100];
    char last_name[100];
    char username[100];
    char password[20];
};

void signup(void);

void signin(void);

void login(void)
{
    int n = 2;
    do
    {
        if (!(n==1||n==2))
        {
            printf("Wrong input! Try again\n");
        }

        printf("Press '1' to signup.\n");
        printf("Press '2' to sign in.\n");
        scanf("%d", &n);
    } while (!(n==1||n==2));
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
    printf("Enter your first name: ");
    scanf("%s", l.first_name);
    printf("Enter your last name: ");
    scanf("%s", l.last_name);
    printf("Enter username: ");
    scanf("%s", l.username);
    printf("Enter password: ");
    scanf("%s", l.password);
    fwrite(&l, sizeof(l), 1, log);
    fclose(log);
    system("CLS");
    printf("Signup successful!!!\n");
    signin();
}
void signin(void)
{
    char username[100];
    char password[20];
    FILE *log;
    log = fopen("login.txt", "r");
    struct login l;
    int s = -1;
    do
    {
        printf("Enter Username: ");
        scanf("%s", username);
        printf("Enter Password: ");
        scanf("%s", password);
        fseek(log, 0, SEEK_SET);
        while (fread(&l, sizeof(l), 1, log))
        {
            if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)
            {
                printf("Login successful!\n");
                printf("Welcome %s %s\n", l.first_name, l.last_name);
                getch();
                s = 0;
                break;
            }
        }
        if (s == -1)
        {
            system("CLS");
            printf("Incorrect ID or password! Please try again\n");
        }
    } while (s == -1);
    fclose(log);
}