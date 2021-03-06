#include "LeagueOrganizer.h"
#include <iostream>
#include <sstream>
#include <string>


const static int MINIMUM_YEAR = 1900;
const static std::string SHORT_SPACING(5, ' ');
const static std::string SHORT_SEPERATOR(10, '-');
const static std::string LONG_SEPERATOR(50, '-');


void LeagueOrganizer::run()
{
	get_current_year();

	bool done = false;
	while (!done) {
		display();

		std::string userChoice = "";
		std::getline(std::cin, userChoice);

		std::stringstream sstream(userChoice);
		int choice = -1;
		sstream >> choice;// extract data

		if (!sstream.eof() || choice < 1 || choice > 8) {// error notify user
			error_message_ = "Invalid input. Enter a number for options 1 through 8.";
		}
		if (error_message_.empty())
			execute_command(choice, done);

		std::cout << std::endl;
	}
}


void LeagueOrganizer::display() {
	std::cout << LONG_SEPERATOR << std::endl;
	show_error_message();

	std::cout << "Options:" << std::endl
		<< SHORT_SPACING << "(1) Start a new season" << std::endl
		<< SHORT_SPACING << "(2) Add a player" << std::endl
		<< SHORT_SPACING << "(3) Look up a player" << std::endl
		<< SHORT_SPACING << "(4) Edit a player's information" << std::endl
		<< SHORT_SPACING << "(5) Delete a player" << std::endl
		<< SHORT_SPACING << "(6) Write player names to a file" << std::endl
		<< SHORT_SPACING << "(7) Display statistics" << std::endl
		<< SHORT_SPACING << "(8) Exit program - Note: Does not save." << std::endl;	std::cout << SHORT_SEPERATOR << std::endl;

	std::cout << "Enter a number 1-8. Choice: ";
}


void LeagueOrganizer::show_error_message() {
	if (!error_message_.empty()) {
		std::cout << "ERROR: " + error_message_ << std::endl;
		error_message_.clear();
	}
}


void LeagueOrganizer::give_options_change() const
{
	std::cout << "Options:" << std::endl
		<< SHORT_SPACING << "(1) Change name of player" << std::endl
		<< SHORT_SPACING << "(2) Change birth year of player" << std::endl
		<< SHORT_SPACING << "(3) Change registration status" << std::endl;
}


void LeagueOrganizer::execute_command(const int& cmd, bool& done) {
	switch (cmd) {
	case 1: {// start new season
		std::cout << "Are you sure that you want to delete all current players?" << std::endl
			<< "If yes, enter \"yes\". If no, enter anything other than \"yes\"." << std::endl;
		std::string user_choice = "";
		getline(std::cin, user_choice);
		if (user_choice == "yes") {
			league_buffer.clear_season();
			std::cout << std::endl << "New season started. ";
			get_current_year();
		}
		else {
			std::cout << std::endl << "Season NOT cleared.";
		}		break;
	}
	case 2: {// 
		int year_of_birth;
		std::string name = get_name_of_player();
		if (error_message_.empty())
			year_of_birth = get_year_of_birth();
		bool player_paid;
		if (error_message_.empty())
			player_paid = get_player_paid();

		if (error_message_.empty()) {
			bool good_add = league_buffer.insert_player(name, current_year, year_of_birth, player_paid);
			if (good_add) {
				std::cout << std::endl << "Successfully added " + name + " into the league.";
			}
			else {
				error_message_ = "Could not add player to the league. Player is already in league.";
			}
		}		break;
	}
	case 3: {
		std::string name = get_name_of_player();
		bool playerFound = league_buffer.look_up_player(name);
		if (!playerFound)
			error_message_ = "Player is not found in the league.";
		break;
	}
	case 4: {
		std::string name = get_name_of_player();

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
		}		break;
	}
	case 5: {
		std::cout << "Deleting a player - ";
		std::string player_name = get_name_of_player();

		bool played_deleted = league_buffer.delete_player(player_name);
		if (!played_deleted) {
			std::cout << std::endl;
			error_message_ = " Cannot delete player. Player was not found in the league.";
		}
		else {
			std::cout << "Successfully deleted " + player_name + " from the league." << std::endl;
		}		break;
	}
	case 6: {
		std::cout << "If you would like to write the names of a single team to a file, enter \"U6\", \"U8\", \"U10\", etc." << std::endl;
		std::cout << "If you would like to write the names of every team to a file, enter \"ALL\"." << std::endl;

		std::string user_choice = "";
		std::getline(std::cin, user_choice);
		std::stringstream sstream(user_choice);

		std::string choice;
		sstream >> choice;// extract data from string stream

		sstream.get();
		if (!sstream) {
			bool file_success = league_buffer.print_to_file(choice);
			if (!file_success) {
				error_message_ = "Invalid entry. File cannot be written to.";
			}
			else {
				std::cout << "File successfully created.";
			}
		}
		else {
			error_message_ = "Invalid file selection. Cannot write to file.";
		}		break;
	}
	case 7: {
		league_buffer.display_stats();
		break;
	}
	case 8: {
		std::cout << "Are you sure that you want to end the program? All unsaved data will be lost." << std::endl
			<< "If yes, enter \"yes\". If no, enter anything other than \"yes\"." << std::endl;

		std::string user_choice = "";
		getline(std::cin, user_choice);
		if (user_choice == "yes")
			done = true;
		else
			std::cout << std::endl;
		break;
	}
	default: {
		error_message_ = "Invalid number given.";
		break;
	}
	}
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
			bool valid_year = league_buffer.edit_player(name,current_year ,new_birth_year);
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


void LeagueOrganizer::get_current_year() {
	bool good_year = false;
	while (!good_year) {
		std::cout << "What is the current year? ";
		std::string user_input = "";
		getline(std::cin, user_input);

		int year;
		std::stringstream sstream(user_input);
		sstream >> year;// extract data

		if (!sstream.eof() || year < MINIMUM_YEAR) {// error notify user
			std::cout << "Invalid input. Please enter a vaild year greater than " << MINIMUM_YEAR << '.' << std::endl;
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
		error_message_ = "Could not add player to league. Player must have age greater \nthan 4 and less than 17.";
		return -1;
	}

	return year_of_birth;
}


bool LeagueOrganizer::get_player_paid() {
	char paid = ' ';
	std::cout << "If player has paid, enter \"y\", if not, enter \"n\": ";
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


std::string LeagueOrganizer::get_name_of_player() {
	std::cout << "Name of player? ";
	std::string name = "";
	getline(std::cin, name);
	if (name.empty()) {
		error_message_ = "Name cannot be empty.";
	}
	return name;
}