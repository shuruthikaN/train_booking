#include "booking.h"
#include "train.h"
#include "file.h"

int booking_count = 0;

const char* status_to_string(TicketStatus status) {
    switch (status) {
        case AVAILABLE: return "AVAILABLE";
        case BOOKED: return "BOOKED";
        case CANCELLED: return "CANCELLED";
        default: return "UNKNOWN";
    }
}

void* log_thread(void *arg) {
    write_log((char*)arg);
    free(arg);
    pthread_exit(NULL);
}

void book_ticket() {
    Booking b;
    Fare fare;

    FILE *fp = fopen("data/bookings.dat", "rb");
    if (fp) {
        fseek(fp, 0, SEEK_END);
        booking_count = ftell(fp) / sizeof(Booking);
        fclose(fp);
    }

    b.booking_id = booking_count + 1;

    printf("Train ID: ");
    scanf("%d", &b.train_id);

    printf("Passenger Name: ");
    scanf(" %49[^\n]", b.passenger_name);

    printf("Age: ");
    scanf("%d", &b.age);

    printf("Number of Tickets: ");
    scanf("%d", &b.tickets);

    if (!reduce_seats(b.train_id, b.tickets)) {
        printf("Not enough seats available!\n");
        return;
    }

    fare.regular_price = 250.0 * b.tickets;
    printf("Total Fare: %.2f\n", fare.regular_price);

    b.status = BOOKED;
    save_booking(&b);

    pthread_t tid;
    char *logmsg = malloc(150);
    sprintf(logmsg, "BookingID %d | Train %d | Passenger %s | Tickets %d",
            b.booking_id, b.train_id, b.passenger_name, b.tickets);

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

    printf("\n%-5s %-6s %-15s %-4s %-7s %-10s\n",
           "BID", "TID", "NAME", "AGE", "TICKETS", "STATUS");
    printf("-----------------------------------------------------\n");

    while (fread(&b, sizeof(Booking), 1, fp)) {
        printf("%-5d %-6d %-15s %-4d %-7d %-10s\n",
               b.booking_id, b.train_id,
               b.passenger_name, b.age,
               b.tickets, status_to_string(b.status));
    }
    fclose(fp);
}

