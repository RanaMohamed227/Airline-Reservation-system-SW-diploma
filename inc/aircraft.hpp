/**
 * @file aircraft.hpp
 * @brief Aircraft class for fleet management
 * @author Rana
 * @date 2025
 * 
 * This file contains the Aircraft class which manages individual aircraft
 * in the fleet including specifications, seat configuration, maintenance
 * tracking, and operational status.
 */

#ifndef AIRCRAFT_HPP
#define AIRCRAFT_HPP

#include <memory>
#include <vector>
#include <string>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/**
 * @class Aircraft
 * @brief Represents an aircraft in the airline fleet
 * 
 * The Aircraft class manages all aspects of an individual aircraft:
 * - Basic specifications (model, manufacturer)
 * - Seat configuration across multiple classes
 * - Operational status and availability
 * - Flight hours tracking
 * - Maintenance scheduling and history
 * 
 * Aircraft status determines availability for flight assignment.
 * Maintenance is required every 500 flight hours to ensure safety
 * and regulatory compliance.
 * 
 * @note Maintenance intervals should be strictly monitored
 * @see Flight, Maintenance, SystemManager
 */
class Aircraft
{
private:
    string aircraftID;       ///< Unique aircraft identifier
    string model;            ///< Aircraft model (e.g., "Boeing 737-800")
    string manufacturer;     ///< Manufacturer name (e.g., "Boeing", "Airbus")

    // Seat configuration
    int totalSeats;          ///< Total number of seats
    int economySeats;        ///< Number of economy class seats
    int businessSeats;       ///< Number of business class seats
    int firstClassSeats;     ///< Number of first class seats

    // Status
    string status;           ///< Status: "Available", "InUse", "Maintenance"
    int flightHours;         ///< Total accumulated flight hours
    int hoursSinceMaintenance;  ///< Hours flown since last maintenance

    // Maintenance
    string lastMaintenanceDate;  ///< Date of last maintenance (YYYY-MM-DD)
    string nextMaintenanceDate;  ///< Scheduled next maintenance date
    vector<string> maintenanceRecordIDs;  ///< List of maintenance record IDs

public:
    /**
     * @brief Constructor for Aircraft
     * @param model Aircraft model designation
     * @param manufacturer Name of the manufacturer
     * @param economy Number of economy class seats
     * @param business Number of business class seats
     * @param first Number of first class seats
     * 
     * Creates a new aircraft with the specified configuration.
     * Total seats is calculated automatically. Status is set to "Available"
     * and flight hours initialized to 0.
     */
    Aircraft(string model, string manufacturer, int economy,
             int business, int first);

    // ===== BASIC INFO GETTERS =====
    
    /**
     * @brief Get aircraft ID
     * @return Unique aircraft identifier
     */
    string getAircraftID() const { return aircraftID; }
    
    /**
     * @brief Get aircraft model
     * @return Model designation
     */
    string getModel() const { return model; }
    
    /**
     * @brief Get manufacturer
     * @return Manufacturer name
     */
    string getManufacturer() const { return manufacturer; }
    
    /**
     * @brief Get current status
     * @return Status: "Available", "InUse", or "Maintenance"
     */
    string getStatus() const { return status; }

    // ===== SEAT INFO GETTERS =====
    
    /**
     * @brief Get total seat count
     * @return Total number of seats
     */
    int getTotalSeats() const { return totalSeats; }
    
    /**
     * @brief Get economy seat count
     * @return Number of economy class seats
     */
    int getEconomySeats() const { return economySeats; }
    
    /**
     * @brief Get business seat count
     * @return Number of business class seats
     */
    int getBusinessSeats() const { return businessSeats; }
    
    /**
     * @brief Get first class seat count
     * @return Number of first class seats
     */
    int getFirstClassSeats() const { return firstClassSeats; }

    // ===== FLIGHT HOURS =====
    
