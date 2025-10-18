#include "../inc/reservation.hpp"
#include "../inc/maintenance.hpp"
#include "../inc/flight.hpp"
static int maintenanceCounter = 1000;
// Constructor
Maintenance::Maintenance(string aircraftID, string type, string scheduled)
    : aircraftID(aircraftID), type(type), scheduledDate(scheduled), status("Scheduled"),
      description(""), technicianName(""), durationHours(0), cost(0.0) {
    maintenanceID = "MNT" + to_string(maintenanceCounter++);
}




// Operations
void Maintenance::startMaintenance(string techName) {
    if (status == "Scheduled") {
        status = "InProgress";
        technicianName = techName;
        cout << "Maintenance " << maintenanceID << " started by " << technicianName << endl;
    } else {
        cout << "Cannot start maintenance. Current status: " << status << endl;
    }
}






void Maintenance::addPartReplaced(string part) {
    partsReplaced.push_back(part);
    cout << "Part " << part << " added to maintenance " << maintenanceID << endl;
}


void Maintenance::complete(int hours, double cost) {
    if (status == "InProgress") {
        status = "Completed";
        durationHours = hours;
        this->cost = cost;
        completedDate = "9-10-2025"; // Placeholder for current date
        cout << "Maintenance " << maintenanceID << " completed in " << durationHours 
             << " hours with cost $" << this->cost << endl;
    } else {
        cout << "Cannot complete maintenance. Current status: " << status << endl;
    }
}




void Maintenance::reschedule(string newDate) {
    if (status == "Scheduled") {
        scheduledDate = newDate;
        cout << "Maintenance " << maintenanceID << " rescheduled to " << scheduledDate << endl;
    } else {
        cout << "Cannot reschedule maintenance. Current status: " << status << endl;
    }
}



// Status checks
bool Maintenance::isCompleted() const {
    return status == "Completed";
}
bool Maintenance::isOverdue() const {
    // Placeholder logic for overdue check
    return false;
}




// Display
void Maintenance::displayDetails() {
    cout << "Maintenance ID: " << maintenanceID << endl;
    cout << "Aircraft ID: " << aircraftID << endl;
    cout << "Type: " << type << endl;
    cout << "Scheduled Date: " << scheduledDate << endl;
    cout << "Completed Date: " << completedDate << endl;
    cout << "Status: " << status << endl;
    cout << "Technician: " << technicianName << endl;
    cout << "Duration (hours): " << durationHours << endl;
    cout << "Cost: $" << cost << endl;
    cout << "Parts Replaced: ";
    for (const auto& part : partsReplaced) {
        cout << part << " ";
    }
    cout << endl;
}
void Maintenance::displaySummary() {
    cout << "Maintenance " << maintenanceID << " [" << type << "] - Status: " << status << endl;
}



// Serialization
json Maintenance::toJson() const {
    json j;
    j["maintenanceID"] = maintenanceID;
    j["aircraftID"] = aircraftID;
    j["type"] = type;
    j["scheduledDate"] = scheduledDate;
    j["completedDate"] = completedDate;
    j["status"] = status;
    j["description"] = description;
    j["partsReplaced"] = partsReplaced;
    j["technicianName"] = technicianName;
    j["durationHours"] = durationHours;
    j["cost"] = cost;
    return j;
}
shared_ptr<Maintenance> Maintenance::fromJson(const json& j) {
    auto m = make_shared<Maintenance>(j.at("aircraftID").get<string>(),
                                     j.at("type").get<string>(),
                                     j.at("scheduledDate").get<string>());
    m->maintenanceID = j.at("maintenanceID").get<string>();
    m->completedDate = j.at("completedDate").get<string>();
    m->status = j.at("status").get<string>();
    m->description = j.at("description").get<string>();
    m->partsReplaced = j.at("partsReplaced").get<vector<string>>();
    m->technicianName = j.at("technicianName").get<string>();
    m->durationHours = j.at("durationHours").get<int>();
    m->cost = j.at("cost").get<double>();
    return m;
}

