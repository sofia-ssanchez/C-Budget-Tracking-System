#include <stdio.h>
#include <stdlib.h>
#include "budget.h"
#include "data.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <data_file>\n", argv[0]);
        return 1;
    }
    int choice;
    entriesArray = readEntries(argv[1], &count);
    while (choice != 7) {
        system("clear"); 
        printf("Welcome to the Budget Tracking System!\n");
        printf(
            "Budget Tracking System\n"
            "=============================\n"
            "1. Display all entries\n"
            "2. Expense distribution\n"
            "3. Sort entries\n"
            "4. Add Income/Expense entry\n"
            "5. Modify Entry\n"
            "6. Filter by month\n"
            "7. Exit\n"
            "Choice: "
        );
        scanf("%d", &choice);
        if (choice < 1 || choice > 7) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        switch (choice) {
            case 1:
                displayAllEntries();
                break;
            case 2:
                expenseDistribution();
                break;
            case 3:
                sortEntries();
                break;
            case 4:
                addEntry();
                break;
            case 5:
                modifyEntry();
                break;
            case 6:
                filterByMonth();
                break;
            case 7:
                printf("Exiting the Budget Tracking System...\n");
                break;
        }
        if (choice != 7) {
            printf("Press Enter to continue...");
            getchar();
            getchar();
        }
    }
    if (entriesArray != NULL) {
        free(entriesArray);
    }
    printf("Goodbye and thank you for using the Budget Tracking System!\n");
    return 0;
}