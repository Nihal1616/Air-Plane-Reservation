#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;
class Flight;

class Passenger {
    string name;
    int age;
    string gender;
    string seatClass;
    int seatNumber;
    Passenger* next;

    Passenger(string n, int a, string g, string cls, int sn)
        : name(n), age(a), gender(g), seatClass(cls), seatNumber(sn), next(nullptr) {}
        friend class Flight;
};

class Flight {
    string flightNumber;
    int totalSeatsEconomy;
    int totalSeatsBusiness;
    vector<bool> economySeats;
    vector<bool> businessSeats;
    Passenger* passengerListHead;
    queue<string> economyWaitlist;
    stack<Passenger*> cancelStack;

public:
    Flight(string fno, int eco, int bus) {
        flightNumber = fno;
        totalSeatsEconomy = eco;
        totalSeatsBusiness = bus;
        economySeats.resize(eco, false);
        businessSeats.resize(bus, false);
        passengerListHead = nullptr;
    }

    void bookTicket(string name, int age, string gender, string cls) {
        int seatIndex = -1;
        if (cls == "Economy") {
            for (int i = 0; i < totalSeatsEconomy; ++i) {
                if (!economySeats[i]) {
                    seatIndex = i;
                    economySeats[i] = true;
                    break;
                }
            }
        } else if (cls == "Business") {
            for (int i = 0; i < totalSeatsBusiness; ++i) {
                if (!businessSeats[i]) {
                    seatIndex = i;
                    businessSeats[i] = true;
                    break;
                }
            }
        }

        if (seatIndex == -1) {
            cout << "No seats available in " << cls << ". Adding to waitlist.\n";
            economyWaitlist.push(name);
        } else {
            auto* p = new Passenger(name, age, gender, cls, seatIndex + 1);
            p->next = passengerListHead;
            passengerListHead = p;
            cout << "Ticket booked! Seat Number: " << p->seatNumber << "\n";
        }
    }


    void cancelTicket(string name) {
        Passenger* curr = passengerListHead;
        Passenger* prev = nullptr;

        while (curr != nullptr && curr->name != name) {
            prev = curr;
            curr = curr->next;
        }

        if (!curr) {
            cout << "Passenger not found.\n";
            return;
        }

        // Free seat
        if (curr->seatClass == "Economy")
            economySeats[curr->seatNumber - 1] = false;
        else
            businessSeats[curr->seatNumber - 1] = false;

        // Remove from linked list
        if (prev)
            prev->next = curr->next;
        else
            passengerListHead = curr->next;

        cancelStack.push(curr);
        cout << "Ticket for " << name << " canceled.\n";

        if (!economyWaitlist.empty()) {
            string waitName = economyWaitlist.front();
            economyWaitlist.pop();
            bookTicket(waitName, 30, "Unknown", "Economy"); 
        }
    }

    void undoCancel() {
        if (cancelStack.empty()) {
            cout << "No recent cancellations to undo.\n";
            return;
        }
        Passenger* lastCanceled = cancelStack.top();
        cancelStack.pop();
        cout << "Restoring ticket for " << lastCanceled->name << "...\n";
        bookTicket(lastCanceled->name, lastCanceled->age, lastCanceled->gender, lastCanceled->seatClass);
    }

    void checkAvailability(){
        int freeEco = 0, freeBus = 0;
        for (bool seat : economySeats)
            if (!seat) ++freeEco;
        for (bool seat : businessSeats)
            if (!seat) ++freeBus;

        cout << "Available Seats - Economy: " << freeEco << ", Business: " << freeBus << "\n";

    }

    void showPassengers() {
        Passenger* temp = passengerListHead;
        cout << "Passenger List for Flight " << flightNumber << ":\n";
        while (temp != nullptr) {
            cout << "- " << temp->name << " | Seat: " << temp->seatNumber
                 << " | Class: " << temp->seatClass << "\n";
            temp = temp->next;
        }
        
    }


};


int main() {
    unordered_map<string, Flight*> flights;
    flights["AI101"] = new Flight("AI101", 5, 2); 

    int choice;
    string fname = "AI101";

    do {
        cout << "\n=== Airline Reservation Menu ===\n";
        cout << "1. Book Ticket\n2. Cancel Ticket\n3. Check Availability\n4. Show Passengers\n5. Undo Cancel\n0. Exit\n";
        cin >> choice;

        string name, gender, cls;
        int age;

        switch (choice) {
            case 1:
                cout << "Enter Name, Age, Gender, Class (Economy/Business): ";
                cin >> name >> age >> gender >> cls;
                flights[fname]->bookTicket(name, age, gender, cls);
                break;
            case 2:
                cout << "Enter Passenger Name to Cancel: ";
                cin >> name;
                flights[fname]->cancelTicket(name);
                break;
            case 3:
                flights[fname]->checkAvailability();
                break;
            case 4:
                flights[fname]->showPassengers();
                break;
            case 5:
                flights[fname]->undoCancel();
                break;
            case 0:
                cout << "Thank you!\n";
                break;
            default:
                cout << "Invalid option.\n";
        }
    } while (choice != 0);

    return 0;
}

