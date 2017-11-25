#include "LeagueOrganizer.h"
#include <iostream>
#include <sstream>
#include <string>

void LeagueOrganizer::show_options() const
{
	std::cout << "Options:" << std::endl
		<< SHORT_SPACING << "(1) Start a new season" << std::endl
		<< SHORT_SPACING << "(2) Add a player" << std::endl
		<< SHORT_SPACING << "(3) Look up a player" << std::endl
		<< SHORT_SPACING << "(4) Edit a player's information" << std::endl
		<< SHORT_SPACING << "(5) Delete a player" << std::endl
		<< SHORT_SPACING << "(6) Write player names to a file" << std::endl
		<< SHORT_SPACING << "(7) Display statistics" << std::endl;
}

void LeagueOrganizer::show_error_message() {
	if (!error_message_.empty()) {
		std::cout << "ERROR: " + error_message_ << std::endl;
		error_message_.clear();
	}
}

void LeagueOrganizer::display() {
	std::cout << LONG_SEPERATOR << std::endl;
	show_error_message();
	show_options();
	std::cout << SHORT_SEPERATOR << std::endl;

	std::cout << "Enter an number 1-7. Choice: ";
}

void LeagueOrganizer::get_current_year() {
	bool good_year = false;
	while (!good_year) {
		std::cout << "Current year? ";
		std::string user_input = "";
		getline(std::cin, user_input);

		int year;
		std::stringstream sstream(user_input);
		sstream >> year;// extract data

		if (!sstream.eof() || year < MINIMUM_YEAR) {// error notify user
			std::cout << "Invalid input. Please enter a vaild year." << std::endl;
		}
		else {
			good_year = true;
			current_year = year;
		}
	}
}

int LeagueOrganizer::get_year_of_birth() {
	int year_of_birth = -1;
	std::cout << "Year of Birth? ";
	std::string user_input = "";
	getline(std::cin, user_input);
	std::stringstream sstream(user_input);

	sstream >> year_of_birth;// extract data

	if (!sstream.eof() || (current_year - year_of_birth) < 4 || (current_year - year_of_birth) > 16) {
		error_message_ = "Could not add player to league. Player must have age greater than 4 and less than 17.";
		return -1;
	}

	return year_of_birth;
}


std::string LeagueOrganizer::get_name_of_player() const {
	std::cout << "Name of player? ";
	std::string name = "";
	getline(std::cin, name);
	return name;
}

bool LeagueOrganizer::get_player_paid() {
	char paid = ' ';
	std::cout << "Has the player paid? If yes, enter 'y', if no, enter 'n': ";
	std::string user_input = "";
	getline(std::cin, user_input);
	std::stringstream sstream(user_input);

	paid = sstream.get();// extract data
	paid = tolower(paid);

	sstream.get();// attempt to read past first character
	if (sstream || (paid != 'y' && paid != 'n')) {// error notify user
		error_message_ = "Invalid pay entry.";
		return false;// will be filtered because of error messgae
	}
	else {
		if (paid == 'y')
			return true;
		else
			return false;
	}

}

