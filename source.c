#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct User // customer
{
    char user_name[25];
    char password[25];
    int login_right; // default : login_right = 3 , unblocked işleminde login_right = 3 , login_right == 0 -> blocked , login_right != 0 -> not blocked
};

int login(char user_name[], char password[], struct User users[], int number_of_users)
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (!strcmp(user_name, "admin"))
        {
            if (!strcmp(password, "qwerty"))
            {
                printf("Successfully logged in!\n");
                return 1; // admin found
            }
            else
            {
                printf("Your user name and/or password is not correct. Please try again!\n");
                return 0; // admin found, wrong password
            }
        }
        else
        {
            if (!strcmp(user_name, users[i].user_name))
            {
                if (users[i].login_right == 0)
                {
                    printf("Your account has been blocked. please contact the administrator.\n");
                    return 0; // customer blocked
                }
                else
                {
                    if (!strcmp(password, users[i].password))
                    {
                        printf("Successfully logged in!\n");
                        users[i].login_right = 3;
                        return 2; // customer found
                    }
                    else
                    {
                        users[i].login_right--;
                        if (users[i].login_right == 0)
                        {
                            printf("Your user name and/or password is not correct.\n");
                            printf("Your account has been blocked. please contact the administrator.\n");
                            return 0; // customer blocked
                        }
                        else
                        {
                            printf("Your user name and/or password is not correct. Please try again!\n");
                        }
                        return 0; // customer found, wrong password
                    }
                }
            }
        }
    }
    printf("Please enter valid admin or customer username.\n");
    return 0; // not found admin or customer
}

void createInitialUsers(struct User users[])
{
    // ahmet created
    strcpy(users[0].user_name, "ahmet");
    strcpy(users[0].password, "1234");
    users[0].login_right = 3;

    // zeynep created
    strcpy(users[1].user_name, "zeynep");
    strcpy(users[1].password, "4444");
    users[1].login_right = 3;
}

struct Product
{
    char name[25];
    int stock_amount;
    int price;
};

void createProducts(struct Product products[])
{
    strcpy(products[0].name, "Asparagus");
    products[0].stock_amount = 10;
    products[0].price = 5;
    strcpy(products[1].name, "Broccoli");
    products[1].stock_amount = 15;
    products[1].price = 6;
    strcpy(products[2].name, "Carrots");
    products[2].stock_amount = 18;
    products[2].price = 7;
    strcpy(products[3].name, "Apples");
    products[3].stock_amount = 20;
    products[3].price = 5;
    strcpy(products[4].name, "Banana");
    products[4].stock_amount = 10;
    products[4].price = 8;
    strcpy(products[5].name, "Berries");
    products[5].stock_amount = 30;
    products[5].price = 3;
    strcpy(products[6].name, "Eggs");
    products[6].stock_amount = 50;
    products[6].price = 2;
    strcpy(products[7].name, "Mixed fruit juice");
    products[7].stock_amount = 0;
    products[7].price = 8;
    strcpy(products[8].name, "Fish Sticks");
    products[8].stock_amount = 25;
    products[8].price = 12;
    strcpy(products[9].name, "Ice Cream");
    products[9].stock_amount = 32;
    products[9].price = 6;
    strcpy(products[10].name, "Apple Juice");
    products[10].stock_amount = 40;
    products[10].price = 7;
    strcpy(products[11].name, "Orange Juice");
    products[11].stock_amount = 30;
    products[11].price = 8;
    strcpy(products[12].name, "Grape Juice");
    products[12].stock_amount = 10;
    products[12].price = 9;
}

char *toLowerString(char string[])
{
    int len = strlen(string);
    char *result = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        result[i] = tolower(string[i]);
    }
    result[len] = '\0'; // Null-terminate the result string

    return result;
}

void searchForAProduct(char search[], struct Product products[], struct Product search_result[], int *size_search_result)
{
    *size_search_result = 0;
    for (int i = 0; i < 13; i++)
    {
        if (strstr(toLowerString(products[i].name), toLowerString(search)) != NULL && products[i].stock_amount != 0) // product found
        {
            search_result[*size_search_result] = products[i];
            (*size_search_result)++;
        }
    }
}

int main()
{
    struct User users[100];
    struct Product products[13];
    int number_of_users = 2;
    char user_name[25];
    char password[25];
    int login_status = 0; // default : login_status = 0 , login_status == 1,2 -> login successful
    int main_menu_choice = 0;
    char search[25];
    struct Product search_result[13];
    int size_search_result = 0;
    int product_choice = 0;
    int product_amount = 0;
    bool is_return_mm;

    createInitialUsers(users);
    createProducts(products);

    printf("****Welcome to Medipol Online Market****\n");
    printf("Please log in by providing your user credentials:\n");
    do
    {
        printf("User Name:");
        scanf("%s", user_name);
        printf("Password:");
        scanf("%s", password);
        login_status = login(user_name, password, users, number_of_users);

    } while (!login_status);

    printf("Welcome, %s! Please choose one of the following options by entering the corresponding menu number.\n", user_name);

    if (login_status == 1)
    {
    }
    else
    {
        do
        {
            printf("Please choose one of the following services:\n");
            printf("1. Search for a product\n");
            printf("2. See Basket\n");
            printf("3. Check Out\n");
            printf("4. Logout\n");
            printf("5. Exit\n");

            do
            {
                printf("Your choice (1-5) : ");
                scanf("%d", &main_menu_choice);
            } while (!(main_menu_choice >= 1 && main_menu_choice <= 5));

            if (main_menu_choice == 1)
            {
                is_return_mm = false;
                printf("What are you searching for? ");
                scanf("%s", search);
                searchForAProduct(search, products, search_result, &size_search_result);

                if (size_search_result == 0)
                {
                    do
                    {
                        printf("Your search did not match any items. Please try something else (Enter 0 for main menu): ");
                        scanf("%s", search);
                        is_return_mm = !strcmp(search, "0") ? true : false;
                        if (!is_return_mm)
                        {
                            searchForAProduct(search, products, search_result, &size_search_result);
                        }
                    } while (!is_return_mm && size_search_result == 0);
                }

                if (is_return_mm)
                {
                    printf("Going back to main menu...\n");
                }
                else
                {
                    printf("found %d similar items:\n", size_search_result);
                    for (int i = 0; i < size_search_result; i++)
                    {
                        printf("%d.%s %d$\n", i + 1, search_result[i].name, search_result[i].price);
                    }
                    printf("Please select which item you want to add to your basket (Enter 0 for main menu): ");
                    scanf("%d", &product_choice);
                    is_return_mm = product_choice == 0 ? true : false;

                    if (is_return_mm)
                    {
                        printf("Going back to main menu...\n");
                    }
                    else
                    {
                        printf("Adding %s. Enter Amount: ", search_result[product_choice - 1].name);
                        scanf("%d", &product_amount);
                        if (product_amount > search_result[product_choice - 1].stock_amount)
                        {
                            do
                            {
                                printf("Sorry! The amount exceeds the limit, Please try again with smaller amount\n");
                                printf("Amount (Enter 0 for main menu): ");
                                scanf("%d", &product_amount);
                                is_return_mm = product_amount == 0 ? true : false;
                            } while (!is_return_mm && product_amount > search_result[product_choice - 1].stock_amount);
                        }

                        if (is_return_mm)
                        {
                            printf("Going back to main menu...\n");
                        }
                        else
                        {
                            printf("Added %s into your Basket.\n", search_result[product_choice - 1].name);
                            is_return_mm = true;
                            printf("Going back to main menu...\n");
                        }
                    }
                }
            }
        } while (is_return_mm);
    }

    return 0;
}