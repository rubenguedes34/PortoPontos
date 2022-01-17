# PortoPontos
@2022
Project made for @UniversidadeFernandoPessoa

Brief explanation:

  There must be a linked list for all customers containing their identification,
contact information and billing; Functions for manipulating the list of clients of
the company PortoPontos:
i. Functions for: inserting a client at the head; 
insert a customer to thetail;
neatly insert (by VAT or name) a customer; 
remove a customer;
search for a customer (by VAT or name); 

  Each customer must also have a dynamic array to record all trips already
made and/or to be made; Functions for manipulating each customer's travel
array:
i. Functions to: create a dynamic array with a given dimension;
resize the dynamic array;
insert, edit and remove trips and/or trip data;

  For each trip (each customer) there should be a dynamic array of all the
cities which customers want to visit during the trip; Functions for manipulating
the array of cities for each trip:
i. Functions to: create a dynamic array with a given dimension;
resize the dynamic array;
insert, edit and remove cities and/or city data tovisit on the trip;
search cities by name;

  Each city can have relevant information associated with it (e.g. name,
description, list of points of interest (PoI)); Functions for manipulating the
information of each city:
i. Functions to search and edit information present in the city
description;
ii. Functions for: creating a city's PoI list;
insert, remove and search for a city's PoI;

Functions to query travel history for a given customer and allow searching
within each trip for specific parameters: e.g. trip which took place in place/city
X, trip where you performed activity/visited PoI Z;

Implement reading and writing functions for text and binary files of the various
entities: customers and their trips, cities and their PoI;

Implement functions to generate reports, in text files, about customers and
their trips;
