#include <iostream>
#include "Flight.h"
using namespace std;

Flight::Flight()
{
  flightNumber = 0;
  rowNumber = 0;
  seatNumber = 0;
}

Flight::Flight(int flightNumber, int rowNumber, int seatNumber)
{
  this->flightNumber = flightNumber;
  this->rowNumber = rowNumber;
  this->seatNumber = seatNumber;

  //Creating an array of pointers
  seats = new int*[rowNumber];

  //Creating for each pointer an array of seat numbers
  for(int index = 0; index < rowNumber; index++ )
  seats[index] = new int[seatNumber];

  // Make all the flight 0
  for (int index = 0; index < rowNumber; index++)
  for (int j = 0; j < seatNumber; j++)
  seats[index][j] = 0;
}

Flight::~Flight()
{
  //If there is no row in the flight there is no flight
  if(rowNumber == 0)
  return;
  //If there is a flight delete all of the seats
  for (int index = 0; index < rowNumber; index++)
  delete[] seats[index];

  delete[] seats;
}

bool Flight::hasReservation(const int ticket)
{
  //Check if there is a reservation with the given reservation code
  for (int index = 0; index < rowNumber; index++)
  for (int j = 0; j < seatNumber; j++)
  if(seats[index][j] == ticket)
  return true;
  return false;
}

void Flight::showReservation(const int ticket)
{
  //Print the message showing the seats of the given reservation code
  cout<< "Reservation under code " << ticket << " in Flight " << getFlightNumber() << ": ";

  //Check every seats and if it exits prints it.
  for (int index = 0; index < rowNumber; index++)
  {
    for (int j = 0; j < seatNumber; j++)
    {
      if(seats[index][j] == ticket)
      {
        cout << (index+1) << (char) ('A' + j) << " ";
      }
    }
  }

  cout << endl << endl;
}

void Flight::cancelReservation( const int resCode )
{

  cout << "Reservation for the seats ";
  for (int index = 0; index < rowNumber; index++)
  {
    for (int j = 0; j < seatNumber; j++)
    {
      if (seats[index][j] == resCode)
      {
        cout << (index+1) << (char) ('A' + j)<<" ";
        seats[index][j] = 0;
      }
    }
  }

  cout<<" is canceled in Flight " << getFlightNumber() <<"\n\n" ;

}

void Flight::showFlight()
{
  //Prints the Flight Number and the available seats on the Flight
  cout<<"Flight " << getFlightNumber() << " has " << showAvailableSeat() << " available seats\n" ;

  //Prints the pattern of the flight with the seats.
  cout << "  ";
  for(int index = 0; index < seatNumber; index++)
  {
    cout<< (char)('A' + index) << " ";
  }
  cout << endl;
  for (int index = 0; index < rowNumber; index++)
  {
    cout<<index+1<<" ";
    for (int j = 0; j < seatNumber; j++)
    {
      if(seats[index][j] == 0)
      cout<<'o'<<" ";
      else
      cout<<'x'<<" ";
    }
    cout << "\n";
  }
  //Print the Reservation Code that is going to have nextUser
  cout<<"Your reservation code is: " << getReservationCode();
  //Make Space for proper Reading
  cout<<"\n\n";
}

//Get the Number of the Flight
int Flight::getFlightNumber()
{
  return flightNumber;
}
//Get the Number of the Rows that the Flight have
int Flight::getRowsNumber()
{
  return rowNumber;
}
//Get the Number of the Seats for Row that the Flight have
int Flight::getSeatsForRowNumber()
{
  return seatNumber;
}
//Set the Number of the Rows according to the user preference
void Flight::setRowsNumber(int rowNumber)
{
  this->rowNumber = rowNumber;
}
//Set the Number of the Seats for Row according to the user preference
void Flight::setSeatsForRowNumber(int seatNumber)
{
  this->seatNumber = seatNumber;
}

void Flight::operator=(Flight &theFlight) {

  flightNumber = (theFlight).getFlightNumber();
  if(rowNumber != 0)
  {

    for (int i = 0; i < rowNumber; i++) {
      delete[] seats[i];
    }
    delete[] seats;
  }

  rowNumber = ((theFlight).getRowsNumber());
  seatNumber = ((theFlight).getSeatsForRowNumber());

  seats = new int*[rowNumber];

  for(int i = 0; i < rowNumber; i++ ) {
    seats[i] = new int[seatNumber];
  }

  for (int i = 0; i < rowNumber; i++) {
    for (int j = 0; j < seatNumber; j++) {
      seats[i][j] = (theFlight).getFlightSeat(i,j);
    }
  }

}

//Return the required seat on the plane
int Flight::getFlightSeat(int rowNumber, int seatNumber)
{
  return seats[rowNumber][seatNumber];
}
//Return the number of the available seats on the Plane
int Flight::showAvailableSeat()
{
  int available = 0;
  for (int i = 0; i < rowNumber; i++)
  {
    for(int j = 0; j < seatNumber; j++ )
    {
      if(seats[i][j] == 0)
      available = available + 1;

    }
  }
  return available;
}

//Return the reservation code
int Flight::getReservationCode()
{
  return reservationCode;
}
//Reserve flight seats and make the seat unavailable
int Flight::reserveFlightSeats( const int *rows, const char *seatArray, const int length)
{
  int numberOfSeatsNotAvailable = 0;
  for (int i = 0; i < length; i++)
  {
    if(seats[ rows[i] - 1 ][ seatArray[i]- 'A' ] != 0)
    {
      numberOfSeatsNotAvailable = numberOfSeatsNotAvailable + 1;
      cout << rows[i] << seatArray[i] <<" ";

    }
  }

  if(numberOfSeatsNotAvailable == 1 )
  cout<<"is not available.\n\n";
  else if(numberOfSeatsNotAvailable > 1)
  cout<<"are not available.\n\n";

  if(numberOfSeatsNotAvailable >0 )
  return -1;

  for (int i = 0; i < length; i++)
  seats[ rows[i] - 1 ][ seatArray[i]-'A' ] = reservationCode;


  return reservationCode++;
}
