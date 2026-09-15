#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>  // Provides find_if() for searching vehicles.

using namespace std; 

/*
    MODERN PARKING SYSTEM
    Data Structures and Algorithms - Task One

    Modules:
    1. Display parking slot availability
    2. Record vehicle arrival
    3. Assign an available parking slot
    4. Calculate parking duration
    5. Calculate parking fees
    6. Process vehicle exit and payment
    7. Open the exit barrier after successful payment

    Data structures:
    - vector: stores parking slots and active vehicles
    - struct: groups related vehicle and slot information
*/

// This structure represents ONE parking slot in the parking area.
struct ParkingSlot {
    int slotNumber;  // Unique number assigned to the parking slot.
    bool occupied;
    string vehicleRegistration;
};

// This structure stores information about ONE vehicle currently parked.
struct Vehicle {
    string registrationNumber;  // Vehicle registration/number plate.

    int slotNumber;
    time_t arrivalTime;
};

// ParkingSystem contains all the operations required to manage the parking area.
class ParkingSystem {
private:
    // Vector is used because the number of active records can change dynamically.
    vector<ParkingSlot> parkingSlots;

    // Stores vehicles that are currently inside the parking area.
    vector<Vehicle> parkedVehicles;

public:
    // Constructor creates the required number of parking slots.
    // All slots are initially available.
    ParkingSystem(int numberOfSlots) {
        for (int i = 1; i <= numberOfSlots; ++i) {
            parkingSlots.push_back({i, false, ""});
        }
    }

    // Display all parking slots and their current status.
    void displayParkingSlots() const {
        // Loop through every slot and display its current status.
        cout << "\n=========================================\n";
        cout << "       PARKING SLOT AVAILABILITY\n";
        cout << "=========================================\n";

        for (const auto& slot : parkingSlots) {
            cout << "Slot " << setw(2) << slot.slotNumber << " : ";
            if (slot.occupied) {
                cout << "OCCUPIED (" << slot.vehicleRegistration << ")";
            } else {
                cout << "AVAILABLE";
            }
            cout << '\n';
        }
        cout << "\n";
    }

    // Find the first available slot.
    int findAvailableSlot() const {
        // Search from the first slot to the last slot.
        // The first unoccupied slot is returned.
        for (const auto& slot : parkingSlots) {
            if (!slot.occupied) {
                return slot.slotNumber;
            }
        }
        return -1;
    }

    // Register a vehicle and assign it an available slot.
    void vehicleArrival() {
        string registrationNumber;

        cout << "\n";
        cout << "VEHICLE ARRIVAL\n";
        cout << "\n";
        cout << "Enter vehicle registration number: ";
        cin >> registrationNumber;

        // Prevent the same vehicle from being registered twice.
        for (const auto& vehicle : parkedVehicles) {
            if (vehicle.registrationNumber == registrationNumber) {
                cout << "This vehicle is already parked.\n";
                return;
            }
        }

        int slotNumber = findAvailableSlot();

        if (slotNumber == -1) {
            cout << "\nSorry, the parking area is FULL.\n";
            return;
        }

        // time(nullptr) obtains the current system date and time.
        // This value becomes the vehicle's official arrival time.
        time_t arrivalTime = time(nullptr);

        // Store the new vehicle in the dynamic vector.
        parkedVehicles.push_back({
            registrationNumber,
            slotNumber,
            arrivalTime
        });

        parkingSlots[slotNumber - 1].occupied = true;
        parkingSlots[slotNumber - 1].vehicleRegistration =
            registrationNumber;

        cout << "\nVehicle successfully registered.\n";
        cout << "Vehicle Registration : " << registrationNumber << '\n';
        cout << "Assigned Slot        : " << slotNumber << '\n';
        cout << "Arrival Time         : " << ctime(&arrivalTime);
        cout << "Barrier: OPEN\n";
        cout << "Please proceed to your assigned parking slot.\n";
    }

    // Calculate the fee using the rates in the assignment.
    double calculateFee(long long minutes) const {
        if (minutes <= 30) {
            return 0.00;
        } else if (minutes <= 120) {
            return 50.00;
        } else if (minutes <= 240) {
            return 100.00;
        } else if (minutes <= 360) {
            return 300.00;
        } else {
            return 500.00;
        }
    }

