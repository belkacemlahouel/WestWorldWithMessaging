#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunkard.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

/*
int main(int argc, char** argv)
{
	std::cout << "Hello World!" << std::endl;

	Drunkard* Jack = new Drunkard(ent_Jack);

	delete Jack;

	std::cout << "Bye World!" << std::endl;
	std::cin.ignore();

	return 0;
}
*/

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create a drunkard
  Drunkard* Jack = new Drunkard(ent_Jack);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Jack);

  //run Bob and Elsa through a few Update calls
  for (int i=0; i<30; ++i)
  { 
    Bob->Update();
    Elsa->Update();
	Jack->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }

  //tidy up
  delete Bob;
  delete Elsa;
  delete Jack;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






