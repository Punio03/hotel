#ifndef UNTITLED1_HEADER_HPP
#define UNTITLED1_HEADER_HPP
#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>
#include <fstream>
using namespace std;

class Reservation;
class Invoice;
class Hotel;
class Administrator;

class Room final {
private:
    int roomID;
    int capacity;
    int price;
    bool available;
public:
    Room(int roomID, int capacity, int price, bool available=true) : roomID(roomID), capacity(capacity),
                                                                     price(price), available(available) {}
    int getRoomID() const { return roomID; }
    int getCapacity() const { return capacity; }
    int getPrice() const { return price; }
    bool getAvailable() const { return available; }
    void setRoomID(int newRoomID) { roomID = newRoomID; }
    void setCapacity(int newCapacity) { capacity = newCapacity; }
    void setPrice(int newPrice) { price = newPrice; }
    void setAvailable(bool newAvailable) { available = newAvailable; }
    friend ostream& operator << (ostream& out, const Room &room);
}; //✅

class Address final {
private:
    string country;
    string streetName;
    string zipCode;
    string city;
    string phoneNumber;
public:
    Address(string country, string streetName, string zipCode, string city, string phoneNumber) : country(std::move(country)), streetName(std::move(streetName)),
                                                                                                  zipCode(std::move(zipCode)), city(std::move(city)),
                                                                                                  phoneNumber(std::move(phoneNumber)) {}
    vector<string> addressInfo() { return { country, streetName, zipCode, city, phoneNumber}; }
    string getCountry() { return country; }
    string getStreetName() { return streetName; }
    string getZipCode() { return zipCode; }
    string getCity() { return city; }
    string getPhoneNumber() { return phoneNumber; }
    void setCountry(string newCountry) { country = std::move(newCountry); }
    void setStreetName(string newStreetName) { streetName = std::move(newStreetName); }
    void setZipCode(string newZipCode) { zipCode = std::move(newZipCode); }
    void setCity(string newCity) { city = std::move(newCity); }
    void setTelephoneNumber(string newPhoneNumber) { phoneNumber = std::move(newPhoneNumber); }
    friend ostream& operator << (ostream& out, const Address &address);
    friend bool operator == (Address &address1, Address &address2) { return address1.addressInfo() == address2.addressInfo(); }
}; //✅

class DateTime final {
private:
    int year;
    int day;
    int month;
    constexpr static int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    static int countLeapYears(DateTime date);
public:
    DateTime(int year, int month, int day) : year(year), day(day), month(month) {}
    [[nodiscard]] int getYear() const { return year; }
    [[nodiscard]] int getDay() const { return day; }
    [[nodiscard]] int getMonth() const { return month; }
    void setYear(int newYear) { year = newYear; }
    void setDay(int newDay) { day = newDay; }
    void setMonth(int newMonth) { month = newMonth; }
    friend int operator - (DateTime &date1, DateTime &date2);
    friend ostream& operator << (ostream& out, const DateTime &date) { return out << date.day << '.' << date.month << '.' << date.year << endl; }
}; //✅

class Client final {
private:
    string name;
    string surname;
    int id;
    vector<Reservation*> reservations;
    Invoice* invoice;
public:
    Client(string name, string surname, int id, Invoice* invoice, vector<Reservation*> reservations = {}) : name(std::move(name)), surname(std::move(surname)), id(id),
                                                                                                      reservations(std::move(reservations)), invoice(invoice) {}
    string getName() { return name; }
    string getSurname() { return surname; }
    [[nodiscard]] int getID() const { return id; }
    vector<Reservation*> getReservations() { return reservations; }
    Invoice* getInvoice() { return invoice; }
    void setName(string newName) { name = std::move(newName); }
    void setSurname(string newSurname) { surname = std::move(newSurname); }
    void setID(int newID) { id = newID; }
    void setReservations(vector<Reservation*> newReservations) { reservations = std::move(newReservations); }
    void setInvoice(Invoice* newInvoice) { invoice = newInvoice; }
    void addOrder(const string& name, int reservationID);
    void addOpinion(int rating, string comment, int reservationID);
    friend ostream& operator << (ostream& out, const Client &client);
};

class Opinion final {
private:
    int rating;
    string comment;
    int clientID;
    int reservationID;
public:
    Opinion(int rating, string comment, int clientID, int reservationID) : rating(rating), comment(std::move(comment)),
                                                                                   clientID(clientID), reservationID(reservationID) {}
    [[nodiscard]] int getRating() const { return rating; }
    string getComment() { return comment; }
    int getClientID() { return clientID; }
    int getReservationID() { return reservationID; }
    void setRating(int newRating) { rating = newRating; }
    void setComment(string newComment) { comment = std::move(newComment); }
    void setClient(int newClientID) { clientID = newClientID; }
    void setReservation(int newReservationID) { reservationID = newReservationID; }
    friend ostream& operator << (ostream& out, const Opinion &opinion);
}; //✅

class Menu final {
private:
    map<string,double> prices;
public:
    Menu(map<string,double> prices = {}) : prices(std::move(prices)) {}
    void addToMenu(const string& name, double price) { prices.insert({name,price}); }
    void removeFromMenu(const string& name) { prices.erase(name); }
    double checkPrice(const string& name);
    friend ostream& operator << (ostream& out, const Menu &menu);
}; //✅

using AdditionalServices = Menu; //✅

