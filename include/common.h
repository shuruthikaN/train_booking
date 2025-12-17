#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

typedef enum {
    AVAILABLE,
    BOOKED,
    CANCELLED
} TicketStatus;

extern int booking_count;

#endif

