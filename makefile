CC = gcc
CFLAGS = -Wall -Wextra -std=c99
OBJS = main.o call_simulator.o app_simulator.o sms_simulator.o logger.o 
TARGET = simulate_app

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c call_simulator.h sms_simulator.h app_simulator.h
	$(CC) $(CFLAGS) -c main.c

call_simulator.o: call_simulator.c call_simulator.h logger.h
	$(CC) $(CFLAGS) -c call_simulator.c

app_simulator.o: app_simulator.c app_simulator.h call_simulator.h logger.h sms_simulator.h
	$(CC) $(CFLAGS) -c app_simulator.c

sms_simulator.o: sms_simulator.c sms_simulator.h logger.h
	$(CC) $(CFLAGS) -c sms_simulator.c

logger.o: logger.c logger.h
	$(CC) $(CFLAGS) -c logger.c

clean:
	rm -f $(TARGET) $(OBJS)
