CXX = g++
CXXFLAGS = -Wall -O2
LDFLAGS = -lfreeglut -lopengl32 -lglu32
TARGET = main

SRCS = main.cpp \
       globals/Globals.cpp \
       physics/Physics.cpp \
       renderer/Renderer.cpp \
       camera/Camera.cpp \
       input/Input.cpp \
       game_manager/GameManager.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET).exe
