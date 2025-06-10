# Library Management System

This C++ project implements a simple library management system using object-oriented programming. It supports adding books and members, borrowing and returning books, updating book copies, and printing details.

## Features

- **Book Management:**  
  - Add books (new, copy from existing, or with details)
  - Update number of copies
- **Member Management:**  
  - Register members (with or without custom borrow limit)
- **Transactions:**  
  - Borrow and return books
- **Printing:**  
  - Print details of books, members, and the entire library

## How to Run

1. **Compile the code:**
   ```sh
   g++ -o library_management code.cpp
   ```

2. **Run the program:**
   ```sh
   ./library_management
   ```

## Input Format

The program operates interactively with the following commands (one per line):

- `Book <Type>`
  - `None`: Add a default book.
  - `ExistingBook <oldisbn> <newisbn>`: Copy an existing book to a new ISBN.
  - `<Title> <Author> <ISBN> <CopiesAvailable> <TotalCopies>`: Add a book with details.
- `UpdateCopiesCount <isbn> <delta>`: Add or remove copies for a book.
- `Member <Type>`
  - `NoBorrowLimit <id> <name>`: Register member with default borrow limit (3).
  - `<id> <name> <limit>`: Register member with custom borrow limit.
- `Borrow <memberID> <isbn>`: Borrow a book.
- `Return <memberID> <isbn>`: Return a book.
- `PrintBook <isbn>`: Print book details.
- `PrintMember <memberID>`: Print member's borrowed books.
- `PrintLibrary`: Print all books and members.
- `Done`: Terminate the program.

## Example Session

```
Book HarryPotter JKRowling 12345 2 5
Member NoBorrowLimit M01 Alice
Borrow M01 12345
PrintBook 12345
Return M01 12345
PrintMember M01
PrintLibrary
Done
```
