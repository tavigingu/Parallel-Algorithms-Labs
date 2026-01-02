CC = gcc
CFLAGS = -Wall -Wextra -pthread

all: oneProducerOneConsumerOneBuffer oneProducerOneConsumerFiveBuffer multipleProducersMultipleConsumers philosophers readersWriters smokers barber

oneProducerOneConsumerOneBuffer: oneProducerOneConsumerOneBuffer.c
	$(CC) $(CFLAGS) oneProducerOneConsumerOneBuffer.c -o oneProducerOneConsumerOneBuffer -lm

oneProducerOneConsumerFiveBuffer: oneProducerOneConsumerFiveBuffer.c
	$(CC) $(CFLAGS) oneProducerOneConsumerFiveBuffer.c -o oneProducerOneConsumerFiveBuffer -lm

multipleProducersMultipleConsumers: multipleProducersMultipleConsumers.c
	$(CC) $(CFLAGS) multipleProducersMultipleConsumers.c -o multipleProducersMultipleConsumers -lm

philosophers: philosophers.c
	$(CC) $(CFLAGS) philosophers.c -o philosophers -lm

readersWriters: readersWriters.c
	$(CC) $(CFLAGS) readersWriters.c -o readersWriters -lm

smokers: smokers.c
	$(CC) $(CFLAGS) smokers.c -o smokers -lm

barber: barber.c
	$(CC) $(CFLAGS) barber.c -o barber -lm

clean:
	rm -f oneProducerOneConsumerOneBuffer oneProducerOneConsumerFiveBuffer multipleProducersMultipleConsumers philosophers readersWriters smokers barber out*

.PHONY: all clean
