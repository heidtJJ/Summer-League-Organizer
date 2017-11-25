#include"Buffer.h"//DELETE THIS
#include"Player.h"//DELETE THIS
#include"LeagueOrganizer.h"
#include<string>
#include<iostream>
#include<sstream>

int main() {/*
			Buffer myBuffer;
			myBuffer.insert_player(std::string("jared"), 2013, false);
			myBuffer.insert_player(std::string("afs"), 2013, true);
			std::cout << myBuffer.insert_player(std::string("fasdfas"), 2013, true);
			std::cout << myBuffer.insert_player(std::string("fasdfas"), 2010, false);
			std::cout << myBuffer.insert_player(std::string("fasdfas"), 2008, true);
			std::cout<< myBuffer.insert_player(std::string("fasdfas"), 2005, true);
			std::cout << myBuffer.look_up_player(std::string("jared")) << std::endl;

			myBuffer.edit_player(std::string("jared"), std::string("jeff"));
			std::cout << myBuffer.look_up_player(std::string("jared")) << std::endl;
			std::cout << myBuffer.look_up_player(std::string("jeff")) << std::endl;
			std::cout << myBuffer.deletePlayer("jeff") << std::endl;
			std::cout << "jeff " << myBuffer.look_up_player(std::string("jeff")) << std::endl;


			myBuffer.edit_player(std::string("jared"), 2012);

			myBuffer.displayStats();

			myBuffer.printToFile(std::string("ALL"));

			myBuffer.clearSeason();
			std::cout << myBuffer.look_up_player(std::string("afs")) << std::endl;
			*/


			/*char payed = ' ';
			bool good_input = false;
			std::cout << "Has the player paid? If yes, enter 'y', if no, enter 'n': ";
			std::string user_input = "";
			getline(std::cin, user_input);
			std::stringstream sstream(user_input);

			sstream >> payed;// extract data
			sstream.get();
			std::cout << bool(sstream) << std::endl;
			*/
	LeagueOrganizer league_organizer;
	league_organizer.run();// fix file outputting


	std::cout << std::endl;
	std::cout << std::endl;
	system("PAUSE");
	return 0;
}