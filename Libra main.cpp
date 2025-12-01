#include<iostream>
#include<string>
#include"menu.h"
using namespace std;


int main() {
    int choice=runMenu();
    cout<<" you selected option "<<choice<<endl;


    cin.ignore();
    cin.get(); // added this so program only closes when we click enter instead of closing automatically
    return 0;
}