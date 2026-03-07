#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct BankAccount {
    int accNo;
    char name[50];
    float balance;
};

struct BankAccount accounts[MAX];
int count = 0;

void saveTransaction(char message[]) {
    FILE *fp = fopen("transactions.txt", "a");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fp, "%s\n", message);
    fclose(fp);
}

void createAccount() {
    printf("Enter Account Number: ");
    scanf("%d", &accounts[count].accNo);
    printf("Enter Name: ");
    scanf("%s", accounts[count].name);
    printf("Enter Initial Balance: ");
    scanf("%f", &accounts[count].balance);

    saveTransaction("New Account Created");
    count++;
    printf("Account Created Successfully!\n");
}

void deposit() {
    int acc, i;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc);

    for(i = 0; i < count; i++) {
        if(accounts[i].accNo == acc) {
            printf("Enter Deposit Amount: ");
            scanf("%f", &amount);
            accounts[i].balance += amount;

            saveTransaction("Deposit Transaction");
            printf("Amount Deposited Successfully!\n");
            return;
        }
    }
    printf("Account Not Found!\n");
}

void withdraw() {
    int acc, i;
    float amount;
    printf("Enter Account Number: ");
    scanf("%d", &acc);

    for(i = 0; i < count; i++) {
        if(accounts[i].accNo == acc) {
            printf("Enter Withdrawal Amount: ");
            scanf("%f", &amount);

            if(accounts[i].balance >= amount) {
                accounts[i].balance -= amount;
                saveTransaction("Withdrawal Transaction");
                printf("Withdrawal Successful!\n");
            } else {
                printf("Insufficient Balance!\n");
            }
            return;
        }
    }
    printf("Account Not Found!\n");
}

void display() {
    for(int i = 0; i < count; i++) {
        printf("\nAccount No: %d", accounts[i].accNo);
        printf("\nName: %s", accounts[i].name);
        printf("\nBalance: %.2f\n", accounts[i].balance);
    }
}

void sortByBalance() {
    struct BankAccount temp;
    for(int i = 0; i < count - 1; i++) {
        for(int j = 0; j < count - i - 1; j++) {
            if(accounts[j].balance > accounts[j+1].balance) {
                temp = accounts[j];
                accounts[j] = accounts[j+1];
                accounts[j+1] = temp;
            }
        }
    }
    printf("Accounts Sorted by Balance.\n");
}

void searchAccount() {
    int acc;
    printf("Enter Account Number to Search: ");
    scanf("%d", &acc);

    for(int i = 0; i < count; i++) {
        if(accounts[i].accNo == acc) {
            printf("Account Found!\n");
            printf("Name: %s\n", accounts[i].name);
            printf("Balance: %.2f\n", accounts[i].balance);
            return;
        }
    }
    printf("Account Not Found!\n");
}

void averageBalance() {
    float sum = 0;
    for(int i = 0; i < count; i++) {
        sum += accounts[i].balance;
    }
    printf("Average Balance: %.2f\n", sum / count);
}

int main() {
    int choice;

    while(1) {
        printf("\n--- Bank Account Management ---\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Display Accounts\n");
        printf("5. Search Account\n");
        printf("6. Sort by Balance\n");
        printf("7. Average Balance\n");
        printf("8. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: display(); break;
            case 5: searchAccount(); break;
            case 6: sortByBalance(); break;
            case 7: averageBalance(); break;
            case 8: exit(0);
            default: printf("Invalid Choice!\n");
        }
    }
}
