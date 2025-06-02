#ifndef BUDGET_H
#define BUDGET_H
#include "data.h"

int displayAllEntries(void);
int expenseDistribution(void);
int sortEntries(void);
int addEntry(void);
int modifyEntry(void);
int filterByMonth(void);

int isValidDateFormat(const char *date);
#endif
