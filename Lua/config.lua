-- Howdy! This sure is a comment!


io.write("start config.lua\n")


width = 1024
height = 768
fullscreen=0
--FPS=30 --not used yet
error = 0

TerrainFilename="Lua/Terrain1.lua"


--delay=1000/FPS -- delay in ms calculated from Frames per sec


if ( (fullscreen~=0) and (fullscreen ~=1) )then

   fullscreen = 1
   error = 3
	
end


io.write("Breite: " .. width .. "\tHöhe: " .. height .. "\tFullscreen: " .. fullscreen .. "\t Error: " .. error .. "\n")

io.write("end config.lua\n")
