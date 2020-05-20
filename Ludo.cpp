#include "Ludo.h"
#include "team.h"
#include "Position.h"
#include <iostream>
#include <windows.h>
#include <math.h>
#define DiceRow 4*80+30
#define DiceCol 9*80+30
//red=0 purple=4 cyan=1 blue=2 yellow/golden=5 green=3
int  rows = 10, cols = 20;

void Ludo::RefreshStops()
{
    setbkcolor(BLACK);
    setfillstyle(4, 4);	//Red stay
    bar(80, 0, 159, 79);
    setfillstyle(4, 4);
    bar(10, 10, 70, 70);
    setfillstyle(4, 1);	//Blue stay
    bar(160, 9 * 80, 239, 799);
    setfillstyle(4, 1);
    bar(250, 730, 309, 789);

    setfillstyle(4, 2);	//	Green //Stay
    bar(18 * 80, 800, 19 * 80 - 1, 719);
    setfillstyle(4, 2);
    bar(19 * 80 + 10, 9 * 80 + 10, 20 * 80 - 10, 10 * 80 - 10);
    setfillstyle(4, 3);	//cyan Stay
    bar(17 * 80, 0, 18 * 80 - 1, 79);
    setfillstyle(4, 3);
    bar(16 * 80 + 10, 10, 17 * 80 - 10, 70);

    setfillstyle(4, 5);	//Purple Stay
    bar(640, 0, 719, 79);
    setfillstyle(4, 5);
    bar(570, 10, 630, 70);

    setfillstyle(4, 6);	//Yellow Stop
    bar(720, 800, 799, 719);
    setfillstyle(4, 6);
    bar(10 * 80 + 10, 9 * 80 + 10, 11 * 80 - 10, 10 * 80 - 10);
    setfillstyle(SOLID_FILL, WHITE);

}
void Ludo::Init()
{
     bool Solo = false;
     TeamMode = false;
     initwindow(1950, 1000, "Ludo");
     setfillstyle(SOLID_FILL, GREEN);
     bar(0, 0, 159, 79);
     bar(160, 0, 319, 79);
     //setbkcolor(GREEN);
     outtextxy(30, 30, "SOLO MODE");
     outtextxy(190, 30, "TEAM MODE");
     int r, c;
     do
     {
         Select(r, c);
     } while (r != 0 || c >= 4);
     cleardevice();
     if (c < 2)Solo = true;
     if (Solo)
     {
        bar(0, 0, 79, 79);
        bar(80, 0, 159, 79);
        bar(160, 0, 239, 79);
        outtextxy(15, 30, "2 Player");
        outtextxy(15 + 80, 30, "4 Player");
        outtextxy(15 + 160, 30, "6 Player");
        do
        {
            Select(r, c);
        } while (r != 0 || c >= 4);
        setbkcolor(BLACK);
        cleardevice();
        NOP = 2 * (c + 1);
        NOT = NOP;
    }
    else
    {
        NOP = 6;
        NOT = 2;
        TeamMode = true;
    }
    Pl = new Player[NOP];
    if (TeamMode)
    {
        static Team T1(0,4,Pl); //??
        static Team T2(1, 4, Pl + 3);//??
        for (int i = 0; i < 6; i++)
        {
            string N = "Player ";
            char s = '0';
            s += i;
            N += s;
            if (i < 2 || i==4)
                Pl[i].InitPlayer(0, N, &T1);
            else
                Pl[i].InitPlayer(0, N, &T2);

        }
    }
    else
    {
        static Team Ts[6];
        for (int i = 0; i < NOP; i++)
        {
            string N = "Player ";
            char s = '0';
            s += i;
            N += s;
            Ts[i].InitTeam(i, 1, &Pl[i]);
            Pl[i].InitPlayer(i, N, &Ts[i]);
        }
    }
    setfillstyle(SOLID_FILL, WHITE);
    srand(time(0));
    Turn = rand() % NOP;
}

void Ludo::DisplayElipse()
{
    for (int i = 0; i < NOP; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            setcolor(BLUE);
            setfillstyle(SOLID_FILL, LIGHTGRAY);
            fillellipse(Pl[i].Ps[j].EndPosition.c*80 +40, Pl[i].Ps[j].EndPosition.r*80 + 40, 20, 20);
        }
    }
}

