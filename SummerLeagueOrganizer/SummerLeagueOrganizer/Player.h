#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<string>

const enum CATEGORY { ERR = -1, U6, U8, U10, U12, U14, U17 };// Age categories for each team
const enum REG_STATUS { PAID, NOT_PAID };// registration status

class Player {
public:
	Player(const std::string& name, const int& year_of_birth, const CATEGORY& category, 
		const REG_STATUS& reg_status) : name_(name), year_of_birth_(year_of_birth), 
		category_(category), reg_status_(reg_status) {};

	// get methods
	const std::string& name() const { return name_; };
	const CATEGORY& category() const { return category_; };
	const int& year_of_birth() const { return year_of_birth_; };
	const REG_STATUS& reg_status() const { return reg_status_; };

	// set methods
	void set_name(const std::string& name) { name_ = name; };
	void set_category(const CATEGORY& category) { category_ = category; };
	void set_reg_status(const REG_STATUS& reg_status) { reg_status_ = reg_status; };
	void set_year_of_birth(const int& year_of_birth) { year_of_birth_ = year_of_birth; };

	// friend declarations
	friend std::ostream& operator<<(std::ostream& out, const Player& player);
	friend std::ostream& operator<<(std::ostream& out, const CATEGORY& category);

private:
	CATEGORY category_;
	std::string name_ = "";
	REG_STATUS reg_status_;
	int year_of_birth_ = -1;
};

#endif