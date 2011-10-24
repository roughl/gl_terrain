# Project: gl_terrain

CPP  = g++
CC   = gcc
OBJ  = src/main.o src/OpenGL.o src/Terrain.o src/HMapReader.o src/LuaFuncs.o src/Cube.o src/world.o src/Object.o src/Particle.o src/Config.o src/VectorCalc.o src/sphere.o
LINKOBJ  = src/main.o src/OpenGL.o src/Terrain.o src/HMapReader.o src/LuaFuncs.o src/Cube.o src/world.o src/Object.o src/Particle.o src/Config.o src/VectorCalc.o src/sphere.o
LIBS = lua sdl gl glu
BIN  = gl_terrain
LOGS = ReadBMP.log Terrain.log
CXXFLAGS += `pkg-config --cflags --libs $(LIBS)` $(CXXINCS)   -fexpensive-optimizations -O3 -std=c++0x
RM = rm -f

.PHONY: all all-before all-after clean clean-custom

all: all-before gl_terrain all-after


clean: clean-custom
	${RM} $(OBJ) $(BIN) $(LOGS)

$(BIN): $(OBJ)
	$(CPP) $(LINKOBJ) -o "gl_terrain" -Dmain=SDL_main $(CXXFLAGS)

%.o: %.cpp %.hpp
	$(CPP) -c $(CXXFLAGS) $< -o $@

# DO NOT DELETE

