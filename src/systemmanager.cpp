#include "../inc/systemmanager.hpp"

// Constructor
SystemManager::SystemManager() : currentUser(nullptr)
{
    initializeDataDirectory();
    loadAllData();
}

// ===== USER MANAGEMENT =====

bool SystemManager::registerUser(string role, string username, string password,
                                 string email, string phone)
{
    if (findUserByUsername(username))
    {
        cout << "Username already exists." << endl;
        return false;
    }

shared_ptr<User> newUser;
if (role == "Admin") {
    newUser = make_shared<Admin>(username, password);
} else if (role == "Agent") {
    newUser = make_shared<BookingAgent>(username, password);
} else if (role == "Passenger") {
    // Passenger needs passport, nationality, and date of birth
    newUser = make_shared<Passenger>(username, password, "", "", "");
} else {
    cout << "Invalid role specified." << endl;
    return false;
}
    newUser->updateEmail(email);
    newUser->updatePhone(phone);
    users.push_back(newUser);
    saveUsers();
    cout << "User registered successfully with ID: " << newUser->getUserID() << endl;
    return true;
}
shared_ptr<User> SystemManager::authenticateUser(string username, string password)
{
    for (const auto &user : users)
    {
        if (user->getUsername() == username && user->validatePassword(password))
        {
            currentUser = user;
            cout << "Login successful. Welcome, " << currentUser->getUsername() << "!" << endl;
            return currentUser;
        }
    }
    cout << "Invalid username or password." << endl;
    return nullptr;
}

void SystemManager::logoutUser()
{
    if (currentUser)
    {
        cout << "User " << currentUser->getUsername() << " logged out." << endl;
        currentUser = nullptr;
    }
    else
    {
        cout << "No user is currently logged in." << endl;
    }
}

shared_ptr<User> SystemManager::getCurrentUser() const
{
    return currentUser;
}

shared_ptr<User> SystemManager::findUserByID(string userID)
{
    for (const auto &user : users)
    {
        if (user->getUserID() == userID)
        {
            return user;
        }
    }
    return nullptr;
}

shared_ptr<User> SystemManager::findUserByUsername(string username)
{
    for (const auto &user : users)
    {
        if (user->getUsername() == username)
        {
            return user;
        }
    }
    return nullptr;
}

vector<shared_ptr<User>> SystemManager::getAllUsers() const
{
    return users;
}

bool SystemManager::deleteUser(string userID)
{
    auto it = remove_if(users.begin(), users.end(),
                        [&userID](const shared_ptr<User> &user)
                        {
                            return user->getUserID() == userID;
                        });
    if (it != users.end())
    {
        users.erase(it, users.end());
        saveUsers();
        cout << "User with ID " << userID << " deleted successfully." << endl;
        return true;
    }
    cout << "User with ID " << userID << " not found." << endl;
    return false;
}

void SystemManager::displayAllUsers()
{
    cout << "----- All Users -----" << endl;
    for (const auto &user : users)
    {
        cout << "ID: " << user->getUserID()
             << ", Username: " << user->getUsername()
             << ", Role: " << user->getRole()
             << ", Email: " << user->getEmail()
             << ", Phone: " << user->getPhone() << endl;
    }
    cout << "---------------------" << endl;
}

// ===== AIRCRAFT MANAGEMENT =====

void SystemManager::addAircraft(shared_ptr<Aircraft> aircraftPtr)
{
    aircraft.push_back(aircraftPtr);
    saveAircraft();
    cout << "Aircraft added successfully with ID: " << aircraftPtr->getAircraftID() << endl;
}

shared_ptr<Aircraft> SystemManager::findAircraftByID(string aircraftID)
{
    for (const auto &ac : aircraft)
    {
        if (ac->getAircraftID() == aircraftID)
        {
            return ac;
        }
    }
    return nullptr;
}

vector<shared_ptr<Aircraft>> SystemManager::getAvailableAircraft()
{
    vector<shared_ptr<Aircraft>> available;
    for (const auto &ac : aircraft)
    {
        if (ac->isAvailable())
        {
            available.push_back(ac);
        }
    }
    return available;
}

vector<shared_ptr<Aircraft>> SystemManager::getAllAircraft() const
{
    return aircraft;
}

bool SystemManager::removeAircraft(string aircraftID)
{
    auto it = remove_if(aircraft.begin(), aircraft.end(),
                        [&aircraftID](const shared_ptr<Aircraft> &ac)
                        {
                            return ac->getAircraftID() == aircraftID;
                        });
    if (it != aircraft.end())
    {
        aircraft.erase(it, aircraft.end());
        saveAircraft();
        cout << "Aircraft with ID " << aircraftID << " removed successfully." << endl;
        return true;
    }
    cout << "Aircraft with ID " << aircraftID << " not found." << endl;
    return false;
}

