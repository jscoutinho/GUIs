#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *w = SDL_CreateWindow("3 Retângulos", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);

    float x1 = 100;
    int y1 = 100;
    int dir1 = 1;
    int x2 = 300, y2 = 250;
    int x3 = 500, y3 = 400;
    Uint32 last = SDL_GetTicks();
    SDL_Event e;

    while (!SDL_QuitRequested()) {
        SDL_WaitEventTimeout(&e, 16);
        Uint32 now = SDL_GetTicks();
        float delta = (now - last)/1000.0f;
        last = now;

        x1 += dir1*100*delta;
        if(x1>=700) dir1=-1;
        if(x1<=100) dir1=1;

        const Uint8 *state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_UP]) y2-=200*delta;
        if(state[SDL_SCANCODE_DOWN]) y2+=200*delta;
        if(state[SDL_SCANCODE_LEFT]) x2-=200*delta;
        if(state[SDL_SCANCODE_RIGHT]) x2+=200*delta;

        int mx,my;
        SDL_GetMouseState(&mx,&my);
        x3=mx; y3=my;

        boxRGBA(r,0,0,800,600,60,0,60,255);
        boxRGBA(r,(int)x1-25,y1-25,(int)x1+25,y1+25,255,165,0,255);
        boxRGBA(r,(int)x2-25,y2-25,(int)x2+25,y2+25,0,255,255,255);
        boxRGBA(r,(int)x3-25,y3-25,(int)x3+25,y3+25,255,0,255,255);

        SDL_RenderPresent(r);
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
