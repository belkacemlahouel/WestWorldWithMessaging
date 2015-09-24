#ifndef MESSAGE_TYPES
#define MESSAGE_TYPES

#include <string>

enum message_type
{
  Msg_HiHoneyImHome,
  Msg_StewReady,
  Msg_Tease,
  Msg_Punch,
  Msg_Warning,
};


inline std::string MsgToStr(int msg)
{
  switch (msg)
  {
  case Msg_HiHoneyImHome:
    
    return "HiHoneyImHome"; 

  case Msg_StewReady:
    
    return "StewReady";

  case Msg_Tease:

	  return "Teasing";

  case Msg_Punch:

	  return "Punching";

  case Msg_Warning:

	  return "WarningFight";

  default:

    return "Not recognized!";
  }
}

#endif