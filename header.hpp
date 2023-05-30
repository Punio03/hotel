#ifndef UNTITLED1_HEADER_HPP
#define UNTITLED1_HEADER_HPP
#include <iostream>
#include <vector>
using namespace std;
class Room final {
private:
    int RoomID;
    int Capacity;
    int Price;
    bool Available;
public:
    inline Room(int newRoomID, int newCapacity, int newPrice, bool Available=true) noexcept : RoomID(newRoomID), Capacity(newCapacity), Price(newPrice), Available(Available) { }
    inline Room(Room const &oldRoom) = default;
    inline Room(Room &&oldRoom) = default;
    inline ~Room() = default;
    inline int getRoomID() const noexcept { return this->RoomID; }
    inline int getCapacity() const noexcept { return this->Capacity; }
    inline int getPrice() const noexcept { return this->Price; }
    inline bool getAvailable() const noexcept { return this->Available; }
    inline void setRoomID(int newRoomID)  noexcept { this->RoomID = newRoomID; }
    inline void setCapacity(int newCapacity)  noexcept { this->Capacity = newCapacity; }
    inline void setPrice(int newPrice)  noexcept { this->Price = newPrice; }
    inline friend ostream& operator<<(ostream& out, const Room &room) noexcept {
        out << "ID:" << room.RoomID << endl << "Capacity:" << room.Capacity << endl<< "Price for night:" << room.Price << "$" << endl << "Availability:" << room.Available;
        return out;
    }
}; // gotowe
class Address final{
public:
    string Country;
    string StreetName;
    string ZipCode;
    string City;
    string TelephoneNumber;
    inline Address(string newCountry, string newStreetName, string newZipCode, string newCity, string newTelephoneNumber) noexcept : Country(newCountry), StreetName(newStreetName), ZipCode(newZipCode), City(newCity), TelephoneNumber(newTelephoneNumber) { }
    inline Address(Address const  &adress) = default;
    inline Address(Address &&adress) = default;
    inline ~Address() = default;
    inline vector<string> AdressInfo() { return { this->Country,this->StreetName, this->ZipCode, this->City, this->TelephoneNumber }; }
    inline friend ostream& operator<<(ostream& out, const Address &address) noexcept {
        out << "Country:" << address.Country << endl << "StreetName:" << address.StreetName << endl << "ZipCode:" << address.ZipCode << endl << "City:" << address.City << endl << "Telephone Number:" << address.TelephoneNumber << endl;
        return out;
    }
    inline friend bool operator==(Address &address1, Address &address2) { return address1.AdressInfo() == address2.AdressInfo(); }
}; // gotowe
class Opinion {

};
class Restauration {

};
class Hotel {
private:
    string Name;
    Address HotelAddress;
    vector<Room> Rooms;
    vector<Opinion> Opinions;
    Restauration HotelRestauration;
public:
    inline Hotel(string newName, Address newAddress, vector<Room>newRooms, vector<Opinion>newOpinions, Restauration newRestauration) noexcept : Name(newName), HotelAddress(newAddress), Rooms(newRooms), Opinions(newOpinions), HotelRestauration(newRestauration) { }
    inline void AddRoom(const Room &newRoom){ this->Rooms.push_back(newRoom); }
    inline int SearchForRoom(int RoomID) { for(int i = 0;i<Rooms.size();i++){ if(Rooms[i].getRoomID()==RoomID){ return i; } } return -1; }
    inline friend ostream& operator<<(ostream& out, const Hotel &hotel) { for(auto room : hotel.Rooms){ out << room << endl; } return out; }
};
class Client {};
class Reservation {};
class ReservationSystem {};
class Application {};
class Administrator {};
class Invoice {};
class Order {};
class Menu {};
class Date {};
class Services {};
class AdditionalServices {};
#endif //UNTITLED1_HEADER_HPP