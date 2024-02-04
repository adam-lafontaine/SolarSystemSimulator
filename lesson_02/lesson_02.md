# Lesson 02

Topics covered
* Install SDL2 - sudo apt-get install libsdl2-dev
* Open SDL window


### Steps

* Add SDL init and close and run without updating Makefile

```cpp
int main()
{
    if (sdl::init())
    {
        printf("SDL OK!\n");
    }
    
    sdl::close();
}

```
* Update Makefile links and run
* Create types.hpp
* ScreenMemory with SDL_Window*
* Update Makefile with types.hpp

```cpp
int main()
{
    if (sdl::init())
    {
        printf("SDL OK!\n");
    }

    sdl::ScreenMemory screen{};

    if (sdl::create_screen_memory(screen, "Window", 200, 200))
    {
        printf("create_screen_memory() OK!\n");
    }

    sdl::destroy_screen_memory(screen);
    
    sdl::close();
}
```

* Refactor with main_init() and main_close()
* Add main_loop() with counter and SDL_Delay()