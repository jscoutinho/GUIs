#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

int auxTempo(SDL_Event* e, unsigned int* t) {
    unsigned int s = SDL_GetTicks();
    int r = SDL_WaitEventTimeout(e, *t);
    unsigned int f = SDL_GetTicks();

    unsigned int elapsed = f - s;
    if (*t > elapsed) *t -= elapsed;
    else *t = 0;

    return r;
}

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erro ao inicializar SDL: %s\n", SDL_GetError());
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("Erro ao inicializar SDL_image: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Window* w = SDL_CreateWindow("Sprite com boost",
    SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1200, 800, 0);
    SDL_Renderer* r = SDL_CreateRenderer(w, -1, SDL_RENDERER_ACCELERATED);

   
    SDL_Surface* spriteSurface = IMG_Load("pixil-frame-0.png");
    if (!spriteSurface) {
        printf("Erro ao carregar imagem: %s\n", IMG_GetError());
        return 1;
    }

    SDL_Texture* spriteTexture = SDL_CreateTextureFromSurface(r, spriteSurface);
    SDL_FreeSurface(spriteSurface);

    
    const int frameWidth = 1150;   // largura de cada frame
    const int frameHeight = 1050;  // altura de cada frame
    const int cols = 4;
    const int rows = 4;

    
    float x = 200;
    int y = 400, dir = 1;
    float speed = 200; 
    unsigned int t = 16;
    SDL_Event e;
    unsigned int last = SDL_GetTicks(), boostEnd = 0;

    // Controle da animação
    int currentFrame = 0;
    unsigned int frameTime = 150; // tempo de cada frame em ms
    unsigned int lastFrameTime = 0;

    while (!SDL_QuitRequested()) {
        auxTempo(&e, &t);

        // Teclado
        const Uint8* state = SDL_GetKeyboardState(NULL);
        if (state[SDL_SCANCODE_SPACE] && boostEnd == 0) {
            speed = 400;
            boostEnd = SDL_GetTicks() + 2000;
        }
        if (boostEnd && SDL_GetTicks() > boostEnd) {
            speed = 200;
            boostEnd = 0;
        }

        // Movimento
        unsigned int now = SDL_GetTicks();
        float delta = (now - last) / 1000.0f;
        last = now;

        x += dir * speed * delta;
        if (x >= 900) dir = -1;
        if (x <= 300) dir = 1;

        // Atualizar frame da animação
        if (now > lastFrameTime + frameTime) {
            currentFrame = (currentFrame + 1) % cols; // avança coluna
            lastFrameTime = now;
        }

        // Linha da spritesheet depende da direção
        int row = (dir == 1) ? 0 : 2; // 0 = direita, 2 = esquerda

        SDL_Rect srcRect;
        srcRect.x = currentFrame * frameWidth;
        srcRect.y = row * frameHeight;
        srcRect.w = frameWidth;
        srcRect.h = frameHeight;
        
        SDL_Rect destRect;
        destRect.w = frameWidth / 2;
        destRect.h = frameHeight / 2;
        destRect.x = (int)x - destRect.w / 2;
        destRect.y = y - destRect.h / 2;

        SDL_SetRenderDrawColor(r, 50, 50, 50, 255);
        SDL_RenderClear(r);
        SDL_RenderCopy(r, spriteTexture, &srcRect, &destRect);
        SDL_RenderPresent(r);

        t = 16;
    }

    SDL_DestroyTexture(spriteTexture);
    SDL_DestroyRenderer(r);
    SDL_DestroyWindow(w);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
