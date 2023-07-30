OBJ_PATH = objects
SRC_PATH = source

SRCS = $(wildcard $(SRC_PATH)/*.cpp)

OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(notdir $(SRCS)))

CC = g++ -std=c++11 -O3 -g

BOOST_FLAG = -lboost_program_options -lgsl -lgslcblas -lm -lboost_iostreams -lboost_system -lboost_filesystem

all: demo

demo: $(OBJS)
	$(CC) $^ $(BOOST_FLAG) -o $@

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.cpp
	$(CC) -o $@ -c $<

clean:
	-rm -f $(OBJ_PATH)/*.o demo

run:
	./demo
