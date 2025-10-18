/**
 * @file admin.hpp
 * @brief Admin class for system administration
 * @author Rana
 * @date 2025
 * 
 * This file contains the Admin class which provides full administrative
 * access to the Airline Management System including user management,
 * flight operations, aircraft management, and system reports.
 */

#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <memory>
#include "user.hpp"

class SystemManager;

/**
 * @class Admin
 * @brief Administrator user with full system access
 * 
 * The Admin class extends User to provide comprehensive administrative
 * capabilities including:
 * - User account management (create, delete, modify)
 * - Flight scheduling and management
 * - Aircraft fleet management
 * - Maintenance scheduling
 * - System-wide reports and analytics
 * 
 * Admins have unrestricted access to all system functions and data.
 * 
 * @note Inherits from User base class
 * @see User, SystemManager, BookingAgent, Passenger
 */
class Admin : public User
{
public:
    /**
     * @brief Constructor for Admin
     * @param username The admin's username for login
     * @param password The admin's password
     * 
     * Creates a new administrator account with full system privileges.
     * Sets the role to "Admin" automatically.
     */
    Admin(string username, string password);

    // ===== USER MANAGEMENT =====
    
    /**
     * @brief Create a new user account
     * @param system Reference to the SystemManager
     * @param role User role: "Admin", "Agent", or "Passenger"
     * @param username Username for the new account
     * @param password Password for the new account
     * @param email Email address for the new user
     * 
     * Creates a new user account in the system with the specified role
     * and credentials. Validates input and ensures username uniqueness.
     */
    void createUser(SystemManager &system, string role, string username,
                    string password, string email);
    
    /**
     * @brief Delete a user account
     * @param system Reference to the SystemManager
     * @param userID The unique ID of the user to delete
     * 
     * Permanently removes a user account from the system.
     * @warning This action cannot be undone
     */
    void deleteUser(SystemManager &system, string userID);
    
    /**
     * @brief View all users in the system
     * @param system Reference to the SystemManager
     * 
     * Displays a comprehensive list of all registered users with their
     * details including ID, username, role, and contact information.
     */
    void viewAllUsers(SystemManager &system);
    
    /**
     * @brief Update user information
     * @param system Reference to the SystemManager
     * @param userID The unique ID of the user to update
     * 
     * Allows modification of user account details such as email,
     * phone, and other profile information.
     */
    void updateUserInfo(SystemManager &system, string userID);

    // ===== FLIGHT MANAGEMENT =====
    
    /**
     * @brief Add a new flight to the system
     * @param system Reference to the SystemManager
     * @param flightNum Flight number (e.g., "AA123")
     * @param origin Departure airport code
     * @param dest Destination airport code
     * @param depTime Departure time (ISO 8601 format)
     * @param arrTime Arrival time (ISO 8601 format)
     * @param aircraftID ID of the assigned aircraft
     * 
     * Creates a new flight schedule with the specified route and timing.
     * Validates aircraft availability and time format.
     */
    void addFlight(SystemManager &system, string flightNum, string origin,
                   string dest, string depTime, string arrTime,
                   string aircraftID);
    
    /**
     * @brief Update existing flight details
     * @param system Reference to the SystemManager
     * @param flightNum Flight number to update
     * 
     * Allows modification of flight schedule, route, aircraft assignment,
     * and other flight parameters.
     */
    void updateFlight(SystemManager &system, string flightNum);
    
    /**
     * @brief Delete a flight from the system
     * @param system Reference to the SystemManager
     * @param flightNum Flight number to delete
     * 
     * Removes a flight from the schedule.
     * @warning Cancels all associated reservations
     */
    void deleteFlight(SystemManager &system, string flightNum);
    
    /**
     * @brief View all flights in the system
     * @param system Reference to the SystemManager
     * 
     * Displays a comprehensive list of all scheduled flights with
     * details including route, timing, status, and aircraft.
     */
    void viewAllFlights(SystemManager &system);
    
    /**
     * @brief Assign or change aircraft for a flight
     * @param system Reference to the SystemManager
     * @param flightNum Flight number
     * @param aircraftID ID of the aircraft to assign
     * 
     * Associates an aircraft with a flight, updating seat availability
     * based on aircraft configuration.
     */
    void assignAircraftToFlight(SystemManager &system, string flightNum,
                                string aircraftID);

