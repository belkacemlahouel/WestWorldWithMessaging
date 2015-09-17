#ifndef DRUNKARD_OWNED_STATES_H
#define DRUNKARD_OWNED_STATES_H

#include "fsm/State.h"

class Drunkard;

// ----------------

/* class DrunkardsGlobalState : public State<Drunkard>
{  
private:
  
  DrunkardsGlobalState(){}
  DrunkardsGlobalState(const DrunkardsGlobalState&);
  DrunkardsGlobalState& operator=(const DrunkardsGlobalState&);
 
public:

  static DrunkardsGlobalState* Instance();
  virtual void Enter(Drunkard* drunkard){}
  virtual void Execute(Drunkard* drunkard);
  virtual void Exit(Drunkard* drunkard){}
  virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);
}; */

// ----------------

class SayNumberOfDrinks : public State<Drunkard>
{
private:
  
  SayNumberOfDrinks(){}
  SayNumberOfDrinks(const SayNumberOfDrinks&);
  SayNumberOfDrinks& operator=(const SayNumberOfDrinks&);

public:

  static SayNumberOfDrinks* Instance();
  virtual void Enter(Drunkard* drunkard);
  virtual void Execute(Drunkard* drunkard);
  virtual void Exit(Drunkard* drunkard);
  virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);
};

// ----------------

class Drink : public State<Drunkard>
{
private:
  
  Drink(){}
  Drink(const Drink&);
  Drink& operator=(const Drink&);

public:

  static Drink* Instance();
  virtual void Enter(Drunkard* drunkard);
  virtual void Execute(Drunkard* drunkard);
  virtual void Exit(Drunkard* drunkard);
  virtual bool OnMessage(Drunkard* drunkard, const Telegram& msg);
};

#endif // DRUNKARD_OWNED_STATES_H