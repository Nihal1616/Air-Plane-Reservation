Airline Ticket Reservation System (C++)

This project is a console-based Airline Ticket Reservation System built in C++ using fundamental data structures such as arrays, linked lists, queues, stacks, and STL containers like vector, queue, and unordered_map. It simulates basic operations of booking, cancelling, and managing flight tickets for a single flight.

Data Structures Used:
•  Linked List: For dynamically managing the list of booked passengers.
•  Queue: To manage the waitlist in FIFO order.
•  Stack: To store and undo canceled tickets.
•  Vectors: To represent seat occupancy (true = booked, false = available).
•  Unordered Map: For managing multiple flights (currently supports one flight for simplicity).

Features:
1. Ticket Booking
    •	Users can book a ticket by entering their name, age, gender, and seat class (Economy or           Business).
    •	The system assigns the first available seat in the requested class using a vector<bool> to       track occupancy.
    •	If no seats are available in Economy class, the passenger is added to a waitlist (a               queue<string>) instead of being rejected immediately.
    •	A Passenger node is created dynamically and added to a singly linked list representing the       current passenger list for that flight.
    •	Business class bookings do not support a waitlist currently and are simply rejected if           full.
2. Ticket Cancellation
    •	Passengers can cancel a booking by providing their name.
    •	The system searches through the linked list of passengers to find the matching record.
    •	On successful match:
        o	The corresponding seat is freed (set to false in the seat vector).
        o	The passenger node is removed from the linked list.
        o	The canceled ticket is pushed onto a stack (stack<Passenger*>) to allow undo                     functionality.
    •	If the canceled seat is in Economy, and the waitlist is not empty, the first person in the       queue is automatically assigned the             newly freed seat using their name (with placeholder age and gender).
3. Undo Cancellation
    •	This feature lets you undo the most recent ticket cancellation.
    •	It pops the top passenger from the cancelStack and attempts to rebook them using the original booking details (name, age, gender, seat           class).
    •	If a seat is available, the booking is restored, and the passenger is re-added to the list.
    •	This feature is useful in scenarios of accidental cancellations.
4. Check Seat Availability
    •	Displays the current number of unbooked seats in both Economy and Business classes.
    •	Internally, it counts the number of false entries in the economySeats and businessSeats vectors.

5. Passenger List Display
•	Shows a formatted list of all booked passengers for the current flight.
•	Includes passenger name, seat number, and seat class.
•	Uses simple iteration over the linked list to gather and display information.

   





