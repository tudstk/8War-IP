#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <cmath>

#define player1 1
#define player2 2
#define neocupat 0
#define inexistent 3

using namespace std;


void patrat(int a,int b, int c,int d)
{
    ///a left, b top, c right, d bottom
    if(abs(a-c)>70&&abs(b-d)>70)
    {
        //rectangle(a,(b+d)/2,(a+c)/2,d);
        //rectangle((a+c)/2,b,c,(b+d)/2);
        patrat(a,(b+d)/2,(a+c)/2,d);
        patrat((a+c)/2,b,c,(b+d)/2);
        patrat(a,b,(a+c)/2,(b+d)/2);
        patrat((a+c)/2,(b+d)/2,c,d);
    }
    if(a==30&&c==165)
    {
        setcolor(BLACK);
        setfillstyle(1,BLACK);
        fillellipse(((b+d)/2+b)/2,((a+c)/2+a)/2,20,20);
        fillellipse(((b+d)/2+d)/2,((a+c)/2+c)/2,20,20);
        //circle(((b+d)/2+b)/2,((a+c)/2+a)/2,20);
        //circle(((b+d)/2+d)/2,((a+c)/2+c)/2,20);
    }
    if(a==435&&c==570)
    {
        setcolor(WHITE);
        setfillstyle(1,WHITE);
        fillellipse(((b+d)/2+b)/2,((a+c)/2+a)/2,20,20);
        fillellipse(((b+d)/2+d)/2,((a+c)/2+c)/2,20,20);
    }
}
void form_tabla()
{
    int i,j,k=0,poly[8],l,m=0;
    double x=68;
    double y=68;
    for(i=30,k+=y;m<8;i+=y,m++)
        for(j=30,l=0;l<8;j+=x,l++)
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
    setcolor(WHITE);
    rectangle(30,30,574,574);
}
struct joc
{

    int x,y;///coord piesei de pe linia L si coloana C (coresp A[L][C])
    int L,C;///L=i,C=j in parcurgerea lui A[][]
    int player;/// 1-neagra(circle), 2-alba(fillellipse), 3-spatiu inaccesibil

} tabla[10][10];

