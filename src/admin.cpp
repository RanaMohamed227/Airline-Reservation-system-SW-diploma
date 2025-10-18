#include "../inc/admin.hpp"
#include "../inc/systemmanager.hpp"

// Constructor
Admin::Admin(string username, string password)
    : User(username, password, "Admin") {}

// User Management
void Admin::createUser(SystemManager &system, string role, string username,
                       string password, string email)
{
    system.registerUser(role, username, password, email,"010-0000-0000");
}

void Admin::deleteUser(SystemManager &system, string userID)
{
    system.deleteUser(userID);
}

void Admin::viewAllUsers(SystemManager &system)
{
    system.displayAllUsers();
}

void Admin::updateUserInfo(SystemManager &system, string userID)
{

    // search for user by ID

    auto findUser = system.findUserByID(userID);

    if (!findUser)
    {

        cout << "User not found!" << endl;

        return;
    }
    cin.ignore();
    string newEmail, newPhone;
    cout << "Enter new email (or press enter to skip):  " << endl;
    getline(cin, newEmail);
    if (!newEmail.empty())
    {
        findUser->updateEmail(newEmail);
    }
    cout << "Enter new phone (or press enter to skip): " << endl;
    getline(cin, newPhone);
    if (!newPhone.empty())
    {
        findUser->updatePhone(newPhone);
    }
    cout << "User information updated successfully." << endl;
}

// Flight Management
void Admin::addFlight(SystemManager &system, string flightNum, string origin,
                      string dest, string depTime, string arrTime,
                      string aircraftID)
{
    // Create flight object
    auto newFlight = make_shared<Flight>(flightNum, origin, dest, depTime, arrTime, aircraftID);

    system.addFlight(newFlight);
}

void Admin::updateFlight(SystemManager &system, string flightNum)
{
    // search for flight by number
    auto flight = system.findFlightByNumber(flightNum);
    if (!flight)
    {
        cout << "Flight not found!" << endl;
        return;
    }

    cout << "Updating flight " << flightNum << endl;
    cout << "what do you want to update?" << endl;
    cout << "1. Status (Scheduled/Boarding/Departed/etc)" << endl;
    cout << "2. Gate" << endl;
    cout << "3. Delay Flight" << endl;
    cout << "4. Cancel Flight" << endl;
    cout << "5. Update Pricing" << endl;
    cout << "6. Origin" << endl;
    cout << "7. Destination" << endl;
    cout << "8. Departure Time" << endl;
    cout << "9. Arrival Time" << endl;
    cout << "10. Aircraft ID" << endl;

    cout << "Enter choice (1-10): ";
    int choice;
    cin >> choice;
    cin.ignore(); // to ignore the newline character after integer input
    switch (choice)
    {
    case 1:
    {
        string newStatus;
        cout << "Enter new status: ";
        getline(cin, newStatus);
        flight->updateStatus(newStatus); // This method likely exists
        break;
    }
    case 2:
    {
        string newGate;
        cout << "Enter gate number: ";
        getline(cin, newGate);
        flight->setGate(newGate); // This method likely exists
        break;
    }
    case 3:
    {
        int minutes;
        cout << "Enter delay in minutes: ";
        cin >> minutes;
        flight->delayFlight(minutes); // This method likely exists
        break;
    }
    case 4:
    {
        flight->cancelFlight(); // This method likely exists
        cout << "Flight cancelled." << endl;
        break;
    }
    case 5:
    {
        double economy, business, first;
        cout << "Enter economy price: ";
        cin >> economy;
        cout << "Enter business price: ";
        cin >> business;
        cout << "Enter first class price: ";
        cin >> first;
        flight->setPricing(economy, business, first); // This method likely exists
        break;
    }
    case 6:
    {
        string newOrigin;
        cout << "Enter new origin: ";
        getline(cin, newOrigin);
        flight->setOrigin(newOrigin);
        break;
    }
    case 7:
    {
        string newDest;
        cout << "Enter new destination: ";
        getline(cin, newDest);
        flight->setDestination(newDest);
        break;
    }
    case 8:
    {
        string newDepTime;
        cout << "Enter new departure time: ";
        getline(cin, newDepTime);
        flight->setDepartureTime(newDepTime);
        break;
    }
    case 9:
    {
        string newArrTime;
        cout << "Enter new arrival time: ";
        getline(cin, newArrTime);
        flight->setArrivalTime(newArrTime);
        break;
    }

    case 10:
    {
        string newAircraftID;
        cout << "Enter new aircraft ID: ";
        getline(cin, newAircraftID);
        flight->setAircraft(newAircraftID);
        break;
    }
    default:
        cout << "Invalid choice." << endl;
        return;
    }
    cout << "Flight updated successfully." << endl;
}

