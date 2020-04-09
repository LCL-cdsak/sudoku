#include"sudoku.h"
#include<iostream>
using namespace std;
class Table{
    private:
        int table[81][10];//{幾個條件,1,2,3,4,5,6....}陣列第一個元素紀錄有幾個數可以填
    public:
        Table(){
            for (int i = 0; i < 81;i++)
                for (int j = 0; j < 10;j++)
                    table[i][j] = 0;
        }
        void remove(int i)
        {
            for (int j = 0; j < 10;j++)
                table[i][j] = 0;
        }
        void basic(int i,Sudoku *su)/*用刪去法建立map[i]的table，首次產生table記得排除已經有答案的(之後根據table
                                      刪條件時，可以避開已經填好的*/
            {
                for (int j = 0; j < 10;j++)
                    table[i][j] = j;
                int location;
                int c;
                if(i%9<=2&&i%9>=0)
                    c = 0;
                if(i%9<=5&&i%9>=3)
                    c = 3;
                if(i%9<=8&&i%9>=6)
                    c = 6;
                    location = (i / 27) * 27 + c;                 //定出每個九宮格左上的那一格
                for (int j = 1; j < 10;j++)
                {
                    for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)//檢查row有沒有跟table相同的數
                        if((*su).getanswer(k)==j)
                            table[i][j] = 0;        //有相同的，把j設為0
                    for (int k = i % 9; k < 81;k+=9)//檢查column
                        if((*su).getanswer(k)==j)
                            table[i][j] = 0;
                    for (int k = location; k < (location + 3);k++)
                        if((*su).getanswer(k)==j)
                            table[i][j] = 0;
                    for (int k = location+9; k < (location + 12);k++)
                        if((*su).getanswer(k)==j)
                            table[i][j] = 0;
                    for (int k = location+18; k < (location + 21);k++)
                        if((*su).getanswer(k)==j)
                            table[i][j] = 0;
                }
                table[i][0] = 0;
                for (int k = 1; k < 10;k++)
                  if(table[i][k]!=0)
                      table[i][0]++;
            }
        int advanced_1(int i,Sudoku *su){ /*看map[i]的條件是否有唯一，若有，則把map[i]的table轉成唯一解，並更新條件數為1
                                            再把map[i]所在行、列、宮的該條件都設為0*/
                    int location;
                    int arr[9] = {0};
                    int c;
                    if(i%9<=2&&i%9>=0)
                    c = 0;
                    if(i%9<=5&&i%9>=3)
                    c = 3;
                    if(i%9<=8&&i%9>=6)
                    c = 6;
                    location = (i / 27) * 27 +c;//定出每個九宮格左上的那一格
                    for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)//處理row
                        if(k==i)    //排除自己的table
                            continue;
                        else
                            for (int j = 0; j < 9;j++)
                            if(table[k][j+1]!=0)
                                arr[j] = j + 1;
                            else
                                continue;
                    for (int j = 0; j < 9;j++)
                        if(table[i][j+1]!=0&&arr[j]==0)
                            {
                                for (int k = 0; k < 9;k++)
                                    table[i][k+1] = 0;
                                (*su).setanswer(i,j+1);//把答案設成那個數，把table清空
                                for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)//處理row
                                if(k==i)    //排除自己的table
                                continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = i % 9; k < 81;k+=9)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = location; k < (location + 3);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+9; k < (location + 12);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+18; k < (location + 21);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                 table[i][0] = 0;
                    for (int k = 1; k < 10;k++)
                        if(table[i][k]!=0)
                        table[i][0]++;//更新條件數
                    return 1;
                            }
                            for (int i = 0; i < 9;i++)
                        arr[i] = 0;
                   for (int k = i % 9; k < 81; k += 9) //處理column
                        if(k==i)    //排除自己的table
                            continue;
                        else
                            for (int j = 0; j < 9;j++)
                            if(table[k][j+1]!=0)
                                arr[j] = j + 1;
                            else
                                continue;
                    for (int j = 0; j < 9;j++)
                        if(table[i][j+1]!=0&&arr[j]==0)
                            {
                                for (int k = 0; k < 9;k++)
                                    table[i][k+1] = 0;
                               (*su).setanswer(i,j+1);//把答案設成那個數，把table清空
                                for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)//處理row
                                if(k==i)    //排除自己的table
                                continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = i % 9; k < 81;k+=9)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = location; k < (location + 3);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+9; k < (location + 12);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+18; k < (location + 21);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                 table[i][0] = 0;
                    for (int k = 1; k < 10;k++)
                        if(table[i][k]!=0)
                        table[i][0]++;//更新條件數
                    return 1;
                            }
                       for (int i = 0; i < 9;i++)
                        arr[i] = 0;
                    for (int k = location; k < (location + 3);k++)
                    if(k==i)
                            continue;
                        else
                            for (int j = 0; j < 9;j++)
                            if(table[k][j+1]!=0)
                                arr[j] = j + 1;
                            else
                                continue;
                    for (int k = location+9; k < (location + 12);k++)
                    if(k==i)
                            continue;
                        else
                            for (int j = 0; j < 9;j++)
                            if(table[k][j+1]!=0)
                                arr[j] = j + 1;
                            else
                                continue;
                    for (int k = location+18; k < (location + 21);k++)
                    if(k==i)
                            continue;
                        else
                            for (int j = 0; j < 9;j++)
                            if(table[k][j+1]!=0)
                                arr[j] = j + 1;
                            else
                                continue;
                    for (int j = 0; j < 9;j++)
                        if(table[i][j+1]!=0&&arr[j]==0)
                           {
                                for (int k = 0; k < 9;k++)
                                    table[i][k+1] = 0;
                                (*su).setanswer(i,j+1);//把答案設成那個數，把table清空
                                for (int k = i - (i % 9); k < i + 9 - (i % 9);k++)//處理row
                                if(k==i)    //排除自己的table
                                continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = i % 9; k < 81;k+=9)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                for (int k = location; k < (location + 3);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+9; k < (location + 12);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                    for (int k = location+18; k < (location + 21);k++)
                                if(k==i)
                                    continue;
                                else
                                    {
                                    table[k][j + 1] = 0;
                                    table[k][0] = 0;
                                    for (int m = 1; m < 10;m++)
                                    if(table[k][m]!=0)
                                    table[k][0]++;
                                    }
                                 table[i][0] = 0;
                    for (int k = 1; k < 10;k++)
                        if(table[i][k]!=0)
                        table[i][0]++;//更新條件數
                    return 1;
                            }
                    return 0;
                }
        int gettable(int i,int j)//回傳map[i]的table[index]值
            {
            return table[i][j];
            }
};
bool guess(Sudoku * su,Table *tb,int i)
{
    if(i==80)//最後一個的情況
    {
        if((*su).getanswer(i)!=0)
            return true;
        else
        {
            {
            (*tb).basic(i, su);
            for (int k = 1; k < 10;k++)
                if((*tb).gettable(i,k)==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k);
                    return true;
                    }
            }
            (*su).setanswer(i,0);
            return false;
        }
    }
    if((*su).getanswer(i)!=0)
    {
        if(guess(su,tb,i+1))
            return true;
        else
            return false;
    }
    else
    {
        (*tb).basic(i, su);
        for (int k = 1; k < 10;k++)
                {
                if((*tb).gettable(i,k)==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k);
                    if(guess(su,tb,i+1))
                        return true;
                    else
                        continue;
                    }
                }
            (*su).setanswer(i, 0);
                    return false;
    }
}
bool guess2(Sudoku * su,Table *tb,int i)
{
    if(i==80)//最後一個的情況
    {
        if((*su).getanswer(i)!=0)
            return true;
        else
        {
            {
            (*tb).basic(i, su);
            for (int k = 9; k >0;k--)
                if((*tb).gettable(i,k)==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k);
                    return true;
                    }
            }
            (*su).setanswer(i,0);
            return false;
        }
    }
    if((*su).getanswer(i)!=0)
    {
        if(guess2(su,tb,i+1))
            return true;
        else
            return false;
    }
    else
    {
        (*tb).basic(i, su);
        for (int k = 9; k >0;k--)
                {
                if((*tb).gettable(i,k)==0)
                    continue;
                else
                    {
                    (*su).setanswer(i,k);
                    if(guess2(su,tb,i+1))
                        return true;
                    else
                        continue;
                    }
                }
            (*su).setanswer(i, 0);
                    return false;
    }
}
int simplified(Table *tb,Sudoku *su)
{
    int count = 0;
    int c;
    for (int i = 0; i < 81;i++)
        {
        if((*su).getanswer(i)!=0)
            continue;
        else
            c = (*tb).advanced_1(i, su);
            count += c;
        }
        return count;
}
int main(void)
{
    int arr[81];
    bool result;
    for (int i = 0; i < 81;i++)
    {
        cin >> arr[i];
    }
    Sudoku su(arr);
    
    Table tb;
    for (int i = 0; i < 81;i++)
    {
        if(su.getanswer(i)!=0)
            continue;
        else
            tb.basic(i, &su);
    }
    for (int i = 0; i < 81;i++)
    {
        if(su.getanswer(i)!=0)
            continue;
        else
            tb.advanced_1(i,&su);
    }
    int c =1;
    while(c!=0)
        {c = 0;
        c = simplified(&tb, &su);}
    Table tb2 = tb;        //複製一份
    Sudoku su_reverse= su; //複製一份
    result = guess(&su, &tb, 0);
    if(!result)
    {
        cout<<"0"<<endl;
        return 0;
    }
    guess2(&su_reverse, &tb2, 0);
    for (int i = 0; i < 81;i++)
        if(su.getanswer(i)==su_reverse.getanswer(i))
            continue;
        else
            {
            cout << "2" << endl;
            return 0;
            }
    cout << "1" << endl;
    for (int i = 0; i < 81; i++)
    {

        cout << su.getanswer(i);
        if (i % 9 != 8)
            cout << " ";
        else
            cout << endl;
        }
}
