blasteroids: blasteroids.o blast.o asteroid.o spaceship.o
	gcc -g blasteroids.o blast.o asteroid.o spaceship.o -I/usr/local/include -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives -o blasteroids

blasteroids.o: blasteroids.c blasteroids.h
	gcc -g -o0 -c -I/usr/local/include blasteroids.c -o blasteroids.o

spaceship: spaceship.c spaceship.o
	gcc -g -o0 -c -I/usr/local/include spaceship.c -o spaceship.o

asteroid.o: asteroid.c asteroid.h
	gcc -g -o0 -c -I/usr/local/include asteroid.c -o asteroid.o

blast.o: blast.c blast.h
	gcc -g -o0 -c -I/usr/local/include blast.c -o blast.o
	
threads: threads.c
	gcc -g -o0 threads.c -I/usr/local/include -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives -o threads

bitmap: bitmap.c
	gcc -g bitmap.c -I/usr/local/include -L/usr/local/lib -lallegro -lallegro_main -lallegro_primitives -o bitmap
