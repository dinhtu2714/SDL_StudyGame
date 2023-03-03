


#include <iostream>
#include <SDL.h>

using namespace std;

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const char* WINDOW_TITLE = "SET UP SDL CODE";

void logSDLError (ostream& os, string msg, bool fatal)
{
    os << msg << "Error: "<<SDL_GetError() <<endl;
    if (fatal)
    {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logSDLError(std::cout,"SDL_Init", true);
        //May that
        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //May ao
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL)
        logSDLError(cout, "CreateWindow", true);
    //Maythat
    //renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Mayao
    renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == NULL)
        logSDLError(cout, "CreateRenderer", true);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "Linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void waitKeyPressed()
{
    SDL_Event e;
    while (true)
    {
        if (SDL_WaitEvent(&e) != 0 && e.type == SDL_QUIT)
            return ;
        SDL_Delay(10);
    }
}

void Draw(SDL_Window* window, SDL_Renderer* renderer, const SDL_Rect& filled_rect)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255 , 255);
    SDL_RenderFillRect(renderer, &filled_rect);

    //SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);
}
void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

int main (int argc, char* argv[])
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    initSDL(window, renderer);

    SDL_Rect filled_rect;
    filled_rect.x = SCREEN_WIDTH/2;
    filled_rect.y = SCREEN_HEIGHT/2;
    filled_rect.w = 30;
    filled_rect.h = 30;
    Draw(window, renderer, filled_rect);

    int step = 10;
    SDL_Event e;
    while (true)
    {

        if (SDL_WaitEvent(&e) == 0)
            continue;
        if (e.type == SDL_QUIT)
            break;
        if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_ESCAPE)
                break;
            if (e.key.keysym.sym == SDLK_LEFT)
                filled_rect.x = (filled_rect.x + SCREEN_WIDTH - step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_RIGHT)
                filled_rect.x = (filled_rect.x + SCREEN_WIDTH + step) % SCREEN_WIDTH;
            if (e.key.keysym.sym == SDLK_UP)
                filled_rect.y = (filled_rect.y + SCREEN_HEIGHT - step) % SCREEN_HEIGHT;
            if (e.key.keysym.sym == SDLK_DOWN)
                filled_rect.y = (filled_rect.y + SCREEN_HEIGHT + step) % SCREEN_HEIGHT;
            Draw(window, renderer, filled_rect);
        }
    }

    waitKeyPressed();
    quitSDL(window, renderer);
    return 0;
}



