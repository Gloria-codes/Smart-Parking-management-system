#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#include <cmath>

using namespace std;

// Stores information about one parking slot
struct ParkingSlot {
    int slotNumber;
    bool occupied;
};

// Stores information about a vehicle currently in the parking lot
struct Vehicle {
    string plateNumber;
    string ownerName;
    int slotNumber;
    time_t entryTime;
};

// Stores information about a completed parking session
struct ParkingSession {
    string plateNumber;
    int slotNumber;
    time_t entryTime;
    time_t exitTime;
    double amountPaid;
};

class ParkingSystem {
private:
    vector<ParkingSlot> slots;

    // The plate number is used as the key to find a parked vehicle
    unordered_map<string, Vehicle> parkedVehicles;

    // Stores vehicles that have already left the parking lot
    vector<ParkingSession> completedSessions;

    // Parking charge per hour
    double ratePerHour = 100.0;

    // Converts the time into a readable date and time
    string formatTime(time_t timeValue) const {
        tm* localTime = localtime(&timeValue);

        if (localTime == nullptr) {
            return "Unknown time";
        }

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localTime);

        return string(buffer);
    }

public:
    // Creates the required number of parking slots
    ParkingSystem(int totalSlots) {
        for (int i = 1; i <= totalSlots; i++) {
            slots.push_back({i, false});
        }
    }

    // Counts the number of slots that are currently available
    int availableSlots() const {
        int count = 0;

        for (const auto& slot : slots) {
            if (!slot.occupied) {
                count++;
            }
        }

        return count;
    }

    // Displays the current parking availability
    void showAvailability() const {
        cout << "\n===== PARKING AVAILABILITY =====\n";
        cout << "Total slots: " << slots.size() << endl;
        cout << "Available slots: " << availableSlots() << endl;
        cout << "Occupied slots: "
             << slots.size() - availableSlots() << endl;

        cout << "\nSlot status:\n";

        for (const auto& slot : slots) {
            cout << "Slot " << slot.slotNumber << ": ";

            if (slot.occupied) {
                cout << "Occupied";
            } else {
                cout << "Available";
            }

            cout << endl;
        }
    }

    // Handles the process of a vehicle entering the parking lot
    void vehicleEntry() {
        // Check if there is space before allowing entry
        if (availableSlots() == 0) {
            cout << "\nSorry, the parking lot is full.\n";
            return;
        }

        string plate;
        string owner;

        cout << "\nEnter vehicle plate number: ";
        cin >> plate;

        // Check whether this vehicle is already parked
        if (parkedVehicles.find(plate) != parkedVehicles.end()) {
            cout << "This vehicle is already inside the parking lot.\n";
            return;
        }

        cout << "Enter owner name: ";

        // Clear the newline left in the input buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, owner);

        int selectedSlot = -1;

        // Find the first available slot
        for (auto& slot : slots) {
            if (!slot.occupied) {
                selectedSlot = slot.slotNumber;
                slot.occupied = true;
                break;
            }
        }

        // Get the current time as the entry time
        time_t entryTime = time(nullptr);

        // Create a Vehicle object
        Vehicle vehicle{
            plate,
            owner,
            selectedSlot,
            entryTime
        };

        // Add the vehicle to the list of parked vehicles
        parkedVehicles[plate] = vehicle;

        cout << "\nVehicle successfully entered.\n";
        cout << "Assigned slot: " << selectedSlot << endl;
        cout << "Entry time: " << formatTime(entryTime) << endl;
        cout << "Available slots remaining: "
             << availableSlots() << endl;
    }

    // Handles vehicle exit and calculates the parking fee
    void vehicleExit() {
        string plate;

        cout << "\nEnter vehicle plate number: ";
        cin >> plate;

        // Search for the vehicle using its plate number
        auto it = parkedVehicles.find(plate);

        if (it == parkedVehicles.end()) {
            cout << "Vehicle not found in the parking lot.\n";
            return;
        }

        // Get the exit time
        time_t exitTime = time(nullptr);

        // Copy the vehicle information before removing it
        Vehicle vehicle = it->second;

        // Calculate the time spent in seconds
        double seconds = difftime(exitTime, vehicle.entryTime);

        // Convert seconds into hours
        double hours = seconds / 3600.0;

        // Round up so that part of an hour is charged as a full hour
        int billableHours = static_cast<int>(ceil(hours));

        // Make sure the minimum charge is one hour
        if (billableHours < 1) {
            billableHours = 1;
        }

        // Calculate the total amount to pay
        double amount = billableHours * ratePerHour;

        // Make the vehicle's parking slot available again
        for (auto& slot : slots) {
            if (slot.slotNumber == vehicle.slotNumber) {
                slot.occupied = false;
                break;
            }
        }

        // Create a record of the completed parking session
        ParkingSession session{
            vehicle.plateNumber,
            vehicle.slotNumber,
            vehicle.entryTime,
            exitTime,
            amount
        };

        // Add the session to the parking history
        completedSessions.push_back(session);

        // Remove the vehicle from the currently parked vehicles
        parkedVehicles.erase(it);

        // Display the parking bill
        cout << fixed << setprecision(2);
        cout << "\n===== PARKING BILL =====\n";
        cout << "Plate number: " << vehicle.plateNumber << endl;
        cout << "Owner: " << vehicle.ownerName << endl;
        cout << "Slot: " << vehicle.slotNumber << endl;
        cout << "Entry time: "
             << formatTime(vehicle.entryTime) << endl;
        cout << "Exit time: "
             << formatTime(exitTime) << endl;
        cout << "Time spent: " << hours << " hour(s)" << endl;
        cout << "Billable hours: " << billableHours << endl;
        cout << "Amount to pay: KSh " << amount << endl;
        cout << "Vehicle exited successfully.\n";
        cout << "Available slots now: "
             << availableSlots() << endl;
    }

    // Displays vehicles that are currently inside the parking lot
    void showParkedVehicles() const {
        cout << "\n===== PARKED VEHICLES =====\n";

        if (parkedVehicles.empty()) {
            cout << "No vehicles are currently parked.\n";
            return;
        }

        for (const auto& item : parkedVehicles) {
            const Vehicle& vehicle = item.second;

            cout << "Plate: " << vehicle.plateNumber
                 << " | Owner: " << vehicle.ownerName
                 << " | Slot: " << vehicle.slotNumber
                 << " | Entry: "
                 << formatTime(vehicle.entryTime)
                 << endl;
        }
    }

    // Displays the history of vehicles that have already exited
    void showCompletedSessions() const {
        cout << "\n===== PARKING HISTORY =====\n";

        if (completedSessions.empty()) {
            cout << "No completed parking sessions yet.\n";
            return;
        }

        cout << fixed << setprecision(2);

        for (const auto& session : completedSessions) {
            cout << "Plate: " << session.plateNumber
                 << " | Slot: " << session.slotNumber
                 << " | Paid: KSh " << session.amountPaid
                 << " | Entry: "
                 << formatTime(session.entryTime)
                 << " | Exit: "
                 << formatTime(session.exitTime)
                 << endl;
        }
    }
};

