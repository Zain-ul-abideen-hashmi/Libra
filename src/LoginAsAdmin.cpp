#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>



bool adminLogin() {
    std::string adminName;
    std::cout << "Enter admin name: ";
    std::cin >> adminName;

    std::string adminNames[] = {"Zain", "Muneeb", "Abdullahi"};
    std::string adminEmails[] = {"junaibhashmi@gmail.com", "muneebahmed2070@gmail.com", "admin3@gmail.com"};

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

    // Use raw string literal for the command
    std::string command = R"(D:/Libra/Scripts/python.exe D:/Libra/Scripts/SendEmail.py )"
                          + matchedEmail + " " + std::to_string(otp);



    system(command.c_str());

    int userOtp;
    std::cout << "Enter OTP sent to your email: ";
    std::cin >> userOtp;

    if (userOtp == otp) {
        std::cout << "Login successful!\n";
        return true;
    } else {
        std::cout << "Incorrect OTP. Access denied.\n";
        return false;
    }
}