
// Program to calculate the type effectiveness of the opposing pokemon and displayed as a readable table/GUI
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include <conio.h>
#include <exception>
using namespace std;
// Declarations //

/*Function when two types are provided, return an empty, size 0 vector if type entered could not be found in type dictionary */
vector<vector<string>> Calculate_Type_Effectiveness(string type1, string type2);
/*Function when one type is provided same as above*/
vector<vector<string>> Calculate_Type_Effectiveness(string type1);

/*Main*/
int main() {
	// Insert function to read in the pokemon types!
	bool B_quit = false;
	while (!B_quit)
	{
		cout << "\nPlease state if the opposing Pokemon is a dual type (press the letter 'D') or a monotype (press the letter 'M'): ";
		char T_num = _getch();
		string type1, type2;
		vector<vector<string>> vec;
		while (T_num != 'D' && T_num != 'M' && T_num != 'd' && T_num != 'm')
		{
			cout << "\nInvalid letter entered. Please try again!";
			T_num = _getch();
		}
		if (T_num == 'D' || T_num == 'd')
		{
			cout << "\nPlease enter the Pokemon's Types\nType 1 : ";
			getline(cin, type1);
			cout << "Type 2: ";
			getline(cin, type2);
			vec = Calculate_Type_Effectiveness(type1, type2);
		}
		else
		{
			cout << "\nPlease enter the Type: ";
			getline(cin, type1);
			vec = Calculate_Type_Effectiveness(type1);
			// test;
		}
		if (!vec.empty())
		{
			for (size_t i = 0; i < vec.size(); i++)
			{
				if (vec.at(i).empty()) // ensures the following switch statements are only printed if there is anything inside the vector types
					continue;
				switch (i)
				{
				case 0:
					cout << "Opponent is 2x weak to:" << endl;
					break;
				case 1:
					cout << "Opponent is 0.5x resistant to: " << endl;
					break;
				case 2:
					cout << "Opponent is not effected by: " << endl;
					break;
				case 3:
					cout << "Opponent is 4x weak to:" << endl;
					break;
				case 4:
					cout << "Opponent is 0.25x resistant to: " << endl;
					break;
				default:
					cout << "The size of the vector<vector<string>> was not equal to 5" << endl;
				}
				for (size_t j = 0; j < vec[i].size(); j++) // doesn't print empty vectors 
					cout << vec[i][j] << endl;
				cout << endl;
			}
		}
		cout << "Would you like to Try Again (press A) or quit (press Q): ";
		char quit = _getch();
		while (quit != 'A' && quit != 'a' && quit != 'q' && quit != 'Q')
		{
			cout << "\nInvalid letter entered. Please try again!";
			quit = _getch();
		}
		if (quit == 'Q' || quit == 'q')
		{
			B_quit = true;
		}
	}
	
}
/*Function to calcute type effectiveness when two types are provided, return an empty, size 0 vector if type entered could not be found in type dictionary*/
vector<vector<string>> Calculate_Type_Effectiveness(string type1, string type2) // error check before passing in with try block
{
	/*Basic error checking to ensure the input matches the dictionary*/
	transform(type1.begin(), type1.end(), type1.begin(), ::toupper); // get the string and make it all uppercase to match dictionary
	transform(type2.begin(), type2.end(), type2.begin(), ::toupper); // get the string and make it all uppercase to match dictionary
	bool error_in_type = false;
	vector<vector<string>> Calculated_Type_Matchup;
	vector<string> types{ type1, type2 }; // basic dictionary of given types
	vector<string> SuperEffective;
	vector<string> NotVeryEffective;
	vector<string> Ineffective;
	vector<string> UltraEffective;
	vector<string> Resistive;
	for (unsigned int i = 0; i < types.size(); i++)
	{
		if (types[i] == "NORMAL")
		{
			SuperEffective.push_back("Fighting");
			Ineffective.push_back("Ghost");
		}
		else if (types[i] == "FIGHTING")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fairy","Flying", "Psychic" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Dark", "Rock" });
		}
		else if (types[i] == "FLYING")
		{
			SuperEffective.insert(SuperEffective.end(), { "Electric","Ice", "Rock" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Fighting", "Grass" });
			Ineffective.push_back("Ground");
		}
		else if (types[i] == "POISON")
		{
			SuperEffective.insert(SuperEffective.end(), { "Ground", "Psychic" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fighting","Poison", "Bug","Grass","Fairy" });
		}
		else if (types[i] == "GROUND")
		{
			SuperEffective.insert(SuperEffective.end(), { "Grass","Ice", "Water" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Posion", "Rock" });
			Ineffective.push_back("Electric");
		}
		else if (types[i] == "ROCK")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fighting","Grass", "Ground", "Steel", "Water" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Flying", "Normal", "Poison" });
		}
		else if (types[i] == "BUG")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fire","Flying", "Rock" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Ground","Grass", "Fighting" });
		}
		else if (types[i] == "GHOST")
		{
			SuperEffective.insert(SuperEffective.end(), { "Dark","Ghost" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Poison" });
			Ineffective.insert(Ineffective.end(), { "Fighting", "Normal" });
		}
		else if (types[i] == "STEEL")
		{
			SuperEffective.insert(SuperEffective.end(), {"Fighting","Fire", "Ground"});
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fairy","Flying", "Psychic", "Bug","Dragon", "Grass","Ice","Normal","Rock","Steel" });
			Ineffective.push_back("Poison");
		}
		else if (types[i] == "FIRE")
		{
			SuperEffective.insert(SuperEffective.end(), { "Ground","Rock", "Water" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Fairy", "Fire", "Grass", "Ice","Steel" });
		}
		else if (types[i] == "WATER")
		{
			SuperEffective.insert(SuperEffective.end(), { "Electric","Grass" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Ice", "Steel", "Water" });
		}
		else if (types[i] == "GRASS")
		{
			SuperEffective.insert(SuperEffective.end(), { "Bug","Fire", "Flying", "Ice", "Poison" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Electric", "Grass", "Ground", "Water" });
		}
		else if (types[i] == "ELECTRIC")
		{
			SuperEffective.insert(SuperEffective.end(), {"Ground"});
			NotVeryEffective.insert(NotVeryEffective.end(), { "Electric","Flying", "Steel" });
		}
		else if (types[i] == "PSYCHIC")
		{
			SuperEffective.insert(SuperEffective.end(), { "Bug","Dark", "Ghost" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fighting","Psychic" });
		}
		else if (types[i] == "ICE")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fighting","Fire", "Rock","Steel" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Ice" });
		}
		else if (types[i] == "DRAGON")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fairy","Dragon", "Ice" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Water", "Electric", "Grass" });
		}
		else if (types[i] == "DARK")
		{
			SuperEffective.insert(SuperEffective.end(), { "Fairy","Bug", "Fighting" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Ghost","Dark"});
			Ineffective.push_back("Psychic");
		}
		else if (types[i] == "FAIRY")
		{
			SuperEffective.insert(SuperEffective.end(), { "Poison","Steel" });
			NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Dark", "Fighting" });
			Ineffective.push_back("Dragon");
		}
		else
		{
			cout << "ERROR: One of the types processed does not match the given dictionary" << endl;
			error_in_type = true;
			break;
		}

	}
	// Pass in the result 
	Calculated_Type_Matchup.push_back(SuperEffective);
	Calculated_Type_Matchup.push_back(NotVeryEffective);
	Calculated_Type_Matchup.push_back(Ineffective);
	/*Find duplicates and add them to 4x strong/ 0.25x weak to*/
	for (unsigned int i = 0; i < Calculated_Type_Matchup.size(); i++)
	{
		if (Calculated_Type_Matchup[i].empty())// don't do operation on empty vector
			continue;
		sort(Calculated_Type_Matchup[i].begin(), Calculated_Type_Matchup[i].end());// sort each effectiveness out
		map<string, int> dup;
		for_each(Calculated_Type_Matchup[i].begin(), Calculated_Type_Matchup[i].end(), [&dup, i](string val) 
			{ 
				if (i != 2)
					return dup[val]++;
				else
					return dup[val]--;
			}); // find each type in the map, and keep a count of them
		for (auto p : dup) 
		{
			// Store 4x and 0.25x effectiveness, checking each hasp map element
			if (p.second == 2)
			{
				vector<string>::iterator it = std::find(Calculated_Type_Matchup[i].begin(), Calculated_Type_Matchup[i].end(), p.first);
				if (it != Calculated_Type_Matchup[i].end())
				{
					Calculated_Type_Matchup[i].erase(it, it + 2);// remove duplicates
					if (i == 0)
						UltraEffective.push_back(p.first);
					else if (i == 1)
						Resistive.push_back(p.first);
				}
			}
			else if (p.second == -1)
			{
				for (int j = 0; j < 2; j++) // Remove anything that is in 'does not affect' in the super and half effective columns 
				{
					vector<string>::iterator it2 = std::find(Calculated_Type_Matchup[j].begin(), Calculated_Type_Matchup[j].end(), p.first);
					if (it2 != Calculated_Type_Matchup[j].end())
						Calculated_Type_Matchup[j].erase(it2);// remove duplicates
				}
			}
		}
	}
	// add the final two elements
	Calculated_Type_Matchup.push_back(UltraEffective);
	Calculated_Type_Matchup.push_back(Resistive);
	// Remove duplicates that are common between Super & NotVery Effective
	vector<string> v(Calculated_Type_Matchup[0].size() + Calculated_Type_Matchup[1].size());
	vector<string>::iterator neutral, st;

	neutral = set_intersection(Calculated_Type_Matchup[0].begin(),
		Calculated_Type_Matchup[0].end(),
		Calculated_Type_Matchup[1].begin(),
		Calculated_Type_Matchup[1].end(),
		v.begin());

	for (st = v.begin(); st != neutral; ++st)
	{
		for (int j = 0; j < 2; j++)
		{
			vector<string>::iterator it3 = std::find(Calculated_Type_Matchup[j].begin(), Calculated_Type_Matchup[j].end(), *st);
			if (it3 != Calculated_Type_Matchup[j].end())
				Calculated_Type_Matchup[j].erase(it3);// remove duplicates
		}
	}
	if (error_in_type) // return a 0 sized vector if type given is wrong
		Calculated_Type_Matchup.clear();
	return Calculated_Type_Matchup;
}

/*Function to calcute type effectiveness when one type is provided*/
vector<vector<string>> Calculate_Type_Effectiveness(string type1)
{
	transform(type1.begin(), type1.end(), type1.begin(), ::toupper); // get the string and make it all uppercase to match dictionary
	bool error_in_type = false;
	vector<vector<string>> Calculated_Type_Matchup;
	vector<string> SuperEffective;
	vector<string> NotVeryEffective;
	vector<string> Ineffective;
	vector<string> UltraEffective;
	vector<string> Resistive;
	if (type1 == "NORMAL")
	{
		SuperEffective.push_back("Fighting");
		Ineffective.push_back("Ghost");
	}
	else if (type1 == "FIGHTING")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fairy","Flying", "Psychic" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Dark", "Rock" });
	}
	else if (type1 == "FLYING")
	{
		SuperEffective.insert(SuperEffective.end(), { "Electric","Ice", "Rock" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Fighting", "Grass" });
		Ineffective.push_back("Ground");
	}
	else if (type1 == "POISON")
	{
		SuperEffective.insert(SuperEffective.end(), { "Ground", "Psychic" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fighting","Poison", "Bug","Grass","Fairy" });
	}
	else if (type1 == "GROUND")
	{
		SuperEffective.insert(SuperEffective.end(), { "Grass","Ice", "Water" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Posion", "Rock" });
		Ineffective.push_back("Electric");
	}
	else if (type1 == "ROCK")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fighting","Grass", "Ground", "Steel", "Water" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Flying", "Normal", "Poison" });
	}
	else if (type1 == "BUG")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fire","Flying", "Rock" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Ground","Grass", "Fighting" });
	}
	else if (type1 == "GHOST")
	{
		SuperEffective.insert(SuperEffective.end(), { "Dark","Ghost" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Poison" });
		Ineffective.insert(Ineffective.end(), { "Fighting", "Normal" });
	}
	else if (type1 == "STEEL")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fighting","Fire", "Ground" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fairy","Flying", "Psychic", "Bug","Dragon", "Grass","Ice","Normal","Rock","Steel" });
		Ineffective.push_back("Poison");
	}
	else if (type1 == "FIRE")
	{
		SuperEffective.insert(SuperEffective.end(), { "Ground","Rock", "Water" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Fairy", "Fire", "Grass", "Ice","Steel" });
	}
	else if (type1 == "WATER")
	{
		SuperEffective.insert(SuperEffective.end(), { "Electric","Grass" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Ice", "Steel", "Water" });
	}
	else if (type1 == "GRASS")
	{
		SuperEffective.insert(SuperEffective.end(), { "Bug","Fire", "Flying", "Ice", "Poison" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Electric", "Grass", "Ground", "Water" });
	}
	else if (type1 == "ELECTRIC")
	{
		SuperEffective.insert(SuperEffective.end(), { "Ground" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Electric","Flying", "Steel" });
	}
	else if (type1 == "PSYCHIC")
	{
		SuperEffective.insert(SuperEffective.end(), { "Bug","Dark", "Ghost" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fighting","Psychic" });
	}
	else if (type1 == "ICE")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fighting","Fire", "Rock","Steel" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Ice" });
	}
	else if (type1 == "DRAGON")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fairy","Dragon", "Ice" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Fire","Water", "Electric", "Grass" });
	}
	else if (type1 == "DARK")
	{
		SuperEffective.insert(SuperEffective.end(), { "Fairy","Bug", "Fighting" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Ghost","Dark" });
		Ineffective.push_back("Psychic");
	}
	else if (type1 == "FAIRY")
	{
		SuperEffective.insert(SuperEffective.end(), { "Poison","Steel" });
		NotVeryEffective.insert(NotVeryEffective.end(), { "Bug","Dark", "Fighting" });
		Ineffective.push_back("Dragon");
	}
	else
	{
		cout << "ERROR: One of the types processed does not match the given dictionary" << endl;
		error_in_type = true;
	}
	// Pass in the result 

	Calculated_Type_Matchup.push_back(SuperEffective);
	Calculated_Type_Matchup.push_back(NotVeryEffective);
	Calculated_Type_Matchup.push_back(Ineffective);
	if (error_in_type) // return a 0 sized vector if type given is wrong
		Calculated_Type_Matchup.clear();
	return Calculated_Type_Matchup;
}

