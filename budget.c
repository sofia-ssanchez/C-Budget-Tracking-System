#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "data.h"
#include "budget.h"
#include "ordering.h"


int displayAllEntries(void) {
    if (entriesArray) {
        system("clear"); 
        printf("Budget Tracking System - All Entries\n");
        printf("=================================================================================================\n");
        printf("ID   | Date       | Type                 | Category       | Description               | Amount\n");
        printf("-----|------------|----------------------|----------------|---------------------------|----------\n");
        for (int i = 0; i < count; i++) {
            printf("%-4d | %-10s | %-20s | %-14s | %-25s | %9.2lf\n",
                entriesArray[i].id,
                entriesArray[i].date,
                entriesArray[i].type,
                entriesArray[i].category,
                entriesArray[i].description,
                entriesArray[i].amount);
        }
        printf("=================================================================================================\n");
    }
    return 0;
}

int expenseDistribution(void) {
    float income, expense, needs, wants, netBalance, needsPercentOfExpense, wantsPercentOfExpense, needsPercentOfIncome, wantsPercentOfIncome;
    income = expense = needs = wants = netBalance = 0.0;

    if (entriesArray == NULL) {
        printf("No entries found.\n");
        return -1;
    }
    for (int i = 0; i < count; i++) {
        if (strcasecmp(entriesArray[i].type, "income") == 0 ) {
            income += entriesArray[i].amount;
        } else if (strcasecmp(entriesArray[i].type, "expense") == 0) {
            expense += entriesArray[i].amount;
            if (strcasecmp(entriesArray[i].category, "needs") == 0) {
                needs += entriesArray[i].amount;
            } else if (strcasecmp(entriesArray[i].category, "wants") == 0) {
                wants += entriesArray[i].amount;
            }
        }
    }

    netBalance = income - expense;
    needsPercentOfExpense = (expense > 0) ? (needs / expense) * 100 : 0;
    wantsPercentOfExpense = (expense > 0) ? (wants / expense) * 100 : 0;
    needsPercentOfIncome = (income > 0) ? (needs / income) * 100 : 0;
    wantsPercentOfIncome = (income > 0) ? (wants / income) * 100 : 0;

    system("clear"); 
    printf("Budget Tracking System - Expense Distribution\n");
    printf("=========================================================\n");
    printf("Total Income: $%.2f\n", income);
    printf("Total Expenses: $%.2f\n", expense);
    printf("Needs: $%.2f (%.2f%% of expenses, %.2f%% of income)\n", needs, needsPercentOfExpense, needsPercentOfIncome);
    printf("Wants: $%.2f (%.2f%% of expenses, %.2f%% of income)\n", wants, wantsPercentOfExpense, wantsPercentOfIncome);
    printf("Net Balance: $%.2f\n", netBalance);
    printf("=========================================================\n");
    return 0;
}

int sortEntries(void) {
    system("clear"); 
    printf("Budget Tracking System - Sort Entries\n");
    printf("======================================\n\n");
    printf("Sort Menu Options: \n");
    printf("1. Sort by ID\n");
    printf("2. Sort by Date\n");
    printf("3. Sort by Amount\n");
    printf("4. Sort by Description\n");
    printf("Choice: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            sortByID();
            displayAllEntries();
            break;
        case 2:
            sortByDate();
            displayAllEntries();
            break;
        case 3:
            sortByAmount();
            displayAllEntries();
            break;
        case 4:
            sortByDescription();
            displayAllEntries();
            break;
        default:
            printf("Invalid choice. Please try again.");
    }
    return 0;
}

int isValidDateFormat(const char *date) {
    if (strlen(date) != 10)
        return 0;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) {
            if (date[i] != '-') return 0;
        } else {
            if (!isdigit((unsigned char)date[i])) return 0;
        }
    }
    return 1;
}

