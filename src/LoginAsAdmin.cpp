#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../Include/Admin.h"

// We put your logic inside the class scope
bool Admin::login() {
    std::string adminName;
    std::cout << "\n=== ADMIN PORTAL ===\n";
    std::cout << "Enter admin name: ";
    std::cin >> adminName;

    std::string adminNames[] = {"Zain", "Muneeb", "Abdullahi"};
    std::string adminEmails[] = {"junaibhashmi@gmail.com", "junaibhashmi@gmail.com", "admin3@gmail.com"};

    std::string matchedEmail = "";
    for (int i = 0; i < 3; ++i) {
        if (adminName == adminNames[i]) {
            matchedEmail = adminEmails[i];
            break;
        }
    }

    if (matchedEmail == "") {
        std::cout << "Admin not found!\n";
        return false;
    }

    srand(time(0));
    int otp = rand() % 900000 + 100000;

    // Your existing python command logic
    std::string command = R"(D:/Libra/Scripts/python.exe D:/Libra/Scripts/SendEmail.py )"
                          + matchedEmail + " " + std::to_string(otp);

    system(command.c_str());

    int userOtp;
    std::cout << "OTP sent to " << matchedEmail << ".\nEnter OTP: ";
    std::cin >> userOtp;

    if (userOtp == otp) {
        std::cout << "Login successful!\n";
        system("pause"); // Wait for user to see success
        return true;
    } else {
        std::cout << "Incorrect OTP. Access denied.\n";
        system("pause");
        return false;
    }
}