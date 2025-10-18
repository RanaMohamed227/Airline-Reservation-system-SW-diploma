/**
 * @file payment.hpp
 * @brief Payment class for transaction processing
 * @author Your Name
 * @date 2025
 * 
 * This file contains the Payment class which handles all financial
 * transactions including payment processing, receipts, refunds, and
 * loyalty points calculation for the airline management system.
 */

#ifndef PAYMENT_HPP
#define PAYMENT_HPP

#include <string>
#include <iostream>
#include <memory>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/**
 * @class Payment
 * @brief Manages financial transactions for reservations
 * 
 * The Payment class handles all payment-related operations:
 * - Payment processing (CreditCard, DebitCard, Cash)
 * - Transaction status tracking
 * - Receipt generation
 * - Refund processing for cancellations
 * - Loyalty points calculation based on spend
 * 
 * Payment status progression:
 * - Pending: Payment initiated but not processed
 * - Completed: Payment successfully processed
 * - Failed: Payment processing failed
 * - Refunded: Payment has been refunded
 * 
 * @note This is a simulated payment system for demonstration
 * @see Reservation, Passenger, SystemManager
 */
class Payment
{
private:
    string paymentID;        ///< Unique payment identifier
    string reservationID;    ///< Associated reservation ID
    double amount;           ///< Payment amount
    string method;           ///< Payment method: "CreditCard", "DebitCard", "Cash"
    
    // Status
    string status;           ///< Status: "Pending", "Completed", "Failed", "Refunded"
    string paymentDate;      ///< Date and time of payment
    
    // Card info (simulated)
    string cardLastFour;     ///< Last 4 digits of card (for CreditCard/DebitCard)
    
    // Refund
    bool refunded;           ///< Refund status flag
    double refundAmount;     ///< Amount refunded (may be partial)
    string refundDate;       ///< Date of refund

public:
    /**
     * @brief Constructor for Payment
     * @param reservationID ID of the reservation this payment is for
     * @param amount Payment amount
     * @param method Payment method: "CreditCard", "DebitCard", or "Cash"
     * 
     * Creates a new payment record with "Pending" status.
     * Payment ID is generated automatically. Payment date is set to
     * current date/time. Process must be called to complete payment.
     */
    Payment(string reservationID, double amount, string method);
    
    // ===== GETTERS =====
    
    /**
     * @brief Get payment ID
     * @return Unique payment identifier
     */
    string getPaymentID() const { return paymentID; }
    
    /**
     * @brief Get reservation ID
     * @return Associated reservation identifier
     */
    string getReservationID() const { return reservationID; }
    
    /**
     * @brief Get payment status
     * @return Current status: "Pending", "Completed", "Failed", or "Refunded"
     */
    string getStatus() const { return status; }
    
    /**
     * @brief Get payment amount
     * @return Original payment amount
     */
    double getAmount() const { return amount; }
    
    /**
     * @brief Get payment method
     * @return Payment method used
     */
    string getMethod() const { return method; }
    
    /**
     * @brief Check if payment was refunded
     * @return true if refunded
     */
    bool isRefunded() const { return refunded; }
    
    // ===== PAYMENT PROCESSING =====
    
    /**
     * @brief Process the payment
     * @return true if payment successful, false otherwise
     * 
     * Simulates payment processing. In a real system, this would
     * integrate with payment gateways. Changes status to "Completed"
     * or "Failed" based on result.
     * 
     * @note This is a simulation - always succeeds for valid inputs
     */
    bool process();
    
    /**
     * @brief Set card information
     * @param lastFour Last 4 digits of card number
     * 
     * Stores masked card information for receipt and record keeping.
     * Only last 4 digits are stored for security.
     */
    void setCardInfo(string lastFour);
    
    // ===== STATUS MANAGEMENT =====
    
    /**
     * @brief Mark payment as completed
     * 
     * Sets status to "Completed" and records completion time.
     * Called after successful payment processing.
     */
    void markCompleted();
    
    /**
     * @brief Mark payment as failed
     * 
     * Sets status to "Failed". Should log reason for failure.
     * Reservation should remain in "Pending" state for retry.
     */
    void markFailed();
    
    /**
     * @brief Check if payment was successful
     * @return true if status is "Completed"
     */
    bool isSuccessful() const;
    
    // ===== REFUND PROCESSING =====
    
    /**
     * @brief Process refund
     * @param amount Amount to refund (can be partial)
     * @return true if refund successful, false otherwise
     * 
     * Processes a refund for the payment. Can handle partial refunds.
     * Changes status to "Refunded" and records refund details.
     * 
     * @note Cannot refund more than original amount
     * @note Cannot refund already refunded payments
     */
    bool refund(double amount);
    
    /**
     * @brief Get refund amount
     * @return Total amount refunded
     */
    double getRefundAmount() const { return refundAmount; }
    
    // ===== LOYALTY POINTS =====
    
    /**
     * @brief Calculate loyalty points earned
     * @return Number of loyalty points (1 point per $10 spent)
     * 
     * Calculates loyalty points based on payment amount.
     * Standard rate: 1 point for every $10 spent.
     * Used to credit passenger's loyalty account.
     */
    int calculatePointsEarned() const;
    
    // ===== DISPLAY =====
    
    /**
     * @brief Display payment receipt
     * 
     * Shows formatted receipt including:
     * - Payment and reservation IDs
     * - Date and time
     * - Amount paid
     * - Payment method (with masked card info)
     * - Status
     * - Points earned
     * 
     * Suitable for printing or display to customer.
     */
    void displayReceipt();
    
    /**
     * @brief Display payment details
     * 
     * Shows detailed payment information for administrative purposes
     * including all fields and refund information if applicable.
     */
    void displayDetails();
    
    // ===== SERIALIZATION =====
    
    /**
     * @brief Serialize payment to JSON
     * @return JSON object containing complete payment data
     * 
     * Converts payment object to JSON for persistence including
     * all transaction details and refund information.
     */
    json toJson() const;
    
    /**
     * @brief Deserialize payment from JSON
     * @param j JSON object containing payment data
     * @return Shared pointer to created Payment object
     */
    static shared_ptr<Payment> fromJson(const json &j);
};

#endif // PAYMENT_HPP