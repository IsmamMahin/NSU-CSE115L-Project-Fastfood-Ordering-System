#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50

extern char customer[50];

// Structure to represent a menu item
typedef struct
{
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

float nPrice(float, int);
void newDelay(int);

int menu(void)
{
    FILE *file;
    MenuItem menu[MAX_ITEMS];
    int itemCount = 0;

    // Open the file in read mode
    file = fopen("menu.txt", "r");
    if (file == NULL)
    {
        printf("Unable to open the file.\n");
        return 1;
    }

    char line[100]; // Assuming a maximum line length of 100 characters

    // Read the menu items from the file
    while (fgets(line, sizeof(line), file))
    {
        // Extract the name and price from the line
        char *name = strtok(line, "-");
        char *priceStr = strtok(NULL, " ");
        float price = atof(priceStr);

        // Copy the name and price to the menu structure
        strncpy(menu[itemCount].name, name, MAX_NAME_LENGTH);
        menu[itemCount].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
        menu[itemCount].price = price;

        itemCount++;
    }

    // Close the file
    fclose(file);

    // Display the menu and add items to the invoice
    int choice = 1;
    float totalAmount = 0.0;
    FILE *invoiceFile = fopen("invoice.txt", "w");
    if (invoiceFile == NULL)
    {
        printf("Unable to create the invoice file.\n");
        return 1;
    }
    int itemChoice;
    int quantity;
    float total;
    float vat;
    float pay;
    time_t t;
    time(&t);

    fprintf(invoiceFile, "************************************************\n");
    fprintf(invoiceFile, "*          Welcome to Eren's FastFood          *\n");
    fprintf(invoiceFile, "*            Where Yeagerists Meet             *\n");
    fprintf(invoiceFile, "************************************************\n\n");
    fprintf(invoiceFile, "------------------- Invoice --------------------\n");
    fprintf(invoiceFile, "  Item                      Quantity     Price  \n");
    fprintf(invoiceFile, "------------------------------------------------\n\n");

    while (choice != 3)
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\t************************************************\n");
        printf("\t\t\t\t\t\t*          Welcome to Eren's FastFood          *\n");
        printf("\t\t\t\t\t\t*            Where Yeagerists Meet             *\n");
        printf("\t\t\t\t\t\t************************************************\n\n");
        printf("\t\t\t\t\t\t--------------------- MENU ---------------------\n");
        printf("\t\t\t\t\t\t  Item                                   Price  \n");
        printf("\t\t\t\t\t\t                                      (vat exc.)\n\n");
        for (int i = 0; i < itemCount; i++)
        {
            printf("\t\t\t\t\t\t%2d. %-24s\t\t$%7.2f\n", i + 1, menu[i].name, menu[i].price);
        }
        printf("\t\t\t\t\t\t");
        for (int i = 0; i < 48; i++)
            printf("-");
        printf("\n\t\t\t\t\t\tDate and Time: %s", ctime(&t));
        printf("\t\t\t\t\t\t");
        for (int i = 0; i < 48; i++)
            printf("-");
        printf("\n\t\t\t\t\t\t1. Add item from the list.\n");
        printf("\t\t\t\t\t\t2. Clear list.\n");
        printf("\t\t\t\t\t\t3. Proceed to payment.\n");
        printf("\t\t\t\t\t\tEnter the corresponding number of the option you want to choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)
        {
        case 1:

            printf("\t\t\t\t\t\tEnter the item number you want to add: ");
            scanf("%d", &itemChoice);
            printf("\t\t\t\t\t\tEnter quantity: ");
            scanf("%d", &quantity);

            if (itemChoice >= 1 && itemChoice <= itemCount)
            {
                MenuItem selected = menu[itemChoice - 1];
                total = nPrice(selected.price, quantity);
                fprintf(invoiceFile, "%-22s\t       %2d      $%8.2f\n", selected.name, quantity, total);
                totalAmount += total;
                printf("\t\t\t\t\t\tItem added to the invoice.\n");
                getch();
                system("cls");
            }
            else
            {
                printf("\t\t\t\t\t\tInvalid item number.\a\n");
                getch();
                system("cls");
            }
            break;

        case 2:
            // Clear the invoice
            fclose(invoiceFile);
            invoiceFile = fopen("invoice.txt", "w");
            if (invoiceFile == NULL)
            {
                printf("Unable to create the invoice file.\n");
                return 1;
            }
            fprintf(invoiceFile, "************************************************\n");
            fprintf(invoiceFile, "*          Welcome to Eren's FastFood          *\n");
            fprintf(invoiceFile, "*            Where Yeagerists Meet             *\n");
            fprintf(invoiceFile, "************************************************\n\n");
            fprintf(invoiceFile, "------------------- Invoice --------------------\n");
            fprintf(invoiceFile, "  Item                      Quantity     Price  \n");
            fprintf(invoiceFile, "------------------------------------------------\n\n");
            totalAmount = 0.0;
            printf("\t\t\t\t\t\tInvoice cleared.\a\n");
            getch();
            system("cls");
            break;

        case 3:
            // Proceed to payment
            system("cls");
            vat = totalAmount * 0.25;
            fprintf(invoiceFile, "Total:                                 $%8.2f\n", totalAmount);
            fprintf(invoiceFile, "Vat(25%%):                              $%8.2f\n", vat);
            pay = totalAmount + vat + 20;
            fprintf(invoiceFile,"Delivery charge:                       $   20.00\n");
            fprintf(invoiceFile, "Total payable:                         $%8.2f\n", pay);
            fclose(invoiceFile);
            invoiceFile = fopen("invoice.txt", "r");
            if (invoiceFile == NULL)
            {
                printf("Unable to open the invoice file.\n");
                return 1;
            }
            printf("\n\n\n");
            while (fgets(line, sizeof(line), invoiceFile))
            {
                printf("\t\t\t\t\t\t%s", line);
            }

            fclose(invoiceFile);

            printf("\n\t\t\t\t\t\tOrder created successfully.\n");
            printf("\t\t\t\t\t\tPlease proceed to next step.\n");
            getch();
            break;

        default:
            printf("\t\t\t\t\t\tInvalid choice.\a\n");
            getch();
            system("cls");
            break;
        }
    }
    system("cls");
    printf("\n\n\n");
    printf("\t\t\t\t\t\tEnter your address: ");
    char address[100];
    fgets(address, sizeof(address), stdin);
    invoiceFile = fopen("invoice.txt", "a");
    fprintf(invoiceFile,"\nCustomer name: %s",customer);
    fprintf(invoiceFile, "\nAddress: %s", address);
    fprintf(invoiceFile,"\nDate and Time: %s", ctime(&t));
    system("cls");
    int paychoice = 0;
    char phone[20];
    while (1)
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\tFor payement choose any of the follow methods:\n");
        printf("\t\t\t\t\t\t1.Cash on Delivery.\n");
        printf("\t\t\t\t\t\t2.Bkash.\n");
        printf("\n\t\t\t\t\t\tEnter your choice: ");
        scanf("%d", &paychoice);
        if (paychoice == 1)
        {
            system("cls");
            break;
        }
        else if (paychoice == 2)
        {
            system("cls");
            printf("\n\n\n");
            printf("\t\t\t\t\t\tAmount $%7.2f will be credited from your account.\n", pay);
            printf("\t\t\t\t\t\tEnter your phone number: ");
            scanf("%s", phone);
            printf("\t\t\t\t\t\tProcessing Transaction");
            for (int i = 0; i < 15; i++)
            {
                printf(".");
                newDelay(30);
            }
            printf("\n\t\t\t\t\t\tAmount $%7.2f has been credited from your account.\n", pay);
            getch();
            break;
        }
        else
        {
            printf("\t\t\t\t\t\tInvalid input.\a");
            getch();
            system("cls");
        }
    }
    if (paychoice == 1)
    {
        fprintf(invoiceFile, "Payement system: Cash on Delivery.\n");
    }
    else if (paychoice == 2)
    {
        fprintf(invoiceFile, "Payment system: Bkash. Phone Number: %s\n", phone);
    }
    fclose(invoiceFile);
    system("cls");
    char invoicePrint;
    while (1)
    {
        printf("\n\n\n");
        printf("\t\t\t\t\t\tIf you want to keep a copy of invoice press 'y', if not the press 'n': ");
        scanf(" %c", &invoicePrint);
        if (invoicePrint == 'Y' || invoicePrint == 'y')
        {
            char command[100];
            sprintf(command, "notepad invoice.txt");

            int status = system(command);
            if (status == -1)
            {
                printf("Failed to open the invoice file.\n");
                return 1;
            }
            break;
        }
        else if (invoicePrint == 'N' || invoicePrint == 'n')
        {
            break;
        }
        else
        {
            printf("Invalid input.\a");
            getch();
            system("cls");
        }
    }
    return 0;
}

float nPrice(float i, int n)
{
    if (n == 1)
    {
        return i;
    }
    return i + nPrice(i, n - 1);
}

void newDelay(int number)
{
    // Input 100 is equal to 1 second
    int milli_seconds = 10 * number;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}
