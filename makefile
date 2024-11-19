CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o call_simulator.o app_simulator.o sms_simulator.o location_simulator.o network_simulator.o notification_simulator.o screen_lock_simulator.o logger.o
TARGET = simulate_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c call_simulator.h sms_simulator.h app_simulator.h notification_simulator.h network_simulator.h location_simulator.h screen_lock_simulator.h 
	$(CC) $(CFLAGS) -c main.c

call_simulator.o: call_simulator.c call_simulator.h logger.h network_simulator.h
	$(CC) $(CFLAGS) -c call_simulator.c

app_simulator.o: app_simulator.c app_simulator.h call_simulator.h logger.h sms_simulator.h network_simulator.h
	$(CC) $(CFLAGS) -c app_simulator.c

sms_simulator.o: sms_simulator.c sms_simulator.h logger.h
	$(CC) $(CFLAGS) -c sms_simulator.c

location_simulator.o: location_simulator.c location_simulator.h logger.h
	$(CC) $(CFLAGS) -c location_simulator.c

network_simulator.o: network_simulator.c network_simulator.h logger.h
	$(CC) $(CFLAGS) -c network_simulator.c

notification_simulator.o: notification_simulator.c notification_simulator.h logger.h
	$(CC) $(CFLAGS) -c notification_simulator.c

screen_lock_simulator.o: screen_lock_simulator.c screen_lock_simulator.h logger.h
	$(CC) $(CFLAGS) -c screen_lock_simulator.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f $(TARGET) $(OBJS)
