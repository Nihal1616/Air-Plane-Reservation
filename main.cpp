
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stack>
#include <string>

using namespace std;

struct Passenger {
    string name;
    int age;
    string gender;
    string seatClass;
    int seatNumber;
    Passenger* next;

    Passenger(string n, int a, string g, string cls, int sn)
        : name(n), age(a), gender(g), seatClass(cls), seatNumber(sn), next(nullptr) {}
};