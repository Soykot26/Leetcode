#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- Structures -------- */
struct Account {
    int accountNumber;
    char name[50];
    char password[20];
    float balance;
};

struct Admin {
    char id[10];
    char name[50];
    char password[20];
};

/* -------- Function Prototypes -------- */
void initAdmin();
void adminLogin();
void adminMenu();
void viewAllAccounts();
void updateAdminInfo();

void createAccount();
void loginSystem();
void accountMenu(struct Account acc);
void depositMoney(struct Account acc);
void withdrawMoney(struct Account acc);
void updateAccount(struct Account acc);
void updateAccountInfo(struct Account acc);

int generateAccountNumber();
int getAccountByNumber(int accNo, struct Account *acc);

/* -------- Helper -------- */
void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

/* -------- Main -------- */
int main() {
    int choice;
    initAdmin();

    while (1) {
        printf("\n===== Bank Account Management System =====\n");
        printf("1. Create Account\n");
        printf("2. User Login\n");
        printf("3. Admin Login\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar(); // clear buffer

        switch (choice) {
            case 1: createAccount(); break;
            case 2: loginSystem(); break;
            case 3: adminLogin(); break;
            case 4:
                printf("Thank you for using the system.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

/* ================= ADMIN PART ================= */

void initAdmin() {
    FILE *fp = fopen("admin.txt", "r");
    if (fp) {
        fclose(fp);
        return;
    }

    fp = fopen("admin.txt", "w");
    struct Admin admin = {"0001", "Default Admin", "admin"};
    fprintf(fp, "%s,%s,%s\n", admin.id, admin.name, admin.password);
    fclose(fp);
}

void adminLogin() {
    struct Admin admin;
    char id[10], pass[20];
    FILE *fp = fopen("admin.txt", "r");

    if (!fp) {
        printf("Admin file not found!\n");
        return;
    }

    fscanf(fp, "%9[^,],%49[^,],%19[^\n]",
           admin.id, admin.name, admin.password);
    fclose(fp);

    printf("\nAdmin ID: ");
    scanf("%s", id);
    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(id, admin.id) == 0 && strcmp(pass, admin.password) == 0) {
        printf("Admin login successful!\n");
        adminMenu();
    } else {
        printf("Invalid admin credentials!\n");
    }
}

void adminMenu() {
    int choice;
    while (1) {
        printf("\n===== Admin Menu =====\n");
        printf("1. View All Accounts\n");
        printf("2. Update Admin Info\n");
        printf("3. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: viewAllAccounts(); break;
            case 2: updateAdminInfo(); break;
            case 3: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void updateAdminInfo() {
    struct Admin admin;
    FILE *fp = fopen("admin.txt", "r");
    if (!fp) return;

    fscanf(fp, "%9[^,],%49[^,],%19[^\n]",
           admin.id, admin.name, admin.password);
    fclose(fp);

    printf("New Admin Name: ");
    fgets(admin.name, sizeof(admin.name), stdin);
    removeNewline(admin.name);

    printf("New Password: ");
    scanf("%19s", admin.password);

    fp = fopen("admin.txt", "w");
    fprintf(fp, "%s,%s,%s\n",
            admin.id, admin.name, admin.password);
    fclose(fp);

    printf("Admin info updated successfully!\n");
}

// void viewAllAccounts() {
//     FILE *fp = fopen("accounts.txt", "r");
//     struct Account acc;
//     int count = 0;
//
//     if (!fp) {
//         printf("No accounts found!\n");
//         return;
//     }
//
//     printf("\nAccNo\tName\t\tBalance\n");
//     while (fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
//            &acc.accountNumber, acc.name,
//            acc.password, &acc.balance) != EOF) {

//         printf("%d\t%-15s\t%.2f\n",
//                acc.accountNumber, acc.name, acc.balance);
//         count++;
//     }
//     fclose(fp);

//     printf("Total Users: %d\n", count);
// }

