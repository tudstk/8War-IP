#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
using namespace std;
void patrat(int a,int b, int c,int d)
{///a left, b top, c right, d bottom
    if(abs(a-c)>70&&abs(b-d)>70)
    {
        ///rectangle(a,(b+d)/2,(a+c)/2,d);
        ///rectangle((a+c)/2,b,c,(b+d)/2);
        rectangle(a,b,(a+c)/2,(b+d)/2);
        rectangle((a+c)/2,(b+d)/2,c,d);
        patrat(a,(b+d)/2,(a+c)/2,d);
        patrat((a+c)/2,b,c,(b+d)/2);
        patrat(a,b,(a+c)/2,(b+d)/2);
        patrat((a+c)/2,(b+d)/2,c,d);
    }
    if(a==30&&c==165)
    {
        circle(((b+d)/2+b)/2,((a+c)/2+a)/2,20);
        circle(((b+d)/2+d)/2,((a+c)/2+c)/2,20);
    }
    if(a==435&&c==570)
    {
        fillellipse(((b+d)/2+b)/2,((a+c)/2+a)/2,20,20);
        fillellipse(((b+d)/2+d)/2,((a+c)/2+c)/2,20,20);
    }
}
struct
{
    int x,y;///coord piesei de pe linia L si coloana C (coresp A[L][C])
    int L,C;///L=i,C=j in parcurgerea lui A[][]
    int player;/// 1-neagra(circle), 2-alba(fillellipse)
}A[10][10];
int main()
{
    for(int i=0;i<=9;++i)
        for(int j=0;j<=9;++j)
         {
            if(((i<1||i>8)||(j<1||j>8))||(i+j)%2)
                A[i][j].player=3;///noteaza cu 3 locatiile in  care nu pot ajunge piesele
            else A[i][j].player=0;///noteaza cu 0 potentialele locatii in care pot ajunge piesele
         }
 //   A[]
    for(int j=1;j<=8;j+=2)
    {
        A[1][j].player=A[2][j+1].player=1;
        A[7][j].player=A[8][j+1].player=2;
    }
    /**for(int i=0;i<=9;++i) ///afisarea matricii din spatele jocului
    {
        for(int j=0;j<=9;++j)
            cout<<A[i][j].player<<" ";
        cout<<'\n';
    }*/
    initwindow(600,600);
    rectangle(30,30,570,570);
    patrat(30,30,570,570);
    int X,Y;
    while(1)
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, X, Y);
            cout<<"x="<<X<<'\n'<<"y="<<Y<<'\n';
        }
    /** stergerea piesei dupa mutare
    setcolor(BLACK);
    setfillstyle(1,BLACK);
    fillellipse(100,100,20,20);*/
    getch();
    return 0;
}
