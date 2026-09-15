# Modern Parking System

## Introduction

The Modern Parking System is a C++ based parking management system designed to automate parking operations.

The system allows drivers to view available parking slots before entering, records vehicles when they arrive, calculates parking duration, calculates parking fees, processes payments and allows exit after successful payment.

## Objectives

- Display available and occupied parking slots.
- Record vehicles on arrival.
- Assign available parking slots.
- Record arrival time.
- Calculate total parking duration.
- Calculate parking fees automatically.
- Process parking payments.
- Calculate change.
- Release parking slots after vehicles exit.
- Open the exit barrier after successful payment.

## Parking Fee Structure

| Parking Duration | Fee |
| Up to 30 minutes | Ksh 0 |
| Up to 2 hours | Ksh 50 |
| Up to 4 hours | Ksh 100 |
| Up to 6 hours | Ksh 300 |
| Over 6 hours | Ksh 500 |

## Main Modules

1. **Parking Slot Module** - displays available and occupied slots.
2. **Vehicle Arrival Module** - records a vehicle and assigns a slot.
3. **Fee Calculation Module** - calculates the fee based on parking duration.
4. **Vehicle Exit Module** - calculates time, displays the receipt and processes exit.
5. **Payment Module** - checks payment, calculates change and opens the barrier after successful payment.

## Data Structures

The C++ implementation uses:

- vector
- struct
- bool
- string
- time_t

Vectors are used for dynamic storage of slots and active vehicles. Structures group related information about vehicles and parking slots.

## Database

The proposed MySQL database contains:

- parking_slots
- vehicles
- parking_records
- payments


## Requirements

To run the C++ program you need:

- A C++ compiler such as G++
- A C++ IDE such as VS Code, Code::Blocks, or Eclipse with C++ support

MySQL is required if you want to create and use the database structure included in this repository.

## How to Run

### Using G++

g++ parking_system.cpp -o parking_system


Then run:

**Windows:**

parking_system.exe


**Linux/macOS:**

./parking_system


### Using an IDE

1. Open the 'src/parking_system.cpp' file.
2. Open it in your C++ IDE.
3. Build/compile the program.
4. Run the program.
5. Select an option from the menu.

## System Menu

1. View Parking Slot Availability
2. Vehicle Arrival
3. Vehicle Exit
4. View Parked Vehicles
5. Exit System


## Example

A driver enters:


KDA 123A


The system assigns an available slot and records the arrival time.

When the driver exits, the system calculates:

- Arrival time
- Exit time
- Total parking duration
- Parking fee
- Amount paid
- Change

After successful payment, the slot becomes available and the exit barrier opens.


## Author

"Gloria Magoma Karani"


