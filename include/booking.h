#ifndef BOOKING_H
#define BOOKING_H

#include "common.h"

typedef union {
    float regular_price;
    float discounted_price;
} Fare;

typedef struct {
    int booking_id;
    int train_id;
    char passenger_name[50];
    int age;
    int tickets;
    TicketStatus status;
} Booking;

void book_ticket();
void view_bookings();
const char* status_to_string(TicketStatus status);

#endif

