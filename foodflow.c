#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    FOODFLOW
    Online Food Order Management System

    Data Structures:
    1. Linked List      -> Food Menu
    2. Queue            -> Normal Orders
    3. Priority Queue   -> Priority Orders
    4. Stack            -> Cancelled Orders
    5. Searching        -> Search Food
    6. Sorting          -> Sort Food by Price
*/


/* ================= FOOD LINKED LIST ================= */

typedef struct Food
{
    int id;
    char name[50];
    char category[30];
    float price;

    struct Food *next;

} Food;


Food *menuHead = NULL;


/* ADD FOOD */

void addFood(
    int id,
    char name[],
    char category[],
    float price)
{
    Food *newFood =
        (Food *)malloc(sizeof(Food));

    newFood->id = id;

    strcpy(newFood->name, name);

    strcpy(newFood->category, category);

    newFood->price = price;

    newFood->next = NULL;


    if (menuHead == NULL)
    {
        menuHead = newFood;
    }
    else
    {
        Food *temp = menuHead;

        while (temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newFood;
    }
}


/* DISPLAY MENU */

void displayMenu()
{
    Food *temp = menuHead;

    printf("\n============================================\n");
    printf("              FOOD MENU\n");
    printf("============================================\n");

    while (temp != NULL)
    {
        printf(
            "%d. %-25s %-12s Rs. %.2f\n",
            temp->id,
            temp->name,
            temp->category,
            temp->price
        );

        temp = temp->next;
    }
}


/* SEARCH FOOD */

void searchFood(char keyword[])
{
    Food *temp = menuHead;

    int found = 0;

    printf("\nSearch Results:\n");

    while (temp != NULL)
    {
        if (
            strstr(temp->name, keyword) != NULL
            ||
            strstr(temp->category, keyword) != NULL
        )
        {
            printf(
                "%d. %s - Rs. %.2f\n",
                temp->id,
                temp->name,
                temp->price
            );

            found = 1;
        }

        temp = temp->next;
    }

    if (!found)
    {
        printf("No food item found.\n");
    }
}


/* ================= ORDER QUEUE ================= */

typedef struct Order
{
    int orderId;
    char customer[50];
    float amount;

    struct Order *next;

} Order;


Order *front = NULL;
Order *rear = NULL;


/* PLACE NORMAL ORDER */

void placeOrder(
    int id,
    char customer[],
    float amount)
{
    Order *newOrder =
        (Order *)malloc(sizeof(Order));

    newOrder->orderId = id;

    strcpy(
        newOrder->customer,
        customer
    );

    newOrder->amount = amount;

    newOrder->next = NULL;


    if (rear == NULL)
    {
        front = rear = newOrder;
    }
    else
    {
        rear->next = newOrder;

        rear = newOrder;
    }

    printf(
        "\nOrder #%d added to Queue.\n",
        id
    );
}


/* PROCESS ORDER */

void processOrder()
{
    if (front == NULL)
    {
        printf("\nNo pending orders.\n");
        return;
    }


    Order *temp = front;

    printf(
        "\nProcessing Order #%d",
        temp->orderId
    );

    printf(
        "\nCustomer: %s",
        temp->customer
    );

    printf(
        "\nAmount: Rs. %.2f\n",
        temp->amount
    );


    front = front->next;


    if (front == NULL)
    {
        rear = NULL;
    }


    free(temp);
}


/* DISPLAY ORDERS */

void displayOrders()
{
    Order *temp = front;

    if (temp == NULL)
    {
        printf("\nNo pending orders.\n");
        return;
    }


    printf("\n========== PENDING ORDERS ==========\n");


    while (temp != NULL)
    {
        printf(
            "Order #%d | %s | Rs. %.2f\n",
            temp->orderId,
            temp->customer,
            temp->amount
        );

        temp = temp->next;
    }
}


/* ================= PRIORITY QUEUE ================= */

typedef struct PriorityOrder
{
    int orderId;
    char customer[50];
    int priority;

    struct PriorityOrder *next;

} PriorityOrder;


PriorityOrder *priorityFront = NULL;


/* ADD PRIORITY ORDER */

void addPriorityOrder(
    int id,
    char customer[],
    int priority)
{
    PriorityOrder *newOrder =
        (PriorityOrder *)
        malloc(sizeof(PriorityOrder));


    newOrder->orderId = id;

    strcpy(
        newOrder->customer,
        customer
    );

    newOrder->priority = priority;

    newOrder->next = NULL;


    if (
        priorityFront == NULL
        ||
        priority >
        priorityFront->priority
    )
    {
        newOrder->next =
            priorityFront;

        priorityFront =
            newOrder;
    }
    else
    {
        PriorityOrder *temp =
            priorityFront;


        while (
            temp->next != NULL
            &&
            temp->next->priority >= priority
        )
        {
            temp = temp->next;
        }


        newOrder->next =
            temp->next;

        temp->next =
            newOrder;
    }


    printf(
        "\nPriority Order #%d added.\n",
        id
    );
}


/* PROCESS PRIORITY ORDER */

void processPriorityOrder()
{
    if (priorityFront == NULL)
    {
        printf(
            "\nNo priority orders.\n"
        );

        return;
    }


    PriorityOrder *temp =
        priorityFront;


    printf(
        "\nProcessing Priority Order #%d\n",
        temp->orderId
    );


    printf(
        "Customer: %s\n",
        temp->customer
    );


    priorityFront =
        priorityFront->next;


    free(temp);
}


/* ================= CANCEL STACK ================= */

typedef struct CancelledOrder
{
    int orderId;

    char reason[100];

    struct CancelledOrder *next;

} CancelledOrder;


CancelledOrder *top = NULL;


/* CANCEL ORDER */

void cancelOrder(
    int orderId,
    char reason[])
{
    CancelledOrder *newOrder =
        (CancelledOrder *)
        malloc(sizeof(CancelledOrder));


    newOrder->orderId =
        orderId;


    strcpy(
        newOrder->reason,
        reason
    );


    newOrder->next = top;

    top = newOrder;


    printf(
        "\nOrder #%d cancelled.\n",
        orderId
    );
}


/* DISPLAY CANCELLED ORDERS */

void displayCancelled()
{
    CancelledOrder *temp = top;


    if (temp == NULL)
    {
        printf(
            "\nNo cancelled orders.\n"
        );

        return;
    }


    printf(
        "\n========== CANCELLED ORDERS ==========\n"
    );


    while (temp != NULL)
    {
        printf(
            "Order #%d | Reason: %s\n",
            temp->orderId,
            temp->reason
        );

        temp = temp->next;
    }
}


/* ================= SORTING ================= */

void sortFoodByPrice()
{
    if (menuHead == NULL)
        return;


    Food *i;

    Food *j;


    for (i = menuHead;
         i != NULL;
         i = i->next)
    {
        for (
            j = i->next;
            j != NULL;
            j = j->next
        )
        {
            if (
                i->price > j->price
            )
            {
                int tempId =
                    i->id;

                i->id =
                    j->id;

                j->id =
                    tempId;


                char tempName[50];

                strcpy(
                    tempName,
                    i->name
                );

                strcpy(
                    i->name,
                    j->name
                );

                strcpy(
                    j->name,
                    tempName
                );


                float tempPrice =
                    i->price;

                i->price =
                    j->price;

                j->price =
                    tempPrice;
            }
        }
    }


    printf(
        "\nMenu sorted by price.\n"
    );
}


/* ================= SAMPLE DATA ================= */

void initializeMenu()
{
    addFood(
        1,
        "Margherita Pizza",
        "Pizza",
        249
    );

    addFood(
        2,
        "Farmhouse Pizza",
        "Pizza",
        299
    );

    addFood(
        3,
        "Classic Burger",
        "Burger",
        159
    );

    addFood(
        4,
        "Cheese Burger",
        "Burger",
        189
    );

    addFood(
        5,
        "Chicken Biryani",
        "Indian",
        220
    );

    addFood(
        6,
        "Paneer Biryani",
        "Indian",
        190
    );

    addFood(
        7,
        "Hakka Noodles",
        "Noodles",
        179
    );

    addFood(
        8,
        "Chocolate Cake",
        "Dessert",
        149
    );
}


/* ================= MAIN ================= */

int main()
{
    int choice;

    initializeMenu();


    while (1)
    {
        printf(
            "\n\n===================================="
        );

        printf(
            "\n       FOODFLOW MANAGEMENT SYSTEM"
        );

        printf(
            "\n===================================="
        );


        printf(
            "\n1. Display Food Menu"
        );

        printf(
            "\n2. Search Food"
        );

        printf(
            "\n3. Sort Food by Price"
        );

        printf(
            "\n4. Place Normal Order"
        );

        printf(
            "\n5. Process Normal Order"
        );

        printf(
            "\n6. Display Pending Orders"
        );

        printf(
            "\n7. Add Priority Order"
        );

        printf(
            "\n8. Process Priority Order"
        );

        printf(
            "\n9. Cancel Order"
        );

        printf(
            "\n10. View Cancelled Orders"
        );

        printf(
            "\n11. Exit"
        );


        printf(
            "\n\nEnter choice: "
        );

        scanf(
            "%d",
            &choice
        );


        switch (choice)
        {
            case 1:

                displayMenu();

                break;


            case 2:
            {
                char keyword[50];

                printf(
                    "Enter food/category: "
                );

                scanf(
                    "%s",
                    keyword
                );

                searchFood(keyword);

                break;
            }


            case 3:

                sortFoodByPrice();

                displayMenu();

                break;


            case 4:
            {
                int id;

                char customer[50];

                float amount;


                printf(
                    "Enter Order ID: "
                );

                scanf(
                    "%d",
                    &id
                );


                printf(
                    "Enter Customer Name: "
                );

                scanf(
                    "%s",
                    customer
                );


                printf(
                    "Enter Amount: "
                );

                scanf(
                    "%f",
                    &amount
                );


                placeOrder(
                    id,
                    customer,
                    amount
                );

                break;
            }


            case 5:

                processOrder();

                break;


            case 6:

                displayOrders();

                break;


            case 7:
            {
                int id;

                int priority;

                char customer[50];


                printf(
                    "Enter Order ID: "
                );

                scanf(
                    "%d",
                    &id
                );


                printf(
                    "Enter Customer Name: "
                );

                scanf(
                    "%s",
                    customer
                );


                printf(
                    "Enter Priority Level: "
                );

                scanf(
                    "%d",
                    &priority
                );


                addPriorityOrder(
                    id,
                    customer,
                    priority
                );

                break;
            }


            case 8:

                processPriorityOrder();

                break;


            case 9:
            {
                int id;

                char reason[100];


                printf(
                    "Enter Order ID: "
                );

                scanf(
                    "%d",
                    &id
                );


                printf(
                    "Enter Cancellation Reason: "
                );

                scanf(
                    "%s",
                    reason
                );


                cancelOrder(
                    id,
                    reason
                );

                break;
            }


            case 10:

                displayCancelled();

                break;


            case 11:

                printf(
                    "\nThank you for using FoodFlow!\n"
                );

                return 0;


            default:

                printf(
                    "\nInvalid choice.\n"
                );
        }
    }


    return 0;
}