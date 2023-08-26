#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

struct User
{
    int user_id; // default : user_id = users array index
    char user_name[25];
    char password[25];
    int login_right; // default : login_right = 3, blocked : login_right = 0, unblocked : login_right = 3
};

struct Product
{
    char name[25];
    int stock_amount;
    int price;
};

struct Basket
{
    struct Product products[13];
    int number_of_items;
    int product_quantities[13];
    int total;
};

int login(char user_name[], char password[], struct User users[], int number_of_users)
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (!strcmp(user_name, "admin"))
        {
            if (!strcmp(password, "qwerty"))
            {
                printf("Successfully logged in!\n\n");
                return 100; // The value 100, which is not defined for the users array, is being used for admin login.
            }
            else
            {
                printf("Your user name and/or password is not correct. Please try again!\n");
                return -1; // Admin entered wrong password
            }
        }
        else
        {
            if (!strcmp(user_name, users[i].user_name))
            {
                if (users[i].login_right == 0)
                {
                    printf("Your account has been blocked. please contact the administrator.\n");
                    return -1; // User blocked
                }
                else
                {
                    if (!strcmp(password, users[i].password))
                    {
                        printf("Successfully logged in!\n\n");
                        users[i].login_right = 3;
                        return users[i].user_id; // The user ID of the user found in the system is being used for user login.
                    }
                    else
                    {
                        users[i].login_right--;
                        if (users[i].login_right == 0)
                        {
                            printf("Your user name and/or password is not correct.\n");
                            printf("Your account has been blocked. please contact the administrator.\n");
                            return -1; // User blocked
                        }
                        else
                        {
                            printf("Your user name and/or password is not correct. Please try again!\n");
                        }
                        return -1; // User entered wrong password
                    }
                }
            }
        }
    }
    printf("Please enter a valid admin or user username.\n");
    return -1; // No admin or user found in the system for the entered username.
}

void createInitialUsers(struct User users[])
{
    users[0].user_id = 0;
    strcpy(users[0].user_name, "ahmet");
    strcpy(users[0].password, "1234");
    users[0].login_right = 3;

    users[1].user_id = 1;
    strcpy(users[1].user_name, "zeynep");
    strcpy(users[1].password, "4444");
    users[1].login_right = 3;
}

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

char *toLowerCase(char string[])
{
    int len = strlen(string);
    char *result = (char *)malloc(len + 1);
    for (int i = 0; i < len; i++)
    {
        result[i] = tolower(string[i]);
    }
    result[len] = '\0';

    return result;
}

void searchForAProduct(char search[], struct Product products[], struct Product search_result[], int *size_sr)
{
    *size_sr = 0;
    for (int i = 0; i < 13; i++)
    {
        if (strstr(toLowerCase(products[i].name), toLowerCase(search)) != NULL && products[i].stock_amount != 0) // The product has been found.
        {
            search_result[*size_sr] = products[i];
            (*size_sr)++;
        }
    }
}

void createInitialBaskets(struct Basket baskets[])
{
    for (int i = 0; i < 100; i++)
    {
        baskets[i].number_of_items = 0;
        baskets[i].total = 0;
    }
}

void calculateTotalAndShowBasket(struct Basket *basket)
{
    basket->total = 0;
    printf("------------------------\n");
    for (int i = 0; i < basket->number_of_items; i++)
    {
        printf("%d.%s price=%d amount=%d total=%d$\n", i + 1, basket->products[i].name, basket->products[i].price, basket->product_quantities[i], basket->product_quantities[i] * basket->products[i].price);
        basket->total += basket->product_quantities[i] * basket->products[i].price;
    }
    printf("------------------------\n");
    printf("Total %d$\n", basket->total);
    printf("------------------------\n");
}

void removeItemAndEditBasket(struct Basket *basket, int remove_item_index)
{
    for (int i = 0; i < basket->number_of_items; i++)
    {
        if (i > remove_item_index)
        {
            basket->products[i - 1] = basket->products[i];
            basket->product_quantities[i - 1] = basket->product_quantities[i];
        }
        else
        {
            basket->total -= basket->products[i].price * basket->product_quantities[i];
        }
    }
    basket->number_of_items--;
}

