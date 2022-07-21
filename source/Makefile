all:
	gcc -I../header *.c -c
	cp *.o ../object
debug:
	gcc -g -I../header *.c -c
	cp *.o ../object
build:
	gcc *.o -o OnlineAirlineReservationApp -lm
	cp OnlineAirlineReservationApp ../build
	rm *.o 
clean:
	rm -r *.o OnlineAirlineReservationApp
run:
	./OnlineAirlineReservationApp
