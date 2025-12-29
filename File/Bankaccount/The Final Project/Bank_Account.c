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

/* Function Prototypes */
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


void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


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

/*  ADMIN PART */

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


void viewAllAccounts() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account acc;
    int count = 0;

    if (!fp) {
        printf("No accounts found!\n");
        return;
    }

    printf("\nAccNo\tName\t\tBalance\n");

    while (fscanf(fp, "%d,%49[^,],%19[^,],%f",
           &acc.accountNumber,
           acc.name,
           acc.password,
           &acc.balance) == 4) {

        printf("%d\t%-15s\t%.2f\n",
               acc.accountNumber,
               acc.name,
               acc.balance);
        count++;
    }

    fclose(fp);
    printf("Total Users: %d\n", count);
}


/* USER PART */

void createAccount() {
    struct Account acc;
    FILE *fp = fopen("accounts.txt", "a");

    if (!fp) {
        printf("File error!\n");
        return;
    }

    acc.accountNumber = generateAccountNumber();
    acc.balance = 0.0;

    printf("Enter Full Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    removeNewline(acc.name);

    printf("Set Password: ");
    scanf("%19s", acc.password);

    fprintf(fp, "%d,%s,%s,%.2f\n",
            acc.accountNumber,
            acc.name,
            acc.password,
            acc.balance);

    fclose(fp);

    printf("Account created successfully!\n");
    printf("Account Number: %d\n", acc.accountNumber);
}

int generateAccountNumber() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account acc;
    int last = 1000;

    if (!fp) return last + 1;

    while (fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
           &acc.accountNumber, acc.name,
           acc.password, &acc.balance) != EOF) {
        last = acc.accountNumber;
    }
    fclose(fp);
    return last + 1;
}

void loginSystem() {
    FILE *fp = fopen("accounts.txt", "r");
    struct Account acc;
    int accNo, found = 0;
    char pass[20];

    if (!fp) {
        printf("No accounts found!\n");
        return;
    }

    printf("Account Number: ");
    scanf("%d", &accNo);
    printf("Password: ");
    scanf("%19s", pass);

    while (fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
           &acc.accountNumber, acc.name,
           acc.password, &acc.balance) != EOF) {

        if (acc.accountNumber == accNo &&
            strcmp(acc.password, pass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("Login successful!\n");
        accountMenu(acc);
    } else {
        printf("Invalid login!\n");
    }
}

void accountMenu(struct Account acc) {
    int choice;
    while (1) {
        getAccountByNumber(acc.accountNumber, &acc);

        printf("\n===== Account Menu =====\n");
        printf("1. Deposit\n2. Withdraw\n3. View\n4. Update Info\n5. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: depositMoney(acc); break;
            case 2: withdrawMoney(acc); break;
            case 3:
                printf("Name: %s\nBalance: %.2f\n",
                       acc.name, acc.balance);
                break;
            case 4: updateAccountInfo(acc); break;
            case 5: return;
            default: printf("Invalid choice!\n");
        }
    }
}

void depositMoney(struct Account acc) {
    float amount;
    printf("Amount to deposit: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }

    acc.balance += amount;
    updateAccount(acc);
    printf("Deposit successful!\n");
}

void withdrawMoney(struct Account acc) {
    float amount;
    printf("Amount to withdraw: ");
    scanf("%f", &amount);

    if (amount <= 0 || amount > acc.balance) {
        printf("Invalid amount!\n");
        return;
    }

    acc.balance -= amount;
    updateAccount(acc);
    printf("Withdrawal successful!\n");
}

void updateAccountInfo(struct Account acc) {
    printf("New Full Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    removeNewline(acc.name);

    printf("New Password: ");
    scanf("%19s", acc.password);

    updateAccount(acc);
    printf("Account updated successfully!\n");
}

void updateAccount(struct Account updatedAcc) {
    FILE *fp = fopen("accounts.txt", "r");
    FILE *tmp = fopen("temp.txt", "w");
    struct Account acc;

    if (!fp || !tmp) return;

    while (fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
           &acc.accountNumber, acc.name,
           acc.password, &acc.balance) != EOF) {

        if (acc.accountNumber == updatedAcc.accountNumber)
            fprintf(tmp, "%d,%s,%s,%.2f\n",
                    updatedAcc.accountNumber,
                    updatedAcc.name,
                    updatedAcc.password,
                    updatedAcc.balance);
        else
            fprintf(tmp, "%d,%s,%s,%.2f\n",
                    acc.accountNumber,
                    acc.name,
                    acc.password,
                    acc.balance);
    }

    fclose(fp);
    fclose(tmp);
    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");
}

int getAccountByNumber(int accNo, struct Account *acc) {
    FILE *fp = fopen("accounts.txt", "r");
    if (!fp) return 0;

    while (fscanf(fp, "%d,%49[^,],%19[^,],%f\n",
           &acc->accountNumber,
           acc->name,
           acc->password,
           &acc->balance) != EOF) {

        if (acc->accountNumber == accNo) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}