#ifndef USER_H
#define USER_H

#include <stdbool.h> // Include this line

typedef struct {
    int user_id;
    char username[50];
    char password[10];
    float current_balance;
} User;

extern User users[100]; // Assuming max 100 users
extern int user_count;  // Total number of users loaded from CSV

void loadUsersFromCSV(void);
void loadTransactionsFromCSV(void);
bool authenticateUser(const char *username, const char *password, int *user_id);
float getBalance(int user_id);
void updateUserBalance(int user_id, float new_balance);

#endif
