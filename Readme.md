# Airline Management System

## Overview

The Airline Management System is a comprehensive C++ application designed to manage all aspects of airline operations, including flight scheduling, passenger bookings, aircraft management, crew assignments, and maintenance tracking.

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
SystemManager (Facade Pattern)
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

### Technologies Used
- **Language**: C++17
- **Data Storage**: JSON-based persistence using nlohmann/json library
- **Design Patterns**: 
  - Inheritance (User hierarchy)
  - Facade (SystemManager)
  - Factory (Object creation from JSON)

### Key Features
- Object-Oriented Design
- RAII principles
- Smart pointers (shared_ptr) for memory management
- Exception handling
- Serialization/Deserialization to JSON
- File-based data persistence

## Data Persistence

The system stores data in JSON format in the following files:
- `data/users.json` - User accounts and profiles
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

## Building Documentation

### Prerequisites
- Doxygen (version 1.9.0 or higher)
- Graphviz (for UML diagrams)

### Generate Documentation

```bash
# Run Doxygen
doxygen Doxyfile

# Open documentation
cd docs/html
open index.html  # macOS
xdg-open index.html  # Linux
start index.html  # Windows
```

## UML Diagrams

The documentation includes comprehensive UML diagrams:
- **Class Diagrams**: Show relationships between classes
- **Inheritance Diagrams**: Display class hierarchies
- **Collaboration Diagrams**: Show class interactions
- **Include Graphs**: Display file dependencies

## API Documentation

Detailed API documentation is generated for:
- All public class methods
- Protected and private members (optional)
- Function parameters and return values
- Code examples and usage notes
- Cross-references between related classes

## Development Guidelines

### Coding Standards
- Use meaningful variable and function names
- Follow C++ naming conventions
- Add comments for complex logic
- Keep functions focused and concise
- Use const correctness

### Error Handling
- Validate input parameters
- Use exceptions for error conditions
- Provide meaningful error messages
- Handle edge cases

### Memory Management
- Use smart pointers (shared_ptr)
- Follow RAII principles
- Avoid memory leaks
- Proper object lifecycle management

## Future Enhancements

Potential improvements:
- Database integration (MySQL/PostgreSQL)
- Real-time notifications
- Mobile application integration
- Advanced reporting dashboards
- Multi-language support
- Enhanced security features (encryption, 2FA)

## License

[Specify your license here]

## Contributors

[List contributors here]

## Contact

[Contact information]

---

*This documentation was generated using Doxygen. Last updated: 2025*
