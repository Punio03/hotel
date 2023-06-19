#ifndef UNTITLED1_HEADER_HPP
#define UNTITLED1_HEADER_HPP

#include <iostream>
#include <utility>
#include <vector>
#include <map>
#include <stack>
#include <iomanip>

using namespace std;

class Reservation;
class Invoice;
class Hotel;
class Administrator;
class Order;

class Room final {
private:
    int roomID;
    int capacity;
    int price;
    bool available;
public:
    Room (int roomID, int capacity, int price, bool available=true) : roomID(roomID), capacity(capacity),
                                                                     price(price), available(available) {}
    [[nodiscard]] int getRoomID() const { return roomID; }
    [[nodiscard]] int getCapacity() const { return capacity; }
    [[nodiscard]] int getPrice() const { return price; }
    [[nodiscard]] bool getAvailable() const { return available; }
    void setRoomID(int newRoomID) { roomID = newRoomID; }
    void setCapacity(int newCapacity) { capacity = newCapacity; }
    void setPrice(int newPrice) { price = newPrice; }
    void setAvailable(bool newAvailable) { available = newAvailable; }
    friend ostream& operator << (ostream& out, const Room &room);
};

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
    [[nodiscard]] string getCountry() const { return country; }
    [[nodiscard]] string getStreetName() const { return streetName; }
    [[nodiscard]] string getZipCode() const { return zipCode; }
    [[nodiscard]] string getCity() const { return city; }
    [[nodiscard]] string getPhoneNumber() const { return phoneNumber; }
    void setCountry(string newCountry) { country = std::move(newCountry); }
    void setStreetName(string newStreetName) { streetName = std::move(newStreetName); }
    void setZipCode(string newZipCode) { zipCode = std::move(newZipCode); }
    void setCity(string newCity) { city = std::move(newCity); }
    void setTelephoneNumber(string newPhoneNumber) { phoneNumber = std::move(newPhoneNumber); }
    friend ostream& operator << (ostream& out, const Address &address);
    friend bool operator == (Address &address1, Address &address2) { return address1.addressInfo() == address2.addressInfo(); }
};

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
    DateTime operator ++ ();
    friend bool operator <= (const DateTime& date1, const DateTime & date2);
    friend ostream& operator << (ostream& out, const DateTime &date) { return out << date.day << '.' << date.month << '.' << date.year << endl; }
};

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
    [[nodiscard]] string getName() const { return name; }
    [[nodiscard]] string getSurname() const { return surname; }
    [[nodiscard]] int getID() const { return id; }
    [[nodiscard]] vector<Reservation*> getReservations() const { return reservations; }
    [[nodiscard]] Invoice* getInvoice() const { return invoice; }
    void setName(string newName) { name = std::move(newName); }
    void setSurname(string newSurname) { surname = std::move(newSurname); }
    void setID(int newID) { id = newID; }
    void setReservations(vector<Reservation*> newReservations) { reservations = std::move(newReservations); }
    void setInvoice(Invoice* newInvoice) { invoice = newInvoice; }
    void addReservation(Reservation* reservation) { reservations.emplace_back(reservation); }
    Order* addOrder(const string& itemName, double price, int reservationID);
    void addOpinion(int rating, const string& comment, int reservationID);
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
    [[nodiscard]] string getComment() const { return comment; }
    [[nodiscard]] int getClientID() const { return clientID; }
    [[nodiscard]] int getReservationID() const { return reservationID; }
    void setRating(int newRating) { rating = newRating; }
    void setComment(string newComment) { comment = std::move(newComment); }
    void setClient(int newClientID) { clientID = newClientID; }
    void setReservation(int newReservationID) { reservationID = newReservationID; }
    friend ostream& operator << (ostream& out, const Opinion &opinion);
};

class Menu final {
private:
    map<string,double> prices;
public:
    explicit Menu(map<string,double> prices = {}) : prices(std::move(prices)) {}
    [[nodiscard]] map<string,double> getPrices() const { return prices; }
    void addToMenu(const string& name, double price) { prices.insert({name,price}); }
    void removeFromMenu(const string& name) { prices.erase(name); }
    double checkPrice(const string& name);
    friend ostream& operator << (ostream& out, const Menu &menu);
};

using AdditionalServices = Menu;

class Order final {
private:
    Hotel* hotel;
    pair<string,double> position;
    bool done;
public:
    Order(const string& name, Hotel* hotel, bool done = false, double price = 0);
    [[nodiscard]] double getPrice() const { return position.second; }
    [[nodiscard]] string getName() const { return position.first; }
    [[nodiscard]] Hotel* getHotel() const { return hotel; }
    [[nodiscard]] bool getDone() const { return done; }
    void setPrice(double newPrice) { position.second = newPrice; }
    void setName(string name) { position.first = std::move(name); }
    void setHotel(Hotel* newHotel) { hotel = newHotel; }
    void setDone(bool newDone) { done = newDone; }
    friend ostream& operator << (ostream& out, const Order &order);
};

