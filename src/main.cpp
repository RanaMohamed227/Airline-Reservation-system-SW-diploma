#include "inc/systemmanager.hpp"
#include "inc/admin.hpp"
#include "inc/bookingagent.hpp"
#include "inc/passenger.hpp"
#include "inc/menu.hpp"
#include <iostream>
#include <limits>

using namespace std;

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*
// Forward declarations
void adminMenu(SystemManager &system, shared_ptr<Admin> admin);
void agentMenu(SystemManager &system, shared_ptr<BookingAgent> agent);
void passengerMenu(SystemManager &system, shared_ptr<Passenger> passenger);
*/
int main()
{
    SystemManager system;
    menu menucli;

    cout << "========================================" << endl;
    cout << "  Airline Reservation Management System" << endl;
    cout << "========================================" << endl;

    while (true)
    {
        cout << "\nWelcome to Airline Reservation and Management System" << endl;
        cout << "Please select your role:" << endl;
        cout << "1. Administrator" << endl;
        cout << "2. Booking Agent" << endl;
        cout << "3. Passenger" << endl;
        cout << "4. Register New User" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";

        int roleChoice;
        cin >> roleChoice;
        cin.ignore();

        if (roleChoice == 5)
        {
            cout << "\nSaving all data..." << endl;
            system.saveAllData();
            cout << "Thank you for using our system. Goodbye!" << endl;
            break;
        }

        if (roleChoice == 4)
        {
            // Registration
            string role, username, password, email, phone;

            cout << "\n--- User Registration ---" << endl;
            cout << "Select role (Admin/Agent/Passenger): ";
            getline(cin, role);

            cout << "Enter username: ";
            getline(cin, username);

            cout << "Enter password: ";
            getline(cin, password);

            cout << "Enter email: ";
            getline(cin, email);

            cout << "Enter phone: ";
            getline(cin, phone);

            if (system.registerUser(role, username, password, email, phone))
            {
                cout << "\nRegistration successful! You can now login." << endl;
            }
            else
            {
                cout << "\nRegistration failed. Please try again." << endl;
            }
            menucli.pause();
            continue;
        }

        // Login
        string roleStr;
        if (roleChoice == 1)
            roleStr = "Administrator";
        else if (roleChoice == 2)
            roleStr = "Booking Agent";
        else if (roleChoice == 3)
            roleStr = "Passenger";
        else
        {
            cout << "Invalid choice!" << endl;
            continue;
        }

        cout << "\n--- " << roleStr << " Login ---" << endl;
        cout << "Username: ";
        string username, password;
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        auto user = system.authenticateUser(username, password);

        if (!user)
        {
            cout << "\nLogin failed! Invalid credentials." << endl;
            menucli.pause();
            continue;
        }

        // Route to appropriate menu based on role
        if (user->getRole() == "Admin")
        {
            auto admin = dynamic_pointer_cast<Admin>(user);
            menucli.adminMenu(system, admin);
        }
        else if (user->getRole() == "Agent")
        {
            auto agent = dynamic_pointer_cast<BookingAgent>(user);
            menucli.agentMenu(system, agent);
        }
        else if (user->getRole() == "Passenger")
        {
            auto passenger = dynamic_pointer_cast<Passenger>(user);
            menucli.passengerMenu(system, passenger);
        }

        system.logoutUser();
    }
    cout << "\nSaving all data..." << endl;
    system.saveAllData();

    return 0;
}
