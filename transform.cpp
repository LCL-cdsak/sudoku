#include<iostream>
#include"sudoku.h"
using namespace std;
int main(void)
{
    int arr[81];
    bool result = true;
    for (int i = 0; i < 81;i++)
            cin >> arr[i];
    cout << endl;
    Sudoku su(arr);
    while(result)
    {
        int flag,x,y;
        cin >> flag;
        switch(flag)
        {
            case 0:
                result = false;
                break;
            case 1:
            {
                cin >> x >> y;
                su.swapNum(x, y);
            }
            break;
            case 2:
            {
                cin >> x >> y;
                su.swapRow(x, y);
            }
            break;
            case 3:
            {
                cin >> x >> y;
                su.swapCol(x, y);
            }
            break;
            case 4:
            {
                cin >> x;
                su.rotate(x);
            }
            break;
            case 5:
            {
                cin >> x;
                su.flip(x);
            }
            break;
        }
    }
    for (int i = 0; i < 81;i++)
        {
            
            cout << su.getanswer(i);
            if(i%9!=8)
                cout << " ";
            else
                cout << endl;
        }
}