void initCoordonate()
{
    tabla[1][1].x = 63;
    tabla[1][1].y = 63;
    for(int j=2; j<=8; j++)
    {
        tabla[1][j].x = tabla[1][j-1].x + 68;
        tabla[1][j].y = 63;
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
void initJoc()
{
    initwindow(600,600);
    setbkcolor(RED);
    cleardevice();
    setcolor(WHITE);
    rectangle(30,30,570,570);
    int i,j,k=0,poly[8],l,m=0;
    double x=68;
    double y=68;
    for(i=30,k+=y;m<8;i+=y,m++)
        for(j=30,l=0;l<8;j+=x,l++)
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
               setcolor(RED);
               setfillstyle(1,RED);
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
    setcolor(WHITE);
    rectangle(30,30,574,574);
    patrat(30,30,570,570);
}
void mutareDreaptaJOS(joc tabla[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    form_tabla();

    setcolor(BLACK);

    circle(X+34,Y+34,20);
    setfillstyle(1,BLACK);
    fillellipse(X+34,Y+34,20,20);

    delay(400);

    setcolor(RED);
    setfillstyle(1,RED);
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

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    form_tabla();

    setcolor(BLACK);

    circle(X+34,Y-34,20);
    setfillstyle(1,BLACK);
    fillellipse(X+34,Y-34,20,20);

    delay(400);

    setcolor(RED);
    setfillstyle(1,RED);
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
void mutareStangaJOS(joc A[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    form_tabla();

    setcolor(BLACK);

    circle(X-34,Y+34,20);
    setfillstyle(1,BLACK);
    fillellipse(X-34,Y+34,20,20);

    delay(400);

    setcolor(RED);
    setfillstyle(1,RED);
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
void mutareStangaSUS(joc A[][10], int i, int j)
{
    int X = tabla[i][j].x;
    int Y = tabla[i][j].y;

    //stergere

    setcolor(RED);
    setfillstyle(1,RED);
    fillellipse(X,Y,30,30);

    //semimutare

    setcolor(WHITE);
    form_tabla();

    setcolor(BLACK);

    circle(X-34,Y-34,20);
    setfillstyle(1,BLACK);
    fillellipse(X-34,Y-34,20,20);

    delay(400);

    setcolor(RED);
    setfillstyle(1,RED);
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
void initMeniu()
{
    initwindow(595,380);
    cleardevice();
    readimagefile("C:\\Users\\tudor\\OneDrive\\Desktop\\info\\test\\razboi2.jpg",-40,-40,630,420 );
    int x,y;
    int temp=1;
    while(temp>0){
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            if (x>175  && x<400 && y>150 && y<200){
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
                        int L1,C1;
                        if(time==2)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
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
                            cout<<L<<" "<<C<<"\n";
                            setcolor(RED);
                            setfillstyle(1,RED);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,30,30);
                            L1=L;C1=C;

                        }
                        if(time==1)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
                            for(int i=1; i<=8; ++i)
                                for(int j=1; j<=8; ++j)
                                    if(tabla[i][j].player!=inexistent)
                                        if(abs(X-tabla[i][j].x)<vminx&&abs(Y-tabla[i][j].y)<vminy)
                                        {
                                            vminx=abs(X-tabla[i][j].x);
                                            vminy=abs(Y-tabla[i][j].y);
                                            L=i;
                                            C=j;
                                        }
                            cout<<L<<" "<<C<<"\n";
                            if(rand==1)
                            {
                                setcolor(YELLOW);
                                outtextxy(227,580, "PLAYER 1: YOUR TURN!");

                                if(L>L1)
                                    L=L1+1;
                                else
                                    L=L1-1;
                                if(C1>C)
                                    C=C1-1;
                                else
                                    C=C1+1;
                                setcolor(BLACK);
                                setfillstyle(1,BLACK);
                                fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                                tabla[L][C].player=player2;
                                tabla[L1][C1].player=neocupat;
                            }
                            if(rand==2)
                            {
                                setcolor(YELLOW);
                                outtextxy(227,580, "PLAYER 2: YOUR TURN!");

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
                                    setcolor(WHITE);
                                    setfillstyle(1,WHITE);
                                    fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                                    tabla[L][C].player=player1;
                                    tabla[L1][C1].player=neocupat;
                                }
                                /*for(int i=1;i<=8;++i)
                                {
                                    for(int j=1;j<=8;++j)
                                        cout<<tabla[i][j].player<<" ";
                                    cout<<'\n';
                                }
                                */
                            }
                            if(rand==1)
                                rand=2;
                            else if(rand==2)
                                rand=1;
                        }
                        time--;
                    }
                }
                for(int i=1;i<=8;++i)
                    for(int j=1;j<=8;++j)
                        {if(tabla[i][j].player==player1)
                        {
                            if(i!=8)
                            {
                                if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                                    &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                                        &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                                            &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
                                        {
                                            tabla[i][j].player=neocupat;
                                            setcolor(RED);
                                            setfillstyle(1,RED);
                                            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);

                                        }
                            }
                            else if(i==8)
                                if((tabla[i-1][j+1].player==player2&&tabla[i-1][j-1].player!=neocupat)
                                   ||(tabla[i-1][j+1].player!=neocupat&&tabla[i-1][j-1].player==player2))
                                {
                                    tabla[i][j].player=neocupat;
                                    setcolor(RED);
                                    setfillstyle(1,RED);
                                    fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
                                }
                        }
                        if(tabla[i][j].player==player2)
                            {
                            if(i!=1)
                            {
                                if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                                    &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                                        &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                                            &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
                                        {
                                            tabla[i][j].player = neocupat;
                                            setcolor(RED);
                                            setfillstyle(1,RED);
                                            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);

                                        }
                            }
                            else if(i==1)
                                if((tabla[i+1][j+1].player==player1&&tabla[i+1][j-1].player!=neocupat)
                                   ||(tabla[i+1][j+1].player!=neocupat&&tabla[i+1][j-1].player==player1))
                                {
                                    tabla[i][j].player=neocupat;
                                    setcolor(RED);
                                    setfillstyle(1,RED);
                                    fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
                                }
                        }
                    }

                time=2;
            }

        }


            ///BOT

            else if(x>145  && x<408 && y>250 && y<300)
            {
                closegraph(CURRENT_WINDOW);
                initJoc();
                initCoordonate();
                //PLAYER 2 = AI

                    int X,Y,time=2,castigator=0,rand=2;///rand stabileste cine trebuie sa mute piesa
                    int I_ai=2, J_ai=4, randMutare=1;
            while(!castigator)
            {
                while(time>0)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int L1,C1;
                        if(time==2)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
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
                            cout<<L<<" "<<C<<"\n";
                            setcolor(RED);
                            setfillstyle(1,RED);
                            fillellipse(tabla[L][C].x,tabla[L][C].y,30,30);
                            L1=L;C1=C;
                            outtextxy(277,580, "YOUR TURN!");

                        }
                        if(time==1)
                        {
                            getmouseclick(WM_LBUTTONDOWN, X, Y);
                            cout<<X<<" "<<Y<<'\n';
                            int vminx=100,vminy=100,L=0,C=0;
                            for(int i=1; i<=8; ++i)
                                for(int j=1; j<=8; ++j)
                                    if(tabla[i][j].player!=inexistent)
                                        if(abs(X-tabla[i][j].x)<vminx&&abs(Y-tabla[i][j].y)<vminy)
                                        {
                                            vminx=abs(X-tabla[i][j].x);
                                            vminy=abs(Y-tabla[i][j].y);
                                            L=i;
                                            C=j;
                                        }
                            cout<<L<<" "<<C<<"\n";

                            if(rand==2)
                            {
                                ///strategie AI

                                /*for(int i=1;i<=7;i++)
                                {
                                    if(tabla[i][C].player == player2)
                                    {
                                        if(tabla[i+1][C-1].player == neocupat){
                                            mutareStangaJOS(tabla,i,C);
                                            break;
                                        }
                                        else if(tabla[i+1][C+1].player == neocupat)
                                        {
                                            mutareDreaptaJOS(tabla,i,C);
                                            break;
                                        }
                                    }
                                    else{

                                        while()
                                        {

                                        }
                                    }
                                }
                                */


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
                                    setcolor(WHITE);
                                    setfillstyle(1,WHITE);
                                    fillellipse(tabla[L][C].x,tabla[L][C].y,20,20);
                                    tabla[L][C].player=player1;
                                    tabla[L1][C1].player=neocupat;
                                }

                                setcolor(YELLOW);

                                delay(800);

                                if(tabla[I_ai+1][J_ai+1].player == neocupat){
                                    mutareDreaptaJOS(tabla,I_ai,J_ai);
                                    tabla[I_ai][J_ai].player=neocupat;
                                    I_ai++;
                                    J_ai++;
                                    tabla[I_ai][J_ai].player=player1;
                                }
                                else if(tabla[I_ai+1][J_ai-1].player == neocupat){
                                    mutareStangaJOS(tabla,I_ai, J_ai);
                                    tabla[I_ai][J_ai].player=neocupat;
                                    I_ai++;
                                    J_ai--;
                                    tabla[I_ai][J_ai].player=player1;
                                }
                                else if(tabla[I_ai-1][J_ai-1].player == neocupat)
                                {
                                    mutareStangaSUS(tabla,I_ai, J_ai);
                                    tabla[I_ai][J_ai].player=neocupat;
                                    I_ai--;
                                    J_ai--;
                                    tabla[I_ai][J_ai].player=player1;
                                }
                                else if(tabla[I_ai-1][J_ai+1].player == neocupat)
                                {
                                    mutareDreaptaSUS(tabla,I_ai,J_ai);
                                    tabla[I_ai][J_ai].player=neocupat;
                                    I_ai--;
                                    J_ai++;
                                    tabla[I_ai][J_ai].player=player1;
                                }

                                /*for(int i=1;i<=8;++i)
                                {
                                    for(int j=1;j<=8;++j)
                                        cout<<tabla[i][j].player<<" ";
                                    cout<<'\n';
                                }
                                */
                            }
                        }
                        time--;
                    }


                }
                time = 2;
                /*int I = 2, J = 2;
                delay(800);
                if(tabla[I+1][J+1].player == neocupat)
                    mutareDreapta(tabla,I,J);
                delay(800);
                int I2 = I+1, J2 = J+1;
                if(tabla[I2+1][J2-1].player == neocupat)
                    mutareStanga(tabla,I2,J2);
                    */
                for(int i=1;i<=8;++i)
                    for(int j=1;j<=8;++j)
                        {if(tabla[i][j].player==player1)
                        {
                            if(i!=8)
                            {
                                if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                                    &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                                        &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                                            &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
                                        {
                                            tabla[i][j].player=neocupat;
                                            setcolor(RED);
                                            setfillstyle(1,RED);
                                            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);

                                        }
                            }
                            else if(i==8)
                                if((tabla[i-1][j+1].player==player2&&tabla[i-1][j-1].player!=neocupat)
                                   ||(tabla[i-1][j+1].player!=neocupat&&tabla[i-1][j-1].player==player2))
                                {
                                    tabla[i][j].player=neocupat;
                                    setcolor(RED);
                                    setfillstyle(1,RED);
                                    fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
                                }
                        }
                        if(tabla[i][j].player==player2)
                            {
                            if(i!=1)
                            {
                                if(((tabla[i-1][j-1].player==player2||tabla[i-1][j-1].player==inexistent)||tabla[i-1][j-1].player==player1)
                                    &&((tabla[i+1][j-1].player==player2||tabla[i+1][j-1].player==inexistent)||tabla[i+1][j-1].player==player1)
                                        &&((tabla[i+1][j+1].player==player2||tabla[i+1][j+1].player==inexistent)||tabla[i+1][j+1].player==player1)
                                            &&((tabla[i-1][j+1].player==player2||tabla[i-1][j+1].player==inexistent)||tabla[i-1][j+1].player==player1))
                                        {
                                            tabla[i][j].player=neocupat;
                                            setcolor(RED);
                                            setfillstyle(1,RED);
                                            fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);

                                        }
                            }
                            else if(i==1)
                                if((tabla[i+1][j+1].player==player1&&tabla[i+1][j-1].player!=neocupat)
                                    ||(tabla[i+1][j+1].player!=neocupat&&tabla[i+1][j-1].player==player1))
                                {
                                    tabla[i][j].player=neocupat;
                                    setcolor(RED);
                                    setfillstyle(1,RED);
                                    fillellipse(tabla[i][j].x,tabla[i][j].y,30,30);
                                }
                        }
                    }
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
                tabla[i][j].player=inexistent;///noteaza cu 3 locatiile in  care nu pot ajunge piesele
            else tabla[i][j].player=neocupat;///noteaza cu 0 potentialele locatii in care pot ajunge piesele
        }
//   A[]
    for(int j=1; j<=8; j+=2)
    {
        tabla[1][j].player=tabla[2][j+1].player=player2;
        tabla[7][j].player=tabla[8][j+1].player=player1;
    }
    for(int i=0;i<=9;++i) ///afisarea matricii din spatele jocului
    {
        for(int j=0;j<=9;++j)
            cout<<tabla[i][j].player<<" ";
        cout<<'\n';
    }

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

