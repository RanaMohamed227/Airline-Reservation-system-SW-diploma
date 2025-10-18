/**
 * @file systemmanager.hpp
 * @brief SystemManager class 
 * @author Rana
 * @date 2025
 * 
 * This file contains the SystemManager class which serves as the central
 * management for the entire Airline Management System. It coordinates
 * all operations including user management, flight scheduling, aircraft fleet,
 * reservations, payments, and maintenance tracking with JSON persistence.
 */

#ifndef SYSTEMMANAGER_HPP
#define SYSTEMMANAGER_HPP

#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include "User.hpp"
#include "Admin.hpp"
#include "BookingAgent.hpp"
#include "Passenger.hpp"
#include "Aircraft.hpp"
#include "Flight.hpp"
#include "Reservation.hpp"
#include "Payment.hpp"
#include "Maintenance.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

/**
 * @class SystemManager
 * @brief Central management system 
 * 
 * The SystemManager class is the core of the Airline Management System,
 * provide a unified interface
 * for all system operations:
 * 
 * - **User Management**: Authentication, registration, profile management
 * - **Aircraft Management**: Fleet tracking, availability, maintenance
 * - **Flight Management**: Scheduling, status updates, seat management
 * - **Reservation Management**: Booking lifecycle, modifications, cancellations
 * - **Payment Management**: Transaction processing, revenue tracking
 * - **Maintenance Management**: Scheduling, tracking, compliance
 * - **Data Persistence**: JSON-based save/load operations
 * - **Reports & Analytics**: System-wide statistics and insights
 * 
 * All data is stored in memory during runtime and persisted to JSON
 * files in the data/ directory for permanent storage.
 * 
 * 
 * @see User, Aircraft, Flight, Reservation, Payment, Maintenance
 */
class SystemManager
{
private:
    // Data storage
    vector<shared_ptr<User>> users;            ///< All system users
    vector<shared_ptr<Aircraft>> aircraft;     ///< Aircraft fleet
    vector<shared_ptr<Flight>> flights;        ///< All flights
    vector<shared_ptr<Reservation>> reservations;  ///< All reservations
    vector<shared_ptr<Payment>> payments;      ///< All payments
    vector<shared_ptr<Maintenance>> maintenanceRecords;  ///< Maintenance history

    // Current logged-in user
    shared_ptr<User> currentUser;  ///< Currently authenticated user

public:
    /**
     * @brief Constructor for SystemManager
     * 
     * Initializes the system manager and creates the data directory
     * structure if it doesn't exist. Loads existing data from JSON files.
     */
    SystemManager();

    // ===== USER MANAGEMENT =====
    
    /**
     * @brief Register a new user
     * @param role User role: "Admin", "Agent", or "Passenger"
     * @param username Desired username (must be unique)
     * @param password User password
     * @param email Email address
     * @param phone Phone number
     * @return true if registration successful, false if username exists
     * 
     * Creates a new user account in the system. Validates uniqueness
     * of username and creates appropriate User subclass based on role.
     */
    bool registerUser(string role, string username, string password,
                      string email, string phone);
    
    /**
     * @brief Authenticate user login
     * @param username Username for login
     * @param password Password for authentication
     * @return Shared pointer to User if successful, nullptr if failed
     * 
     * Validates credentials and sets currentUser if authentication succeeds.
     */
    shared_ptr<User> authenticateUser(string username, string password);
    
    /**
     * @brief Logout current user
     * 
     * Clears the currentUser pointer, ending the session.
     */
    void logoutUser();
    
    /**
     * @brief Get current logged-in user
     * @return Shared pointer to current user, or nullptr if not logged in
     */
    shared_ptr<User> getCurrentUser() const;
    
    /**
     * @brief Find user by ID
     * @param userID User identifier to search for
     * @return Shared pointer to User if found, nullptr otherwise
     */
    shared_ptr<User> findUserByID(string userID);
    
