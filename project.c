#include <stdio.h>
#include <string.h>
#include <time.h>

#define BANK_NAME "Siddhartha Bank Limited"
#define MAX 100

struct BankAccount {
    char acc_no[20];
    char password[20];
    char acc_name[50];
    float balance;
    char created_time[30];
};

struct BankAccount accounts[MAX] = {
    {"101", "pass101", "Alice", 5000.50, "2026/03/13"},
    {"102", "pass102", "Bob", 12000.75, "2026/03/25"},
    {"103", "pass103", "Charlie", 8000.00, "2025/10/24"}
};

int total = 3;

/* ---------- TIME ---------- */
void getTime(char *buffer) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(buffer, "%d-%02d-%02d %02d:%02d",
            tm.tm_year + 1900,
            tm.tm_mon + 1,
            tm.tm_mday,
            tm.tm_hour,
            tm.tm_min);
}

/* ---------- FIND ACCOUNT ---------- */
int findAccount(char num[]) {
    for (int i = 0; i < total; i++) {
        if (strcmp(accounts[i].acc_no, num) == 0) {
            return i;
        }
    }
    return -1;
}

/* ---------- DISPLAY ---------- */
void showAccount(int i) {
    printf("\n===== %s =====\n", BANK_NAME);
    printf("Account Name   : %s\n", accounts[i].acc_name);
    printf("Account Number : %s\n", accounts[i].acc_no);
    printf("Balance        : %.2f\n", accounts[i].balance);
    printf("Created Time   : %s\n", accounts[i].created_time);
}

/* ---------- LOGIN ---------- */
int login() {
    char num[20], pass[20];

    printf("\n--- %s Login ---\n", BANK_NAME);

    printf("Account Number: ");
    scanf("%s", num);

    int index = findAccount(num);

    if (index == -1) {
        printf("Account Number  %s not found! Please visit the nearest branch or call 01-55098 for any help. Thankyou.\n");
        return -1;
    }

    printf("Password: ");
    scanf("%s", pass);

    if (strcmp(accounts[index].password, pass) == 0) {
        return index;
    } else {
        printf("Wrong password!\n");
        return -1;
    }
}

/* ---------- CREATE ACCOUNT ---------- */
void createAccount() {

    if (total >= MAX) {
        printf("Bank storage full!\n");
        return;
    }

    printf("\n--- Create Account (%s) ---\n", BANK_NAME);

    printf("Enter Account Number: ");
    scanf("%s", accounts[total].acc_no);

    if (findAccount(accounts[total].acc_no) != -1) {
        printf("Account already exists!\n");
        return;
    }

    printf("Enter Password: ");
    scanf("%s", accounts[total].password);

    printf("Enter Account Name: ");
    scanf("%s", accounts[total].acc_name);

    printf("Enter Initial Balance: ");
    scanf("%f", &accounts[total].balance);

    getTime(accounts[total].created_time);

    total++;

    printf("Account created successfully!\n");
}

/* ---------- USER MENU ---------- */
void userMenu(int i) {
    int choice;
    float amount;

    do {
        showAccount(i);

        printf("\n1. Deposit\n");
        printf("2. Withdraw\n");
        printf("3. Transfer\n");
        printf("4. Logout\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {

            printf("Enter deposit amount: ");
            scanf("%f", &amount);

            if (amount > 0) {
                accounts[i].balance += amount;
                printf("Deposit successful!\n");
            }

        } else if (choice == 2) {

            printf("Enter withdraw amount: ");
            scanf("%f", &amount);

            if (amount <= accounts[i].balance && amount > 0) {
                accounts[i].balance -= amount;
                printf("Withdrawal successful!\n");
            } else {
                printf("Not enough balance!\n");
            }

        } else if (choice == 3) {

            char target[20];

            printf("Enter receiver account number: ");
            scanf("%s", target);

            int t = findAccount(target);

            if (t == -1) {
                printf("Receiver not found!\n");
                continue;
            }

            printf("Enter amount: ");
            scanf("%f", &amount);

            if (amount > 0 && amount <= accounts[i].balance) {

                accounts[i].balance -= amount;
                accounts[t].balance += amount;

                char timeNow[30];
                getTime(timeNow);

                printf("\n--- Transfer Receipt ---\n");
                printf("Bank: %s\n", BANK_NAME);
                printf("From: %s (%s)\n", accounts[i].acc_name, accounts[i].acc_no);
                printf("To  : %s (%s)\n", accounts[t].acc_name, accounts[t].acc_no);
                printf("Amount: %.2f\n", amount);
                printf("Time  : %s\n", timeNow);

            } else {
                printf("Transfer failed!\n");
            }

        }

    } while (choice != 4);
}

/* ---------- MAIN ---------- */
int main() {
    int choice;

    while (1) {

        printf("\n==== %s ====\n", BANK_NAME);
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        if (choice == 1) {

            int user = login();
            if (user != -1) {
                userMenu(user);
            }

        } else if (choice == 2) {

            createAccount();

        } else if (choice == 3) {

            printf("Thank you for using %s\n", BANK_NAME);
            break;

        } else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}