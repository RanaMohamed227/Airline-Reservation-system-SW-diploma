/**
 * @file bookingagent.hpp
 * @brief BookingAgent class for customer service operations
 * @author Rana
 * @date 2025
 * 
 * This file contains the BookingAgent class which handles customer-facing
 * booking operations including flight search, reservation management,
 * payment processing, and check-in services.
 */

#ifndef BOOKINGAGENT_HPP
#define BOOKINGAGENT_HPP

#include "user.hpp"
#include <memory>
#include <vector>
#include <string>

using namespace std;

class SystemManager;
class Flight;
class Passenger;

/**
 * @class BookingAgent
 * @brief Customer service agent for booking operations
 * 
 * The BookingAgent class extends User to provide customer service
 * functionality including:
 * - Flight search and availability checking
 * - Booking creation and modification
 * - Payment processing
 * - Check-in services
 * - Boarding pass generation
 * 
 * Agents assist passengers with bookings and earn performance
 * metrics based on number of bookings processed.
 * 
 * @note Inherits from User base class
 * @see User, Reservation, Flight, Payment, SystemManager
 */
class BookingAgent : public User
{
private:
    int bookingsProcessed;  ///< Total number of bookings processed by this agent

public:
    /**
     * @brief Constructor for BookingAgent
     * @param username The agent's username for login
     * @param password The agent's password
     * 
     * Creates a new booking agent account with customer service privileges.
     * Initializes bookingsProcessed counter to 0.
     */
    BookingAgent(string username, string password);

    // ===== FLIGHT SEARCH =====
    
    /**
     * @brief Search for flights
     * @param system Reference to the SystemManager
     * @param origin Departure airport code (e.g., "JFK")
     * @param dest Destination airport code (e.g., "LAX")
     * @param date Departure date (YYYY-MM-DD format)
     * 
     * Searches and displays all available flights matching the search criteria.
     * Shows comprehensive flight details including available seats and pricing.
     */
    void searchFlights(SystemManager &system, string origin, string dest,
                       string date);
    
    /**
     * @brief Display available flights
     * @param flights Vector of Flight shared pointers to display
     * 
     * Presents flight information in a user-friendly format including:
     * - Flight number and route
     * - Departure and arrival times
     * - Available seats by class
     * - Pricing for each class
     * - Current flight status
     */
    void displayAvailableFlights(const vector<shared_ptr<Flight>> &flights);

    // ===== BOOKING OPERATIONS =====
    
    /**
     * @brief Create a new booking for a passenger
     * @param system Reference to the SystemManager
     * @param passengerID The passenger's unique ID
     * @param flightNum Flight number to book
     * @param seats Vector of seat numbers (e.g., {"12A", "12B"})
     * 
     * Creates a new reservation for the specified passenger and flight.
     * Validates seat availability, calculates total cost, and applies
     * any applicable discounts. Increments agent's bookingsProcessed counter.
     * 
     * @note Payment must be processed separately
     * @see processPayment()
     */
    void createBooking(SystemManager &system, string passengerID,
                       string flightNum, vector<string> seats);
    
    /**
     * @brief Modify an existing booking
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID to modify
     * 
     * Allows modification of an existing reservation such as:
     * - Changing seats
     * - Adding/removing seats
     * - Updating passenger preferences
     * 
     * @note Cannot modify confirmed reservations after check-in
     */
    void modifyBooking(SystemManager &system, string reservationID);
    
    /**
     * @brief Cancel a booking
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID to cancel
     * 
     * Cancels the specified reservation, releases booked seats,
     * and initiates refund process if payment was completed.
     * 
     * @see Payment::refund()
     */
    void cancelBooking(SystemManager &system, string reservationID);
    
    /**
     * @brief View booking details
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID to view
     * 
     * Displays comprehensive booking information including:
     * - Passenger details
     * - Flight information
     * - Seat assignments
     * - Payment status
     * - Check-in status
     */
    void viewBooking(SystemManager &system, string reservationID);
    
    /**
     * @brief View all bookings in the system
     * @param system Reference to the SystemManager
     * 
     * Displays a list of all reservations with key details.
     * Useful for monitoring and reporting purposes.
     */
    void viewAllBookings(SystemManager &system);

    // ===== PAYMENT PROCESSING =====
    
    /**
     * @brief Process payment for a reservation
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID to process payment for
     * @param method Payment method: "CreditCard", "DebitCard", or "Cash"
     * @param amount Payment amount
     * 
     * Processes payment for the specified reservation. Validates amount
     * against reservation total, creates payment record, and updates
     * reservation status to "Confirmed" upon successful payment.
     * 
     * @return Payment is processed immediately (simulated)
     * @see Payment
     */
    void processPayment(SystemManager &system, string reservationID,
                        string method, double amount);

    // ===== CHECK-IN SERVICES =====
    
    /**
     * @brief Check in a passenger
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID to check in
     * 
     * Performs online check-in for the passenger. Available 24 hours
     * before flight departure. Updates reservation status to "CheckedIn"
     * and generates boarding pass.
     * 
     * @note Requires confirmed reservation with completed payment
     * @see generateBoardingPass()
     */
    void checkInPassenger(SystemManager &system, string reservationID);
    
    /**
     * @brief Print boarding pass
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID
     * 
     * Generates and displays boarding pass information including:
     * - Passenger name and passport number
     * - Flight details and gate
     * - Seat assignments
     * - Boarding time
     * - Barcode/QR code (simulated)
     * 
     * @note Passenger must be checked in
     */
    void printBoardingPass(SystemManager &system, string reservationID);
    
    /**
     * @brief Select seat for a passenger
     * @param system Reference to the SystemManager
     * @param reservationID The reservation ID
     * @param seatNum The seat number to assign (e.g., "12A")
     * 
     * Assigns or changes seat for a reservation. Validates seat
     * availability and class matching with booking.
     * 
     * @note Cannot change seats after check-in without agent override
     */
    void selectSeatForPassenger(SystemManager &system, string reservationID,
                                string seatNum);

    // ===== PERFORMANCE METRICS =====
    
    /**
     * @brief Get number of bookings processed
     * @return Total bookings processed by this agent
     * 
     * Returns the performance metric for this agent.
     * Used for agent evaluation and commission calculation.
     */
    int getBookingsProcessed() const { return bookingsProcessed; }
    
    /**
     * @brief Increment bookings counter
     * 
     * Increments the bookingsProcessed counter by 1.
     * Called automatically when a new booking is created.
     */
    void incrementBookings() { bookingsProcessed++; }

    /**
     * @brief Display booking agent menu
     * 
     * Overrides User::showMenu() to display agent-specific menu options
     * including search, booking operations, payment processing, and check-in.
     */
    void showMenu() override;

    /**
     * @brief Serialize booking agent to JSON
     * @return JSON object containing agent data
     * 
     * Converts the agent object to JSON format for persistence.
     * Includes user fields plus agent-specific data such as
     * bookingsProcessed count.
     */
    json toJson() const override;

    /**
     * @brief Deserialize booking agent from JSON
     * @param j JSON object containing agent data
     * @return Shared pointer to created BookingAgent object
     * 
     * Creates a BookingAgent object from stored JSON data.
     */
    static shared_ptr<BookingAgent> fromJson(const json &j);
};

#endif // BOOKINGAGENT_HPP