void SystemManager::displayAllAircraft()
{
    cout << "----- All Aircraft -----" << endl;
    for (const auto &ac : aircraft)
    {
        ac->displayInfo();
        ac->displayMaintenanceStatus();
        cout << "------------------------" << endl;
    }
}

// ===== FLIGHT MANAGEMENT =====
void SystemManager::addFlight(shared_ptr<Flight> flight)
{
    flights.push_back(flight);
    saveFlights();
    cout << "Flight added successfully with Number: " << flight->getFlightNumber() << endl;
}

shared_ptr<Flight> SystemManager::findFlightByNumber(string flightNum)
{
    for (const auto &fl : flights)
    {
        if (fl->getFlightNumber() == flightNum)
        {
            return fl;
        }
    }
    return nullptr;
}

vector<shared_ptr<Flight>> SystemManager::searchFlights(string origin, string dest,
                                                        string date)
{
    vector<shared_ptr<Flight>> results;
    for (const auto &fl : flights)
    {
        if (fl->getOrigin() == origin && fl->getDestination() == dest &&
            fl->getDepartureTime().substr(0, 10) == date)
        { // Assuming date format "YYYY-MM-DD HH:MM"
            results.push_back(fl);
        }
    }
    return results;
}

vector<shared_ptr<Flight>> SystemManager::getAllFlights() const
{
    return flights;
}

bool SystemManager::deleteFlight(string flightNum)
{
    auto it = remove_if(flights.begin(), flights.end(),
                        [&flightNum](const shared_ptr<Flight> &fl)
                        {
                            return fl->getFlightNumber() == flightNum;
                        });
    if (it != flights.end())
    {
        flights.erase(it, flights.end());
        saveFlights();
        cout << "Flight with Number " << flightNum << " deleted successfully." << endl;
        return true;
    }
    cout << "Flight with Number " << flightNum << " not found." << endl;
    return false;
}

void SystemManager::updateFlightStatus(string flightNum, string status)
{
    auto flight = findFlightByNumber(flightNum);
    if (flight)
    {
        flight->setStatus(status);
        saveFlights();
        cout << "Flight " << flightNum << " status updated to " << status << "." << endl;
    }
    else
    {
        cout << "Flight with Number " << flightNum << " not found." << endl;
    }
}

void SystemManager::displayAllFlights()
{
    cout << "----- All Flights -----" << endl;
    for (const auto &fl : flights)
    {
        cout << "Flight Number: " << fl->getFlightNumber()
             << ", From: " << fl->getOrigin()
             << ", To: " << fl->getDestination()
             << ", Departure: " << fl->getDepartureTime()
             << ", Arrival: " << fl->getArrivalTime()
             << ", Status: " << fl->getStatus()
             << ", Aircraft ID: " << fl->getAircraftID() << endl;
    }
    cout << "-----------------------" << endl;
}

// ===== RESERVATION MANAGEMENT =====
void SystemManager::addReservation(shared_ptr<Reservation> reservation)
{
    reservations.push_back(reservation);
    saveReservations();
    cout << "Reservation added successfully with ID: " << reservation->getReservationID() << endl;
}
shared_ptr<Reservation> SystemManager::findReservationByID(string reservationID)
{
    for (const auto &res : reservations)
    {
        if (res->getReservationID() == reservationID)
        {
            return res;
        }
    }
    return nullptr;
}
vector<shared_ptr<Reservation>> SystemManager::getReservationsByPassenger(string passengerID)
{
    vector<shared_ptr<Reservation>> results;
    for (const auto &res : reservations)
    {
        if (res->getPassengerID() == passengerID)
        {
            results.push_back(res);
        }
    }
    return results;
}
vector<shared_ptr<Reservation>> SystemManager::getReservationsByFlight(string flightNum)
{
    vector<shared_ptr<Reservation>> results;
    for (const auto &res : reservations)
    {
        if (res->getFlightNumber() == flightNum)
        {
            results.push_back(res);
        }
    }
    return results;
}
bool SystemManager::cancelReservation(string reservationID)
{
    auto reservation = findReservationByID(reservationID);
    if (reservation)
    {
        reservation->cancel();
        saveReservations();
        cout << "Reservation " << reservationID << " cancelled successfully." << endl;
        return true;
    }
    cout << "Reservation with ID " << reservationID << " not found." << endl;
    return false;
}
void SystemManager::displayAllReservations()
{
    cout << "----- All Reservations -----" << endl;
    for (const auto &res : reservations)
    {
        res->displayDetails();
        cout << "----------------------------" << endl;
    }
    cout << "----------------------------" << endl;
}

