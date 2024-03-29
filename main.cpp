#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define player1 1
#define player2 2
#define neocupat 0
#define inexistent 3

using namespace std;


struct joc
{
    int colour;
    int timer;
    int x,y;///coord piesei de pe linia L si coloana C
    int player;/// 1,2,3,0
} tabla[10][10];
void initMatrice()
{
    for(int i=0; i<=9; ++i)
        for(int j=0; j<=9; ++j)
        {
            if(((i<1||i>8)||(j<1||j>8))||(i+j)%2)
                tabla[i][j].player=inexistent;///noteaza cu 3 locatiile in  care nu pot ajunge piesele
            else tabla[i][j].player=neocupat;///noteaza cu 0 potentialele locatii in care pot ajunge piesele
        }
//   A[]
    for(int j=1; j<=8; j+=2)
    {
        tabla[1][j].player=tabla[2][j+1].player=player2;
        tabla[7][j].player=tabla[8][j+1].player=player1;
    }
    for(int i=0; i<=9; ++i) ///afisarea matricii din spatele jocului
    {
        for(int j=0; j<=9; ++j)
            cout<<tabla[i][j].player<<" ";
        cout<<'\n';
    }
}
void initCoordonate()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    tabla[1][1].x = (width-544)/2;     //544 e lungimea si latimea tablei
    tabla[1][1].y = (height-544)/2;
    for(int j=2; j<=8; j++)
    {
        tabla[1][j].x = tabla[1][j-1].x + 68;
        tabla[1][j].y = (height-544)/2;
    }
    int i,j;
    for(i=2; i<=8; i++)
    {
        for(j=1; j<=8; j++)
        {
            tabla[i][j].x = tabla[i-1][j].x;
            tabla[i][j].y = tabla[i-1][j].y + 68;

        }

    }
}
void exitbutton()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    setcolor(RED);
    int poly[8];
    setfillstyle(1,RED);
    poly[0]=width*19/20;
    poly[1]=0;
    poly[2]=width;
    poly[3]=0;
    poly[4]=width;
    poly[5]=height/20;
    poly[6]=width*19/20;
    poly[7]=height/20;
    fillpoly(4,poly);
    setcolor(WHITE);
    line((width*19/20)+20,10,width-20,(height/20-10));
    line((width-20),10,(width*19/20+20),(height/20-10));

    /*
    exitbutton();
    if(x>width*19/20&&y<height/20)
                exit(0);
                */
}
void crearePiese(joc tabla[][10])
{
    for(int i=1; i<=8; ++i)
        for(int j=1; j<=8; ++j)
            if(tabla[i][j].player==player1)
            {
                setcolor(WHITE);
                setfillstyle(1,WHITE);
                fillellipse(tabla[i][j].x,tabla[i][j].y,20,20);
            }
            else if(tabla[i][j].player==player2)
            {
                setcolor(BLACK);
                setfillstyle(1,BLACK);
                fillellipse(tabla[i][j].x,tabla[i][j].y,20,20);
            }
}
void creareTabla()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    int i,j,k=0,poly[8],l,m=0;
    double x=68;
    double y=68;
    for(i=(height-544)/2-34,k+=y; m<8; i+=y,m++)
        for(j=(width-544)/2-34,l=0; l<8; j+=x,l++)
        {
            if((l%2==1 && m%2==0) || (l%2==0 && m%2==1))
            {
                setcolor(BLACK);
                setfillstyle(1,BLACK);
                poly[0]=j;
                poly[1]=i;
                poly[2]=j+x;
                poly[3]=i;
                poly[4]=j+x;
                poly[5]=k+i;
                poly[6]=j;
                poly[7]=k+i;
                fillpoly(4,poly);
            }
        }
    //setcolor(WHITE);
    //rectangle(30,30,574,574);
}
void initMeniu();

