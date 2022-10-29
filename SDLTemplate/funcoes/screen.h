#include <SDL2/SDL.h>
#include <vector>

/**/
class Screen {
    public:
    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;

    Screen(){
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(600*1, 600*1, 0, &window, &renderer);
        SDL_RenderSetScale(renderer,1,1);
    }

    void pixel(float x, float y){
        points.emplace_back(x,y);
    }

    void show(){
        SDL_SetRenderDrawColor(renderer,100,100,100,255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer,255, 0, 0, 255);
        for (auto& point: points){
            SDL_RenderDrawPointF(renderer, point.x, point.y);
        }

        SDL_RenderPresent(renderer);
    }

    void input(){
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_QUIT){
                SDL_Quit();
                exit(0);
            }
        }
    }
};