// ===== PAYMENT MANAGEMENT =====
void SystemManager::addPayment(shared_ptr<Payment> payment)
{
    payments.push_back(payment);
    savePayments();
    cout << "Payment added successfully with ID: " << payment->getPaymentID() << endl;
}

shared_ptr<Payment> SystemManager::findPaymentByID(string paymentID)
{
    for (const auto &pay : payments)
    {
        if (pay->getPaymentID() == paymentID)
        {
            return pay;
        }
    }
    return nullptr;
}

shared_ptr<Payment> SystemManager::findPaymentByReservation(string reservationID)
{
    for (const auto &pay : payments)
    {
        if (pay->getReservationID() == reservationID)
        {
            return pay;
        }
    }
    return nullptr;
}

vector<shared_ptr<Payment>> SystemManager::getAllPayments() const
{
    return payments;
}

double SystemManager::getTotalRevenue()
{
    double total = 0.0;
    for (const auto &pay : payments)
    {
        if (pay->getStatus() == "Completed")
        {
            total += pay->getAmount();
        }
    }
    return total;
}

// ===== MAINTENANCE MANAGEMENT =====

void SystemManager::addMaintenanceRecord(shared_ptr<Maintenance> maintenance)
{
    maintenanceRecords.push_back(maintenance);
    saveMaintenance();
    cout << "Maintenance record added successfully with ID: " << maintenance->getMaintenanceID() << endl;
}

shared_ptr<Maintenance> SystemManager::findMaintenanceByID(string maintenanceID)
{
    for (const auto &mr : maintenanceRecords)
    {
        if (mr->getMaintenanceID() == maintenanceID)
        {
            return mr;
        }
    }
    return nullptr;
}

vector<shared_ptr<Maintenance>> SystemManager::getMaintenanceByAircraft(string aircraftID)
{
    vector<shared_ptr<Maintenance>> results;
    for (const auto &mr : maintenanceRecords)
    {
        if (mr->getAircraftID() == aircraftID)
        {
            results.push_back(mr);
        }
    }
    return results;
}

vector<shared_ptr<Maintenance>> SystemManager::getScheduledMaintenance()
{
    vector<shared_ptr<Maintenance>> results;
    for (const auto &mr : maintenanceRecords)
    {
        if (mr->getStatus() == "Scheduled")
        {
            results.push_back(mr);
        }
    }
    return results;
}

vector<shared_ptr<Maintenance>> SystemManager::getOverdueMaintenance()
{
    vector<shared_ptr<Maintenance>> results;
    for (const auto &mr : maintenanceRecords)
    {
        if (mr->isOverdue())
        {
            results.push_back(mr);
        }
    }
    return results;
}

// ===== FILE OPERATIONS (JSON Persistence) =====

void SystemManager::saveAllData()
{
    saveUsers();
    saveAircraft();
    saveFlights();
    saveReservations();
    savePayments();
    saveMaintenance();
}
void SystemManager::loadAllData()
{
    loadUsers();
    loadAircraft();
    loadFlights();
    loadReservations();
    loadPayments();
    loadMaintenance();
}

