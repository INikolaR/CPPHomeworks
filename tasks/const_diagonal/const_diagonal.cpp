#include "const_diagonal.h"

void BuildDiagonalArray(TableType table) {
    const int side = 9;
    int counter = 0;
    int i = 0;
    int j = 0;
    table[i][j] = 0;
    while (i != side || j != side) {
        if (i == side) {
            i = j + 1;
            j = side;
        } else if (j == 0) {
            j = i + 1;
            i = 0;
        } else {
            --j;
            ++i;
        }
        table[i][j] = ++counter;
    }
}
