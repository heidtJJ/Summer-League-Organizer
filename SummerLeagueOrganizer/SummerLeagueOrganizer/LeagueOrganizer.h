#ifndef _LEAGUE_ORGANIZER_H_
#define _LEAGUE_ORGANIZER_H_

#include "Buffer.h"

const static int MINIMUM_YEAR = 1900;
const static std::string SHORT_SPACING(5, ' ');
const static std::string SHORT_SEPERATOR(10, '-');
const static std::string LONG_SEPERATOR(50, '-');

class LeagueOrganizer {
public:
	void run();

private:
	// interface
	void display();
	void show_error_message();
	void give_options_change() const;

	// executing commands methods for interface
	void execute_command(const int& cmd, bool& done);
	void execute_change_player(const int& cmd, const std::string& name);// first to do

	// commands for each task
	void add_player();
	void edit_player();
	void delete_player();
	void write_to_file();
	void search_for_player();
	void start_new_season();

	// methods for getting data from user
	bool get_player_paid();
	int get_year_of_birth();
	void get_current_year();
	std::string get_name_of_player();

	// data members
	int current_year;
	Buffer league_buffer;
	std::string error_message_ = "";
};

#endif // _LEAGUE_ORGANIZER_H_