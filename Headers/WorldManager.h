/*========================================================================
The holder and controller of the the world objects. This will act as 
both a singleton and a state maching controller, where each world will
be a state that can be set to active. 

For now, all of the states that are to be used will be instantiated 
during the initialization in the main loop, however later, each level
will only be created once it is called, as part of a loading screen.

This is not free to use, and cannot be used without the express permission
of KillerWave.

Written by Maxwell Miller
========================================================================*/

#ifndef WORLD_MANAGER_H
#define WORLD_MANAGER_H

//Killer1 includes
#include <Atom.h>
#include <World.h>

//3rd party includes
#include <map>

class WorldManager{
private:
	std::map<text, World*>		      _worlds;
	World* 							  _activeWorld;
	text 						  	  _activeWorldID;
	static WorldManager* 			  _instance;

public:
	~WorldManager(void) {  }

	static WorldManager* Instance();

	bool   AddWorld		   (text worldID, World* world);
	bool   RemoveWorld     (text worldID);
	bool   SetActiveWorld  (text worldID);
	text GetActiveWorldID(void) { return _activeWorldID; }

	void Update(void);
	void Render(void);

protected:
	WorldManager(void) {  }

};


#endif