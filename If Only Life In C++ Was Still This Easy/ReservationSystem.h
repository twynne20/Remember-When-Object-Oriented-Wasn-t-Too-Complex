#include "Flight.h"
class flightReservationSystem {

public:
  //Constructor
  flightReservationSystem();
  //Destructor
  ~flightReservationSystem();
  //Add a Flight in the System
  void addFlight( const int flightNumber, const int rowNumber, const int seatNumber );
  //Cancel a Flight in the System
  void cancelFlight( const int flightNumber );
  //Show all Flight with their Flight Number and the available seats
  void showAllFlights();
  //Show a particular flight with his available seats pattern of the flight seats and the reservation code
  void showFlight( const int flightNumber );
  //Reserve a seat in the Plane and then it is not more available
  int makeReservation( const int flightNumber, const int numPassengers, const int *seatRow, const char *seatCol );
  //Cancel a reservation and make the seats available
  void cancelReservation( const int resCode );
  //Show the seats taken according to the reservation number
  void showReservation( const int resCode );

private:
  Flight *flights;
  int numberOfFlights;

};
