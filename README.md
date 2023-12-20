# asteroids-sdl-cpp

## Start
Linux compile (TODO: use cmake or something to make this less convoluted to maintain)
`g++ -std=c++20 main.cpp glad/src/glad.c util.cpp game.cpp ./sdl_components/texture.cpp -I ./ -I ./sdl_components -I ./members -I ./entities -I ./glad/include -o prog -lSDL2`

Run
`./prog`