// TextAdventure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <windows.h>

using namespace std;

void section_command(string Cmd, string &wd1, string &wd2)
{
	string sub_str;
	vector<string> words;
	char search = ' ';
	size_t i, j;

	// Split Command into vector
	for (i = 0; i < Cmd.size(); i++)
	{
		if (Cmd.at(i) != search)
		{
			sub_str.insert(sub_str.end(), Cmd.at(i));
		}
		if (i == Cmd.size() - 1)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
		if (Cmd.at(i) == search)
		{
			words.push_back(sub_str);
			sub_str.clear();
		}
	}
	// Clear out blanks
	for (i = words.size() - 1; i > 0; i--)
	{
		if (words.at(i) == "")
		{
			words.erase(words.begin() + i);
		}
	}
	// Make words upper case
	for (i = 0; i < words.size(); i++)
	{
		for (j = 0; j < words.at(i).size(); j++)
		{
			if (islower(words.at(i).at(j)))
			{
				words.at(i).at(j) = toupper(words.at(i).at(j));
			}
		}
	}
	// Get 2 words.
	if (words.size() == 0)
	{
		cout << "No command given" << endl;
	}
	if (words.size() == 1)
	{
		wd1 = words.at(0);
	}
	if (words.size() == 2)
	{
		wd1 = words.at(0);
		wd2 = words.at(1);
	}
	if (words.size() > 2)
	{
		cout << "Command too long. Only type one or two words (direction or verb and noun)" << endl;
	}
}

void turn_around(string &facing, string looking, string word2){
	if (word2 == "RIGHT"){
		if (looking == "NORTH"){
			cout << "I turn to my right, i'm now facing east." << endl;
			facing = "EAST";
		}
		else if (looking == "EAST"){
			cout << "I turn to my right, i'm now facing south." << endl;
			facing == "SOUTH";
		}
		else if (looking == "SOUTH"){
			cout << "I turn to my right, i'm now facing west." << endl;
			facing == "WEST";
		}
		else{
			cout << "I turn to my right, i'm now facing south." << endl;
			facing == "NORTH";
		}
	}
	else if (word2 == "LEFT"){
		if (looking == "NORTH"){
			cout << "I turn to my left, i'm now facing west." << endl;
			facing = "WEST";
		}
		else if (looking == "EAST"){
			cout << "I turn to my left, i'm now facing north." << endl;
			facing == "NORTH";
		}
		else if (looking == "SOUTH"){
			cout << "I turn to my left, i'm now facing east." << endl;
			facing == "EAST";
		}
		else{
			cout << "I turn to my left, i'm now facing south." << endl;
			facing == "SOUTH";
		}
	}
	else if (word2 == "AROUND"){
		if (looking == "NORTH"){
			cout << "I turn around, i'm now facing south." << endl;
			facing = "SOUTH";
		}
		else if (looking == "EAST"){
			cout << "I turn around, i'm now facing west." << endl;
			facing == "WEST";
		}
		else if (looking == "SOUTH"){
			cout << "I turn around, i'm now facing north." << endl;
			facing == "NORTH";
		}
		else{
			cout << "I turn around, i'm now facing east." << endl;
			facing == "EAST";
		}
	}
}

