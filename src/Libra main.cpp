#include <iostream>
#include <string>
#include "../Include/menu.h"
#include "../Include/Admin.h"         // Changed from LoginAsAdmin.h
#include "../Include/ElectionSystem.h" // Include logic

using namespace std;

int main()
{
    ElectionSystem system; // system object ceation

    while (true)
    {
        int choice = runMenu(); //menu


        if (choice == 0)
        {
            if (Admin::login())
            {

                system.showAdminMenu();
            }
        }

        else if (choice == 1)
        {
            system.voterLogin();
        }

        else if (choice == 2)
        {
            system.candidateLogin();
        }

        else if (choice == 3)
        {
            system.registerVoter();
        }

        else if (choice == 4)
        {

            system.registerCandidate();
        }
    }

    return 0;
}