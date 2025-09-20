#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *w = SDL_CreateWindow("Carro", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);

    float x = 100;
    int y = 400;
    int dir = 1;
    Uint32 last = SDL_GetTicks();

    while (!SDL_QuitRequested()) {
        Uint32 now = SDL_GetTicks();
        float delta = (now - last) / 1000.0f;
        last = now;

        x += dir * 10 * delta;

        if (x >= 700) dir = -1;
        if (x <= 100) dir = 1;

        boxRGBA(r, 0, 0, 800, 600, 50, 50, 50, 255);

      
        boxRGBA(r, (int)x-40, y-20, (int)x+40, y+20, 200, 0, 0, 255);
        boxRGBA(r, (int)x-25, y-35, (int)x+25, y-20, 150, 0, 0, 255);
        filledCircleRGBA(r, (int)x-30, y+25, 12, 0, 0, 0, 255);
        filledCircleRGBA(r, (int)x+30, y+25, 12, 0, 0, 0, 255);

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
