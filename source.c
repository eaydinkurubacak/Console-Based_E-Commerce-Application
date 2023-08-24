#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

struct User // customer
{
    int user_id;
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
                return 100; // admin found
            }
            else
            {
                printf("Your user name and/or password is not correct. Please try again!\n");
                return -1; // admin found, wrong password
            }
        }
        else
        {
            if (!strcmp(user_name, users[i].user_name))
            {
                if (users[i].login_right == 0)
                {
                    printf("Your account has been blocked. please contact the administrator.\n");
                    return -1; // customer blocked
                }
                else
                {
                    if (!strcmp(password, users[i].password))
                    {
                        printf("Successfully logged in!\n");
                        users[i].login_right = 3;
                        return users[i].user_id; // customer found
                    }
                    else
                    {
                        users[i].login_right--;
                        if (users[i].login_right == 0)
                        {
                            printf("Your user name and/or password is not correct.\n");
                            printf("Your account has been blocked. please contact the administrator.\n");
                            return -1; // customer blocked
                        }
                        else
                        {
                            printf("Your user name and/or password is not correct. Please try again!\n");
                        }
                        return -1; // customer found, wrong password
                    }
                }
            }
        }
    }
    printf("Please enter valid admin or customer username.\n");
    return -1; // not found admin or customer
}

void createInitialUsers(struct User users[])
{
    // ahmet created
    users[0].user_id = 0;
    strcpy(users[0].user_name, "ahmet");
    strcpy(users[0].password, "1234");
    users[0].login_right = 3;

    // zeynep created
    users[1].user_id = 1;
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

struct Basket
{
    struct Product products[13];
    int size_basket;
    int product_amount[13];
    int total;
};

void createInitialBaskets(struct Basket baskets[])
{
    for (int i = 0; i < 100; i++)
    {
        baskets[i].size_basket = 0;
        baskets[i].total = 0;
    }
}

void calculateTotalAndShowBasket(struct Basket *basket)
{
    basket->total = 0;
    for (int i = 0; i < basket->size_basket; i++)
    {
        printf("%d.%s price=%d amount=%d total=%d$\n", i + 1, basket->products[i].name, basket->products[i].price, basket->product_amount[i], basket->product_amount[i] * basket->products[i].price);
        basket->total += basket->product_amount[i] * basket->products[i].price;
    }
    printf("Total %d$\n", basket->total);
}

void removeItemEditBasket(struct Basket *basket, int remove_item_index)
{
    for (int i = 0; i < basket->size_basket; i++)
    {
        if (i > remove_item_index)
        {
            basket->products[i - 1] = basket->products[i];
            basket->product_amount[i - 1] = basket->product_amount[i];
        }
        else
        {
            basket->total -= basket->products[i].price * basket->product_amount[i];
        }
    }
    basket->size_basket--;
}

void checkOutAndPrintReceipt(struct Product products[], struct Basket *basket)
{
    time_t current_time;
    struct tm *time_info;
    char time_string[80];
    for (int i = 0; i < basket->size_basket; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            if (!strcmp(basket->products[i].name, products[j].name))
            {
                products[j].stock_amount -= basket->product_amount[i];
            }
        }
    }

    printf("Processing your receipt...\n");
    printf("******* Medipol Online Market ********\n");
    printf("**************************************\n");
    printf("444 8 544\n");
    printf("medipol.edu.tr\n");
    printf("------------------------\n");
    calculateTotalAndShowBasket(basket);
    printf("------------------------\n");
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(time_string, sizeof(time_string), "%Y-%m-%d %H:%M:%S", time_info);
    printf("%s\n", time_string);
    printf("Thank You for using our Market!\n");

    basket->size_basket = 0;
    basket->total = 0;
}

