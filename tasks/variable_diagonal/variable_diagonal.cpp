#include "variable_diagonal.h"

#include <climits>

int** BuildDiagonalArray(size_t lines, size_t columns) {
    int** ans = new int*[lines];
    for (size_t i = 0; i < lines; ++i) {
        ans[i] = new int[columns];
    }
    int counter = 0;
    size_t i = 0;
    size_t j = 0;
    for (size_t diag_counter = 0; diag_counter < lines + columns - 1; ++diag_counter) {
        if (diag_counter > columns - 1) {
            i = diag_counter - columns + 1;
            j = columns - 1;
        } else {
            i = 0;
            j = diag_counter;
        }
        while (i < lines) {
            ans[i][j] = counter++;
            ++i;
            if (j == 0) {
                break;
            }
            --j;
        }
    }
    return ans;
}