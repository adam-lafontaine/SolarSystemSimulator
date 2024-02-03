GPP := g++-11 -std=c++17

NO_FLAGS := 
ALL_LFLAGS := 


# directories

root := .

build := $(root)/build

exe := solar_system

program_exe := $(build)/$(exe)


#*** main cpp ***

main_c := $(root)/ss_main.cpp
main_o := $(build)/main.o
obj := $(main_o)

main_dep := 

#************



$(main_o): $(main_c) $(main_dep)
	@echo "\n  main"
	$(GPP) -o $@ -c $< $(NO_FLAGS)


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