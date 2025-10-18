/**
 * @file flight.hpp
 * @brief Flight class for airline flight management
 * @author Rana
 * @date 2025
 * 
 * This file contains the Flight class which manages all aspects of a
 * scheduled flight including route, timing, seat allocation, crew assignment,
 * pricing, and real-time status tracking.
 */

#ifndef FLIGHT_HPP
#define FLIGHT_HPP

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

class SystemManager;

/**
 * @class Flight
 * @brief Represents a scheduled airline flight
 * 
 * The Flight class manages comprehensive flight operations including:
 * - Route and schedule management
 * - Dynamic seat allocation and booking
 * - Multi-class pricing (Economy, Business, First)
 * - Crew assignment and management
 * - Real-time status tracking
 * - Delay and cancellation handling
 * 
 * Each flight has a unique seat map that is initialized based on the
 * assigned aircraft's configuration. Seats can be booked, released,
 * and tracked individually.
 * 
 * @note Flight times should be in ISO 8601 format
 * @see Aircraft, Reservation, SystemManager
 */
class Flight
{
private:
    /**
     * @struct Seat
     * @brief Represents an individual seat on the flight
     * 
     * Nested structure containing seat information including
     * number, class, occupancy status, and passenger assignment.
     */
    struct Seat
    {
        string seatNumber;   ///< Seat identifier (e.g., "12A")
        string seatClass;    ///< Seat class: "Economy", "Business", or "First"
        bool isOccupied;     ///< Occupancy status
        string passengerID;  ///< ID of passenger if occupied

        /**
         * @brief Default constructor
         */
        Seat() : seatNumber(""), seatClass(""), isOccupied(false), passengerID("") {}
        
        /**
         * @brief Parameterized constructor
         * @param num Seat number
         * @param cls Seat class
         */
        Seat(string num, string cls) 
            : seatNumber(num), seatClass(cls), isOccupied(false), passengerID("") {}

        /**
         * @brief Serialize seat to JSON
         * @return JSON object containing seat data
         */
        json toJson() const;
        
        /**
         * @brief Deserialize seat from JSON
         * @param j JSON object containing seat data
         * @return Seat object
         */
        static Seat fromJson(const json &j);
    };

    string flightNumber;     ///< Unique flight identifier (e.g., "AA123")
    string origin;           ///< Departure airport code (e.g., "JFK")
    string destination;      ///< Destination airport code (e.g., "LAX")
    string departureTime;    ///< Scheduled departure time (ISO 8601)
    string arrivalTime;      ///< Scheduled arrival time (ISO 8601)

    string aircraftID;       ///< ID of assigned aircraft
    
    vector<string> crewMemberIDs;  ///< List of crew member user IDs

    string status;           ///< Flight status: "Scheduled", "Boarding", "Departed", "Arrived", "Delayed", "Cancelled"
    int delayMinutes;        ///< Flight delay in minutes

    // Pricing
    double economyPrice;     ///< Base price for economy class
    double businessPrice;    ///< Base price for business class
    double firstClassPrice;  ///< Base price for first class

    map<string, Seat> seatMap;  ///< Seat map: key is seat number (e.g., "1A")

    string gate;  ///< Boarding gate assignment

public:
    /**
     * @brief Constructor for Flight
     * @param flightNum Unique flight number
     * @param orig Origin airport code
     * @param dest Destination airport code
     * @param dep Departure time (ISO 8601 format)
     * @param arr Arrival time (ISO 8601 format)
     * @param aircraftID ID of assigned aircraft
     * 
     * Creates a new flight with the specified route and schedule.
     * Seat map must be initialized separately using initializeSeats().
     */
    Flight(string flightNum, string orig, string dest,
           string dep, string arr, string aircraftID);

    // ===== GETTERS =====
    
    /**
     * @brief Get flight number
     * @return The unique flight identifier
     */
    string getFlightNumber() const { return flightNumber; }
    
    /**
     * @brief Get origin airport
     * @return Departure airport code
     */
    string getOrigin() const { return origin; }
    
    /**
     * @brief Get destination airport
     * @return Destination airport code
     */
    string getDestination() const { return destination; }
    
    /**
     * @brief Get departure time
     * @return Scheduled departure time
     */
    string getDepartureTime() const { return departureTime; }
    
    /**
     * @brief Get arrival time
     * @return Scheduled arrival time
     */
    string getArrivalTime() const { return arrivalTime; }
    
    /**
     * @brief Get flight status
     * @return Current status of the flight
     */
    string getStatus() const { return status; }
    
    /**
     * @brief Get assigned aircraft ID
     * @return ID of the aircraft assigned to this flight
     */
    string getAircraftID() const { return aircraftID; }
    
    /**
     * @brief Get boarding gate
     * @return Gate number/identifier
     */
    string getGate() const { return gate; }

    /**
     * @brief Get price for a seat class
     * @param seatClass Class name: "Economy", "Business", or "First"
     * @return Price for the specified class, or -1.0 if invalid
     */
    double getPrice(string seatClass) const
    {
        if (seatClass == "Economy")
            return economyPrice;
        else if (seatClass == "Business")
            return businessPrice;
        else if (seatClass == "First")
            return firstClassPrice;
        else
            return -1.0;
    }

    /**
     * @brief Get economy class price
     * @return Economy class base price
     */
    double getEconomyPrice() const { return economyPrice; }
    
    /**
     * @brief Get business class price
     * @return Business class base price
     */
    double getBusinessPrice() const { return businessPrice; }
    
    /**
     * @brief Get first class price
     * @return First class base price
     */
    double getFirstClassPrice() const { return firstClassPrice; }

    /**
     * @brief Get delay duration
     * @return Delay in minutes
     */
    int getDelayMinutes() const { return delayMinutes; }

