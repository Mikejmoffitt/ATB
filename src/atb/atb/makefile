CXX=g++
CFLAGS=
LDFLAGS=`pkg-config --cflags --libs allegro-5.1 allegro_acodec-5.1 allegro_audio-5.1 allegro_color-5.1 allegro_dialog-5.1 allegro_image-5.1 allegro_main-5.1 allegro_memfile-5.1 allegro_primitives-5.1`
INCLUDE=

OBJS=main.cpp BackdropRenderer.cpp Controller.cpp Grid.cpp HowToPlay.cpp LevelSelect.cpp Player.cpp TextRenderer.cpp 
OUT=atb

all: atb_rule

clean:
	rm -rf *.o atb

atb_rule: $(OJBS)
	$(CXX) $(OBJS) -o $(OUT) $(INCLUDE) $(CFLAGS) $(LDFLAGS)