void LeagueOrganizer::execute_command(const int& cmd, bool& done) {
	switch (cmd) {// start new season
	case 1: {
		league_buffer.clearSeason();
		std::cout << "New season started." << std::endl;
		break;
	}
	case 2: {// add a player
		std::string name = get_name_of_player();
		int year_of_birth = get_year_of_birth();
		bool player_paid;
		if (error_message_.empty())
			player_paid = get_player_paid();

		if (error_message_.empty()) {
			bool good_add = league_buffer.insert_player(name, year_of_birth, player_paid);
			if (good_add) {
				std::cout << "Successfully added " + name + " into the league." << std::endl;
			}
			else {
				error_message_ = "Could not add player to the league. Player is already in league.";
			}
		}
		break;
	}
	case 3: {// search for player
		std::string name = get_name_of_player();
		std::cout << std::endl;
		bool playerFound = league_buffer.look_up_player(name);
		if (!playerFound)
			error_message_ = "Player is not found in the league.";
		break;
	}
	case 4: {// edit a player
		std::string name = get_name_of_player();
		std::cout << std::endl;

		bool playerFound = league_buffer.look_up_player(name);
		if (!playerFound)
			error_message_ = "Player is not found in the league.";

		if (error_message_.empty()) {
			give_options_change();

			std::string userChoice = "";
			std::getline(std::cin, userChoice);
			std::stringstream sstream(userChoice);

			int choice;
			sstream >> choice;// extract data from string stream

			if (!sstream.eof() || choice < 1 || choice > 4) {// error notify user
				error_message_ = "Invalid input. Number must be betweenr options 1 and 4.";
			}
			else {
				execute_change_player(choice, name);
			}
		}
		break;
	}
	case 5: {// delete a player
		std::cout << "Deleting a player - ";
		std::string player_name = get_name_of_player();

		bool played_deleted = league_buffer.deletePlayer(player_name);
		if (!played_deleted) {
			error_message_ = " Cannot delete player. Player was not found in the league.";
		}
		else {
			std::cout << "Successfully deleted " + player_name + " from the league." << std::endl;
		}
		break;
	}
	case 6: {// write to file
		std::cout << "If you would like to write the names of a single team to a file, enter 'U6', 'U8', 'U10', etc." << std::endl;
		std::cout << "If you would like to write the names of every team to a file, enter 'ALL'." << std::endl;

		std::string user_choice = "";
		std::getline(std::cin, user_choice);
		std::stringstream sstream(user_choice);

		std::string choice;
		sstream >> choice;// extract data from string stream

		sstream.get();
		if (!sstream) {
			bool file_success = league_buffer.printToFile(choice);
			if (!file_success) {
				error_message_ = "File cannot be written to.";
			}
			else {
				std::cout << "File successfully created.";
			}
		}
		else {
			error_message_ = "Invalid file selection. Cannot write to file.";
		}
		break;
	}
	case 7: {// display statistics
		league_buffer.displayStats();
		break;
	}
	default: {
		error_message_ = "Invalid number given.";
		break;
	}

	}
}

void LeagueOrganizer::give_options_change() const
{
	std::cout << "Options:" << std::endl
		<< SHORT_SPACING << "(1) Change name of player" << std::endl
		<< SHORT_SPACING << "(2) Change birth year of player" << std::endl
		<< SHORT_SPACING << "(3) Change registration status" << std::endl;
}

void LeagueOrganizer::execute_change_player(const int & cmd, const std::string& name)
{
	// NOTE: player is already assumed to be in the league. This is checked in the execute_command method
	switch (cmd) {
	case 1: {
		std::cout << "New name of player? ";
		std::string new_name = "";
		getline(std::cin, new_name);
		league_buffer.edit_player(name, new_name);
		std::cout << "Player successfully edited." << std::endl;
		break;
	}
	case 2: {
		std::cout << "New ";
		int new_birth_year = get_year_of_birth();

		if (error_message_.empty()) {
			league_buffer.edit_player(name, new_birth_year);
			std::cout << "Player successfully edited." << std::endl;
		}
		break;
	}
	case 3: {
		bool player_paid = get_player_paid();

		if (error_message_.empty()) {
			league_buffer.edit_player(name, player_paid);
			std::cout << "Player successfully edited." << std::endl;
		}
		break;
	}
	default: {
		error_message_ = "Invalid entry given.";
		break;
	}
	}
}

void LeagueOrganizer::run()
{
	get_current_year();

	bool done = false;
	while (!done) {
		display();

		std::string userChoice = "";
		std::getline(std::cin, userChoice);

		std::stringstream sstream(userChoice);
		int choice;
		sstream >> choice;// extract data

		if (!sstream.eof() || choice < 1 || choice > 7) {// error notify user
			error_message_ = "Invalid input. Please enter a number for options 1 and 7.";
		}
		if (error_message_.empty())
			execute_command(choice, done);

		std::cout << std::endl << std::endl;
	}
}
