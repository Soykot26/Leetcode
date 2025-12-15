#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =====================
// Structure Definitions
// =====================

typedef struct {
    int productID;
    char name[50];
    float price;
    int quantity;
} Product;

typedef struct {
    int billNumber;
    int productID;
    int quantity;
    float totalAmount;
    char date[20];
} Bill;

// =====================
// Function Declarations
// =====================

void adminMenu(void);
void cashierMenu(void);
void addProduct(void);
void viewProducts(void);
void generateBill(void);
void viewSalesReport(void);

// =====================
// Utility
// =====================

void clear_stdin(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// =====================
// Main Function (NO AUTHENTICATION)
// =====================

int main(void) {
    int choice;

    printf("=== Shop Billing System ===\n");
    printf("1. Admin\n");
    printf("2. Cashier\n");
    printf("Choose Role: ");

    if (scanf("%d", &choice) != 1) {
        printf("Invalid input!\n");
        return 0;
    }

    if (choice == 1) {
        adminMenu();
    } else if (choice == 2) {
        cashierMenu();
    } else {
        printf("Invalid role selected!\n");
    }

    return 0;
}

// =====================
// Admin Menu
// =====================

void adminMenu(void) {
    int choice = -1;

    do {
        printf("\n--- Admin Menu ---\n");
        printf("1. Add Product\n");
        printf("2. View Products\n");
        printf("3. View Sales Report\n");
        printf("0. Logout\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            continue;
        }

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: viewSalesReport(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

// =====================
// Product Management
// =====================

void addProduct(void) {
    FILE *fp = fopen("products.txt", "a");
    Product p;

    if (fp == NULL) {
        printf("Error opening products file!\n");
        return;
    }

    printf("Product ID: ");
    scanf("%d", &p.productID);
    clear_stdin();

    printf("Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = 0;

    printf("Price: ");
    scanf("%f", &p.price);
    printf("Quantity: ");
    scanf("%d", &p.quantity);

    fprintf(fp, "%d %s %.2f %d\n",
            p.productID, p.name, p.price, p.quantity);
    fclose(fp);

    printf("Product added successfully!\n");
}

void viewProducts(void) {
    FILE *fp = fopen("products.txt", "r");
    Product p;

    if (fp == NULL) {
        printf("No products found!\n");
        return;
    }

    printf("\nID\tName\t\tPrice\tQty\n");
    printf("--------------------------------------\n");

    while (fscanf(fp, "%d %49s %f %d",
                  &p.productID, p.name, &p.price, &p.quantity) == 4) {
        printf("%d\t%-10s\t%.2f\t%d\n",
               p.productID, p.name, p.price, p.quantity);
    }

    fclose(fp);
}

// =====================
// Cashier Menu
// =====================

void cashierMenu(void) {
    int choice = -1;

    do {
        printf("\n--- Cashier Menu ---\n");
        printf("1. View Products\n");
        printf("2. Generate Bill\n");
        printf("0. Logout\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            clear_stdin();
            continue;
        }

        switch (choice) {
            case 1: viewProducts(); break;
            case 2: generateBill(); break;
            case 0: break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}



// =====================
// Billing Module
// =====================

void generateBill(void) {
    FILE *fp = fopen("bills.txt", "a");
    Bill b;

    if (fp == NULL) {
        printf("Error opening bills file!\n");
        return;
    }

    printf("Bill Number: ");
    scanf("%d", &b.billNumber);
    printf("Product ID: ");
    scanf("%d", &b.productID);
    printf("Quantity: ");
    scanf("%d", &b.quantity);
    printf("Total Amount: ");
    scanf("%f", &b.totalAmount);

    printf("Date (DD/MM/YYYY): ");
    scanf("%19s", b.date);

    fprintf(fp, "%d %d %d %.2f %s\n",
            b.billNumber, b.productID, b.quantity, b.totalAmount, b.date);
    fclose(fp);

    printf("Bill generated successfully!\n");
}

// =====================
// Sales Report Module
// =====================

void viewSalesReport(void) {
    FILE *fp = fopen("bills.txt", "r");
    Bill b;

    if (fp == NULL) {
        printf("No sales data available!\n");
        return;
    }

    printf("\nBillNo\tProdID\tQty\tTotal\tDate\n");
    printf("-----------------------------------------\n");

    while (fscanf(fp, "%d %d %d %f %19s",
                  &b.billNumber, &b.productID, &b.quantity,
                  &b.totalAmount, b.date) == 5) {
        printf("%d\t%d\t%d\t%.2f\t%s\n",
               b.billNumber, b.productID, b.quantity,
               b.totalAmount, b.date);
    }

    fclose(fp);
}
