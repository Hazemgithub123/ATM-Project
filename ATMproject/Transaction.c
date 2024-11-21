#include "Transaction.h"
#include <stdio.h>
#include <string.h>

Transaction transactions[100]; // Array of transactions
int transaction_count = 0;     // Initialize transaction count

void loadTransactionsFromCSV() {
    // Example implementation for loading transactions
    FILE *file = fopen("transactions.csv", "r");
    if (file == NULL) {
        printf("Error: Could not open transactions.csv\n");
        return;
    }

    while (fscanf(file, "%d,%[^,],%f,%d",
            &transactions[transaction_count].transaction_id,
            transactions[transaction_count].transaction_type,
            &transactions[transaction_count].amount,
            &transactions[transaction_count].user_id) != EOF) {
        transaction_count++;
    }

    fclose(file);
}

void addTransaction(Transaction transaction) {
    transactions[transaction_count++] = transaction; // Add transaction
    FILE *file = fopen("transactions.csv", "a");
    if (file) {
        fprintf(file, "%d,%s,%.2f,%d\n",
                transaction.transaction_id,
                transaction.transaction_type,
                transaction.amount,
                transaction.user_id);
        fclose(file);
    } else {
        printf("Error: Could not open transactions.csv to append\n");
    }
}

void getTransactionHistory(int user_id) {
    printf("\nTransaction History for User ID: %d\n", user_id);
    printf("ID\tType\tAmount\n");
    for (int i = 0; i < transaction_count; i++) {
        if (transactions[i].user_id == user_id) {
            printf("%d\t%s\t%.2f\n",
                   transactions[i].transaction_id,
                   transactions[i].transaction_type,
                   transactions[i].amount);
        }
    }
}