void Ludo::InitPeices()
{
    if (TeamMode||NOP==6)
    {
        InitAll();
    }
    else
    {
        switch (NOP)
        {
        case 2:
            InitRed();
            InitCyan();
            break;
        case 4:
            InitRed();
            InitCyan();
            InitBlue();
            InitGreen();
            break;
        }
    }
}
void Ludo::InitAll()
{
    InitRed();
    InitPurple();
    InitCyan();
    InitBlue();
    InitYellow ();
    InitGreen();

}
//20+(id*10)
void Ludo::InitRed() 
{
    Pl[0].Ps[0].InitPiece(&Pl[0], 0, Position(1, 1), Position(0, 20), 1, 0, 20,RED,Pl[0].T->ID);
    Pl[0].Ps[1].InitPiece(&Pl[0], 0, Position(1, 2), Position(0, 21), 1, 0, 20, RED, Pl[0].T->ID);
    Pl[0].Ps[2].InitPiece(&Pl[0], 0, Position(2, 1), Position(0, 22), 1, 0, 20, RED, Pl[0].T->ID);
    Pl[0].Ps[3].InitPiece(&Pl[0], 0, Position(2, 2), Position(0, 23), 1, 0, 20, RED, Pl[0].T->ID);
}
void Ludo::InitPurple()
{
    Pl[4].Ps[0].InitPiece(&Pl[4], 4, Position(1, 8), Position(4, 20), 8,7, 60,MAGENTA, Pl[4].T->ID);
    Pl[4].Ps[1].InitPiece(&Pl[4], 4, Position(1, 9), Position(4, 21), 8, 7, 60, MAGENTA, Pl[4].T->ID);
    Pl[4].Ps[2].InitPiece(&Pl[4], 4, Position(2, 8), Position(4, 22), 8, 7, 60, MAGENTA, Pl[4].T->ID);
    Pl[4].Ps[3].InitPiece(&Pl[4], 4, Position(2, 9), Position(4, 23), 8, 7, 60, MAGENTA, Pl[4].T->ID);
}
void Ludo::InitCyan()
{
    Pl[1].Ps[0].InitPiece(&Pl[1], 1, Position(1, 17), Position(1, 20), 17, 16, 30,CYAN, Pl[1].T->ID);
    Pl[1].Ps[1].InitPiece(&Pl[1], 1, Position(1, 18), Position(1, 21), 17, 16, 30, CYAN, Pl[1].T->ID);
    Pl[1].Ps[2].InitPiece(&Pl[1], 1, Position(2, 17), Position(1, 22), 17, 16, 30, CYAN, Pl[1].T->ID);
    Pl[1].Ps[3].InitPiece(&Pl[1], 1, Position(2, 18), Position(1, 23), 17, 16, 30, CYAN, Pl[1].T->ID);
}
void Ludo::InitBlue()
{
    Pl[2].Ps[3].InitPiece(&Pl[3],2, Position(7, 1), Position(2, 23), 45, 44, 40,BLUE, Pl[2].T->ID);
    Pl[2].Ps[0].InitPiece(&Pl[3],2, Position(8, 1), Position(2, 20), 45, 44, 40, BLUE, Pl[2].T->ID);
    Pl[2].Ps[1].InitPiece(&Pl[3],2, Position(7, 2), Position(2, 21), 45, 44, 40, BLUE, Pl[2].T->ID);
    Pl[2].Ps[2].InitPiece(&Pl[3],2, Position(8, 2), Position(2, 22), 45, 44, 40, BLUE, Pl[2].T->ID);
}
void Ludo::InitYellow()
{
    Pl[5].Ps[0].InitPiece(&Pl[5], 5, Position(7, 8), Position(5, 20), 38, 37, 70,YELLOW, Pl[5].T->ID);
    Pl[5].Ps[1].InitPiece(&Pl[5], 5, Position(8, 8), Position(5, 21), 38, 37, 70, YELLOW, Pl[5].T->ID);
    Pl[5].Ps[2].InitPiece(&Pl[5], 5, Position(7, 9), Position(5, 22), 38, 37, 70, YELLOW, Pl[5].T->ID);
    Pl[5].Ps[3].InitPiece(&Pl[5], 5, Position(8, 9), Position(5, 23), 38, 37, 70, YELLOW, Pl[5].T->ID);
}
void Ludo::InitGreen()
{
    Pl[3].Ps[0].InitPiece(&Pl[3], 3, Position(7, 17), Position(3, 20), 29, 28, 50, GREEN, Pl[3].T->ID);
    Pl[3].Ps[1].InitPiece(&Pl[3], 3, Position(8, 17), Position(3, 21), 29, 28, 50, GREEN, Pl[3].T->ID);
    Pl[3].Ps[2].InitPiece(&Pl[3], 3, Position(7, 18), Position(3, 22), 29, 28, 50, GREEN, Pl[3].T->ID);
    Pl[3].Ps[3].InitPiece(&Pl[3], 3, Position(8, 18), Position(3, 23), 29, 28, 50, GREEN, Pl[3].T->ID);
}
bool Ludo::GameEnd()
{
    int Count=0;
    if (NOT == 2 && NOP == 6)
    {
        if (Pl[0].IsCompleted() && Pl[1].IsCompleted() && Pl[4].IsCompleted()) return true;
        if (Pl[2].IsCompleted() && Pl[3].IsCompleted() && Pl[5].IsCompleted()) return true;
        return false;
    }
    else
    {
        for (int i = 0; i < NOP; i++)
        {
            if (Pl[i].IsCompleted() == true)
                Count++;
        }
        if (Count == NOP - 1)return true;
        return false;
    }
}
int Ludo::RowCol2Index(int r, int c)
{
    if (r == 0 && c == 0) return 0;
    if (r == 0) return c;
    if (c == 19) return 19 + r;
    if (r == 9) return 28 + (19 - c);
    if (c == 0) return 47 + (9 - r);
    cout<<"ERROR IN ROWCOL2INDEX!!";
}
bool Ludo::AnyMovePossible()
{
    for(int i=0;i<D.size;i++)
    {
           for(int x=0;x<4;x++)
           {
                if(Pl[Turn].Ps[x].IsLegalMove(D.Ds[i])) return true;
		   }
    }
    return false;
}

