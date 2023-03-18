#include <iostream>
#include <vector>
using namespace std;

enum RideStatus {IDLE, CREATED, WITHDRAWN, COMPLETED};

class Ride
{
public:
    static const int AMT_PER_KM = 20;
    Ride();
    int calculateFare(bool);
    void setDest(int dest);
    int getId() const;
    void setId(int id);
    void setOrigin(int origin);
    RideStatus getRideStatus() const;
    void setRideStatus(RideStatus rideStatus);
    void setSeats(int seats);

private:
    int id;
    int origin, dest;
    int seats;
    RideStatus rideStatus;
};

class Person
{
public:
    string name;
};

class Driver: private Person
{
public:
    Driver(string);
};

class Rider: private Person
{
private:
    int id;
    vector<Ride> allRides;
    
public:
    Rider(int, string);
    void createRide(int, int, int, int);
    void updateRide(int, int, int, int);
    void withdrawRide(int);
    int closeRide(int);
    int getId() const;
};

class System
{
private:
    int drivers; 
    vector<Rider> riders;
public:
    System(int, vector<Rider>&);
    void createRide(int, int, int, int, int);
    void updateRide(int, int, int, int, int);
    void withdrawRide(int, int);
    int closeRide(int);
};

Ride::Ride()
{
    id = origin = dest = seats = 0;
    rideStatus = RideStatus::IDLE;
}

Driver::Driver(string name)
{
    this->name = name;
}

int Ride::calculateFare(bool isPriorityRider)
{
    int dist = dest - origin;
    if(seats < 2)
    {
        return dist * AMT_PER_KM * (isPriorityRider?0.75:1);
    }

    return dist * seats * AMT_PER_KM * (isPriorityRider?0.5:0.75);
}

void Ride::setDest(int dest) {
    this->dest = dest;
}

int Ride::getId() const {
    return id;
}

void Ride::setId(int id) {
    this->id = id;
}

void Ride::setOrigin(int origin) {
    this->origin = origin;
}

RideStatus Ride::getRideStatus() const {
    return rideStatus;
}

void Ride::setRideStatus(RideStatus rideStatus) {
    this->rideStatus = rideStatus;
}

void Ride::setSeats(int seats) {
    this->seats = seats;
}

Rider::Rider(int id, string name)
{
    this->id = id;
    this->name = name;
}

void Rider::createRide(int id, int origin, int dest, int seats)
{
    if (origin >= dest)
    {
        cout << "Wrong values of Origin and Destination provided. Can't create ride\n";
        return;
    }
    Ride currentRide;
    currentRide.setId(id);
    currentRide.setOrigin(origin);
    currentRide.setDest(dest);
    currentRide.setSeats(seats);
    currentRide.setRideStatus(RideStatus::CREATED);
    allRides.push_back(currentRide);
}
void Rider::updateRide(int id, int origin, int dest, int seats)
{
    auto it = allRides.rbegin();
    for(; it!= allRides.rend();it++)
    {
        if(it->getId()==id)
        {
            break;
        }
    }
    if(it->getRideStatus()!=RideStatus::CREATED)
    {
        cout << "Ride wasn't in progress, Can't update Ride\n";
        return;
    }
    it->setOrigin(origin);
    it->setDest(dest);
    it->setSeats(seats);
}

void Rider::withdrawRide(int id)
{
    auto it = allRides.rbegin();
    for(; it!= allRides.rend();it++)
    {
        if(it->getId()==id)
        {
            break;
        }
    }
    if(it->getRideStatus()!=RideStatus::CREATED)
    {
        cout << "Ride wasn't in progress, Can't withdraw Ride\n";
        return;
    }
    it->setRideStatus(RideStatus::WITHDRAWN);
    allRides.erase((it+1).base());
    
}

int Rider::getId() const {
    return id;
}

int Rider::closeRide(int id)
{
    auto it = allRides.rbegin();
    for(; it!= allRides.rend();it++)
    {
        if(it->getId()==id)
        {
            break;
        }
    }
    if(it->getRideStatus()!=RideStatus::CREATED)
    {
        cout << "Ride wasn't in progress, Can't close Ride\n";
        return 0;
    }
    it->setRideStatus(RideStatus::COMPLETED);
    return it->calculateFare(allRides.size()>=10);
}



int main()
{

Rider rider(1,"Anmit");
Driver driver("Batman");
rider.createRide(1,50,60,1);
rider.createRide(2,40,60,2);
cout << rider.closeRide(1) << endl;  
cout << rider.closeRide(2) << endl; 
}





