void initJoc()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);

    initwindow(width,height,"",-3,-3);
    readimagefile("img\\theme.jpg",-87,-80,width+83,height+80);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\theme.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\theme.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);
    readimagefile("img\\backbut.jpg",0,height-150,150,height);
    setcolor(YELLOW);
    exitbutton();

    int X,Y;
    int temp=1,color=1;
    while(temp>0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            X=mousex();
            Y=mousey();
            if(X>width*19/20&&Y<height/20)
                exit(0);
            if(X<150&&X>0&&Y<height&&Y>height-150)
            {

                closegraph(CURRENT_WINDOW);
                initMeniu();
            }
            else if (X>width/2-100  && X<width/2+90 && Y>height/2-80 && Y<height/2)
            {
                temp=0;
                color=RED;
                closegraph();
            }
            else if(X>width/2-130 && X<width/2+150 && Y>height/2+50 && Y<height/2+130)
            {
                temp=0;
                color=BLUE;
                closegraph();
            }
            else if(X>width/2-170  && X<width/2+200 && Y>height/2+180 && Y<height/2+260)
            {
                temp=0;
                color=GREEN;
                closegraph();
            }
        }
    }
    tabla[1][1].colour=color;
    initwindow(width,height,"",-3,-3);
    setbkcolor(color);
    if(color==RED)
    {
        readimagefile("img\\red.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bk.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk.jpg",-40,-40,width+40,height+40);

    }
    else if(color==BLUE)
    {
        readimagefile("img\\blue.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bk2.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk2.jpg",-40,-40,width+40,height+40);
    }
    else if(color==GREEN)
    {
        readimagefile("img\\green.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bkgreen.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bkgreen.jpg",-40,-40,width+40,height+40);
    }
    exitbutton();

    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\bk.jpg",-40,-40,width+40,height+40);
    setbkcolor(color);
    settextstyle(3,HORIZ_DIR,4);
    setcolor(YELLOW);

    //outtextxy(610,530,"Player 2's TURN");
    /* delay(500);
     outtextxy(610,50,"                                      ");
     delay(0);*/
    int i,j,k=0,poly[8],l,m=0;
    double x=68;
    double y=68;
    for(i=(height-544)/2-34,k+=y; m<8; i+=y,m++)
        for(j=(width-544)/2-34,l=0; l<8; j+=x,l++)
        {
            if((l%2==1 && m%2==0) || (l%2==0 && m%2==1))
            {
                setcolor(BLACK);
                setfillstyle(1,BLACK);
                poly[0]=j;
                poly[1]=i;
                poly[2]=j+x;
                poly[3]=i;
                poly[4]=j+x;
                poly[5]=k+i;
                poly[6]=j;
                poly[7]=k+i;
                fillpoly(4,poly);
            }
            else
            {
                setcolor(color+8);
                setfillstyle(1,color+8);
                poly[0]=j;
                poly[1]=i;
                poly[2]=j+x;
                poly[3]=i;
                poly[4]=j+x;
                poly[5]=k+i;
                poly[6]=j;
                poly[7]=k+i;
                fillpoly(4,poly);
            }
        }

    crearePiese(tabla);
}
void mutareDreaptaJOS(joc tabla[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    creareTabla();

    setcolor(BLACK);

    circle(X+34,Y+34,20);
    setfillstyle(1,BLACK);
    fillellipse(X+34,Y+34,20,20);

    delay(400);

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X+34,Y+34,30,30);

    delay(0);

    setcolor(WHITE);
    creareTabla();

    //mutare

    setcolor(BLACK);

    int X2 = tabla[i][j].x + 68;
    int Y2 = tabla[i][j].y +68;

    circle(X2,Y2,20);
    setfillstyle(1,BLACK);
    fillellipse(X2,Y2,20,20);

}
void mutareDreaptaSUS(joc tabla[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    creareTabla();

    setcolor(BLACK);

    circle(X+34,Y-34,20);
    setfillstyle(1,BLACK);
    fillellipse(X+34,Y-34,20,20);

    delay(400);

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X+34,Y-34,30,30);

    delay(0);

    setcolor(WHITE);
    creareTabla();

    //mutare

    setcolor(BLACK);

    int X2 = tabla[i][j].x + 68;
    int Y2 = tabla[i][j].y - 68;
    circle(X2,Y2,20);
    setfillstyle(1,BLACK);
    fillellipse(X2,Y2,20,20);

}
void mutareStangaJOS(joc tabla[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    creareTabla();

    setcolor(BLACK);

    circle(X-34,Y+34,20);
    setfillstyle(1,BLACK);
    fillellipse(X-34,Y+34,20,20);

    delay(400);

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X-34,Y+34,30,30);

    delay(0);

    setcolor(WHITE);
    creareTabla();

    //mutare

    setcolor(BLACK);

    int X2 = tabla[i][j].x - 68;
    int Y2 = tabla[i][j].y +68;

    circle(X2,Y2,20);
    setfillstyle(1,BLACK);
    fillellipse(X2,Y2,20,20);

}
void mutareStangaSUS(joc tabla[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    creareTabla();

    setcolor(BLACK);

    circle(X-34,Y-34,20);
    setfillstyle(1,BLACK);
    fillellipse(X-34,Y-34,20,20);

    delay(400);

    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(X-34,Y-34,30,30);

    delay(0);

    setcolor(WHITE);
    creareTabla();

    //mutare

    setcolor(BLACK);

    int X2 = tabla[i][j].x - 68;
    int Y2 = tabla[i][j].y - 68;

    circle(X2,Y2,20);
    setfillstyle(1,BLACK);
    fillellipse(X2,Y2,20,20);
}
void afisareScor(int nrPiesePlayer1, int nrPiesePlayer2)
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:0");
        outtextxy(width-400, height/2-30, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:1");
        outtextxy(width-400, height/2-30, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:8");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:7");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:6");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:5");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:4");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:3");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/2-30, "P2 SCORE:2");
        outtextxy(width-400, height/2-30, "P1 SCORE:0");
    }
}
void cautaPiesaApasata(joc tabla[][10], int X, int Y,int &L,int &C)
{
    int vminx=100,vminy=100;
    for(int i=1; i<=8; ++i)
        for(int j=1; j<=8; ++j)
            if(tabla[i][j].player!=inexistent)
                if(abs(X-tabla[i][j].x) < vminx&&abs(Y-tabla[i][j].y)<vminy)
                {
                    vminx=abs(X-tabla[i][j].x);
                    vminy=abs(Y-tabla[i][j].y);
                    L=i;
                    C=j;
                }
}
void eliminaPiesa(int lin,int col,joc tabla[][10])
{
    setcolor(tabla[1][1].colour+8);
    setfillstyle(1,tabla[1][1].colour+8);
    fillellipse(tabla[lin][col].x,tabla[lin][col].y,30,30);
    tabla[lin][col].player=neocupat;
}
void verificaStergereALB(int i, int j, joc tabla[][10], int &nrPiesePlayer1)
{

    if(i!=8)
    {
        if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
        {
            tabla[i][j].player=neocupat;
            setcolor(tabla[1][1].colour+8);
            setfillstyle(1,tabla[1][1].colour+8);
            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
            nrPiesePlayer1--;
        }
    }
    else if(i==8)
        if((tabla[i-1][j+1].player==player2&&tabla[i-1][j-1].player!=neocupat)
                ||(tabla[i-1][j+1].player!=neocupat&&tabla[i-1][j-1].player==player2))
        {
            tabla[i][j].player=neocupat;
            setcolor(tabla[1][1].colour+8);
            setfillstyle(1,tabla[1][1].colour+8);
            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
            nrPiesePlayer1--;
        }
}
void verificaStergereNEGRU(int i, int j, joc tabla[][10], int &nrPiesePlayer2)
{
    if(i!=1)
    {
        if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
        {
            tabla[i][j].player = neocupat;
            setcolor(tabla[1][1].colour+8);
            setfillstyle(1,tabla[1][1].colour+8);
            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
            nrPiesePlayer2--;

        }
    }
    else if(i==1)
        if((tabla[i+1][j+1].player==player1&&tabla[i+1][j-1].player!=neocupat)
                ||(tabla[i+1][j+1].player!=neocupat&&tabla[i+1][j-1].player==player1))
        {
            tabla[i][j].player=neocupat;
            setcolor(tabla[1][1].colour+8);
            setfillstyle(1,tabla[1][1].colour+8);
            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
            nrPiesePlayer2--;
        }
}
bool verificaPericol(joc tabla[][10], int i, int j)
{
    if(tabla[i][j].player==neocupat)
    {
        if(tabla[i+1][j-1].player==player2 && tabla[i-1][j+1].player==player2
                &&(tabla[i-2][j].player==player2 || tabla[i-2][j].player==player1) &&
                (tabla[i][j+2].player==player2 || tabla[i][j+2].player==player1) &&
                (tabla[i-2][j+2].player==player2 || tabla[i-2][j+2].player==player1))
        {
            cout<<"if 1"<<"\n";
            return true;///colt stanga jos
        }

        else if(tabla[i-1][j-1].player==player2 && tabla[i+1][j+1].player==player2
                && (tabla[i][j+2].player==player2 ||tabla[i][j+2].player==player1)
                && (tabla[i+2][j].player==player2 || tabla[i+2][j].player==player1) &&
                (tabla[i+2][j+2].player==player2 || tabla[i+2][j+2].player==player1))
        {
            cout<<"if 2"<<"\n";
            return true;///colt stanga sus

        }

        else if(tabla[i+1][j+1].player==player2 && tabla[i-1][j-1].player==player2
                &&(tabla[i][j-2].player==player2 || tabla[i][j-2].player==player1)
                && (tabla[i-2][j].player==player2 || tabla[i-2][j].player==player1) &&
                (tabla[i-2][j-2].player==player2||tabla[i-2][j-2].player==player1))
        {
            cout<<"if 3"<<"\n";
            return true;///colt dreapta jos
        }
        else if(tabla[i-1][j+1].player==player2 && tabla[i+1][j-1].player==player2
                &&(tabla[i][j-2].player==player1 || tabla[i][j-2].player==player2)
                && (tabla[i+2][j].player==player1 || tabla[i+2][j].player==player2) &&
                (tabla[i+2][j-2].player==player1 || tabla[i+2][j-2].player==player2))
        {
            cout<<"if 4"<<"\n";
            return true;///colt dreapta sus
        }

    }
    return false;

}
void verificaCastigator(int nrPiesePlayer1, int nrPiesePlayer2)
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    if(nrPiesePlayer1 == 0||(nrPiesePlayer1+2<=nrPiesePlayer2&&nrPiesePlayer1==1))///3 piese asigura eliminarea unei piese in cazul 3<=3,nrPiesePlayer1=1 si nrPiesePlayer2=3
    {
        delay(500);
        closegraph();
        initwindow(500,300,"WINNER",width/3,height/3);
        settextstyle(3,HORIZ_DIR,5);
        setcolor(tabla[1][1].colour+8);
        outtextxy(60,120,"PLAYER 2 WON!");
        delay(5000);
        closegraph();
        initMeniu();
    }
    else if(nrPiesePlayer2 == 0||(nrPiesePlayer2+2<=nrPiesePlayer1&&nrPiesePlayer2==1))
    {
        delay(500);
        closegraph();
        initwindow(500,300,"WINNER",width/3,height/3);
        settextstyle(3,HORIZ_DIR,5);
        setcolor(tabla[1][1].colour+8);
        outtextxy(60,120,"PLAYER 1 WON!");
        delay(5000);
        closegraph();
        initMeniu();
    }
    else if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 1)
    {
        delay(500);
        closegraph();
        initwindow(500,300,"WINNER",width/3,height/3);
        settextstyle(3,HORIZ_DIR,5);
        setcolor(tabla[1][1].colour+8);
        outtextxy(170,120,"DRAW!");
        delay(5000);
        closegraph();
        initMeniu();
    }
}
void playPVP()
{

    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    closegraph(CURRENT_WINDOW);
    initJoc();
    initCoordonate();
    setcolor(YELLOW);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\pvp.jpg",600,200,800,300 );
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\back.png",0,height-150,150,height );
    ///left top right bottom
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(100, height/2-30, "P2 SCORE:8");
    outtextxy(width-400, height/2-30, "P1 SCORE:8");
    outtextxy(width/3,height-100,"PLAYER 1: YOUR TURN!");
    outtextxy(width/3,20,"PLAYER 2 WAITING...      ");
    outtextxy(20, height-40, "Save & Exit");
    ///outtextxy(width/3-50,height-100,"PLAYER 1: YOUR TURN!");
    for(int i=0; i<=9; ++i)
    {
        cout<<'\n';
        for(int j=0; j<=9; ++j)
            cout<<tabla[i][j].player<<" ";
        cout<<'\n';
    }
    int X,Y,time = 2,castigator = 0,rand = 1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8,clickedPlayer = neocupat;///rand stabileste cine trebuie sa mute piesa

    afisareScor(nrPiesePlayer1, nrPiesePlayer2);
    long i = 0;
    clock_t now = 0;
    int interval = 1;
    int elapsed = 0;
    int sec=0;
    int d=0,f=0;
    now = clock();
    while(!castigator)
    {
        while(time>0)
        {
            elapsed = (clock()-now)/CLOCKS_PER_SEC;

            if(elapsed>=interval)
            {
                interval += 1;
                //sec=120-(elapsed-d);
                sec=tabla[1][1].timer-(elapsed-0);
                if(sec<100)
                    outtextxy(50,100,"        ");
                char buffer [50];
                int n=sprintf (buffer, "%d", sec);
                outtextxy(50,50,"TIME");
                outtextxy(50,100,buffer);

                if(120-(elapsed-d)==0)
                {
                    if(nrPiesePlayer1>nrPiesePlayer2)
                    {
                        closegraph();
                        initwindow(500,300,"WINNER",width/3,height/3);
                        outtextxy(30,50,"PLAYER 1 WON!");
                        delay(5000);
                        closegraph();
                        initMeniu();
                    }
                    if(nrPiesePlayer1<nrPiesePlayer2)
                    {
                        closegraph();
                        initwindow(500,300,"WINNER",width/3,height/3);
                        outtextxy(30,50,"PLAYER 2 WON!");
                        delay(5000);
                        closegraph();
                        initMeniu();
                    }
                    if(nrPiesePlayer1==nrPiesePlayer2)
                    {
                        closegraph();
                        initwindow(500,300,"WINNER",width/3,height/3);
                        outtextxy(30,50,"DRAW!");
                        delay(5000);
                        closegraph();
                        initMeniu();
                    }
                }
            }
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                int L1,C1;
                if(time==2)
                {

                    clickedPlayer=neocupat;
                    while(clickedPlayer!=rand)
                    {
                        getmouseclick(WM_LBUTTONDOWN, X, Y);
                        cout<<X<<" "<<Y<<" "<<clickedPlayer<<'\n';
                        int L=0,C=0;
                        int width=GetSystemMetrics(SM_CXSCREEN);
                        int height=GetSystemMetrics(SM_CYSCREEN);
                        if(X>width*19/20&&Y<height/20)
                            exit(0);

                        if(X<150&&X>0&&Y<height&&Y>height-150)
                        {

                            FILE *progres;
                            progres=fopen("fisier.txt","w");
                            int poz[101]= {0},nr=0;
                            for(int i=0; i<=9; ++i)
                                for(int j=0; j<=9; ++j)
                                {
                                    int coord=tabla[i][j].player;
                                    cout<<coord<<" ";
                                    //poz[++nr]=tabla[i][j].player;
                                    fprintf(progres,"%d ",coord);
                                    //fout<<coord<<" ";
                                }
                                int timer=sec;
                                fprintf(progres,"%d",timer);
                            fclose(progres);
                            //fwrite(&poz,sizeof(int),nr,progres);
                            closegraph(CURRENT_WINDOW);
                            initMeniu();
                        }
                        cautaPiesaApasata(tabla, X,Y,L,C);
                        clickedPlayer = tabla[L][C].player;
                        cout<<L<<" "<<C<<"\n";

                        if(clickedPlayer==rand)
                        {
                            if((tabla[L+1][C+1].player==neocupat||tabla[L+1][C-1].player==neocupat)||(tabla[L-1][C+1].player==neocupat||tabla[L-1][C-1].player==neocupat))///verifica piesa apasata ca sa nu fie blocata
                            {
                                tabla[L][C].player=neocupat;
                                eliminaPiesa(L,C,tabla);
                            }
                            //else clickedPlayer=neocupat;
                        }
                        /*else
                        {
                            clickedPlayer=neocupat;
                            if(ismouseclick(WM_LBUTTONDOWN)){
                            Beep(1000,10);
                            clearmouseclick(WM_LBUTTONDOWN);}
                        }*/
                        L1=L;
                        C1=C;
                    }

                }
                if(time==1)
                {
                    getmouseclick(WM_LBUTTONDOWN, X, Y);
                    cout<<X<<" "<<Y<<'\n';
                    int width=GetSystemMetrics(SM_CXSCREEN);
                    int height=GetSystemMetrics(SM_CYSCREEN);
                    if(X>width*19/20&&Y<height/20)
                        exit(0);
                    if(X<150&&X>0&&Y<height&&Y>height-150)
                    {

                        FILE *progres;
                        progres=fopen("fisier.txt","w");
                        int poz[101]= {0},nr=0;
                        for(int i=0; i<=9; ++i)
                            for(int j=0; j<=9; ++j)
                            {
                                int coord=tabla[i][j].player;
                                cout<<coord<<" ";
                                //poz[++nr]=tabla[i][j].player;
                                fprintf(progres,"%d ",coord);
                                //fout<<coord<<" ";
                            }
                            int timer=sec;
                        fprintf(progres,"%d",timer);
                        fclose(progres);
                        //fwrite(&poz,sizeof(int),nr,progres);
                        closegraph(CURRENT_WINDOW);
                        initMeniu();
                    }
                    int vminx=100,vminy=100, L=0,C=0;
                    cautaPiesaApasata(tabla,X,Y,L,C);
                    cout<<L<<" "<<C<<"\n";

                    if(rand == 2 && clickedPlayer == player2)
                    {
                        if(L>L1)
                            L=L1+1;
                        else
                            L=L1-1;
                        if(C1>C)
                            C=C1-1;
                        else
                            C=C1+1;
                        if(tabla[L][C].player==neocupat)
                        {
                            setcolor(YELLOW);
                            outtextxy(width/3,height-100,"PLAYER 1: YOUR TURN!");
                            outtextxy(width/3,20,"PLAYER 2 WAITING...      ");

                            setcolor(BLACK);
                            setfillstyle(1,BLACK);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                            tabla[L][C].player=player2;
                            //tabla[L1][C1].player=neocupat;
                            rand=1;
                        }
                        else
                        {
                            setcolor(BLACK);
                            setfillstyle(1,BLACK);
                            Beep(1000,10);
                            fillellipse(tabla[L1][C1].x,tabla[L1][C1].y,20,20);
                            rand=5;
                            tabla[L1][C1].player=player2;
                        }

                    }
                    else if(rand==1 && clickedPlayer == player1)
                    {
                        if(L>L1)
                            L=L1+1;
                        else
                            L=L1-1;
                        if(C1>C)
                            C=C1-1;
                        else
                            C=C1+1;
                        if(tabla[L][C].player==neocupat)
                        {
                            setcolor(YELLOW);
                            outtextxy(width/3,20, "PLAYER 2: YOUR TURN!");
                            outtextxy(width/3,height-100,"PLAYER 1 WAITING...      ");
                            setcolor(WHITE);
                            setfillstyle(1,WHITE);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                            tabla[L][C].player=player1;
                            tabla[L1][C1].player=neocupat;
                            rand=2;
                        }
                        else
                        {
                            setcolor(WHITE);
                            setfillstyle(1,WHITE);
                            Beep(1000,10);
                            fillellipse(tabla[L1][C1].x,tabla[L1][C1].y,20,20);
                            tabla[L1][C1].player=player1;
                            rand=4;
                        }
                    }
                    if(rand==5)rand=2;
                    if(rand==4)rand=1;

                }

                time--;
            }
        }
        for(int i=1; i<=8; ++i)
            for(int j=1; j<=8; ++j)
            {
                if(tabla[i][j].player==player1)
                    verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                if(tabla[i][j].player==player2)
                    verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
            }
        afisareScor(nrPiesePlayer1, nrPiesePlayer2);
        verificaCastigator(nrPiesePlayer1, nrPiesePlayer2);
        time=2;
    }
}
//}
void inchiderePiesa(int &mutat)
{
    mutat=0;
    for(int i = 1; i <= 8; i++)
        for(int j = 1; j <= 8; j++)
        {
            ///caz I - colt STANGA JOS
            if(tabla[i][j].player==player1 && (tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1)
                    && (tabla[i+1][j+1].player==player2 || tabla[i+1][j+1].player==player1) && tabla[i+1][j-1].player==neocupat)
            {
                cout<<"CAZ 1!!";
                if(tabla[i][j-2].player==player2)
                {
                    mutat = 1;
                    mutareDreaptaJOS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i+2][j-2].player == player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j-2);
                    tabla[i+2][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i+2][j].player ==player2)
                {
                    mutat = 1;
                    mutareStangaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    return;
                    break;
                }
                return;
            }
            ///caz 2 - colt DREAPTA JOS
            else if(tabla[i][j].player==player1 && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && (tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && tabla[i+1][j+1].player==neocupat)
            {
                cout<<"CAZ 2!!";
                if(tabla[i][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i+2][j+2].player == player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i+2,j+2);
                    tabla[i+2][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i+2][j].player == player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
            }
            ///caz 3 - colt DREAPTA SUS
            else if(tabla[i][j].player==player1 && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && (tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1) && (tabla[i+1][j+1].player==player2 || tabla[i+1][j+1].player==player1) && tabla[i-1][j+1].player==neocupat)
            {
                cout<<"CAZ 3!!";
                if(tabla[i-2][j+2].player == player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i-2][j].player == player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i][j+2].player ==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                return;
            }
            ///caz 4 - colt STANGA SUS
            else if(tabla[i][j].player==player1 && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && (tabla[i+1][j+1].player==player2 || tabla[i+1][j+1].player==player1) && tabla[i-1][j-1].player==neocupat)
            {
                cout<<"CAZ 4!!";
                if(tabla[i-2][j-2].player == player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j-2);
                    tabla[i-2][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i-2][j].player == player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i][j-2].player ==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
            }
            ///caz 5 - margine STANGA - SUS
            else if(tabla[i][j].player==player1 && tabla[i][j-1].player==inexistent && tabla[i+1][j-1].player==inexistent && (tabla[i+1][j+1].player==player1 || tabla[i+1][j+1].player==player2) &&tabla[i-1][j+1].player==neocupat)
            {
                cout<<"CAZ 5!!"<<"\n";
                if(tabla[i-2][j].player==player2)
                {
                    cout<<"c5 ramura 1"<<"\n";
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i-2][j+2].player==player2)
                {
                    cout<<"c5 ramura 2"<<"\n";
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i][j+2].player==player2)
                {
                    cout<<"c5 ramura 3"<<"\n";
                    mutat=1;
                    mutareStangaSUS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    return;
                    break;
                }
                return;
            }
            ///caz 6 - margine STANGA - JOS
            else if(tabla[i][j].player==player1 && tabla[i][j-1].player==inexistent && tabla[i+1][j-1].player==inexistent && (tabla[i-1][j+1].player==player1||tabla[i-1][j+1].player==player2)&&tabla[i+1][j+1].player==neocupat)
            {
                cout<<"CAZ 6!!";
                if(tabla[i+2][j].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i+2][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i+2,j+2);
                    tabla[i+2][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
            }
            ///caz 7 - margine SUS - STANGA
            else if(tabla[i][j].player==player1 && tabla[i-1][j].player==inexistent && tabla[i-1][j-1].player==inexistent && (tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==player1) && tabla[i+1][j-1].player==neocupat)
            {
                cout<<"CAZ 7!!";
                if(tabla[i+2][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla, i+2, j-2);
                    tabla[i+2][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla, i, j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i+2][j].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla, i+2, j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
            }
            ///caz 8 - margine sus - DREAPTA
            else if(tabla[i][j].player==player1 && tabla[i-1][j].player==inexistent && tabla[i-1][j-1].player==inexistent &&(tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==player1) && tabla[i+1][j+1].player==neocupat)
            {
                cout<<"CAZ 8!!";
                if(tabla[i+2][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i+2,j+2);
                    tabla[i+2][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i+2][j].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    return;
                    break;
                }
                return;
            }
            ///caz 9 - margine DREAPTA - JOS
            else if(tabla[i][j].player==player1 && tabla[i][j+1].player==inexistent && tabla[i-1][j+1].player==inexistent &&(tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1)&&tabla[i+1][j-1].player==neocupat)
            {
                cout<<"CAZ 9!!";
                if(tabla[i+2][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla, i+2,j-2);
                    tabla[i+2][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i+2][j].player==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
            }
            ///cazul 10 -  margine DREAPTA - SUS
            else if(tabla[i][j].player==player1 && tabla[i][j+1].player==inexistent && tabla[i-1][j+1].player==inexistent && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && tabla[i-1][j-1].player==neocupat)
            {
                cout<<"CAZ 10!!";
                if(tabla[i-2][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j-2);
                    tabla[i-2][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i-2][j].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
            }
            ///cazul 11 - margine JOS -  DREAPTA
            else if(tabla[i][j].player==player1 && tabla[i-1][j].player == inexistent && tabla[i-1][j-1].player==inexistent && (tabla[i-1][j-1].player==player2 && tabla[i-1][j-1].player==player1 ) && tabla[i-1][j+1].player==neocupat)
            {
                cout<<"CAZ 11!!";
                if(tabla[i-2][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
                else if(tabla[i-2][j].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
                else if(tabla[i][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
            }
            ///cazul 12 - margine JOS - STANGA
            else if(tabla[i][j].player==player1 && tabla[i-1][j].player==inexistent && tabla[i-1][j-1].player==inexistent && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && tabla[i-1][j-1].player==neocupat)
            {
                cout<<"CAZ 12!!";
                if(tabla[i-2][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j-2);
                    tabla[i-2][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i][j-2].player==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i-2][j].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
            }
            ///cazul 13 - colt STANGA SUS
            else if(tabla[i][j].player==player1 && tabla[i-1][j-1].player==inexistent &&  tabla[i+1][j+1].player==neocupat && tabla[i+2][j+2].player==player2)
            {
                cout<<"CAZ 13!!";
                if(tabla[i+2][j+2].player==player2)
                {

                    mutat=1;
                    mutareStangaSUS(tabla,i+2,j+2);
                    tabla[i+2][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i][j+2].player==player2)
                {

                    mutat=1;
                    mutareStangaJOS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
                else if(tabla[i+2][j].player==player2)
                {

                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j+1].player=player2;
                    break;
                }
            }
            ///cazul 14 - colt DREAPTA JOS
            else if(tabla[i][j].player==player1 && tabla[i+1][j+1].player==inexistent && tabla[i+1][j].player==inexistent && tabla[i][j+1].player == inexistent &&  tabla[i-1][j-1].player==neocupat && tabla[i-2][j-2].player==player2)
            {
                cout<<"CAZ 14!!"<<"\n";
                if(tabla[i-2][j-2].player==player2)
                {
                    cout<<"c14 ramura 1"<<"\n";
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j-2);
                    tabla[i-2][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i-2][j].player==player2)
                {
                    cout<<"c14 ramura 2"<<"\n";
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
                else if(tabla[i][j-2].player==player2)
                {
                    cout<<"c14 ramura 3"<<"\n";
                    mutat=1;
                    mutareDreaptaSUS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    return;
                    break;
                }
                return;


            }
        }
}
void playAgainstSoldierBOT()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);

    closegraph(CURRENT_WINDOW);
    initJoc();
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);
    readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.jpg",0,height-150,150,height);
    initCoordonate();
    //cleardevice();

    //PLAYER 2 = AI
    setcolor(YELLOW);
    settextstyle(4,HORIZ_DIR,3);
    outtextxy(width/2-150,40,"SOLDIER BOT");
    outtextxy(width-400,80,"DIFFICULTY LEVEL:");
    outtextxy(width-400,130,"EASY");
    outtextxy(20, height-40, "BACK");
    int X,Y,time=2,castigator=0,rand=2, coloanaBot = 2;///rand stabileste cine trebuie sa mute piesa
    int I_ai=2, J_ai = coloanaBot, jCount=1, countMutariInitiale=1, piesaMutata[9]= {0};
    int liniaCurenta = 2,randMutare=1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8, i_hitler = 3;
    int i_soldier=2, j_soldier=4, moveCounterSoldier=3;
    afisareScor(nrPiesePlayer1,nrPiesePlayer2);

    exitbutton();

    while(!castigator)
    {
        while(time>0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                int L1,C1;
                for(int i=1; i<=8; ++i)
                    for(int j=1; j<=8; ++j)
                    {
                        if(tabla[i][j].player==player1)
                            verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                        if(tabla[i][j].player==player2)
                            verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                    }
                if(time==2)
                {
                    cout<<X<<" "<<Y<<'\n';
                    getmouseclick(WM_LBUTTONDOWN, X, Y);
                    if(X>width*19/20&&Y<height/20)
                        exit(0);
                    if(X<150&&X>0&&Y<height&&Y>height-150)
                    {
                        closegraph(CURRENT_WINDOW);
                        initMeniu();
                    }
                    int L=0,C=0;
                    cautaPiesaApasata(tabla, X,Y,L,C);
                    setcolor(tabla[1][1].colour+8);
                    setfillstyle(1,tabla[1][1].colour+8);
                    fillellipse(tabla[L][C].x,tabla[L][C].y,30,30);
                    L1=L;
                    C1=C;

                }
                if(time==1)
                {
                    int width=GetSystemMetrics(SM_CXSCREEN);
                    int height=GetSystemMetrics(SM_CYSCREEN);
                    cout<<X<<" "<<Y<<'\n';
                    getmouseclick(WM_LBUTTONDOWN, X, Y);
                    if(X>width*19/20&&Y<height/20)
                        exit(0);
                    if(X<150&&X>0&&Y<height&&Y>height-150)
                    {
                        closegraph(CURRENT_WINDOW);
                        initMeniu();
                    }
                    cout<<X<<" "<<Y<<'\n';
                    int L=0,C=0;
                    cautaPiesaApasata(tabla, X,Y,L,C);
                    cout<<L<<" "<<C<<"\n";

                    if(rand==2)
                    {
                        if(L>L1)
                            L=L1+1;
                        else
                            L=L1-1;
                        if(C1>C)
                            C=C1-1;
                        else
                            C=C1+1;
                        cout<<L<<" "<<C<<"\n";
                        if(tabla[L][C].player==neocupat)
                        {
                            setcolor(WHITE);
                            setfillstyle(1,WHITE);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                            tabla[L][C].player=player1;
                            tabla[L1][C1].player=neocupat;
                        }
                        int gasit;

                        if(moveCounterSoldier==4)
                        {
                            gasit=0;
                            for(int i=1; i<=8; i++)
                            {
                                for(int j=1; j<=8; j++)
                                    if(tabla[i][j].player==player2 && (tabla[i+1][j-1].player == neocupat || tabla[i+1][j+1].player == neocupat || tabla[i-1][j-1].player == neocupat|| tabla[i-1][j+1].player == neocupat)&& gasit==0)
                                    {
                                        //cout<<"I IS:"<<i<<"\n";
                                        //cout<<"J IS:"<<j<<"\n";
                                        moveCounterSoldier=0;
                                        i_soldier=i;
                                        j_soldier=j;
                                        cout<<"I SOLDIER IS:"<<i_soldier<<"\n";
                                        cout<<"J SOLDIER IS:"<<j_soldier<<"\n";
                                        gasit=1;
                                        break;

                                    }
                                if(gasit==1)
                                    break;
                            }
                            moveCounterSoldier=0;
                        }
                        cout<<"COUNTER SOLDIER IS:"<<moveCounterSoldier<<"\n";
                        //cout<<"I SOLDIER IS:"<<i_soldier<<"\n";
                        //cout<<"J SOLDIER IS:"<<j_soldier<<"\n";
                        if(tabla[i_soldier+1][j_soldier-1].player == neocupat && tabla[i_soldier][j_soldier].player==player2)
                        {
                            cout<<"A INTRAT PE 1"<<"\n";
                            delay(300);
                            mutareStangaJOS(tabla,i_soldier, j_soldier);
                            tabla[i_soldier][j_soldier].player=neocupat;
                            i_soldier++;
                            j_soldier--;
                            tabla[i_soldier][j_soldier].player=player2;
                            moveCounterSoldier++;
                        }
                        else if(tabla[i_soldier+1][j_soldier+1].player == neocupat && tabla[i_soldier][j_soldier].player==player2)
                        {
                            cout<<"A INTRAT PE 2"<<"\n";
                            delay(300);
                            mutareDreaptaJOS(tabla,i_soldier,j_soldier);
                            tabla[i_soldier][j_soldier].player=neocupat;
                            i_soldier++;
                            j_soldier++;
                            tabla[i_soldier][j_soldier].player=player2;
                            moveCounterSoldier++;
                        }
                        else if(tabla[i_soldier-1][j_soldier-1].player == neocupat && tabla[i_soldier][j_soldier].player==player2)
                        {
                            cout<<"A INTRAT PE 3"<<"\n";
                            delay(300);
                            mutareStangaSUS(tabla,i_soldier, j_soldier);
                            tabla[i_soldier][j_soldier].player=neocupat;
                            i_soldier--;
                            j_soldier--;
                            tabla[i_soldier][j_soldier].player=player2;
                            moveCounterSoldier++;
                        }
                        else if(tabla[i_soldier-1][j_soldier+1].player == neocupat && tabla[i_soldier][j_soldier].player==player2)
                        {
                            cout<<"A INTRAT PE 4"<<"\n";
                            delay(300);
                            mutareDreaptaSUS(tabla,i_soldier,j_soldier);
                            tabla[i_soldier][j_soldier].player=neocupat;
                            i_soldier--;
                            j_soldier++;
                            tabla[i_soldier][j_soldier].player=player2;
                            moveCounterSoldier++;
                        }
                        else
                        {
                            moveCounterSoldier=4;
                        }

                        /*
                        if(liniaCurenta == 2)
                        {
                            if(J_ai != 8)
                            {
                                if(jCount == 6)
                                {
                                    I_ai = 2;
                                    coloanaBot += 2;
                                    J_ai = coloanaBot;
                                    jCount = 1;

                                }
                            }
                            else
                            {
                                liniaCurenta = 1;
                                coloanaBot = 1;
                                J_ai = 1;
                                I_ai = 1;
                            }
                        }
                        else
                        {

                            if(jCount == 6 && J_ai != 7)
                            {
                                I_ai = 1;
                                coloanaBot+=2;
                                J_ai = coloanaBot;
                                jCount = 1;

                            }
                            cout<<endl;
                            cout<<jCount<<'\n';
                        }
                        */
                    }

                }
                time--;

            }


        }
        time=2;
        for(int i=1; i<=8; ++i)
            for(int j=1; j<=8; ++j)
            {
                if(tabla[i][j].player==player1)
                    verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                if(tabla[i][j].player==player2)
                    verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
            }
        afisareScor(nrPiesePlayer1, nrPiesePlayer2);
        verificaCastigator(nrPiesePlayer1, nrPiesePlayer2);

    }
}

void playAgainstHitlerBOT()
{
    closegraph(CURRENT_WINDOW);
    initJoc();
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);
    //readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.jpg",0,height-150,150,height);
    readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    initCoordonate();
    exitbutton();
    //cleardevice();

    //PLAYER 2 = AI
    settextstyle(4,HORIZ_DIR,3);
    setcolor(YELLOW);
    outtextxy(width/2-150,40,"HITLER BOT");
    outtextxy(width-400,80,"DIFFICULTY LEVEL:");
    outtextxy(width-400,130,"HARD");
    outtextxy(20, height-40, "BACK");
    //outtextxy(width-100, 530, "                                                             ");

    int X,Y,time=2,castigator=0,rand=2, coloanaBot = 2;///rand stabileste cine trebuie sa mute piesa
    int I_ai=2, J_ai = coloanaBot, jCount=1, countMutariInitiale=1, piesaMutata[9]= {0};
    int liniaCurenta = 2,randMutare=1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8, i_hitler = 3;
    afisareScor(nrPiesePlayer1,nrPiesePlayer2);
    while(!castigator)
    {
        while(time>0)
        {
            if(ismouseclick(WM_LBUTTONDOWN))
            {
                int L1,C1;
                for(int i=1; i<=8; ++i)
                    for(int j=1; j<=8; ++j)
                    {
                        if(tabla[i][j].player==player1)
                            verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                        if(tabla[i][j].player==player2)
                            verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                    }
                if(time==2)
                {
                    getmouseclick(WM_LBUTTONDOWN, X, Y);
                    cout<<X<<" "<<Y<<'\n';
                    if(X>width*19/20&&Y<height/20)
                        exit(0);
                    if(X<150&&X>0&&Y<height&&Y>height-150)
                    {
                        closegraph(CURRENT_WINDOW);
                        initMeniu();
                    }
                    int L=0,C=0;
                    cautaPiesaApasata(tabla, X,Y,L,C);
                    setcolor(tabla[1][1].colour+8);
                    setfillstyle(1,tabla[1][1].colour+8);
                    fillellipse(tabla[L][C].x,tabla[L][C].y,30,30);
                    L1=L;
                    C1=C;

                }
                if(time==1)
                {

                    getmouseclick(WM_LBUTTONDOWN, X, Y);
                    cout<<X<<" "<<Y<<'\n';
                    int L=0,C=0;
                    int width=GetSystemMetrics(SM_CXSCREEN);
                    int height=GetSystemMetrics(SM_CYSCREEN);
                    if(X>width*19/20&&Y<height/20)
                        exit(0);
                    if(X<150&&X>0&&Y<height&&Y>height-150)
                    {
                        closegraph(CURRENT_WINDOW);
                        initMeniu();
                    }
                    cautaPiesaApasata(tabla, X,Y,L,C);
                    cout<<L<<" "<<C<<"\n";

                    if(rand==2)
                    {
                        if(L>L1)
                            L=L1+1;
                        else
                            L=L1-1;
                        if(C1>C)
                            C=C1-1;
                        else
                            C=C1+1;
                        cout<<L<<" "<<C<<"\n";
                        if(tabla[L][C].player==neocupat)
                        {
                            setcolor(WHITE);
                            setfillstyle(1,WHITE);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                            tabla[L][C].player=player1;
                            tabla[L1][C1].player=neocupat;
                        }
                        setcolor(YELLOW);

                        delay(600);
                        if(countMutariInitiale==1)
                        {
                            mutareStangaJOS(tabla, 2, C);
                            countMutariInitiale++;
                            piesaMutata[C]=1;
                            tabla[2][C].player=neocupat;
                            tabla[3][C-1].player=player2;
                        }
                        else if(countMutariInitiale==2 || countMutariInitiale==3)
                        {
                            if(tabla[2][C-1].player==player2)
                            {
                                mutareStangaJOS(tabla, 2, C-1);
                                countMutariInitiale++;
                                piesaMutata[C-1]=1;
                                tabla[2][C-1].player=neocupat;
                                tabla[3][C-2].player=player2;

                            }
                            else if(tabla[2][C+1].player==player2)
                            {
                                mutareStangaJOS(tabla,2,C+1);
                                countMutariInitiale++;
                                piesaMutata[C+1]=1;
                                tabla[2][C+1].player=neocupat;
                                tabla[3][C].player=player2;
                            }

                            else if(C>4)
                            {

                                if(tabla[2][6].player == player2)
                                {
                                    mutareStangaJOS(tabla, 2, 6);
                                    countMutariInitiale++;
                                    piesaMutata[6]=1;
                                    tabla[2][6].player = neocupat;
                                    tabla[3][5].player = player2;

                                }
                                else if(tabla[2][8].player == player2)
                                {
                                    mutareStangaJOS(tabla, 2, 8);
                                    countMutariInitiale++;
                                    piesaMutata[8]=1;
                                    tabla[2][8].player = neocupat;
                                    tabla[3][7].player = player2;
                                }
                                else if(tabla[2][4].player == player2)
                                {
                                    mutareStangaJOS(tabla, 2, 4);
                                    countMutariInitiale++;
                                    piesaMutata[4]=1;
                                    tabla[2][4].player = neocupat;
                                    tabla[3][3].player = player2;
                                }
                                else if(tabla[2][2].player == player2)
                                {
                                    mutareStangaJOS(tabla,2,2);
                                    countMutariInitiale++;
                                    piesaMutata[2]=1;
                                    tabla[2][2].player = neocupat;
                                    tabla[3][1].player = player2;
                                }

                            }
                            else if(C<=4)
                            {
                                if(tabla[2][2].player == player2)
                                {
                                    mutareStangaJOS(tabla,2,2);
                                    countMutariInitiale++;
                                    piesaMutata[2]=1;
                                    tabla[2][2].player = neocupat;
                                    tabla[3][1].player = player2;
                                }
                                else if(tabla[2][4].player == player2)
                                {
                                    mutareStangaJOS(tabla,2,4);
                                    countMutariInitiale++;
                                    piesaMutata[4]=1;
                                    tabla[2][4].player = neocupat;
                                    tabla[3][3].player = player2;
                                }
                                else if(tabla[2][6].player == player2)
                                {
                                    mutareStangaJOS(tabla, 2, 6);
                                    countMutariInitiale++;
                                    piesaMutata[6]=1;
                                    tabla[2][6].player = neocupat;
                                    tabla[3][5].player = player2;

                                }
                                else if(tabla[2][8].player == player2)
                                {
                                    mutareStangaJOS(tabla, 2, 8);
                                    countMutariInitiale++;
                                    piesaMutata[8]=1;
                                    tabla[2][8].player = neocupat;
                                    tabla[3][7].player = player2;
                                }
                            }



                        }
                        else if(countMutariInitiale==4)
                        {
                            for(int j=2; j<=8; j+=2)
                                if(piesaMutata[j]==0)
                                {
                                    mutareStangaJOS(tabla,2,j);
                                    tabla[2][j].player=neocupat;
                                    tabla[3][j-1].player=player2;
                                }
                            countMutariInitiale++;

                        }
                        else if(countMutariInitiale==5)
                        {
                            if(tabla[4][2].player!=player1)
                            {
                                mutareDreaptaJOS(tabla, 1, 1);
                                tabla[1][1].player=neocupat;
                                tabla[2][2].player=player2;
                                countMutariInitiale++;
                            }
                            else
                            {
                                mutareDreaptaJOS(tabla,3,3);
                                tabla[3][3].player=neocupat;
                                tabla[4][4].player=player2;
                                countMutariInitiale++;
                            }
                        }
                        else
                        {
                            int mutat;
                            inchiderePiesa(mutat);
                            cout<<endl;
                            cout<<"MUTAT = "<<mutat<<"\n";
                            if(mutat==0)
                            {

                                int Col;
                                int oki = 0;
                                while(oki == 0)
                                {
                                    for(int j = 1; j<=8; j++)
                                        if(tabla[i_hitler][j].player == player2)
                                        {
                                            Col=j;
                                            oki = 1;
                                            break;
                                        }
                                    if(oki == 0)
                                    {
                                        if(i_hitler == 3 || i_hitler == 2)
                                            i_hitler--;
                                        else if(i_hitler == 1)
                                            i_hitler = 4;
                                        else if(i_hitler == 8)
                                            i_hitler = 5;
                                        else if(i_hitler==7 || i_hitler==6)
                                            i_hitler--;
                                        else i_hitler++;
                                    }

                                }

                                if(tabla[i_hitler+1][Col+1].player == neocupat && tabla[i_hitler][Col].player==player2&& verificaPericol(tabla, i_hitler+1,Col+1)==false)
                                {

                                    mutareDreaptaJOS(tabla,i_hitler,Col);
                                    tabla[i_hitler][Col].player=neocupat;
                                    tabla[i_hitler+1][Col+1].player=player2;
                                    mutat=1;

                                }
                                else if(tabla[i_hitler+1][Col-1].player == neocupat && tabla[i_hitler][Col].player==player2 && verificaPericol(tabla, i_hitler+1, Col-1)==false)
                                {

                                    mutareStangaJOS(tabla,i_hitler,Col);
                                    tabla[i_hitler][Col].player=neocupat;
                                    tabla[i_hitler+1][Col-1].player=player2;
                                    mutat=1;
                                }
                                else if(tabla[i_hitler-1][Col+1].player == neocupat && tabla[i_hitler][Col].player==player2&& verificaPericol(tabla, i_hitler-1, Col+1)==false)
                                {

                                    mutareDreaptaSUS(tabla,i_hitler,Col);
                                    tabla[i_hitler][Col].player=neocupat;
                                    tabla[i_hitler-1][Col+1].player=player2;
                                    mutat=1;
                                }
                                else if(tabla[i_hitler-1][Col-1].player == neocupat && tabla[i_hitler][Col].player==player2 && verificaPericol(tabla, i_hitler-1, Col-1)==false)
                                {

                                    mutareStangaSUS(tabla,i_hitler,Col);
                                    tabla[i_hitler][Col].player=neocupat;
                                    tabla[i_hitler-1][Col-1].player=player2;
                                    mutat=1;
                                }
                                else
                                {
                                    if(i_hitler == 3 || i_hitler == 2)
                                        i_hitler--;
                                    else if(i_hitler == 1)
                                        i_hitler = 4;
                                    else if(i_hitler == 8)
                                        i_hitler = 5;
                                    else if(i_hitler==7 || i_hitler==6)
                                        i_hitler--;
                                    else i_hitler++;

                                    int oki2=0, Col2;
                                    while(oki2==0)
                                    {
                                        for(int j = 1; j<=8; j++)
                                            if(tabla[i_hitler][j].player == player2)
                                            {
                                                Col2=j;
                                                oki2 = 1;
                                                break;
                                            }
                                        if(oki2 == 0)
                                        {
                                            if(i_hitler == 3 || i_hitler == 2)
                                                i_hitler--;
                                            else if(i_hitler == 1)
                                                i_hitler = 4;
                                            else if(i_hitler == 8)
                                                i_hitler = 5;
                                            else if(i_hitler==7 || i_hitler==6)
                                                i_hitler--;
                                            else i_hitler++;
                                        }
                                    }


                                    if(tabla[i_hitler+1][Col2+1].player == neocupat && tabla[i_hitler][Col2].player==player2&& verificaPericol(tabla, i_hitler+1,Col2+1)==false)
                                    {

                                        mutareDreaptaJOS(tabla,i_hitler,Col);
                                        tabla[i_hitler][Col2].player=neocupat;
                                        tabla[i_hitler+1][Col2+1].player=player2;


                                    }
                                    else if(tabla[i_hitler+1][Col2-1].player == neocupat && tabla[i_hitler][Col2].player==player2 && verificaPericol(tabla, i_hitler+1, Col2-1)==false)
                                    {

                                        mutareStangaJOS(tabla,i_hitler,Col2);
                                        tabla[i_hitler][Col2].player=neocupat;
                                        tabla[i_hitler+1][Col2-1].player=player2;

                                    }
                                    else if(tabla[i_hitler-1][Col2+1].player == neocupat && tabla[i_hitler][Col2].player==player2&& verificaPericol(tabla, i_hitler-1, Col2+1)==false)
                                    {

                                        mutareDreaptaSUS(tabla,i_hitler,Col2);
                                        tabla[i_hitler][Col2].player=neocupat;
                                        tabla[i_hitler-1][Col2+1].player=player2;

                                    }
                                    else if(tabla[i_hitler-1][Col2-1].player == neocupat && tabla[i_hitler][Col2].player==player2 && verificaPericol(tabla, i_hitler-1, Col2-1)==false)
                                    {

                                        mutareStangaSUS(tabla,i_hitler,Col2);
                                        tabla[i_hitler][Col2].player=neocupat;
                                        tabla[i_hitler-1][Col2-1].player=player2;

                                    }
                                    else
                                    {
                                        int okay=0;
                                        int i_bonus=i_hitler+1;

                                        for(int j=2; j<=8; j+=2)
                                        {
                                            if(tabla[i_bonus][j].player==player2)
                                            {
                                                if(tabla[i_bonus+1][j+1].player==neocupat && okay==0)
                                                {
                                                    mutareDreaptaJOS(tabla, i_bonus,j);
                                                    tabla[i_bonus][j].player==neocupat;
                                                    tabla[i_bonus+1][j+1].player==player2;
                                                    okay=1;
                                                    break;
                                                }
                                                else if(tabla[i_bonus-1][j+1].player==neocupat && okay==0)
                                                {
                                                    mutareDreaptaSUS(tabla, i_bonus,j);
                                                    tabla[i_bonus][j].player==neocupat;
                                                    tabla[i_bonus-1][j+1].player==player2;
                                                    okay=1;
                                                    break;
                                                }
                                                else if(tabla[i_bonus+1][j-1].player==neocupat && okay==0)
                                                {
                                                    mutareStangaJOS(tabla, i_bonus,j);
                                                    tabla[i_bonus][j].player==neocupat;
                                                    tabla[i_bonus+1][j+1].player==player2;
                                                    okay=1;
                                                    break;
                                                }
                                                else if(tabla[i_bonus-1][j-1].player==neocupat && okay==0)
                                                {
                                                    mutareStangaSUS(tabla, i_bonus,j);
                                                    tabla[i_bonus][j].player==neocupat;
                                                    tabla[i_bonus-1][j-1].player==player2;
                                                    okay=1;
                                                    break;

                                                }
                                            }
                                            if(okay==1)
                                                break;
                                        }

                                    }

                                }


                            }

                        }

                    }
                    for(int i=1; i<=8; ++i)
                    {
                        for(int j=1; j<=8; ++j)
                            cout<<tabla[i][j].player<<" ";
                        cout<<'\n';
                    }
                }
                time--;
            }


        }
        time = 2;
        /*int I = 2, J = 2;
        delay(800);
        if(tabla[I+1][J+1].player == neocupat)
            mutatabla[1][1].colour+8 reapta(tabla,I,J);
        delay(800);
        int I2 = I+1, J2 = J+1;
        if(tabla[I2+1][J2-1].player == neocupat)
            mutareStanga(tabla,I2,J2);
            */
        for(int i=1; i<=8; ++i)
            for(int j=1; j<=8; ++j)
            {
                if(tabla[i][j].player==player1)
                    verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                if(tabla[i][j].player==player2)
                    verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
            }
        afisareScor(nrPiesePlayer1, nrPiesePlayer2);
        verificaCastigator(nrPiesePlayer1, nrPiesePlayer2);
    }



}
void initMeniuBOT()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    initwindow(width,height,"",-3,-3);
    cleardevice();

    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\difficulty.jpg",-40,-40,width+40,height+40);
    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    readimagefile("img\\difficulty.jpg",-87,-80,width+83,height+80);
    readimagefile("img\\backbut.jpg",0,height-150,150,height);
    //readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\ai.jpg",-40,-40,width+40,height+40);
    //readimagefile("‪C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.png",0,height-150,150,height);

    exitbutton();

    int x,y;
    int temp=1;
    while(temp>0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            int width=GetSystemMetrics(SM_CXSCREEN);
            int height=GetSystemMetrics(SM_CYSCREEN);
            x=mousex();
            y=mousey();
            if(x>width*19/20&&y<height/20)
                exit(0);
            if(x<150&&x>0&&y<height&&y>height-150)
            {
                closegraph(CURRENT_WINDOW);
                initMeniu();
            }
            if(x>width*19/20&&y<height/20)
                exit(0);

            cout<<x<<" "<<y;
            //if ((x>30  && x<290 && y>270 && y<300)||(x>115  && x<180 && y>325 && y<345))
            if(x<width/2&&y>height*2/3)
            {
                closegraph(CURRENT_WINDOW);
                playAgainstSoldierBOT();
            }
            //else if ((x>340  && x<565 && y>270 && y<305)||(x>405  && x<480 && y>325 && y<345))
            else if(x>width/2&&y>height*2/3)
            {
                closegraph(CURRENT_WINDOW);
                playAgainstHitlerBOT();
            }

        }
    }

}
void initpvpmeniu()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    initwindow(width,height,"",-3,-3);
    cleardevice();
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\difficulty.jpg",-40,-40,630,420);

    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\load game.jpg",-40,-40,width+40,height+40);
    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);

    //readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\load game.jpg",-40,-40,width+40,height+40);
    //readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.jpg",0,height-150,150,height);

    readimagefile("img\\loadgame.jpg",-87,-80,width+83,height+80);
    readimagefile("img\\backbut.jpg",0,height-150,150,height);
    exitbutton();
    int x,y;
    int temp=1;
    while(temp>0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>width*19/20&&y<height/20)
                exit(0);
            if(x<150&&y>height-150)
            {
                closegraph();
                initMeniu();
            }
            if (x>width/4  && x<width*3/4 && y>height/4 && y<height/2)
            {
                closegraph();
                initMatrice();
                tabla[1][1].timer=120;
                playPVP();
            }
            else if(x>width/4  && x<width*3/4 && y>height/2 && y<height*3/4)
            {
                initMatrice();
                FILE *progres=fopen("fisier.txt","r");
                int poz[101],nr=0;
                closegraph();
                while(!feof(progres))
                {
                    int coord;
                    fscanf(progres,"%d",&coord);
                    cout<<coord<<" ";
                    poz[++nr]=coord;
                }
                tabla[1][1].timer=poz[nr];
                int k=1;
                for(int i=0; i<=9; ++i)
                    for(int j=0; j<=9; ++j)
                        tabla[i][j].player=poz[k],k++;
                fclose(progres);
                playPVP();
            }
        }
    }
}
void initMeniu()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    initwindow(width,height,"",-3,-3);
    cleardevice();
    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\razboi2.jpg",-40,-40,width+40,height+40 );
    //readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\pvp.jpg",-40,-40,width+40,height+40);
    readimagefile("img\\pvp_ai.jpg",-87,-80,width+83,height+80);
    exitbutton();
    int x,y;
    int temp=1;
    while(temp>0)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if(x>width*19/20&&y<height/20)
                exit(0);
            else if (x>width/4  && x<width*3/4 && y>height/4 && y<height/2+100)
            {
                closegraph();
                initpvpmeniu();
            }
            else if(x>width/4  && x<width*3/4 && y>height/2 && y<height*3/4)
            {
                closegraph();
                initMatrice();
                initMeniuBOT();
            }
        }
    }
}
int main()
{
    initCoordonate();
    initMatrice();
    initMeniu();
    cleardevice();
    getch();
    return 0;
}

