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
    char *t = ctime(&now);
    t[strlen(t) - 1] = '\0';

    fprintf(fp, "[%s] %s\n", t, msg);
    fclose(fp);
}

