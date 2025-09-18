#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SDL_MAIN_HANDLED
#define MAX_RECTS 10

int main(int argc, char* argv[]) {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Event event;
    int quit = 0;

    SDL_Rect rect = { 50, 50, 50, 50 };

    SDL_Rect rects[MAX_RECTS];
    SDL_Color colors[MAX_RECTS];
    int c = 0;

    srand(time(NULL));
    window = SDL_CreateWindow("keys-m", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    while (!quit) {
        if (SDL_WaitEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            } 
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                        if (rect.y > 0) rect.y -= 10;
                        break;
                    case SDLK_DOWN:
                        if (rect.y + rect.h < 400) rect.y += 10;
                        break;
                    case SDLK_LEFT:
                        if (rect.x > 0) rect.x -= 10;
                        break;
                    case SDLK_RIGHT:
                        if (rect.x + rect.w < 600) rect.x += 10;
                        break;
                }
            } 
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (c < MAX_RECTS) {
                    rects[c].x = event.button.x - 25;
                    rects[c].y = event.button.y - 25;
                    rects[c].w = 50;
                    rects[c].h = 50;

                    colors[c].r = rand() % 256;
                    colors[c].g = rand() % 256;
                    colors[c].b = rand() % 256;
                    colors[c].a = 255;

                    c++;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        SDL_RenderFillRect(renderer, &rect);

        for (int i = 0; i < c; i++) {
            SDL_SetRenderDrawColor(renderer,
                                   colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderFillRect(renderer, &rects[i]);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
