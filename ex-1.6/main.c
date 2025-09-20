#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

int auxTempo(SDL_Event* e,unsigned int* t){
    unsigned int s=SDL_GetTicks();
    int r=SDL_WaitEventTimeout(e,*t);
    unsigned int f=SDL_GetTicks();
    unsigned int elapsed=f-s;
    if(*t>elapsed) *t-=elapsed; else *t=0;
    return r;
}

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window*w=SDL_CreateWindow("Corrida",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,400,0);
    SDL_Renderer*r=SDL_CreateRenderer(w,-1,0);

    float x1=100, x2=100, x3=100;
    int y1=100, y2=200, y3=300;
    int finished1=0, finished2=0, finished3=0;
    int winner=0;
    unsigned int t=16; SDL_Event e;

    while(!SDL_QuitRequested()){
        auxTempo(&e,&t);

        const Uint8* state=SDL_GetKeyboardState(NULL);
        int mx,my;
        SDL_GetMouseState(&mx,&my);

        if(!finished1){ x1+=50*0.016f; if(x1>=700){x1=700; finished1=1; if(!winner) winner=1;} }
        if(!finished2){ if(state[SDL_SCANCODE_RIGHT]) x2+=50*0.016f; if(x2>=700){x2=700; finished2=1; if(!winner) winner=2;} }
        if(!finished3){ x3=mx; if(x3>=700){x3=700; finished3=1; if(!winner) winner=3;} }

        boxRGBA(r,0,0,800,400,30,30,30,255);
        lineRGBA(r,700,0,700,400,255,255,0,255);
        boxRGBA(r,(int)x1-25,y1-25,(int)x1+25,y1+25,255,0,0,255);  
        boxRGBA(r,(int)x2-25,y2-25,(int)x2+25,y2+25,0,255,255,255);   
        boxRGBA(r,(int)x3-25,y3-25,(int)x3+25,y3+25,255,0,255,255);    

        SDL_RenderPresent(r);
        t=16;

        if(finished1 && finished2 && finished3){
            if(winner==1) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Vencedor","Vermelho venceu!",w);
            else if(winner==2) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Vencedor","Ciano venceu!",w);
            else if(winner==3) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,"Vencedor","Magenta venceu!",w);

            SDL_Delay(2000);
            x1=x2=x3=100;
            finished1=finished2=finished3=0;
            winner=0;
        }
    }

    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    SDL_Quit();
    return 0;
}
