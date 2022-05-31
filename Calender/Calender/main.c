#define _CRT_SECURE_NO_WARNINGS


#include<stdio.h>
#include<conio.h>
#include<windows.h>

int getkey();
void display(int, int, int, int[]);
void calendar(int, int);


// GOTO function definition

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// Change the color

//------------ Change color -------------------
void SetColor(int ForgC)
{
    WORD wColor;
    //We will need this handle to get the current background attribute
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    //We use csbi for the wAttributes word.
    if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
    {
        //Mask out all but the background attribute, and add in the forgournd color
        wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
        SetConsoleTextAttribute(hStdOut, wColor);
    }
    return;
}

char* month[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
char* week[] = { "Mon","Tue","Wed","Thu","Fri","Sat","Sun" };


int main() {

    int nmonth, nyear, ch;
enteryear:
    while (1) {
        printf("\nEnter year and month(number) : ");
        scanf("%d %d", &nyear, &nmonth);

        if (nyear < 1900) {
            printf("Please enter a year above 1900 \n");
            continue;
        }
        else {
            calendar(nyear,nmonth);
        }
        while (1) {
            gotoxy(20, 20); printf("(*) Use LEFT, RIGHT, UP and DOWN arrow.");
            gotoxy(20, 22); printf("(*) Press P to go to particular year and month.");
            gotoxy(20, 24); printf("(*) Press ESC to Exit.");
            ch = getkey();
            switch (ch)
            {
            case 80: //-------- DOWN ARROW -----------
                   //Increasing month
                if (nmonth == 12)
                {
                    //Jump to next year if month is december
                    nmonth = 1;
                    nyear++;
                }
                else
                {
                    nmonth++;
                }
                calendar(nyear, nmonth);
                break;
            case 77: //-------- RIGHT ARROW ----------
                //Increasing Year
                nyear++;
                calendar(nyear, nmonth);
                break;
            case 72: //------- UP ARROW -------------
                // Decreasing Month
                if (nmonth == 1)
                {
                    // Jump to previous year if month is january
                    if (nyear == 1900) {
                        //If year is 1945 and we click left arrow than
                        gotoxy(15, 2); printf("Year below 1900 not available");
                    }
                    else {
                        nyear--;
                        nmonth = 12;
                    }
                    
                }
                else
                    nmonth--;
                calendar(nyear, nmonth);
                break;
            case 75: //-------- LEFT ARROW ----------
                //Decreasing year
                if (nyear == 1900)
                {
                    //If year is 1945 and we click left arrow than
                    gotoxy(15, 2); printf("Year below 1900 not available");
                }
                else
                {
                    nyear--;
                    calendar(nyear, nmonth);
                }

                break;
            case 27: //--------- ESC KEY ------------
                //Exit program
                system("cls");
                gotoxy(50, 14); printf("Exiting program.\n\n\n\n\n");
                exit(0);
            case 112://---------- p KEY ------------
                //Go to particular year and month
                system("cls");
                goto enteryear;
            }
        }
        break;

    }
    _getch();
    return 0;
}



//==============  ARROW KEY ===============
int getkey()
{
    int ch;
    ch = _getch();
    if (ch == 0)
    {
        printf("zero");
        ch = _getch();

        return ch;
    }
    return ch;
}

void calendar(int nyear, int nmonth) {
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    int tdays = 0, myear;
    myear = nyear - 1;
    int i;

    for (i = 1900; i <= myear; i++) {
        if (i % 4 == 0) {   // if i is a leap year, we have 366 days in a year.
            tdays += 366;
        }
        else {  // if i is NOT a leap year, we have 365 days in a year.
            tdays += 365;
        }
    }

    if (nyear % 4 == 0) {   //in a leap year, there are 29 days in february
        days[1] = 29;
    }
    else {  // it is not leap year, so there are 29 days in february
        days[1] = 28;
    }

    for (i = 0; i < nmonth - 1; i++) {
        tdays += days[i];
    }
    tdays = tdays % 7;

    display(nyear, nmonth, tdays, days);
}

void display(int nyear, int nmonth, int tdays, int days[]) {
    int i, j, pos;
    SetColor(12);   // Color Red
    gotoxy(56, 6); printf("%s %d", month[nmonth - 1], nyear);   //heading year and month displaying 

    for (i = 0, pos = 30; i < 7; i++, pos += 10) {
        if (i == 6) {
            SetColor(9);    //Sunday color blue
        }
        else {
            SetColor(10);   //Other days color green
        }
        gotoxy(pos, 8); printf("%s", week[i]);
    }

    SetColor(15);   //setting the color white

    tdays++; //incrementing the tdays by 1
    if (tdays == 0 || tdays == 7)
        pos = 91; //if tdays is 0 or 7, position is sunday
    if (tdays == 1)
        pos = 31; //if tdays is 1, position is monday
    if (tdays == 2)
        pos = 41;  //if tdays is 2, position is tuesday
    if (tdays == 3)
        pos = 51;  //if tdays is 3, position is wednesday
    if (tdays == 4)
        pos = 61;  //if tdays is 4, position is thursday
    if (tdays == 5)
        pos = 71;  //if tdays is 5, position is friday
    if (tdays == 6)
        pos = 81;  //if tdays is 6, position is saturday

    for (i = 0, j = 10, pos; i < days[nmonth - 1]; i++, pos += 10) {
        if (pos == 91) {
            SetColor(8);    // Changing color to dark grey for sunday
        }
        else {
            SetColor(7);    //Changing color to white for all days
        }
        gotoxy(pos, j); printf("%d", i + 1);
        if (pos == 91) {
            pos = 21;   // moving position to monday
            j++;    //Increasing j by 10 if position is sunday
        }
    }
    SetColor(5);    //Changing color to purple

    //drawing horizontal line
    for (i = 22; i < 102; i++) {
        gotoxy(i, 4); printf("%c", 196);
        gotoxy(i, 17); printf("%c", 196);
    }

    //Drawing all the corner of the rectangle
    gotoxy(21, 4); printf("%c", 218);
    gotoxy(102, 4); printf("%c", 191);
    gotoxy(21, 17); printf("%c", 192);
    gotoxy(102, 17); printf("%c", 217);

    //Drawing vertical line
    for (i = 5; i < 17; i++) {
        gotoxy(21, i); printf("%c", 179);
        gotoxy(102, i); printf("%c", 179);
    }

    SetColor(11);   //Changing color to aqua

    //Drawing left and the right navigation symbol
    gotoxy(24, 11); printf("%c", 174);
    gotoxy(98, 11); printf("%c", 175);
}


