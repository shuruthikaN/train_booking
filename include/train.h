#ifndef TRAIN_H
#define TRAIN_H

#include "common.h"

typedef struct {
    int train_id;
    char name[50];
    char timing[20];
    int total_seats;
    int available_seats;
} Train;

void add_train();
void view_trains();
void reduce_seat_count(int train_id);

#endif

