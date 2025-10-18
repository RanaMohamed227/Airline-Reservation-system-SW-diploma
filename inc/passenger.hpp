/**
 * @file passenger.hpp
 * @brief Passenger class for end-user flight bookings
 * @author Rana
 * @date 2025
 * 
 * This file contains the Passenger class which represents airline customers
 * who can search flights, make bookings, check-in online, and manage their
 * travel preferences and loyalty rewards.
 */

#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include <memory>
#include "user.hpp"

class SystemManager;

/**
 * @class Passenger
 * @brief End-user class for flight bookings and travel management
 * 
 * The Passenger class extends User to provide customer-facing functionality:
 * - Flight search and booking
 * - Personal booking management
 * - Online check-in and boarding passes
 * - Loyalty program participation
 * - Travel preferences and history
 * 
 * Passengers earn loyalty points based on their bookings and receive
 * tier-based discounts (Bronze, Silver, Gold, Platinum).
 * 
 * @note Inherits from User base class
 * @see User, Reservation, Flight, SystemManager
 */
class Passenger : public User
{
private:
    string passportNumber;    ///< Passenger's passport number
    string nationality;       ///< Passenger's nationality
    string dateOfBirth;       ///< Date of birth (YYYY-MM-DD format)

    // Loyalty Program
    int loyaltyPoints;        ///< Accumulated loyalty points
    string tier;              ///< Loyalty tier: "Bronze", "Silver", "Gold", "Platinum"
    
    // Preferences
    string mealPreference;    ///< Preferred meal type (e.g., "Vegetarian", "Halal")
    string seatPreference;    ///< Preferred seat location (e.g., "Window", "Aisle")
    bool needsWheelchair;     ///< Wheelchair assistance required flag

    // Booking history
    vector<string> reservationIDs;  ///< List of all reservation IDs for this passenger

public:
    /**
     * @brief Constructor for Passenger
     * @param username The passenger's username for login
     * @param password The passenger's password
     * @param passport Passport number
     * @param nationality Passenger's nationality
     * @param DOB Date of birth (YYYY-MM-DD format)
     * 
     * Creates a new passenger account with basic profile information.
     * Initializes loyalty points to 0 and tier to "Bronze".
     */
    Passenger(string username, string password, string passport,
              string nationality, string DOB);

    // ===== GETTERS =====
    
    /**
     * @brief Get passport number
     * @return The passenger's passport number
     */
    string getPassportNumber() const { return passportNumber; }
    
    /**
     * @brief Get nationality
     * @return The passenger's nationality
     */
    string getNationality() const { return nationality; }
    
    /**
     * @brief Get date of birth
     * @return The passenger's date of birth
     */
    string getDateOfBirth() const { return dateOfBirth; }

    /**
     * @brief Get loyalty points
     * @return Current loyalty points balance
     */
    int getLoyaltyPoints() const { return loyaltyPoints; }
    
    /**
     * @brief Get loyalty tier
     * @return Current tier: "Bronze", "Silver", "Gold", or "Platinum"
     */
    string getTier() const { return tier; }

    /**
     * @brief Get wheelchair assistance requirement
     * @return true if wheelchair assistance is needed
     */
    bool getNeedsWheelchair() const { return needsWheelchair; }
    
    /**
     * @brief Get meal preference
     * @return Preferred meal type
     */
    string getMealPreference() const { return mealPreference; }
    
    /**
     * @brief Get seat preference
     * @return Preferred seat location
     */
    string getSeatPreference() const { return seatPreference; }

    /**
     * @brief Get reservation history
     * @return Vector of reservation IDs for this passenger
     */
    vector<string> getReservationHistory() const { return reservationIDs; }

    // ===== FLIGHT SEARCH & BOOKING =====
    
    /**
     * @brief Search for available flights
     * @param system Reference to the SystemManager
     * @param origin Departure airport code (e.g., "JFK")
     * @param dest Destination airport code (e.g., "LAX")
     * @param date Departure date (YYYY-MM-DD format)
     * 
     * Searches and displays all available flights matching the criteria.
     * Shows flight details, available seats, and prices with applicable
     * loyalty discounts.
     */
    void searchFlights(SystemManager &system, string origin, string dest,
                       string date);
    
