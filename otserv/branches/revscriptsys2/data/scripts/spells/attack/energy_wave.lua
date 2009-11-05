
local energyWave = Spell:new("Energy Wave")

energyWave.words       = "exevo mort hur"
energyWave.vocation    = "sorcerer"
energyWave.damageType  = COMBAT_ENERGYDAMAGE
energyWave.level       = 38
energyWave.magicLevel  = 40
energyWave.mana        = 170
energyWave.aggressive  = true
energyWave.areaEffect  = MAGIC_EFFECT_ENERGY_AREA

energyWave.area        =
	{
		{" ", " ", " ", "n", "n", "n", " ", " ", " "},
		{" ", " ", " ", "n", "n", "n", " ", " ", " "},
		{" ", " ", " ", "n", "n", "n", " ", " ", " "},
		{"w", "w", "w", " ", "n", " ", "e", "e", "e"},
		{"w", "w", "w", "w", " ", "e", "e", "e", "e"},
		{"w", "w", "w", " ", "s", " ", "e", "e", "e"},
		{" ", " ", " ", "s", "s", "s", " ", " ", " "},
		{" ", " ", " ", "s", "s", "s", " ", " ", " "},
		{" ", " ", " ", "s", "s", "s", " ", " ", " "},
	}
	

--[[
energyWave.area        = {
		{"[ne][sw]", "        ", "[e][w]", "        ", "[nw][se]"},
		{"        ", "[ne][sw]", "[e][w]", "[nw][se]", "        "},
		{"[s][n]  ", "[s][n]  ","  [a]  ", "[s][n]  ", "[s][n]  "},
		{"        ", "[nw][se]", "[e][w]", "[ne][sw]", "        "},
		{"[nw][se]", "        ", "[e][w]", "        ", "[ne][sw]"}
	}
]]--

energyWave.onHitCreature =
	function(creature)
		print(energyWave.name .. " - onHitCreature: " .. creature:getName() )
	end

energyWave.onHitTile =
	function(tile)
		local field = createItem(1491)
		tile:addItem(field)
		--print("onHitTile")
	end
	
energyWave.formula = 
	function(player)
		return -math.random(player:getLevel()/5 + player:getMagicLevel() * 4.5,
						   player:getLevel()/5 + player:getMagicLevel() * 9)
	end

energyWave:register()
