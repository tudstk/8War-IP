#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>

using namespace std;


void patrat(int a,int b, int c,int d)
{
    ///a left, b top, c right, d bottom
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
struct joc
{
    int x,y;///coord piesei de pe linia L si coloana C (coresp A[L][C])
    int L,C;///L=i,C=j in parcurgerea lui A[][]
    int player;/// 1-neagra(circle), 2-alba(fillellipse), 3-spatiu inaccesibil
} A[10][10];

void initCoordonate()
{
    A[1][1].x = 63;
    A[1][1].y = 63;
    for(int j=2; j<=8; j++)
    {
        A[1][j].x = A[1][j-1].x + 68;
        A[1][j].y = 63;
    }
    int i,j;
    for(i=2; i<=8; i++)
    {
        for(j=1; j<=8; j++)
        {
            A[i][j].x = A[i-1][j].x;
            A[i][j].y = A[i-1][j].y + 68;

        }

    }

    /**for(int i=1;i<=7;i+=2)
        A[1][i].y=63,A[i][1].x=63;
    for(int i=2;i<=8;i+=2)
        A[2][i].y=132,A[i][2].x=132;
    for(int i=1;i<=7;i+=2)
        A[3][i].y=199,A[i][3].x=199;
    for(int i=2;i<=8;i+=2)
        A[4][i].y=266,A[i][4].x=266;
    for(int i=1;i<=7;i+=2)
        A[5][i].y=333,A[i][5].x=333;
    for(int i=2;i<=8;i+=2)
        A[6][i].y=400,A[i][6].x=400;
    for(int i=1;i<=7;i+=2)
        A[7][i].y=467,A[i][7].x=467;
    for(int i=2;i<=8;i+=2)
        A[8][i].y=534,A[i][8].x=534;*/
}
void initJoc()
{
    initwindow(600,600);
    setbkcolor(RED);
    cleardevice();
    setcolor(YELLOW);
    rectangle(30,30,570,570);
    patrat(30,30,570,570);
}
void mutareDreapta(joc A[][10], int i, int j)
{
    int X = A[i][j].x;
    int Y = A[i][j].y;

    //stergere

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,20,20);

    //mutare

    setcolor(YELLOW);

    A[i][j].x = A[i][j].x + 68;
    A[i][j].y = A[i][j].y + 68;

    int X2 = A[i][j].x;
    int Y2 = A[i][j].y;

    circle(X2,Y2,20);
}
void mutareStanga(joc A[][10], int i, int j)
{
    int X = A[i][j].x;
    int Y = A[i][j].y;

    //stergere

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,20,20);

    //mutare

    setcolor(YELLOW);

    A[i][j].x = A[i][j].x - 68;
    A[i][j].y = A[i][j].y + 68;

    int X2 = A[i][j].x;
    int Y2 = A[i][j].y;

    circle(X2,Y2,20);
}
void initMeniu()
{
    initwindow(612,398);
    cleardevice();
    readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\razboi.jpg",0,0,612,398);
    settextstyle(6, HORIZ_DIR, 2);
    outtextxy(209,30, "RAZBOI IN 8");
    settextstyle(6, HORIZ_DIR, 1);
    outtextxy(207, 120,"MULTIPLAYER");
    int x,y;
    int gatu=1;
    while(gatu>0){
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>200  && x<400 && y>115 && y<150){
                closegraph(CURRENT_WINDOW);
                initJoc();
                initCoordonate();
                int X,Y,time=2,castigator=0,rand=2;///rand stabileste cine trebuie sa mute piesa
            while(!castigator)
            {
                while(time>0)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        if(time==2)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
                            for(int i=1; i<=8; ++i)
                                for(int j=1; j<=8; ++j)
                                    if(A[i][j].player!=3)
                                        if(abs(X-A[i][j].x)<vminx&&abs(Y-A[i][j].y)<vminy)
                                        {
                                            vminx=abs(X-A[i][j].x);
                                            vminy=abs(Y-A[i][j].y);
                                            L=i;
                                            C=j;
                                        }
                            cout<<L<<" "<<C<<"\n";
                            setcolor(RED);
                            setfillstyle(1,RED);
                            fillellipse(A[L][C].x,A[L][C].y,30,30);
                            setcolor(YELLOW);
                        }
                        if(time==1)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
                            for(int i=1; i<=8; ++i)
                                for(int j=1; j<=8; ++j)
                                    if(A[i][j].player!=3)
                                        if(abs(X-A[i][j].x)<vminx&&abs(Y-A[i][j].y)<vminy)
                                        {
                                            vminx=abs(X-A[i][j].x);
                                            vminy=abs(Y-A[i][j].y);
                                            L=i;
                                            C=j;
                                        }
                            cout<<L<<" "<<C<<"\n";
                            if(rand==1)
                                circle(A[L][C].x,A[L][C].y,20);
                            if(rand==2)
                            {
                                setfillstyle(1,WHITE);
                                fillellipse(A[L][C].x,A[L][C].y,20,20);
                            }
                            if(rand==1)rand=2;
                            else if(rand==2)rand=1;
                        }
                        time--;
                    }
                }
                time=2;
            }

            }

        }
    }
}
int main()
{
    for(int i=0; i<=9; ++i)
        for(int j=0; j<=9; ++j)
        {
            if(((i<1||i>8)||(j<1||j>8))||(i+j)%2)
                A[i][j].player=3;///noteaza cu 3 locatiile in  care nu pot ajunge piesele
            else A[i][j].player=0;///noteaza cu 0 potentialele locatii in care pot ajunge piesele
        }
//   A[]
    for(int j=1; j<=8; j+=2)
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

    initMeniu();
    initCoordonate();
    cleardevice();

    ///getmouseclick(WM_LBUTTONDOWN, X, Y);
    ///cout<<"x="<<X<<'\n'<<"y="<<Y<<'\n';

    /** stergerea piesei dupa mutare
    setcolor(BLACK);
    setfillstyle(1,BLACK);
    fillellipse(100,100,20,20);//coord x,coord y, raza,raza
    */
    getch();
    return 0;
}
