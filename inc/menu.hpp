/**
 * @file menu.hpp
 * @brief Menu class for user interface navigation
 * @author Your Name
 * @date 2025
 * 
 * This file contains the Menu class which provides console-based user
 * interface menus for different user roles (Admin, BookingAgent, Passenger).
 * Handles user input and delegates operations to appropriate classes.
 */

#ifndef MENU_HPP
#define MENU_HPP

#include "systemmanager.hpp"
#include "admin.hpp"
#include "bookingagent.hpp"
#include "passenger.hpp"
#include <iostream>
#include <limits>

using namespace std;

/**
 * @class menu
 * @brief Console-based user interface controller
 * 
 * The Menu class provides interactive console menus for all user types:
 * - Admin menu: Full system administration
 * - Booking Agent menu: Customer service operations
 * - Passenger menu: Personal booking management
 * 
 * Each menu presents role-appropriate options and handles user input
 * validation and error handling. Delegates actual operations to the
 * corresponding user class and SystemManager.
 * 
 * @note Uses console I/O with cin/cout
 * @see Admin, BookingAgent, Passenger, SystemManager
 */
class menu
{
public:
    /**
     * @brief Display and handle admin menu
     * @param system Reference to SystemManager for operations
     * @param admin Shared pointer to logged-in Admin user
     * 
     * Displays comprehensive admin menu with options:
     * - User management (create, delete, view, update users)
     * - Flight management (add, update, delete, view flights)
     * - Aircraft management (add, remove, view fleet)
     * - Maintenance scheduling and viewing
     * - System reports (flight, revenue, maintenance, user activity)
     * - System status dashboard
     * - Logout
     * 
     * Runs in a loop until admin chooses to logout.
     * Validates input and provides appropriate error messages.
     */
    void adminMenu(SystemManager &system, shared_ptr<Admin> admin);
    
    /**
     * @brief Display and handle booking agent menu
     * @param system Reference to SystemManager for operations
     * @param agent Shared pointer to logged-in BookingAgent user
     * 
     * Displays booking agent menu with options:
     * - Search flights
     * - Create new booking
     * - View booking details
     * - Modify booking
     * - Cancel booking
     * - Process payment
     * - Check-in passenger
     * - Print boarding pass
     * - View all bookings
     * - View performance stats
     * - Logout
     * 
     * Runs in a loop until agent chooses to logout.
     * Provides user-friendly prompts and error handling.
     */
    void agentMenu(SystemManager &system, shared_ptr<BookingAgent> agent);
    
    /**
     * @brief Display and handle passenger menu
     * @param system Reference to SystemManager for operations
     * @param passenger Shared pointer to logged-in Passenger user
     * 
     * Displays passenger menu with options:
     * - Search and book flights
     * - View my bookings
     * - Cancel booking
     * - Online check-in
     * - View boarding pass
     * - Manage preferences (meal, seat, wheelchair)
     * - View loyalty status
     * - Update profile
     * - Logout
     * 
     * Runs in a loop until passenger chooses to logout.
     * Shows personalized information and loyalty benefits.
     */
    void passengerMenu(SystemManager &system, shared_ptr<Passenger> passenger);
    
    /**
     * @brief Pause for user input
     * 
     * Utility function to pause execution and wait for user to press Enter.
     * Used after displaying information to prevent menu from immediately
     * reappearing. Improves user experience by giving time to read output.
     * 
     * Usage:
     * @code
     * displaySomeInfo();
     * pause();  // Wait for user to press Enter
     * @endcode
     */
    void pause();
};

#endif // MENU_HPP