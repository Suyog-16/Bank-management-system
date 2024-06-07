#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct User {
    int pin_code;
    char address[100];
    char name[100];
    char gender;
    float deposit;
    char account_number[15];
    char dob[11];  // Format: YYYY-MM-DD
};

// Function Declarations
void register_user();
void login_user();
void deposit(struct User *user);
void withdraw(struct User *user);
void update_file(struct User users[], int num_users);
int load_users(struct User users[], int max_users);
void admin();
int admin_login();
void view_user_details(struct User users[], int num_users);
void view_all_users(struct User users[], int num_users);
void delete_user(struct User users[], int *num_users);
void clear_screen();

int main() {
    int choice;

    do {
        clear_screen();
        printf("\nBank Management System\n");
        printf("1. Register User\n");
        printf("2. Login User\n");
        printf("3. Admin Access\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                login_user();
                break;
            case 3:
                admin();
                break;
            case 4:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 4);

    return 0;
}

void register_user() {
    struct User user;
    FILE *fp;
    int repin;

    fp = fopen("users.txt", "a+");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    clear_screen();
    printf("Enter Name: ");
    scanf(" %[^\n]%*c", user.name);

    printf("Enter Address: ");
    scanf(" %[^\n]%*c", user.address);

    printf("Enter Date of Birth (YYYY-MM-DD): ");
    scanf(" %[^\n]%*c", user.dob);

    printf("Enter Gender (M/F): ");
    scanf(" %c", &user.gender);

    do {
        printf("Enter a 5-digit pin code: ");
        scanf("%d", &user.pin_code);
        printf("Re-enter the pin code: ");
        scanf("%d", &repin);
        if (user.pin_code != repin) {
            printf("Pin codes do not match. Please try again.\n");
        }
    } while (user.pin_code != repin);

    printf("Enter Initial Deposit: ");
    scanf("%f", &user.deposit);

    // Generate a 14-digit random account number
    srand(time(0));
    for (int i = 0; i < 14; i++) {
        user.account_number[i] = '0' + rand() % 10;
    }
    user.account_number[14] = '\0';

    fprintf(fp, "%s\t%s\t%s\t%c\t%d\t%s\t%.2f\n", user.name, user.address, user.dob, user.gender, user.pin_code, user.account_number, user.deposit);
    fclose(fp);

    printf("User successfully registered. Your account number is: %s\n", user.account_number);
    printf("Press any key to continue...\n");
    getchar(); getchar();  // To capture the newline and wait for an input
}

void login_user() {
    struct User users[100];
    int num_users = load_users(users, 100);
    char name[100];
    int pin_code;
    int found = 0;

    clear_screen();
    printf("Enter your name: ");
    scanf(" %[^\n]%*c", name);
    printf("Enter your pin code: ");
    scanf("%d", &pin_code);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].name, name) == 0 && users[i].pin_code == pin_code) {
            clear_screen();
            printf("\nLogin successful.\n");
            printf("Name: %s\nAddress: %s\nDOB: %s\nGender: %c\nAccount Number: %s\nBalance: Rs%.2f\n",
                   users[i].name, users[i].address, users[i].dob, users[i].gender, users[i].account_number, users[i].deposit);
            found = 1;
            int action;
            do {
                printf("Choose an action:\n");
                printf("  1. Deposit\n");
                printf("  2. Withdraw\n");
                printf("  3. Return to Main Menu\n");
                printf("Enter choice: ");
                scanf("%d", &action);
                switch(action) {
                    case 1:
                        deposit(&users[i]);
                        break;
                    case 2:
                        withdraw(&users[i]);
                        break;
                    case 3:
                        update_file(users, num_users);
                        printf("Returning to main menu.\n");
                        break;
                    default:
                        printf("Invalid choice. Please try again.\n");
                }
            } while (action != 3);
            break;
        }
    }
    if (!found) {
        printf("No user found with the given name and pin code. Please try again.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();  // To capture the newline and wait for an input
}

void deposit(struct User *user) {
    float amount;
    printf("Enter the amount to deposit: ");
    scanf("%f", &amount);
    if (amount > 0) {
        user->deposit += amount;
        printf("Amount Rs%.2f deposited successfully.\n", amount);
        printf("New balance: Rs%.2f\n", user->deposit);
    } else {
        printf("Invalid amount entered. Deposit failed.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();
}

void withdraw(struct User *user) {
    float amount;
    printf("Enter the amount to withdraw: ");
    scanf("%f", &amount);
    if (amount > 0 && amount <= user->deposit) {
        user->deposit -= amount;
        printf("Amount Rs%.2f withdrawn successfully.\n", amount);
        printf("Remaining balance: Rs%.2f\n", user->deposit);
    } else {
        printf("Invalid amount or insufficient balance.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();
}

void update_file(struct User users[], int num_users) {
    FILE *fp = fopen("users.txt", "w");
    if (fp == NULL) {
        perror("Failed to open file");
        return;
    }

    for (int i = 0; i < num_users; i++) {
        fprintf(fp, "%s\t%s\t%s\t%c\t%d\t%s\t%.2f\n", users[i].name, users[i].address, users[i].dob, users[i].gender, users[i].pin_code, users[i].account_number, users[i].deposit);
    }
    fclose(fp);
}

int load_users(struct User users[], int max_users) {
    FILE *fp;
    int num_users = 0;
    fp = fopen("users.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 0;
    }

    while (fscanf(fp, "%99s %99s %10s %c %d %14s %f", users[num_users].name, users[num_users].address, users[num_users].dob, &users[num_users].gender, &users[num_users].pin_code, users[num_users].account_number, &users[num_users].deposit) == 7) {
        num_users++;
        if (num_users >= max_users) break;
    }
    fclose(fp);
    return num_users;
}

void admin() {
    if (!admin_login()) {
        return;  // Exit if login fails
    }

    struct User users[100];
    int num_users = load_users(users, 100);
    int choice;
    do {
        clear_screen();
        printf("Admin Menu\n");
        printf("  1. View User Details\n");
        printf("  2. View All Users\n");
        printf("  3. Delete User\n");
        printf("  4. Return to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                view_user_details(users, num_users);
                break;
            case 2:
                view_all_users(users, num_users);
                break;
            case 3:
                delete_user(users, &num_users);
                break;
            case 4:
                printf("Returning to main menu.\n");
                break;
            default:
                printf("Invalid choice. Please enter again.\n");
        }
    } while (choice != 4);
}

int admin_login() {
    char username[100], password[100];
    clear_screen();
    printf("Admin Login\n");
    printf("Username : ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "admin") == 0) {
        return 1;  // Login successful
    } else {
        printf("Incorrect username or password.\n");
        return 0;  // Login failed
    }
}

void view_user_details(struct User users[], int num_users) {
    char account_number[15];
    int found = 0;

    clear_screen();
    printf("Enter the account number of the user: ");
    scanf("%s", account_number);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].account_number, account_number) == 0) {
            printf("\nUser Details\n");
            printf("Name: %s\nAddress: %s\nDOB: %s\nGender: %c\nAccount Number: %s\nBalance: Rs%.2f\n",
                   users[i].name, users[i].address, users[i].dob, users[i].gender, users[i].account_number, users[i].deposit);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User not found.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();  // To capture the newline and wait for an input
}

void view_all_users(struct User users[], int num_users) {
    clear_screen();
    printf("All Users\n");
    for (int i = 0; i < num_users; i++) {
        printf("User %d\n", i+1);
        printf("Name: %s\n", users[i].name);
        printf("Address: %s\n", users[i].address);
        printf("DOB: %s\n", users[i].dob);
        printf("Gender: %c\n", users[i].gender);
        printf("Account Number: %s\n", users[i].account_number);
        printf("Balance: Rs%.2f\n", users[i].deposit);
        printf("\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();  // To capture the newline and wait for an input
}

void delete_user(struct User users[], int *num_users) {
    char account_number[15];
    int found = 0;

    clear_screen();
    printf("Enter the account number of the user to delete: ");
    scanf("%s", account_number);

    for (int i = 0; i < *num_users; i++) {
        if (strcmp(users[i].account_number, account_number) == 0) {
            found = 1;
            for (int j = i; j < *num_users - 1; j++) {
                users[j] = users[j + 1];
            }
            (*num_users)--;
            printf("User deleted successfully.\n");
            update_file(users, *num_users);
            break;
        }
    }

    if (!found) {
        printf("User not found.\n");
    }
    printf("Press any key to continue...\n");
    getchar(); getchar();  // To capture the newline and wait for an input
}

void clear_screen() {
   
        system("cls");
  
}

