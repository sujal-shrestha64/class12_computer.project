#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define FILE_NAME "accounts.dat"

struct BankAccount {
    int accNo;
    char name[50];
    char password[20];
    float balance;
};

// Function to save account to file
void saveAccount(struct BankAccount account) {
    FILE *fp = fopen(FILE_NAME, "ab"); // append in binary mode
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&account, sizeof(struct BankAccount), 1, fp);
    fclose(fp);
}

// Function to read all accounts from file
int loadAccounts(struct BankAccount accounts[]) {
    FILE *fp = fopen(FILE_NAME, "rb"); // read binary
    if (fp == NULL) {
        return 0; // no accounts yet
    }
    int count = 0;
    while(fread(&accounts[count], sizeof(struct BankAccount), 1, fp)) {
        count++;
        if(count >= MAX) break;
    }
    fclose(fp);
    return count;
}

// Update all accounts to file (overwrite)
void updateAllAccounts(struct BankAccount accounts[], int count) {
    FILE *fp = fopen(FILE_NAME, "wb"); // write binary
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(accounts, sizeof(struct BankAccount), count, fp);
    fclose(fp);
}

// Create new account
int createAccount(struct BankAccount accounts[], int *count) {
    struct BankAccount account;
    printf("Enter Account Number: ");
    scanf("%d", &account.accNo);
    // Check if account number exists
    for(int i=0; i<*count; i++) {
        if(accounts[i].accNo == account.accNo) {
            printf("Account number already exists!\n");
            return -1;
        }
    }
    printf("Enter Name: ");
    scanf("%s", account.name);
    printf("Enter Password: ");
    scanf("%s", account.password);
    printf("Enter Initial Balance: ");
    scanf("%f", &account.balance);
    
    accounts[*count] = account;
    (*count)++;
    
    saveAccount(account); // save permanently
    printf("Account Created Successfully!\n");
    return 0;
}

// Login function
int login(struct BankAccount accounts[], int count) {
    int acc;
    char name[50], pass[20];
    printf("Enter Account Number: ");
    scanf("%d", &acc);
    for(int i=0; i<count; i++) {
        if(accounts[i].accNo == acc) {
            printf("Enter Name: ");
            scanf("%s", name);
            if(strcmp(accounts[i].name, name) != 0) {
                printf("Name does not match!\n");
                return -1;
            }
            printf("Enter Password: ");
            scanf("%s", pass);
            if(strcmp(accounts[i].password, pass) != 0) {
                printf("Password incorrect!\n");
                return -1;
            }
            printf("\nWelcome %s!\n", accounts[i].name);
            printf("Account Number: %d\n", accounts[i].accNo);
            printf("Available Balance: %.2f\n", accounts[i].balance);
            return i; // return index of logged-in account
        }
    }
    printf("Account Number not found!\n");
    return -1;
}

// Transfer function
void transfer(struct BankAccount accounts[], int count, int fromIndex) {
    int toAcc;
    float amount;
    printf("Enter Account Number to Transfer To: ");
    scanf("%d", &toAcc);
    for(int i=0; i<count; i++) {
        if(accounts[i].accNo == toAcc) {
            printf("Enter Amount to Transfer: ");
            scanf("%f", &amount);
            if(amount > accounts[fromIndex].balance) {
                printf("Insufficient Balance!\n");
                return;
            }
            accounts[fromIndex].balance -= amount;
            accounts[i].balance += amount;
            updateAllAccounts(accounts, count); // save changes
            printf("Transfer Successful!\n");
            printf("Available Balance: %.2f\n", accounts[fromIndex].balance);
            return;
        }
    }
    printf("Recipient Account not found!\n");
}

int main() {
    struct BankAccount accounts[MAX];
    int count = loadAccounts(accounts);
    int choice, loggedInIndex;
    
    while(1) {
        printf("\n--- Bank System ---\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                createAccount(accounts, &count);
                break;
            case 2:
                loggedInIndex = login(accounts, count);
                if(loggedInIndex != -1) {
                    transfer(accounts, count, loggedInIndex); // allow transfer
                }
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid Choice!\n");
        }
    }
}