class Order final {
private:
    Hotel* hotel;
    pair<string,double> position;
    bool done;
public:
    Order(const string& name, Hotel* hotel, bool done = false);
    double getPrice() const { return position.second; }
    void setDone(bool newDone) { done = newDone; }
    friend ostream& operator << (ostream& out, const Order &order);
}; //✅

class Restaurant final {
private:
    Menu menu;
    stack<Order> orders;
public:
    Restaurant(Menu menu = {}, stack<Order> orders = {}) : menu(std::move(menu)), orders(std::move(orders)) {}
    Menu getMenu() { return menu; }
    Order doOrder();
    void addOrder(const Order& order) { orders.push(order); }
    friend ostream& operator << (ostream& out, const Restaurant &restaurant) { return out << restaurant.menu << endl; }
}; //✅

using Services = Restaurant; //✅

class Hotel final {
private:
    string name;
    Address hotelAddress;
    vector<Room> rooms;
    vector<Opinion> opinions;
    Restaurant restaurant;
    Services services;
public:
    Hotel(string name, Address address, Restaurant restaurant, Services services, vector<Room> rooms = {}, vector<Opinion> opinions = {}) : name(std::move(name)), hotelAddress(std::move(address)),
                                                                                                               rooms(std::move(rooms)), opinions(std::move(opinions)),
                                                                                                               restaurant(std::move(restaurant)),
                                                                                                               services(std::move(services)) {}
    Services getServices() { return services; }
    Restaurant getRestaurant() { return restaurant; }
    string getName() { return name; }
    void changeAv(int roomID) { for(auto room : rooms) if (room.getRoomID() == roomID) room.setAvailable(false);}
    Room* findEmpty() { for (auto room : rooms) if (room.getAvailable() == true) return &room; return NULL; }
    void addOpinion(const Opinion &op) { opinions.emplace_back(op); }
    vector<Room> getRooms() { return rooms; }
    void addRoom(const Room &newRoom){ rooms.push_back(newRoom); }
    int searchForRoom(int roomID);
    friend ostream& operator<<(ostream& out, const Hotel &hotel);
};

class Invoice final {
private:
    vector<Order> orders;
    double wholePrice;
public:
    explicit Invoice(vector<Order> orders = {}, double wholePrice = 0) : orders(std::move(orders)), wholePrice(wholePrice) {}
    void addOrder(const string& name, Hotel* hotel);
    friend ostream& operator<<(ostream& out, const Invoice &invoice);
};

class Reservation final {
private:
    int id;
    DateTime checkInDate;
    DateTime checkOutDate;
    Room room;
    Invoice invoice;
    Hotel hotel;
public:
    Reservation(int id, DateTime checkInDate, DateTime checkOutDate, Room room, Invoice inv, Hotel hotel) : id(id), checkInDate(checkInDate),checkOutDate(checkOutDate), room(room), invoice(inv), hotel(hotel) {}
    int getID() const { return id; }
    Hotel getHotel() { return hotel; }
    inline friend ostream& operator << (ostream& out, const Reservation &res);
}; //✅

class ReservationSystem {
private:
    vector<Hotel*> hotels;
    vector<Reservation> reservations;
public:
    ReservationSystem(vector<Hotel*> hotel = {}, vector<Reservation> res = {}) : hotels(hotel), reservations(res) {}
    void addHotel(Hotel *hotel){ hotels.emplace_back(hotel); }
    void removeHotel(string name) {
        for (auto it = hotels.begin(); it != hotels.end(); it++){
            if((*it)->getName() == name){
                hotels.erase(it);
                return;
            }
        }
    }
    Room findRoom(string name){
        for (auto hotel : hotels){
            if (hotel->getName() == name){
                Room* emptyRoom = hotel->findEmpty();
                if(emptyRoom != NULL){
                    return *emptyRoom;
                }else{
                    try{
                        throw logic_error("error!");
                    }catch (exception) {
                        cout << "Nie znaleziono wolnego pokoju w " << name << endl;
                    }
                }
            }
        }
    }

    void reservateRoom(int roomID, string name, Client client, DateTime checkin, DateTime checkout) {
        for (auto hotel : hotels){
            if(hotel->getName() == name){
                hotel->changeAv(roomID);
                vector<Room> vec = hotel->getRooms();
                Room room = vec[hotel->searchForRoom(roomID)];
                Reservation newReservation = Reservation(reservations.size()+1,checkin,checkout,room,Invoice(),*hotel);
                reservations.emplace_back(newReservation);
                return;
            }
        }
    }
};

class Administrator final {
private:
    string login = "John Doe";
    string password = "1234";
public:
    Administrator() = default;
    string getLogin() { return login; }
    string getPassword() { return password; }
    void addHotel(Hotel *hotel, ReservationSystem rs) { rs.addHotel(hotel); }
    void removeHotel(string name, ReservationSystem rs){ rs.removeHotel(name); }
};

class Application final {
private:
    Administrator admin;
    ReservationSystem rs;
    string login;
    string password;
public:
    Application(string login, string password, ReservationSystem rs, Administrator admin) : login(std::move(login)), password(std::move(password)), rs(rs)
                                                                                            , admin(admin) {};
    int commands(){
        if( login != admin.getLogin() || password != admin.getPassword()){
            cout << "Wrong login details!" << endl;
        }
        //mozna pisac komendy...
        return 0;
    }
};

#endif //UNTITLED1_HEADER_HPP