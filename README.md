# Phone Book Management System (C)

This project is a functional phone book application written in the C programming language. It allows users to manage contacts using a simple command-line interface. Supported operations include adding, modifying, deleting, listing, and searching for contacts, with data persisted in a plain text file.

## Features

- Add a new contact
- Display a list of all contacts
- Search for a contact by telephone number
- Modify contact information
- Delete a contact by number
- Exit with confirmation

## Technologies

- C Standard: C23
- File operations using `FILE*`, `fscanf`, `fprintf`
- Terminal interaction via `stdio.h`, `conio.h`
- Data stored in `input.txt`

## Build Instructions

```
git clone https://github.com/dragosh29/phone-book-C.git
cd phone-book-C
mkdir build
cd build
cmake ..
make
./untitled2
```

## Data Format

Contacts are stored in the following plain-text format:

```
<name> <address> <father_name> <mother_name> <number> <gender> <email>
```

Each contact is written to a new line in `input.txt`. Reading and writing are done sequentially using formatted I/O.

## Notes

- The program uses `system("cls")` and `getch()` which are Windows-specific. On Linux/macOS, substitute `cls` with `clear` or remove these lines for portability.
- Uses `scanf` with field width specifiers to prevent buffer overflow.
- File update operations (modify/delete) are handled via a temporary file strategy (`temp.txt`, `f_temp.txt`).

## License

This project is licensed under the MIT License.
