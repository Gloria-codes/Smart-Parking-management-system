# Algorithms - Modern Parking System

## 1. Display Available Parking Slots

1. Start.
2. Access the list of parking slots.
3. Check each slot.
4. If occupied, display OCCUPIED.
5. Otherwise, display AVAILABLE.
6. Continue until all slots are checked.
7. Stop.

### Pseudocode

START
FOR each parking slot
    IF slot is occupied
        Display "OCCUPIED"
    ELSE
        Display "AVAILABLE"
    END IF
END FOR
STOP

## 2. Vehicle Arrival

1. Start.
2. Ask for the vehicle registration number.
3. Check whether the vehicle is already parked.
4. If it is already parked, display a message and stop.
5. Search for an available slot.
6. If no slot is available, display "Parking is full" and stop.
7. Assign the available slot.
8. Record registration number, slot number and arrival time.
9. Change the slot status to OCCUPIED.
10. Open the entrance barrier.
11. Display the assigned slot.
12. Stop.

## 3. Parking Fee Calculation

1. Start.
2. Input total parking time in minutes.
3. If time <= 30 minutes, fee = Ksh 0.
4. Else if time <= 120 minutes, fee = Ksh 50.
5. Else if time <= 240 minutes, fee = Ksh 100.
6. Else if time <= 360 minutes, fee = Ksh 300.
7. Otherwise, fee = Ksh 500.
8. Display the fee.
9. Stop.

## 4. Vehicle Exit

1. Start.
2. Ask for the vehicle registration number.
3. Search for the vehicle.
4. If not found, display an error and stop.
5. Record the exit time.
6. Calculate total parking time.
7. Calculate the parking fee.
8. Display the parking receipt.
9. Ask for payment.
10. If payment is insufficient, keep the barrier closed.
11. Otherwise calculate change.
12. Mark the parking slot AVAILABLE.
13. Remove the vehicle from active parking records.
14. Open the exit barrier.
15. Stop.

## 5. Overall System

START

REPEAT
    Display system menu
    Read user's choice

    IF choice = 1
        Display parking slots
    ELSE IF choice = 2
        Process vehicle arrival
    ELSE IF choice = 3
        Process vehicle exit
    ELSE IF choice = 4
        Display parked vehicles
    ELSE IF choice = 5
        Exit system
    ELSE
        Display invalid choice
    END IF
UNTIL choice = 5

STOP
