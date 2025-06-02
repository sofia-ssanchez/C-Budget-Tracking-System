
#include "data.h"
#include "budget.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

  int count = 0;
  int largestId = 0;
  struct entry *entriesArray = NULL;

int findLargestId(void) {
    if (entriesArray == NULL || count == 0) {
        printf("No entries loaded.\n");
        return -1; // or another error value
    }
    int maxId = entriesArray[0].id;
    for (int i = 1; i < count; i++) {
        if (entriesArray[i].id > maxId) {
            maxId = entriesArray[i].id;
        }
    }
    return maxId;
}

  struct entry *readEntries(const char *filename, int *count) {
    int capacity = 0;

    FILE *entriesFile = fopen(filename, "r");
    if (entriesFile == NULL) {
        printf("Error opening the file.\n");
        return NULL;
    }

    char entry[606];
    while (fgets(entry, sizeof(entry), entriesFile)) {
        struct entry currentEntry;

        int matched = sscanf(entry, " %d | %100[^|] | %100[^|] | %100[^|] | %100[^|] | %lf", &currentEntry.id, currentEntry.date, currentEntry.type, currentEntry.category, currentEntry.description, &currentEntry.amount);

        if (matched != 6|| currentEntry.id <= 0|| !isValidDateFormat(currentEntry.date)|| (strcmp(currentEntry.type, "income") != 0 && strcmp(currentEntry.type, "expense") != 0)|| currentEntry.amount < 0) {
            fprintf(stderr, "Error: Malformed line in input file:\n%s\n", entry);
            fclose(entriesFile);
            free(entriesArray);
            exit(EXIT_FAILURE);
        }

        if (*count >= capacity) {
            capacity = (capacity == 0) ? 4 : capacity * 2;
            struct entry *temp = realloc(entriesArray, capacity * sizeof(struct entry));
            if (temp == NULL) {
                printf("Memory allocation failed.\n");
                free(entriesArray);
                fclose(entriesFile);
                return NULL;
            }
            entriesArray = temp;
        }
        entriesArray[(*count)++] = currentEntry;
    }

    fclose(entriesFile);
    largestId = findLargestId();
    return entriesArray;
}