    /**
     * @brief Find user by username
     * @param username Username to search for
     * @return Shared pointer to User if found, nullptr otherwise
     */
    shared_ptr<User> findUserByUsername(string username);
    
    /**
     * @brief Get all users
     * @return Vector of all user shared pointers
     */
    vector<shared_ptr<User>> getAllUsers() const;
    
    /**
     * @brief Delete a user account
     * @param userID ID of user to delete
     * @return true if deletion successful, false if user not found
     * 
     * Permanently removes user from the system.
     * @warning This action cannot be undone
     */
    bool deleteUser(string userID);
    
    /**
     * @brief Display all users
     * 
     * Shows list of all registered users with basic information.
     */
    void displayAllUsers();

    // ===== AIRCRAFT MANAGEMENT =====
    
    /**
     * @brief Add aircraft to fleet
     * @param aircraft Shared pointer to Aircraft object
     * 
     * Adds a new aircraft to the fleet management system.
     */
    void addAircraft(shared_ptr<Aircraft> aircraft);
    
    /**
     * @brief Find aircraft by ID
     * @param aircraftID Aircraft identifier
     * @return Shared pointer to Aircraft if found, nullptr otherwise
     */
    shared_ptr<Aircraft> findAircraftByID(string aircraftID);
    
    /**
     * @brief Get available aircraft
     * @return Vector of aircraft with "Available" status
     * 
     * Returns only aircraft that can be assigned to flights.
     */
    vector<shared_ptr<Aircraft>> getAvailableAircraft();
    
    /**
     * @brief Get all aircraft
     * @return Vector of all aircraft in fleet
     */
    vector<shared_ptr<Aircraft>> getAllAircraft() const;
    
    /**
     * @brief Remove aircraft from fleet
     * @param aircraftID ID of aircraft to remove
     * @return true if removal successful, false if not found
     * 
     * @warning Cannot remove aircraft assigned to active flights
     */
    bool removeAircraft(string aircraftID);
    
    /**
     * @brief Display all aircraft
     * 
     * Shows complete fleet listing with specifications and status.
     */
    void displayAllAircraft();

    // ===== FLIGHT MANAGEMENT =====
    
    /**
     * @brief Add flight to schedule
     * @param flight Shared pointer to Flight object
     * 
     * Adds a new flight to the system schedule.
     */
    void addFlight(shared_ptr<Flight> flight);
    
    /**
     * @brief Find flight by number
     * @param flightNum Flight number to search
     * @return Shared pointer to Flight if found, nullptr otherwise
     */
    shared_ptr<Flight> findFlightByNumber(string flightNum);
    
    /**
     * @brief Search flights by criteria
     * @param origin Departure airport code
     * @param dest Destination airport code
     * @param date Departure date (YYYY-MM-DD)
     * @return Vector of matching flights
     * 
     * Searches for flights matching the specified route and date.
     */
    vector<shared_ptr<Flight>> searchFlights(string origin, string dest, string date);
    
    /**
     * @brief Get all flights
     * @return Vector of all scheduled flights
     */
    vector<shared_ptr<Flight>> getAllFlights() const;
    
    /**
     * @brief Delete a flight
     * @param flightNum Flight number to delete
     * @return true if deletion successful, false if not found
     * 
     * Removes flight from schedule. Associated reservations should be cancelled.
     */
    bool deleteFlight(string flightNum);
    
    /**
     * @brief Update flight status
     * @param flightNum Flight number
     * @param status New status value
     * 
     * Updates the status of a flight (e.g., Boarding, Departed, Delayed).
     */
    void updateFlightStatus(string flightNum, string status);
    
    /**
     * @brief Display all flights
     * 
     * Shows complete flight schedule with details.
     */
    void displayAllFlights();

    // ===== RESERVATION MANAGEMENT =====
    
    /**
     * @brief Add reservation to system
     * @param reservation Shared pointer to Reservation object
     * 
     * Registers a new booking in the system.
     */
    void addReservation(shared_ptr<Reservation> reservation);
    
