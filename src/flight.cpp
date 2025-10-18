#include "../inc/flight.hpp"
#include <iostream>
using namespace std;
#include "../inc/json.hpp"
using json = nlohmann::json;

json Flight::Seat::toJson() const
{
    json j;
    j["seatNumber"] = seatNumber;
    j["seatClass"] = seatClass;
    j["isOccupied"] = isOccupied;
    j["passengerID"] = passengerID;
    return j;
}

Flight::Seat Flight::Seat::fromJson(const json &j)
{
    Seat seat;
    seat.seatNumber = j.at("seatNumber").get<string>();
    seat.seatClass = j.at("seatClass").get<string>();
    seat.isOccupied = j.at("isOccupied").get<bool>();
    seat.passengerID = j.at("passengerID").get<string>();
    return seat;
}

Flight::Flight(string flightNum, string orig, string dest,
               string dep, string arr, string aircraftID)
    : flightNumber(flightNum), origin(orig), destination(dest),
      departureTime(dep), arrivalTime(arr), aircraftID(aircraftID),
      status("Scheduled"), delayMinutes(0),
      economyPrice(100.0), businessPrice(300.0), firstClassPrice(500.0),
      gate("Not Assigned")
{
    // Initialize seat map based on aircraft configuration

    /*
        int rows = 20; // Example: 20 rows
        string seatClasses[] = {"Economy", "Business", "First"};
        int classRowLimits[] = {15, 18, 20}; // Rows 1-15 Economy, 16-18 Business, 19-20 First

        for (int r = 1; r <= rows; ++r)
        {
            for (char s = 'A'; s <= 'F'; ++s) // Seats A-F
            {
                string seatNum = to_string(r) + s;
                string seatClass;
                if (r <= classRowLimits[0])
                    seatClass = seatClasses[0];
                else if (r <= classRowLimits[1])
                    seatClass = seatClasses[1];
                else
                    seatClass = seatClasses[2];

                seatMap[seatNum] = {seatNum, seatClass, false, ""};
            }
        }
    */
}




void Flight ::setOrigin(string newOrigin)
{
    origin = newOrigin;
}
void Flight ::setDestination(string newDestination)
{
    destination = newDestination;
}
void Flight ::setDepartureTime(string newDepTime)
{
    departureTime = newDepTime;
}
void Flight ::setArrivalTime(string newArrTime)
{
    arrivalTime = newArrTime;
}

void Flight ::setGate(string newGate)
{
    gate = newGate;
}
void Flight ::setPricing(double economy, double business, double first)
{
    economyPrice = economy;
    businessPrice = business;
    firstClassPrice = first;
}
void Flight ::setAircraft(string newAircraftID)
{
    aircraftID = newAircraftID;
}


void Flight ::setStatus(string newStatus)
{
    status = newStatus;
}





void Flight ::initializeSeats(int economy, int business, int first)
{
    seatMap.clear();
   // int row = 1;

    // First Class: Rows 1-3, Seats A-D (4 seats per row)
    int firstRows = (first + 3) / 4; // Calculate rows needed
    for (int r = 1; r <= firstRows && r <= 3; r++)
    {
        for (char s = 'A'; s <= 'D'; s++)
        {
            string seatNum = to_string(r) + s;
            seatMap[seatNum] = Seat(seatNum, "First");
        }
    }

    // Business Class: Rows 4-10, Seats A-E (5 seats per row)
    int businessRows = (business + 4) / 5;
    for (int r = 4; r < 4 + businessRows && r <= 10; r++)
    {
        for (char s = 'A'; s <= 'E'; s++)
        {
            string seatNum = to_string(r) + s;
            seatMap[seatNum] = Seat(seatNum, "Business");
        }
    }

    // Economy Class: Rows 11-30, Seats A-F (6 seats per row)
    int economyRows = (economy + 5) / 6;
    for (int r = 11; r < 11 + economyRows && r <= 30; r++)
    {
        for (char s = 'A'; s <= 'F'; s++)
        {
            string seatNum = to_string(r) + s;
            seatMap[seatNum] = Seat(seatNum, "Economy");

            // seatMap[seatNum] = Seat{"", seatNum, "Economy", false, ""};
        }
    }

    cout << " Initialized " << seatMap.size() << " seats for flight "
         << flightNumber << endl;
}

bool Flight ::isSeatAvailable(string seatNum) const
{
    auto it = seatMap.find(seatNum);
    if (it != seatMap.end())
    {
        return !it->second.isOccupied;
    }
    return false; // Seat does not exist
}

bool Flight ::bookSeat(string seatNum, string passengerID)
{
    auto it = seatMap.find(seatNum);
    if (it != seatMap.end() && !it->second.isOccupied)
    {
        it->second.isOccupied = true;
        it->second.passengerID = passengerID;
        return true;
    }
    return false; // Seat does not exist or is already occupied
}

void Flight ::releaseSeat(string seatNum)
{
    auto it = seatMap.find(seatNum);
    if (it != seatMap.end() && it->second.isOccupied)
    {
        it->second.isOccupied = false;
        it->second.passengerID = "";
    }
}

