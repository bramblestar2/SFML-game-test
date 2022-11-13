#include "ID.h"

ID::ID(const std::string _type)
{
	type = _type;
}

ID::ID()
{
	id = -1;
	color = {0,0,0};
	type = "NONE";
}
