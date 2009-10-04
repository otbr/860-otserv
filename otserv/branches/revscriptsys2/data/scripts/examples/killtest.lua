KillTest = {}

function KillTest.simpleKillHandler(event)
	if typeof(event.killer, "Player") then
		event.killer:sendNote("You killed " .. event.creature:getName() .. ".")
		
		local listener = ""
		
		local function KillAgain(evt)
			evt.killer:sendNote("You killed again!")
			stopListener(listener)
		end
		
		listener = registerOnCreatureKill(event.killer, "all", KillAgain)
	end
end
KillTest.simpleKillListener = registerOnKill("all", KillTest.simpleKillHandler)


KillTest.watchList = {}

function KillTest.ratDeathHandler(event)
	sendAnimatedText(event.creature:getPosition(), 215, "Block")
	
	local function KillerKilled(evt)
		sendAnimatedText(event.creature:getPosition(), 215, "Haha")
	end
	
	local function KillerKillsSomething(evt)
		local tag = createItem(2599)
		tag:setSpecialDescription("You tried to kill a " .. event.creature:getName() .. " before!")
		evt.corpse:addItem(tag)
	end
	
	if not table.find(KillTest.watchList, event.killer) then
		registerOnCreatureKilled(event.killer, "all", KillerKilled)
		registerOnCreatureDeathBy(event.killer, "all", KillerKillsSomething)
		table.append(KillTest.watchList, event.killer)
	end
	
	event:skip()
end

registerOnKilled("rat", "name", KillTest.ratDeathHandler)

function KillTest.playerKillHandler(event)
	local tag = createItem(2599)
	tag:setSpecialDescription("Killed by " .. event.killer:getName() .. ".")
	event.corpse:addItem(tag)
end

KillTest.playerKillListener = registerOnDeathBy("killer_player", KillTest.playerKillHandler)

--[[
registerOnDeath([string what = nil], string method, function callback)
registerOnCreatureDeath(Creature creature [, string what = nil], string method, function callback)
]]--
