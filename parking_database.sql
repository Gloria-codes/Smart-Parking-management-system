-- MODERN PARKING SYSTEM DATABASE
-- MySQL database structure

CREATE DATABASE IF NOT EXISTS modern_parking_system;
USE modern_parking_system;

-- Stores all parking slots.
CREATE TABLE parking_slots (
    slot_id INT AUTO_INCREMENT PRIMARY KEY,
    slot_number INT NOT NULL UNIQUE,
    status ENUM('AVAILABLE', 'OCCUPIED') NOT NULL DEFAULT 'AVAILABLE',
    vehicle_registration VARCHAR(20)
);

-- Stores vehicle information.
CREATE TABLE vehicles (
    vehicle_id INT AUTO_INCREMENT PRIMARY KEY,
    registration_number VARCHAR(20) NOT NULL UNIQUE,
    vehicle_type VARCHAR(30),
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

-- Stores each parking session.
CREATE TABLE parking_records (
    record_id INT AUTO_INCREMENT PRIMARY KEY,
    vehicle_id INT NOT NULL,
    slot_id INT NOT NULL,
    arrival_time DATETIME NOT NULL,
    exit_time DATETIME,
    total_minutes INT,
    parking_fee DECIMAL(10,2),
    status ENUM('PARKED', 'COMPLETED') NOT NULL DEFAULT 'PARKED',
    FOREIGN KEY (vehicle_id) REFERENCES vehicles(vehicle_id),
    FOREIGN KEY (slot_id) REFERENCES parking_slots(slot_id)
);

-- Stores payment information.
CREATE TABLE payments (
    payment_id INT AUTO_INCREMENT PRIMARY KEY,
    record_id INT NOT NULL,
    amount_due DECIMAL(10,2) NOT NULL,
    amount_paid DECIMAL(10,2) NOT NULL,
    change_amount DECIMAL(10,2) NOT NULL DEFAULT 0.00,
    payment_time DATETIME DEFAULT CURRENT_TIMESTAMP,
    payment_status ENUM('PENDING', 'PAID') NOT NULL DEFAULT 'PENDING',
    FOREIGN KEY (record_id) REFERENCES parking_records(record_id)
);

-- Create 10 initial parking slots.
INSERT INTO parking_slots (slot_number, status) VALUES
(1, 'AVAILABLE'),
(2, 'AVAILABLE'),
(3, 'AVAILABLE'),
(4, 'AVAILABLE'),
(5, 'AVAILABLE'),
(6, 'AVAILABLE'),
(7, 'AVAILABLE'),
(8, 'AVAILABLE'),
(9, 'AVAILABLE'),
(10, 'AVAILABLE');
