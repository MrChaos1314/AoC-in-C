CXX = g++

CXXFLAGS = -Wall -g -O3

TARGET = main

SRCS = main.cpp general.cpp map.cpp

OBJS = $(SRCS:.cpp=.o)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

%.o: %.cpp %.h
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm $(TARGET) $(OBJS)
