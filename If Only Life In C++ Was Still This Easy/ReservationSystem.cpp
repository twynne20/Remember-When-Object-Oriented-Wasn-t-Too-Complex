#include <iostream>
#include "flightReservationSystem.h"
using namespace std;

flightReservationSystem::flightReservationSystem()
{
  //Initialize the Flights we have in the System to 0
  numberOfFlights = 0;
}

flightReservationSystem::~flightReservationSystem()
{
  //Delete all the flights in the system
  delete[] flights;
}
//Initialize the first reservation code to 1.
int Flight::reservationCode = 1;

void flightReservationSystem::showAllFlights()
{
  //If the number of flights is 0 prints the message
  if ( numberOfFlights == 0)
  {
    cout << "No flights exist\n" << endl;
    return;
  }
  //If there are flights prints the flights with their general information
  cout<<"Flights currently operated:\n";
  for ( int i = 0; i < numberOfFlights; i++)
  cout<<"Flight "<<flights[i].getFlightNumber() << " (" << flights[i].showAvailableSeat()<<" available seats)\n";
  cout<<"\n";
}


void flightReservationSystem::showFlight(const int flightNumber)
{
  //Initialize a bool to false since we haven't found the flight
  bool found = false;
  //Check the whole flights to find the desired flight
  for(int i = 0; i < numberOfFlights; i++)
  {
    if(flights[i].getFlightNumber() == flightNumber)
    {
      //If the flight is found make the bool found true and call showFlight method of Flight.
      found = true;
      flights[i].showFlight();
    }

  }
  //If there is no flight prints the message
  if(found == false)
  cout<<"Flight "<< flightNumber << " does not exist\n\n";
}

void flightReservationSystem::addFlight( int flightNumber, int rowNumber, const int seatNumber)
{
  //Check the whole system to see if the flight already exists
  for (int i = 0; i < numberOfFlights; i++)
  {
    //If the flight exists prints the message to the user.
    if(flights[i].getFlightNumber() == flightNumber)
    {
      cout << "Flight " << flightNumber << " already exists.\n\n";
      return;
    }
  }
  //Create a flight with the given data
  Flight temFlight( flightNumber, rowNumber, seatNumber);
  //Create a dynamic alocated array with a size 1 bigger than the actual
  Flight* temporary = new Flight[numberOfFlights + 1];

  //Copy all the inforamtion to our new array
  for(int i = 0 ; i < numberOfFlights; i++)
  temporary[i] = flights[i];
  //Add the last Flight to our array
  temporary[numberOfFlights] = (temFlight);

  //Delete flights and make it points to temporary
  if(numberOfFlights != 0 )
  delete[] flights;

  flights = temporary;

  //Increase the number of flight by one
  numberOfFlights = numberOfFlights + 1;
  //Prints a message to the user letting it know that the Flight has been added
  cout<<"Flight " << flightNumber << " has been added\n";

}


int flightReservationSystem::makeReservation( const int flightNumber, const int numPassengers, const int *seatRow, const char *seatCol )
{
  //Declare a bool with false value since we haven't found the flight
  bool flightFound = false;
  //Check all the flightNumber in order to find the desired Flight
  for (int i = 0; i < numberOfFlights; i++)
  {
    //If the flight is found this statement will process
    if(flights[i].getFlightNumber() == flightNumber)
    {
      //Make the bool true and use the reserveFlightSeats method
      //This method determine whether you can reserve or not the seat
      flightFound = true;
      return flights[i].reserveFlightSeats(seatRow, seatCol, numPassengers);
    }
  }

  //If the flight is not found prints a message to notify the user.
  if(flightFound == false)
  cout<<"Flight "<< flightNumber << " does not exist\n\n";

  return -1;
}

void flightReservationSystem::cancelReservation(const int resCode)
{
  //If the reservation code is smaller or equall to zero there is no reservation
  if(resCode <= 0)
  {
    cout << "No reservation found with that code.\n\n";
    return;
  }

  //If the reservation exits we delete the reservation making the seats empty
  for (int i = 0; i < numberOfFlights; i++)
  {
    if(flights[i].hasReservation(resCode) )
    {
      flights[i].cancelReservation(resCode);
      return;
    }
  }
  cout<<"No reservation are found under "<< resCode << "\n\n";
}

void flightReservationSystem::cancelFlight( const int flightNumber )
{
  int index = -1;

  for(int i = 0; i < numberOfFlights ; i++)
  {
    if( flights[i].getFlightNumber() == flightNumber )
    {
      index = i;
      break;
    }
  }

  //Check if the index is still the same
  if(index == -1)
  {

    cout << "There exists no plane with flight number " << flightNumber << endl << endl;

    return;
  }

  Flight* temp = new Flight[numberOfFlights - 1];

  //Copy all of the flight from the beginning until we reach the flight we want to remove
  for(int i = 0; i < index; i++)
  temp[i] = flights[i];

  //Continue copying from the index till the number of flights
  for(int i = index; i + 1 < numberOfFlights; i++)
  temp[i] = (flights[i+1]);

  if( numberOfFlights != 0 )
  delete [] flights;

  flights = temp;
  //Decrement the number of flights by one
  cout<<"Flight "<< flightNumber<<" and all of its reservations are canceled\n\n";
  numberOfFlights--;

}

void flightReservationSystem::showReservation( const int resCode )
{

  for (int i = 0; i < numberOfFlights; i++)
  {

    if (flights[i].hasReservation(resCode))
    {
      flights[i].showReservation(resCode);
      return;
    }
  }
  cout<<"No reservation under Code " << resCode << "\n\n";

}
