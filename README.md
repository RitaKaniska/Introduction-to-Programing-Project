# My Library Management C++ Project

A console-based Library Management System implemented in C++. This project offers basic administrative and student functionalities for managing books and user accounts through a straightforward command-line interface.

---

##  Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Prerequisites](#prerequisites)
- [Getting Started](#getting-started)
- [Usage Guide](#usage-guide)
- [Project Structure](#project-structure)
- [Future Enhancements](#future-enhancements)
- [Contributing](#contributing)
- [Author](#author)
- [License](#license)

---

## About the Project

This Library Management System demonstrates a fundamental C++ console application designed to help practice programming fundamentals. It allows administrators and student users to manage book inventories, student accounts, and transactions—all without advanced C++ features like classes or pointers.

---

## Features

- **Admin capabilities**:
  - Add and edit book details (using ISBN).
  - View book availability.
  - List registered students and check balances.

- **Student capabilities**:
  - Account creation with deposit.
  - View balance and deposit funds.
  - Issue books with due return handling.

- **Additional details**:
  - Simple pricing and fines structure (e.g., deposit, book issue fee, late return fines).
  - Uses fixed-size 2D arrays for data storage.
  - Loop-driven UI stays active until user exits.

---

## Technologies Used

- **Language**: C++ (mostly procedural style)
- **Concepts covered**:
  - Arrays, functions, conditional logic (`if/else`, `switch`), loops.
  - No use of classes, pointers, or dynamic data structures.

---

## Prerequisites

- A C++ compiler such as `g++` (e.g., GCC), or any IDE that supports C++.
- A terminal or command prompt.

---

## Getting Started

1. Clone the repository:
    ```bash
    git clone https://github.com/RitaKaniska/Introduction-to-Programing-Project.git
    cd Introduction-to-Programing-Project
    ```

2. Compile the code. For example:
    ```bash
    g++ main.cpp book.cpp reader.cpp stats.cpp transaction.cpp -o library_management
    ```

3. Run the executable:
    ```bash
    ./library_management
    ```

---

## Usage Guide

Follow on-screen prompts to:
- Log in as an **admin** or **student**.
- Execute commands such as adding books, viewing inventory, managing accounts, or issuing books.
- Observe system responses and track your account’s status and due fines.

---

## Project Structure

