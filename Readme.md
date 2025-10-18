# Airline Management System

## Overview

The Airline Management System is a comprehensive C++ application designed to manage all aspects of airline operations, including flight scheduling, passenger bookings, aircraft management, crew assignments, and maintenance tracking.


Project Statement (Expect having this only to build the project):
The Airline Reservation and Management System is an advanced, console-based application developed
in C++ that leverages Object-Oriented Programming (OOP) principles and Modern C++ features to
simulate the comprehensive operations of an airline. Designed to cater to multiple user roles—including
Administrators, Booking Agents, and Passengers—the system ensures secure and role-based access to its
diverse functionalities. Administrators can manage user accounts, oversee flight schedules, and handle
aircraft and crew assignments, while Booking Agents facilitate flight reservations, seat selections, and
payment processing. Passengers benefit from an intuitive interface to search for flights, make bookings,
select seats, and manage their personal profiles, including participation in loyalty programs.
Flight scheduling and management system, allowing for the addition, updating, and removal of flights
with detailed information such as flight numbers, origins, destinations, departure and arrival times, and
aircraft types. The system also manages the airline’s fleet by tracking aircraft specifications, maintenance
schedules, and availability, ensuring optimal operational efficiency. Crew assignment functionalities
enable the allocation of pilots and flight attendants to specific flights while adhering to regulatory
compliance regarding maximum flight hours.
The booking system is robust, offering search capabilities based on various criteria like date, destination,
and price, along with seat selection through interactive seat maps. It supports reservation creation,
modification, and cancellation, complete with simulated payment processing and refund handling.
Additionally, the system maintains comprehensive passenger profiles, facilitating personalized
experiences and tracking travel histories. The check-in module provides both online and airport-based
check-in processes, including the generation of boarding passes and management of the boarding
procedure.
Maintenance tracking is integral to the system, ensuring that all aircraft undergo scheduled maintenance
and that detailed logs of maintenance activities are maintained for safety and regulatory compliance.
Real-time flight status updates inform relevant users of changes such as delays or cancellations, while
the reporting and analytics module generates insightful reports on flight performance, reservations,
financial summaries, and user activities.
Data persistence is achieved through file-based databases like JSON or CSV. 
## Features

### User Management
- **Multiple User Roles**: Admin, Booking Agent, and Passenger
- **Authentication System**: Secure login and password management
- **Role-Based Access Control**: Different permissions for different user types

### Flight Operations
- **Flight Scheduling**: Create and manage flight schedules
- **Real-time Status Updates**: Track flight status (Scheduled, Boarding, Departed, etc.)
- **Seat Management**: Dynamic seat allocation with different classes (Economy, Business, First)
- **Pricing System**: Flexible pricing for different seat classes

### Booking System
- **Reservation Management**: Create, modify, and cancel reservations
- **Multi-seat Booking**: Support for booking multiple seats
- **Online Check-in**: 24-hour advance check-in facility
- **Boarding Pass Generation**: Digital boarding passes

### Aircraft Management
- **Fleet Management**: Track all aircraft in the fleet
- **Maintenance Scheduling**: Schedule and track maintenance activities
- **Flight Hours Tracking**: Monitor aircraft usage and maintenance intervals
- **Status Management**: Available, In Use, Under Maintenance

### Payment Processing
- **Multiple Payment Methods**: Credit Card, Debit Card, Cash
- **Payment Tracking**: Complete payment history and receipts
- **Refund Management**: Process refunds for cancelled bookings

### Loyalty Program
- **Points System**: Earn points on flights
- **Tier Levels**: Bronze, Silver, Gold, Platinum
- **Discounts**: Tier-based discounts on bookings

### Reports & Analytics
- **Flight Reports**: Detailed flight statistics
- **Revenue Reports**: Financial analysis and revenue tracking
- **Maintenance Reports**: Aircraft maintenance history
- **User Activity**: Track system usage and user actions

## System Architecture
```
├── inc
├── src
└── build
cmakelists.txt
doxyfile
```

### Class Hierarchy

```
User (Abstract Base Class)
├── Admin
├── BookingAgent
└── Passenger

Aircraft
Flight
Reservation
Payment
Maintenance
SystemManager 
```

### Core Components

1. **SystemManager**: Central management class that coordinates all system operations
2. **User Classes**: Handle authentication and role-specific operations
3. **Aircraft**: Manage fleet and maintenance
4. **Flight**: Handle flight operations and seat management
5. **Reservation**: Manage booking lifecycle
6. **Payment**: Process and track payments
7. **Maintenance**: Schedule and track aircraft maintenance

## Technical Details



### Key Features
- Object-Oriented Design
- RAII principles
- Smart pointers (shared_ptr) for memory management
- Exception handling
- Serialization/Deserialization to JSON
- File-based data persistence

## Data Persistence

The system stores data in JSON format in the following files:
- `data/users.json` - User acunts and profiles
- `data/aircraft.json` - Aircraft fleet information
- `data/flights.json` - Flight schedules and details
- `data/reservations.json` - Booking records
- `data/payments.json` - Payment transactions
- `data/maintenance.json` - Maintenance records

## Class Descriptions

### User Classes

#### Admin
Full system access including:
- User management (create, delete, modify users)
- Flight management (add, update, delete flights)
- Aircraft management (add, remove aircraft)
- Maintenance scheduling
- System reports and analytics

#### BookingAgent
Handles customer-facing operations:
- Search and display flights
- Create and modify bookings
- Process payments
- Check-in passengers
- Generate boarding passes

#### Passenger
End-user functionality:
- Search flights
- Book tickets
- Manage personal bookings
- Online check-in
- View loyalty points and benefits

### Flight Management

#### Flight Class
- Flight scheduling and routing
- Seat map management
- Crew assignment
- Status tracking
- Delay management

#### Aircraft Class
- Aircraft specifications
- Seat configuration
- Maintenance tracking
- Flight hours monitoring
- Availability status

### Booking System

#### Reservation Class
- Booking lifecycle management
- Seat selection and modification
- Check-in processing
- Boarding pass generation
- Status tracking (Pending, Confirmed, Checked-In, Cancelled, Completed)

#### Payment Class
- Payment processing
- Multiple payment methods
- Receipt generation
- Refund processing
- Loyalty points calculation

### Maintenance System

#### Maintenance Class
- Scheduled maintenance
- Maintenance types (Routine, Inspection, Repair)
- Parts tracking
- Cost management
- Status monitoring


---

