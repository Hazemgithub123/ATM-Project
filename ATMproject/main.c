#include <stdio.h>
#include <stdbool.h>
#include "User.h"
#include "Transaction.h"

// Function to display the ATM menu
void displayMenu() {
    printf("\nATM Menu:\n");
    printf("1. Balance Inquiry\n");
    printf("2. Deposit Funds\n");
    printf("3. Withdraw Funds\n");
    printf("4. Transaction History\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    loadUsersFromCSV();  // Load the users into the 'users' array
    loadTransactionsFromCSV(); // Load transactions into the 'transactions' array

    char username[50], password[10];
    int user_id;
    printf("Welcome to the ATM System\n");
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (authenticateUser(username, password, &user_id)) {
        printf("Login Successful! Your user ID: %d\n", user_id);
    } else {
        printf("Invalid username or password.\n");
        return 1; // Exit if authentication fails
    }

    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Your balance: %.2f\n", getBalance(user_id));
                break;
            case 2: {
                float depositAmount;
                printf("Enter amount to deposit: ");
                scanf("%f", &depositAmount);

                // Find the user in the array and update balance
                for (int i = 0; i < user_count; i++) {
                    if (users[i].user_id == user_id) {
                        users[i].current_balance += depositAmount; // Update balance in the array
                        updateUserBalance(user_id, users[i].current_balance); // Save updated user to the CSV
                        Transaction transaction = {transaction_count + 1, "deposit", depositAmount, user_id};
                        addTransaction(transaction); // Save transaction
                        printf("Deposit successful. New balance: %.2f\n", users[i].current_balance);
                        break;
                    }
                }
                break;
            }
            case 3: {
                float withdrawAmount;
                printf("Enter amount to withdraw: ");
                scanf("%f", &withdrawAmount);

                // Check if sufficient balance is available
                for (int i = 0; i < user_count; i++) {
                    if (users[i].user_id == user_id) {
                        if (users[i].current_balance >= withdrawAmount) {
                            users[i].current_balance -= withdrawAmount; // Update balance
                            updateUserBalance(user_id, users[i].current_balance); // Save updated user to the CSV
                            Transaction transaction = {transaction_count + 1, "withdraw", withdrawAmount, user_id};
                            addTransaction(transaction); // Save transaction
                            printf("Withdrawal successful. New balance: %.2f\n", users[i].current_balance);
                        } else {
                            printf("Insufficient balance for this withdrawal.\n");
                        }
                        break;
                    }
                }
                break;
            }
            case 4:
                getTransactionHistory(user_id);
                break;
            case 5:
                printf("Thank you for using the ATM!\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
