#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <mmsystem.h>
#include <time.h>

#define player1 1
#define player2 2
#define neocupat 0
#define inexistent 3
#define nerecomandat 4

using namespace std;

///FILE *progres=fopen("progres.txt","w+");
//ofstream fout("progres.txt");
/*struct game{

    int player;

    struct board{
        int ocupat;
        int x,y;
        int L,C;
    }tabla[10][10];
}joc;
*/
struct joc
{
    int colour;
    int x,y;///coord piesei de pe linia L si coloana C (coresp A[L][C])
    int L,C;///L=i,C=j in parcurgerea lui A[][]
    int player;/// 1-neagra(circle), 2-alba(fillellipse), 3-spatiu inaccesibil 0-neocupat
    int mutare_ai;/// nerecomandat ptr miscarile cu care AI isi poate bloca singur piesele
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
void patrat(joc tabla[][10])
{
    for(int i=1;i<=8;++i)
        for(int j=1;j<=8;++j)
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
void form_tabla()
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
    readimagefile("theme.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\theme.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\theme.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);

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
            else if (X>686  && X<876 && Y>348 && Y<430)
            {
                temp=0;
                color=RED;
                closegraph();
            }
            else if(X>656  && X<916 && Y>490 && Y<566)
            {
                temp=0;
                color=BLUE;
                closegraph();
            }
            else if(X>607  && X<954 && Y>627 && Y<702)
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
        readimagefile("bk.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bk.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk.jpg",-40,-40,width+40,height+40);

    }
    else if(color==BLUE)
    {
        readimagefile("bk2.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bk2.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk2.jpg",-40,-40,width+40,height+40);
    }
    else if(color==GREEN)
    {
        readimagefile("bkgreen.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\Munteanu\\Desktop\\copieproiect\\bkgreen.jpg",-40,-40,width+40,height+40);
        //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bkgreen.jpg",-40,-40,width+40,height+40);
    }
    exitbutton();

    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\bk.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\bk.jpg",-40,-40,width+40,height+40);
    setbkcolor(color);
    settextstyle(3,HORIZ_DIR,5);
    setcolor(YELLOW);
    outtextxy(width/3-50,height-100,"PLAYER 1: YOUR TURN!");
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

    patrat(tabla);
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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
    form_tabla();

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
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    else if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 8 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:8");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 7 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:7");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 6 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:6");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 5 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:5");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 4 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:4");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 3 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:3");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 2 && nrPiesePlayer2 == 0)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:0");
        outtextxy(width-400, height*3/4, "P1 SCORE:2");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:1");
        outtextxy(width-400, height*3/4, "P1 SCORE:1");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 8)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:8");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 7)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:7");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 6)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:6");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 5)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:5");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 4)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:4");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 3)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:3");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
    }
    if(nrPiesePlayer1 == 0 && nrPiesePlayer2 == 2)
    {
        setcolor(YELLOW);
        outtextxy(100, height/4, "P2 SCORE:2");
        outtextxy(width-400, height*3/4, "P1 SCORE:0");
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
void elimina_piesa(int lin,int col,joc tabla[][10])
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
            return true;///colt stanga jos
        else if(tabla[i-1][j-1].player==player2 && tabla[i+1][j+1].player==player2
                && (tabla[i][j+2].player==player2 ||tabla[i][j+2].player==player1)
                && (tabla[i+2][j].player==player2 || tabla[i+2][j].player==player1) &&
                (tabla[i+2][j+2].player==player2 || tabla[i+2][j+2].player==player1))
            return true;///colt stanga sus
        else if(tabla[i+1][j+1].player==player2 && tabla[i-1][j-1].player==player2
                &&(tabla[i][j-2].player==player2 || tabla[i][j-2].player==player1)
                && (tabla[i-2][j].player==player2 || tabla[i-2][j].player==player1) &&
                (tabla[i-2][j-2].player==player2||tabla[i-2][j-2].player==player1))
            return true;///colt dreapta jos
        else if(tabla[i-1][j+1].player==player2 && tabla[i+1][j-1].player==player2
                &&(tabla[i][j-2].player==player1 || tabla[i][j-2].player==player2)
                && (tabla[i+2][j].player==player1 || tabla[i+2][j].player==player2) &&
                (tabla[i+2][j-2].player==player1 || tabla[i+2][j-2].player==player2))
            return true;///colt dreapta sus
    }
    return false;

}
void verificaCastigator(int nrPiesePlayer1, int nrPiesePlayer2)
{
    if(nrPiesePlayer1 == 0||(nrPiesePlayer1+2<=nrPiesePlayer2&&nrPiesePlayer1==1))///3 piese asigura eliminarea unei piese in cazul 3<=3,nrPiesePlayer1=1 si nrPiesePlayer2=3
    {
        setcolor(YELLOW);
        outtextxy(610,290, "PLAYER 2 WON!");
        delay(2500);
        closegraph();
        initMeniu();
    }
    else if(nrPiesePlayer2 == 0||(nrPiesePlayer2+2<=nrPiesePlayer1&&nrPiesePlayer2==1))
    {
        setcolor(YELLOW);
        outtextxy(610,290, "PLAYER 1 WON!");
        delay(2500);
        closegraph();
        initMeniu();
    }
    else if(nrPiesePlayer1 == 1 && nrPiesePlayer2 == 1)
    {
        setcolor(YELLOW);
        outtextxy(610,290, "DRAW!");
        delay(2500);
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
    settextstyle(3,HORIZ_DIR,5);
    outtextxy(100, height/4, "P2 SCORE:8");
    outtextxy(width-400, height*3/4, "P1 SCORE:8");
    for(int i=0;i<=9;++i)
    {
        cout<<'\n';
        for(int j=0;j<=9;++j)
            cout<<tabla[i][j].player<<" ";
        cout<<'\n';
    }
    int X,Y,time = 2,castigator = 0,rand = 1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8,clickedPlayer = neocupat;///rand stabileste cine trebuie sa mute piesa

    afisareScor(nrPiesePlayer1, nrPiesePlayer2);
    long i = 0;
    clock_t now = 0;                 /* Holds initial clock time  */
    int interval = 1;                /* Seconds interval for o/p  */
    int elapsed = 0;
    int sec=0;
    int d=0,f=0;
    now = clock();
    while(!castigator)
    {
        while(time>0)
        {
            //for(i=0;;++i)
            //{
            elapsed = (clock()-now)/CLOCKS_PER_SEC;

            if(elapsed>=interval)
            {
                interval += 1;
                sec=20-(elapsed-d);
                if(sec<100)
                    outtextxy(50,100,"        ");
                char buffer [50];
                int n=sprintf (buffer, "%d", sec);
                outtextxy(50,50,"TIME");
                outtextxy(50,100,buffer);

            if(20-(elapsed-d)==0)
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
            }}
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
                            int poz[101]={0},nr=0;
                            for(int i=0;i<=9;++i)
                                for(int j=0;j<=9;++j)
                                    {
                                        int coord=tabla[i][j].player;
                                        cout<<coord<<" ";
                                        //poz[++nr]=tabla[i][j].player;
                                        fprintf(progres,"%d ",coord);
                                        //fout<<coord<<" ";
                                    }
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
                                elimina_piesa(L,C,tabla);
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
                            int poz[101]={0},nr=0;
                            for(int i=0;i<=9;++i)
                                for(int j=0;j<=9;++j)
                                    {
                                        int coord=tabla[i][j].player;
                                        cout<<coord<<" ";
                                        //poz[++nr]=tabla[i][j].player;
                                        fprintf(progres,"%d ",coord);
                                        //fout<<coord<<" ";
                                    }
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
                            outtextxy(width/3-50,height-100,"PLAYER 1: YOUR TURN!");
                            outtextxy(width/3-50,20,"PLAYER 2 WAITING...      ");

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
                            outtextxy(width/3-50,20, "PLAYER 2: YOUR TURN!");
                            outtextxy(width/3-50,height-100,"PLAYER 1 WAITING...      ");
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
            if(tabla[i][j].player==player1 && (tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && (tabla[i+1][j+1].player==player2 || tabla[i+1][j+1].player==player1) && tabla[i+1][j-1].player==neocupat)
            {
                if(tabla[i][j-2].player==player2)
                {
                    mutat = 1;
                    mutareDreaptaJOS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i+2][j-2].player == player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i+2,j-2);
                    tabla[i+2][j-2].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
                else if(tabla[i+2][j].player ==player2)
                {
                    mutat = 1;
                    mutareStangaSUS(tabla,i+2,j);
                    tabla[i+2][j].player=neocupat;
                    tabla[i+1][j-1].player=player2;
                    break;
                }
            }
            ///caz 2 - colt DREAPTA JOS
            else if(tabla[i][j].player==player1 && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && (tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && tabla[i+1][j+1].player==neocupat)
            {
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
                if(tabla[i-2][j+2].player == player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
                else if(tabla[i-2][j].player == player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
                else if(tabla[i][j+2].player ==player2)
                {
                    mutat=1;
                    mutareStangaSUS(tabla,i,j+2);
                    tabla[i][j+2].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
            }
            ///caz 4 - colt STANGA SUS
            else if(tabla[i][j].player==player1 && (tabla[i+1][j-1].player==player2 || tabla[i+1][j-1].player==player1) && (tabla[i-1][j+1].player==player2 || tabla[i-1][j+1].player==player1) && (tabla[i+1][j+1].player==player2 || tabla[i+1][j+1].player==player1) && tabla[i-1][j-1].player==neocupat)
            {
                if(tabla[i-2][j-2].player == player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j-2);
                    tabla[i-2][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i-2][j].player == player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
                else if(tabla[i][j-2].player ==player2)
                {
                    mutat=1;
                    mutareDreaptaSUS(tabla,i,j-2);
                    tabla[i][j-2].player=neocupat;
                    tabla[i-1][j-1].player=player2;
                    break;
                }
            }
            ///caz 5 - margine STANGA - SUS
            else if(tabla[i][j].player==player1 && tabla[i][j-1].player==inexistent && tabla[i+1][j-1].player==inexistent && (tabla[i+1][j+1].player==player1||tabla[i+1][j+1].player==player2)&&tabla[i-1][j+1].player==neocupat)
            {
                if(tabla[i-2][j].player==player2)
                {
                    mutat=1;
                    mutareDreaptaJOS(tabla,i-2,j);
                    tabla[i-2][j].player=neocupat;
                    tabla[i-1][j+1].player=player2;
                    break;
                }
                else if(tabla[i-2][j+2].player==player2)
                {
                    mutat=1;
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
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
            ///caz 6 - margine STANGA - JOS
            else if(tabla[i][j].player==player1 && tabla[i][j-1].player==inexistent && tabla[i+1][j-1].player==inexistent && (tabla[i-1][j+1].player==player1||tabla[i-1][j+1].player==player2)&&tabla[i+1][j+1].player==neocupat)
            {
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
            ///caz 9 - margine DREAPTA - JOS
            else if(tabla[i][j].player==player1 && tabla[i][j+1].player==inexistent && tabla[i-1][j+1].player==inexistent &&(tabla[i-1][j-1].player==player2 || tabla[i-1][j-1].player==player1)&&tabla[i+1][j-1].player==neocupat)
            {

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
                    mutareStangaJOS(tabla,i-2,j+2);
                    tabla[i-2][j+2].player=neocupat;
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
            else if(tabla[i][j].player==player1 && tabla[i-1][j-1].player==inexistent &&  tabla[i+1][j+1].player==neocupat)
            {
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
            else if(tabla[i][j].player==player1 && tabla[i+1][j+1].player==inexistent &&  tabla[i-1][j-1].player==neocupat)
            {
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
        }
}
void playAgainstSoldierBOT()
{
    closegraph(CURRENT_WINDOW);
    initJoc();
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    readimagefile("backbut.jpg",-40,-40,width+40,height+40);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.jpg",0,height-150,150,height);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    initCoordonate();
    exitbutton();
    //cleardevice();

    //PLAYER 2 = AI
    setcolor(YELLOW);
    outtextxy(280,580, "P1");
    outtextxy(width/3+60,height/11,"SOLDIER BOT");
    outtextxy(width-500,50,"DIFFICULTY LEVEL:");
    outtextxy(width-500,100,"EASY");
    //outtextxy(width-100, 530, "                                                             ");

    int X,Y,time=2,castigator=0,rand=2, coloanaBot = 2;///rand stabileste cine trebuie sa mute piesa
    int I_ai=2, J_ai = coloanaBot, jCount=1, countMutariInitiale=1, piesaMutata[9]= {0};
    int liniaCurenta = 2,randMutare=1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8, I_intermediar = 3;
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
                    for(int i=1; i<=8; ++i)
                        for(int j=1; j<=8; ++j)
                        {
                            if(tabla[i][j].player==player1)
                                verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                            if(tabla[i][j].player==player2)
                                verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                        }

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
                    for(int i=1; i<=8; ++i)
                        for(int j=1; j<=8; ++j)
                        {
                            if(tabla[i][j].player==player1)
                                verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                            if(tabla[i][j].player==player2)
                                verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                        }

                    if(rand==2)
                    {
                        for(int i=1; i<=8; ++i)
                            for(int j=1; j<=8; ++j)
                            {
                                if(tabla[i][j].player==player1)
                                    verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                                if(tabla[i][j].player==player2)
                                    verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                            }
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

                        delay(800);
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
                            if(mutat==0)
                            {

                                int Col;
                                int oki = 0;
                                while(oki == 0)
                                {
                                    for(int j = 1; j<=8; j++)
                                        if(tabla[I_intermediar][j].player == player2)
                                        {
                                            Col=j;
                                            oki = 1;
                                            break;
                                        }
                                    if(oki == 0)
                                    {
                                        if(I_intermediar == 3 || I_intermediar == 2)
                                            I_intermediar--;
                                        else if(I_intermediar == 1)
                                            I_intermediar = 4;
                                        else if(I_intermediar == 8)
                                            I_intermediar = 3;
                                        else I_intermediar++;
                                    }

                                }


                                if(tabla[I_intermediar+1][Col+1].player == neocupat && tabla[I_intermediar][Col].player==player2 && verificaPericol(tabla, I_intermediar+1,Col+1)==false)
                                {
                                    mutareDreaptaJOS(tabla,I_intermediar,Col);
                                    tabla[I_intermediar][Col].player=neocupat;
                                    tabla[I_intermediar+1][Col+1].player=player2;
                                }
                                else if(tabla[I_intermediar+1][Col-1].player == neocupat && tabla[I_intermediar][Col].player==player2 && verificaPericol(tabla, I_intermediar+1, Col-1)==false)
                                {
                                    mutareStangaJOS(tabla,I_intermediar,Col);
                                    tabla[I_intermediar][Col].player=neocupat;
                                    tabla[I_intermediar+1][Col-1].player=player2;
                                }
                                else if(tabla[I_intermediar-1][Col+1].player == neocupat && tabla[I_intermediar][Col].player==player2 && verificaPericol(tabla, I_intermediar-1, Col+1)==false)
                                {
                                    mutareDreaptaSUS(tabla,I_intermediar,Col);
                                    tabla[I_intermediar][Col].player=neocupat;
                                    tabla[I_intermediar-1][Col+1].player=player2;
                                }
                                else if(tabla[I_intermediar-1][Col-1].player == neocupat && tabla[I_intermediar][Col].player==player2 || verificaPericol(tabla, I_intermediar-1, Col-1)==false)
                                {
                                    mutareStangaSUS(tabla,I_intermediar,Col);
                                    tabla[I_intermediar][Col].player=neocupat;
                                    tabla[I_intermediar-1][Col-1].player=player2;
                                }

                                cout<<endl;
                                cout<<"I INTERMEDIAR: "<<I_intermediar<<"\n";
                            }

                        }




                        /*if(tabla[I_ai+1][J_ai+1].player == neocupat)
                        {
                            mutareDreaptaJOS(tabla,I_ai,J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai++;
                            J_ai++;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai+1][J_ai-1].player == neocupat)
                        {
                            mutareStangaJOS(tabla,I_ai, J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai++;
                            J_ai--;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai-1][J_ai-1].player == neocupat)
                        {
                            mutareStangaSUS(tabla,I_ai, J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai--;
                            J_ai--;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai-1][J_ai+1].player == neocupat)
                        {
                            mutareDreaptaSUS(tabla,I_ai,J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai--;
                            J_ai++;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        if(liniaCurenta == 2)
                        {
                            if(J_ai != 8)
                            {
                                if(jCount == 3)
                                {
                                    I_ai = 2;
                                    coloanaBot += 2;
                                    J_ai = coloanaBot;
                                    jCount = 1;

                                }
                            }
                            if(J_ai == 8)
                            {
                                liniaCurenta = 1;
                                coloanaBot = 1;
                                J_ai = 1;
                                I_ai = 1;
                            }
                        }
                        else
                        {

                            if(jCount == 3 && J_ai != 7)
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

                        /*for(int i=1;i<=8;++i)
                        {
                            for(int j=1;j<=8;++j)
                                cout<<tabla[i][j].player<<" ";
                            cout<<'\n';
                        }
                        */
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


void playAgainstHitlerBOT()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);

    closegraph(CURRENT_WINDOW);
    initJoc();
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\hitler.jpg",575,110,200, 500);
    ///readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    ///readimagefile("C:\\Users\\Munteanu\\Desktop\\copie proiect\\backbut.jpg",0,height-150,150,height);
    readimagefile("backbut.jpg",-40,-40,width+40,height+40);
    initCoordonate();
    //cleardevice();

    //PLAYER 2 = AI
    setcolor(YELLOW);
    outtextxy(280,580, "P1");
    outtextxy(width/3+60,height/11,"HITLER BOT");
    outtextxy(width-500,height/11,"DIFFICULTY LEVEL:");
    outtextxy(width-500,height/11+50,"HARD");
    int X,Y,time=2,castigator=0,rand=2, coloanaBot = 2;///rand stabileste cine trebuie sa mute piesa
    int I_ai=2, J_ai = coloanaBot, jCount=1, countMutariInitiale=1, piesaMutata[9]= {0};
    int liniaCurenta = 2,randMutare=1, nrPiesePlayer1 = 8, nrPiesePlayer2 = 8, I_intermediar = 3;
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
                    for(int i=1; i<=8; ++i)
                        for(int j=1; j<=8; ++j)
                        {
                            if(tabla[i][j].player==player1)
                                verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                            if(tabla[i][j].player==player2)
                                verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                        }

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
                    for(int i=1; i<=8; ++i)
                        for(int j=1; j<=8; ++j)
                        {
                            if(tabla[i][j].player==player1)
                                verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                            if(tabla[i][j].player==player2)
                                verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                        }

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
                        for(int i=1; i<=8; ++i)
                            for(int j=1; j<=8; ++j)
                            {
                                if(tabla[i][j].player==player1)
                                    verificaStergereALB(i,j,tabla,nrPiesePlayer1);
                                if(tabla[i][j].player==player2)
                                    verificaStergereNEGRU(i,j,tabla,nrPiesePlayer2);
                            }
                        if(tabla[L][C].player==neocupat)
                        {
                            setcolor(WHITE);
                            setfillstyle(1,WHITE);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                            tabla[L][C].player=player1;
                            tabla[L1][C1].player=neocupat;
                        }
                        if(tabla[I_ai+1][J_ai+1].player == neocupat)
                        {
                            delay(300);
                            mutareDreaptaJOS(tabla,I_ai,J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai++;
                            J_ai++;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai+1][J_ai-1].player == neocupat)
                        {
                            delay(300);
                            mutareStangaJOS(tabla,I_ai, J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai++;
                            J_ai--;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai-1][J_ai-1].player == neocupat)
                        {
                            delay(300);
                            mutareStangaSUS(tabla,I_ai, J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai--;
                            J_ai--;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        else if(tabla[I_ai-1][J_ai+1].player == neocupat)
                        {
                            delay(300);
                            mutareDreaptaSUS(tabla,I_ai,J_ai);
                            tabla[I_ai][J_ai].player=neocupat;
                            I_ai--;
                            J_ai++;
                            tabla[I_ai][J_ai].player=player2;
                            jCount++;
                        }
                        if(liniaCurenta == 2)
                        {
                            if(J_ai != 8)
                            {
                                if(jCount == 3)
                                {
                                    I_ai = 2;
                                    coloanaBot += 2;
                                    J_ai = coloanaBot;
                                    jCount = 1;

                                }
                            }
                            if(J_ai == 8)
                            {
                                liniaCurenta = 1;
                                coloanaBot = 1;
                                J_ai = 1;
                                I_ai = 1;
                            }
                        }
                        else
                        {

                            if(jCount == 3 && J_ai != 7)
                            {
                                I_ai = 1;
                                coloanaBot+=2;
                                J_ai = coloanaBot;
                                jCount = 1;

                            }
                            cout<<endl;
                            cout<<jCount<<'\n';
                        }
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
void initMeniuBOT()
{
    int width=GetSystemMetrics(SM_CXSCREEN);
    int height=GetSystemMetrics(SM_CYSCREEN);
    initwindow(width,height,"",-3,-3);
    cleardevice();

    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\difficulty.jpg",-40,-40,width+40,height+40);
    //readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\backbut.jpg",0,height-150,150,height);
    readimagefile("ai.jpg",-40,-40,width+40,height+40);
    readimagefile("backbut.jpg",-40,-40,width+40,height+40);
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

    readimagefile("load game.jpg",-40,-40,width+40,height+40);
    readimagefile("backbut.jpg",-40,-40,width+40,height+40);
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
                playPVP();
            }
            else if(x>width/4  && x<width*3/4 && y>height/2 && y<height*3/4)
            {
                initMatrice();
                FILE *progres=fopen("D:\\proiectcopy\\fisier.txt","r");
                int poz[101],nr=0;
                closegraph();
                while(!feof(progres))
                {
                    int coord;
                    fscanf(progres,"%d",&coord);
                    cout<<coord<<" ";
                    poz[++nr]=coord;
                }
                int k=1;
                for(int i=0;i<=9;++i)
                    for(int j=0;j<=9;++j)
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
    readimagefile("pvp.jpg",-40,-40,width+40,height+40);
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

