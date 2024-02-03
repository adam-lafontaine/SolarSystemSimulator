GPP := g++-11 -std=c++17

#GPP += -O3
#GPP += -DNDEBUG

# apt-get install libsdl2-dev

SDL2 := -lSDL2

NO_FLAGS := 
ALL_LFLAGS := $(SDL2)


# directories

root := .

build := $(root)/build

exe := solar_system

program_exe := $(build)/$(exe)


#*** util ***

types_h := $(root)/types.hpp

#**********


#*** main cpp ***

main_c := $(root)/ss_main.cpp
main_o := $(build)/main.o
obj := $(main_o)

main_dep := $(types_h)

#************



$(main_o): $(main_c) $(main_dep)
	@echo "\n  main"
	$(GPP) -o $@ -c $< $(SDL2)


$(program_exe): $(obj)
	@echo "\n  program_exe"
	$(GPP) -o $@ $+ $(ALL_LFLAGS)



build: $(program_exe)


run: build
	$(program_exe)
	@echo "\n"


clean:
	rm -rfv $(build)/*

setup:
	mkdir -p $(build)