#include"Buffer.h"
#include<fstream>

void Buffer::lower_string(std::string& word) const {
	for (unsigned int x = 0; x < word.size(); ++x)
		word[x] = tolower(word[x]);
}

void Buffer::print_team(std::ostream & out, const CATEGORY& category) const {
	out << CATEGORY(category) << "Players:" << std::endl;
	for (std::pair<std::string, Player>const & player : league_teams[category])
		out << player.first << std::endl;
}

Buffer::Buffer() {
	for (int x = 0; x < NUM_TEAMS; ++x) {
		std::map<std::string, Player> team;
		league_teams.push_back(team);
	}
}

void Buffer::clear_season() {
	for (std::map<std::string, Player>& team : league_teams) {
		team.clear();
	}
}

CATEGORY Buffer::findAgeCategory(const int& age) const {
	if (age >= 4 && age < 6)
		return U6;
	else if (age >= 6 && age < 8)
		return U8;
	else if (age >= 8 && age < 10)
		return U10;
	else if (age >= 10 && age < 12)
		return U12;
	else if (age >= 12 && age < 14)
		return U14;
	else if (age >= 14 && age < 17)
		return U17;
	else
		return ERR;
}

bool Buffer::insert_player(const std::string& name_, const int& current_year, const int& year_of_birth_,const bool& reg_status_) {
	int age = current_year - year_of_birth_;
	REG_STATUS reg_status = reg_status_ ? PAID : NOT_PAID;
	// find the category of the player
	CATEGORY playerCategory = findAgeCategory(age);

	if (playerCategory == ERR)
		return false;
	else {
		Player playerToAdd(name_, year_of_birth_, playerCategory, reg_status);

		try {
			findPlayer(name_);// if player is not found, we want to insert
			return false;
		}
		catch (PlayerNotFoundException) {
			league_teams[playerCategory].insert(std::pair<std::string, Player>(name_, playerToAdd));
			return true;
		}
	}
}

Player& Buffer::findPlayer(const std::string& name_) {
	for (std::map<std::string, Player>& team : league_teams) {
		auto it = team.find(name_);
		if (it != team.end())
			return it->second;
	}
	throw PlayerNotFoundException();
}

bool Buffer::look_up_player(const std::string& name_) {
	try {
		Player player = findPlayer(name_);
		std::cout << std::endl << player;
		return true;
	}
	catch (PlayerNotFoundException) {
		return false;
	}
}

bool Buffer::edit_player(const std::string& name_, const std::string& new_name) {
	try {
		Player player = findPlayer(name_);// find the player's entry
		Player playerToAdd(new_name, player.year_of_birth(), player.category(), player.reg_status());

		CATEGORY category = player.category();
		league_teams[category].erase(name_);// erase the current entry

		league_teams[category].insert(std::pair<std::string, Player>(new_name, playerToAdd));// add new entry
		return true;
	}
	catch (PlayerNotFoundException) {
		return false;
	}
}

bool Buffer::edit_player(const std::string& name_, const int& current_year, const int& new_year_of_birth) {// could change category
	try {
		Player player = findPlayer(name_);
		if (findAgeCategory(new_year_of_birth) != player.category()) {
			delete_player(name_);
			bool paid = player.reg_status() == PAID ? true : false;
			insert_player(player.name(), current_year, new_year_of_birth, paid);
		}
		else {
			findPlayer(name_).set_year_of_birth(new_year_of_birth);
		}
		return true;
	}
	catch (PlayerNotFoundException) {
		return false;
	}
}


bool Buffer::edit_player(const std::string& name_, const CATEGORY& new_category) {
	try {
		findPlayer(name_).set_category(new_category);// find the player's entry and change it
		return true;
	}
	catch (PlayerNotFoundException) {
		return false;
	}
}

bool Buffer::edit_player(const std::string& name_, const bool& new_reg_status) {
	try {
		REG_STATUS reg_status = new_reg_status ? PAID : NOT_PAID;
		findPlayer(name_).set_reg_status(reg_status);// find the player's entry and change it
		return true;
	}
	catch (PlayerNotFoundException) {
		return false;
	}
}

bool Buffer::delete_player(const std::string& name) {
	for (std::map<std::string, Player>& team : league_teams) {
		auto it = team.find(name);
		if (it != team.end()) {
			league_teams[it->second.category()].erase(name);
			return true;
		}
	}
	return false;
}

void Buffer::display_stats()const {
	int numPlayers = 0;
	int numPaid = 0;
	std::vector<int> numUnpaid;

	int teamCat = U6;
	for (std::map<std::string, Player> const & team : league_teams) {
		numUnpaid.push_back(0);
		numPlayers += int(team.size());

		for (auto& it = team.begin(); it != team.end(); ++it) {
			if (it->second.reg_status() == PAID) {
				++numPaid;
			}
			else {
				++numUnpaid[teamCat];
			}
		}
		++teamCat;
	}

	std::cout << std::endl << "\tNumber of player in league: " << numPlayers << std::endl
		<< "\tNumber of players who have paid: " << numPaid << std::endl;
	for (int team = U6; team < NUM_TEAMS; ++team) {
		std::cout << "\tNumber of players who need to pay in " << CATEGORY(team) << ": " << numUnpaid[team] << std::endl;
	}
}

bool Buffer::print_to_file(std::string& category) const {
	lower_string(category);
	std::ofstream out;
	bool goodOpen = true;
	if (category == "u6") {
		out.open("U6.txt");
		print_team(out, U6);
	}
	else if (category == "u8") {
		out.open("U8.txt");
		print_team(out, U8);
	}
	else if (category == "u10") {
		out.open("U10.txt");
		print_team(out, U10);
	}
	else if (category == "u12") {
		out.open("U12.txt");
		print_team(out, U12);
	}
	else if (category == "u14") {
		out.open("U14.txt");
		print_team(out, U14);
	}
	else if (category == "u17") {
		out.open("U17.txt");
		print_team(out, U17);
	}
	else if (category == "all") {
		out.open("ALL.txt");
		for (int team = U6; team < NUM_TEAMS; ++team) {
			print_team(out, CATEGORY(team));
			out << std::endl;
		}
	}
	else {
		goodOpen = false;
	}

	out.close();
	return goodOpen;
}