    // ===== SETTERS =====
    
    /**
     * @brief Set origin airport
     * @param newOrigin New departure airport code
     */
    void setOrigin(string newOrigin);
    
    /**
     * @brief Set destination airport
     * @param newDest New destination airport code
     */
    void setDestination(string newDest);
    
    /**
     * @brief Set departure time
     * @param newDepTime New departure time (ISO 8601)
     */
    void setDepartureTime(string newDepTime);
    
    /**
     * @brief Set arrival time
     * @param newArrTime New arrival time (ISO 8601)
     */
    void setArrivalTime(string newArrTime);
    
    /**
     * @brief Set boarding gate
     * @param gateNum Gate number/identifier
     */
    void setGate(string gateNum);
    
    /**
     * @brief Set pricing for all seat classes
     * @param economy Economy class price
     * @param business Business class price
     * @param first First class price
     */
    void setPricing(double economy, double business, double first);
    
    /**
     * @brief Set flight status
     * @param newStatus New status value
     */
    void setStatus(string newStatus);
    
    /**
     * @brief Set assigned aircraft
     * @param aircraftID ID of the aircraft to assign
     * 
     * Updates the aircraft assignment for this flight.
     * Should reinitialize seat map if aircraft changes.
     */
    void setAircraft(string aircraftID);

    // ===== SEAT MANAGEMENT =====
    
    /**
     * @brief Initialize seat map based on aircraft configuration
     * @param economy Number of economy seats
     * @param business Number of business seats
     * @param first Number of first class seats
     * 
     * Creates the seat map with the specified configuration.
     * Seats are numbered sequentially (e.g., 1A, 1B, 2A, 2B...).
     */
    void initializeSeats(int economy, int business, int first);
    
    /**
     * @brief Check if a seat is available
     * @param seatNum Seat number to check
     * @return true if seat is available, false if occupied or invalid
     */
    bool isSeatAvailable(string seatNum) const;
    
    /**
     * @brief Book a seat for a passenger
     * @param seatNum Seat number to book
     * @param passengerID ID of the passenger
     * @return true if booking successful, false otherwise
     * 
     * Attempts to book the specified seat. Fails if seat is
     * already occupied or doesn't exist.
     */
    bool bookSeat(string seatNum, string passengerID);
    
    /**
     * @brief Release a booked seat
     * @param seatNum Seat number to release
     * 
     * Marks the seat as available and clears passenger assignment.
     * Used when canceling or modifying reservations.
     */
    void releaseSeat(string seatNum);
    
    /**
     * @brief Get the class of a seat
     * @param seatNum Seat number
     * @return Seat class: "Economy", "Business", "First", or empty if invalid
     */
    string getSeatClass(string seatNum) const;
    
    /**
     * @brief Get list of available seats by class
     * @param seatClass Class to filter: "Economy", "Business", or "First"
     * @return Vector of available seat numbers
     */
    vector<string> getAvailableSeats(string seatClass) const;
    
    /**
     * @brief Count available seats by class
     * @param seatClass Class to count: "Economy", "Business", or "First"
     * @return Number of available seats in the specified class
     */
    int countAvailableSeats(string seatClass) const;
    
    /**
     * @brief Display seat map
     * 
     * Shows visual representation of seat availability.
     * Uses symbols to indicate: Available, Occupied, by class.
     */
    void showSeatMap();

    // ===== CREW MANAGEMENT =====
    
    /**
     * @brief Assign crew member to flight
     * @param crewID User ID of crew member
     * 
     * Adds a crew member to the flight manifest.
     */
    void assignCrew(string crewID);
    
    /**
     * @brief Remove crew member from flight
     * @param crewID User ID of crew member to remove
     */
    void removeCrew(string crewID);
    
    /**
     * @brief Get list of crew members
     * @return Vector of crew member IDs
     */
    vector<string> getCrew() const { return crewMemberIDs; }

    // ===== STATUS MANAGEMENT =====
    
    /**
     * @brief Update flight status
     * @param newStatus New status: "Scheduled", "Boarding", "Departed", "Arrived", "Delayed", "Cancelled"
     * 
     * Updates the current flight status. Logs status changes
     * for tracking and reporting purposes.
     */
    void updateStatus(string newStatus);
    
    /**
     * @brief Delay flight
     * @param minutes Number of minutes to delay
     * 
     * Records a delay and updates status to "Delayed".
     * Adjusts departure and arrival times accordingly.
     */
    void delayFlight(int minutes);
    
    /**
     * @brief Cancel flight
     * 
     * Sets status to "Cancelled". All reservations should be
     * cancelled and passengers notified.
     */
    void cancelFlight();
    
    /**
     * @brief Check if flight has departed
     * @return true if status is "Departed" or "Arrived"
     */
    bool isDeparted() const;
    
    /**
     * @brief Check if flight is cancelled
     * @return true if status is "Cancelled"
     */
    bool isCancelled() const;

    // ===== DISPLAY =====
    
    /**
     * @brief Display basic flight information
     * 
     * Shows essential flight details: number, route, times, status.
     */
    void displayFlightInfo();
    
    /**
     * @brief Display detailed flight information
     * 
     * Shows comprehensive flight details including seat availability,
     * pricing, crew, gate, and status.
     */
    void displayDetailedInfo();

    // ===== SERIALIZATION =====
    
    /**
     * @brief Serialize flight to JSON
     * @return JSON object containing complete flight data
     * 
     * Converts flight object to JSON including all seats and assignments.
     */
    json toJson() const;
    
    /**
     * @brief Deserialize flight from JSON
     * @param j JSON object containing flight data
     * @return Shared pointer to created Flight object
     */
    static shared_ptr<Flight> fromJson(const json &j);
};

#endif // FLIGHT_HPP