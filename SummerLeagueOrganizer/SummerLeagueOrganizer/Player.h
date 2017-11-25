#ifndef _PLAYER_H_
#define _PLAYER_H_

#include<string>

const enum Category { ERR = -1, U6, U8, U10, U12, U14, U17 };
const enum RegistrationStatus { PAID, NOT_PAID };

class Player {
public:
	Player(const std::string& name, const int& year_of_birth, const Category& category, const RegistrationStatus& reg_status) : name_(name), year_of_birth_(year_of_birth), category_(category), reg_status_(reg_status) {};
	const int& year_of_birth() const { return year_of_birth_; };
	const std::string& name() const { return name_; };
	const Category& category() const { return category_; };
	const RegistrationStatus& reg_status() const { return reg_status_; };
	void set_year_of_birth(const int& year_of_birth) { year_of_birth_ = year_of_birth; };
	void set_name(const std::string& name) { name_ = name; };
	void set_category(const Category& category) { category_ = category; };
	void set_reg_status(const RegistrationStatus& reg_status) { reg_status_ = reg_status; };

	friend std::ostream& operator<<(std::ostream& out, Category category);
	friend std::ostream& operator<<(std::ostream& out, const Player& player);


private:
	int year_of_birth_ = -1;
	std::string name_ = "";
	Category category_;
	RegistrationStatus reg_status_;
};

#endif