int addEntry(void) {
    struct entry newEntry;
    char useToday[100], date[101], type[101], category[101], description[101]; // YYYY-MM-DD format
    float amount;
    int id;
    system("clear"); 
    printf("Budget Tracking System - Add Entry\n");
    printf("==================================\n\n");
    while (strcasecmp(useToday, "y") != 0 && strcasecmp(useToday, "n") != 0) {
        printf("Use today's date? (y/n): ");
        scanf(" %s", useToday);
    }
    if (strcmp(useToday, "y") == 0) {
        time_t todaysDate = time(NULL);
        struct tm tm = *localtime(&todaysDate);
        strftime(date, sizeof(date), "%Y-%m-%d", &tm);
    } else {
        while (isValidDateFormat(date) != 1) {
            printf("Enter date (YYYY-MM-DD): ");
            scanf("%s", date);
        }   
    }
    printf("Enter type (income/expense): ");
    scanf("%s", type);
    while (strcasecmp(type, "income") != 0 && strcasecmp(type, "expense") != 0) {
        printf("Invalid type. Please enter 'income' or 'expense': ");
        scanf("%s", type);
    }

    if (strcasecmp(type, "expense") == 0) {
        printf("Enter category (needs/wants): ");
        scanf("%s", category);
        while (strcasecmp(category, "needs") != 0 && strcasecmp(category, "wants") != 0) {
            printf("Invalid category. Please enter 'needs' or 'wants': ");
            scanf("%s", category);
        } 
    } else {
        printf("Enter category (active/passive): ");
        scanf("%s", category);
        while (strcasecmp(category, "active") != 0 && strcasecmp(category, "passive") != 0) {
            printf("Invalid category. Please enter 'active' or 'passive': ");
            scanf("%s", category);
        }
    }      
    category[0] = toupper(category[0]);

    printf("Enter description: "); 
    scanf(" %[^\n]", description);
    
    printf("Enter amount: ");
    scanf("%f", &amount);
    if (amount < 0) {
        printf("Amount cannot be negative. Please try again.\n");
        scanf("%f", &amount);
    }
    id = largestId + 1;
    largestId = id;

    strcpy(newEntry.date, date);
    strcpy(newEntry.type, type);
    strcpy(newEntry.category, category);
    strcpy(newEntry.description, description);
    newEntry.amount = amount;
    newEntry.id = id;

    entriesArray = realloc(entriesArray, (count + 1) * sizeof(struct entry));
    entriesArray[count] = newEntry;
    count++;
    printf("\nEntry added successfully with ID: %d\n", id);
    return 0;
}

int findEntryById(int id) {
    for (int i = 0; i < count; i++) {
        if (entriesArray[i].id == id) {
            return i; 
        }
    }
    return -1; // Entry not found
}

