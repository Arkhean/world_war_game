all : game

# $@ = entete
# $< = premier
# $^ = tout

build/menu.o : src/menu.c src/menu.h
	gcc -o $@ -c $<
build/AI.o : src/AI.c src/AI.h
	gcc -o $@ -c $<
build/init.o : src/init.c src/init.h
	gcc -o $@ -c $<
build/main.o : src/main.c
	gcc -o $@ -c $<
build/pixel.o : src/pixel.c src/pixel.h
	gcc -o $@ -c $<
build/jeu.o : src/jeu.c src/jeu.h
	gcc -o $@ -c $<

game : build/main.o build/menu.o build/AI.o build/init.o build/pixel.o build/jeu.o
	gcc -o $@ $^ -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean :
	rm build/*.o
