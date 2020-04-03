#include<iostream>
#include"sudoku.h"
using namespace std;

int build_table(int i,int j,Sudoku *su)
{
    int location;
    int c;
    if(i%9<=2&&i%9>=0)
        c = 0;
    if(i%9<=5&&i%9>=3)
        c = 3;
    if(i%9<=8&&i%9>=6)
        c = 6;
    location = (i / 27) * 27 +c;
    for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)
        if((*su).getanswer(k)==(j+1))
            return 0; 
    for (int k = i % 9; k < 81;k+=9)
        if((*su).getanswer(k)==(j+1))
            return 0;
    for (int k = location; k < (location + 3);k++)
        if((*su).getanswer(k)==(j+1))
            return 0;
    for (int k = location+9; k < (location + 12);k++)
        if((*su).getanswer(k)==(j+1))
            return 0;
    for (int k = location+18; k < (location + 21);k++)
        if((*su).getanswer(k)==(j+1))
            return 0;
    return (j+1);
}
bool guess1(int i, Sudoku *su,int (*fp)(int, int, Sudoku*))
{
    int table[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};//table
    for (int j = 0; j < 9;j++)
        table[j] = fp(i, j, su);
    if(i==80)
    {
        if((*su).getanswer(i)!=0)
            return true;
        else
        {    
            {
            for (int k = 0; k < 9;k++)
                if(table[k]==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k+1);
                    return true;
                    }
            }
            (*su).setanswer(i,0);
            return false;
        }
    }
    if((*su).getanswer(i)!=0)
    {
        if(guess1(i+1,su,fp))
            return true;
        else
            return false;
    }
    else
    {
        for (int k = 0; k < 9;k++)
                {
                if(table[k]==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k+1);
                    if(guess1(i+1,su,fp))
                        return true;
                    else
                        continue;
                    }
                }
            (*su).setanswer(i, 0);
                    return false;
    }
}
bool guess2(int i, Sudoku *su,int (*fp)(int, int, Sudoku*))
{
    int table[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};//table
    for (int j = 0; j < 9;j++)
        table[j] = fp(i, j, su);
    if(i==80)
    {
        if((*su).getanswer(i)!=0)
            return true;
        else
        {    
            {
            for (int k = 8; k >=0;k--)
                if(table[k]==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k+1);
                    return true;
                    }
            }
            (*su).setanswer(i,0);
            return false;
        }
    }
    if((*su).getanswer(i)!=0)
    {
        if(guess2(i+1,su,fp))
            return true;
        else
            return false;
    }
    else
    {
        for (int k = 8; k >=0;k--)
                {
                if(table[k]==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k+1);
                    if(guess2(i+1,su,fp))
                        return true;
                    else
                        continue;
                    }
                }
            (*su).setanswer(i, 0);
                    return false;
    }
}
int main()
{
    int (*fp)(int, int, Sudoku*) = build_table;
    int arr[81];
    bool result;
    for (int i = 0; i < 81;i++)
            cin >> arr[i];
    cout << endl;
    Sudoku su(arr);
    Sudoku su_reverse(arr);
    result = guess1(0, &su, fp);
    if(!result)
    {
        cout<<"0"<<endl;
        return 0;
    }
    guess2(0, &su_reverse, fp);
    for (int i = 0; i < 81;i++)
        if(su.getanswer(i)==su_reverse.getanswer(i))
            continue;
        else
            {
            cout << "2" << endl;
            return 0;
            }
    cout << "1" << endl;
    for (int i = 0; i < 81;i++)
        {
            
            cout << su.getanswer(i);
            if(i%9!=8)
                cout << " ";
            else
                cout << endl;
        }
}