    /**
     * @brief Book a flight
     * @param system Reference to the SystemManager
     * @param flightNum Flight number to book
     * @param seats Vector of seat numbers to book (e.g., {"12A", "12B"})
     * 
     * Creates a new reservation for the specified flight and seats.
     * Applies loyalty discount if applicable. Adds reservation to
     * passenger's history and earns loyalty points.
     * 
     * @note Payment must be processed separately
     * @see Payment
     */
    void bookFlight(SystemManager &system, string flightNum,
                    vector<string> seats);

    // ===== LOYALTY PROGRAM =====
    
    /**
     * @brief Earn loyalty points
     * @param points Number of points to add
     * 
     * Adds points to the passenger's loyalty account.
     * Points are typically earned based on flight cost (1 point per $10).
     * Automatically updates tier if threshold is reached.
     */
    void earnPoints(int points);
    
    /**
     * @brief Redeem loyalty points
     * @param points Number of points to redeem
     * @return true if redemption successful, false if insufficient points
     * 
     * Deducts points from the passenger's loyalty account.
     * Can be used for discounts or upgrades.
     */
    bool redeemPoints(int points);
    
    /**
     * @brief Get loyalty discount percentage
     * @return Discount percentage based on current tier
     * 
     * Returns the discount applicable to this passenger:
     * - Bronze: 0%
     * - Silver: 5%
     * - Gold: 10%
     * - Platinum: 15%
     */
    double getDiscount();
    
    /**
     * @brief Update loyalty tier based on points
     * 
     * Recalculates and updates the passenger's tier based on
     * accumulated points:
     * - Bronze: 0-999 points
     * - Silver: 1000-4999 points
     * - Gold: 5000-9999 points
     * - Platinum: 10000+ points
     */
    void updateTier();
    
    /**
     * @brief Display loyalty status
     * 
     * Shows current loyalty points, tier, discount percentage,
     * and points needed for next tier upgrade.
     */
    void checkLoyaltyStatus();

    // ===== PREFERENCES =====
    
    /**
     * @brief Set meal preference
     * @param meal Meal type (e.g., "Vegetarian", "Vegan", "Halal", "Kosher")
     * 
     * Updates the passenger's meal preference for future bookings.
     */
    void setMealPreference(string meal);
    
    /**
     * @brief Set seat preference
     * @param pref Seat location preference (e.g., "Window", "Aisle", "Middle")
     * 
     * Updates the passenger's preferred seat location.
     */
    void setSeatPreference(string pref);
    
    /**
     * @brief Set wheelchair assistance requirement
     * @param needed true if wheelchair assistance is required
     * 
     * Updates wheelchair assistance flag for future bookings.
     */
    void setWheelchairNeeded(bool needed);

    // ===== BOOKING HISTORY =====
    
    /**
     * @brief Add reservation to passenger's history
     * @param reservationID The reservation ID to add
     * 
     * Adds a reservation to the passenger's booking history.
     * Called automatically when creating a new booking.
     */
    void addReservationToHistory(string reservationID);

    /**
     * @brief Display passenger menu
     * 
     * Overrides User::showMenu() to display passenger-specific menu options
     * including flight search, booking management, check-in, and loyalty info.
     */
    void showMenu() override;

    /**
     * @brief Serialize passenger to JSON
     * @return JSON object containing passenger data
     * 
     * Converts the passenger object to JSON format for persistence.
     * Includes user fields plus passenger-specific data such as passport,
     * loyalty info, and preferences.
     */
    json toJson() const override;
    
    /**
     * @brief Deserialize passenger from JSON
     * @param j JSON object containing passenger data
     * @return Shared pointer to created Passenger object
     * 
     * Creates a Passenger object from stored JSON data.
     */
    static shared_ptr<Passenger> fromJson(const json &j);
};

#endif // PASSENGER_HPP