    // ===== AIRCRAFT MANAGEMENT =====
    
    /**
     * @brief Add a new aircraft to the fleet
     * @param system Reference to the SystemManager
     * @param model Aircraft model (e.g., "Boeing 737")
     * @param manufacturer Aircraft manufacturer
     * @param economy Number of economy class seats
     * @param business Number of business class seats
     * @param first Number of first class seats
     * 
     * Registers a new aircraft in the system with its seat configuration.
     * Automatically generates a unique aircraft ID.
     */
    void addAircraft(SystemManager &system, string model, string manufacturer,
                     int economy, int business, int first);
    
    /**
     * @brief Remove an aircraft from the fleet
     * @param system Reference to the SystemManager
     * @param aircraftID ID of the aircraft to remove
     * 
     * Removes an aircraft from the system.
     * @warning Cannot remove aircraft assigned to active flights
     */
    void removeAircraft(SystemManager &system, string aircraftID);
    
    /**
     * @brief View all aircraft in the fleet
     * @param system Reference to the SystemManager
     * 
     * Displays complete fleet information including aircraft details,
     * status, maintenance history, and flight hours.
     */
    void viewAllAircraft(SystemManager &system);

    // ===== MAINTENANCE MANAGEMENT =====
    
    /**
     * @brief Schedule maintenance for an aircraft
     * @param system Reference to the SystemManager
     * @param aircraftID ID of the aircraft requiring maintenance
     * @param type Maintenance type: "Routine", "Inspection", or "Repair"
     * @param date Scheduled maintenance date
     * 
     * Creates a maintenance schedule entry for the specified aircraft.
     * Aircraft status is updated to prevent flight assignment during maintenance.
     */
    void scheduleMaintenanceForAircraft(SystemManager &system,
                                        string aircraftID, string type, string date);
    
    /**
     * @brief View maintenance schedule
     * @param system Reference to the SystemManager
     * 
     * Displays all scheduled, in-progress, and completed maintenance
     * activities with dates, status, and aircraft information.
     */
    void viewMaintenanceSchedule(SystemManager &system);

    // ===== REPORTS =====
    
    /**
     * @brief Generate comprehensive flight report
     * @param system Reference to the SystemManager
     * 
     * Produces detailed statistics on flights including:
     * - Total flights scheduled
     * - On-time performance
     * - Cancellation rates
     * - Popular routes
     */
    void generateFlightReport(SystemManager &system);
    
    /**
     * @brief Generate revenue report
     * @param system Reference to the SystemManager
     * 
     * Produces financial analysis including:
     * - Total revenue
     * - Revenue by flight
     * - Revenue by seat class
     * - Payment method breakdown
     */
    void generateRevenueReport(SystemManager &system);
    
    /**
     * @brief Generate maintenance report
     * @param system Reference to the SystemManager
     * 
     * Produces maintenance statistics including:
     * - Maintenance costs
     * - Aircraft downtime
     * - Maintenance frequency
     * - Overdue maintenance
     */
    void generateMaintenanceReport(SystemManager &system);
    
    /**
     * @brief Generate user activity report
     * @param system Reference to the SystemManager
     * 
     * Produces user statistics including:
     * - Total users by role
     * - Active users
     * - Registration trends
     * - Booking agent performance
     */
    void generateUserActivityReport(SystemManager &system);
    
    /**
     * @brief Display overall system status
     * @param system Reference to the SystemManager
     * 
     * Shows real-time system overview including active flights,
     * current bookings, fleet status, and pending maintenance.
     */
    void displaySystemStatus(SystemManager &system);

    /**
     * @brief Display admin menu
     * 
     * Overrides User::showMenu() to display admin-specific menu options.
     */
    void showMenu() override;

    /**
     * @brief Serialize admin to JSON
     * @return JSON object containing admin data
     * 
     * Converts the admin object to JSON format for persistence.
     * Includes all user fields plus admin-specific data.
     */
    json toJson() const override;
    
    /**
     * @brief Deserialize admin from JSON
     * @param j JSON object containing admin data
     * @return Shared pointer to created Admin object
     * 
     * Creates an Admin object from stored JSON data.
     */
    static shared_ptr<Admin> fromJson(const json &j);
};

#endif // ADMIN_HPP