void SystemManager::saveUsers(string filename)
{
    json jUsers = json::array();
    for (const auto &user : users)
    {
        jUsers.push_back(user->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jUsers.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving users to " << filename << endl;
    }
}
void SystemManager::saveAircraft(string filename)
{
    json jAircraft = json::array();
    for (const auto &ac : aircraft)
    {
        jAircraft.push_back(ac->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jAircraft.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving aircraft to " << filename << endl;
    }
}
void SystemManager::saveFlights(string filename)
{
    json jFlights = json::array();
    for (const auto &fl : flights)
    {
        jFlights.push_back(fl->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jFlights.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving flights to " << filename << endl;
    }
}

void SystemManager::saveReservations(string filename)
{
    json jReservations = json::array();
    for (const auto &res : reservations)
    {
        jReservations.push_back(res->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jReservations.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving reservations to " << filename << endl;
    }
}

void SystemManager::savePayments(string filename)
{
    json jPayments = json::array();
    for (const auto &pay : payments)
    {
        jPayments.push_back(pay->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jPayments.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving payments to " << filename << endl;
    }
}

void SystemManager::saveMaintenance(string filename)
{
    json jMaintenance = json::array();
    for (const auto &mr : maintenanceRecords)
    {
        jMaintenance.push_back(mr->toJson());
    }
    ofstream file(filename);
    if (file.is_open())
    {
        file << jMaintenance.dump(4);
        file.close();
    }
    else
    {
        cerr << "Error saving maintenance records to " << filename << endl;
    }
}

void SystemManager::loadUsers(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jUsers;
        file >> jUsers;
        file.close();
        users.clear();
        for (const auto &jUser : jUsers)
        {
            users.push_back(User::fromJson(jUser));
        }
    }
    else
    {
        cerr << "Error loading users from " << filename << endl;
    }
}

void SystemManager::loadAircraft(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jAircraft;
        file >> jAircraft;
        file.close();
        aircraft.clear();
        for (const auto &jAc : jAircraft)
        {
            aircraft.push_back(Aircraft::fromJson(jAc));
        }
    }
    else
    {
        cerr << "Error loading aircraft from " << filename << endl;
    }
}

void SystemManager::loadFlights(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jFlights;
        file >> jFlights;
        file.close();
        flights.clear();
        for (const auto &jFl : jFlights)
        {
            flights.push_back(Flight::fromJson(jFl));
        }
    }
    else
    {
        cerr << "Error loading flights from " << filename << endl;
    }
}

void SystemManager::loadReservations(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jReservations;
        file >> jReservations;
        file.close();
        reservations.clear();
        for (const auto &jRes : jReservations)
        {
            reservations.push_back(Reservation::fromJson(jRes));
        }
    }
    else
    {
        cerr << "Error loading reservations from " << filename << endl;
    }
}

void SystemManager::loadPayments(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jPayments;
        file >> jPayments;
        file.close();
        payments.clear();
        for (const auto &jPay : jPayments)
        {
            payments.push_back(Payment::fromJson(jPay));
        }
    }
    else
    {
        cerr << "Error loading payments from " << filename << endl;
    }
}

void SystemManager::loadMaintenance(string filename)
{
    ifstream file(filename);
    if (file.is_open())
    {
        json jMaintenance;
        file >> jMaintenance;
        file.close();
        maintenanceRecords.clear();
        for (const auto &jMr : jMaintenance)
        {
            maintenanceRecords.push_back(Maintenance::fromJson(jMr));
        }
    }
    else
    {
        cerr << "Error loading maintenance records from " << filename << endl;
    }
}

// ===== REPORTS & ANALYTICS =====
void SystemManager::generateFlightReport()
{
    cout << "----- Flight Report -----" << endl;
    for (const auto &fl : flights)
    {
        int totalReservations = getReservationsByFlight(fl->getFlightNumber()).size();
        cout << "Flight Number: " << fl->getFlightNumber()
             << ", From: " << fl->getOrigin()
             << ", To: " << fl->getDestination()
             << ", Departure: " << fl->getDepartureTime()
             << ", Arrival: " << fl->getArrivalTime()
             << ", Status: " << fl->getStatus()
             << ", Total Reservations: " << totalReservations << endl;
    }
    cout << "-------------------------" << endl;
}
void SystemManager::generateRevenueReport()
{
    double totalRevenue = getTotalRevenue();
    cout << "----- Revenue Report -----" << endl;
    cout << "Total Revenue from Completed Payments: $" << totalRevenue << endl;
    cout << "--------------------------" << endl;
}
void SystemManager::generateMaintenanceReport()
{
    cout << "----- Maintenance Report -----" << endl;
    for (const auto &mr : maintenanceRecords)
    {
        mr->displaySummary();
        cout << "-----------------------------" << endl;
    }
    cout << "-----------------------------" << endl;
}

void SystemManager::generateUserActivityReport()
{
    cout << "----- User Activity Report -----" << endl;
    for (const auto &user : users)
    {
        int userReservations = getReservationsByPassenger(user->getUserID()).size();
        cout << "User ID: " << user->getUserID()
             << ", Username: " << user->getUsername()
             << ", Role: " << user->getRole()
             << ", Total Reservations: " << userReservations << endl;
    }
    cout << "-------------------------------" << endl;
}

void SystemManager::displaySystemStatus()
{
    cout << "===== System Status =====" << endl;
    cout << "Total Users: " << users.size() << endl;
    cout << "Total Aircraft: " << aircraft.size() << endl;
    cout << "Total Flights: " << flights.size() << endl;
    cout << "Total Reservations: " << reservations.size() << endl;
    cout << "Total Payments: " << payments.size() << endl;
    cout << "Total Maintenance Records: " << maintenanceRecords.size() << endl;
    cout << "=========================" << endl;
}

void SystemManager::initializeDataDirectory()
{
    const string dataDir = "data";
    if (!filesystem::exists(dataDir))
    {
        filesystem::create_directory(dataDir);
    }
}
