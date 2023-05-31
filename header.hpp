#ifndef UNTITLED1_HEADER_HPP
#define UNTITLED1_HEADER_HPP
#include <iostream>
#include <vector>
#include <map>
#include <stack>
using namespace std;

class Room final {
private:
    int roomID;
    int capacity;
    int price;
    bool available;
public:
    Room(int roomID, int capacity, int price, bool available=true) noexcept : roomID(roomID), capacity(capacity), price(price), available(available) { }
    int getRoomID() const noexcept { return this->roomID; }
    int getCapacity() const noexcept { return this->capacity; }
    int getPrice() const noexcept { return this->price; }
    bool getAvailable() const noexcept { return this->available; }
    void setRoomID(int newRoomID)  noexcept { this->roomID = newRoomID; }
    void setCapacity(int newCapacity)  noexcept { this->capacity = newCapacity; }
    void setPrice(int newPrice)  noexcept { this->price = newPrice; }
    inline friend ostream& operator<<(ostream& out, const Room &room) noexcept { return out << "ID:" << room.roomID << endl << "capacity:" << room.capacity << endl << "price for night:" << room.price << "$" << endl << "Availability:" << room.available; }
}; // G

class Address final {
private:
    string Country;
    string StreetName;
    string ZipCode;
    string City;
    string TelephoneNumber;
public:
    Address(string newCountry, string newStreetName, string newZipCode, string newCity, string newTelephoneNumber) noexcept : Country(newCountry), StreetName(newStreetName), ZipCode(newZipCode), City(newCity), TelephoneNumber(newTelephoneNumber) { }
    vector<string> AdressInfo() { return { this->Country,this->StreetName, this->ZipCode, this->City, this->TelephoneNumber }; }
    inline friend ostream& operator<<(ostream& out, const Address &address) noexcept { return out << "Country:" << address.Country << endl << "StreetName:" << address.StreetName << endl << "ZipCode:" << address.ZipCode << endl << "City:" << address.City << endl << "Telephone Number:" << address.TelephoneNumber << endl; }
    inline friend bool operator==(Address &address1, Address &address2) { return address1.AdressInfo() == address2.AdressInfo(); }
}; // G

class DateTime final {
private:
    int year;
    int day;
    int month;
    constexpr static int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static int countLeapYears(DateTime date){
        int years = date.year;
        if (date.month <= 2) years--;
        return years / 4 - years / 100 + years / 400;
    }
public:
    DateTime(int year, int month, int day) noexcept : year(year), day(day), month(month) { }
    inline friend int operator-(DateTime &date1, DateTime &date2) {
        long int n1 = date1.year * 365 + date1.day;
        for (int i = 0; i < date1.month - 1; i++) n1 += monthDays[i];
        n1 += countLeapYears(date1);
        long int n2 = date2.year * 365 + date2.day;
        for (int i = 0; i < date2.month - 1; i++) n2 += monthDays[i];
        n2 += countLeapYears(date2);
        return (n2 - n1);
    }
    void setYear(int year) noexcept { this->year = year; }
    void setDay(int day) noexcept { this->day = day; }
    void setMonth(int month) noexcept { this->month = month; }
    inline friend ostream& operator<<(ostream& out, const DateTime &date) { return out << date.day << '.' << date.month << '.' << date.year << endl; }
}; // G

class Client {

};

class Opinion {

};

class Menu final {
private:
    map<string,double> prices;
public:
    void addToMenu(string name, double price) noexcept { prices.insert({name,price}); }
    void removeFromMenu(string name) noexcept { prices.erase(name); }
    double checkPrice(string name) { prices.at(name); }
    inline friend ostream& operator<<(ostream& out, const Menu &menu) { out << "---Nazwa---" << "---Cena---";  for(const auto& n : menu.prices) out << n.first << " " << n.second << endl; return out; }
}; // G

class Order {

};

class Restauration final {
private:
    Menu menu;
    stack<Order> orders;
public:
    inline Restauration(Menu menu1, stack<Order> orders1) noexcept : menu(menu1), orders(orders1) { }
    inline Order doOrder() { orders.pop(); }
    inline void addOrer(Order order) noexcept { orders.push(order); }
    inline friend ostream& operator<<(ostream& out, const Restauration &restauration) { out << restauration.menu << restauration.orders << endl; }
};

class Hotel {
private:
    string Name;
    Address HotelAddress;
    vector<Room> Rooms;
    vector<Opinion> Opinions;
    Restauration HotelRestauration;
public:
    Hotel(string newName, Address newAddress, vector<Room>newRooms, vector<Opinion>newOpinions, Restauration newRestauration) noexcept : Name(newName), HotelAddress(newAddress), Rooms(newRooms), Opinions(newOpinions), HotelRestauration(newRestauration) { }
    void AddRoom(const Room &newRoom){ this->Rooms.push_back(newRoom); }
    int SearchForRoom(int RoomID) { for(int i = 0;i<Rooms.size();i++){ if(Rooms[i].getRoomID()==RoomID){ return i; } } return -1; }
    inline friend ostream& operator<<(ostream& out, const Hotel &hotel) { for(auto room : hotel.Rooms){ out << room << endl; } return out; }
};

class Invoice final {

};

class Reservation {
private:
    int id;
    DateTime checkInDate;
    DateTime checkOutDate;
    vector<Room> rooms;
    Invoice invoice;
public:
    Reservation(int id, DateTime checkInDate, DateTime checkOutDate, vector<Room> rooms, Invoice inv) : id(id), checkInDate(checkInDate),checkOutDate(checkOutDate), rooms(rooms), invoice(inv) {}
    template<typename T>
    inline friend ostream& operator<<(ostream& out, const vector<T>&vec){ for(auto n : vec) out << n; return out; }
    //inline friend ostream& operator<<(ostream& out, const Reservation &res) { return out << "ID: " << res.id << endl << "Data zameldownia: " << res.checkInDate << endl << "Data wymeldowania: " << res.checkOutDate << endl << "--- Pokoje ---" << endl << &res.rooms << endl; }
}; // G

class ReservationSystem {};
class Application {};
class Administrator {};
class Services {

};
class AdditionalServices final {
    virtual ~AdditionalServices() = default;

};
#endif //UNTITLED1_HEADER_HPP