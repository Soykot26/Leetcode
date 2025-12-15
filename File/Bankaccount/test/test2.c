#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* -------- Structure -------- */
struct Account {
    int accountNumber;
    char name[50];
    char password[20];
    float balance;
};

/* -------- Function Prototypes -------- */
void createAccount();
void loginSystem();
int generateAccountNumber();

/* -------- Main Control Module -------- */
int main() {
    int choice;

    while (1) {
        printf("\n====== Bank Account System ======\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                loginSystem();
                break;
            case 3:
                printf("Thank You!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

/* -------- Create Account Module -------- */
void createAccount() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.dat", "ab");
    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    acc.accountNumber = generateAccountNumber();

    printf("\n--- Create New Account ---\n");

    printf("Enter Name: ");
    getchar();
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = '\0';

    printf("Set Password: ");
    scanf("%s", acc.password);

    acc.balance = 0.0;

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!\n");
    printf("Your Account Number: %d\n", acc.accountNumber);
}

/* -------- Account Number Generator -------- */
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

/* -------- Login Module -------- */
void loginSystem() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    char pass[20];

    fp = fopen("accounts.dat", "rb");
    if (fp == NULL) {
        printf("No account found!\n");
        return;
    }

    printf("\n--- Login ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Password: ");
    scanf("%s", pass);

    while (fread(&acc, sizeof(acc), 1, fp)) {
        if (acc.accountNumber == accNo &&
            strcmp(acc.password, pass) == 0) {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found) {
        printf("\nLogin Successful!\n");
        printf("Welcome %s\n", acc.name);
        printf("Current Balance: %.2f\n", acc.balance);
    } else {
        printf("\nInvalid Account Number or Password!\n");
    }
}