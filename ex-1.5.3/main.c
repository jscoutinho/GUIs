#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int auxTempo(SDL_Event* e,unsigned int* t){
    unsigned int s=SDL_GetTicks();
    int r=SDL_WaitEventTimeout(e,*t);
    unsigned int f=SDL_GetTicks();

    unsigned int elapsed = f - s;
    if(*t > elapsed) *t -= elapsed;
    else *t = 0;

    return r;
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window*w=SDL_CreateWindow("Carro com boost",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,600,0);
    SDL_Renderer*r=SDL_CreateRenderer(w,-1,0);

    float x=200; int y=400,dir=1;
    float speed=10; unsigned int t=16; SDL_Event e;
    unsigned int last=SDL_GetTicks(),boostEnd=0;

    while(!SDL_QuitRequested()){
        auxTempo(&e,&t);
      
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if(state[SDL_SCANCODE_SPACE] && boostEnd==0){
            speed=20;
            boostEnd = SDL_GetTicks()+2000;
        }
        if(boostEnd && SDL_GetTicks()>boostEnd){speed=10; boostEnd=0;}

        unsigned int now=SDL_GetTicks();
        float delta=(now-last)/1000.0f; last=now;

        x+=dir*speed*delta;
        if(x>=600) dir=-1;
        if(x<=200) dir=1;

        boxRGBA(r,0,0,800,600,50,50,50,255);
        boxRGBA(r,(int)x-40,y-20,(int)x+40,y+20,200,0,0,255);
        boxRGBA(r,(int)x-25,y-35,(int)x+25,y-20,150,0,0,255);
        filledCircleRGBA(r,(int)x-30,y+25,12,0,0,0,255);
        filledCircleRGBA(r,(int)x+30,y+25,12,0,0,0,255);

        SDL_RenderPresent(r);
        t=16;
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
