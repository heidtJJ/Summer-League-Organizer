#ifndef _BUFFER_H_
#define _BUFFER_H_

#include<map>
#include<vector>
#include<string>
#include<iostream>
#include"Player.h"

const int NUM_TEAMS = 6;

class PlayerNotFoundException {};

class Buffer {
public:
	Buffer();

	void clear_season();
	void display_stats() const;
	bool delete_player(const std::string& name_);
	bool print_to_file(std::string& category) const;
	bool look_up_player(const std::string& name_);
	bool insert_player(const std::string& name_, const int& current_year, const int& year_of_birth_, const bool& reg_status_);

	bool edit_player(const std::string& name_, const bool& new_reg_status);
	bool edit_player(const std::string& name_, const std::string& new_name);
	bool edit_player(const std::string& name_, const CATEGORY& new_category);
	bool edit_player(const std::string& name_, const int& current_year, const int& new_year_of_birth);

private:
	void lower_string(std::string& word) const;
	Player& findPlayer(const std::string& name_);
	CATEGORY findAgeCategory(const int& age) const;
	void print_team(std::ostream& out, const CATEGORY& category) const;

	std::vector<std::map<std::string, Player>> league_teams;
};
#endif // _BUFFER_H_