src/2DFuncs.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/2DFuncs.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/2DFuncs.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/2DFuncs.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/2DFuncs.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/2DFuncs.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
src/2DFuncs.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/2DFuncs.o: /usr/include/endian.h /usr/include/bits/endian.h
src/2DFuncs.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/2DFuncs.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/2DFuncs.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/2DFuncs.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/2DFuncs.o: /usr/include/libio.h /usr/include/_G_config.h
src/2DFuncs.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/2DFuncs.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/2DFuncs.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/2DFuncs.o: /usr/include/alloca.h /usr/include/string.h
src/2DFuncs.o: /usr/include/xlocale.h /usr/include/strings.h
src/2DFuncs.o: /usr/include/inttypes.h /usr/include/stdint.h
src/2DFuncs.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/2DFuncs.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/2DFuncs.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/2DFuncs.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/2DFuncs.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/2DFuncs.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/2DFuncs.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/2DFuncs.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/2DFuncs.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/2DFuncs.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/2DFuncs.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/2DFuncs.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/2DFuncs.o: /usr/include/SDL/SDL_ttf.h /usr/include/SDL/SDL.h
src/Config.o: src/Config.hpp /usr/include/SDL/SDL.h
src/Config.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/Config.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/Config.o: /usr/include/sys/types.h /usr/include/features.h
src/Config.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/Config.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/Config.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/Config.o: /usr/include/time.h /usr/include/endian.h
src/Config.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/Config.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/Config.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/Config.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/Config.o: /usr/include/stdio.h /usr/include/libio.h
src/Config.o: /usr/include/_G_config.h /usr/include/wchar.h
src/Config.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/Config.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/Config.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/Config.o: /usr/include/string.h /usr/include/xlocale.h
src/Config.o: /usr/include/strings.h /usr/include/inttypes.h
src/Config.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/Config.o: /usr/include/ctype.h /usr/include/iconv.h
src/Config.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/Config.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/Config.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/Config.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/Config.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/Config.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/Config.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/Config.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/Config.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/Config.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/Config.o: /usr/include/SDL/SDL_version.h
src/Cube.o: src/Cube.hpp src/Object.hpp /usr/include/lua.hpp
src/Cube.o: /usr/include/lua.h /usr/include/luaconf.h /usr/include/limits.h
src/Cube.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/Cube.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/Cube.o: /usr/include/gnu/stubs-64.h /usr/include/bits/posix1_lim.h
src/Cube.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/Cube.o: /usr/include/bits/posix2_lim.h /usr/include/lualib.h
src/Cube.o: /usr/include/lauxlib.h /usr/include/stdio.h
src/Cube.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/Cube.o: /usr/include/libio.h /usr/include/_G_config.h
src/Cube.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/Cube.o: /usr/include/bits/sys_errlist.h /usr/include/GL/gl.h
src/Cube.o: /usr/include/GL/glext.h /usr/include/inttypes.h
src/Cube.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/Cube.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/Cube.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/Cube.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/Cube.o: /usr/include/time.h /usr/include/endian.h
src/Cube.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/Cube.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/Cube.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/Cube.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/Cube.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/Cube.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/Cube.o: /usr/include/string.h /usr/include/xlocale.h
src/Cube.o: /usr/include/strings.h /usr/include/ctype.h /usr/include/iconv.h
src/Cube.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/Cube.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/Cube.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/Cube.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/Cube.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/Cube.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/Cube.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/Cube.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/Cube.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/Cube.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/Cube.o: /usr/include/SDL/SDL_version.h src/IObject.hpp src/VectorCalc.hpp
src/Cube.o: src/World.hpp src/Terrain.hpp src/HMapReader.hpp src/Particle.hpp
src/Cube.o: src/sphere.hpp /usr/include/GL/glu.h
src/HMapReader.o: /usr/include/stdlib.h /usr/include/features.h
src/HMapReader.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/HMapReader.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/HMapReader.o: /usr/include/bits/waitflags.h
src/HMapReader.o: /usr/include/bits/waitstatus.h /usr/include/endian.h
src/HMapReader.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/HMapReader.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/HMapReader.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/HMapReader.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/HMapReader.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/HMapReader.o: /usr/include/sys/sysmacros.h
src/HMapReader.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/HMapReader.o: src/HMapReader.hpp /usr/include/SDL/SDL.h
src/HMapReader.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/HMapReader.o: /usr/include/SDL/SDL_config.h
src/HMapReader.o: /usr/include/SDL/SDL_platform.h /usr/include/stdio.h
src/HMapReader.o: /usr/include/libio.h /usr/include/_G_config.h
src/HMapReader.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/HMapReader.o: /usr/include/bits/sys_errlist.h /usr/include/string.h
src/HMapReader.o: /usr/include/xlocale.h /usr/include/strings.h
src/HMapReader.o: /usr/include/inttypes.h /usr/include/stdint.h
src/HMapReader.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/HMapReader.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/HMapReader.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/HMapReader.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/HMapReader.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/HMapReader.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/HMapReader.o: /usr/include/SDL/SDL_cpuinfo.h
src/HMapReader.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/HMapReader.o: /usr/include/SDL/SDL_keyboard.h
src/HMapReader.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/HMapReader.o: /usr/include/SDL/SDL_video.h
src/HMapReader.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/HMapReader.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/HMapReader.o: /usr/include/SDL/SDL_version.h
src/LuaFuncs.o: /usr/include/stdlib.h /usr/include/features.h
src/LuaFuncs.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/LuaFuncs.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/LuaFuncs.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/LuaFuncs.o: /usr/include/endian.h /usr/include/bits/endian.h
src/LuaFuncs.o: /usr/include/bits/byteswap.h /usr/include/sys/types.h
src/LuaFuncs.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/LuaFuncs.o: /usr/include/time.h /usr/include/sys/select.h
src/LuaFuncs.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/LuaFuncs.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/LuaFuncs.o: /usr/include/bits/pthreadtypes.h /usr/include/alloca.h
src/LuaFuncs.o: /usr/include/lua.hpp /usr/include/lua.h
src/LuaFuncs.o: /usr/include/luaconf.h /usr/include/limits.h
src/LuaFuncs.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
src/LuaFuncs.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
src/LuaFuncs.o: /usr/include/lualib.h /usr/include/lauxlib.h
src/LuaFuncs.o: /usr/include/stdio.h /usr/include/libio.h
src/LuaFuncs.o: /usr/include/_G_config.h /usr/include/wchar.h
src/LuaFuncs.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/LuaFuncs.o: src/LuaFuncs.h src/main.h
src/main.o: /usr/include/unistd.h /usr/include/features.h
src/main.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/main.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/main.o: /usr/include/bits/posix_opt.h /usr/include/bits/environments.h
src/main.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/main.o: /usr/include/bits/confname.h /usr/include/getopt.h
src/main.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/main.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/main.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/main.o: /usr/include/time.h /usr/include/endian.h
src/main.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/main.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/main.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/main.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/main.o: /usr/include/stdio.h /usr/include/libio.h
src/main.o: /usr/include/_G_config.h /usr/include/wchar.h
src/main.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/main.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/main.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/main.o: /usr/include/string.h /usr/include/xlocale.h
src/main.o: /usr/include/strings.h /usr/include/inttypes.h
src/main.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/main.o: /usr/include/ctype.h /usr/include/iconv.h
src/main.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/main.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/main.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/main.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/main.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/main.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/main.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/main.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/main.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/main.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/main.o: /usr/include/SDL/SDL_version.h /usr/include/GL/gl.h
src/main.o: /usr/include/GL/glext.h /usr/include/lua.hpp /usr/include/lua.h
src/main.o: /usr/include/luaconf.h /usr/include/limits.h
src/main.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
src/main.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
src/main.o: /usr/include/lualib.h /usr/include/lauxlib.h src/main.h
src/main.o: src/LuaFuncs.h src/Terrain.hpp src/HMapReader.hpp src/Object.hpp
src/main.o: src/IObject.hpp src/Cube.hpp src/Particle.hpp src/OpenGL.h
src/main.o: /usr/include/GL/glu.h src/World.hpp src/sphere.hpp
src/Object.o: src/Object.hpp /usr/include/lua.hpp /usr/include/lua.h
src/Object.o: /usr/include/luaconf.h /usr/include/limits.h
src/Object.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/Object.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/Object.o: /usr/include/gnu/stubs-64.h /usr/include/bits/posix1_lim.h
src/Object.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/Object.o: /usr/include/bits/posix2_lim.h /usr/include/lualib.h
src/Object.o: /usr/include/lauxlib.h /usr/include/stdio.h
src/Object.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/Object.o: /usr/include/libio.h /usr/include/_G_config.h
src/Object.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/Object.o: /usr/include/bits/sys_errlist.h /usr/include/GL/gl.h
src/Object.o: /usr/include/GL/glext.h /usr/include/inttypes.h
src/Object.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/Object.o: /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/Object.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/Object.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/Object.o: /usr/include/time.h /usr/include/endian.h
src/Object.o: /usr/include/bits/endian.h /usr/include/bits/byteswap.h
src/Object.o: /usr/include/sys/select.h /usr/include/bits/select.h
src/Object.o: /usr/include/bits/sigset.h /usr/include/bits/time.h
src/Object.o: /usr/include/sys/sysmacros.h /usr/include/bits/pthreadtypes.h
src/Object.o: /usr/include/stdlib.h /usr/include/bits/waitflags.h
src/Object.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/Object.o: /usr/include/string.h /usr/include/xlocale.h
src/Object.o: /usr/include/strings.h /usr/include/ctype.h
src/Object.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/Object.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/Object.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/Object.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/Object.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/Object.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/Object.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/Object.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/Object.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/Object.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/Object.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/Object.o: src/IObject.hpp src/World.hpp src/Terrain.hpp
src/Object.o: src/HMapReader.hpp src/Cube.hpp src/Particle.hpp src/sphere.hpp
src/Object.o: /usr/include/GL/glu.h
src/OpenGL.o: src/OpenGL.h /usr/include/GL/gl.h /usr/include/GL/glext.h
src/OpenGL.o: /usr/include/inttypes.h /usr/include/features.h
src/OpenGL.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/OpenGL.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/OpenGL.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/OpenGL.o: /usr/include/GL/glu.h /usr/include/SDL/SDL.h
src/OpenGL.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/OpenGL.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/OpenGL.o: /usr/include/sys/types.h /usr/include/bits/types.h
src/OpenGL.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/OpenGL.o: /usr/include/endian.h /usr/include/bits/endian.h
src/OpenGL.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/OpenGL.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/OpenGL.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/OpenGL.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/OpenGL.o: /usr/include/libio.h /usr/include/_G_config.h
src/OpenGL.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/OpenGL.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/OpenGL.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/OpenGL.o: /usr/include/alloca.h /usr/include/string.h
src/OpenGL.o: /usr/include/xlocale.h /usr/include/strings.h
src/OpenGL.o: /usr/include/ctype.h /usr/include/iconv.h
src/OpenGL.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/OpenGL.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/OpenGL.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/OpenGL.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/OpenGL.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/OpenGL.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/OpenGL.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/OpenGL.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/OpenGL.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/OpenGL.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/OpenGL.o: /usr/include/SDL/SDL_version.h
src/Particle.o: src/Particle.hpp src/Object.hpp /usr/include/lua.hpp
src/Particle.o: /usr/include/lua.h /usr/include/luaconf.h
src/Particle.o: /usr/include/limits.h /usr/include/features.h
src/Particle.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/Particle.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/Particle.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
src/Particle.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
src/Particle.o: /usr/include/lualib.h /usr/include/lauxlib.h
src/Particle.o: /usr/include/stdio.h /usr/include/bits/types.h
src/Particle.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/Particle.o: /usr/include/_G_config.h /usr/include/wchar.h
src/Particle.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/Particle.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
src/Particle.o: /usr/include/inttypes.h /usr/include/stdint.h
src/Particle.o: /usr/include/bits/wchar.h /usr/include/SDL/SDL.h
src/Particle.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/Particle.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/Particle.o: /usr/include/sys/types.h /usr/include/time.h
src/Particle.o: /usr/include/endian.h /usr/include/bits/endian.h
src/Particle.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/Particle.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/Particle.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/Particle.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
src/Particle.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/Particle.o: /usr/include/alloca.h /usr/include/string.h
src/Particle.o: /usr/include/xlocale.h /usr/include/strings.h
src/Particle.o: /usr/include/ctype.h /usr/include/iconv.h
src/Particle.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/Particle.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/Particle.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/Particle.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/Particle.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/Particle.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/Particle.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/Particle.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/Particle.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/Particle.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/Particle.o: /usr/include/SDL/SDL_version.h src/IObject.hpp src/World.hpp
src/Particle.o: src/Terrain.hpp src/HMapReader.hpp src/Cube.hpp
src/Particle.o: src/sphere.hpp /usr/include/GL/glu.h src/OpenGL.h
src/sphere.o: src/sphere.hpp /usr/include/GL/gl.h /usr/include/GL/glext.h
src/sphere.o: /usr/include/inttypes.h /usr/include/features.h
src/sphere.o: /usr/include/sys/cdefs.h /usr/include/bits/wordsize.h
src/sphere.o: /usr/include/gnu/stubs.h /usr/include/gnu/stubs-64.h
src/sphere.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/sphere.o: /usr/include/GL/glu.h /usr/include/lua.hpp /usr/include/lua.h
src/sphere.o: /usr/include/luaconf.h /usr/include/limits.h
src/sphere.o: /usr/include/bits/posix1_lim.h /usr/include/bits/local_lim.h
src/sphere.o: /usr/include/linux/limits.h /usr/include/bits/posix2_lim.h
src/sphere.o: /usr/include/lualib.h /usr/include/lauxlib.h
src/sphere.o: /usr/include/stdio.h /usr/include/bits/types.h
src/sphere.o: /usr/include/bits/typesizes.h /usr/include/libio.h
src/sphere.o: /usr/include/_G_config.h /usr/include/wchar.h
src/sphere.o: /usr/include/bits/stdio_lim.h /usr/include/bits/sys_errlist.h
src/sphere.o: src/Object.hpp /usr/include/SDL/SDL.h
src/sphere.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/sphere.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/sphere.o: /usr/include/sys/types.h /usr/include/time.h
src/sphere.o: /usr/include/endian.h /usr/include/bits/endian.h
src/sphere.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/sphere.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/sphere.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/sphere.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
src/sphere.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/sphere.o: /usr/include/alloca.h /usr/include/string.h
src/sphere.o: /usr/include/xlocale.h /usr/include/strings.h
src/sphere.o: /usr/include/ctype.h /usr/include/iconv.h
src/sphere.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/sphere.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/sphere.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/sphere.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/sphere.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/sphere.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/sphere.o: /usr/include/SDL/SDL_keyboard.h /usr/include/SDL/SDL_keysym.h
src/sphere.o: /usr/include/SDL/SDL_mouse.h /usr/include/SDL/SDL_video.h
src/sphere.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/sphere.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/sphere.o: /usr/include/SDL/SDL_version.h src/IObject.hpp
src/sphere.o: src/VectorCalc.hpp src/World.hpp src/Terrain.hpp
src/sphere.o: src/HMapReader.hpp src/Cube.hpp src/Particle.hpp
src/Terrain.o: src/Terrain.hpp /usr/include/lua.hpp /usr/include/lua.h
src/Terrain.o: /usr/include/luaconf.h /usr/include/limits.h
src/Terrain.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/Terrain.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/Terrain.o: /usr/include/gnu/stubs-64.h /usr/include/bits/posix1_lim.h
src/Terrain.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/Terrain.o: /usr/include/bits/posix2_lim.h /usr/include/lualib.h
src/Terrain.o: /usr/include/lauxlib.h /usr/include/stdio.h
src/Terrain.o: /usr/include/bits/types.h /usr/include/bits/typesizes.h
src/Terrain.o: /usr/include/libio.h /usr/include/_G_config.h
src/Terrain.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/Terrain.o: /usr/include/bits/sys_errlist.h /usr/include/SDL/SDL.h
src/Terrain.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/Terrain.o: /usr/include/SDL/SDL_config.h /usr/include/SDL/SDL_platform.h
src/Terrain.o: /usr/include/sys/types.h /usr/include/time.h
src/Terrain.o: /usr/include/endian.h /usr/include/bits/endian.h
src/Terrain.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/Terrain.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/Terrain.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/Terrain.o: /usr/include/bits/pthreadtypes.h /usr/include/stdlib.h
src/Terrain.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/Terrain.o: /usr/include/alloca.h /usr/include/string.h
src/Terrain.o: /usr/include/xlocale.h /usr/include/strings.h
src/Terrain.o: /usr/include/inttypes.h /usr/include/stdint.h
src/Terrain.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/Terrain.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/Terrain.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/Terrain.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/Terrain.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/Terrain.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/Terrain.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/Terrain.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/Terrain.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/Terrain.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/Terrain.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/Terrain.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/Terrain.o: /usr/include/GL/gl.h /usr/include/GL/glext.h
src/Terrain.o: src/HMapReader.hpp src/Object.hpp src/IObject.hpp src/Cube.hpp
src/Terrain.o: src/Particle.hpp /usr/include/math.h
src/Terrain.o: /usr/include/bits/huge_val.h /usr/include/bits/huge_valf.h
src/Terrain.o: /usr/include/bits/huge_vall.h /usr/include/bits/inf.h
src/Terrain.o: /usr/include/bits/nan.h /usr/include/bits/mathdef.h
src/Terrain.o: /usr/include/bits/mathcalls.h src/LuaFuncs.h src/main.h
src/Terrain.o: src/OpenGL.h /usr/include/GL/glu.h src/VectorCalc.hpp
src/Terrain.o: src/World.hpp src/sphere.hpp
src/VectorCalc.o: src/VectorCalc.hpp src/World.hpp /usr/include/SDL/SDL.h
src/VectorCalc.o: /usr/include/SDL/SDL_main.h /usr/include/SDL/SDL_stdinc.h
src/VectorCalc.o: /usr/include/SDL/SDL_config.h
src/VectorCalc.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/VectorCalc.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/VectorCalc.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/VectorCalc.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
src/VectorCalc.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/VectorCalc.o: /usr/include/endian.h /usr/include/bits/endian.h
src/VectorCalc.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/VectorCalc.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/VectorCalc.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/VectorCalc.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/VectorCalc.o: /usr/include/libio.h /usr/include/_G_config.h
src/VectorCalc.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/VectorCalc.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/VectorCalc.o: /usr/include/bits/waitflags.h
src/VectorCalc.o: /usr/include/bits/waitstatus.h /usr/include/alloca.h
src/VectorCalc.o: /usr/include/string.h /usr/include/xlocale.h
src/VectorCalc.o: /usr/include/strings.h /usr/include/inttypes.h
src/VectorCalc.o: /usr/include/stdint.h /usr/include/bits/wchar.h
src/VectorCalc.o: /usr/include/ctype.h /usr/include/iconv.h
src/VectorCalc.o: /usr/include/SDL/begin_code.h /usr/include/SDL/close_code.h
src/VectorCalc.o: /usr/include/SDL/SDL_audio.h /usr/include/SDL/SDL_error.h
src/VectorCalc.o: /usr/include/SDL/SDL_endian.h /usr/include/SDL/SDL_mutex.h
src/VectorCalc.o: /usr/include/SDL/SDL_thread.h /usr/include/SDL/SDL_rwops.h
src/VectorCalc.o: /usr/include/SDL/SDL_cdrom.h /usr/include/SDL/SDL_cpuinfo.h
src/VectorCalc.o: /usr/include/SDL/SDL_events.h /usr/include/SDL/SDL_active.h
src/VectorCalc.o: /usr/include/SDL/SDL_keyboard.h
src/VectorCalc.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/VectorCalc.o: /usr/include/SDL/SDL_video.h
src/VectorCalc.o: /usr/include/SDL/SDL_joystick.h /usr/include/SDL/SDL_quit.h
src/VectorCalc.o: /usr/include/SDL/SDL_loadso.h /usr/include/SDL/SDL_timer.h
src/VectorCalc.o: /usr/include/SDL/SDL_version.h /usr/include/lua.hpp
src/VectorCalc.o: /usr/include/lua.h /usr/include/luaconf.h
src/VectorCalc.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
src/VectorCalc.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/VectorCalc.o: /usr/include/bits/posix2_lim.h /usr/include/lualib.h
src/VectorCalc.o: /usr/include/lauxlib.h /usr/include/GL/gl.h
src/VectorCalc.o: /usr/include/GL/glext.h src/Terrain.hpp src/HMapReader.hpp
src/VectorCalc.o: src/Object.hpp src/IObject.hpp src/Cube.hpp
src/VectorCalc.o: src/Particle.hpp src/sphere.hpp /usr/include/GL/glu.h
src/world.o: src/World.hpp /usr/include/SDL/SDL.h /usr/include/SDL/SDL_main.h
src/world.o: /usr/include/SDL/SDL_stdinc.h /usr/include/SDL/SDL_config.h
src/world.o: /usr/include/SDL/SDL_platform.h /usr/include/sys/types.h
src/world.o: /usr/include/features.h /usr/include/sys/cdefs.h
src/world.o: /usr/include/bits/wordsize.h /usr/include/gnu/stubs.h
src/world.o: /usr/include/gnu/stubs-64.h /usr/include/bits/types.h
src/world.o: /usr/include/bits/typesizes.h /usr/include/time.h
src/world.o: /usr/include/endian.h /usr/include/bits/endian.h
src/world.o: /usr/include/bits/byteswap.h /usr/include/sys/select.h
src/world.o: /usr/include/bits/select.h /usr/include/bits/sigset.h
src/world.o: /usr/include/bits/time.h /usr/include/sys/sysmacros.h
src/world.o: /usr/include/bits/pthreadtypes.h /usr/include/stdio.h
src/world.o: /usr/include/libio.h /usr/include/_G_config.h
src/world.o: /usr/include/wchar.h /usr/include/bits/stdio_lim.h
src/world.o: /usr/include/bits/sys_errlist.h /usr/include/stdlib.h
src/world.o: /usr/include/bits/waitflags.h /usr/include/bits/waitstatus.h
src/world.o: /usr/include/alloca.h /usr/include/string.h
src/world.o: /usr/include/xlocale.h /usr/include/strings.h
src/world.o: /usr/include/inttypes.h /usr/include/stdint.h
src/world.o: /usr/include/bits/wchar.h /usr/include/ctype.h
src/world.o: /usr/include/iconv.h /usr/include/SDL/begin_code.h
src/world.o: /usr/include/SDL/close_code.h /usr/include/SDL/SDL_audio.h
src/world.o: /usr/include/SDL/SDL_error.h /usr/include/SDL/SDL_endian.h
src/world.o: /usr/include/SDL/SDL_mutex.h /usr/include/SDL/SDL_thread.h
src/world.o: /usr/include/SDL/SDL_rwops.h /usr/include/SDL/SDL_cdrom.h
src/world.o: /usr/include/SDL/SDL_cpuinfo.h /usr/include/SDL/SDL_events.h
src/world.o: /usr/include/SDL/SDL_active.h /usr/include/SDL/SDL_keyboard.h
src/world.o: /usr/include/SDL/SDL_keysym.h /usr/include/SDL/SDL_mouse.h
src/world.o: /usr/include/SDL/SDL_video.h /usr/include/SDL/SDL_joystick.h
src/world.o: /usr/include/SDL/SDL_quit.h /usr/include/SDL/SDL_loadso.h
src/world.o: /usr/include/SDL/SDL_timer.h /usr/include/SDL/SDL_version.h
src/world.o: /usr/include/lua.hpp /usr/include/lua.h /usr/include/luaconf.h
src/world.o: /usr/include/limits.h /usr/include/bits/posix1_lim.h
src/world.o: /usr/include/bits/local_lim.h /usr/include/linux/limits.h
src/world.o: /usr/include/bits/posix2_lim.h /usr/include/lualib.h
src/world.o: /usr/include/lauxlib.h /usr/include/GL/gl.h
src/world.o: /usr/include/GL/glext.h src/Terrain.hpp src/HMapReader.hpp
src/world.o: src/Object.hpp src/IObject.hpp src/Cube.hpp src/Particle.hpp
src/world.o: src/sphere.hpp /usr/include/GL/glu.h src/LuaFuncs.h src/main.h
src/world.o: src/OpenGL.h src/VectorCalc.hpp
