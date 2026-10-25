cmake_minimum_required(VERSION 3.13...3.27)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(my_project)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# rest of your project
add_executable(main
	main.c
	pico.c
	display.c
	keyboard.c
	text.c
	tty.c

	character_set/null.c
	character_set/a.c
	character_set/b.c
	character_set/c.c
	character_set/d.c
	character_set/e.c
	character_set/f.c
	character_set/g.c
	character_set/h.c
	character_set/i.c
	character_set/j.c
	character_set/k.c
	character_set/l.c
	character_set/m.c
	character_set/n.c
	character_set/o.c
	character_set/p.c
	character_set/q.c
	character_set/r.c
	character_set/s.c
	character_set/t.c
	character_set/u.c
	character_set/v.c
	character_set/w.c
	character_set/x.c
	character_set/y.c
	character_set/z.c
	character_set/space.c

	character_set/set.c
	character_set/character.h
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(main pico_stdlib hardware_spi)

# create map/bin/hex/uf2 file in addition to ELF.
pico_enable_stdio_usb(main  1)
pico_enable_stdio_uart(main 0)
pico_add_extra_outputs(main)
