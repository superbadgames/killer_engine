/*--------------------------------------------------------------------
The holder and controller of the the world objects. This will act as 
both a singleton and a state maching controller, where each world will
be a state that can be set to active. 

For now, all of the states that are to be used will be instantiated 
during the initialization in the main loop, however later, each level
will only be created once it is called, as part of a loading screen.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
---------------------------------------------------------------------*/

#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

//Killer1 includes
#include <Atom.h>
#include <World.h>

//3rd party includes
#include <string>
#include <map>

class WorldManager{
	//Members
	std::map<std::string, World*>		  _worlds;
	World* 								  _activeWorld;
	string 						  _activeWorldID;
	static WorldManager* 				  _instance;

public:
	~WorldManager(void) {}

	static WorldManager* Instance();

	bool 		AddWorld(string worldID, World* world);
	bool 		RemoveWorld(string worldID);
	bool 		SetActiveWorld(string worldID);
	std::string GetActiveWorldID(void) { return _activeWorldID; }

	void Update(void);
	void Render(void);

protected:
	WorldManager(void) {  }

};


#endif