int modifyEntry(void) {
    system("clear"); 
    printf("Budget Tracking System - Modify Entry\n");
    printf("=====================================\n");
    displayAllEntries();
    int idToUpdate, idx;
    do {
        char idStr[100];
        char *endptr;
        printf("Enter the ID of the entry you want to modify: ");
        scanf("%s", idStr);
        idToUpdate = (int)strtol(idStr, &endptr, 10);
        if (endptr == idStr || *endptr != '\0') {
            printf("Invalid input. Please enter a valid integer ID.\n");
            idx = -1;
            continue;
        }
        idx = findEntryById(idToUpdate);
        if (idx == -1) {
            printf("Entry with ID %d not found, please try again.\n", idToUpdate);
        }
    } while (idx == -1);

    struct entry *entryToUpdate = &entriesArray[idx];
    printf("\nCurrent entry details:\n");
    printf("ID: %d\n", entryToUpdate->id);
    printf("Date: %s\n", entryToUpdate->date);
    printf("Type: %s\n", entryToUpdate->type);
    printf("Category: %s\n", entryToUpdate->category);
    printf("Description: %s\n", entryToUpdate->description);
    printf("Amount: %.2f\n", entryToUpdate->amount);

    printf("What would you like to modify?\n");
    printf("1. Date\n");
    printf("2. Amount\n");
    int choice = 0;
    char choiceStr[100];
    char *endptr;
    do {
        printf("Enter your choice (1 or 2): ");
        scanf("%s", choiceStr);
        choice = (int)strtol(choiceStr, &endptr, 10);
        if (endptr == choiceStr || *endptr != '\0' || (choice != 1 && choice != 2)) {
            printf("Invalid choice. Please try again.\n");
            choice = 0; // reset to stay in loop
        }
    } while (choice != 1 && choice != 2);

    switch (choice) {
        case 1: 
            printf("Enter new date (YYYY-MM-DD): ");
            char newDate[101];
            scanf("%s", newDate);
            while (isValidDateFormat(newDate) != 1) {
                printf("Invalid date format. Please enter again (YYYY-MM-DD): ");
                scanf("%s", newDate);
            }
            strcpy(entryToUpdate->date, newDate);
            printf("Date updated successfully.\n");
            break;
        case 2: 
            printf("Enter new amount: ");
            char amountStr[100];
            float newAmount;
            char *endptr;
            int valid = 0;
            while (!valid) {
                scanf("%s", amountStr);
                newAmount = strtof(amountStr, &endptr);
                if (endptr == amountStr || *endptr != '\0') {
                    printf("Invalid input. Please enter a valid number: ");
                } else if (newAmount < 0) {
                    printf("Amount cannot be negative. Please try again: ");
                } else {
                    valid = 1;
                }
            }
            entryToUpdate->amount = newAmount;
            printf("Amount updated successfully.\n");
            break; 
        default:
            printf("Invalid choice. No changes made.\n");
            return -1;
    }
    return 0;
}

int filterByMonth(void) {
    system("clear"); 
    printf("Budget Tracking System - Filter by Month\n");
    printf("=========================================\n");
    int month = 0, year = 0;
    char monthStr[10], yearStr[10];
    do {
        printf("Enter year (YYYY): ");
        scanf("%s", yearStr);
        if (strlen(yearStr) == 4 &&
            isdigit((unsigned char)yearStr[0]) &&
            isdigit((unsigned char)yearStr[1]) &&
            isdigit((unsigned char)yearStr[2]) &&
            isdigit((unsigned char)yearStr[3])) {
            year = atoi(yearStr);
        } else {
            printf("Invalid year format. Please enter a valid year (YYYY).\n");
        }
    } while (year == 0);

    do {
        printf("Enter month (1-12): ");
        scanf("%s", monthStr);
        if (strlen(monthStr) == 1 || strlen(monthStr) == 2) {
            if (strlen(monthStr) == 2 && isdigit(monthStr[0]) && isdigit(monthStr[1]) && monthStr[0] == 1) {
                    month = atoi(monthStr);
            } else if (isdigit(monthStr[0]) && monthStr[0] != '0') {
                month = atoi(monthStr);
            } else {
            printf("Invalid month format. Please enter a valid month (1-12).\n");
            }
        } else {
            printf("Invalid month format. Please enter a valid month (1-12).\n");
        }
    } while (month == 0);
    printf("\nEntries for %d-%02d:\n", year, month);
    printf("=================================================================================================\n");
    printf("ID   | Date       | Type                 | Category       | Description               | Amount\n");
    printf("-----|------------|----------------------|----------------|---------------------------|----------\n");
    int found = 0;
    for (int i = 0; i < count; i++) {
        int entryYear, entryMonth;
        if (sscanf(entriesArray[i].date, "%4d-%2d", &entryYear, &entryMonth) == 2) {
            if (entryYear == year && entryMonth == month) {
                printf("%-4d | %-10s | %-20s | %-14s | %-25s | %9.2lf\n",
                    entriesArray[i].id,
                    entriesArray[i].date,
                    entriesArray[i].type,
                    entriesArray[i].category,
                    entriesArray[i].description,
                    entriesArray[i].amount);
                found = 1;
            }
        }
    }
if (found == 0) {
    printf("No entries found for %d-%02d.\n", year, month);
}
    return 0;
}