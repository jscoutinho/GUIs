#include <SDL2/SDL.h>

int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* win = SDL_CreateWindow("BOOM", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer * ren = SDL_CreateRenderer(win, -1, 0);
	
	
	SDL_SetRenderDrawColor(ren, 0, 4, 0, 0);
	SDL_RenderClear(ren);
	
	SDL_SetRenderDrawColor(ren, 0, 128, 0, 0);
	SDL_Rect r = {200, 100, 200, 200};
	SDL_RenderFillRect(ren, &r);
	
	SDL_SetRenderDrawColor(ren, 4,22,1,0); //Olho esquerdo
	SDL_Rect p1 = {240,140, 40, 40};
	SDL_RenderFillRect(ren, &p1);
	
	SDL_SetRenderDrawColor(ren, 4,22,1,0); //Olho direito
	SDL_Rect p2 = {320,140, 40, 40};
	SDL_RenderFillRect(ren, &p2);
	
	SDL_SetRenderDrawColor(ren, 4,22,1,0); // Nariz 
	SDL_Rect p3 = {280,180, 40, 60};
	SDL_RenderFillRect(ren, &p3);
	
	SDL_SetRenderDrawColor(ren, 4,22,1,0); // Boca esquerda
	SDL_Rect p4 = {260,200, 20, 60};
	SDL_RenderFillRect(ren, &p4);
	
	SDL_SetRenderDrawColor(ren, 4,22,1,0); //Boca direita
	SDL_Rect p5 = {320,200, 20, 60};
	SDL_RenderFillRect(ren, &p5);


	
	SDL_SetRenderDrawColor(ren, 4,45,2,0); //Sombra olho esquerdo
	SDL_Rect p6 = {240,140, 10, 40};
	SDL_RenderFillRect(ren, &p6);

	SDL_SetRenderDrawColor(ren, 4,45,2,0); //Sombra olho esquerdo
	SDL_Rect p7 = {240,140, 40, 10};
	SDL_RenderFillRect(ren, &p7);


	SDL_SetRenderDrawColor(ren, 4,45,2,0); //s Olho direito
	SDL_Rect p8 = {350,140, 10, 40};
	SDL_RenderFillRect(ren, &p8);

	SDL_SetRenderDrawColor(ren, 4,45,2,0); //s Olho direito
	SDL_Rect p9 = {320,140, 40, 10};
	SDL_RenderFillRect(ren, &p9);


	
	SDL_SetRenderDrawColor(ren, 4,45,2,0); // s Nariz 
	SDL_Rect p10 = {280,180, 40, 10};
	SDL_RenderFillRect(ren, &p10);
	


	SDL_SetRenderDrawColor(ren, 4,45,2,0); // s Boca esquerda
	SDL_Rect p11 = {260,200, 20, 10};
	SDL_RenderFillRect(ren, &p11);



	SDL_SetRenderDrawColor(ren, 4,45,2,0); //s Boca direita
	SDL_Rect p12 = {320,200, 20, 10};
	SDL_RenderFillRect(ren, &p12);


	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_Rect p13 = {215, 140, 1, 130};
	SDL_RenderFillRect(ren, &p13);

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	SDL_Rect p14 = {215, 275, 1, 1};
	SDL_RenderFillRect(ren, &p14);
	
	
	SDL_RenderPresent(ren);
	SDL_Delay(5000);
	
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return 0; 
}
