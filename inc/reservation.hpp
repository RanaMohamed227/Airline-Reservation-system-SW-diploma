/**
 * @file reservation.hpp
 * @brief Reservation class for booking management
 * @author Rana 
 * @date 2025
 * 
 * This file contains the Reservation class which manages the complete
 * lifecycle of a flight booking from creation through check-in to completion,
 * including seat management, pricing, payment tracking, and boarding passes.
 */

#ifndef RESERVATION_HPP
#define RESERVATION_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/**
 * @class Reservation
 * @brief Represents a flight booking reservation
 * 
 * The Reservation class manages the complete booking lifecycle:
 * - Initial booking creation and confirmation
 * - Seat selection and modification
 * - Pricing and discount application
 * - Payment linkage
 * - Check-in processing (24 hours before departure)
 * - Boarding pass generation
 * - Status tracking throughout the journey
 * 
 * Reservations progress through several states:
 * - Pending: Initial booking, awaiting payment
 * - Confirmed: Payment received, booking confirmed
 * - CheckedIn: Passenger has checked in, boarding pass issued
 * - Cancelled: Booking cancelled, seats released
 * - Completed: Journey completed successfully
 * 
 * @note Check-in is only available within 24 hours of departure
 * @see Flight, Payment, Passenger, SystemManager
 */
class Reservation
{
private:
    string reservationID;    ///< Unique reservation identifier
    string passengerID;      ///< ID of the passenger who made the booking
    string flightNumber;     ///< Flight number for this reservation
    vector<string> seatNumbers;  ///< List of booked seat numbers

    // Booking info
    string bookingDate;      ///< Date when booking was created
    string bookedBy;         ///< UserID of who made booking (agent or passenger)

    // Status
    string status;           ///< Status: "Pending", "Confirmed", "CheckedIn", "Cancelled", "Completed"

    // Financial
    double totalAmount;      ///< Total booking amount before discounts
    double discount;         ///< Discount percentage applied (0-100)
    string paymentID;        ///< ID of associated payment

    // Check-in
    bool checkedIn;          ///< Check-in status flag
    string checkInTime;      ///< Time of check-in
    string boardingPassNumber;  ///< Boarding pass identifier

public:
    /**
     * @brief Constructor for Reservation
     * @param passengerID ID of the passenger making the booking
     * @param flightNum Flight number to book
     * @param seats Vector of seat numbers to book
     * @param bookedByUserID ID of user creating the booking (agent or passenger)
     * 
     * Creates a new reservation with "Pending" status. The reservation ID
     * is generated automatically. Booking date is set to current date/time.
     * Total amount should be calculated and set separately.
     */
    Reservation(string passengerID, string flightNum,
                vector<string> seats, string bookedByUserID);

    // ===== GETTERS =====
    
    /**
     * @brief Get reservation ID
     * @return Unique reservation identifier
     */
    string getReservationID() const { return reservationID; }
    
    /**
     * @brief Get passenger ID
     * @return ID of the passenger
     */
    string getPassengerID() const { return passengerID; }
    
    /**
     * @brief Get flight number
     * @return Flight number for this booking
     */
    string getFlightNumber() const { return flightNumber; }
    
    /**
     * @brief Get booked seats
     * @return Vector of seat numbers
     */
    vector<string> getSeats() const { return seatNumbers; }
    
    /**
     * @brief Get reservation status
     * @return Current status
     */
    string getStatus() const { return status; }
    
    /**
     * @brief Get total amount
     * @return Total booking amount before discount
     */
    double getTotalAmount() const { return totalAmount; }
    
    /**
     * @brief Get discount percentage
     * @return Discount percentage (0-100)
     */
    double getDiscount() const { return discount; }
    
    /**
     * @brief Get payment ID
     * @return Associated payment identifier
     */
    string getPaymentID() const { return paymentID; }
    
    /**
     * @brief Get boarding pass number
     * @return Boarding pass identifier (empty if not checked in)
     */
    string getBoardingPassNumber() const { return boardingPassNumber; }
    
    /**
     * @brief Get booking date
     * @return Date and time of booking
     */
    string getBookingDate() const { return bookingDate; }

    // ===== BOOKING OPERATIONS =====
    
    /**
     * @brief Confirm the reservation
     * 
     * Changes status from "Pending" to "Confirmed".
     * Called after successful payment processing.
     */
    void confirm();
    
