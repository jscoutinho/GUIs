#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *w = SDL_CreateWindow("Guitarra", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
    
    while (!SDL_QuitRequested()) {

        boxRGBA(r, 0, 0, 800, 600, 20, 20, 40, 255);

        filledEllipseRGBA(r, 250, 350, 120, 150, 40, 80, 200, 255);
        filledEllipseRGBA(r, 350, 350, 120, 150, 40, 80, 200, 255);
        filledCircleRGBA(r, 300, 350, 40, 10, 10, 10, 255);

        boxRGBA(r, 440, 300, 720, 400, 160, 120, 80, 255);
        boxRGBA(r, 720, 280, 770, 420, 100, 70, 50, 255);

        for (int i = 0; i < 6; i++) {
            int y = 310 + i * 18;
            lineRGBA(r, 440, y, 770, y, 230, 230, 230, 255);
        }

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
