#include <bits/stdc++.h>
#include "testlib.h"
 
using namespace std;
 
int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    inf.readInt(1, 500, "w");
    inf.readSpace();
    inf.readInt(1, 10000, "l");
    inf.readEoln();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    int a, b = -1;
    for (int i = 0; i < n; ++i) {
        a = inf.readInt(0, 10000, "a");
        inf.readSpace();
        ensuref(a > b, "Two overlapping columns");
        b = inf.readInt(0, 10000, "b");
        ensuref(b >= a, "Column goes backwards in space");
        inf.readEoln();
    }
    inf.readEof();
}