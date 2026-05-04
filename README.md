## My-Little-Library
This is a simple file-based Library Management System built in C using structured data and modular functions and it can be extended using data structures for optimization.

## Features of My Little Library
- Membership
- Books issue
- Books return
- View your record as a member
- A clean console UI

## Concepts Used
- File Handling in C
- Structures
- Functions

## Folders
My Little Library:
- include/
- source/
- data/ (ignored in git)
- README.md

## How to Run
Follow these steps to run the project on your system
### 1. Clone the Repository

```bash
git clone https://github.com/shrutisarchive/My-Little-Library.git
cd My-Little-Library
```

---

### 2. Navigate to Source Folder

```bash
cd source
```

---

### 3. Compile the Code

Make sure you have GCC installed.

```bash
gcc main.c functions.c -o run
```

---

### 4. Run the Program

```bash
./run
```

~ On Windows (PowerShell or CMD):

```bash
run.exe
```

---

## Important Notes

- The `data/` folder is used to store:
  - `user.txt`
  - `books.txt`
  - `issued.txt`

- These files are **auto-created/used during runtime**.

---

## First Time Setup

If running for the first time:

- The program may initialize default books automatically.
- Make sure the `data/` folder exists in the root directory.

---

## Requirements

- GCC Compiler (MinGW / any C compiler)
- VS Code or any IDE (optional)

---

## Tip

If you face file errors:
- Check folder structure
- Ensure you're running from the `source` directory

## Future Versions will have the following update
- Add due dates
- Add a fine system
- Further use of DSA concepts like linked list for storing books data, search optimization, stack/queue, hashing
- Convert to Web App

---
**Author:** Shruti
