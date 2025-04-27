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
};