string Flight ::getSeatClass(string seatNum) const
{
    auto it = seatMap.find(seatNum);
    if (it != seatMap.end())
    {
        return it->second.seatClass;
    }
    return "Unknown"; // Seat does not exist
}
vector<string> Flight ::getAvailableSeats(string seatClass) const
{
    vector<string> availableSeats;
    for (const auto &pair : seatMap)
    {
        if (pair.second.seatClass == seatClass && !pair.second.isOccupied)
        {
            availableSeats.push_back(pair.first);
        }
    }
    return availableSeats;
}

int Flight ::countAvailableSeats(string seatClass) const
{
    int count = 0;
    for (const auto &pair : seatMap)
    {
        if (pair.second.seatClass == seatClass && !pair.second.isOccupied)
        {
            ++count;
        }
    }
    return count;
}

void Flight ::showSeatMap()
{

    cout << "\n========== SEAT MAP - Flight " << flightNumber << " ==========" << endl;
    cout << "[✓] = Available    [X] = Occupied\n"
         << endl;

    // Group seats by row
    map<int, vector<string>> rowSeats;
    for (const auto &pair : seatMap)
    {
        string seatNum = pair.first;
        int row = stoi(seatNum.substr(0, seatNum.length() - 1));
        rowSeats[row].push_back(seatNum);
    }

    // Display by row
    for (const auto &rowPair : rowSeats)
    {
        int row = rowPair.first;
        cout << "Row " << (row < 10 ? " " : "") << row << ": ";

        for (const string &seatNum : rowPair.second)
        {
            auto it = seatMap.find(seatNum);
            if (it != seatMap.end())
            {
                cout << seatNum << (it->second.isOccupied ? "[X] " : "[✓] ");
            }
        }
        cout << endl;
    }

    cout << "======================================================" << endl;
}

void Flight ::assignCrew(string crewID)
{
    crewMemberIDs.push_back(crewID);
}

void Flight ::removeCrew(string crewID)
{
    crewMemberIDs.erase(remove(crewMemberIDs.begin(), crewMemberIDs.end(), crewID), crewMemberIDs.end());
}

//vector<string> Flight ::getCrew() const
//{
  //  return crewMemberIDs;
//}

void Flight ::updateStatus(string newStatus)
{
    status = newStatus;
}

void Flight::delayFlight(int minutes)
{
    delayMinutes += minutes;
    status = "Delayed";
    cout << "  Flight " << flightNumber << " delayed by " << minutes
         << " minutes. Total delay: " << delayMinutes << " minutes." << endl;
}

void Flight ::cancelFlight()
{
    status = "Cancelled";
}

bool Flight ::isDeparted() const
{
    return status == "Departed";
}

bool Flight ::isCancelled() const
{
    return status == "Cancelled";
}

void Flight ::displayFlightInfo()
{
    cout << "Flight Number: " << flightNumber << "\n"
         << "Origin: " << origin << "\n"
         << "Destination: " << destination << "\n"
         << "Departure Time: " << departureTime << "\n"
         << "Arrival Time: " << arrivalTime << "\n"
         << "Aircraft ID: " << aircraftID << "\n"
         << "Gate: " << gate << "\n"
         << "Status: " << status << "\n"
         << "Delay Minutes: " << delayMinutes << "\n"
         << "Pricing - Economy: $" << economyPrice
         << ", Business: $" << businessPrice
         << ", First Class: $" << firstClassPrice << "\n";
}

void Flight ::displayDetailedInfo()
{
    displayFlightInfo();
    cout << "Crew Members: ";
    for (const auto &crewID : crewMemberIDs)
    {
        cout << crewID << " ";
    }
    cout << "\nSeat Map:\n";
    showSeatMap();
}

json Flight ::toJson() const
{
    json j;
    j["flightNumber"] = flightNumber;
    j["origin"] = origin;
    j["destination"] = destination;
    j["departureTime"] = departureTime;
    j["arrivalTime"] = arrivalTime;
    j["aircraftID"] = aircraftID;
    j["crewMemberIDs"] = crewMemberIDs;
    j["status"] = status;
    j["delayMinutes"] = delayMinutes;
    j["economyPrice"] = economyPrice;
    j["businessPrice"] = businessPrice;
    j["firstClassPrice"] = firstClassPrice;
    j["gate"] = gate;

    // Serialize seat map
    json seatArray = json::array();
    for (const auto &pair : seatMap)
    {
        seatArray.push_back(pair.second.toJson());
    }
    j["seatMap"] = seatArray;

    return j;
}

shared_ptr<Flight> Flight ::fromJson(const json &j)
{
    auto flight = make_shared<Flight>(
        j.at("flightNumber").get<string>(),
        j.at("origin").get<string>(),
        j.at("destination").get<string>(),
        j.at("departureTime").get<string>(),
        j.at("arrivalTime").get<string>(),
        j.at("aircraftID").get<string>());

    flight->crewMemberIDs = j.at("crewMemberIDs").get<vector<string>>();
    flight->status = j.at("status").get<string>();
    flight->delayMinutes = j.at("delayMinutes").get<int>();
    flight->economyPrice = j.at("economyPrice").get<double>();
    flight->businessPrice = j.at("businessPrice").get<double>();
    flight->firstClassPrice = j.at("firstClassPrice").get<double>();
    flight->gate = j.at("gate").get<string>();

    // Deserialize seat map
    for (const auto &seatJson : j.at("seatMap"))
    {
        Flight::Seat seat = Flight::Seat::fromJson(seatJson);
        flight->seatMap[seat.seatNumber] = seat;
    }

    return flight;
}