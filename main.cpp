#include "header.hpp"

int main() {
    Client klient1{"Jakub", "Malczak", 0, new Invoice{}};
    Administrator admin = {};
    Room room1{1,1,100};
    Room room2{2,2,200};
    Restaurant restaurant1{};
    Services services1{};
    Hotel *hotel1 = new Hotel{"Neptune",Address{"Poland","Wojna","47-201","Gdansk","424242"},restaurant1,services1};
    hotel1->addRoom(room1);
    hotel1->addRoom(room2);
    cout << *hotel1;
    cout << klient1 << endl;
    ReservationSystem rs{};
    rs.addHotel(hotel1);
    DateTime checkin{2023,12,12};
    rs.reservateRoom(1,"Neptune",klient1,checkin,checkin);
    cout << klient1 << endl;
    cout << *hotel1;
}
