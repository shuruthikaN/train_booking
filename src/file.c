#include "train.h"
#include "booking.h"
#include "file.h"

void save_train(Train *t) {
    FILE *fp = fopen("data/trains.dat", "ab");
    fwrite(t, sizeof(Train), 1, fp);
    fclose(fp);
}

void save_booking(Booking *b) {
    FILE *fp = fopen("data/bookings.dat", "ab");
    fwrite(b, sizeof(Booking), 1, fp);
    fclose(fp);
}

void write_log(const char *msg) {
    FILE *fp = fopen("data/booking.log", "a");
    if (!fp) return;

    time_t now = time(NULL);
    fprintf(fp, "%s - %s", ctime(&now), msg);
    fclose(fp);
}

