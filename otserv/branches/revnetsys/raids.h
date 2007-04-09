//////////////////////////////////////////////////////////////////////
// 
//////////////////////////////////////////////////////////////////////
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
//////////////////////////////////////////////////////////////////////
#ifndef __OTSERV_RAIDS_H__
#define __OTSERV_RAIDS_H__

#include <string>
#include <vector>
#include <list>

#include "definitions.h"
#include "const79.h"
#include "position.h"

enum RaidState_t{
	RAIDSTATE_IDLE = 0,
	RAIDSTATE_EXECUTING
};

struct MonsterSpawn{
	std::string name;
	uint32_t minAmount;
	uint32_t maxAmount;
};

//How many times it will try to find a tile to add the monster to before giving up
#define MAXIMUM_TRIES_PER_MONSTER 10

class Raid;
class RaidEvent;

typedef std::list<Raid*> RaidList;
typedef std::vector<RaidEvent*> RaidEventVector;
typedef std::list<MonsterSpawn*> MonsterSpawnList;

class Raids{
private:
	Raids();
public:
	static Raids* getInstance(){
		static Raids instance;
		return &instance;
	}
	
	~Raids();
	
	bool loadFromXml(const std::string& _filename);
	void startup();
	
	void clear();
	void reload();
	
	bool isLoaded() { return loaded; }
	bool isStarted() { return started; }
	
	Raid* getRunning() { return running; }
	void setRunning(Raid* newRunning) { running = newRunning; }
	
	Raid* getRaidByName(const std::string& name);
	
	uint64_t getLastRaidEnd() { return lastRaidEnd; }
	void setLastRaidEnd(uint64_t newLastRaidEnd) { lastRaidEnd = newLastRaidEnd; }
	
private:
	RaidList raidList;
	bool loaded, started;
	Raid* running;
	uint64_t lastRaidEnd;
	std::string filename;
};

class Raid{
public:
	Raid(const std::string& _name, uint32_t _chance, uint32_t _interval, uint32_t _marginTime);
	~Raid();
	
	bool loadFromXml(const std::string& _filename);
	
	void checkRaid();
	void executeRaidEvent(RaidEvent* raidEvent);
	void resetRaid();
	
	RaidEvent* getNextRaidEvent();
	void setState(RaidState_t newState) { state = newState; }
	std::string getName() const { return name; }
	
	void addEvent(RaidEvent* event);
	
	bool isLoaded() { return loaded; }
	uint64_t getMargin() { return margin; }
	uint32_t getInterval() {return interval;}
	
	void stopEvents();
	void setRaidCheckEvent(uint32_t eventId) { checkRaidEvent = eventId; }
	
private:
	RaidEventVector raidEvents;
	std::string name;
	uint32_t interval, chance;
	uint32_t nextEvent;
	uint64_t margin;
	RaidState_t state;
	uint32_t checkRaidEvent, nextEventEvent;
	bool loaded;
};

class RaidEvent{
public:
	RaidEvent(uint32_t _delay);
	virtual ~RaidEvent() {};
	
	virtual bool executeEvent() {return false;};
	uint32_t getDelay() const { return delay;}
	void setDelay(uint32_t newDelay) { delay = newDelay; }
	
private:
	uint32_t delay;
};

class AnnounceEvent : public RaidEvent{
public:
	AnnounceEvent(const std::string& _message, MessageClasses _messageType, uint32_t _delay);
	virtual ~AnnounceEvent() {};
	
	virtual bool executeEvent();

private:
	std::string message;
	MessageClasses messageType;
};

class SingleSpawnEvent : public RaidEvent{
public:
	SingleSpawnEvent(const std::string& _monsterName, const Position& pos, uint32_t _delay);
	virtual ~SingleSpawnEvent() {};
	
	virtual bool executeEvent();

private:
	std::string monsterName;
	Position position;
};

class AreaSpawnEvent : public RaidEvent{
public:
	AreaSpawnEvent(const Position& fromPos, const Position& toPos, uint32_t _delay);
	virtual ~AreaSpawnEvent();
	
	void addMonster(MonsterSpawn* monsterSpawn);
	void addMonster(const std::string& monsterName, uint32_t minAmount, uint32_t maxAmount);
	
	virtual bool executeEvent();

private:
	MonsterSpawnList spawnList;
	Position fromPos, toPos;
};

/*
//Not yet implemented...
class CustomEvent : public RaidEvent{
public:
	CustomEvent(const std::string& _scriptFile, uint32_t _delay);
	~CustomEvent();
	
	bool executeEvent();

private:
	std::string scriptFile;
}*/

#endif