void Admin::deleteFlight(SystemManager &system, string flightNum)
{
    system.deleteFlight(flightNum);
}
void Admin::viewAllFlights(SystemManager &system)
{
    system.displayAllFlights();
}

// aircraft management

void Admin::assignAircraftToFlight(SystemManager &system, string flightNum,
                                   string aircraftID)
{
    auto findFlight = system.findFlightByNumber(flightNum);
    if (!findFlight)
    {
        cout << "Flight not found!" << endl;
        return;
    }
    auto findAircraft = system.findAircraftByID(aircraftID);
    if (!findAircraft)
    {
        cout << "Aircraft not found!" << endl;
        return;
    }
    findFlight->setAircraft(aircraftID);
    cout << "Aircraft " << aircraftID << " assigned to flight " << flightNum << endl;
}

// Aircraft Management
void Admin::addAircraft(SystemManager &system, string model, string manufacturer,
                        int economy, int business, int first)
{
    auto newAircraft = make_shared<Aircraft>(model, manufacturer, economy, business, first);
    system.addAircraft(newAircraft);
    cout << "Aircraft added successfully." << endl;
}

void Admin::removeAircraft(SystemManager &system, string aircraftID)
{
    system.removeAircraft(aircraftID);
}
void Admin::viewAllAircraft(SystemManager &system)
{
    system.displayAllAircraft();
}

// Maintenance Management
void Admin::scheduleMaintenanceForAircraft(SystemManager &system,
                                           string aircraftID, string type, string date)
{
    auto newMaintenance = make_shared<Maintenance>(aircraftID, type, date);

    system.addMaintenanceRecord(newMaintenance);
    cout << "Maintenance scheduled successfully." << endl;
}
void Admin::viewMaintenanceSchedule(SystemManager &system)
{
    system.getScheduledMaintenance();
}

// Reports
void Admin::generateFlightReport(SystemManager &system)
{
    system.generateFlightReport();
}
void Admin::generateRevenueReport(SystemManager &system)
{
    system.generateRevenueReport();
}
void Admin::generateMaintenanceReport(SystemManager &system)
{
    system.generateMaintenanceReport();
}
void Admin::generateUserActivityReport(SystemManager &system)
{
    system.generateUserActivityReport();
}
void Admin::displaySystemStatus(SystemManager &system)
{
    system.displaySystemStatus();
}

// Override
void Admin::showMenu()
{
    cout << "\n--- Admin Menu ---\n";
    cout << "1. User Management\n";
    cout << "2. Flight Management\n";
    cout << "3. Aircraft Management\n";
    cout << "4. Maintenance Management\n";
    cout << "5. Reports\n";
    cout << "6. Update Profile\n";
    cout << "7. Logout\n";
    cout << "Enter choice: ";

}
// Serialization
json Admin::toJson() const
{
    json j = User::toJson();
    return j;
}

// Static method to create Admin from JSON
shared_ptr<Admin> Admin::fromJson(const json &j)
{
    auto admin = make_shared<Admin>(
        j.at("username").get<string>(),
        j.at("password").get<string>());
    admin->userID = j.at("userID").get<string>();
    admin->email = j.at("email").get<string>();
    admin->phone = j.at("phone").get<string>();
    return admin;
}


