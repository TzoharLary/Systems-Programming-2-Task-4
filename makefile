// ID: 207492315
// Email: Tzohary1234@gmail.com

CXX = g++
CXXFLAGS = -std=c++17 -Wall -g
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

SOURCES = Demo.cpp Complex.cpp TestCounter.cpp Test.cpp
OBJECTS = $(SOURCES:.cpp=.o)

DEMO = demo
TREE = tree
TEST = test
BUILD_TEST = build_test

$(TREE): $(DEMO)
	./$^ 

$(TEST): $(BUILD_TEST)
	./$(TEST)

$(DEMO): Demo.o Complex.o
	$(CXX) $(CXXFLAGS) $^ -o $(DEMO) $(SFML_FLAGS)

$(BUILD_TEST): TestCounter.o Test.o Complex.o
	$(CXX) $(CXXFLAGS) $^ -o $(TEST)

tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

valgrind: $(DEMO) $(TEST)
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o demo test
