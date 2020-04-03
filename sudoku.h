#ifndef SUDOKU_H
#define SUDOKU_H
/***************************************************
 * Finish your .cpp according to this header file. *
 * You can modify this file if needed.             *
 ***************************************************/
class Sudoku {
  public:
    Sudoku() { //default constructor
        for (int i = 0; i < 81; i++)
            map[i]= 0;
    }
    Sudoku(int arr[]) {
        for (int i = 0; i < 81; i++)
            map[i]= arr[i];
    }
    bool isCorrect() {
        bool check_result;
        int check_arr[9];
        int location;
        for(int i=0; i<81; i+=9) { // check rows
            for(int j=0; j<9; ++j)
                check_arr[j] = map[i+j];
            check_result = checkUnity(check_arr);
            if(check_result == false)
                return false;
        }
        for(int i=0; i<9; ++i) { // check columns
            for(int j=0; j<9; ++j)
                check_arr[j] = map[i+9*j];
            check_result = checkUnity(check_arr);
            if(check_result == false)
                return false;
        }
        for(int i=0; i<9; ++i) { // check cells
            for(int j=0; j<9; ++j) {
                location = 27 * (i / 3) + 3 * (i % 3) + 9 * (j / 3) + (j % 3);
                check_arr[j] = map[location];
            }
            check_result =
                checkUnity(check_arr);
            if(check_result == false)
                return false;
        }
        return true;
    }
    int getanswer(int i) {
        return map[i];
    }
    void setanswer(int i,int ans) {
        map[i]= ans;
        return;
    }
    void swapNum(int x, int y) { //x,y number change
        for (int i = 0; i < 81; i++) {
            if(map[i]==x) {
                map[i] = y;
                continue;
            }
            if (map[i] == y) {
                map[i] = x;
                continue;
            }
        }
    }
    void swapRow(int x, int y) {
        int temp;
        for (int k = 0; k < 27; k++) {
            temp = map[27 * x + k];
            map[27 * x + k] = map[27 * y + k];
            map[27 * y + k] = temp;
        }
    }
    void swapCol(int x, int y) {
        int temp;
        for (int i = 0; i < 81; i+=9)
            for (int j = 0; j < 3; j++) {
                temp = map[i + j % 3+x*3];
                map[i + j % 3+x*3] = map[i + j % 3+y*3];
                map[i + j % 3+y*3] = temp;
            }
    }
    void rotate(int x) {
        int map_temp[9][9];
        int map_output[9][9];
        for (int m = 0; m < x; m++) {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    map_temp[i][j] = map[9 * i + j];
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++) {
                    map_output[j][i] = map_temp[8-i][j];
                }
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    map[9 * i + j] = map_output[i][j];
        }
    }
    void flip(int x) {
        int map_temp[9][9];
        int map_output[9][9] = {{0,0}};
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                map_temp[i][j] = map[9 * i + j];
        switch(x) {
        case 0: {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    map_output[i][j] = map_temp[8 - i][j];
        }
        break;
        case 1: {
            for (int i = 0; i < 9; i++)
                for (int j = 0; j < 9; j++)
                    map_output[j][i] = map_temp[j][8-i];
        }
        break;
        }
        for (int i = 0; i < 9; i++)
            for (int j = 0; j < 9; j++)
                map[9 * i + j] = map_output[i][j];
    }

  private:
    int map[81];
    bool checkUnity(int arr[]) {
        int arr_unity[9]; // counters
        for(int i=0; i<9; ++i)
            arr_unity[i] = 0; // initialize
        for(int i=0; i<9; ++i)
            ++arr_unity[arr[i]-1]; // count
        for(int i=0; i<9; ++i)
            if(arr_unity[i] != 1) // all element
                return false; // must be 1
        return true;
    }
};
#endif // SUDOKU_H
