#ifndef __DRUNKARD__
#define __DRUNKARD__

#include "BaseGameEntity.h"
#include "fsm/StateMachine.h"
#include "Locations.h"

#include <string>

#include "fsm/State.h"
#include "misc/ConsoleUtils.h"
#include "misc/Utils.h"

#include "DrunkardOwnedStates.h"

class BaseGameEntity;

// ----------------------------------------------
//					buveur de base
// toujours au bar
// annonce aléatoirement son numéro de verre
//		ensuite perçu comme une provocation par le mineur
// sinon, il boit
// ----------------------------------------------

static const float ProbabilityOfSpeaking = 0.7f;

static const int WarmingUpThreshold = 2;

class Drunkard : public BaseGameEntity
{
private:

	int m_nbDrinks;
	location_type m_location;
	StateMachine<Drunkard>*  m_pStateMachine;

public:
	
	Drunkard(int id):m_location(saloon), m_nbDrinks(0), BaseGameEntity(id)
	{
		m_pStateMachine = new StateMachine<Drunkard>(this);
		m_pStateMachine->SetCurrentState(WarmingUp::Instance());
	}

	~Drunkard(){delete m_pStateMachine;}
	void Update();
	virtual bool HandleMessage(const Telegram& msg);
	StateMachine<Drunkard>* GetFSM()const{return m_pStateMachine;}
	void drinkOneMore();

	// --------------------------------------------- accessors
	int getNbDrinks(){return m_nbDrinks;}
	location_type getLocation(){return m_location;}
	void setLocation(location_type loc){m_location = loc;}
	bool isWarmedUp(){return m_nbDrinks > WarmingUpThreshold;}

};

#endif // __DRUNKARD__