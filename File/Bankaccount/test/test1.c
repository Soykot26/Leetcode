#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* --------- Structure --------- */
struct Account {
    int accountNumber;
    char name[50];
    char password[20];
    float balance;
};

/* --------- Function Prototypes --------- */
void createAccount();
void loginSystem();
void depositMoney(struct Account acc);
void withdrawMoney(struct Account acc);
void checkBalance(struct Account acc);
int generateAccountNumber();

/* --------- Main Control Module --------- */
int main() {
    int choice;

    while (1) {
        printf("\n====== Bank Account Management System ======\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                loginSystem();
                break;
            case 3:
                printf("Thank you for using the system.\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* --------- Create Account Module --------- */
void createAccount() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("File open failed!\n");
        return;
    }

    acc.accountNumber = generateAccountNumber();

    printf("\n--- Create New Account ---\n");
    printf("Enter Name: ");
    getchar();
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0;

    printf("Set Password: ");
    scanf("%s", acc.password);

    acc.balance = 0.0;

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
    printf("Your Account Number: %d\n", acc.accountNumber);
}

/* --------- Generate Account Number --------- */
int generateAccountNumber() {
    FILE *fp;
    struct Account acc;
    int lastAccNo = 1000;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        return lastAccNo + 1;
    }

    while (fread(&acc, sizeof(acc), 1, fp)) {
        lastAccNo = acc.accountNumber;
    }

    fclose(fp);
    return lastAccNo + 1;
}

/* --------- Login System --------- */
void loginSystem() {
    FILE *fp;
    struct Account acc;
    int accNo;
    char pass[20];
    int found = 0;

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    printf("\n--- Login ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Password: ");
    scanf("%s", pass);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo && strcmp(acc.password, pass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Invalid account number or password!\n");
        return;
    }

    int choice;
    while (1) {
        printf("\nWelcome %s\n", acc.name);
        printf("1. Deposit Money\n");
        printf("2. Withdraw Money\n");
        printf("3. Check Balance\n");
        printf("4. Logout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                depositMoney(acc);
                break;
            case 2:
                withdrawMoney(acc);
                break;
            case 3:
                checkBalance(acc);
                break;
            case 4:
                return;
            default:
                printf("Invalid choice!\n");
        }

        /* Reload updated data */
        fp = fopen("accounts.dat", "rb");
        while (fread(&acc, sizeof(acc), 1, fp)) {
            if (acc.accountNumber == accNo)
                break;
        }
        fclose(fp);
    }
}

/* --------- Deposit Module --------- */
void depositMoney(struct Account acc) {
    FILE *fp, *temp;
    float amount;

    printf("Enter deposit amount: ");
    scanf("%f", &amount);

    fp = fopen("accounts.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acc.accountNumber) {
            acc.balance += amount;
        }
        fwrite(&acc, sizeof(acc), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");

    printf("Deposit successful!\n");
}

/* --------- Withdraw Module --------- */
void withdrawMoney(struct Account acc) {
    FILE *fp, *temp;
    float amount;

    printf("Enter withdraw amount: ");
    scanf("%f", &amount);

    fp = fopen("accounts.dat", "rb");
    temp = fopen("temp.dat", "wb");

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == acc.accountNumber) {
            if (acc.balance >= amount) {
                acc.balance -= amount;
                printf("Withdrawal successful!\n");
            } else {
                printf("Insufficient balance!\n");
            }
        }
        fwrite(&acc, sizeof(acc), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("accounts.dat");
    rename("temp.dat", "accounts.dat");
}

/* --------- Balance Inquiry --------- */
void checkBalance(struct Account acc) {
    printf("\nCurrent Balance: %.2f\n", acc.balance);
}