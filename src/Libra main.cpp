#include<iostream>
#include<string>
#include "../Include/menu.h"
#include "../Include/LoginAsAdmin.h"
using namespace std;


int main() {
    int choice=runMenu();

    if(choice == 0)
    {
        adminLogin();
    }


    cin.ignore();
    cin.get(); // added this so program only closes when we click enter instead of closing automatically
    return 0;
}