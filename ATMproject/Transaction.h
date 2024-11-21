#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef struct {
    int transaction_id;
    char transaction_type[10];
    float amount;
    int user_id;
} Transaction;

extern Transaction transactions[100]; // Global array of transactions
extern int transaction_count;         // Global transaction count

void loadTransactionsFromCSV();
void addTransaction(Transaction transaction);
void getTransactionHistory(int user_id);

#endif
