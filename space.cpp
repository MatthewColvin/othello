#include "space.h"
#include "colors.h"
#include <iostream>


space::space(bool b , bool w ,bool n)
{
	black = b;
	white = w;
	neutral = n;
}

void space::make_white()
{
	white = true;
	black = false;
	neutral = false;
}

void space::make_black()
{
	black = true;
	white = false;
	neutral = false;
}

void space::make_neutral()
{
	black = false;
	white = false;
	neutral = true;
}

void space::flip()
{
	if (white) {
		make_black();
		return;
	}
	if (black) {
		make_white();
		return;
	}
}

bool const space:: are_oppsite(space sp)const 
{
	if (black && sp.white) { return true; }
	if (white && sp.black) { return true; }
	return false;
	
}


bool const space:: are_same(space sp)const
{
	if (black && sp.black) { return true; }
	if (white && sp.white) { return true; }
	return false;
}

bool const space::is_white()const
{
	if (white && !black) { return true; }
	return false;
}

bool const space::is_black()const
{
	if (black && !white) { return true; }
	return false;
}

void space::output(std::ostream& out)
{
	if (white) { out << B_WHITE << "  " << RESET; }
	if (black) { out << B_BLACK << "  " << RESET; }
	if (neutral) { out << "  "; }
}

std::ostream& operator<<(std::ostream& os,space sp)
{
	sp.output(os);
	return os;
}