    /**
     * @brief Cancel the reservation
     * 
     * Changes status to "Cancelled". Booked seats should be released
     * by the calling function. Refund should be initiated if payment
     * was completed.
     */
    void cancel();
    
    /**
     * @brief Modify booked seats
     * @param newSeats New vector of seat numbers
     * @return true if modification successful, false otherwise
     * 
     * Attempts to change the seat selection for this reservation.
     * Fails if reservation is already checked in or completed.
     * Old seats should be released and new seats validated before calling.
     */
    bool modifySeats(vector<string> newSeats);
    
    /**
     * @brief Set seat numbers
     * @param seats Vector of seat numbers
     * 
     * Directly sets the seat numbers. Use with caution.
     * modifySeats() is preferred for seat changes.
     */
    void setSeats(vector<string> seats);

    // ===== PRICING =====
    
    /**
     * @brief Set total amount
     * @param amount Total booking amount
     * 
     * Sets the total price before any discounts.
     * Should be calculated based on seat classes and flight pricing.
     */
    void setTotalAmount(double amount);
    
    /**
     * @brief Apply discount to booking
     * @param discountPercent Discount percentage to apply (0-100)
     * 
     * Applies a discount (e.g., loyalty discount) to the booking.
     * The discount is stored as a percentage for calculation purposes.
     */
    void applyDiscount(double discountPercent);
    
    /**
     * @brief Get final amount after discount
     * @return Final payable amount
     * 
     * Calculates and returns the final amount after applying discount:
     * finalAmount = totalAmount * (1 - discount/100)
     */
    double getFinalAmount() const;

    // ===== PAYMENT =====
    
    /**
     * @brief Link payment to reservation
     * @param paymentID ID of the payment record
     * 
     * Associates a payment with this reservation.
     * Should be called after successful payment processing.
     */
    void linkPayment(string paymentID);

    // ===== CHECK-IN =====
    
    /**
     * @brief Perform check-in
     * @return true if check-in successful, false otherwise
     * 
     * Checks in the passenger for the flight. Only available within
     * 24 hours of departure. Changes status to "CheckedIn" and
     * generates a boarding pass.
     * 
     * @note Requires confirmed reservation
     * @see canCheckIn(), generateBoardingPass()
     */
    bool checkIn();
    
    /**
     * @brief Check if check-in is available
     * @return true if within 24 hours of departure
     * 
     * Validates that check-in is available based on:
     * - Reservation is confirmed
     * - Within 24 hours of flight departure
     * - Not already checked in
     */
    bool canCheckIn();
    
    /**
     * @brief Generate boarding pass
     * @return Boarding pass number/identifier
     * 
     * Generates a unique boarding pass for the passenger.
     * Includes passenger info, flight details, seat assignments, and barcode.
     * Called automatically during check-in process.
     */
    string generateBoardingPass();
    
    /**
     * @brief Check if passenger is checked in
     * @return true if checked in
     */
    bool isCheckedIn() const { return checkedIn; }

    // ===== STATUS =====
    
    /**
     * @brief Mark reservation as completed
     * 
     * Changes status to "Completed" after flight arrives.
     * Should be called when the flight journey is finished.
     */
    void markCompleted();

    // ===== DISPLAY =====
    
    /**
     * @brief Display reservation details
     * 
     * Shows comprehensive reservation information including:
     * - Reservation and passenger IDs
     * - Flight information
     * - Seat assignments
     * - Pricing and payment status
     * - Current status
     */
    void displayDetails();
    
    /**
     * @brief Display boarding pass information
     * 
     * Shows boarding pass details including:
     * - Passenger name and passport
     * - Flight number and gate
     * - Boarding time
     * - Seat numbers
     * - Boarding pass barcode/QR code
     * 
     * @note Only available after check-in
     */
    void displayBoardingPassInfo();

    // ===== SERIALIZATION =====
    
    /**
     * @brief Serialize reservation to JSON
     * @return JSON object containing complete reservation data
     * 
     * Converts reservation object to JSON for persistence including
     * all booking details, payment info, and check-in status.
     */
    json toJson() const;
    
    /**
     * @brief Deserialize reservation from JSON
     * @param j JSON object containing reservation data
     * @return Shared pointer to created Reservation object
     */
    static shared_ptr<Reservation> fromJson(const json &j);
};

#endif // RESERVATION_HPP