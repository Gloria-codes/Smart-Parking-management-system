
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>

using namespace std;


//          CORE DATABASE STRUCTS

// 1. Manages individual parking spaces and their real-time availability statuses
struct ParkingSlot {
    int slotId;
    string category;       // e.g., Regular,Disabled,Electric
    bool isAvailable;      // True if empty, False if occupied
};

// 2. Encapsulates the dynamic pricing tier matrix defined by the client
struct ParkingRate {
    int maxMinutes;        // Upper minute bound for this tier
    double rateKshs;       // Cost associated with this tier in Kenyan Shillings
};

// 3. Tracks active and historic vehicle tracking sessions
struct ParkingSession {
    string licensePlate;
    int assignedSlotId;
    time_t checkInTime;    // System epoch timestamp at entrance
    time_t checkOutTime;   // System epoch timestamp at exit (0 if active)
    double amountPaid;     // Balance cleared upon processing
    bool isPaid;           // Explicit state flag to safely trigger gate barrier
};

// 4. The core Database Engine holding runtime tables in memory
struct ParkingDatabase {
    vector<ParkingSlot> slotsTable;
    vector<ParkingRate> ratesTable;
    vector<ParkingSession> sessionsTable;
};


//      DATABASE OPERATIONS & BUSINESS LOGIC


/**
 * Pre-loads the specific operational rates requested by the MMU client brief.
 */
void initializeDatabase(ParkingDatabase &db, int totalSlots) {
    // Populate physical parking lot slots
    for (int i = 1; i <= totalSlots; i++) {
        db.slotsTable.push_back({i, "Regular", true});
    }

    // Populate billing tiers strictly mapping MMU requirements
    // 1. Up to 30 minutes: Free
    db.ratesTable.push_back({30, 0.0});       
    // 2. Up to 2 hours (120 mins): Kshs. 50
    db.ratesTable.push_back({120, 50.0});     
    // 3. Up to 4 hours (240 mins): Kshs. 100
    db.ratesTable.push_back({240, 100.0});    
    // 4. Up to 6 hours (360 mins): Kshs. 300
    db.ratesTable.push_back({360, 300.0});    
    // 5. Over six hours (represented by large sentinel): Kshs. 500
    db.ratesTable.push_back({99999, 500.0});  
}

/**
 * Provides an instantaneous visual display panel of available slots before physical entry.
 */
void displayAvailableSlots(const ParkingDatabase &db) {
    int availableCount = 0;
    cout << << endl;
    cout << "LIVE PARKING DISPLAY PANEL      " << endl;
    cout << << endl;
    
    for (size_t i = 0; i < db.slotsTable.size(); i++) {
        const auto &slot = db.slotsTable[i];
        cout << "Slot " << setfill('0') << setw(2) << slot.slotId << ": ";
        if (slot.isAvailable) {
            cout << "[ AVAILABLE ]   ";
            availableCount++;
        } else {
            cout << "[ OCCUPIED  ]   ";
        }
        // Print 4 slots per row for neat visual alignment
        if ((i + 1) % 4 == 0) cout << "\n";
    }
    
    cout << "\n\n>> Total Available Parking Slots Left: " << availableCount << " / " << db.slotsTable.size() << endl;
    cout << "\n" << endl;
}

/**
 * Records a vehicle on arrival, updates slot state, and creates an active session.
 */
bool registerVehicleArrival(ParkingDatabase &db, string plate) {
    for (auto &slot : db.slotsTable) {
        if (slot.isAvailable) {
            slot.isAvailable = false; // Dynamically claim slot
            
            ParkingSession newSession;
            newSession.licensePlate = plate;
            newSession.assignedSlotId = slot.slotId;
            newSession.checkInTime = time(0); // Capture current machine timestamp
            newSession.checkOutTime = 0;
            newSession.amountPaid = 0.0;
            newSession.isPaid = false;

            db.sessionsTable.push_back(newSession);
            cout << ">>> ACCESS GRANTED: Vehicle " << plate << " assigned to Slot " << slot.slotId << "." << endl;
            return true;
        }
    }
    cout << ">>> ACCESS DENIED: Parking Lot is Full! Drivers redirected via visual board." << endl;
    return false;
}

/**
 * Helper function mapping total duration minutes against client pricing table structures.
 */
double calculateFee(const ParkingDatabase &db, long durationMinutes) {
    for (const auto &rate : db.ratesTable) {
        if (durationMinutes <= rate.maxMinutes) {
            return rate.rateKshs;
        }
    }
    return 500.0; // Fallback maximum pricing boundary
}

/**
 * Processes billing transactions, updates payment state flags, and opens exit barriers.
 */
void processVehicleExit(ParkingDatabase &db, string plate, int simulatedDurationMins = -1) {
    for (auto &session : db.sessionsTable) {
        // Look for matching active session that hasn't cleared payment yet
        if (session.licensePlate == plate && !session.isPaid) {
            session.checkOutTime = time(0);
            
            // Allow manual timing simulation to verify assignment pricing requirements easily
            long durationMins = (simulatedDurationMins >= 0) ? 
                                 simulatedDurationMins : 
                                 (difftime(session.checkOutTime, session.checkInTime) / 60);

            double fee = calculateFee(db, durationMins);
            
            cout << "<< endl;
            cout << "       OUTBOUND BILLING INVOICE           " << endl;
            cout << << endl;
            cout << " Vehicle Plate   : " << plate << endl;
            cout << " Assigned Slot   : " << session.assignedSlotId << endl;
            cout << " Parking Duration: " << durationMins << " minutes" << endl;
            cout << " Total Bill Due  : Kshs. " << fee << endl;
            cout << << endl;

            // Handle client step logic: Barrier opens automatically ON payment
            session.amountPaid = fee;
            session.isPaid = true;
            cout << ">>> Payment Verified: Kshs. " << fee << " processed successfully." << endl;

            // Free the structural space table resource back to the open pool
            for (auto &slot : db.slotsTable) {
                if (slot.slotId == session.assignedSlotId) {
                    slot.isAvailable = true;
                    break;
                }
            }

            cout << ">>> ACTION: [BARRIER OPENED] Safe travels  from Multimedia University!" << endl;
            cout << << endl;
            return;
        }
    }
    cout << ">>> ERROR: No active parking record found for plate number: " << plate << endl;
}

// ==========================================
//             SIMULATION RUNNER
// ==========================================
int main() {
    ParkingDatabase db;
    
    // Instantiate our database with 8 structural parking slot units
    initializeDatabase(db, 8); 

    // Simulation Step 1: Initial Entry Board State
    displayAvailableSlots(db);

    // Simulation Step 2: Inbound vehicles arriving at the entry barrier 
    registerVehicleArrival(db, "KCA 123A");
    registerVehicleArrival(db, "KCD 789B");
    registerVehicleArrival(db, "KBR 456C");

    // Simulation Step 3: View changed states on the dashboard display
    displayAvailableSlots(db);

    // Simulation Step 4: Outbound car exit updates
    // Simulating KCA 123A departing after exactly 15 minutes (Should map to Kshs 0 - Free tier)
    processVehicleExit(db, "KCA 123A", 15);

    // Simulating KCD 789B departing after exactly 3 hours / 180 minutes (Should map to Kshs 100 tier)
    processVehicleExit(db, "KCD 789B", 180);

    // Simulation Step 5: Verify slots have recycled cleanly back to 'AVAILABLE' state
    displayAvailableSlots(db);

    return 0;
}
