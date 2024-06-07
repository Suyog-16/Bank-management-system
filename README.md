
# Bank Management System

Welcome to the Bank Management System! This project is a simple console-based application written in C that allows users to register, log in, deposit, and withdraw money from their bank accounts. There is also an admin interface for managing user accounts.

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)

## Features

- **User Registration**: New users can register by providing their name, address, date of birth, gender, and an initial deposit amount.
- **User Login**: Registered users can log in using their name and pin code.
- **Deposit**: Users can deposit money into their account.
- **Withdraw**: Users can withdraw money from their account.
- **Admin Access**: Admin can view user details, view all users, and delete user accounts.

## Prerequisites

To run this project, you need:
- A C compiler (like GCC)
- A terminal or command prompt

## Installation

1. **Clone the Repository**:
   ```sh
   git clone https://github.com/yourusername/bank-management-system.git
   cd bank-management-system
   ```

2. **Compile the Program**:
   ```sh
   gcc -o bank.exe bank.c
   ```

3. **Run the Program**:
   ```sh
   ./bank.exe
   ```

## Usage

### Main Menu
When you run the program, you will see the main menu with the following options:
1. Register User
2. Login User
3. Admin Access
4. Exit

### Register User
- Select option `1` to register a new user.
- Follow the prompts to enter your name, address, date of birth, gender, pin code, and initial deposit.
- A 14-digit account number will be generated for you.

### Login User
- Select option `2` to log in as an existing user.
- Enter your name and pin code.
- Once logged in, you can choose to deposit, withdraw, or return to the main menu.

### Admin Access
- Select option `3` for admin access.
- Enter the admin username and password (`admin` for both by default).
- Admin can view user details, view all users, and delete user accounts.

## Project Structure

```
bank-management-system/
│
├── users.txt              # File to store user information
├── bank.c                 # Main program file
├── bank.exe               # Compiled executable
├── README.md              # This README file
```

## Contributing

Contributions are welcome! If you have suggestions or improvements, please:
1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

Feel free to customize this README file according to your project's specifics and preferences. Happy coding!

