/**
Author: Victor Nguyen, Collin Sipple, David Ryan, Salman Djingueinabaye, Tony Ong
My NU ID: 02357235
CLASS: 155E
Section 250
Date Started: 11/01/2018
Date Finished: 11/02/2018
 *
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "airport.h"


/**
 * A factory function to create a new Airport with the given
 * attributes.  This function should make *deep* copies of each
 * of the relevant fields and return a pointer to the newly
 * created Airport structure.
 */
Airport* createAirport(const char* gpsId,
                       const char* type,
                       const char* name,
                       double latitude,
                       double longitude,
                       int elevationFeet,
                       const char* city,
                       const char* countryAbbrv){

Airport *airport1 = (Airport*) malloc(sizeof(Airport) * 1);
airport1->gpsId = (char*) malloc(sizeof(char) * (strlen(gpsId) +1));
strcpy(airport1->gpsId, gpsId);
airport1->type = (char*) malloc(sizeof(char) * (strlen(type) +1));
strcpy(airport1->type, type);
airport1->name = (char*) malloc(sizeof(char) * (strlen(name) +1));
strcpy(airport1->name, name);
airport1->latitude = latitude;
airport1->longitude = longitude;
airport1->elevationFeet = elevationFeet;
if( latitude < -90 || latitude > 90 || longitude < -180 || longitude > 180) {
return NULL; }
airport1->city = (char*) malloc(sizeof(char) * (strlen(city) +1));
strcpy(airport1->city, city);
airport1->countryAbbrv = (char*) malloc(sizeof(char) * (strlen(countryAbbrv) +1));
strcpy(airport1->countryAbbrv, countryAbbrv);
return airport1;
}

/**
 * This function initializes an existing allocated
 * Airport structure with the given attributes.
 */
void initAirport(Airport* airport,
                 const char* gpsId,
                 const char* type,
                 const char* name,
                 double latitude,
                 double longitude,
                 int elevationFeet,
                 const char* city,
const char* countryAbbrv){
airport->gpsId = (char*) malloc(sizeof(char) * (strlen(gpsId) +1));
strcpy(airport->gpsId, gpsId);
airport->type = (char*) malloc(sizeof(char) * (strlen(type) +1));
strcpy(airport->type, type);
airport->name = (char*) malloc(sizeof(char) * (strlen(name) +1));
strcpy(airport->name, name);
airport->latitude = latitude;
airport->longitude = longitude;
airport->elevationFeet = elevationFeet;
airport->city = (char*) malloc(sizeof(char) * (strlen(city) +1));
strcpy(airport->city, city);
airport->countryAbbrv = (char*) malloc(sizeof(char) * (strlen(countryAbbrv) +1));
strcpy(airport->countryAbbrv, countryAbbrv);
return;
}
//
// airport->gpsId = (char*)malloc(sizeof(char) * (strlen(gpsId) + 1));
//  strcpy(airport->gpsId, gpsId);
/**
 * Constructs a new string representation of the given
 * Airport structure.
 */
char* airportToString(const Airport* a){
  if (a == NULL) {
    char *result1 = (char *)malloc(sizeof(char) * 7);
    strcpy(result1, "(null)");
    return result1;
  }

  // compute the number of characters we'll need:
int n = strlen(a->gpsId) + strlen(a->type) + strlen(a->name) + sizeof(double) + sizeof(double) + sizeof(int) + strlen(a->city) + strlen(a->countryAbbrv);

  // create a result string
  char *str = (char *)malloc(sizeof(char) * (n+15));

  // format the student into the temporary string
  sprintf(str, "%s, %s, %s, %f, %f, %d, %s, %s", a->gpsId,
a->type, a->name, a->latitude,
a->longitude, a->elevationFeet, a->city, a->countryAbbrv);

  // return the result
  return str;
}

/**
 * Computes the air distance, in kilometers, between
 * the two Airports using their latitude/longitude
 */
double getAirDistance(const Airport* origin, const Airport* destination){
int R = 6371;
double lat1Rad = ((origin->latitude) / 180) * M_PI;
double long1Rad = ((origin->longitude) / 180) * M_PI;
double lat2Rad = ((destination->latitude) / 180) * M_PI;
double long2Rad = ((destination->longitude) / 180) * M_PI;
double difference = (long2Rad - long1Rad);
double answer = (acos(((sin(lat1Rad)) * sin(lat2Rad)) + (cos(lat1Rad) * cos(lat2Rad) * cos(difference))) * R);
return answer;
}
/**
 * Computes the estimated travel time (in hours) for a flight
 * that involves the given stops using the average flight speed
 * (kilometers per hour) and average layover time (in hours)
 */
double getEstimatedTravelTime(const Airport* stops,
int size,
double aveKmsPerHour,
double aveLayoverTimeHrs){
int x=0;
int y=1;
int R = 6371;
double distance;
double totaldistance = 0;
while (y < size) {
double origLatitude = stops[x].latitude;
double destLatitude = stops[y].latitude;
double origLongitude = stops[x].longitude;
double destLongitude = stops[y].longitude;
double rLatitudeA = (origLatitude * (M_PI/180.0));
double rLatitudeB = (destLatitude * (M_PI/180.0));
double rLongitudeA = (origLongitude * (M_PI/180.0));
double rLongitudeB = (destLongitude * (M_PI/180.0));
double rLongitudeDiffernce = rLongitudeB - rLongitudeA;

distance = (acos((sin(rLatitudeA) * sin(rLatitudeB)) + (cos(rLatitudeA) * cos(rLatitudeB) * cos(rLongitudeDiffernce))) * R);

totaldistance += distance;
x++;
y++;
}

return ((totaldistance / aveKmsPerHour) + aveLayoverTimeHrs);
}
