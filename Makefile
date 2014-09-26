CC := clang++
# CFLAGS := -O3  -fno-rtti -DUNIX
CFLAGS := -Iinclude -O3 -fno-rtti -DUNIX
LDFLAGS := `pkg-config --cflags --static --libs allegro-static-5 allegro_acodec-static-5 allegro_audio-static-5 allegro_color-static-5 allegro_dialog-static-5 allegro_image-static-5 allegro_main-static-5 allegro_primitives-static-5`
SOURCES := $(wildcard *.cpp)
OBJECTS := $(SOURCES:.cpp=.o)
EXECUTABLE := atb

.PHONY: all clean

all: $(EXECUTABLE)

clean:
	$(RM) $(OBJECTS) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@  $(LDFLAGS) 

.cpp.o:
	$(CC) -c $(CFLAGS) $< -o $@

