#include <stdio.h>
#include <string.h>
#include <stdbool.h> // Include this line for bool, true, false
#include "User.h"

User users[100];  // Declare users array
int user_count = 0;  // Initialize user count

// Function to load users from CSV file
void loadUsersFromCSV() {
    FILE *file = fopen("users.csv", "r");
    if (file == NULL) {
        printf("Error: Could not open users.csv\n");
        return;
    }

    while (fscanf(file, "%d,%49[^,],%9[^,],%f\n",
                  &users[user_count].user_id,
                  users[user_count].username,
                  users[user_count].password,
                  &users[user_count].current_balance) == 4) {
        user_count++;
    }

    fclose(file);
}

// Function to authenticate user by username and password
bool authenticateUser(const char *username, const char *password, int *user_id) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            *user_id = users[i].user_id;
            return true;
        }
    }
    return false;
}

// Function to update user balance in the CSV file
void updateUserBalance(int user_id, float new_balance) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            users[i].current_balance = new_balance;
            break;
        }
    }

    // Save updated balance back to CSV
    FILE *file = fopen("users.csv", "w");
    if (file == NULL) {
        printf("Error: Could not open users.csv for writing.\n");
        return;
    }

    for (int i = 0; i < user_count; i++) {
        fprintf(file, "%d,%s,%s,%.2f\n",
                users[i].user_id,
                users[i].username,
                users[i].password,
                users[i].current_balance);
    }

    fclose(file);
}

float getBalance(int user_id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            return users[i].current_balance;
        }
    }
    return -1; // Return -1 if user not found
}
