# Smart Parking Management System

A beginner-friendly C++ console project for managing a parking lot.

## Features

- Shows total, available and occupied parking slots.
- Records vehicles when they enter.
- Automatically assigns an available parking slot.
- Records entry time.
- Records vehicle owner and plate number.
- Calculates parking duration when a vehicle exits.
- Calculates the amount to pay.
- Frees the parking slot after exit.
- Shows currently parked vehicles.
- Shows completed parking history.

## Data structures

1. `vector<ParkingSlot>` - stores the parking slots.
2. `unordered_map<string, Vehicle>` - quickly finds vehicles using their plate number.
3. `vector<ParkingSession>` - stores completed parking sessions.

## Compile and run

With g++:

```bash
g++ main.cpp -o parking_system
```

Run on Windows:

```bash
parking_system.exe
```

Or:

```bash
./parking_system
```

## Database design

For a real application, the C++ program should connect to a database such as SQLite or MySQL.

### ParkingSlots

- `slot_id` - Primary Key
- `slot_number`
- `status`

### Vehicles

- `vehicle_id` - Primary Key
- `plate_number`
- `owner_name`

### ParkingSessions

- `session_id` - Primary Key
- `vehicle_id` - Foreign Key
- `slot_id` - Foreign Key
- `entry_time`
- `exit_time`
- `amount_paid`

### Payments

- `payment_id` - Primary Key
- `session_id` - Foreign Key
- `amount`
- `payment_time`
- `payment_status`

## Future improvements

- Add a graphical user interface.
- Add SQLite/MySQL database storage.
- Add different prices for different vehicle types.
- Add online parking availability.
- Add user/admin login.
- Add payment integration.
- Add QR-code based vehicle entry.
