FLAGS = -pedantic-errors -std=c++11

game_mechanics.o: game_mechanics.cpp game_mechanics.h
	g++ $(FLAGS) -c $<

user_management.o: user_management.cpp user_management.h
	g++ $(FLAGS) -c $<

shop.o: shop.cpp game_mechanics.h user_management.h
	g++ $(FLAGS) -c $<

main.o: main.cpp game_mechanics.h user_management.h
	g++ $(FLAGS) -c $<

main: game_mechanics.o user_management.o shop.o main.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -rf *.o *.txt main

.PHONY: clean