void removeUserAndEditUsersAndTheirBaskets(struct User users[], int number_of_users, int remove_user_index, struct Basket baskets[])
{
    for (int i = 0; i < number_of_users; i++)
    {
        if (i > remove_user_index)
        {
            users[i].user_id--;
            users[i - 1] = users[i];
            baskets[i - 1] = baskets[i];
        }
    }
}

void checkOutAndPrintReceipt(struct Product products[], struct Basket *basket)
{
    time_t current_time;
    struct tm *time_info;
    char time_string[80];
    for (int i = 0; i < basket->number_of_items; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (!strcmp(basket->products[i].name, products[j].name))
            {
                products[j].stock_amount -= basket->product_quantities[i];
            }
        }
    }

    printf("Processing your receipt...\n");
    printf("******* Medipol Online Market ********\n");
    printf("**************************************\n");
    printf("444 8 544\n");
    printf("medipol.edu.tr\n");
    calculateTotalAndShowBasket(basket);
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
    printf("%s\n", time_string);
    printf("Thank You for using our Market!\n");

    basket->number_of_items = 0;
    basket->total = 0;
}

char *editStringForDisplay(char string[], int result_sl)
{
    int len = strlen(string);
    char *result = (char *)malloc(result_sl + 1);

    for (int i = 0; i < result_sl; i++)
    {
        if (i < len)
        {
            result[i] = string[i];
        }
        else
        {
            result[i] = ' ';
        }
    }
    result[result_sl] = '\0';

    return result;
}

void displayUsers(struct User users[], int number_of_users)
{
    char list_order[5];
    printf("Displaying users...\n");
    printf("     %s  %s  %s\n", editStringForDisplay("Username", 24), editStringForDisplay("Password", 24), editStringForDisplay("Status", 9));
    for (int i = 0; i < number_of_users; i++)
    {
        sprintf(list_order, "%d.", i + 1);
        printf("%s%s  %s  %s\n", editStringForDisplay(list_order, 5), editStringForDisplay(users[i].user_name, 24), editStringForDisplay(users[i].password, 24), users[i].login_right == 0 ? editStringForDisplay("Blocked", 9) : editStringForDisplay("Unblocked", 9));
    }
}

