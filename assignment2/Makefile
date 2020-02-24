CC               = $(CXX)
CXXFLAGS        += -std=c++11 -W -Wall -Werror

SOURCES          = $(wildcard *.cpp)
OBJECTS          = $(patsubst %.cpp,%.o,$(SOURCES))

all:             blackjack
blackjack:       $(OBJECTS)