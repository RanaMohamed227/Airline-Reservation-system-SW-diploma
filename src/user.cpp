#include "../inc/user.hpp"
#include "../inc/admin.hpp"
#include "../inc/bookingagent.hpp"
#include "../inc/passenger.hpp"
static int userIDCounter = 1000;// Static counter for unique user IDs
// Constructor
User::User(string username, string password, string role)
    : username(username), password(password), role(role)
{
   
        // Generate a simple userID (in a real system, this should be more robust)
        userID = "U" + to_string(userIDCounter++);
        email = "";
        phone = "";

}
// Authentication
bool User::validatePassword(string pass) const
{
    return pass == password;
}
// Update profile
void User::updateEmail(string newEmail)
{
    email = newEmail;
}
void User::updatePhone(string newPhone)
{
    phone = newPhone;
}
bool User::changePassword(string oldPass, string newPass)
{
    if (validatePassword(oldPass))
    {
        password = newPass;
        return true ;
    }
    else
    {
        cout<<"Old password is incorrect."<<endl;
        return false ;
    }
}
// Serialization
json User::toJson() const      
{
    json j;
    j["userID"] = userID;
    j["username"] = username;
    j["password"] = password; // In a real system, never store plain passwords
    j["email"] = email;
    j["phone"] = phone;
    j["role"] = role;
    return j;
}




shared_ptr<User> User::fromJson(const json &j)
{
    string role = j.at("role").get<string>();
    shared_ptr<User> user;

    if (role == "Admin")
    {
        user = Admin::fromJson(j);
    }
    else if (role == "Agent")
    {
        user = BookingAgent::fromJson(j);
    }
    else if (role == "Passenger")
    {
        user = Passenger::fromJson(j);
    }
    else
    {
        throw invalid_argument("Unknown user role: " + role);
    }

    return user;
}



/*
shared_ptr<User> User::fromJson(const json &j)
{
    string role = j.at("role").get<string>();
    shared_ptr<User> user;

    if (role == "Admin")
    {
        // Assuming Admin class is defined and inherits from User
        user = make_shared<Admin>(j.at("username").get<string>(),
                                  j.at("password").get<string>());
    }
    else if (role == "Agent")
    {
        // Assuming Agent class is defined and inherits from User
        user = make_shared<BookingAgent>(j.at("username").get<string>(),
                                  j.at("password").get<string>());
    }
    else if (role == "Passenger")
    {
        // Assuming Passenger class is defined and inherits from User
        user = make_shared<Passenger>(j.at("username").get<string>(),
                                      j.at("password").get<string>());
    }
    else
    {
        throw invalid_argument("Unknown user role: " + role);
    }

    user->userID = j.at("userID").get<string>();
    user->email = j.at("email").get<string>();
    user->phone = j.at("phone").get<string>();

    return user;
}
*/
//getters are inline in the header file




