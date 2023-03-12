// winRegistry.cpp : This file contains the 'main' function. Program execution begins and ends there.
// created by Sai Venu Kiran Bolla
//

#include <iostream>
#include "registry.h"
#include <string.h>

using namespace std;

const wstring registry_location = L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion";
const wstring registry_location2 = L"SOFTWARE\\TestReg";


void getReg(registry& reg, wstring key, wstring value) {
    if (!reg.get(key, value))
        cout << "Unable to access to registry. You probably don't have the required rights.\n";
    else 
        wcout << key << ": " << value << endl;
}

void putReg(registry& reg, wstring key, wstring value) {
    if (!reg.put(key, value))
        cout << "Unable to access to registry. You probably don't have the required rights.\n";
    else
        wcout << key << ": " << value << endl;
}

int main()
{
    cout << "Program execution started!\n";

    //create obj for registry
    registry reg(registry::local_machine, registry_location, KEY_READ | KEY_WRITE);
    registry reg2(registry::local_machine, registry_location2, KEY_READ | KEY_WRITE);

    //attributes
    wstring ProductName, CurrentBuild, DisplayVersion, CurrentVersion;

    //get reistry value
    getReg(reg, L"ProductName", ProductName);
    getReg(reg, L"CurrentBuild", CurrentBuild);
    getReg(reg, L"DisplayVersion", DisplayVersion);
    getReg(reg, L"CurrentVersion", CurrentVersion);

    //create registry entry
    putReg(reg2, ProductName, L"winReg");

    cout << "Program execution ended!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