int main() {
    int totalSlots;

    cout << "===== SMART PARKING MANAGEMENT SYSTEM =====\n";
    cout << "Enter total number of parking slots: ";

    // Check that the user enters a valid number
    while (!(cin >> totalSlots) || totalSlots <= 0) {
        cout << "Please enter a number greater than 0: ";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Create the parking system
    ParkingSystem parking(totalSlots);

    int choice;

    // Keep displaying the menu until the user chooses 0
    do {
        cout << "\n========== MENU ==========\n";
        cout << "1. Check parking availability\n";
        cout << "2. Vehicle entry\n";
        cout << "3. Vehicle exit and payment\n";
        cout << "4. View parked vehicles\n";
        cout << "5. View parking history\n";
        cout << "0. Exit program\n";
        cout << "Choose an option: ";

        // Check that the menu choice is a number
        while (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (choice) {
            case 1:
                parking.showAvailability();
                break;

            case 2:
                parking.vehicleEntry();
                break;

            case 3:
                parking.vehicleExit();
                break;

            case 4:
                parking.showParkedVehicles();
                break;

            case 5:
                parking.showCompletedSessions();
                break;

            case 0:
                cout << "\nThank you for using the Smart Parking System.\n";
                break;

            default:
                cout << "Invalid option. Please choose from 0 to 5.\n";
        }

    } while (choice != 0);

    return 0;
}
