#include <stdio.h>

int main(void) {
    printf("\033[H\033[J");
    printf("Welcome to the Budget Tracking System!\n");
    printf(
        "Budget Tracking System\n"
        "===========================\n"
        "1. Display all entries\n"
        "2. Expense distribution\n"
        "3. Sort entries\n"
        "4. Add Income/Expense entry\n"
        "5. Modify Entry\n"
        "6. Filter by month\n"
        "7. Exit\n"
        "Choice: "
    );
    int choice;
    scanf("%d", &choice);
    printf("%d\n", choice);
    return 0;
}