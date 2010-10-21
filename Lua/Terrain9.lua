-- Howdy! This sure is a comment!

map ="Data/Map9.bmp"

zspeed= 0.05
xspeed= 0.05
gravity= 0.0001    -- yspeed-=gravity*milliseconds when in air; default 0.0005
jumpvelocity= 0.10 -- yspeed=jumpvelocity when jumping; default 0.10
maxheight= 0.2     -- limit for "climbing"; default 3.0
turnspeed= 0.1     -- if you like to look up and down with PgUP / PgDOWN
mousespeed= 1.0 

waterlevel =1.5

maxFontains= 15











-- Do not change this, if you do, the engine may crash!
if (maxFontains<0) then
	print("Warning! maxFontains<0")
	print("Changing maxFontains to 0")
	maxFontains=0
end
