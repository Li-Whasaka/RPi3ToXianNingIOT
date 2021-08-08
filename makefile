main: *.o
	gcc *.o -o main -lmosquitto -lcjson -lwiringPi

*.o: *.c
	gcc -c *.c

.PHONY:clean
clean:
	rm *.o main
