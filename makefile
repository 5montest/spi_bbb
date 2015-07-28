CC		= g++
CCFLAGS	= -Wall -Wextra -O2 -g
SOURCES:= $(wildcard *.cpp)
TARGET	= $(SOURCES:.cpp=.bin)
INCLUDE = wiringBBB.cpp
all: $(TARGET)

%.bin:%.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) $< -o $@

clean:
	$(RM) -r *.bin