void Ludo::CompletedAll(Player Pl)
{
  //  for (int i=0;i<NOP;i++)
    //{
    int count = 0;
        for (int x = 0; x < 4; x++)
        {
            if (Pl.Ps[x].state == -1)
                count++;
        }
        if (count == 4)
        {
            PlayersCompleted++;
            Pl.Rank = PlayersCompleted;
        }
                                         
    //}
}
void Ludo::TurnChange()
{
    Turn = (Turn + 1) % NOP;     
    if (Pl[Turn].IsCompleted()) TurnChange();
    Beep(2000, 1000);
}
void Ludo::TurnDisplay(int X, int Y)
{

    colors coolor;
    if (Turn == 1)  coolor = CYAN;
    else if (Turn == 0)  coolor = RED;                 ////red=0 purple=4 cyan=1 blue=2 yellow/golden=5 green=3
    else if (Turn == 2)  coolor = BLUE;
    else if (Turn == 3)  coolor = GREEN;
    else if (Turn == 4)  coolor = MAGENTA;
    else if (Turn == 5)  coolor = YELLOW;               // araam
                                                        // ab kiya kerna hai       
    setcolor(15);
    setfillstyle(SOLID_FILL, 15);
    bar(X * 80 - 30, Y * 80 - 30, X * 80 + 100 + 30, Y * 80 + 100 + 30);

    setcolor(coolor);
    setfillstyle(SOLID_FILL, coolor);
    bar(X * 80, Y * 80, X * 80 + 100, Y * 80 + 100);
    setcolor(BLACK);
    setbkcolor(WHITE);
    settextstyle(1, 0, 20);
    outtextxy(X*80 - 10, Y*80 - 20, "TURN");
}

