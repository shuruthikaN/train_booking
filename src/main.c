#include "train.h"
#include "booking.h"

typedef void (*MenuFunc)();

int main() {
    int choice;
    MenuFunc menu[] = { add_train, view_trains, book_ticket, view_bookings };

    do {
        printf("\n1.Add Train\n2.View Trains\n3.Book Ticket\n4.View Bookings\n0.Exit\nChoice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4)
            menu[choice - 1]();

    } while (choice != 0);

    return 0;
}

