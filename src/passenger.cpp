#include "../inc/passenger.hpp"
#include "../inc/systemmanager.hpp"

// Constructor

Passenger::Passenger(string username, string password, string passport,
                     string nationality, string DOB)
    : User(username, password, "Passenger"),
      passportNumber(passport),
      nationality(nationality),
      dateOfBirth(DOB),
      loyaltyPoints(0),
      tier("Bronze"),
      mealPreference("None"),
      seatPreference("None"),
      needsWheelchair(false) {}

// Search & Book
void Passenger::searchFlights(SystemManager &system, string origin, string dest, string date)
{
    cout << "\n=== Searching Flights ===" << endl;
    cout << "From: " << origin << " To: " << dest << " Date: " << date << endl;

    auto flights = system.searchFlights(origin, dest, date);

    if (flights.empty())
    {
        cout << "No flights found." << endl;
        return;
    }

    cout << "Available Flights:\n";
    cout << "\nFound    " << flights.size() << "    flights:\n"
         << endl;
    for (const auto &flight : flights)
    {
        flight->displayFlightInfo();
        cout << "-------------------" << endl;
    }
}

void Passenger::bookFlight(SystemManager &system, string flightNum, vector<string> seats)
{
    // first we need to check if the flight exists and seats are available
    cout << "\n searching for flight " << flightNum << endl;

    auto flight = system.findFlightByNumber(flightNum);
    if (!flight)
    {
        cout << "Flight not found!" << endl;
        return;
    }

    cout << "\n flight found. checking seat availability..." << endl;
    for (const auto &seat : seats)
    {
        if (!flight->isSeatAvailable(seat))
        {
            cout << "Seat " << seat << " is not available!" << endl;
            return;
        }
    }
    double totalAmount = 0;
    for (const auto &seat : seats)
    {
        string seatClass = flight->getSeatClass(seat); // Get seat class from flight

        double price = flight->getPrice(seatClass);
        totalAmount += price;

        cout << "  " << seat << " (" << seatClass << "): $" << price << endl;
    }

    cout << "Total before discount: $" << totalAmount << endl;

    // 4. Apply discount
    double discount = getDiscount();
    double finalAmount = totalAmount * (1 - discount);
    cout << "Final Amount After Discount : $" << finalAmount << endl;

    // 5. Create reservation
    auto reservation = make_shared<Reservation>(userID, flightNum, seats, userID);
    reservation->setTotalAmount(totalAmount);
    reservation->applyDiscount(discount * 100); // Convert to percentage

    // 6. Book seats on flight
    for (const auto &seat : seats)
    {
        flight->bookSeat(seat, userID);
    }

    // 7. Add to system
    system.addReservation(reservation);

    // 8. Add to history
    addReservationToHistory(reservation->getReservationID());

    // 9. Earn loyalty points (1 point per $10)
    int pointsEarned = static_cast<int>(finalAmount / 10);
    earnPoints(pointsEarned);

    cout << "\n Booking Successful!" << endl;
    cout << "Reservation ID: " << reservation->getReservationID() << endl;
    cout << "Total Amount: $" << finalAmount << endl;
    cout << "Loyalty Points Earned: " << pointsEarned << endl;
}
/*


// My Bookings
void Passenger::viewMyBookings(SystemManager &system)
{
    system.viewBookingsByUser(userID);
}

void Passenger::cancelMyBooking(SystemManager &system, string reservationID)
{
    system.cancelBooking(reservationID, userID);
}

// Check-in
void Passenger::doOnlineCheckIn(SystemManager &system, string reservationID)
{
    system.onlineCheckIn(reservationID, userID);
}
void Passenger::chooseSeat(SystemManager &system, string reservationID, string seatNum)
{
    system.selectSeat(reservationID, userID, seatNum);
}
void Passenger::getBoardingPass(SystemManager &system, string reservationID)
{
    system.generateBoardingPass(reservationID, userID);
}


    */