int main()
{
    // struct arrays
    struct User users[100];
    struct Product products[13];
    struct Basket baskets[100];
    struct Product search_result[13];

    // System variables
    int number_of_users = 2;
    int login_id = -1;
    int size_sr = 0; // size_search_result
    int c;           // clear the input buffer

    // Menu choices
    int main_menu_choice = 0;
    int basket_sub_menu_choice = 0;
    int temp_bsm_choice = 0; // temp basket sub menu choice
    int admin_sub_menu_choice = 0;

    // Input variables
    char user_name[25];
    char password[25];
    char search[25];
    int product_choice = 0;
    int product_amount = 0;

    // Loop control variables
    bool is_return_mm = false;  // is return basket main menu
    bool is_return_bsm = false; // is return basket sub menu
    bool is_return_lp = false;  // is return login page

    // System Initialization
    createInitialUsers(users);
    createProducts(products);
    createInitialBaskets(baskets);

    do
    {
        is_return_lp = false;
        printf("****Welcome to Medipol Online Market****\n");
        printf("Please log in by providing your user credentials:\n");
        do
        {
            printf("User Name : ");
            scanf("%s", user_name);
            printf("Password : ");
            scanf("%s", password);
            login_id = login(user_name, password, users, number_of_users);

        } while (login_id == -1);

        printf("Welcome, %s! Please choose one of the following options by entering the corresponding menu number.\n", user_name);

        if (login_id == 100)
        {
            do
            {
                is_return_mm = false;
                printf("Please choose one of the following services:\n");
                printf("1. Activate User Account\n");
                printf("2. Deactivate User Account\n");
                printf("3. Add User\n");
                printf("4. Remove User\n");
                printf("5. Logout\n");
                printf("6. Exit\n");
                do
                {
                    printf("Your selection (1-6) : ");
                    scanf("%d", &main_menu_choice);
                } while (!(main_menu_choice >= 1 && main_menu_choice <= 6));

                if (main_menu_choice == 1)
                {
                    printf("\n");
                    displayUsers(users, number_of_users);
                    do
                    {
                        printf("Please choose one of the users above to activate his/her account (1-%d / Enter 0 for main menu) : ", number_of_users);
                        scanf("%d", &admin_sub_menu_choice);
                    } while (!(admin_sub_menu_choice >= 0 && admin_sub_menu_choice <= number_of_users));
                    is_return_mm = admin_sub_menu_choice == 0 ? true : false;

                    if (!is_return_mm)
                    {
                        if (users[admin_sub_menu_choice - 1].login_right == 0)
                        {
                            users[admin_sub_menu_choice - 1].login_right = 3;
                            printf("The activation process for the selected user is being completed...\n");
                        }
                        else
                        {
                            printf("The user you are trying to unblock is not currently blocked.\n");
                        }
                        is_return_mm = true;
                    }
                    printf("Going back to main menu...\n\n");
                }
                else if (main_menu_choice == 2)
                {
                    printf("\n");
                    displayUsers(users, number_of_users);
                    do
                    {
                        printf("Please choose one of the users above to deactivate his/her account (1-%d / Enter 0 for main menu) : ", number_of_users);
                        scanf("%d", &admin_sub_menu_choice);
                    } while (!(admin_sub_menu_choice >= 0 && admin_sub_menu_choice <= number_of_users));
                    is_return_mm = admin_sub_menu_choice == 0 ? true : false;

                    if (!is_return_mm)
                    {
                        if (users[admin_sub_menu_choice - 1].login_right == 0)
                        {
                            printf("The user you are trying to block is already blocked.\n");
                        }
                        else
                        {
                            users[admin_sub_menu_choice - 1].login_right = 0;
                            printf("The deactivation process for the selected user is being completed...\n");
                        }
                        is_return_mm = true;
                    }
                    printf("Going back to main menu...\n\n");
                }
                else if (main_menu_choice == 3)
                {
                    printf("\n");
                    while ((c = getchar()) != '\n')
                    {
                        // Clear the input buffer (main_menu_choice's '\n' character)
                    }

                    do
                    {
                        printf("Please enter the username of the new user to be added (Enter 0 for main menu) : ");
                        fgets(user_name, 50, stdin);

                        user_name[strlen(user_name) - 1] = '\0';
                        if (strlen(user_name) == 0)
                        {
                            printf("The username cannot be left blank\n");
                        }
                        else if (strlen(user_name) > 24)
                        {
                            printf("Username should be a maximum of 24 characters in length\n");
                        }
                        else
                        {
                            if (strchr(user_name, ' ') != NULL)
                            {
                                printf("Username should not contain whitespace characters !\n");
                            }
                        }
                    } while (!(strlen(user_name) != 0 && strlen(user_name) <= 24 && strrchr(user_name, ' ') == NULL));
                    // Clean buffer

                    is_return_mm = !strcmp(user_name, "0") ? true : false;
                    if (!is_return_mm)
                    {
                        do
                        {
                            printf("Please enter the password for the new user to be added (Enter 0 for main menu) : ");
                            fgets(password, 50, stdin);

                            password[strlen(password) - 1] = '\0';
                            if (strlen(password) == 0)
                            {
                                printf("The password cannot be left blank\n");
                            }
                            else if (strlen(password) > 24)
                            {
                                printf("Password should be a maximum of 24 characters in length\n");
                            }
                            else
                            {
                                if (strchr(password, ' ') != NULL)
                                {
                                    printf("Password should not contain whitespace characters !\n");
                                }
                            }
                        } while (!(strlen(password) != 0 && strlen(password) <= 24 && strrchr(password, ' ') == NULL));
                        // Clean buffer

                        is_return_mm = !strcmp(password, "0") ? true : false;
                        if (!is_return_mm)
                        {
                            users[number_of_users].user_id = number_of_users;
                            strcpy(users[number_of_users].user_name, user_name);
                            strcpy(users[number_of_users].password, password);
                            users[number_of_users].login_right = 3;
                            number_of_users++;
                            printf("The process of adding a new user is being completed...\n");
                            is_return_mm = true;
                        }
                    }
                    printf("Going back to main menu...\n\n");
                }
                else if (main_menu_choice == 4)
                {
                    printf("\n");
                    displayUsers(users, number_of_users);
                    do
                    {
                        printf("Please choose one of the users above to remove his/her account (1-%d / Enter 0 for main menu) : ", number_of_users);
                        scanf("%d", &admin_sub_menu_choice);
                    } while (!(admin_sub_menu_choice >= 0 && admin_sub_menu_choice <= number_of_users));
                    is_return_mm = admin_sub_menu_choice == 0 ? true : false;

                    if (!is_return_mm)
                    {
                        removeUserAndEditUsersAndTheirBaskets(users, number_of_users, admin_sub_menu_choice - 1, baskets);
                        number_of_users--;
                        printf("The process of removing a user is being completed...\n");
                        is_return_mm = true;
                    }
                    printf("Going back to main menu...\n\n");
                }
                else if (main_menu_choice == 5)
                {
                    printf("Going back to login page...\n\n");
                    is_return_lp = true;
                }
            } while (is_return_mm);
        }
        else
        {
            do
            {
                is_return_mm = false;
                printf("Please choose one of the following services:\n");
                printf("1. Search for a product\n");
                printf("2. See Basket\n");
                printf("3. Check Out\n");
                printf("4. Logout\n");
                printf("5. Exit\n");

                do
                {
                    printf("Your selection (1-5) : ");
                    scanf("%d", &main_menu_choice);
                } while (!(main_menu_choice >= 1 && main_menu_choice <= 5));

                if (main_menu_choice == 1)
                {
                    printf("\n");
                    printf("What are you searching for ? ");
                    scanf("%s", search);
                    searchForAProduct(search, products, search_result, &size_sr);

                    if (size_sr == 0)
                    {
                        do
                        {
                            printf("Your search did not match any items. Please try something else (Enter 0 for main menu) : ");
                            scanf("%s", search);
                            is_return_mm = !strcmp(search, "0") ? true : false;
                            if (!is_return_mm)
                            {
                                searchForAProduct(search, products, search_result, &size_sr);
                            }
                        } while (!is_return_mm && size_sr == 0);
                    }

                    if (is_return_mm)
                    {
                        printf("Going back to main menu...\n\n");
                    }
                    else
                    {
                        printf("\n");
                        printf("found %d similar items:\n", size_sr);
                        for (int i = 0; i < size_sr; i++)
                        {
                            printf("%d.%s %d$\n", i + 1, search_result[i].name, search_result[i].price);
                        }

                        do
                        {
                            printf("Please select which item you want to add to your basket (1-%d / Enter 0 for main menu) : ", size_sr);
                            scanf("%d", &product_choice);
                        } while (!(product_choice >= 0 && product_choice <= size_sr));
                        is_return_mm = product_choice == 0 ? true : false;

                        if (is_return_mm)
                        {
                            printf("Going back to main menu...\n\n");
                        }
                        else
                        {
                            do
                            {
                                printf("Adding %s. Enter Amount (Entered amount must be greater than zero) : ", search_result[product_choice - 1].name);
                                scanf("%d", &product_amount);
                            } while (!(product_amount > 0));

                            if (product_amount > search_result[product_choice - 1].stock_amount)
                            {
                                do
                                {
                                    printf("Sorry! The amount exceeds the limit, Please try again with smaller amount\n");
                                    do
                                    {
                                        printf("Amount (Entered amount must be greater than zero / Enter 0 for main menu) : ");
                                        scanf("%d", &product_amount);
                                    } while (product_amount < 0);

                                    is_return_mm = product_amount == 0 ? true : false;
                                } while (!is_return_mm && product_amount > search_result[product_choice - 1].stock_amount);
                            }

                            if (is_return_mm)
                            {
                                printf("Going back to main menu...\n\n");
                            }
                            else
                            {
                                baskets[login_id].products[baskets[login_id].number_of_items] = search_result[product_choice - 1];
                                baskets[login_id].product_quantities[baskets[login_id].number_of_items] = product_amount;
                                baskets[login_id].number_of_items++;

                                printf("Added %s into your Basket.\n", search_result[product_choice - 1].name);
                                is_return_mm = true;
                                printf("Going back to main menu...\n\n");
                            }
                        }
                    }
                }
                else if (main_menu_choice == 2)
                {
                    printf("\n");
                    do
                    {
                        is_return_bsm = false;
                        if (baskets[login_id].number_of_items == 0)
                        {
                            printf("User's basket is empty.\n");
                            printf("Going back to main menu...\n\n");
                            is_return_mm = true;
                        }
                        else
                        {
                            printf("Your basket contains:\n");
                            calculateTotalAndShowBasket(&baskets[login_id]);
                            printf("\n");
                            printf("Please choose an option:\n");
                            printf("1.Update amount\n");
                            printf("2.Remove an item\n");
                            printf("3.Check out\n");
                            printf("4.Go back to main menu\n");
                            do
                            {
                                printf("Your selection (1-4) : ");
                                scanf("%d", &basket_sub_menu_choice);
                            } while (!(basket_sub_menu_choice >= 1 && basket_sub_menu_choice <= 4));

                            if (basket_sub_menu_choice == 1)
                            {
                                printf("\n");
                                do
                                {
                                    printf("Please select which item to change its amount (1-%d) : ", baskets[login_id].number_of_items);
                                    scanf("%d", &temp_bsm_choice);
                                } while (!(temp_bsm_choice >= 1 && temp_bsm_choice <= baskets[login_id].number_of_items));

                                do
                                {
                                    printf("Please type the new amount (Entered amount must be greater than zero) : ");
                                    scanf("%d", &product_amount);
                                } while (!(product_amount > 0));

                                if (product_amount > baskets[login_id].products[temp_bsm_choice - 1].stock_amount)
                                {
                                    do
                                    {
                                        printf("Sorry! The amount exceeds the limit, Please try again with smaller amount\n");
                                        do
                                        {
                                            printf("Amount (Entered amount must be greater than zero / Enter 0 for main menu) : ");
                                            scanf("%d", &product_amount);
                                        } while (product_amount < 0);
                                        is_return_mm = product_amount == 0 ? true : false;
                                    } while (!is_return_mm && product_amount > baskets[login_id].products[temp_bsm_choice - 1].stock_amount);
                                }

                                if (is_return_mm)
                                {
                                    printf("Going back to main menu...\n\n");
                                }
                                else
                                {
                                    baskets[login_id].product_quantities[temp_bsm_choice - 1] = product_amount;
                                    printf("\n");
                                    is_return_bsm = true;
                                }
                            }
                            else if (basket_sub_menu_choice == 2)
                            {
                                printf("\n");
                                do
                                {
                                    printf("Please select which item to remove (1-%d) : ", baskets[login_id].number_of_items);
                                    scanf("%d", &temp_bsm_choice);
                                } while (!(temp_bsm_choice >= 1 && temp_bsm_choice <= baskets[login_id].number_of_items));
                                removeItemAndEditBasket(&baskets[login_id], temp_bsm_choice - 1);
                                printf("\n");
                                is_return_bsm = true;
                            }
                            else if (basket_sub_menu_choice == 3)
                            {
                                printf("\n");
                                checkOutAndPrintReceipt(products, &baskets[login_id]);
                                printf("Going back to main menu...\n\n");
                                is_return_mm = true;
                            }
                            else if (basket_sub_menu_choice == 4)
                            {
                                printf("Going back to main menu...\n\n");
                                is_return_mm = true;
                            }
                        }

                    } while (is_return_bsm);
                }
                else if (main_menu_choice == 3)
                {
                    printf("\n");
                    if (baskets[login_id].number_of_items == 0)
                    {
                        printf("User's basket is empty.\n");
                    }
                    else
                    {
                        checkOutAndPrintReceipt(products, &baskets[login_id]);
                    }
                    printf("Going back to main menu...\n\n");
                    is_return_mm = true;
                }
                else if (main_menu_choice == 4)
                {
                    printf("Going back to login page...\n\n");
                    is_return_lp = true;
                }

            } while (is_return_mm);
        }
    } while (is_return_lp);

    return 0;
}