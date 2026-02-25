#include <stdio.h>
#include <stdbool.h>

int main() {
    int arr[5] = {9876, 9875, 9874, 9873, 9872};
    int input;
    bool found = false;
    
    printf("Enter your bank account number: ");
    scanf("%d", &input);
    
    for (int i = 0; i < 5; i++) {
        if (arr[i] == input) {
            found = true;
            break;
        }
    }
    
    if (found) {
        printf("Number matched!\n");
        scanf
    } else {
        printf("Number not found.\n");
    }
    
    return 0;
}
