#include "../inc/bookingagent.hpp"
#include "../inc/systemmanager.hpp"
#include "../inc/Passenger.hpp"
#include <algorithm>

BookingAgent :: BookingAgent(string username, string password)
    : User(username, password, "Agent"), bookingsProcessed(0) {}



void BookingAgent::searchFlights(SystemManager &system, string origin, string dest, string date)
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


void BookingAgent::displayAvailableFlights(const vector<shared_ptr<Flight>> &flights)
{
    if (flights.empty())
    {
        cout << "No available flights." << endl;
        return;
    }

    cout << "\nAvailable Flights:\n";
    for (const auto &flight : flights)
    {
        flight->displayFlightInfo();
        cout << "-------------------" << endl;
    }
}

void BookingAgent::createBooking(SystemManager &system, string passengerID, string flightNum, vector<string> seats)
{
    // 1. Validate passenger
    auto passenger = system.findUserByID(passengerID);
    if ((!passenger) || (passenger->getRole() != "Passenger"))
    {
        cout << "Invalid passenger ID!" << endl;
        return;
    }

    // 2. Validate flight
    auto flight = system.findFlightByNumber(flightNum);
    if (!flight)
    {
        cout << "Flight not found!" << endl;
        return;
    }

    // 3. Check seat availability and calculate total
    cout << "\n Booking seats for passenger " << passenger->getUsername() << " on flight " << flightNum << endl;
    cout << "Selected Seats:\n";
    for (const auto &seat : seats)
    {
        if (!flight->isSeatAvailable(seat))
        {
            cout << "Seat " << seat << " is not available!" << endl;
            return;
        }
    }
    cout << "\n Seat Pricing:\n";
    double totalAmount = 0; 
    for (const auto &seat : seats)
    {
        string seatClass = flight->getSeatClass(seat); // Get seat class from flight

        double price = flight->getPrice(seatClass);
        totalAmount += price;

        cout << "  " << seat << " (" << seatClass << "): $" << price << endl;
    }


    cout << "Total before discount: $" << totalAmount << endl;
   
   
   //passenger pointer to access getDiscount method
   //apply discount based on passenger tier
   
    // 4. Apply discount 

auto passengerPtr = dynamic_pointer_cast<Passenger>(passenger);
double discount = 0.0;
if (passengerPtr) {
    discount = passengerPtr->getDiscount();
    cout << "Passenger Tier: " << passengerPtr->getTier() 
         << " - Discount: " << (discount * 100) << "%" << endl;
}

double finalAmount = totalAmount * (1 - discount);
cout << "Final Amount After Discount: $" << finalAmount << endl;

    // 5. Create reservation
    auto userID = passenger->getUserID();
    auto reservation = make_shared<Reservation>(userID, flightNum, seats, userID);
    reservation->setTotalAmount(totalAmount);
    reservation->applyDiscount(discount * 100); // Convert to percentage

 // 6. Book seats
    for (const auto &seat : seats)
    {
        flight->bookSeat(seat, userID);
    }
    // 7. Add to system
    system.addReservation(reservation);
    incrementBookings();




// Update loyalty points and history
if (passengerPtr) {
    int pointsEarned = static_cast<int>(finalAmount / 10);
    passengerPtr->earnPoints(pointsEarned);
    passengerPtr->addReservationToHistory(reservation->getReservationID());
    cout << "Loyalty Points Earned: " << pointsEarned << endl;
}



   

   
    // 8. Process payment (simplified - assume full payment)
    auto payment = make_shared<Payment>(reservation->getReservationID(), finalAmount, "CreditCard");
    payment->markCompleted();
    system.addPayment(payment); 



    cout << "\n Booking Successful!" << endl;
    cout << "Reservation ID: " << reservation->getReservationID() << endl;
    cout << "Total Amount Paid: $" << finalAmount << endl;
    cout << "Payment ID: " << payment->getPaymentID() << endl;
}





void BookingAgent::modifyBooking(SystemManager &system, string reservationID)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }

    cout << "Modifying Reservation " << reservationID << endl;
    cout << "1. Add Seat\n";
    cout << "2. Remove Seat\n";
    cout << "Select an option: ";
    int choice;
    cin >> choice;
    cin.ignore();

    auto flight = system.findFlightByNumber(reservation->getFlightNumber());
    if (!flight)
    {
        cout << "Associated flight not found!" << endl;
        return;
    }


