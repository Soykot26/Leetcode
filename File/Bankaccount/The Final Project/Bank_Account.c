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
