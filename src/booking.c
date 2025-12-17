#include "booking.h"
#include "train.h"
#include "file.h"

int booking_count = 0;

void* log_thread(void *arg) {
    char *msg = (char*)arg;
    write_log(msg);
    free(msg);
    pthread_exit(NULL);
}

void book_ticket() {
    Booking b;
    Fare fare;

    printf("Train ID: ");
    scanf("%d", &b.train_id);
    printf("Passenger Name: ");
    scanf("%s", b.passenger_name);

    b.booking_id = ++booking_count;
    b.status = BOOKED;

    fare.regular_price = 250.0;
    printf("Ticket Price: %.2f\n", fare.regular_price);

    save_booking(&b);
    reduce_seat_count(b.train_id);

    pthread_t tid;
    char *logmsg = malloc(100);
    sprintf(logmsg, "Booking ID %d for %s\n",
            b.booking_id, b.passenger_name);

    pthread_create(&tid, NULL, log_thread, logmsg);
    pthread_detach(tid);

    printf("Ticket booked successfully!\n");
}

void view_bookings() {
    Booking b;
    FILE *fp = fopen("data/bookings.dat", "rb");

    if (!fp) {
        printf("No bookings found.\n");
        return;
    }

    while (fread(&b, sizeof(Booking), 1, fp)) {
        printf("BookingID:%d TrainID:%d Name:%s Status:%d\n",
               b.booking_id, b.train_id,
               b.passenger_name, b.status);
    }
    fclose(fp);
}

