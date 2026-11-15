// timing.cpp - A4 timing experiment: insertion sort vs merge sort
#include <iostream>
#include <fstream>
#include <chrono>      // clock for measuring time
#include <cstdlib>     // rand, srand
#include "Sorts.h"
using namespace std;

const int RUNS = 3;        // repeat every size 3 times, then average
const int START_N = 1000;
const int MAX_N = 64000;

// build n random records (random marks from 0 to 100)
void makeData(Result a[], int n) {
    for (int i = 0; i < n; i++) {
        a[i].RegNo = "VU-" + to_string(rand() % 100000);
        a[i].name = "Student";
        a[i].course = "Course";
        a[i].marks = rand() % 101;
    }
}

int main() {
    srand(12345);                          // fixed seed so the experiment can be repeated
    auto byMarks = [](const Result& x, const Result& y) { return x.marks < y.marks; };

    ofstream csv("timing.csv");            // saved so you can draw the chart in Excel
    csv << "n,insertion_ms,merge_ms,insertion_ratio,merge_ratio\n";

    cout << "n\tinsertion(ms)\tratio\tmerge(ms)\tratio" << endl;
    double prevIns = 0, prevMer = 0;

    for (int n = START_N; n <= MAX_N; n *= 2) {
        double insTotal = 0, merTotal = 0;

        for (int run = 0; run < RUNS; run++) {
            Result* master = new Result[n];
            makeData(master, n);
            Result* a = new Result[n];     // copy 1 for insertion sort
            Result* b = new Result[n];     // copy 2 for merge sort
            for (int i = 0; i < n; i++) { a[i] = master[i]; b[i] = master[i]; }

            auto t1 = chrono::high_resolution_clock::now();
            insertionSort(a, n, byMarks);
            auto t2 = chrono::high_resolution_clock::now();
            mergeSort(b, 0, n - 1, byMarks);
            auto t3 = chrono::high_resolution_clock::now();

            insTotal += chrono::duration<double, milli>(t2 - t1).count();
            merTotal += chrono::duration<double, milli>(t3 - t2).count();

            delete[] master; delete[] a; delete[] b;
        }

        double ins = insTotal / RUNS;      // average of the 3 runs
        double mer = merTotal / RUNS;
        double insRatio = prevIns > 0 ? ins / prevIns : 0;   // time at n divided by time at n/2
        double merRatio = prevMer > 0 ? mer / prevMer : 0;

        cout << n << "\t" << ins << "\t\t" << insRatio << "\t" << mer << "\t\t" << merRatio << endl;
        csv << n << "," << ins << "," << mer << "," << insRatio << "," << merRatio << "\n";
        prevIns = ins; prevMer = mer;
    }
    cout << "Saved timing.csv" << endl;
    return 0;
}