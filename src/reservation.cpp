#include "../inc/reservation.hpp"

static int reservationIDCounter = 5000; // Static counter for unique reservation IDs

// Constructor
Reservation::Reservation(string passengerID, string flightNum,
                         vector<string> seats, string bookedByUserID )
    : passengerID(passengerID), flightNumber(flightNum),
      seatNumbers(seats), bookedBy(bookedByUserID), status("Pending"),
      totalAmount(0.0), discount(0.0), paymentID(""), checkedIn(false),
      boardingPassNumber("")
{
    // Generate a simple reservationID (in a real system, this should be more robust)
    reservationID = "R" + to_string(reservationIDCounter++);
    bookingDate = "9-10-2025"; // Assuming DateTime has a static now() method
}




// Booking operations
void Reservation::confirm()
{
    if (status == "Pending")
    {
        status = "Confirmed";
        cout << "Reservation " << reservationID << " confirmed." << endl;
    }
    else
    {
        cout << "Reservation cannot be confirmed from status: " << status << endl;
    }
}
void Reservation::cancel()
{
    if (status == "Cancelled" || status == "Completed")
    {
        cout << "Reservation cannot be cancelled from status: " << status << endl;
        return;
    }
    status = "Cancelled";
    cout << "Reservation " << reservationID << " cancelled." << endl;
}

bool Reservation::modifySeats(vector<string> newSeats)
{
    if (status != "Pending" && status != "Confirmed")
    {
        cout << "Seats can only be modified for Pending or Confirmed reservations." << endl;
        return false;
    }
    seatNumbers = newSeats;
    cout << "Seats updated for reservation " << reservationID << "." << endl;
    return true;
}



void Reservation::setSeats(vector<string> seats)
{
    seatNumbers = seats;
}
// Pricing
void Reservation::setTotalAmount(double amount)
{
    totalAmount = amount;
}
void Reservation::applyDiscount(double discountPercent)
{
    if (discountPercent < 0 || discountPercent > 100)
    {
        cout << "Invalid discount percentage." << endl;
        return;
    }
    discount = discountPercent ;
}



double Reservation::getFinalAmount() const
{
    return totalAmount * (1 - discount / 100.0);
}


// Payment
void Reservation::linkPayment(string payID)
{
    paymentID = payID;
}
// Check-in
bool Reservation::canCheckIn()
{

if(status == "Confirmed" && !checkedIn)
    {
        return true;
    }
    //here el mafroud n3ml check 3la el date bta3t el flight w el booking date
    //w n3ml compare w nshof lw el booking date 2abl 24 sa3a mn el flight date
    //bas 3lshan el code msh kaml w msh 3arfa aml eh bta3t el date h3ml placeholder

if(1) // Placeholder for actual date check
    {
        return true;
    }

    // Assuming DateTime has a method to get current time and compare
    // return (flightDateTime - DateTime::now()).toHours() <= 24;
    return false; // Placeholder
}


bool Reservation::checkIn()
{
 
    if (!canCheckIn())
    {
        cout << "Check-in is only allowed within 24 hours of flight." << endl;
        return false;
    }
    checkedIn = true;
    status = "CheckedIn";
    checkInTime = "10-10-2025"; 
    boardingPassNumber = generateBoardingPass();
    cout << "Check-in successful. Boarding Pass Number: " << boardingPassNumber << endl;
    return true;
}

static int boardingPassCounter = 1000;

string Reservation::generateBoardingPass()
{
   
    
    boardingPassNumber = "BP" + to_string(boardingPassCounter++);
   
    return boardingPassNumber;


}


// Status
void Reservation::markCompleted()
{
    if (status == "CheckedIn")
    {
        status = "Completed";
        cout << "Reservation " << reservationID << " marked as Completed." << endl;
    }
    else
    {
        cout << "Only CheckedIn reservations can be marked as Completed." << endl;
    }
}
// Display
void Reservation::displayDetails()
{
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Passenger ID: " << passengerID << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Seats: ";
    for (const auto &seat : seatNumbers)
        cout << seat << " ";
    cout << endl;
    cout << "Booking Date: " << bookingDate << endl;
    cout << "Booked By: " << bookedBy << endl;
    cout << "Status: " << status << endl;
    cout << "Total Amount: $" << totalAmount << endl;
    cout << "Discount: $" << discount << endl;
    cout << "Final Amount: $" << getFinalAmount() << endl;
    cout << "Payment ID: " << paymentID << endl;
    cout << "Checked In: " << (checkedIn ? "Yes" : "No") << endl;
    if (checkedIn)
    {
        cout << "Check-In Time: " << checkInTime << endl;
        cout << "Boarding Pass Number: " << boardingPassNumber << endl;
    }
}
void Reservation::displayBoardingPassInfo()
{
    if (!checkedIn)
    {
        cout << "Passenger has not checked in yet." << endl;
        return;
    }

    cout << "Boarding Pass Information ------------------------" << endl;
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Passenger ID: " << passengerID << endl;
    cout << "Flight Number: " << flightNumber << endl;
    cout << "Seats: ";
    for (const auto &seat : seatNumbers)
        cout << seat << " ";
    cout << endl;
    cout << "Boarding Pass Number: " << boardingPassNumber << endl;
    cout << "Check-In Time: " << checkInTime << endl;                                 // Placeholder
    cout << "Boarding Time: " << "30 minutes before departure" << endl; 
    cout << "------------------------" << endl;
}
// Serialization
json Reservation::toJson() const
{
    json j;
    j["reservationID"] = reservationID;
    j["passengerID"] = passengerID;
    j["flightNumber"] = flightNumber;
    j["seatNumbers"] = seatNumbers;
    j["bookingDate"] = bookingDate;
    j["bookedBy"] = bookedBy;
    j["status"] = status;
    j["totalAmount"] = totalAmount;
    j["discount"] = discount;
    j["paymentID"] = paymentID;
    j["checkedIn"] = checkedIn;
    j["checkInTime"] = checkInTime;
    j["boardingPassNumber"] = boardingPassNumber;
    return j;
}

shared_ptr<Reservation> Reservation::fromJson(const json &j)
{
    auto reservation = make_shared<Reservation>(
        j.at("passengerID").get<string>(),
        j.at("flightNumber").get<string>(),
        j.at("seatNumbers").get<vector<string>>(),
        j.at("bookedBy").get<string>());
    reservation->reservationID = j.at("reservationID").get<string>();
    reservation->bookingDate = j.at("bookingDate").get<string>();
    reservation->status = j.at("status").get<string>();
    reservation->totalAmount = j.at("totalAmount").get<double>();
    reservation->discount = j.at("discount").get<double>();
    reservation->paymentID = j.at("paymentID").get<string>();
    reservation->checkedIn = j.at("checkedIn").get<bool>();
    reservation->checkInTime = j.at("checkInTime").get<string>();
    reservation->boardingPassNumber = j.at("boardingPassNumber").get<string>();
    return reservation;
}