void Ludo::Select(int& R, int& C)
{
    do
    {

    } while (!ismouseclick(WM_LBUTTONDOWN));
    //Beep(532, 200);
    getmouseclick(WM_LBUTTONDOWN, C, R);
    C = C / 80;
    R = R / 80;
}
bool Ludo::IsValidSelection(int R,int C)
{
   
    if (C > 19) return false;
    if (R == 0 || R == 9 || C == 0 || C == 19)
    {
        if (B.Cs[RowCol2Index(R, C)].Size[Turn] > 0)
        {
            for (int i = 0; i < D.size; i++)
                if (B.Cs[RowCol2Index(R, C)].Ps[Turn][0]->IsLegalMove(D.Ds[i])) return true;
        }
    }
    for (int i = 0; i < 4; i++)
    {
        if (Pl[Turn].Ps[i].state == -1 && Pl[Turn].Ps[i].HomePosition == Position(R, C))
        {
            return true;
        }

    }
    //Add condition to check move for particular piece
    return false;
}
bool Ludo::IsValidDestination(int SR,int SC,int ER,int EC)
{
    int bsi = RowCol2Index(SR, SC);
    int bei = RowCol2Index(ER, EC);
    if (bei < bsi) bei += 56;
    int N = bei - bsi;
    bool PID = false;
    for (int i = 0; i < D.size; i++)
    {
        if (N == D.Ds[i]) PID = true;
    }
    if (!PID) return false;
    return B.Cs[bsi].Ps[Turn][0]->IsLegalMove(N);
}
void Ludo::DisplayResult() 
{
    closegraph();
    if (NOP == 6 && NOT == 2)
    {
        if (Pl[0].IsCompleted() && Pl[1].IsCompleted() && Pl[4].IsCompleted()) cout << "TEAM 1 WINS!!";
        else cout << "TEAM 2 WINS!!";
    }
    else
    {
        for (int i = 0; i < NOP; i++)
        {
            cout << Pl[i].name << " Got Position: " << Pl[i].Rank << endl;
        }
    }
    cout <<endl<< "GAME END! Thanks For Playing!!!";
}
void Ludo::DrawPieces()
{
    int in;
    for (int i = 0; i < NOP; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            in = Pl[i].Ps[j].Draw();
            if (in != -1)
            {
                B.Cs[in].Draw();
            }
        }
    }
}
void Ludo::PieceSelection(int &SR, int &SC)
{
    do
    {
        Select(SR, SC);
    } while (!IsValidSelection(SR, SC));
}
void Ludo::DestinationSelection(int SR,int SC,int& ER, int& EC)
{
    do
    {
        Select(ER, EC);
    } while (!IsValidDestination(SR,SC,ER, EC));
}
bool Ludo::IsHomeSelection(int R, int C)
{
    if (R == 0 || R == 9 || C == 0 || C == 19) return false;
    return true;
}
void Ludo::DiceRollCommand(int R, int C)
{
    D.Ds[0] = D.Ds[1] = D.Ds[2] = 0;
    D.UpdateDiceValues(4, 9);
    int r, c;
    do
    {
        Select(r, c);
    } while (r != R || c != C);
}
void Ludo::Play()
{
    int Rank = 1;
    initwindow(1950, 1000, "Ludo");
    Init();
    InitPeices();
    B.Display();      
    DisplayElipse(); //Pugney wali pos pa display shashkay
    D.PrintDiceAt(4, 9);
    int SR, SC, ER, EC;
    bool MoveDone;
   /* DoSomethingCrazy();
    return;*/
    while (!GameEnd())
    {
        TurnDisplay(21, 8);
        DrawPieces();
        DiceRollCommand(5, 9);
        D.RollDice(4, 9,1);
        while (!D.IsEmpty()  && AnyMovePossible())
        {
            MoveDone = false;
            while (!MoveDone)
            {
                PieceSelection(SR, SC);
                if (IsHomeSelection(SR, SC))
                {
                    if (D.HasSix())
                    {
                        Piece* temp = Pl[Turn].PieceWithHomeAt(SR, SC);
                        temp->GetOutOfHome();
                        B.Cs[temp->Home].AddPeice(temp, Turn);

                        D.RemoveNum(6);
                        MoveDone = true;
                        RefreshStops();
                        DrawPieces();
                    }
                }
                else
                {
                    B.Highlight(RowCol2Index(SR, SC), Turn, D);
                    DestinationSelection(SR,SC,ER,EC);
                    B.UnHighlight(RowCol2Index(SR, SC), Turn, D);
                    B.Move(RowCol2Index(SR, SC), RowCol2Index(ER, EC), Turn, D);//??
                    RefreshStops();
                    DrawPieces();
                    MoveDone = true;
                }
            }
            D.UpdateDiceValues(4,9);
        }
        if (Pl[Turn].IsCompleted()) Pl[Turn].Rank = Rank, Rank++;
        TurnChange();
    }
    DisplayResult();
    return;


}
void Ludo::DoSomethingCrazy()
{
    for (int i = 0; i < NOP; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            B.Cs[3].AddPeice(&Pl[i].Ps[j],i);
            Pl[i].Ps[j].DoSomethingCrazy();
        }
    }
    DrawPieces();
    delay(100000000000);
}
