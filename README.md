# Composting Batch and Yield Tracker

## Project Information
- **Course:** CAP455 – Object-Oriented Programming Using C++
- **Project:** Composting Batch and Yield Tracker
- **Phase:** CA2 – Constructors and File Handling
- **Academic Session:** 2026–27

## 1. Project Overview
The Composting Batch and Yield Tracker is a console-based C++ application designed to manage composting batches. It stores batch information, allows users to search and update records, and maintains data permanently using binary file handling.

## 2. Technologies Used
- Programming Language: C++
- Compiler: GCC (g++)
- IDE: Visual Studio Code
- File Handling: Binary File Handling
- Storage: Binary data file

## 3. Project Structure
```text
CompostingTracker/
│
├── data/
│   └── batches.dat
│
├── docs/
│   ├── flowchart.png
│   ├── proposal.pdf
│   └── uml.png
│
├── src/
│   └── main.cpp
│
├── tests/
│   └── test_cases.txt
│
├── README.md
├── .gitignore
└── tracker.exe
```

## 4. Features
1. Add new compost batches.
2. View all saved compost batches.
3. Search batches using Batch ID.
4. Update final compost weight and batch status.
5. Calculate compost yield.
6. Validate user inputs.
7. Prevent duplicate Batch IDs.
8. Store records permanently using binary files.
9. Load previously saved records when the application starts.
10. Support a maximum of 100 batch records.

## 5. Object-Oriented Programming Concepts
- Default Constructor
- Parameterized Constructor
- Copy Constructor
- Destructor
- Static Data Members
- Friend Function
- Inline Function
- Array of Objects
- Pointers
- `this` Pointer
- `std::string`

## 6. Binary File Handling
The application uses a fixed-size `BatchRecord` structure for binary storage.

The following operations are implemented:

- `ofstream` and `write()` – Save batch records.
- `ifstream` and `read()` – Read saved records.
- `seekg()` – Locate records while searching.
- `seekp()` – Locate records while updating.
- `loadBatches()` – Load saved records when the program starts.

The `CompostBatch` class uses strings, so its objects are converted into fixed-size records before binary storage.

## 7. Compilation and Execution

Open the project folder in Visual Studio Code.

Compile:
```bash
g++ src/main.cpp -o tracker.exe
```

Run:
```powershell
.\tracker.exe
```

Make sure the `data` folder exists before running the application.

## 8. Data Storage
All batch records are stored in:

```text
data/batches.dat
```

The application reads this file during startup and restores the previously saved batch records.

## 9. Testing
The application has been tested for:
- Constructor functionality.
- Binary file writing and reading.
- Searching and updating records.
- Persistence after restarting.
- Duplicate Batch ID validation.
- Invalid input handling.
- Record limit checks in source code.

## 10. Conclusion
The CA2 phase extends the initial Composting Batch and Yield Tracker by introducing constructors, destructors and binary file handling. The application can save, retrieve, search and update batch records while maintaining data across multiple executions.