class Restaurant final {
private:
    Menu* menu;
    stack<Order> orders;
public:
    explicit Restaurant(Menu* menu = {}, stack<Order> orders = {}) : menu(menu), orders(std::move(orders)) {}
    [[nodiscard]] Menu* getMenu() const { return menu; }
    [[nodiscard]] stack<Order> getOrders() const { return orders; }
    Order doOrder();
    double checkPrice(const string& name) { return menu->checkPrice(name); }
    void addOrder(const Order& order) { orders.push(order); }
    friend ostream& operator << (ostream& out, const Restaurant &restaurant) { return out << restaurant.menu; }
};

using Services = Restaurant;

class Hotel final {
private:
    string name;
    Address hotelAddress;
    vector<Room*> rooms;
    vector<Opinion*> opinions;
    Restaurant* restaurant;
    Services* services;
public:
    Hotel(string name, Address address, Restaurant* restaurant, Services* services, vector<Room*> rooms = {}, vector<Opinion*> opinions = {}) : name(std::move(name)), hotelAddress(std::move(address)),
                                                                                                               rooms(std::move(rooms)), opinions(std::move(opinions)),
                                                                                                               restaurant(restaurant),
                                                                                                               services(services) {}
    [[nodiscard]] Services* getServices() const { return services; }
    [[nodiscard]] Restaurant* getRestaurant() const { return restaurant; }
    [[nodiscard]] string getName() const { return name; }
    [[nodiscard]] Address getAddress() const { return hotelAddress; }
    [[nodiscard]] vector<Room*> getRooms() const { return rooms; }
    [[nodiscard]] vector<Opinion*> getOpinion() const { return opinions; }
    void changeAv(int roomID) { for(auto room : rooms) if (room->getRoomID() == roomID) room->setAvailable(false);}
    Room* findEmpty() { for (auto room : rooms) if (room->getAvailable()) return room; return nullptr; }
    void addOpinion(Opinion* op) { opinions.emplace_back(op); }
    vector<Room*> getRooms() { return rooms; }
    void addRoom(Room *newRoom){ rooms.push_back(newRoom); }
    int searchForRoom(int roomID);
    friend ostream& operator<<(ostream& out, const Hotel &hotel);
};

class Invoice final {
private:
    vector<Order*> orders;
    double wholePrice;
public:
    explicit Invoice(vector<Order*> orders = {}, double wholePrice = 0) : orders(std::move(orders)), wholePrice(wholePrice) {}
    void addOrder(Order* order);
    friend ostream& operator<<(ostream& out, const Invoice &invoice);
};

class Reservation final {
private:
    int id;
    DateTime checkInDate;
    DateTime checkOutDate;
    Room* room;
    Invoice* invoice;
    Hotel* hotel;
public:
    Reservation(int id, DateTime checkInDate, DateTime checkOutDate, Room* room, Invoice* inv, Hotel* hotel) : id(id), checkInDate(checkInDate),
                                                                                                                checkOutDate(checkOutDate), room(room), invoice(inv), hotel(hotel) {}
    [[nodiscard]] int getID() const { return id; }
    [[nodiscard]] Room* getRoom() const { return room; }
    [[nodiscard]] Hotel* getHotel() const { return hotel; }
    [[nodiscard]] Invoice* getInvoice() const { return invoice; }
    [[nodiscard]] DateTime getCheckOutDate() const { return checkOutDate; }
    friend ostream& operator << (ostream& out, const Reservation &res);
};

class ReservationSystem {
private:
    vector<Hotel*> hotels;
    vector<Reservation*> reservations;
public:
    explicit ReservationSystem(vector<Hotel*> hotel = {}, vector<Reservation*> res = {}) : hotels(std::move(hotel)), reservations(std::move(res)) {}
    void addHotel(Hotel *hotel){ hotels.emplace_back(hotel); }
    void removeHotel(const string& name);
    Room findRoom(const string& name);
    void reservateRoom(int roomID, const string& name, Client *client, DateTime checkin, DateTime checkout);
    friend ostream& operator << (ostream& out, ReservationSystem& rs);
    void update(DateTime cDate){
        for(auto reservation : reservations){
            if(cDate <= reservation->getCheckOutDate()){
                reservation->getRoom()->setAvailable(true);
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
    void removeHotel(const string& name, ReservationSystem rs){ rs.removeHotel(name); }
    friend bool operator == (const vector<string>& vec, Administrator& admin) { return vec.front() == admin.login && vec.back() == admin.password; }
};

class Application final {
private:
    Administrator* admin;
    ReservationSystem* rs;
    string login;
    string password;
    DateTime currentDate;
public:
    Application(string login, string password, ReservationSystem* rs, Administrator* admin, DateTime date) : login(std::move(login)), password(std::move(password)), rs(rs)
                                                                                            , admin(admin), currentDate(date) {};
    int commands();
    void update() {
        ++currentDate;
        rs->update(currentDate);
    }
};

#endif //UNTITLED1_HEADER_HPP