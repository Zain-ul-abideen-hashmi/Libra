#include <iostream>
#include <conio.h>
#include <windows.h>
#include "../Include/menu.h"

using namespace std;

void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int runMenu()
{
    const int MENU_SIZE = 6;
    string options[MENU_SIZE] =
    {
        "Log In as Admin",
        "Log In as Voter",
        "Log In as Candidate",
        "Register as Voter",
        "Register as Candidate",

    };

    int selected = 0;

    while (true)
    {
        system("cls");

        cout << "=== LIBRA ===\n\n";

        for (int i = 0; i < MENU_SIZE; i++) {

            if (i == selected)
            {
                setColor(10);
                cout << " > " << options[i] << "\n";
                setColor(7);
            }
            else
             {
                cout << "   " << options[i] << "\n";
            }
        }

        char key = _getch();

        if (key == 72 && selected > 0)
        {
            selected--;
        }

        else if (key == 80 && selected < MENU_SIZE - 1)
        {
            selected++;
        }

        else if (key == 13)
            {
            return selected;
        }
    }
}