    /**
     * @brief Get total flight hours
     * @return Accumulated flight hours
     */
    int getFlightHours() const { return flightHours; }
    
    /**
     * @brief Get hours since maintenance
     * @return Flight hours since last maintenance
     */
    int getHoursSinceMaintenance() const { return hoursSinceMaintenance; }
    
    /**
     * @brief Add flight hours
     * @param hours Number of hours to add
     * 
     * Increments both total flight hours and hours since maintenance.
     * Should be called when a flight using this aircraft is completed.
     * 
     * @note Triggers maintenance requirement check if hours exceed 500
     */
    void addFlightHours(int hours);

    // ===== MAINTENANCE INFO =====
    
    /**
     * @brief Get last maintenance date
     * @return Date of last maintenance (YYYY-MM-DD format)
     */
    string getLastMaintenanceDate() const { return lastMaintenanceDate; }
    
    /**
     * @brief Get next maintenance date
     * @return Scheduled next maintenance date
     */
    string getNextMaintenanceDate() const { return nextMaintenanceDate; }
    
    /**
     * @brief Get maintenance history
     * @return Vector of maintenance record IDs
     */
    vector<string> getMaintenanceHistory() const { return maintenanceRecordIDs; }

    // ===== STATUS MANAGEMENT =====
    
    /**
     * @brief Set aircraft status
     * @param newStatus New status: "Available", "InUse", or "Maintenance"
     * 
     * Updates the operational status of the aircraft.
     * - "Available": Ready for flight assignment
     * - "InUse": Currently assigned to a flight
     * - "Maintenance": Undergoing maintenance, unavailable
     */
    void setStatus(string newStatus);
    
    /**
     * @brief Check if aircraft is available
     * @return true if status is "Available"
     * 
     * Convenience method to check availability for flight assignment.
     */
    bool isAvailable() const;

    // ===== MAINTENANCE OPERATIONS =====
    
    /**
     * @brief Check if maintenance is needed
     * @return true if hours since maintenance exceed 500
     * 
     * Aircraft require mandatory maintenance every 500 flight hours
     * for safety and regulatory compliance.
     */
    bool needsMaintenance() const;
    
    /**
     * @brief Schedule next maintenance
     * @param date Date for next scheduled maintenance (YYYY-MM-DD)
     * 
     * Sets the next maintenance date. Used for planning and
     * preventing over-utilization.
     */
    void scheduleNextMaintenance(string date);
    
    /**
     * @brief Record maintenance activity
     * @param maintenanceID ID of the maintenance record
     * 
     * Adds a maintenance record to the aircraft's history.
     * Links aircraft to maintenance records for tracking.
     */
    void recordMaintenance(string maintenanceID);
    
    /**
     * @brief Mark maintenance as performed
     * 
     * Resets hours since maintenance to 0, updates last maintenance date
     * to current date, and sets status back to "Available".
     * Called when maintenance is completed.
     */
    void performedMaintenance();

    // ===== DISPLAY =====
    
    /**
     * @brief Display aircraft information
     * 
     * Shows basic aircraft details including ID, model, manufacturer,
     * seat configuration, and current status.
     */
    void displayInfo();
    
    /**
     * @brief Display maintenance status
     * 
     * Shows maintenance-related information including:
     * - Flight hours and hours since maintenance
     * - Last and next maintenance dates
     * - Maintenance requirement status
     * - Maintenance history
     */
    void displayMaintenanceStatus();

    // ===== SERIALIZATION =====
    
    /**
     * @brief Serialize aircraft to JSON
     * @return JSON object containing complete aircraft data
     * 
     * Converts aircraft object to JSON for persistence including
     * all specifications, status, and maintenance information.
     */
    json toJson() const;
    
    /**
     * @brief Deserialize aircraft from JSON
     * @param j JSON object containing aircraft data
     * @return Shared pointer to created Aircraft object
     */
    static shared_ptr<Aircraft> fromJson(const json &j);
};

#endif // AIRCRAFT_HPP