#id:324207935 email:shbabkoff123@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Demo.cpp Complex.cpp TestCounter.cpp Test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

tree: demo
	./$^

demo: Demo.o Complex.o
	$(CXX) $(CXXFLAGS) $^ -o demo $(SFML_FLAGS)

test: TestCounter.o Test.o Complex.o
	$(CXX) $(CXXFLAGS) $^ -o test

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test
