#include "image.hpp"

#include <cstdio>

#if defined(_WIN32)
#define SDL_MAIN_HANDLED
#endif

#include <SDL2/SDL.h>


namespace img = image;


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
        SDL_Renderer* renderer = nullptr;
        SDL_Texture* texture = nullptr;

        img::Image image;
    };


    static void destroy_screen_memory(ScreenMemory& screen)
    {
        img::destroy_image(screen.image);

        if (screen.texture)
        {
            SDL_DestroyTexture(screen.texture);
        }

        if (screen.renderer)
        {
            SDL_DestroyRenderer(screen.renderer);
        }

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


    static bool create_renderer(ScreenMemory& screen)
    {
        screen.renderer = SDL_CreateRenderer(screen.window, -1, 0);

        if(!screen.renderer)
        {
            print_error("SDL_CreateRenderer failed");
            return false;
        }

        return true;
    }


    static bool create_texture(ScreenMemory& screen, u32 width, u32 height)
    {
        screen.texture =  SDL_CreateTexture(
            screen.renderer,
            SDL_PIXELFORMAT_ABGR8888,
            SDL_TEXTUREACCESS_STREAMING,
            width,
            height);
        
        if(!screen.texture)
        {
            print_error("SDL_CreateTexture failed");
            return false;
        }

        return true;
    }


    static bool create_screen_memory(ScreenMemory& screen, cstr title, u32 width, u32 height)
    {
        destroy_screen_memory(screen);

        if (!img::create_image(screen.image, width, height))
        {
            return false;
        }

        if (!create_window(screen, title, width, height))
        {
            destroy_screen_memory(screen);
            return false;
        }

        if (!create_renderer(screen))
        {
            destroy_screen_memory(screen);
            return false;
        }

        if (!create_texture(screen, width, height))
        {
            destroy_screen_memory(screen);
            return false;
        }

        return true;
    }


    static void render_screen(ScreenMemory const& screen)
    {
        static_assert(sizeof(img::Pixel) == 4); // RGBAu8 -> SDL_PIXELFORMAT_ABGR8888

        auto const pitch = screen.image.width * sizeof(img::Pixel);
        auto error = SDL_UpdateTexture(screen.texture, 0, (void*)screen.image.data_, pitch);
        if(error)
        {
            print_error("SDL_UpdateTexture failed");
        }

        error = SDL_RenderCopy(screen.renderer, screen.texture, 0, 0);
        if(error)
        {
            print_error("SDL_RenderCopy failed");
        }
        
        SDL_RenderPresent(screen.renderer);
    }
}


/* main variables */

namespace
{
    sdl::ScreenMemory screen{};
    static bool running = false;

    img::Pixel background_color;
    constexpr auto BG_RED = img::to_pixel(255, 0, 0);
    constexpr auto BG_GREEN = img::to_pixel(0, 255, 0);
    constexpr auto BG_BLUE = img::to_pixel(0, 0, 255);
}


static void end_program()
{
    running = false;
}


static void handle_keyboard_event(SDL_Keycode key_code)
{
    switch (key_code)
    {
    case SDLK_r:
        background_color = BG_RED;
        break;

    case SDLK_g:
        background_color = BG_GREEN;
        break;

    case SDLK_b:
        background_color = BG_BLUE;
        break;
    }
}


static void handle_sdl_event(SDL_Event const& event, SDL_Window* window)
{
    switch (event.type)
    {
    case SDL_QUIT:
        printf("SDL_QUIT\n");
        end_program();
        break;
    
    case SDL_KEYDOWN:
    case SDL_KEYUP:
    {
        auto key_code = event.key.keysym.sym;
        auto alt = event.key.keysym.mod & KMOD_ALT;

        if (alt)
        {
            switch (key_code)
            {
            case SDLK_F4:
                printf("ALT F4\n");
                end_program();
                break;
            
            default:
                break;
            }
        }
        else
        {
            switch (key_code)
            {
            case SDLK_ESCAPE:
                printf("ESC\n");
                end_program();
                break;

            default:
                handle_keyboard_event(key_code);
                break;
            }
        }
    }
    
    default:
        break;
    }
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

    background_color = BG_RED;

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
    running = true;

    u32 count = 0;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            handle_sdl_event(event, screen.window);
        }

        img::fill(img::make_view(screen.image), background_color);
        sdl::render_screen(screen);

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