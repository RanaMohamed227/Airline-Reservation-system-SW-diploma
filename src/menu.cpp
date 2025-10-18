#include "../inc/menu.hpp"

void menu::adminMenu(SystemManager &system, shared_ptr<Admin> admin)
{
    while (true)
    {
        admin->showMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 7)
            break; // Logout

        switch (choice)
        {
        case 1:
        { // User Management
            cout << "\n--- User Management ---" << endl;
            cout << "1. Create User" << endl;
            cout << "2. Delete User" << endl;
            cout << "3. View All Users" << endl;
            cout << "4. Update User Info" << endl;
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
            {
                string role, username, password, email;
                cout << "Role (Admin/Agent/Passenger): ";
                getline(cin, role);
                cout << "Username: ";
                getline(cin, username);
                cout << "Password: ";
                getline(cin, password);
                cout << "Email: ";
                getline(cin, email);
                admin->createUser(system, role, username, password, email);
            }
            else if (subChoice == 2)
            {
                string userID;
                cout << "Enter User ID to delete: ";
                getline(cin, userID);
                admin->deleteUser(system, userID);
            }
            else if (subChoice == 3)
            {
                admin->viewAllUsers(system);
            }
            else if (subChoice == 4)
            {
                string userID;
                cout << "Enter User ID to update: ";
                getline(cin, userID);
                admin->updateUserInfo(system, userID);
            }
            break;
        }
        case 2:
        { // Flight Management
            cout << "\n--- Manage Flights ---" << endl;
            cout << "1. Add New Flight" << endl;
            cout << "2. Update Existing Flight" << endl;
            cout << "3. Remove Flight" << endl;
            cout << "4. View All Flights" << endl;
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
            {
                string flightNum, origin, dest, depTime, arrTime, aircraftID;
                cout << "Enter Flight Number: ";
                getline(cin, flightNum);
                cout << "Enter Origin: ";
                getline(cin, origin);
                cout << "Enter Destination: ";
                getline(cin, dest);
                cout << "Enter Departure Date and Time (YYYY-MM-DD HH:MM): ";
                getline(cin, depTime);
                cout << "Enter Arrival Date and Time (YYYY-MM-DD HH:MM): ";
                getline(cin, arrTime);
                cout << "Enter Aircraft ID: ";
                getline(cin, aircraftID);
                admin->addFlight(system, flightNum, origin, dest, depTime, arrTime, aircraftID);
            }
            else if (subChoice == 2)
            {
                string flightNum;
                cout << "Enter Flight Number to Update: ";
                getline(cin, flightNum);
                admin->updateFlight(system, flightNum);
            }
            else if (subChoice == 3)
            {
                string flightNum;
                cout << "Enter Flight Number to Remove: ";
                getline(cin, flightNum);
                admin->deleteFlight(system, flightNum);
            }
            else if (subChoice == 4)
            {
                admin->viewAllFlights(system);
            }
            break;
        }
        case 3:
        { // Aircraft Management
            cout << "\n--- Aircraft Management ---" << endl;
            cout << "1. Add Aircraft" << endl;
            cout << "2. Remove Aircraft" << endl;
            cout << "3. View All Aircraft" << endl;
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
            {
                string model, manufacturer;
                int economy, business, first;
                cout << "Model: ";
                getline(cin, model);
                cout << "Manufacturer: ";
                getline(cin, manufacturer);
                cout << "Economy Seats: ";
                cin >> economy;
                cout << "Business Seats: ";
                cin >> business;
                cout << "First Class Seats: ";
                cin >> first;
                cin.ignore();
                admin->addAircraft(system, model, manufacturer, economy, business, first);
            }
            else if (subChoice == 2)
            {
                string aircraftID;
                cout << "Aircraft ID to remove: ";
                getline(cin, aircraftID);
                admin->removeAircraft(system, aircraftID);
            }
            else if (subChoice == 3)
            {
                admin->viewAllAircraft(system);
            }
            break;
        }
        case 4:
        { // Maintenance Management
            cout << "\n--- Maintenance Management ---" << endl;
            cout << "1. Schedule Maintenance" << endl;
            cout << "2. View Maintenance Schedule" << endl;
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
            {
                string aircraftID, type, date;
                cout << "Aircraft ID: ";
                getline(cin, aircraftID);
                cout << "Type (Routine/Inspection/Repair): ";
                getline(cin, type);
                cout << "Scheduled Date: ";
                getline(cin, date);
                admin->scheduleMaintenanceForAircraft(system, aircraftID, type, date);
            }
            else if (subChoice == 2)
            {
                admin->viewMaintenanceSchedule(system);
            }
            break;
        }
        case 5:
        { // Reports
            cout << "\n--- Generate Reports ---" << endl;
            cout << "1. Flight Report" << endl;
            cout << "2. Revenue Report" << endl;
            cout << "3. Maintenance Report" << endl;
            cout << "4. User Activity Report" << endl;
            cout << "5. System Status" << endl;
            cout << "Enter choice: ";
            int subChoice;
            cin >> subChoice;
            cin.ignore();

            if (subChoice == 1)
                admin->generateFlightReport(system);
            else if (subChoice == 2)
                admin->generateRevenueReport(system);
            else if (subChoice == 3)
                admin->generateMaintenanceReport(system);
            else if (subChoice == 4)
                admin->generateUserActivityReport(system);
            else if (subChoice == 5)
                admin->displaySystemStatus(system);
            break;
        }
        case 6:
        { // Update Profile
            cout << "\n--- Update Profile ---" << endl;
            string email, phone;
            cout << "New Email (or press enter to skip): ";
            getline(cin, email);
            if (!email.empty())
                admin->updateEmail(email);
            cout << "New Phone (or press enter to skip): ";
            getline(cin, phone);
            if (!phone.empty())
                admin->updatePhone(phone);
            cout << "Profile updated successfully." << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
        }
        pause();
    }
}

