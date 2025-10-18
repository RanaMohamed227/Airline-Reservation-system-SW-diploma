#include "../inc/aircraft.hpp"
#include <iostream>
#include <string>
using namespace std;
#include "../inc/json.hpp"
using json = nlohmann::json;




 static int idCounter = 1;
// Constructor
Aircraft::Aircraft(string model, string manufacturer, int economy,
                   int business, int first)
    : model(model), manufacturer(manufacturer),
      economySeats(economy), businessSeats(business), firstClassSeats(first),
      status("Available"), flightHours(0), hoursSinceMaintenance(0){

        // generate unique aircraftID
       
        aircraftID = "AC" + to_string(idCounter++);
        totalSeats = economy + business + first;
        lastMaintenanceDate = "None";
        nextMaintenanceDate = "Not scheduled";
        maintenanceRecordIDs = {};
      }






// Status   
void Aircraft::setStatus(string newStatus)
{
    if (newStatus == "Available" || newStatus == "InUse" || newStatus == "Maintenance")
    {
        status = newStatus;
    }
    else
    {
        cout << "Invalid status!" << endl;
    }
}





bool Aircraft::isAvailable() const
{
    return status == "Available";
}



// Flight hours
void Aircraft::addFlightHours(int hours)
{
    if (hours > 0)
    {
        flightHours += hours;
        hoursSinceMaintenance += hours;
    }
    else
    {
        cout << "Invalid hours!" << endl;
    }

    if (hoursSinceMaintenance >= 500)
    {
        status = "Maintenance";
        cout << "Aircraft " << aircraftID << " needs maintenance!" << endl;
    }
}



// Maintenance
bool Aircraft::needsMaintenance() const // Check if >500 hours
{
    return hoursSinceMaintenance >= 500;
}


void Aircraft::scheduleNextMaintenance(string date)
{
    nextMaintenanceDate = date;
}


void Aircraft::recordMaintenance(string maintenanceID)
{
    maintenanceRecordIDs.push_back(maintenanceID);
}



void Aircraft::performedMaintenance() // Reset hours since maintenance
{
    hoursSinceMaintenance = 0;
    lastMaintenanceDate = nextMaintenanceDate;
    nextMaintenanceDate = "";
    status = "Available";
    cout << "Aircraft " << aircraftID << " maintenance completed." << endl;
}


// Display
void Aircraft::displayInfo()
{
    cout << "Aircraft ID: " << aircraftID << endl;
    cout << "Model: " << model << ", Manufacturer: " << manufacturer << endl;
    cout << "Seats - Total: " << totalSeats
         << ", Economy: " << economySeats
         << ", Business: " << businessSeats
         << ", First Class: " << firstClassSeats << endl;
    cout << "Status: " << status << endl;
    cout << "Flight Hours: " << flightHours << endl;
}


void Aircraft::displayMaintenanceStatus()
{
    cout << "Aircraft ID: " << aircraftID << endl;
    cout << "Hours Since Last Maintenance: " << hoursSinceMaintenance << endl;
    cout << "Last Maintenance: " << lastMaintenanceDate
         << ", Next Maintenance: " << nextMaintenanceDate << endl;
    cout << "Maintenance Records: ";
    for (const auto &id : maintenanceRecordIDs)
    {
        cout << id << " ";
    }


    if (needsMaintenance())
    {
        cout << "Status: Needs Maintenance!" << endl;
    }
    else
    {
        cout << "Status: No Maintenance Needed." << endl;
    }
    cout << "Next Scheduled Maintenance: " << nextMaintenanceDate << endl;
}


// Serialization
json Aircraft::toJson() const
{
    json j;
    j["aircraftID"] = aircraftID;
    j["model"] = model;
    j["manufacturer"] = manufacturer;
    j["totalSeats"] = totalSeats;
    j["economySeats"] = economySeats;
    j["businessSeats"] = businessSeats;
    j["firstClassSeats"] = firstClassSeats;
    j["status"] = status;
    j["flightHours"] = flightHours;
    j["hoursSinceMaintenance"] = hoursSinceMaintenance;
    j["lastMaintenanceDate"] = lastMaintenanceDate;
    j["nextMaintenanceDate"] = nextMaintenanceDate;
    j["maintenanceRecordIDs"] = maintenanceRecordIDs;
    return j;
}

shared_ptr<Aircraft> Aircraft::fromJson(const json &j)
{
    auto aircraft = make_shared<Aircraft>(
        j.at("model").get<string>(),
        j.at("manufacturer").get<string>(),
        j.at("economySeats").get<int>(),
        j.at("businessSeats").get<int>(),
        j.at("firstClassSeats").get<int>());

    aircraft->aircraftID = j.at("aircraftID").get<string>();
    aircraft->totalSeats = j.at("totalSeats").get<int>();
    aircraft->status = j.at("status").get<string>();
    aircraft->flightHours = j.at("flightHours").get<int>();
    aircraft->hoursSinceMaintenance = j.at("hoursSinceMaintenance").get<int>();
    aircraft->lastMaintenanceDate = j.at("lastMaintenanceDate").get<string>();
    aircraft->nextMaintenanceDate = j.at("nextMaintenanceDate").get<string>();
    aircraft->maintenanceRecordIDs = j.at("maintenanceRecordIDs").get<vector<string>>();

    return aircraft;
}