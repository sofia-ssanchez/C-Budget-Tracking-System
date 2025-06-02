#ifndef DATA_H
#define DATA_H
#include "budget.h"

struct entry {
    int id;
    char date[101];
    char type[101];
    char category[101];
    char description[101];
    double amount;
};

extern struct entry *entriesArray;
extern int count, largestId;

struct entry *readEntries(const char *filename, int *count);

#endif