void menu::agentMenu(SystemManager &system, shared_ptr<BookingAgent> agent)
{
    while (true)
    {
        agent->showMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0)
            break; // Logout

        switch (choice)
        {
        case 1:
        { // Search Flights
            string origin, dest, date;
            cout << "\n--- Search Flights ---" << endl;
            cout << "Enter Origin: ";
            getline(cin, origin);
            cout << "Enter Destination: ";
            getline(cin, dest);
            cout << "Enter Departure Date (YYYY-MM-DD): ";
            getline(cin, date);
            agent->searchFlights(system, origin, dest, date);
            break;
        }
        case 2:
        { // Create Booking
            string passengerID, flightNum, seatInput, paymentmethod, paymentdetails;
            vector<string> seats;

            cout << "\n--- Book a Flight ---" << endl;
            cout << "Enter Passenger ID: ";
            getline(cin, passengerID);
            cout << "Enter Flight Number: ";
            getline(cin, flightNum);
            cout << "Enter Seat Numbers (comma-separated, e.g., 12A,12B): ";
            getline(cin, seatInput);
            cout << " Enter Payment Method (Credit Card/Cash/PayPal): " << paymentmethod;
            getline(cin, paymentmethod);

            cout << "Enter Payment Details: " << paymentdetails;
            getline(cin, paymentdetails);
            // Parse seats
            size_t pos = 0;
            while ((pos = seatInput.find(',')) != string::npos)
            {
                seats.push_back(seatInput.substr(0, pos));
                seatInput.erase(0, pos + 1);
            }
            seats.push_back(seatInput);

            agent->createBooking(system, passengerID, flightNum, seats);
            break;
        }
        case 3:
        { // Modify Booking
            string reservationID;
            cout << "\n--- Modify Reservation ---" << endl;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            agent->modifyBooking(system, reservationID);
            break;
        }
        case 4:
        { // Cancel Booking
            string reservationID;
            cout << "\n--- Cancel Reservation ---" << endl;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            cout << "Are you sure you want to cancel Reservation ID " << reservationID << "? (yes/no): ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "yes")
            {
                agent->cancelBooking(system, reservationID);
            }
            break;
        }
        case 5:
        { // View Booking
            string reservationID;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            agent->viewBooking(system, reservationID);
            break;
        }
        case 6:
        { // View All Bookings
            agent->viewAllBookings(system);
            break;
        }
        case 7:
        { // Process Payment
            string reservationID, method;
            double amount;
            cout << "\n--- Process Payment ---" << endl;
            cout << "Reservation ID: ";
            getline(cin, reservationID);
            cout << "Payment Method (CreditCard/Cash): ";
            getline(cin, method);
            cout << "Amount: ";
            cin >> amount;
            cin.ignore();
            agent->processPayment(system, reservationID, method, amount);
            break;
        }
        case 8:
        { // Check-In Passenger
            string reservationID;
            cout << "\n--- Check-In ---" << endl;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            agent->checkInPassenger(system, reservationID);
            break;
        }
        case 9:
        { // Print Boarding Pass
            string reservationID;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            agent->printBoardingPass(system, reservationID);
            break;
        }
        case 10:
        { // Select Seat
            string reservationID, seatNum;
            cout << "Reservation ID: ";
            getline(cin, reservationID);
            cout << "Seat Number: ";
            getline(cin, seatNum);
            agent->selectSeatForPassenger(system, reservationID, seatNum);
            break;
        }
        case 11:
        { // View Statistics
            cout << "\n--- Agent Statistics ---" << endl;
            cout << "Bookings Processed: " << agent->getBookingsProcessed() << endl;
            break;
        }
        default:
            cout << "Invalid choice!" << endl;
        }
        pause();
    }
}

