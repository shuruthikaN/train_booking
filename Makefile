CC = gcc
CFLAGS = -Wall -pthread -Iinclude

OBJ = src/main.o src/train.o src/booking.o src/file.o

train_booking: $(OBJ)
	$(CC) $(CFLAGS) -o train_booking $(OBJ)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o train_booking

