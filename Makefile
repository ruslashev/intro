OBJS = $(patsubst ./%.cc,.objs/%.o, $(shell find . -type f -name '*.cc'))
CXX = g++

all: out
	./out

.objs/%.o: ./%.cc
	@mkdir -p .objs
	@echo "Compiling $<"
	@$(CXX) -c -o $@ $< -Wall -Wextra -Wpedantic -Wno-unused-function -g -std=c++0x

out: $(OBJS)
	@echo "Linking to $@"
	@$(CXX) -o $@ $^

clean:
	rm -f out $(OBJS)

