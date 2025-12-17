#include "train.h"
#include "file.h"

static void update_seats(Train *t) {
    if (t->available_seats > 0)
        t->available_seats--;
}

void add_train() {
    Train t;

    printf("Train ID: ");
    scanf("%d", &t.train_id);
    printf("Train Name: ");
    scanf("%s", t.name);
    printf("Train Timing (HH:MM): ");
    scanf("%s", t.timing);
    printf("Total Seats: ");
    scanf("%d", &t.total_seats);

    t.available_seats = t.total_seats;
    save_train(&t);

    printf("Train added successfully!\n");
}

void view_trains() {
    Train t;
    FILE *fp = fopen("data/trains.dat", "rb");

    if (!fp) {
        printf("No trains found.\n");
        return;
    }

    while (fread(&t, sizeof(Train), 1, fp)) {
        printf("ID:%d Name:%s Time:%s Seats:%d/%d\n",
               t.train_id, t.name, t.timing,
               t.available_seats, t.total_seats);
    }

    fclose(fp);
}

void reduce_seat_count(int train_id) {
    Train t;
    FILE *fp = fopen("data/trains.dat", "rb+");

    if (!fp) return;

    while (fread(&t, sizeof(Train), 1, fp)) {
        if (t.train_id == train_id) {
            update_seats(&t);
            fseek(fp, -sizeof(Train), SEEK_CUR);
            fwrite(&t, sizeof(Train), 1, fp);
            break;
        }
    }
    fclose(fp);
}

