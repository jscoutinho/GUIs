#include <SDL2/SDL.h>

int auxTempo(SDL_Event* evt, unsigned int* ms) {
    unsigned int start = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(evt, *ms);
    unsigned int end = SDL_GetTicks();

    if (*ms > (end - start)) {
        *ms -= (end - start);
    } else {
        *ms = 0;
    }

    return ret;
}

/*
USO:

SDL_Event e;
unsigned int timeout = 5000;

while (timeout > 0) {
    if (auxTempo(&e, &timeout)) {
        //evento aconteceu
        if (e.type == SDL_QUIT) break;
    } else {
        // timeout expirou
        break;
    }
}

*/
