#include "train.h"
#include "file.h"

static void update_seats(Train *t, int count) {
    t->available_seats -= count;
}

void add_train() {
    Train t;

    printf("Train ID: ");
    scanf("%d", &t.train_id);

    printf("Train Name: ");
    scanf(" %49[^\n]", t.name);

    printf("From: ");
    scanf(" %29[^\n]", t.from);

    printf("To: ");
    scanf(" %29[^\n]", t.to);

    printf("Train Timing (HH:MM): ");
    scanf(" %19[^\n]", t.timing);

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
        printf("No trains available.\n");
        return;
    }

    printf("\n%-6s %-15s %-10s %-10s %-8s %-10s\n",
           "ID", "NAME", "FROM", "TO", "TIME", "SEATS");
    printf("---------------------------------------------------------------\n");

    while (fread(&t, sizeof(Train), 1, fp)) {
        printf("%-6d %-15s %-10s %-10s %-8s %d/%d\n",
               t.train_id, t.name, t.from, t.to,
               t.timing, t.available_seats, t.total_seats);
    }
    fclose(fp);
}

int reduce_seats(int train_id, int count) {
    Train t;
    FILE *fp = fopen("data/trains.dat", "rb+");

    if (!fp) return 0;

    while (fread(&t, sizeof(Train), 1, fp)) {
        if (t.train_id == train_id) {
            if (t.available_seats < count) {
                fclose(fp);
                return 0;
            }
            update_seats(&t, count);
            fseek(fp, -sizeof(Train), SEEK_CUR);
            fwrite(&t, sizeof(Train), 1, fp);
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

