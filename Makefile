game:
	mkdir -p ./out
	clang -o ./out/game ./src/main.c -O3 -Wall -Wextra -std=c11 -pthread -lraylib

clean:
	rm -rf ./out

run: game
	./out/game