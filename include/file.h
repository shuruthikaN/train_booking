#ifndef FILE_H
#define FILE_H

#include "train.h"
#include "booking.h"

void save_train(Train *t);
void save_booking(Booking *b);
void write_log(const char *msg);

#endif