    // Process vehicle exit, payment and barrier opening.
    void vehicleExit() {
        string registrationNumber;

        cout << "\n";
        cout << "VEHICLE EXIT\n";
        cout << "\n";
        cout << "Enter vehicle registration number: ";
        cin >> registrationNumber;

        // find_if() searches the vector for the vehicle registration number.
        // It returns an iterator pointing to the matching vehicle.
        auto vehicle = find_if(
            parkedVehicles.begin(),
            parkedVehicles.end(),
            [&](const Vehicle& v) {
                return v.registrationNumber == registrationNumber;
            }
        );

        if (vehicle == parkedVehicles.end()) {
            cout << "\nVehicle not found in the parking area.\n";
            return;
        }

        // Record the exact time when the vehicle requests to leave.
        time_t exitTime = time(nullptr);

        // Calculate the difference between exit and arrival in seconds.
        long long secondsParked =
            static_cast<long long>(difftime(exitTime, vehicle->arrivalTime));
        // Convert seconds to whole minutes for the fee calculation.
        long long minutesParked = secondsParked / 60;

        // Convert total minutes into hours and remaining minutes
        // so the duration is easier for the driver to understand.
        long long hours = minutesParked / 60;
        long long minutes = minutesParked % 60;
        // Determine the amount to pay according to the parking tariff.
        double fee = calculateFee(minutesParked);

        cout << "\n";
        cout << "           PARKING RECEIPT\n";
        cout << "\n";
        cout << "Vehicle Registration : "
             << vehicle->registrationNumber << '\n';
        cout << "Parking Slot         : "
             << vehicle->slotNumber << '\n';
        cout << "Arrival Time         : "
             << ctime(&vehicle->arrivalTime);
        cout << "Exit Time            : "
             << ctime(&exitTime);
        cout << "Total Time           : "
             << hours << " hour(s) " << minutes << " minute(s)\n";
        cout << fixed << setprecision(2);
        cout << "Parking Fee          : Ksh " << fee << '\n';
        cout << "\n";

        // Ask the driver for the amount of money they are paying.
        double payment;
        cout << "Enter amount paid: Ksh ";
        cin >> payment;

        // Payment must be at least equal to the parking fee.
        if (payment < fee) {
            cout << "\nInsufficient payment.\n";
            cout << "Vehicle cannot exit until full payment is made.\n";
            return;
        }

        // If payment is greater than the fee, calculate the driver's change.
        double change = payment - fee;
        cout << "Change               : Ksh " << change << '\n';
        cout << "\nPayment successful!\n";

        // Release the parking slot so another vehicle can use it.
        // Vector indexes start at 0, while slot numbers start at 1.
        int slotIndex = vehicle->slotNumber - 1;
        parkingSlots[slotIndex].occupied = false;
        parkingSlots[slotIndex].vehicleRegistration = "";

        // Remove the vehicle from the active parking vector.
        // The record is no longer needed for vehicles currently inside.
        parkedVehicles.erase(vehicle);

        cout << "\n";
        cout << "       PAYMENT SUCCESSFUL\n";
        cout << "       BARRIER: OPEN\n";
        cout << "       THANK YOU!\n";
        cout << "\n";
    }

    // Display all vehicles currently inside the parking area.
    void displayParkedVehicles() const {
        // If the vector is empty, there are no vehicles currently parked.
        cout << "\n";
        cout << "          PARKED VEHICLES\n";
        cout << "\n";

        if (parkedVehicles.empty()) {
            cout << "There are currently no parked vehicles.\n";
            return;
        }

        // Display the details of every vehicle currently inside.
        for (const auto& vehicle : parkedVehicles) {
            cout << "Registration : " << vehicle.registrationNumber << '\n';
            cout << "Slot         : " << vehicle.slotNumber << '\n';
            cout << "Arrival      : " << ctime(&vehicle.arrivalTime);
            cout << "\n";
        }
    }
};

int main() {
    // Create a parking area with 10 slots.
    ParkingSystem parking(10);

    int choice;

    do {
        cout << "\n\n";
        cout << "\n";
        cout << "       MODERN PARKING SYSTEM - KENYA\n";
        cout << "\n";
        cout << "1. View Parking Slot Availability\n";
        cout << "2. Vehicle Arrival\n";
        cout << "3. Vehicle Exit\n";
        cout << "4. View Parked Vehicles\n";
        cout << "5. Exit System\n";
        cout << "\n";
        cout << "Enter your choice: ";
        cin >> choice;

        // switch selects the module requested by the user.
        switch (choice) {
            case 1:
                parking.displayParkingSlots();
                break;
            case 2:
                parking.vehicleArrival();
                break;
            case 3:
                parking.vehicleExit();
                break;
            case 4:
                parking.displayParkedVehicles();
                break;
            case 5:
                cout << "\nThank you for using the Modern Parking System.\n";
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
