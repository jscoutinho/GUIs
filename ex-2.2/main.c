#include <SDL2/SDL.h>
#include <stdio.h>

#define DRAG_THRESHOLD 6

typedef enum {
    STATE_IDLE,
    STATE_MAYBE_CLICK,
    STATE_DRAGGING
} InputState;

int main() {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* w = SDL_CreateWindow(
        "Click vs Drag",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0
    );

    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    SDL_Rect box = {300, 200, 150, 150};
    SDL_Rect originalBox = box;

    InputState state = STATE_IDLE;
    int startX = 0, startY = 0;
    int offsetX = 0, offsetY = 0;

    SDL_Event e;

    while (!SDL_QuitRequested()) {

        while (SDL_PollEvent(&e)) {

            // ESC aborta qualquer gesto
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                if (state != STATE_IDLE) {
                    box = originalBox;
                    state = STATE_IDLE;
                    printf("GESTO ABORTADO\n");
                }
            }

            switch (state) {

            case STATE_IDLE:
                if (e.type == SDL_MOUSEBUTTONDOWN &&
                    e.button.button == SDL_BUTTON_LEFT &&
                    SDL_PointInRect(&(SDL_Point){e.button.x, e.button.y}, &box))
                {
                    state = STATE_MAYBE_CLICK;
                    startX = e.button.x;
                    startY = e.button.y;
                    originalBox = box;

                    offsetX = startX - box.x;
                    offsetY = startY - box.y;
                }
                break;

            case STATE_MAYBE_CLICK:
                if (e.type == SDL_MOUSEMOTION) {
                    int dx = e.motion.x - startX;
                    int dy = e.motion.y - startY;

                    if (abs(dx) >= DRAG_THRESHOLD ||
                        abs(dy) >= DRAG_THRESHOLD)
                    {
                        state = STATE_DRAGGING;
                        printf("INICIOU DRAG\n");
                    }
                }
                else if (e.type == SDL_MOUSEBUTTONUP &&
                         e.button.button == SDL_BUTTON_LEFT)
                {
                    printf("CLICK DETECTADO\n");
                    state = STATE_IDLE;
                }
                break;

            case STATE_DRAGGING:
                if (e.type == SDL_MOUSEMOTION) {
                    box.x = e.motion.x - offsetX;
                    box.y = e.motion.y - offsetY;
                }
                else if (e.type == SDL_MOUSEBUTTONUP &&
                         e.button.button == SDL_BUTTON_LEFT)
                {
                    printf("FINALIZOU DRAG\n");
                    state = STATE_IDLE;
                }
                break;
            }
        }

        SDL_SetRenderDrawColor(r, 25, 25, 25, 255);
        SDL_RenderClear(r);

        SDL_SetRenderDrawColor(r, 220, 160, 50, 255);
        SDL_RenderFillRect(r, &box);

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
