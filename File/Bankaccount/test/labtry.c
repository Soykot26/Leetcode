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

/* -------- Main Function -------- */
int main() {
    int choice;

    while (1) {
        printf("\n===== Bank Account System =====\n");
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
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
}

/* -------- Create Account (SAVE to TXT file) -------- */
void createAccount() {
    struct Account acc;
    FILE *fp;

    fp = fopen("accounts.txt", "a");   // append text
    if (fp == NULL) {
        printf("File cannot be opened!\n");
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

    /* SAVE DATA IN TXT FILE */
    fprintf(fp, "%d %s %s %.2f\n",
            acc.accountNumber,
            acc.name,
            acc.password,
            acc.balance);

    fclose(fp);

    printf("\nAccount Created Successfully!\n");
    printf("Account Number: %d\n", acc.accountNumber);
}

/* -------- Generate Account Number -------- */
int generateAccountNumber() {
    FILE *fp;
    struct Account acc;
    int lastAccNo = 1000;

    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        return lastAccNo + 1;
    }

    while (fscanf(fp, "%d %s %s %f",
                  &acc.accountNumber,
                  acc.name,
                  acc.password,
                  &acc.balance) != EOF) {
        lastAccNo = acc.accountNumber;
    }

    fclose(fp);
    return lastAccNo + 1;
}

/* -------- Login System (READ from TXT file) -------- */
void loginSystem() {
    FILE *fp;
    struct Account acc;
    int accNo, found = 0;
    char pass[20];

    fp = fopen("accounts.txt", "r");
    if (fp == NULL) {
        printf("No account data found!\n");
        return;
    }

    printf("\n--- Login ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &accNo);

    printf("Enter Password: ");
    scanf("%s", pass);

    /* READ DATA FROM TXT FILE */
    while (fscanf(fp, "%d %s %s %f",
                  &acc.accountNumber,
                  acc.name,
                  acc.password,
                  &acc.balance) != EOF) {
        if (acc.accountNumber == accNo &&
            strcmp(acc.password, pass) == 0) {
            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found) {
        printf("\nLogin Successful!\n");
        printf("Name: %s\n", acc.name);
        printf("Balance: %.2f\n", acc.balance);
    } else {
        printf("\nInvalid Account Number or Password!\n");
    }
}
