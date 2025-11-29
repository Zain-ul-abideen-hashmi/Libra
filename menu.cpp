#include <iostream>
#include <conio.h>     // for _getch()
#include <windows.h>   // for SetConsoleTextAttribute()
#include "menu.h"

using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int runMenu() {
    const int MENU_SIZE = 6;
    string options[MENU_SIZE] = {
        "Start Election",
        "Register Voter",
        "Register Candidate",
        "View Live Results",
        "Save & Load Data",
        "Exit"
    };

    int selected = 0; // current highlighted index

    while (true) {
        system("cls");

        cout << "=== ELECTRONIC VOTING SYSTEM ===\n\n";

        for (int i = 0; i < MENU_SIZE; i++) {

            if (i == selected) {
                setColor(10);  // bright green for highlight
                cout << " > " << options[i] << "\n";
                setColor(7);   // reset color to normal
            } else {
                cout << "   " << options[i] << "\n";
            }
        }

        char key = _getch();

        // Up arrow
        if (key == 72 && selected > 0) {
            selected--;
        }
        // Down arrow
        else if (key == 80 && selected < MENU_SIZE - 1) {
            selected++;
        }
        // Enter key
        else if (key == 13) {
            return selected;  // return index of chosen option
        }
    }
}