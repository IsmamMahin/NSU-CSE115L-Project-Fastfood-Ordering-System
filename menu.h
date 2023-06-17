#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_ITEMS 100
#define MAX_NAME_LENGTH 50

// Structure to represent a menu item
typedef struct
{
    char name[MAX_NAME_LENGTH];
    float price;
} MenuItem;

float nPrice(float, int);

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

    fprintf(invoiceFile, "************************************************\n");
    fprintf(invoiceFile, "*          Welcome to Eren's FastFood          *\n");
    fprintf(invoiceFile, "*            Where Yeagerists Meet             *\n");
    fprintf(invoiceFile, "************************************************\n\n");
    fprintf(invoiceFile, "------------------- Invoice --------------------\n");
    fprintf(invoiceFile, "  Item                      Quantity     Price  \n");
    fprintf(invoiceFile, "------------------------------------------------\n\n");

    while (choice != 3)
    {
        printf("************************************************\n");
        printf("*          Welcome to Eren's FastFood          *\n");
        printf("*            Where Yeagerists Meet             *\n");
        printf("************************************************\n\n");
        printf("--------------------- MENU ---------------------\n");
        printf("  Item                                   Price  \n");
        printf("                                      (vat exc.)\n\n");
        for (int i = 0; i < itemCount; i++)
        {
            printf("%d. %-24s\t\t$%7.2f\n", i + 1, menu[i].name, menu[i].price);
        }

        printf("\n1. Add item from the list.\n");
        printf("2. Clear list.\n");
        printf("3. Proceed to payment.\n");
        printf("Enter the corresponding number of the option you want to choose: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:

            printf("Enter the item number you want to add: ");
            scanf("%d", &itemChoice);
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            if (itemChoice >= 1 && itemChoice <= itemCount)
            {
                MenuItem selected = menu[itemChoice - 1];
                total = nPrice(selected.price, quantity);
                fprintf(invoiceFile, "%-22s\t       %2d      $%8.2f\n", selected.name, quantity, total);
                totalAmount += total;
                printf("Item added to the invoice.\n");
                system("cls");
            }
            else
            {
                printf("Invalid item number.\n");
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
            printf("Invoice cleared.\n");
            getch();
            system("cls");
            break;

        case 3:
            // Proceed to payment
            system("cls");
            vat = totalAmount * 0.25;
            fprintf(invoiceFile, "Total:                                 $%8.2f\n", totalAmount);
            fprintf(invoiceFile, "Vat(25%%):                              $%8.2f\n", vat);
            pay = totalAmount + vat;
            fprintf(invoiceFile, "Total payable:                         $%8.2f\n", pay);
            fclose(invoiceFile);
            invoiceFile = fopen("invoice.txt", "r");
            if (invoiceFile == NULL)
            {
                printf("Unable to open the invoice file.\n");
                return 1;
            }

            char line[100];

            while (fgets(line, sizeof(line), invoiceFile))
            {
                printf("%s", line);
            }

            fclose(invoiceFile);

            printf("\nInvoice created successfully.\n");
            printf("Please proceed to the payment.\n");
            getch();
            break;

        default:
            printf("Invalid choice.\n");
            getch();
            system("cls");
            break;
        }
    }

    fclose(invoiceFile);
    system("cls");
    int paychoice = 0;
    char phone[20];
    while (1)
    {
        printf("For payement choose any of the follow methods:\n");
        printf("1.Cash on Delivery.\n");
        printf("2.Bkash.\n");
        printf("\nEnter your choice: ");
        scanf("%d", &paychoice);
        if (paychoice == 1)
        {
            system("cls");
            break;
        }
        else if (paychoice == 2)
        {
            system("cls");
            printf("Amount $%7.2f will be credited from your account.\n", pay);
            printf("Enter you phone number: ");
            scanf("%s", &phone);
            printf("Amount $%7.2f has been credited from your account.\n", pay);
            getch();
            break;
        }
        else
        {
            printf("Invalid input.");
            getch();
            system("cls");
        }
    }
    invoiceFile = fopen("invoice.txt", "a");
    if (paychoice == 1)
    {
        fprintf(invoiceFile, "Payement system: Cash on Delivery.\n");
    }
    else if (paychoice == 2)
    {
        fprintf(invoiceFile, "Payment system: Bkash. Phone Number: %s\n", phone);
    }
    fclose(invoiceFile);
    char invoicePrint;
    while (1)
    {
        printf("If you want to keep a copy of invoice press 'y', if not the press 'n': ");
        scanf(" %c", &invoicePrint);
        if (invoicePrint == 'Y' || invoicePrint == 'y')
        {
            char command[100];
            sprintf(command, "notepad invoice.txt"); // Replace "text-editor" with the command to open your preferred text editor.

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
            printf("Invalid input.");
            getch();
            system("cls");
        }
    }
}

float nPrice(float i, int n)
{
    if (n == 1)
    {
        return i;
    }
    return i + nPrice(i, n - 1);
}
