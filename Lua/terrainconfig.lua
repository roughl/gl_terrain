-- Howdy! This sure is a comment!

map ="Data/Map6.bmp"
--map ="Data/Map5.bmp"
--map ="Data/Map4.bmp"
--map ="Data/Map2.bmp"
--map ="Data/Map3.bmp"
--map ="Data/TestGrey.bmp"
--map ="Data/heightmap.raw"
map ="Data/test_alpha.bmp"

--map ="Data/LoadingScreen.bmp" -- don't do this, cause my prog has no error handling ;)

zspeed=0.1
xspeed=0.1
gravity=0.0005    -- yspeed-=gravity*milliseconds when in air; default 0.0005
jumpvelocity=0.10 -- yspeed=jumpvelocity when jumping; default 0.15
maxheight=3.0     -- limit for "climbing"; default 3.0
turnspeed=0.1 -- if you like to look up and down with PgUP / PgDOWN
mousespeed=1.0 

waterlevel =1.9

maxFontains=10







if (maxFontains<0) then
	print("Warning! maxFontains<0")
	print("Changing maxFontains to 0")
	maxFontains=0
end
