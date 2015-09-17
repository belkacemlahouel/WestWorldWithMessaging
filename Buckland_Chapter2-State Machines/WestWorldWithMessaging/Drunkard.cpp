#include "Drunkard.h"

void Drunkard::Update()
{
	SetTextColor(FOREGROUND_BLUE| FOREGROUND_INTENSITY);
	m_pStateMachine->Update();
}

bool Drunkard::HandleMessage(const Telegram& msg)
{
	return m_pStateMachine->HandleMessage(msg);
}

void Drunkard::drinkOneMore()
{
	++m_nbDrinks;
}
	