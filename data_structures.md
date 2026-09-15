# Data Structures Used

## 1. Vector

The C++ program uses:


vector<ParkingSlot> parkingSlots;
vector<Vehicle> parkedVehicles;

Vectors store the parking slots and vehicles currently in the parking area.

### Why we use vector?

- It supports dynamic storage.
- Vehicles can be added when they arrive.
- Vehicles can be removed when they leave.
- It provides easy access to stored elements.

## 2. Structure

The program uses structures to group related information.


struct ParkingSlot {
    int slotNumber;
    bool occupied;
    string vehicleRegistration;
};


This stores information about a parking slot.

struct Vehicle {
    string registrationNumber;
    int slotNumber;
    time_t arrivalTime;
};


This stores information about a vehicle.

## 3. Boolean


bool occupied;


It represents whether a slot is occupied or available.

- true = occupied
- false= available

## 4. String

Strings store vehicle registration numbers such as KDA 123A.

## 5. time_t

time_t stores arrival and exit times so that the system can calculate the total parking duration.
