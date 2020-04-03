#include<iostream>
#include"sudoku.h"
using namespace std;
int main(void) {
    int arr[81] = {3, 0, 2, 0, 0, 5, 6, 9, 0,
                   0, 4, 0, 0, 9, 6, 0, 3, 0,
                   0, 5, 0, 0, 0, 8, 0, 0, 0,
                   1, 9, 0, 0, 8, 0, 7, 0, 3,
                   0, 0, 0, 0, 0, 0, 0, 0, 0,
                   5, 0, 7, 0, 3, 0, 0, 6, 1,
                   0, 0, 0, 8, 0, 0, 0, 2, 0,
                   0, 8, 0, 9, 6, 0, 0, 7, 0,
                   0, 6, 5, 7, 0, 0, 3, 0, 9
                  };
    Sudoku su(arr);
    su.rotate(2);
    for (int i = 0; i < 81; i++) {

        cout << su.getanswer(i);
        if(i%9!=8)
            cout << " ";
        else
            cout << endl;
    }
    return 0;
}
