#include <iostream>
#include <string>
#include "../Include/menu.h"
#include "../Include/Admin.h"         // Changed from LoginAsAdmin.h
#include "../Include/ElectionSystem.h" // Include logic

using namespace std;

int main() {
    ElectionSystem system; // Create the system object

    while (true) {
        int choice = runMenu(); // Your graphical menu

        // 0: Admin Login
        if (choice == 0) {
            if (Admin::login()) {
                // If login true, show admin specific features
                system.showAdminMenu();
            }
        }
        // 1: Log In as Voter
        else if (choice == 1) {
            system.voterLogin();
        }
        // 2: Log In as Candidate (Optional logic)
        else if (choice == 2) {
            cout << "Candidate Login feature coming soon...\n";
            cin.ignore(); cin.get();
        }
        // 3: Register as Voter
        else if (choice == 3) {
            system.registerVoter();
        }
        // 4: Register as Candidate
        else if (choice == 4) {
            // Usually only Admins register candidates, but per menu:
            system.registerCandidate();
        }
    }

    return 0;
}