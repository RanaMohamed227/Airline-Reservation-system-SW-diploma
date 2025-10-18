/**
 * @file user.hpp
 * @brief Base User class for the Airline Management System
 * @author Your Name
 * @date 2025
 *
 * This file contains the abstract base User class that serves as the foundation
 * for all user types in the system (Admin, BookingAgent, and Passenger).
 */

#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <stdexcept>
#include "json.hpp" ///< Include nlohmann/json library
using json = nlohmann::json;
using namespace std;

/**
 * @class User
 * @brief Abstract base class representing a system user
 *
 * The User class provides common functionality for all user types in the
 * Airline Management System. It handles authentication, profile management,
 * and defines the interface that all derived classes must implement.
 *
 * @note This is an abstract class and cannot be instantiated directly.
 *
 * Derived classes include:
 * - Admin: System administrators with full access
 * - BookingAgent: Agents who process bookings and reservations
 * - Passenger: End users who book and manage their flights
 */
class User
{
protected:
    string userID;   ///< Unique identifier for the user
    string username; ///< User's login username
    string password; ///< User's password (should be hashed in production)
    string email;    ///< User's email address
    string phone;    ///< User's phone number
    string role;     ///< User role: "Admin", "Agent", or "Passenger"

public:
    /**
     * @brief Constructor for User
     * @param username The username for login
     * @param password The user's password
     * @param role The role of the user ("Admin", "Agent", or "Passenger")
     *
     * Creates a new user with the specified credentials and role.
     * The userID is automatically generated.
     */
    User(string username, string password, string role);

    /**
     * @brief Virtual destructor
     *
     * Ensures proper cleanup of derived classes
     */
    virtual ~User() = default;

    /**
     * @brief Validates user password
     * @param pass The password to validate
     * @return true if password matches, false otherwise
     *
     * Compares the provided password with the stored password.
     */
    bool validatePassword(string pass) const;

    /**
     * @brief Get the user ID
     * @return The unique user identifier
     */
    string getUserID() const { return userID; }

    /**
     * @brief Get the username
     * @return The user's login username
     */
    string getUsername() const { return username; }

    /**
     * @brief Get the user role
     * @return The user's role (Admin, Agent, or Passenger)
     */
    string getRole() const { return role; }

    /**
     * @brief Get the user's email
     * @return The user's email address
     */
    string getEmail() const { return email; }

    /**
     * @brief Get the user's phone number
     * @return The user's phone number
     */
    string getPhone() const { return phone; }

    /**
     * @brief Display the menu for this user type
     * @pure
     *
     * Pure virtual function that must be implemented by derived classes.
     * Each user type displays a different menu based on their permissions.
     */
    virtual void showMenu() = 0;

    /**
     * @brief Update user's email address
     * @param newEmail The new email address
     *
     * Updates the user's email in the system.
     */
    void updateEmail(string newEmail);

    /**
     * @brief Update user's phone number
     * @param newPhone The new phone number
     *
     * Updates the user's phone number in the system.
     */
    void updatePhone(string newPhone);

    /**
     * @brief Change user password
     * @param oldPass The current password for verification
     * @param newPass The new password to set
     * @return true if password was changed successfully, false otherwise
     *
     * Changes the user's password after verifying the old password.
     */
    bool changePassword(string oldPass, string newPass);

    /**
     * @brief Serialize user to JSON
     * @return JSON object containing user data
     *
     * Converts the user object to a JSON representation for storage.
     * Derived classes should override this to include additional fields.
     */
    virtual json toJson() const;

    /**
     * @brief Deserialize user from JSON
     * @param j JSON object containing user data
     * @return Shared pointer to the created User object
     *
     * Creates a User object from JSON data. Determines the type
     * based on the role field and creates the appropriate derived class.
     */
    static shared_ptr<User> fromJson(const json &j);
};

#endif // USER_HPP