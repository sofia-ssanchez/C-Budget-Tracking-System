#include "data.h"
#include <strings.h>
#include <stdlib.h>


int compareEntriesById(const void *a, const void *b) {
    struct entry *entryA = (struct entry *)a;
    struct entry *entryB = (struct entry *)b;
    return entryA->id - entryB->id;
}
int compareEntriesByDate(const void *a, const void *b) {
    struct entry *entryA = (struct entry *)a;
    struct entry *entryB = (struct entry *)b;
    return strcasecmp(entryA->date, entryB->date);
}
int compareEntriesByAmount(const void *a, const void *b) {
    struct entry *entryA = (struct entry *)a;
    struct entry *entryB = (struct entry *)b;
    if (entryA->amount < entryB->amount) return -1;
    if (entryA->amount > entryB->amount) return 1;
    return 0;
}
int compareEntriesByDescription(const void *a, const void *b) {
    struct entry *entryA = (struct entry *)a;
    struct entry *entryB = (struct entry *)b;
    return strcasecmp(entryA->description, entryB->description);
}

int sortByID(void) {
    qsort(entriesArray, count, sizeof(struct entry), compareEntriesById);
    return 0;
}

int sortByDate(void) {
    qsort(entriesArray, count, sizeof(struct entry), compareEntriesByDate);
    return 0;
}

int sortByAmount(void) {
    qsort(entriesArray, count, sizeof(struct entry), compareEntriesByAmount);
    return 0;
}
int sortByDescription(void) {
    qsort(entriesArray, count, sizeof(struct entry), compareEntriesByDescription);
    return 0;
}


