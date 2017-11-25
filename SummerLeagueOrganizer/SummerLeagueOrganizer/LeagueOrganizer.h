#ifndef _LEAGUE_ORGANIZER_H_
#define _LEAGUE_ORGANIZER_H_

#include <string>
#include "Buffer.h"

const static std::string SHORT_SPACING(5, ' ');
const static std::string SHORT_SEPERATOR(10, '-');
const static std::string LONG_SEPERATOR(50, '-');
const static int MINIMUM_YEAR = 1900;

class LeagueOrganizer {
public:
	void run();

private:
	void display();
	void show_options() const;
	void give_options_change() const;
	void get_current_year();
	void show_error_message();
	void execute_command(const int& cmd, bool& done);
	void execute_change_player(const int& cmd, const std::string& name);// first to do
	int get_year_of_birth();
	std::string get_name_of_player() const;
	bool get_player_paid();

	int current_year;
	Buffer league_buffer;
	std::string error_message_ = "";
};

#endif // _LEAGUE_ORGANIZER_H_
