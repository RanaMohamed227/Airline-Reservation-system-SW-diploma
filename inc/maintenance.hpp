/**
 * @file maintenance.hpp
 * @brief Maintenance class for aircraft maintenance tracking
 * @author Your Name
 * @date 2025
 * 
 * This file contains the Maintenance class which manages aircraft
 * maintenance scheduling, tracking, and history including routine
 * maintenance, inspections, repairs, parts replacement, and cost management.
 */

#ifndef MAINTENANCE_HPP
#define MAINTENANCE_HPP

#include <string>
#include <iostream>
#include <vector>
#include <memory>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/**
 * @class Maintenance
 * @brief Manages aircraft maintenance activities
 * 
 * The Maintenance class tracks all maintenance activities for aircraft:
 * - Routine maintenance (scheduled every 500 flight hours)
 * - Inspections (regulatory and safety checks)
 * - Repairs (unscheduled maintenance for issues)
 * - Parts replacement tracking
 * - Cost and duration recording
 * - Technician assignment
 * 
 * Maintenance records progress through states:
 * - Scheduled: Maintenance planned but not started
 * - InProgress: Currently being performed
 * - Completed: Maintenance finished
 * 
 * Aircraft should be unavailable for flights during maintenance.
 * 
 * @note Critical for regulatory compliance and safety
 * @see Aircraft, SystemManager
 */
class Maintenance
{
private:
    string maintenanceID;    ///< Unique maintenance record identifier
    string aircraftID;       ///< ID of aircraft being maintained
    
    // Type and scheduling
    string type;             ///< Type: "Routine", "Inspection", "Repair"
    string scheduledDate;    ///< Scheduled maintenance date (YYYY-MM-DD)
    string completedDate;    ///< Actual completion date (empty if not completed)
    
    // Status
    string status;           ///< Status: "Scheduled", "InProgress", "Completed"
    
    // Details
    string description;      ///< Description of maintenance work
    vector<string> partsReplaced;  ///< List of parts replaced during maintenance
    string technicianName;   ///< Name of assigned technician
    int durationHours;       ///< Duration of maintenance in hours
    double cost;             ///< Total cost of maintenance

public:
    /**
     * @brief Constructor for Maintenance
     * @param aircraftID ID of the aircraft requiring maintenance
     * @param type Maintenance type: "Routine", "Inspection", or "Repair"
     * @param scheduled Scheduled date (YYYY-MM-DD format)
     * 
     * Creates a new maintenance record with "Scheduled" status.
     * Maintenance ID is generated automatically. Duration and cost
     * are recorded when maintenance is completed.
     */
    Maintenance(string aircraftID, string type, string scheduled);
    
    // ===== GETTERS =====
    
    /**
     * @brief Get maintenance ID
     * @return Unique maintenance record identifier
     */
    string getMaintenanceID() const { return maintenanceID; }
    
    /**
     * @brief Get aircraft ID
     * @return ID of aircraft being maintained
     */
    string getAircraftID() const { return aircraftID; }
    
    /**
     * @brief Get maintenance status
     * @return Current status: "Scheduled", "InProgress", or "Completed"
     */
    string getStatus() const { return status; }
    
    /**
     * @brief Get maintenance type
     * @return Type: "Routine", "Inspection", or "Repair"
     */
    string getType() const { return type; }
    
    /**
     * @brief Get scheduled date
     * @return Scheduled maintenance date
     */
    string getScheduledDate() const { return scheduledDate; }
    
    /**
     * @brief Get completion date
     * @return Completion date (empty string if not completed)
     */
    string getCompletedDate() const { return completedDate; }
    
    /**
     * @brief Get maintenance cost
     * @return Total cost in currency units
     */
    double getCost() const { return cost; }
    
    // ===== MAINTENANCE OPERATIONS =====
    
    /**
     * @brief Start maintenance work
     * @param techName Name of the technician performing maintenance
     * 
     * Begins maintenance work. Changes status to "InProgress" and
     * assigns technician. Aircraft status should be set to "Maintenance"
     * by calling function to prevent flight assignment.
     */
    void startMaintenance(string techName);
    
    /**
     * @brief Add replaced part to record
     * @param part Name/description of the replaced part
     * 
     * Records a part that was replaced during maintenance.
     * Maintains complete history for tracking and compliance.
     */
    void addPartReplaced(string part);
    
    /**
     * @brief Complete maintenance
     * @param hours Duration of maintenance in hours
     * @param cost Total cost of maintenance
     * 
     * Marks maintenance as completed. Records duration, cost, and
     * completion date. Changes status to "Completed". Aircraft status
     * should be updated to "Available" by calling function.
     * 
     * @note Should reset aircraft's hours since maintenance counter
     */
    void complete(int hours, double cost);
    
    /**
     * @brief Reschedule maintenance
     * @param newDate New scheduled date (YYYY-MM-DD)
     * 
     * Changes the scheduled date for maintenance. Can only be
     * rescheduled if status is "Scheduled" (not started).
     */
    void reschedule(string newDate);
    
    // ===== STATUS CHECKS =====
    
    /**
     * @brief Check if maintenance is completed
     * @return true if status is "Completed"
     */
    bool isCompleted() const;
    
    /**
     * @brief Check if maintenance is overdue
     * @return true if scheduled date has passed and not completed
     * 
     * Compares scheduled date with current date to determine if
     * maintenance is overdue. Critical for safety and compliance.
     */
    bool isOverdue() const;
    
    // ===== DISPLAY =====
    
    /**
     * @brief Display detailed maintenance information
     * 
     * Shows comprehensive maintenance record including:
     * - Maintenance and aircraft IDs
     * - Type and status
     * - Scheduled and completion dates
     * - Technician name
     * - Duration and cost
     * - Parts replaced
     * - Description of work performed
     */
    void displayDetails();
    
    /**
     * @brief Display maintenance summary
     * 
     * Shows brief maintenance information suitable for lists:
     * - Maintenance ID and type
     * - Aircraft ID
     * - Scheduled date
     * - Status
     * - Cost (if completed)
     */
    void displaySummary();
    
    // ===== SERIALIZATION =====
    
    /**
     * @brief Serialize maintenance record to JSON
     * @return JSON object containing complete maintenance data
     * 
     * Converts maintenance object to JSON for persistence including
     * all details, parts replaced, and cost information.
     */
    json toJson() const;
    
    /**
     * @brief Deserialize maintenance record from JSON
     * @param j JSON object containing maintenance data
     * @return Shared pointer to created Maintenance object
     */
    static shared_ptr<Maintenance> fromJson(const json &j);
};

#endif // MAINTENANCE_HPP