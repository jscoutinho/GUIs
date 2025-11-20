#include <SDL2/SDL.h>
#include <stdio.h>



int AUX_WaitEventTimeout(SDL_Event* e, unsigned int* t) {
    unsigned int start = SDL_GetTicks();
    int ret = SDL_WaitEventTimeout(e, *t);
    unsigned int end = SDL_GetTicks();
    unsigned int elapsed = end - start;

    if (*t > elapsed) *t -= elapsed;
    else *t = 0;

    return ret;
}

 
#define MULTICLICK_TIMEOUT 250   // 250ms para encerrar um múltiplo clique

static int click_count = 0;
static int tracking = 0;
static int click_x = 0, click_y = 0;
static unsigned int timer = 0;

static void emit_multiclick() {
    if (click_count == 0) return;

    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    ev.user.code = click_count;   
    SDL_PushEvent(&ev);

    click_count = 0;
    tracking = 0;
}

void HandleMultiClick(SDL_Event *e) {

    
    if (tracking && SDL_GetTicks() > timer) {
        emit_multiclick();
    }

    
    if (e->type == SDL_MOUSEMOTION) {
        if (tracking) emit_multiclick();
        return;
    }

  
    if (e->type == SDL_MOUSEBUTTONDOWN) {

        int mx = e->button.x;
        int my = e->button.y;

        if (!tracking) {
           
            tracking = 1;
            click_count = 1;
            click_x = mx;
            click_y = my;
            timer = SDL_GetTicks() + MULTICLICK_TIMEOUT;
            return;
        }

        
        if (abs(mx - click_x) <= 3 && abs(my - click_y) <= 3) {
            click_count++;
            timer = SDL_GetTicks() + MULTICLICK_TIMEOUT;
        } else {
            
            emit_multiclick();
            tracking = 1;
            click_count = 1;
            click_x = mx;
            click_y = my;
            timer = SDL_GetTicks() + MULTICLICK_TIMEOUT;
        }
    }
}

int main() {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* w = SDL_CreateWindow(
        "Double/Triple Click",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600, 0
    );

    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event e;
    unsigned int t = 16;

    SDL_Color color = {255, 255, 255, 255};

    int box_size = 150;           
    const int MIN_SIZE = 20;     
    const int MAX_SIZE = 400;    
    while (!SDL_QuitRequested()) {

        AUX_WaitEventTimeout(&e, &t);

       
        HandleMultiClick(&e);

        if (e.type == SDL_USEREVENT) {
            int n = e.user.code;

            printf("Multiclick detectado: %d\n", n);

            if (n == 1) {
                // clique simples → muda cor
                color.r = rand() % 255;
                color.g = rand() % 255;
                color.b = rand() % 255;
            }
            else if (n == 2) {
              
                box_size += 20;
                if (box_size > MAX_SIZE) box_size = MAX_SIZE;
            }
            else if (n == 3) {
                
                box_size -= 20;
                if (box_size < MIN_SIZE) box_size = MIN_SIZE;
            }
        }

    
        SDL_SetRenderDrawColor(r, 20, 20, 20, 255);
        SDL_RenderClear(r);

        SDL_Rect box;
        box.w = box_size;
        box.h = box_size;
        box.x = 400 - box_size/2;
        box.y = 300 - box_size/2;

        SDL_SetRenderDrawColor(r, color.r, color.g, color.b, 255);
        SDL_RenderFillRect(r, &box);

        SDL_RenderPresent(r);

        t = 16;
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
