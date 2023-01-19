PROGS = asteroids
CC = gcc
CFLAGS = -Wall -g
ALLEGRO = -lallegro -lallegro_primitives -lallegro_image -lallegro_font -lallegro_audio -lallegro_acodec
objects = main.o jewelsLib.o allegroDisplay.o allegroUtil.o allegroKeyboard.o allegroSprites.o allegroAudio.o

asteroids: $(objects)
	$(CC) $(CFLAGS) $(objects) $(ALLEGRO) -o $(PROGS)

main.o: main.c allegroUtil.h jewelsLib.h allegroDisplay.h allegroKeyboard.h allegroSprites.h allegroAudio.h
	$(CC) $(CFLAGS) -c main.c

allegroDisplay.o: allegroDisplay.c allegroDisplay.h
	$(CC) $(CFLAGS) -c allegroDisplay.c allegroDisplay.h

jewelsLib.o: jewelsLib.c jewelsLib.h allegroUtil.h
	$(CC) $(CFLAGS) -c jewelsLib.c

allegroKeyboard.o: allegroKeyboard.c allegroKeyboard.h
	$(CC) $(CFLAGS) -c allegroKeyboard.c

allegroSprites.o: allegroSprites.c allegroSprites.h
	$(CC) $(CFLAGS) -c allegroSprites.c
	
allegroAudio.o: allegroAudio.c allegroAudio.h
	$(CC) $(CFLAGS) -c allegroAudio.c
	
allegroUtil.o: allegroUtil.c allegroUtil.h
	$(CC) $(CFLAGS) -c allegroUtil.c

clean:
	-rm -f *~ *.o

purge: clean
	-rm -f $(PROGS)