int main()
{
	string command;
	string word_1;
	string word_2;
	string looking = "NORTH";
	bool storyInitialized = false;
	bool foundButton = false;
	bool alive = true;
	bool won = false;
	int pushCount = 0;

	HANDLE hConsole;
	int red = 252;
	int black = 15;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	while (word_1 != "QUIT")
	{
		command.clear();
		if (!storyInitialized){
			cout << "I'm alone in a dark small room, don't know where nor how i got here." << endl;
			cout << "";
			storyInitialized = true;
		}
		cout << "What shall I do? ";
		getline(cin, command);
		cout << "Your raw command was " << command << endl;

		word_1.clear();
		word_2.clear();

		// Call command handler
		section_command(command, word_1, word_2);

		if (alive){
			if (word_1 == "HELP"){
				SetConsoleTextAttribute(hConsole, red);
				cout << "Announcer:";
				SetConsoleTextAttribute(hConsole, black);
				cout << " Well i suppose i could help you out a bit:" << endl;
				cout << "Look up/down" << endl;
				cout << "Turn left/right/around" << endl;
				cout << "Search pockets/wall" << endl;
				cout << "Push wall/???" << endl;
			} else if (word_1 == "LOOK"){
				if (word_2 == "UP"){
					cout << "Well it's dark yet i try to look up... seems like there's a low ceiling." << endl;
				}
				else if (word_2 == "DOWN"){
					cout << "In the darkness i faintly see my private parts." << endl;
				}
			}
			else if (word_1 == "SEARCH"){
				if (word_2 == "POCKETS"){
					cout << "The unfortunate thing about not wearing clothing is not having pockets..." << endl;
				}
				else if (word_2 == "WALL"){
					if (looking == "NORTH"){
						cout << "Just some plain wall, seems like solid concrete... " << endl;
					}
					else if (looking == "EAST"){
						cout << "Just some plain wall, seems like solid concrete... " << endl;
					}
					else if (looking == "SOUTH"){
						foundButton = true;
						cout << "I find a button, should i try pushing it?" << endl;
					}
					else if (looking == "WEST"){
						cout << "Just some plain wall, seems like solid concrete... " << endl;
					}
				}
			}
			else if (word_1 == "TURN"){
				turn_around(looking, looking, word_2);
			}
			else if (word_1 == "PUSH"){
				if (word_2 == "WALL"){
					if (looking == "NORTH"){
						cout << "I try pushing as hard as i can, yet... concrete, it's not like i'm The Hulk." << endl;
					}
					else if (looking == "EAST"){
						cout << "Interesting... the wall pushed back, should i try pushing it again?" << endl;
						pushCount++;
						if (pushCount > 5 && pushCount < 10){
							cout << "Ooh it almost sounds like the wall says it's getting angry.... should i push again?" << endl;
						}
						else if (pushCount > 10){
							cout << "I think i've angered the wall now, it seems to slowly move towards me..." << endl;
							cout << "Wait... what means... OH! FUCK!" << endl;
							SetConsoleTextAttribute(hConsole, red);
							cout << "Announcer:";
							SetConsoleTextAttribute(hConsole, black);
							cout << "Ooops! Your actions got the test subject killed. Ah well better luck next time, am i right?" << endl;
							alive = false;
						}
					}
					else if (looking == "SOUTH"){
						cout << "I try pushing as hard as i can, yet... concrete, it's not like i'm The Hulk." << endl;
						if (foundButton){
							cout << "Although i did find that button, should i push it?" << endl;
						}
					}
					else if (looking == "WEST"){
						cout << "I try pushing as hard as i can, yet... concrete, it's not like i'm The Hulk." << endl;
					}
				}
				if (word_2 == "BUTTON"){
					if (looking == "SOUTH" && foundButton){
						cout << "Oooh! I hear some sort of mechanism grinding somewhere around me... and... the ceiling might be coming down slowly...." << endl;
						SetConsoleTextAttribute(hConsole, red);
						cout << "Announcer:";
						SetConsoleTextAttribute(hConsole, black);
						cout << " Ooops! Your actions got the test subject killed. Ah well better luck next time, am i right?" << endl;
						alive = false;
					}
				}
			}
			else if (word_1 == "I'M"){
				if (word_2 == "ARMANDO"){
					SetConsoleTextAttribute(hConsole, red);
					cout << "Announcer:";
					SetConsoleTextAttribute(hConsole, black);
					cout << " Well in that case... you win! Have fun, i'm out!" << endl;
					won = true;
				}
			}
			else if (word_1 == "DEV"){ //Testing stuff
				if (word_2 == "COLORS"){
					for (int k = 1; k < 255; k++)
					{
						SetConsoleTextAttribute(hConsole, k);
						cout << k << " I want to be nice today!" << endl;
					}
					SetConsoleTextAttribute(hConsole, black);
				}
			}
		}
		else if (!won && !alive){
			SetConsoleTextAttribute(hConsole, red);
			cout << "Announcer:";
			SetConsoleTextAttribute(hConsole, black);
			cout << " Dude, you killed our test subject, he can't do anything you say anymore... just restart already." << endl;
		}
		else{
			SetConsoleTextAttribute(hConsole, red);
			cout << "Announcer:";
			SetConsoleTextAttribute(hConsole, black);
			cout << " You won, you can go now! Or you can restart, but what's the fun in that?" << endl;
		}
		if (word_1 == "RESTART"){
			SetConsoleTextAttribute(hConsole, red);
			cout << "Announcer:";
			SetConsoleTextAttribute(hConsole, black);
			cout << " You have restarted, have fun ruining another test subjects life!" << endl;
			looking = "NORTH";
			foundButton = false;
			storyInitialized = false;
			alive = true;
		}

		cout << endl;

	}
	return 0;
}