int main()
{
    struct User users[100];
    struct Product products[13];
    int number_of_users = 2;
    char user_name[25];
    char password[25];
    int login_id = -1; // default : login_id = -1 , login_id == 1,2,.....,99 -> login successful (customer id), login_id == 100 -> login successful (admin)
    int main_menu_choice = 0;
    char search[25];
    struct Product search_result[13];
    int size_search_result = 0;
    int product_choice = 0;
    int product_amount = 0;
    bool is_return_mm = false;
    struct Basket baskets[100];
    int basket_sub_menu_choice = 0;
    int temp_bsm_choice = 0; // temp basket sub menu choice
    bool is_return_bsm = false;
    bool is_return_lp = false; // is return login page

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
                } while (!(main_menu_choice >= 1 && main_menu_choice <= 5)); // main_menu_choice validasyonu

                if (main_menu_choice == 1)
                {
                    printf("What are you searching for ? ");
                    scanf("%s", search);
                    searchForAProduct(search, products, search_result, &size_search_result);

                    if (size_search_result == 0)
                    {
                        do
                        {
                            printf("Your search did not match any items. Please try something else (Enter 0 for main menu) : ");
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

                        do
                        {
                            printf("Please select which item you want to add to your basket (1-%d / Enter 0 for main menu) : ", size_search_result);
                            scanf("%d", &product_choice);
                        } while (!(product_choice >= 0 && product_choice <= size_search_result)); // product_choice validasyonu
                        is_return_mm = product_choice == 0 ? true : false;

                        if (is_return_mm)
                        {
                            printf("Going back to main menu...\n");
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
                                printf("Going back to main menu...\n");
                            }
                            else
                            {
                                baskets[login_id].products[baskets[login_id].size_basket] = search_result[product_choice - 1];
                                baskets[login_id].product_amount[baskets[login_id].size_basket] = product_amount;
                                baskets[login_id].size_basket++;

                                printf("Added %s into your Basket.\n", search_result[product_choice - 1].name);
                                is_return_mm = true;
                                printf("Going back to main menu...\n");
                            }
                        }
                    }
                }
                else if (main_menu_choice == 2)
                {
                    do
                    {
                        is_return_bsm = false;
                        if (baskets[login_id].size_basket == 0)
                        {
                            printf("User's basket is empty.\n");
                            printf("Going back to main menu...\n");
                            is_return_mm = true;
                        }
                        else
                        {
                            printf("Your basket contains:\n");
                            calculateTotalAndShowBasket(&baskets[login_id]);
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
                                do
                                {
                                    printf("Please select which item to change its amount (1-%d) : ", baskets[login_id].size_basket);
                                    scanf("%d", &temp_bsm_choice);
                                } while (!(temp_bsm_choice >= 1 && temp_bsm_choice <= baskets[login_id].size_basket));

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
                                else
                                {
                                    baskets[login_id].product_amount[temp_bsm_choice - 1] = product_amount;
                                }

                                if (is_return_mm)
                                {
                                    printf("Going back to main menu...\n");
                                }
                                else
                                {
                                    is_return_bsm = true;
                                }
                            }
                            else if (basket_sub_menu_choice == 2)
                            {
                                do
                                {
                                    printf("Please select which item to remove (1-%d) : ", baskets[login_id].size_basket);
                                    scanf("%d", &temp_bsm_choice);
                                } while (!(temp_bsm_choice >= 1 && temp_bsm_choice <= baskets[login_id].size_basket));
                                removeItemEditBasket(&baskets[login_id], temp_bsm_choice - 1);
                                is_return_bsm = true;
                            }
                            else if (basket_sub_menu_choice == 3)
                            {
                                checkOutAndPrintReceipt(products, &baskets[login_id]);
                                is_return_mm = true;
                            }
                            else if (basket_sub_menu_choice == 4)
                            {
                                is_return_mm = true;
                            }
                        }

                    } while (is_return_bsm);
                }
                else if (main_menu_choice == 3)
                {
                    if (baskets[login_id].size_basket == 0)
                    {
                        printf("User's basket is empty.\n");
                    }
                    else
                    {
                        checkOutAndPrintReceipt(products, &baskets[login_id]);
                    }
                    printf("Going back to main menu...\n");
                    is_return_mm = true;
                }
                else if (main_menu_choice == 4)
                {
                    printf("Going back to login page...\n");
                    is_return_lp = true;
                }
                // exit için else{} durumu yazmaya gerek yok. is_return_lp = false -> her döngü başlangıçı
            } while (is_return_mm);
        }
    } while (is_return_lp);

    return 0;
}