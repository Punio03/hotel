#include "header.hpp"


// Room
ostream& operator << (ostream& out, const Room &room) {
    return out << "ID: " << room.roomID << endl
               << "Capacity: " << room.capacity << endl
               << "Price for night: " << room.price << "$" << endl
               << "Available: " << ((room.available) ? "true" : "false") << endl;
}


// Address
ostream& operator << (ostream& out, const Address &address) {
    return out << "Country: " << address.country << endl
               << "Street name: " << address.streetName << endl
               << "Zip code: " << address.zipCode << endl
               << "City: " << address.city << endl
               << "Telephone number: " << address.phoneNumber << endl;
}


// DateTime
int DateTime::countLeapYears(DateTime date) {
    int years = date.year;
    if (date.month <= 2) years--;
    return years / 4 - years / 100 + years / 400;
}

int operator - (DateTime &date1, DateTime &date2) {
    long int n1 = date1.year * 365 + date1.day;
    for (int i = 0; i < date1.month - 1; i++) n1 += DateTime::monthDays[i];
    n1 += DateTime::countLeapYears(date1);
    long int n2 = date2.year * 365 + date2.day;
    for (int i = 0; i < date2.month - 1; i++) n2 += DateTime::monthDays[i];
    n2 += DateTime::countLeapYears(date2);
    return (int)(n2 - n1);
}


// Client
ostream& operator << (ostream& out, const Client &client) {
    out << "Name: " << client.name << endl
        << "Surname: " << client.surname << endl
        << "----- Reservations -----" << endl;
    for (const auto& reservation : client.reservations) out << *reservation << endl;
    return out << *client.invoice;
}

Order* Client::addOrder(const string& itemName, double price, int reservationID) {
    for (auto reservation : reservations) {
        if (reservation->getID() == reservationID) {
            Hotel* h{reservation->getHotel()};
            auto* order = new Order(itemName, h, false, price);
            invoice->addOrder(order);
            return order;
        }
    }
    return nullptr;
}

void Client::addOpinion(int rating, const string& comment, int reservationID) {
    for (auto reservation : reservations) {
        if (reservation->getID() == reservationID) {
            Hotel* h{reservation->getHotel()};
            auto* op = new Opinion(rating, comment, id, reservationID);
            h->addOpinion(op);
            return;
        }
    }
}


// Opinion
ostream& operator << (ostream& out, const Opinion &opinion) {
    return out << "Rating: " << opinion.rating << endl
               << "Comment: " << opinion.comment << endl
               << "Client ID: " << opinion.clientID << endl
               << "Reservation ID: " << opinion.reservationID << endl;
}


// Menu
double Menu::checkPrice(const std::string &name) {
    try {
        double price = prices.at(name);
        return price;
    } catch (exception &e) {
        return 0;
    }
}

ostream& operator << (ostream& out, const Menu &menu) {
    out << "----- Name ----- | ----- Price -----" << endl;
    for(const auto& n : menu.prices) {
        out << setw(16) << n.first;
        out << " | " << setw(17) << (to_string(n.second));
    }
    return out;
}


// Order
Order::Order(const string& name, Hotel *hotel, bool done, double price) : done(done), hotel(hotel), position({name,price}) {
    try {
        if (price == 0.0) {
            auto *m = hotel->getRestaurant();
            auto *as = hotel->getServices();
            double newPrice = m->checkPrice(name);
            if (newPrice == 0) newPrice = as->checkPrice(name);
            else {
                hotel->getRestaurant()->addOrder({name, hotel, false, newPrice});
                position = {name, newPrice};
                return;
            }
            if (newPrice == 0) position = {"Wrong position!", 0};
            else {
                hotel->getServices()->addOrder({name, hotel, false, newPrice});
                position = {name, newPrice};
            }
        }
    } catch (exception &e){
        cerr << "Order" << e.what() << endl;
    }
}

ostream& operator << (ostream& out, const Order &order) {
    return out << order.position.first << " "
               << order.position.second << "$" << endl;
}


// Restaurant
Order Restaurant::doOrder() {
    Order o = orders.top();
    orders.pop();
    o.setDone(true);
    return o;
}


// Hotel
int Hotel::searchForRoom(int roomID) {
    for(int i = 0; i < rooms.size(); i++) if (rooms[i]->getRoomID() == roomID) return i;
    return -1;
}

ostream& operator << (ostream& out, const Hotel &hotel) {
    for(auto room : hotel.rooms) out << *room << endl;
    for(auto opinion : hotel.opinions) out << *opinion << endl;
    return out;
}


// Invoice
void Invoice::addOrder(Order* order) {
    wholePrice += order->getPrice();
    orders.emplace_back(order);
}

ostream& operator << (ostream& out, const Invoice &invoice) {
    out << "----- Invoice -----" << endl;
    out << "Whole price: " << invoice.wholePrice << "$" << endl;
    for(auto order : invoice.orders) out << *order;
    return out;
}


