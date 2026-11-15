BCS 2204 - DATA STRUCTURES AND ALGORITHMS - GROUP COURSEWORK 1
Scenario 6: Student Results Register (dynamic array with capacity doubling)
ATEGEKA ANDREW
VU-BCS-2507-1756-DAY

************************
1. FILES
ResultArray.h   Result struct and the DynArray<T> class template (A1)
Sorts.h         insertionSort, mergeSort (template, with comparator) and iterative binarySearch (A2)
main.cpp        Loads results.txt, shows the records, sorts, searches and saves (A1, A2)
test.cpp        Automatic tests T1-T15 for A1 and A2 (A3)
timing.cpp      Timing experiment for A4 (writes timing.csv)
results.txt     Sample data file, 10 records, one per line

Data format in results.txt (comma separated, no spaces around the commas):
RegNo,Name,Course,Marks
Example: VU-BCS-2507-1756-DAY,ATEGEKA ANDREW,Computer Science,78

*************************
2. REQUIREMENTS

A C++17 compiler: g++ (MinGW / MSYS2 UCRT64 on Windows)
All files must be in the same folder.

***************************************
3. HOW TO COMPILE AND RUN (Command Prompt)

Main program (load, display, merge sort, binary search, save):
    g++ main.cpp  -o main
    .\main
OR: g++ main.cpp -o main && ./main

Automatic tests (prints PASS or FAIL for T1-T15):
    g++  test.cpp -o test
    .\test

Timing experiment (takes a few minutes, insertion sort at n = 64000 is slow):
    g++ Timing.cpp -o timing
    .\timing
It prints a table and saves timing.csv (n, times, doubling ratios).

Memory check (AddressSanitizer, use WSL or Linux):
    g++ -fsanitize=address -g test.cpp -o test && ./test

******************************************
4. NOTES

- main.cpp saves the sorted records back into results.txt, so keep a copy of the
  original file if you want to see the unsorted order again.
- Sorting algorithm: the last digit of the registration number is 6 (even), so
  merge sort is the O(n log n) algorithm used.
- No STL containers are used to build the data structure in ResultArray.h.
