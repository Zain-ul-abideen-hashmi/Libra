#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "../Include/Admin.h"
using namespace std;

bool Admin::login()
{
    string adminName;
    cout << "\n=== ADMIN PORTAL ====\n";
    cout << "Enter admin name: ";
    cin >> adminName;

    string adminNames[] = {"Zain", "Muneeb", "Abdullahi"};
    string adminEmails[] = {"junaibhashmi@gmail.com", "junaibhashmi@gmail.com", "admin@gmal.com"};

    string matchedEmail = "";
    for (int i = 0; i < 3; ++i)
    {
        if (adminName == adminNames[i])
        {
            matchedEmail = adminEmails[i];
            break;
        }
    }

    if (matchedEmail == "")
    {
        std::cout << "Admin not found!\n";
        return false;
    }

    srand(time(0));
    int otp = rand() % 900000 + 100000;


    string command = R"(D:/Libra/Scripts/python.exe D:/Libra/Scripts/SendEmail.py )"
                          + matchedEmail + " " + to_string(otp);

    system(command.c_str());

    int userOtp;
    cout << "OTP sent to " << matchedEmail << ".\nEnter OTP: ";
    cin >> userOtp;

    if (userOtp == otp)
    {
        cout << "Login successful!\n";
        system("pause");
        return true;
    } else
    {
        cout << "Incorrect OTP. Access denied.\n";
        system("pause");
        return false;
    }
}