// Reservation
ostream& operator << (ostream &out, const Reservation &res) {
    return out << "ID: " << res.id << endl
    << "Data zameldownia: " << res.checkInDate << endl
    << "Data wymeldowania: " << res.checkOutDate << endl
    << "--- Pokoje ---" << endl << *res.room << endl;
}


// Reservation System
void ReservationSystem::reservateRoom(int roomID, const string& name, Client *client, DateTime checkin, DateTime checkout) {
    for (auto hotel : hotels){
        if(hotel->getName() == name && hotel->getRooms()[hotel->searchForRoom(roomID)]->getAvailable()){
            hotel->changeAv(roomID);
            vector<Room*> vec = hotel->getRooms();
            Room* room = vec[hotel->searchForRoom(roomID)];
            auto* newReservation = new Reservation(reservations.size(),checkin,checkout,room,new Invoice{},hotel);
            reservations.emplace_back(newReservation);
            client->addReservation(newReservation);
            client->addOrder(name, (checkin-checkout)*room->getPrice(), newReservation->getID());
            return;
        }
    }
    cerr << "reservateRoom : nie udało się złożyć rezerwacji na pokój nr: " << roomID << endl;
}

Room ReservationSystem::findRoom(const string &name) {
    for (auto hotel : hotels){
        if (hotel->getName() == name){
            Room* emptyRoom = hotel->findEmpty();
            if(emptyRoom != nullptr){
                return *emptyRoom;
            }else{
                try{
                    throw logic_error("error!");
                }catch (exception &e) {
                    cout << "Nie znaleziono wolnego pokoju w " << name << endl;
                }
            }
        }
    }
    return {0, 0, 0};
}

ostream& operator << (ostream& out, ReservationSystem& rs){
    for(auto hotel : rs.hotels) { out << *hotel; };
    for(auto reservation : rs.reservations) { out << *reservation; }
    return out;
}

void ReservationSystem::removeHotel(const string &name) {
    for (auto it = hotels.begin(); it != hotels.end(); it++){
        if((*it)->getName() == name){
            hotels.erase(it);
            return;
        }
    }
}


// Application

int Application::commands(){
    vector<string> loginDetails{login,password};
    if( loginDetails != *admin){
        cout << "Wrong login details!" << endl;
        return 1;
    }
    try {
        // Klient Jakub Malczak
        auto *klient1 = new Client{"Jakub", "Malczak", 0, new Invoice{}};
        // Klient Piotr Stachowicz
        auto *klient2 = new Client{"Piotr", "Stachowicz", 1, new Invoice{}};
        // Hotel
        Menu *menu1 = new Menu();
        menu1->addToMenu("Kotlet", 15.00);
        menu1->addToMenu("Frytki", 3.00);
        menu1->addToMenu("Cola", 5.00);
        menu1->addToMenu("Pizza", 20.00);
        stack<Order> orders1 = {};
        stack<Order> orders2 = {};
        auto *restaurant1 = new Restaurant(menu1, orders1);
        auto *menu2 = new Menu();
        auto *services1 = new Services{menu2, orders2};
        services1->getMenu()->addToMenu("Sauna", 14.00);
        services1->getMenu()->addToMenu("Basen", 20.00);
        services1->getMenu()->addToMenu("Buffet", 14.00);
        auto *hotel1 = new Hotel{"Neptune", Address{"Poland", "Romualda", "47-201", "Gdansk", "424242"}, restaurant1,
                                 services1};
        // Pokoje
        for (int i = 0; i < 5; i++) {
            Room *room = new Room{i, 1, 100};
            hotel1->addRoom(room);
        }
        rs->addHotel(hotel1);
        // Daty rezerwacji Kuby
        DateTime checkin1{2023, 12, 12};
        DateTime checkout1{2023, 12, 14};
        // Daty rezerwacji Piotrka
        DateTime checkin2{2023, 11, 12};
        DateTime checkout2{2023, 12, 14};
        // Rezerwacja Kuby
        rs->reservateRoom(0, "Neptune", klient1, checkin1, checkout1);
        // Rezerwacja Piotrka
        rs->reservateRoom(1, "Neptune", klient2, checkin2, checkout2);
        cout << rs->findRoom("Neptune");
        // Zamówienia Kuby
        klient1->addOrder("Kotlet", 0, 0);
        // Zamówienia Piotrka
        klient2->addOrder("Pizza", 0, 1);
        klient2->addOrder("Sauna", 0, 1);
        // Opinie
        klient1->addOpinion(10,"Super hotel",0);
        klient2->addOpinion(9, "Fajny hotel, ale pizza slaba...", 1);
        // Wyniki
        cout << *klient1 << endl;
        cout << *klient2 << endl;
        cout << *rs << endl;
    } catch (exception &e){
        cerr << "command" << e.what() << endl;
    }
    return 0;
}
