#include "DrunkardOwnedStates.h"
#include "Drunkard.h"
#include "Locations.h"
#include "messaging/Telegram.h"
#include "MessageDispatcher.h"
#include "MessageTypes.h"
#include "Time/CrudeTimer.h"
#include "EntityNames.h"
#include "EntityManager.h"
#include "Miner.h"

#include <iostream>

using std::cout;

#ifdef TEXTOUTPUT
#include <fstream>
extern std::ofstream os;
#define cout os
#endif

//-------------------------------------------------------------------------SayNumberOfDrinks

SayNumberOfDrinks* SayNumberOfDrinks::Instance()
{
  static SayNumberOfDrinks instance;
  return &instance;
}


void SayNumberOfDrinks::Enter(Drunkard* drunkard)
{
  cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Mmmhhh... Ha many drinks?";
}


void SayNumberOfDrinks::Execute(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": So far, " << drunkard->getNbDrinks()
		<< " beers mate! See that? Yiiiiiha!";

	if (EntityManager::Instance()->GetEntityFromID(ent_Miner_Bob) != NULL &&
		((Miner*)EntityManager::Instance()->GetEntityFromID(ent_Miner_Bob))->Location() == saloon)
	{
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY,
									drunkard->ID(),
									ent_Miner_Bob,
									Msg_Tease,
									NO_ADDITIONAL_INFO);
	}

	drunkard->GetFSM()->ChangeState(Drink::Instance());
}

void SayNumberOfDrinks::Exit(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I should stop now... Or not!";
}

bool SayNumberOfDrinks::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
  return false;
}

//-------------------------------------------------------------------------WarmingUp

WarmingUp* WarmingUp::Instance()
{
	static WarmingUp instance;
	return &instance;
}

void WarmingUp::Enter(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I'm happy today! What about a beer?";
}

void WarmingUp::Execute(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I'm cool, chilling alone with my beer :-)";
	drunkard->drinkOneMore();
	if (drunkard->isWarmedUp())
	{
		drunkard->GetFSM()->ChangeState(Drink::Instance());
	}
}

void WarmingUp::Exit(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I'm all warmed up now!";
}

bool WarmingUp::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Hello :-) !";
	return true;
}


//-------------------------------------------------------------------------Drink

Drink* Drink::Instance()
{
	static Drink instance;
	return &instance;
}

void Drink::Enter(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Ay ay, am gonna drink ma beer!";
}

void Drink::Execute(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Glug-glug-glug...";

	drunkard->drinkOneMore();

	if (RandFloat() < 0.2)
		return;

	drunkard->GetFSM()->ChangeState(SayNumberOfDrinks::Instance());
}

void Drink::Exit(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Aaaaahhhhh! Luv ma beer!";
}

bool Drink::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
	switch (msg.Msg)
	{
	case Msg_Punch:
		drunkard->GetFSM()->ChangeState(KnockedOut::Instance());
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------KnockedOut

KnockedOut* KnockedOut::Instance()
{
	static KnockedOut instance;
	return &instance;
}

void KnockedOut::Enter(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Ooooh I'm faillin...";
}

void KnockedOut::Execute(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": Argh...";
}

void KnockedOut::Exit(Drunkard* drunkard)
{
	cout << "\n" << GetNameOfEntity(drunkard->ID()) << ": I'm feelin better!";
}

bool KnockedOut::OnMessage(Drunkard* drunkard, const Telegram& msg)
{
	return false;
}