// Loyalty
void Passenger::earnPoints(int points)
{
    loyaltyPoints += points;
    updateTier();
}
bool Passenger::redeemPoints(int points) // Based on tier  getDiscount()
{                                        // check if enough points
    if (points <= loyaltyPoints)
    {
        loyaltyPoints -= points;
        updateTier();
        return true;
    }
    else
    {
        cout << "Not enough loyalty points." << endl;
        return false;
    }
}

double Passenger::getDiscount() // Based on tier
{
    if (tier == "Bronze")
        return 0.0;
    else if (tier == "Silver")
        return 0.05;
    else if (tier == "Gold")
        return 0.10;
    else if (tier == "Platinum")
        return 0.15;
    return 0.0;
}

void Passenger::updateTier() // Update based on points
{
    if (loyaltyPoints >= 10000)
        tier = "Platinum";
    else if (loyaltyPoints >= 5000)
        tier = "Gold";
    else if (loyaltyPoints >= 1000)
        tier = "Silver";
    else
        tier = "Bronze";
}
void Passenger::checkLoyaltyStatus()
{
    cout << "Loyalty Points: " << loyaltyPoints << ", Tier: " << tier << endl;
}

// Preferences
void Passenger::setMealPreference(string meal)
{
    mealPreference = meal;
}
void Passenger::setSeatPreference(string pref)
{
    seatPreference = pref;
}
void Passenger::setWheelchairNeeded(bool needed)
{
    needsWheelchair = needed;
}

// History
void Passenger::addReservationToHistory(string reservationID)
{
    reservationIDs.push_back(reservationID);
}
/*
void Passenger::viewTravelHistory(SystemManager &system)
{
    cout << "Travel History for " << username << ":\n";
    for (const auto &resID : reservationIDs)
    {
        system.viewBookingDetails(resID);
    }
}
*/

// Override
void Passenger::showMenu()
{
    cout << "\n--- Passenger Menu ---\n";
    cout << "1. Search Flights\n";
    cout << "2. Book Flight\n";
    cout << "3. View My Bookings\n";
    cout << "4. Cancel My Booking\n";
    cout << "5. Check-In\n";
    cout << "6. Choose Seat\n";
    cout << "7. Get Boarding Pass\n";
    cout << "8. View Loyalty Status\n";
    cout << "9. Set Meal Preference\n";
    cout << "10. Set Seat Preference\n";
    cout << "11. Update Email\n";
    cout << "12. Update Phone\n";
    cout << "13. Change Password\n";
    cout << "14. View Travel History\n";
    cout << "0. Logout\n";
    cout << "Enter choice: ";
}

// Serialization
json Passenger::toJson() const
{
    json j = User::toJson(); // Get base class data
    j["passportNumber"] = passportNumber;
    j["nationality"] = nationality;
    j["loyaltyPoints"] = loyaltyPoints;
    j["dateOfBirth"] = dateOfBirth;
    j["tier"] = tier;
    j["mealPreference"] = mealPreference;
    j["seatPreference"] = seatPreference;
    j["needsWheelchair"] = needsWheelchair;
    j["reservationIDs"] = reservationIDs;
    return j;
}

shared_ptr<Passenger> Passenger::fromJson(const json &j)
{
    auto passenger = make_shared<Passenger>(
        j.at("username").get<string>(),
        j.at("password").get<string>(),
        j.at("passportNumber").get<string>(),
        j.at("nationality").get<string>(),
        j.at("dateOfBirth").get<string>());
    passenger->userID = j.at("userID").get<string>();
    passenger->email = j.at("email").get<string>();
    passenger->phone = j.at("phone").get<string>();
    passenger->loyaltyPoints = j.at("loyaltyPoints").get<int>();
    passenger->tier = j.at("tier").get<string>();
    passenger->mealPreference = j.at("mealPreference").get<string>();
    passenger->seatPreference = j.at("seatPreference").get<string>();
    passenger->needsWheelchair = j.at("needsWheelchair").get<bool>();
    passenger->reservationIDs = j.at("reservationIDs").get<vector<string>>();
    return passenger;
}
