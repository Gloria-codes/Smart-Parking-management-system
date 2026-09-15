
 

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;

// Stores information about one parking slot
struct ParkingSlot
{
    int slotId;
    string category;
    bool isAvailable;
};

// Stores the different parking charges
struct ParkingRate
{
    int maxMinutes;
    double rateKshs;
};

// Stores information about a vehicle that has parked
struct ParkingSession
{
    string licensePlate;
    int assignedSlotId;
    time_t checkInTime;
    time_t checkOutTime;
    double amountPaid;
    bool isPaid;
};

// This structure acts like our small in-memory database
struct ParkingDatabase
{
    vector<ParkingSlot> slotsTable;
    vector<ParkingRate> ratesTable;
    vector<ParkingSession> sessionsTable;
};

// Creates the parking slots and adds the parking charges
void initializeDatabase(ParkingDatabase &db, int totalSlots)
{
    // Create the parking slots
    for (int i = 1; i <= totalSlots; i++)
    {
        ParkingSlot slot;
        slot.slotId = i;
        slot.category = "Regular";
        slot.isAvailable = true;

        db.slotsTable.push_back(slot);
    }

    // Add the parking rates
    // 30 minutes or less is free
    db.ratesTable.push_back({30, 0.0});

    // Up to 2 hours
    db.ratesTable.push_back({120, 50.0});

    // Up to 4 hours
    db.ratesTable.push_back({240, 100.0});

    // Up to 6 hours
    db.ratesTable.push_back({360, 300.0});

    // More than 6 hours
    db.ratesTable.push_back({99999, 500.0});
}

// Displays the parking slots and shows which ones are free
void displayAvailableSlots(const ParkingDatabase &db)
{
    int availableCount = 0;

    cout  << endl;
    cout << "        PARKING SLOTS AT MMU              " << endl;
    cout  << endl;

    for (size_t i = 0; i < db.slotsTable.size(); i++)
    {
        const ParkingSlot &slot = db.slotsTable[i];

        cout << "Slot " << setfill('0') << setw(2) << slot.slotId << ": ";

        if (slot.isAvailable)
        {
            cout << "[ AVAILABLE ]   ";
            availableCount++;
        }
        else
        {
            cout << "[ OCCUPIED  ]   ";
        }

        // Put four slots on each line
        if ((i + 1) % 4 == 0)
        {
            cout << "\n";
        }
    }

    cout << "\n\nTotal Available Slots: "
         << availableCount << " / " << db.slotsTable.size() << endl;
    cout << "\n" << endl;
}

// Registers a vehicle when it enters the parking area
bool registerVehicleArrival(ParkingDatabase &db, string plate)
{
    // Find the first available slot
    for (auto &slot : db.slotsTable)
    {
        if (slot.isAvailable)
        {
            slot.isAvailable = false;

            ParkingSession newSession;
            newSession.licensePlate = plate;
            newSession.assignedSlotId = slot.slotId;
            newSession.checkInTime = time(0);
            newSession.checkOutTime = 0;
            newSession.amountPaid = 0.0;
            newSession.isPaid = false;

            db.sessionsTable.push_back(newSession);

            cout << "Vehicle " << plate
                 << " has been given Slot "
                 << slot.slotId << "." << endl;

            return true;
        }
    }

    cout << "Parking lot is full." << endl;
    return false;
}

// Calculates the amount to pay depending on parking time
double calculateFee(const ParkingDatabase &db, long durationMinutes)
{
    for (const auto &rate : db.ratesTable)
    {
        if (durationMinutes <= rate.maxMinutes)
        {
            return rate.rateKshs;
        }
    }

    return 500.0;
}

// Processes a vehicle leaving the parking area
void processVehicleExit(ParkingDatabase &db, string plate,
                        int simulatedDurationMins = -1)
{
    for (auto &session : db.sessionsTable)
    {
        // Check if the vehicle has an unpaid parking session
        if (session.licensePlate == plate && !session.isPaid)
        {
            session.checkOutTime = time(0);

            long durationMins;

            // This allows us to test different parking times
            if (simulatedDurationMins >= 0)
            {
                durationMins = simulatedDurationMins;
            }
            else
            {
                durationMins =
                    (long)(difftime(session.checkOutTime,
                                    session.checkInTime) / 60);
            }

            double fee = calculateFee(db, durationMins);

            cout << "\n" << endl;
            cout << "             PARKING BILL                 " << endl;
            cout  << endl;
            cout << "Vehicle Plate    : " << plate << endl;
            cout << "Parking Slot     : " << session.assignedSlotId << endl;
            cout << "Parking Duration : " << durationMins
                 << " minutes" << endl;
            cout << "Amount to Pay     : Kshs. " << fee << endl;
            cout <<  << endl;

            // Mark the payment as completed
            session.amountPaid = fee;
            session.isPaid = true;

            cout << "Payment of Kshs. " << fee
                 << " has been received." << endl;

            // Make the parking slot available again
            for (auto &slot : db.slotsTable)
            {
                if (slot.slotId == session.assignedSlotId)
                {
                    slot.isAvailable = true;
                    break;
                }
            }

            cout << "Barrier opened. Vehicle can now leave." << endl;
            cout << "\n" << endl;

            return;
        }
    }

    cout << "No active parking record found for "
         << plate << "." << endl;
}

int main()
{
    ParkingDatabase db;

    // Start the parking system with 8 slots
    initializeDatabase(db, 8);

    // Show the slots before any vehicles arrive
    displayAvailableSlots(db);

    // Three vehicles enter
    registerVehicleArrival(db, "KCA 123A");
    registerVehicleArrival(db, "KCD 789B");
    registerVehicleArrival(db, "KBR 456C");

    // Show the slots after the vehicles enter
    displayAvailableSlots(db);

    // KCA 123A leaves after 15 minutes, so the charge is free
    processVehicleExit(db, "KCA 123A", 15);

    // KCD 789B leaves after 3 hours, so the charge is Kshs. 100
    processVehicleExit(db, "KCD 789B", 180);

    // Check that the two slots are available again
    displayAvailableSlots(db);

    return 0;
}
