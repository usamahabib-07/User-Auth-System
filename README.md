# UserAuthSystem

A console-based user authentication and account management system written in C++. Supports secure user registration, login, account modification, and admin-level user control.

## Features

### ✅ User Functionality
- **Signup** with unique identifier, strong password enforcement, and password confirmation
- **Login** using identifier and password
- **Change Email**
- **Change Password**
- **Logout**
- **Unsubscribe** (account deletion)

### ✅ Admin Functionality
- **Predefined Admin Account** that cannot be deleted
- **Add Users**
- **Delete Users**
- **Change Any User's Email**
- **Change Any User's Password**
- **View Active and Deleted User Records**

### ✅ Security Features
- Password strength evaluation (Weak, Medium, Strong)
- Strong passwords required for signup (Min 8 chars, 1 capital, 1 digit, 1 special character)
- Encrypted password storage (custom algorithm, no built-ins)
- Passwords decrypted only for respective users

### ✅ Technical Design
- Uses two core classes: `User` and `AuthSystem`
- Dynamic array with automatic resizing (doubles capacity when needed)
- Proper encapsulation using setters/getters
- Overloaded `<<` and `>>` operators for input/output
- No external libraries or built-in encryption functions used

## Requirements

- C++ compiler (e.g. g++, clang++)
- Console/terminal access

## How to Run

1. Clone the repo:
   ```bash
   git clone https://github.com/yourusername/UserAuthSystem.git
   cd UserAuthSystem
