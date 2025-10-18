#include "../inc/reservation.hpp"
#include "../inc/payment.hpp"


static int paymentIDCounter = 1000;
//constructor
Payment::Payment(string reservationID, double amount, string method)
    : reservationID(reservationID), amount(amount), method(method), status("Pending"),
      refunded(false), refundAmount(0.0) {
    // Generate a simple payment ID (in real scenarios, use a better method)
    paymentID = "PAY" + to_string(paymentIDCounter++); 
}



//PROCESS PAYMENT
bool Payment::process() {
    // Simulate payment processing
    if (method == "CreditCard" || method == "DebitCard") {
        if (cardLastFour.empty()) {
            cout << "Card information not set." << endl;
            return false;
        }
        // Simulate success
        markCompleted();
        paymentDate = "2024-10-01"; // Simulated date
        return true;
    } 
    
    
    
    else if (method == "Cash") {
        // Cash payments are always successful in this simulation
        markCompleted();
        paymentDate = "2024-10-01"; // Simulated date
        return true;
    }


    
    markFailed();
    return false;
}
void Payment::setCardInfo(string lastFour) {
    cardLastFour = lastFour;
}



//SATUS

//MARK COMPLETED
void Payment::markCompleted() {
    status = "Completed";
}
//MARK FAILED
void Payment::markFailed() {
    status = "Failed";
}
bool Payment::isSuccessful() const {
    return status == "Completed";
}




//REFUND
bool Payment::refund(double amount) {
    if (status != "Completed" || refunded || amount <= 0 || amount > this->amount) {
        return false;
    }
    refunded = true;
    refundAmount = amount;
    refundDate = "2024-10-02"; // Simulated date
    status = "Refunded";
    return true;
}



//LOYALTY POINTS

int Payment::calculatePointsEarned() const {
    return static_cast<int>(amount / 10);
}

//DISPLAY
void Payment::displayReceipt() {
    cout << "----- Payment Receipt -----" << endl;
    cout << "Payment ID: " << paymentID << endl;
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Amount: $" << amount << endl;
    cout << "Method: " << method << endl;
    if (!cardLastFour.empty()) {
        cout << "Card Last Four: **** **** **** " << cardLastFour << endl;
    }
    cout << "Status: " << status << endl;
    if (status == "Completed") {
        cout << "Payment Date: " << paymentDate << endl;
    }
    if (refunded) {
        cout << "Refund Amount: $" << refundAmount << endl;
        cout << "Refund Date: " << refundDate << endl;
    }
    cout << "Points Earned: " << calculatePointsEarned() << endl;
    cout << "---------------------------" << endl;
}


void Payment::displayDetails() {
    cout << "----- Payment Details -----" << endl;
    cout << "Payment ID: " << paymentID << endl;
    cout << "Reservation ID: " << reservationID << endl;
    cout << "Amount: $" << amount << endl;
    cout << "Method: " << method << endl;
    if (!cardLastFour.empty()) {
        cout << "Card Last Four: **** **** **** " << cardLastFour << endl;
    }
    cout << "Status: " << status << endl;
    if (status == "Completed") {
        cout << "Payment Date: " << paymentDate << endl;
    }
    if (refunded) {
        cout << "Refund Amount: $" << refundAmount << endl;
        cout << "Refund Date: " << refundDate << endl;
    }
    cout << "Points Earned: " << calculatePointsEarned() << endl;
    cout << "---------------------------" << endl;
}

//SERIALIZATION
json Payment::toJson() const {
    json j;
    j["paymentID"] = paymentID;
    j["reservationID"] = reservationID;
    j["amount"] = amount;
    j["method"] = method;
    j["status"] = status;
    j["paymentDate"] = paymentDate;
    j["cardLastFour"] = cardLastFour;
    j["refunded"] = refunded;
    j["refundAmount"] = refundAmount;
    j["refundDate"] = refundDate;
    return j;
}
shared_ptr<Payment> Payment::fromJson(const json& j) {
    auto payment = make_shared<Payment>(j.at("reservationID").get<string>(),
                                        j.at("amount").get<double>(),
                                        j.at("method").get<string>());
    payment->paymentID = j.at("paymentID").get<string>();
    payment->status = j.at("status").get<string>();
    payment->paymentDate = j.at("paymentDate").get<string>();
    payment->cardLastFour = j.at("cardLastFour").get<string>();
    payment->refunded = j.at("refunded").get<bool>();
    payment->refundAmount = j.at("refundAmount").get<double>();
    payment->refundDate = j.at("refundDate").get<string>();
    return payment;
}
