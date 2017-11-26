#include "Player.h"
#include<iostream>

std::ostream & operator<<(std::ostream & out, const CATEGORY& category)
{
	switch (category) {
	case U6: {
		out << "U6 ";
		break;
	}
	case U8: {
		out << "U8 ";
		break;
	}
	case U10: {
		out << "U10 ";
		break;
	}
	case U12: {
		out << "U12 ";
		break;
	}
	case U14: {
		out << "U14 ";
		break;
	}
	case U17: {
		out << "U17 ";
		break;
	}
	default: {
		out << "ERR ";
		break;
	}
	}
	return out;
}

std::ostream & operator<<(std::ostream & out, const Player & player)
{
	out << "\tName: " << player.name_ << std::endl << "\tYear of birth: " << player.year_of_birth_ << std::endl
		<< "\tTeam Category: " << player.category_ << std::endl
		<< "\tRegistration status: " << (player.reg_status_ == PAID ? "Paid" : "Not Paid") << std::endl;
	return out;
}