auto currentSeats = reservation->getSeats();

    if (choice == 1)
    {
        string newSeat;
        cout << "Enter seat to add: ";
        getline(cin, newSeat);
        if (!flight->isSeatAvailable(newSeat))
        {
            cout << "Seat not available!" << endl;
            return;
        }
        currentSeats.push_back(newSeat);
        reservation->modifySeats(currentSeats);
        flight->bookSeat(newSeat, reservation->getPassengerID());
        cout << "Seat added successfully." << endl;
    }
    else if (choice == 2)
    {
        string remSeat;
        cout << "Enter seat to remove: ";
        getline(cin, remSeat);
        auto findSeat = std::find(currentSeats.begin(), currentSeats.end(), remSeat);

        if (findSeat == currentSeats.end() )
        {
            cout << "Seat not in reservation!" << endl;
            return;
        }
         currentSeats.erase(
        std::remove(currentSeats.begin(), currentSeats.end(), remSeat), currentSeats.end() );
        reservation->modifySeats(currentSeats);
        flight->releaseSeat(remSeat);
        cout << "Seat removed successfully." << endl;
    }
    else
    {
        cout << "Invalid option!" << endl;
    }
}



void BookingAgent::cancelBooking(SystemManager &system, string reservationID)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }

    auto flight = system.findFlightByNumber(reservation->getFlightNumber());
    if (flight)
    {
        for (const auto &seat : reservation->getSeats())
        {
            flight->releaseSeat(seat);
        }
    }

    system.cancelReservation(reservationID);
    cout << "Reservation " << reservationID << " cancelled successfully." << endl;
}

void BookingAgent::viewBooking(SystemManager &system, string reservationID)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }

    reservation->displayDetails();
}

void BookingAgent::viewAllBookings(SystemManager &system)
{
    system.displayAllReservations();
}




//payment Processing


void BookingAgent::processPayment(SystemManager &system, string reservationID, string method, double amount)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }

    auto existingPayment = system.findPaymentByReservation(reservationID);
    if (existingPayment && existingPayment->getStatus() == "Completed")
    {
        cout << "Payment already completed for this reservation." << endl;
        return;
    }

    auto payment = make_shared<Payment>(reservationID, amount, method);
payment->markCompleted();
    system.addPayment(payment);
    cout << "Payment of $" << amount << " processed successfully. Payment ID: " << payment->getPaymentID() << endl;
}

// Check-in
void BookingAgent::checkInPassenger(SystemManager &system, string reservationID)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    } 
    reservation->checkIn();
    cout << "Passenger checked in successfully." << endl;
//generate boarding pass
   string boardingPass = reservation->generateBoardingPass();
    cout << "Boarding Pass Number: " << boardingPass << endl;

}                  

void BookingAgent::printBoardingPass(SystemManager &system, string reservationID)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }
    if (!reservation->isCheckedIn())
    {
        cout << "Passenger has not checked in yet!" << endl;
        return;
    }
    cout << "Boarding Pass:\n";
    reservation-> displayBoardingPassInfo();
}

void BookingAgent::selectSeatForPassenger(SystemManager &system, string reservationID, string seatNum)
{
    auto reservation = system.findReservationByID(reservationID);
    if (!reservation)
    {
        cout << "Reservation not found!" << endl;
        return;
    }

    auto flight = system.findFlightByNumber(reservation->getFlightNumber());
    if (!flight)
    {
        cout << "Associated flight not found!" << endl;
        return;
    }

    if (!flight->isSeatAvailable(seatNum))
    {
        cout << "Seat not available!" << endl;
        return;
    }

    //reservation->addSeat(seatNum);
    auto currentSeats = reservation->getSeats();
currentSeats.push_back(seatNum);
reservation->modifySeats(currentSeats);
    
    
    flight->bookSeat(seatNum, reservation->getPassengerID());
    cout << "Seat " << seatNum << " assigned to passenger successfully." << endl;
}




// Override
void BookingAgent::showMenu()
{
    cout << "\n--- Booking Agent Menu ---\n";
    cout << "1. Search Flights\n";
    cout << "2. Create Booking\n";
    cout << "3. Modify Booking\n";
    cout << "4. Cancel Booking\n";
    cout << "5. View Booking\n";
    cout << "6. View All Bookings\n";
    cout << "7. Process Payment\n";
    cout << "8. Check-In Passenger\n";
    cout << "9. Print Boarding Pass\n";
    cout << "10. Select Seat for Passenger\n";
    cout << "11. View Statistics\n";
    cout << "0. Logout\n";
    cout << "Enter choice: ";

}


// Serialization
json BookingAgent::toJson() const   
{
    json j = User::toJson();
    j["bookingsProcessed"] = bookingsProcessed;
    return j;
}





shared_ptr<BookingAgent> BookingAgent::fromJson(const json &j)
{
    auto agent = make_shared<BookingAgent>(
        j.at("username").get<string>(),
        j.at("password").get<string>());
    agent->bookingsProcessed = j.at("bookingsProcessed").get<int>();
    agent->userID = j.at("userID").get<string>();
    agent->email = j.at("email").get<string>();
    agent->phone = j.at("phone").get<string>();
    return agent;
}