void menu::passengerMenu(SystemManager &system, shared_ptr<Passenger> passenger)
{
    while (true)
    {
        passenger->showMenu();
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 0)
            break; // Logout

        switch (choice)
        {
        case 1:
        { // Search Flights
            string origin, dest, date;
            cout << "\n--- Search Flights ---" << endl;
            cout << "Enter Origin: ";
            getline(cin, origin);
            cout << "Enter Destination: ";
            getline(cin, dest);
            cout << "Enter Departure Date (YYYY-MM-DD): ";
            getline(cin, date);
            passenger->searchFlights(system, origin, dest, date);
            break;
        }
        case 2:
        { // Book Flight
            string flightNum, seatInput, paymentmethod, paymentdetails;
            vector<string> seats;

            cout << "\n--- Book a Flight ---" << endl;
            cout << "Enter Flight Number: ";
            getline(cin, flightNum);
            cout << "Enter Seat Numbers (comma-separated, e.g., 14C,14D): ";
            getline(cin, seatInput);
            cout << " Enter Payment Method (Credit Card/Cash/PayPal): " << paymentmethod;

            // Parse seats
            size_t pos = 0;
            while ((pos = seatInput.find(',')) != string::npos)
            {
                seats.push_back(seatInput.substr(0, pos));
                seatInput.erase(0, pos + 1);
            }
            seats.push_back(seatInput);

            passenger->bookFlight(system, flightNum, seats);
            break;
        }
        case 3:
        { // View My Bookings
            auto reservations = system.getReservationsByPassenger(passenger->getUserID());
            cout << "\n--- My Reservations ---" << endl;
            if (reservations.empty())
            {
                cout << "No reservations found." << endl;
            }
            else
            {
                for (const auto &res : reservations)
                {
                    res->displayDetails();
                    cout << "------------------------" << endl;
                }
            }
            break;
        }
        case 4:
        { // Cancel My Booking
            string reservationID;
            cout << "Enter Reservation ID to cancel: ";
            getline(cin, reservationID);
            cout << "Are you sure you want to cancel Reservation ID " << reservationID << "? (yes/no): ";
            string confirm;
            getline(cin, confirm);
            if (confirm == "yes")
            {
                system.cancelReservation(reservationID);
            }
            break;
        }
        case 5:
        { // Online Check-In
            string reservationID;
            cout << "Enter Reservation ID to check-in: ";
            getline(cin, reservationID);
            auto reservation = system.findReservationByID(reservationID);
            if (reservation && reservation->getPassengerID() == passenger->getUserID())
            {
                if (reservation->canCheckIn())
                {
                    if (reservation->checkIn())
                    {
                        // string boardingPass = reservation->generateBoardingPass();
                        // cout << "Check-in successful! Boarding Pass Number: " << boardingPass << endl;
                    }
                    else
                    {
                        cout << "Check-in failed. Please try again later." << endl;
                    }
                }
                else
                {
                    cout << "Check-in not allowed at this time. You can check-in within 24 hours of departure." << endl;
                }
            }
            else
            {
                cout << "Reservation not found or does not belong to you." << endl;
            }
            break;
        }
        case 6:
        { // Choose Seat
            string reservationID, seatNum;
            cout << "Enter Reservation ID: ";
            getline(cin, reservationID);
            cout << "Enter Seat Number to choose: ";
            getline(cin, seatNum);
            auto reservation = system.findReservationByID(reservationID);
            if (reservation && reservation->getPassengerID() == passenger->getUserID())
            {
                // For simplicity, we assume the seat can be changed directly
                vector<string> newSeats = reservation->getSeats();
                newSeats.push_back(seatNum); // Add new seat
                if (reservation->modifySeats(newSeats))
                {
                    cout << "Seat " << seatNum << " added to your reservation." << endl;
                }
                else
                {
                    cout << "Failed to modify seats. Please try again." << endl;
                }
            }
            else
            {
                cout << "Reservation not found or does not belong to you." << endl;
            }
            break;
        }
        case 7:
        { // Get Boarding Pass
            string reservationID;
            cout << "Enter Reservation ID to get Boarding Pass: ";
            getline(cin, reservationID);
            auto reservation = system.findReservationByID(reservationID);
            if (reservation && reservation->getPassengerID() == passenger->getUserID())
            {
                if (reservation->isCheckedIn())
                {
                    reservation->displayBoardingPassInfo();
                }
                else
                {
                    cout << "You need to check-in first to get your boarding pass." << endl;
                }
            }
            else
            {
                cout << "Reservation not found or does not belong to you." << endl;
            }
            break;
        }

        case 8:
        { // View Loyalty Status
            passenger->checkLoyaltyStatus();
            break;
        }
        case 9:
        { // Set Meal Preference
            string meal;
            cout << "Enter meal preference: ";
            getline(cin, meal);
            passenger->setMealPreference(meal);
            break;
        }
        case 10:
        { // Set Seat Preference
            string pref;
            cout << "Enter seat preference (Window/Aisle): ";
            getline(cin, pref);
            passenger->setSeatPreference(pref);
            break;
        }
        case 11:
        { // Update Email
            string email;
            cout << "Enter new email: ";
            getline(cin, email);
            passenger->updateEmail(email);
            break;
        }
        case 12:
        { // Update Phone
            string phone;
            cout << "Enter new phone: ";
            getline(cin, phone);
            passenger->updatePhone(phone);
            break;
        }
        case 13:
        { // Change Password
            string oldPass, newPass;
            cout << "Enter old password: ";
            getline(cin, oldPass);
            cout << "Enter new password: ";
            getline(cin, newPass);
            if (passenger->changePassword(oldPass, newPass))
            {
                cout << "Password changed successfully." << endl;
            }
            break;
        }

        case 14:
        { // View Travel History
            // passenger->viewTravelHistory(system);
            auto reservations = system.getReservationsByPassenger(passenger->getUserID());
            cout << "\n--- My Travel History ---" << endl;
            if (reservations.empty())
            {
                cout << "No travel history found." << endl;
            }
            else
            {
                for (const auto &res : reservations)
                {
                    res->displayDetails();
                    cout << "------------------------" << endl;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice or feature not yet implemented!" << endl;
        }
        pause();
    }
}

void menu::pause()
{
    cout << "\nPress Enter to continue...";
    // cout << "Enter choice: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // cout << "Enter choice: ";
    cin.get();
}