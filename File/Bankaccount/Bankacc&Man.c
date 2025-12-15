#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<errno.h>
#define ACCOUNTS_FILE "accounts.txt"
#define USER_FILE "users.txt"
#define TRANSACTIONS_FILE "transactions.txt"
#define MAX_LINE 237

typedef struct {
    char accNo;
    char name[50];
    char email[50];
    char password[50];
    double balance;
} Account;
// Function prototypes

void admin_menu();
void user_menu(int accNo);
void create_account();
void create_account();
void deposit_money();
void withdraw_money();
void check_balance();
void view_account_details();
void update_account();
void delete_account();
// Authentication functions

int authenticate_admin();
int authenticate_user();
//helper hand

void clear_stdin();
//implementation of functions

void clear_stdin() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);{}
}
void create_account(){
    Account acc;
    acc.accNo= generate_account_number();// part of uthility functions
    printf("\n--- Create New Account ---\n");
    clear_stdin();
    printf("Enter Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline character
    printf("Enter Email: ");
    if(fgets(acc.email,sizeof(acc.email),stdin)==NULL) strcpy(acc.email,"");
    acc.email[strcspn(acc.email, "\n")] = 0; // Remove newline character
    printf("Enter Password(no space): ");
    if(scanf("%19s",acc.password)!=1) strcpy(acc.password,"password");
    clear_stdin();
    printf("Enter Initial Deposit Amount: ");
    if(scanf("%lf",&acc.balance)!=1) acc.balance=0.0;
    clear_stdin();
    // Save account to file
    if(save_account_to_file(&acc)){
        printf("Account created successfully! Your Account Number is: %d\n", acc.accNo);
        char note[128];
        snprintf(note,sizeof(note),"Account created for %s",acc.name);
        log_transaction("CREATE",acc.accNo,acc.balance,note);

    } else {
        printf("Error creating account. Please try again.\n");
    }
    press_enter_to_continue();//part of uthility functions

}
void deposit_money() {
    int accNo;
    double amount;
    printf("\n--- Deposit Money ---\n");
    printf("Enter account number: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    printf("Enter amount to deposit: ");
    if (scanf("%lf", &amount) != 1) { clear_stdin(); return; }
    clear_stdin();
    if (amount <= 0) {
        printf("Invalid amount.\n");
        press_enter_to_continue();
        return;
    }
    Account acc;
    if (!load_account(accNo, &acc)) {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    acc.balance += amount;
    if (update_account_in_file(&acc)) {
        printf("Deposit successful. New balance: %.2f\n", acc.balance);
        log_transaction("DEPOSIT", accNo, amount, "Deposit made");
    } else {
        printf("Failed to update account.\n");
    }
    press_enter_to_continue();
}
void withdraw_money() {
    int accNo;
    double amount;
    printf("\n--- Withdraw Money ---\n");
    printf("Enter account number: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    printf("Enter amount to withdraw: ");
    if (scanf("%lf", &amount) != 1) { clear_stdin(); return; }
    clear_stdin();
    if (amount <= 0) {
        printf("Invalid amount.\n");
        press_enter_to_continue();
        return;
    }
    Account acc;
    if (!load_account(accNo, &acc)) {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    if (acc.balance < amount) {
        printf("Insufficient balance. Current balance: %.2f\n", acc.balance);
        press_enter_to_continue();
        return;
    }
    acc.balance -= amount;
    if (update_account_in_file(&acc)) {
        printf("Withdrawal successful. New balance: %.2f\n", acc.balance);
        log_transaction("WITHDRAW", accNo, amount, "Withdrawal made");
    } else {
        printf("Failed to update account.\n");
    }
    press_enter_to_continue();
}
void check_balance() {
    int accNo;
    printf("\n--- Check Balance ---\n");
    printf("Enter account number: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    clear_stdin();
    Account acc;
    if (!load_account(accNo, &acc)) {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    printf("Account: %d\nName: %s\nBalance: %.2f\n", acc.accNo, acc.name, acc.balance);
    press_enter_to_continue();
}

void view_account_details() {
    int accNo;
    printf("\n--- View Account Details ---\n");
    printf("Enter account number: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    clear_stdin();
    Account acc;
    if (!load_account(accNo, &acc)) {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    printf("Account No: %d\nName: %s\nEmail: %s\nBalance: %.2f\n", acc.accNo, acc.name, acc.email, acc.balance);
    press_enter_to_continue();
}
// updated acc detail by admin
void update_account() {
    int accNo;
    printf("\n--- Update Account ---\n");
    printf("Enter account number to update: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    clear_stdin();
    Account acc;
    if (!load_account(accNo, &acc)) //uthility function
    {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    printf("Updating account %d — leave blank to keep current value.\n", accNo);
    char tmp[100];
    clear_stdin();
    printf("Current name: %s\nNew name: ", acc.name);
    if (fgets(tmp, sizeof(tmp), stdin)) {
        tmp[strcspn(tmp, "\n")] = 0;
        if (strlen(tmp) > 0) strncpy(acc.name, tmp, sizeof(acc.name));
    }
    printf("Current email: %s\nNew email: ", acc.email);
    if (fgets(tmp, sizeof(tmp), stdin)) {
        tmp[strcspn(tmp, "\n")] = 0;
        if (strlen(tmp) > 0) strncpy(acc.email, tmp, sizeof(acc.email));
    }
    printf("Change password? (y/n): ");
    char ch;
    if (scanf(" %c", &ch) == 1 && (ch == 'y' || ch == 'Y')) {
        printf("Enter new password (no spaces): ");
        if (scanf("%19s", acc.password) != 1) strcpy(acc.password, "password");
    }
    clear_stdin();

    if (update_account_in_file(&acc)) //uthility function
    {
        printf("Account updated successfully.\n");
        log_transaction("UPDATE", accNo, 0.0, "Account details updated");
    } else {
        printf("Failed to update account.\n");
    }
    press_enter_to_continue();
}

//for Delete account part (admin) */
void delete_account() {
    int accNo;
    printf("\n--- Delete Account (Admin) ---\n");
    printf("Enter account number to delete: ");
    if (scanf("%d", &accNo) != 1) { clear_stdin(); return; }
    clear_stdin();
    Account acc;
    if (!load_account(accNo, &acc)) {
        printf("Account not found.\n");
        press_enter_to_continue();
        return;
    }
    printf("Are you sure to delete account %d (%s)? This action cannot be undone. (y/n): ", acc.accNo, acc.name);
    char ch;
    if (scanf(" %c", &ch) != 1) { clear_stdin(); return; }
    clear_stdin();
    if (ch == 'y' || ch == 'Y') {
        if (delete_account_from_file(accNo)) // from utility function
         {
            printf("Account deleted successfully.\n");
            char note[128];
            snprintf(note, sizeof(note), "Deleted account of %s", acc.name);
            log_transaction("DELETE", accNo, 0.0, note);
        } else {
            printf("Failed to delete account.\n");
        }
    } else {
        printf("Deletion cancelled.\n");
    }
    press_enter_to_continue();
}