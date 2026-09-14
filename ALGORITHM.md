# Algorithm: Smart Parking Management System

1. Start.
2. Ask the administrator for the total number of parking slots.
3. Create all parking slots and mark them as available.
4. Display a menu:
   - Check availability
   - Vehicle entry
   - Vehicle exit/payment
   - View parked vehicles
   - View parking history
   - Exit
5. For availability:
   - Count slots marked available.
   - Display available and occupied slots.
6. For vehicle entry:
   - Check whether an empty slot exists.
   - If the parking lot is full, display a message.
   - Otherwise read the vehicle plate number and owner name.
   - Check that the vehicle is not already parked.
   - Assign the first available slot.
   - Record the current time as entry time.
   - Mark the slot occupied.
   - Display the remaining available slots.
7. For vehicle exit:
   - Ask for the vehicle plate number.
   - Find the vehicle.
   - If it does not exist, display an error.
   - Otherwise record the current time as exit time.
   - Calculate the time spent in the parking lot.
   - Round up to the next whole billable hour.
   - Multiply billable hours by the hourly rate.
   - Mark the vehicle's slot as available.
   - Save the completed parking session.
   - Remove the vehicle from the currently parked list.
   - Display the bill.
8. Repeat the menu until the user chooses Exit.
9. Stop.