    /**
     * @brief Find reservation by ID
     * @param reservationID Reservation identifier
     * @return Shared pointer to Reservation if found, nullptr otherwise
     */
    shared_ptr<Reservation> findReservationByID(string reservationID);
    
    /**
     * @brief Get reservations by passenger
     * @param passengerID Passenger identifier
     * @return Vector of reservations for the passenger
     */
    vector<shared_ptr<Reservation>> getReservationsByPassenger(string passengerID);
    
    /**
     * @brief Get reservations by flight
     * @param flightNum Flight number
     * @return Vector of reservations for the flight
     */
    vector<shared_ptr<Reservation>> getReservationsByFlight(string flightNum);
    
    /**
     * @brief Cancel a reservation
     * @param reservationID ID of reservation to cancel
     * @return true if cancellation successful, false if not found
     * 
     * Cancels the reservation, releases seats, initiates refund if applicable.
     */
    bool cancelReservation(string reservationID);
    
    /**
     * @brief Display all reservations
     * 
     * Shows list of all bookings with key information.
     */
    void displayAllReservations();

    // ===== PAYMENT MANAGEMENT =====
    
    /**
     * @brief Add payment record
     * @param payment Shared pointer to Payment object
     * 
     * Registers a payment transaction in the system.
     */
    void addPayment(shared_ptr<Payment> payment);
    
    /**
     * @brief Find payment by ID
     * @param paymentID Payment identifier
     * @return Shared pointer to Payment if found, nullptr otherwise
     */
    shared_ptr<Payment> findPaymentByID(string paymentID);
    
    /**
     * @brief Find payment by reservation
     * @param reservationID Reservation identifier
     * @return Shared pointer to Payment if found, nullptr otherwise
     */
    shared_ptr<Payment> findPaymentByReservation(string reservationID);
    
    /**
     * @brief Get all payments
     * @return Vector of all payment records
     */
    vector<shared_ptr<Payment>> getAllPayments() const;
    
    /**
     * @brief Calculate total revenue
     * @return Total revenue from all completed payments
     * 
     * Sums all successful (completed) payments minus refunds.
     */
    double getTotalRevenue();

    // ===== MAINTENANCE MANAGEMENT =====
    
    /**
     * @brief Add maintenance record
     * @param maintenance Shared pointer to Maintenance object
     * 
     * Registers a maintenance activity in the system.
     */
    void addMaintenanceRecord(shared_ptr<Maintenance> maintenance);
    
    /**
     * @brief Find maintenance by ID
     * @param maintenanceID Maintenance identifier
     * @return Shared pointer to Maintenance if found, nullptr otherwise
     */
    shared_ptr<Maintenance> findMaintenanceByID(string maintenanceID);
    
    /**
     * @brief Get maintenance records by aircraft
     * @param aircraftID Aircraft identifier
     * @return Vector of maintenance records for the aircraft
     */
    vector<shared_ptr<Maintenance>> getMaintenanceByAircraft(string aircraftID);
    
    /**
     * @brief Get scheduled maintenance
     * @return Vector of maintenance records with "Scheduled" status
     */
    vector<shared_ptr<Maintenance>> getScheduledMaintenance();
    
    /**
     * @brief Get overdue maintenance
     * @return Vector of maintenance records past scheduled date
     * 
     * Critical for safety and compliance monitoring.
     */
    vector<shared_ptr<Maintenance>> getOverdueMaintenance();

    // ===== FILE OPERATIONS (JSON Persistence) =====
    
    /**
     * @brief Save all data to files
     * 
     * Convenience method that calls all individual save methods.
     */
    void saveAllData();
    
    /**
     * @brief Load all data from files
     * 
     * Convenience method that calls all individual load methods.
     */
    void loadAllData();

    /**
     * @brief Save users to JSON file
     * @param filename Output file path (default: data/users.json)
     */
    void saveUsers(string filename = "data/users.json");
    
    /**
     * @brief Save aircraft to JSON file
     * @param filename Output file path (default: data/aircraft.json)
     */
    void saveAircraft(string filename = "data/aircraft.json");
    
