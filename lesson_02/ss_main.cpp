#include "types.hpp"

#include <cstdio>

#if defined(_WIN32)
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>


namespace sdl
{
    static void print_error(const char* msg)
    {
        printf("%s\n%s\n", msg, SDL_GetError());
    }


    static void close()
    {
        SDL_Quit();
    }


    static bool init()
    {    
        constexpr auto SDL_OPTIONS = SDL_INIT_VIDEO;

        if (SDL_Init(SDL_OPTIONS) != 0)
        {
            print_error("SDL_Init failed");
            return false;
        }

        return true;
    }


    class ScreenMemory
    {
    public:
        SDL_Window* window = nullptr;
    };


    static void destroy_screen_memory(ScreenMemory& screen)
    {
        if(screen.window)
        {
            SDL_DestroyWindow(screen.window);
        }
    }


    static bool create_window(ScreenMemory& screen, cstr title, u32 width, u32 height)
    {
        screen.window = SDL_CreateWindow(
            title,
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            (int)width,
            (int)height,
            SDL_WINDOW_RESIZABLE);

        if(!screen.window)
        {
            print_error("SDL_CreateWindow failed");
            return false;
        }

        return true;
    }


    static bool create_screen_memory(ScreenMemory& screen, cstr title, u32 width, u32 height)
    {
        destroy_screen_memory(screen);

        if (!create_window(screen, title, width, height))
        {
            destroy_screen_memory(screen);
            return false;
        }

        return true;
    }
}


/* main variables */

namespace
{
    sdl::ScreenMemory screen{};
}


static bool main_init()
{
    if(!sdl::init())
    {        
        return false;
    }

    if (!sdl::create_screen_memory(screen, "Window", 200, 200))
    {
        return false;
    }

    printf("main_init() OK!\n");
    return true;
}


static void main_close()
{
    sdl::destroy_screen_memory(screen);    
    sdl::close();
}


static void main_loop()
{
    u32 count = 0;
    while (count < 300)
    {
        SDL_Delay(16);
        count++;
    }
}


int main()
{
    if (!main_init())
    {
        return EXIT_FAILURE;
    }

    main_loop();

    main_close();

    return EXIT_SUCCESS;    
}