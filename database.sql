-- Smart Parking Management System database design

CREATE TABLE ParkingSlots (
    slot_id INTEGER PRIMARY KEY,
    slot_number INTEGER UNIQUE NOT NULL,
    status VARCHAR(20) NOT NULL
);

CREATE TABLE Vehicles (
    vehicle_id INTEGER PRIMARY KEY,
    plate_number VARCHAR(20) UNIQUE NOT NULL,
    owner_name VARCHAR(100) NOT NULL
);

CREATE TABLE ParkingSessions (
    session_id INTEGER PRIMARY KEY,
    vehicle_id INTEGER NOT NULL,
    slot_id INTEGER NOT NULL,
    entry_time DATETIME NOT NULL,
    exit_time DATETIME,
    amount_paid DECIMAL(10,2),
    FOREIGN KEY (vehicle_id) REFERENCES Vehicles(vehicle_id),
    FOREIGN KEY (slot_id) REFERENCES ParkingSlots(slot_id)
);

CREATE TABLE Payments (
    payment_id INTEGER PRIMARY KEY,
    session_id INTEGER NOT NULL,
    amount DECIMAL(10,2) NOT NULL,
    payment_time DATETIME NOT NULL,
    payment_status VARCHAR(20) NOT NULL,
    FOREIGN KEY (session_id) REFERENCES ParkingSessions(session_id)
);