    /**
     * @brief Save flights to JSON file
     * @param filename Output file path (default: data/flights.json)
     */
    void saveFlights(string filename = "data/flights.json");
    
    /**
     * @brief Save reservations to JSON file
     * @param filename Output file path (default: data/reservations.json)
     */
    void saveReservations(string filename = "data/reservations.json");
    
    /**
     * @brief Save payments to JSON file
     * @param filename Output file path (default: data/payments.json)
     */
    void savePayments(string filename = "data/payments.json");
    
    /**
     * @brief Save maintenance records to JSON file
     * @param filename Output file path (default: data/maintenance.json)
     */
    void saveMaintenance(string filename = "data/maintenance.json");

    /**
     * @brief Load users from JSON file
     * @param filename Input file path (default: data/users.json)
     * 
     * Loads all user accounts from persistent storage.
     * Creates appropriate User subclass based on role field.
     */
    void loadUsers(string filename = "data/users.json");
    
    /**
     * @brief Load aircraft from JSON file
     * @param filename Input file path (default: data/aircraft.json)
     */
    void loadAircraft(string filename = "data/aircraft.json");
    
    /**
     * @brief Load flights from JSON file
     * @param filename Input file path (default: data/flights.json)
     */
    void loadFlights(string filename = "data/flights.json");
    
    /**
     * @brief Load reservations from JSON file
     * @param filename Input file path (default: data/reservations.json)
     */
    void loadReservations(string filename = "data/reservations.json");
    
    /**
     * @brief Load payments from JSON file
     * @param filename Input file path (default: data/payments.json)
     */
    void loadPayments(string filename = "data/payments.json");
    
    /**
     * @brief Load maintenance records from JSON file
     * @param filename Input file path (default: data/maintenance.json)
     */
    void loadMaintenance(string filename = "data/maintenance.json");

    // ===== REPORTS & ANALYTICS =====
    
    /**
     * @brief Generate comprehensive flight report
     * 
     * Produces detailed statistics including:
     * - Total flights scheduled
     * - Flights by status (Scheduled, Departed, Arrived, Cancelled)
     * - On-time performance metrics
     * - Cancellation rates
     * - Most popular routes
     * - Average seat occupancy
     */
    void generateFlightReport();
    
    /**
     * @brief Generate revenue report
     * 
     * Produces financial analysis including:
     * - Total revenue (completed payments)
     * - Revenue by time period
     * - Revenue by flight route
     * - Revenue by seat class
     * - Payment method distribution
     * - Refunds processed
     * - Average ticket price
     */
    void generateRevenueReport();
    
    /**
     * @brief Generate maintenance report
     * 
     * Produces maintenance statistics including:
     * - Total maintenance activities
     * - Maintenance by type (Routine, Inspection, Repair)
     * - Total maintenance costs
     * - Average maintenance duration
     * - Aircraft downtime analysis
     * - Overdue maintenance alerts
     * - Parts replacement frequency
     */
    void generateMaintenanceReport();
    
    /**
     * @brief Generate user activity report
     * 
     * Produces user statistics including:
     * - Total users by role
     * - Active vs inactive users
     * - Recent registrations
     * - Booking agent performance (bookings processed)
     * - Passenger loyalty tier distribution
     * - Most active passengers
     */
    void generateUserActivityReport();
    
    /**
     * @brief Display system status overview
     * 
     * Shows real-time system dashboard with:
     * - Active flights (in-air, boarding)
     * - Pending reservations
     * - Today's revenue
     * - Fleet availability status
     * - Maintenance due/overdue
     * - System health indicators
     */
    void displaySystemStatus();

    // ===== UTILITY =====
    
    /**
     * @brief Initialize data directory structure
     * 
     * Creates the data/ directory if it doesn't exist.
     * Called automatically during SystemManager construction.
     * Ensures all JSON files can be saved successfully.
     */
    void initializeDataDirectory();
};

#endif // SYSTEMMANAGER_HPP