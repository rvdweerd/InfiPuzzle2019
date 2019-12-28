#include <set>
#include <vector>
#include <map>
#include <iostream>
#include <conio.h>

void Infi1()
{	// aoc.infi.nl 2019, deel 1
	// input
	std::vector<std::pair<int, int>> flats = { {3,3},{5,5},{9,6},{13,7},{15,9},{16,10},{18,9},{21,10},{23,3},{25,4},{28,5},{29,7},{30,8},{34,7},{37,9},{39,7},{41,8},{42,10},{43,9},{47,10},{48,10},{50,6},{52,7},{53,10},{56,6},{57,4},{58,6},{59,2},{62,2} };
	std::vector < std::pair<int, int>> sprongen = { {1,2},{3,1},{0,0},{1,2},{0,1},{1,0},{2,1},{1,0},{1,1},{2,1},{0,2},{0,1},{3,0},{2,2},{1,0},{1,1},{0,2},{0,0},{3,1},{0,0},{1,0},{1,1},{0,3},{2,0},{0,0},{0,2},{0,0},{2,0}, {1,2},{3,1},{0,0},{1,2},{0,1},{1,0},{2,1},{1,0},{1,1},{2,1},{0,2},{0,1},{3,0},{2,2},{1,0},{1,1},{0,2},{0,0},{3,1},{0,0},{1,0},{1,1},{0,3},{2,0},{0,0},{0,2},{0,0},{2,0} };

	// Maak map van alle hoogtes van de flats: KEY= positie x van flat, VALUE = hoogte
	std::map<int, int> hoogtes;
	for (auto p : flats) hoogtes[p.first] = p.second;

	// Initialiseer
	std::pair<int, int> pos = flats[0];
	int nSprongen = 0;

	// Main loop: voer sprong uit tot [vallen] of tot [successvol landen na laatste sprong]
	for (int i = 0; i < sprongen.size(); i++)
	{
		std::cout << "Positie: (" << pos.first << "," << pos.second << "). ";
		pos.first += sprongen[i].first + 1;
		pos.second += sprongen[i].second;
		auto landingsHoogte = hoogtes.find(pos.first);
		if (landingsHoogte != hoogtes.end() && landingsHoogte->second <= pos.second)
		{
			pos.second = landingsHoogte->second;
			nSprongen++;
			std::cout << "Succesvolle " << nSprongen << "e sprong naar (" << pos.first << "," << pos.second << ")" << std::endl;
		}
		else break;
	}
	if (nSprongen == sprongen.size()) std::cout << "success, nSprongen = " << nSprongen; else std::cout << "Fail na sprong: " << nSprongen << ", de kerstman valt dus bij sprong " << nSprongen + 1;
	std::cout << "\nDruk op toets..";
	std::cin.get();
}

struct Node
{
	std::pair<int, int> pos;
	std::pair<int, int> reachedWithJump;
	std::vector<Node*> nextFlats;
	int totalEnergyUsed;
};
bool kanVooruitLanden(std::pair<int, int> pos, std::pair<int, int> sprong, std::vector<std::pair<int, int>>& flats, std::map<int, int>& hoogtes)
{
	pos.first += sprong.first + 1;
	pos.second += sprong.second;
	auto landingsHoogte = hoogtes.find(pos.first);
	if (landingsHoogte != hoogtes.end() && landingsHoogte->second <= pos.second)
	{
		//pos.second = landingsHoogte->second;
		return true;
	}
	else return false;
}
void VulBoom(Node* node, std::vector<std::pair<int, int>>& flats, std::vector < std::pair<int, int>>& basisSprongen, std::map<int, int>& hoogtes)
{
	for (auto s : basisSprongen)
	{
		if (kanVooruitLanden(node->pos, s, flats, hoogtes))
		{
			std::pair<int, int> nextpos;
			nextpos.first = node->pos.first + s.first + 1;
			nextpos.second = hoogtes.find(nextpos.first)->second;
			int energy = s.first + s.second;

			if (node->nextFlats.size() == 0)
			{
				node->nextFlats.push_back(new Node({ nextpos,s, {}, node->totalEnergyUsed + energy }));
				//std::cout << "Stap (virgin): " << s.first << "," << s.second << std::endl;
			}
			else
			{
				bool exists = false;
				for (int i = 0; i < node->nextFlats.size(); i++)
				{
					if (node->nextFlats[i]->pos.first == nextpos.first && node->nextFlats[i]->pos.second == nextpos.second)
					{
						exists = true;
						if (node->totalEnergyUsed + energy <= node->nextFlats[i]->totalEnergyUsed)
						{
							delete node->nextFlats[i];
							node->nextFlats[i] = new Node({ nextpos,s, {}, node->totalEnergyUsed + energy });
							//std::cout << "Stap (added): " << s.first << "," << s.second << std::endl;

						}
					}
				}
				if (!exists)
				{
					node->nextFlats.push_back(new Node({ nextpos, s,{}, node->totalEnergyUsed + energy }));
				}
			}
		}
	}
	for (auto p : node->nextFlats)
	{
		VulBoom(p, flats, basisSprongen, hoogtes);
	}

}
void TraverseTree(Node* node, std::pair<int, int>& endpoint, std::set<int>& res)
{
	// Recursive function to reach all leafs
	if (node->pos.first == endpoint.first && node->pos.second == endpoint.second)
	{
		// FUNCTION CALL TO APPLY AT LEAFS
		int E = node->totalEnergyUsed;
		res.insert(E);
	}
	else
	{
		for (auto n : node->nextFlats)
		{
			TraverseTree(n, endpoint, res);
		}
	}
	return;
}

void Infi2()
{
	// aoc.infi.nl 2019, deel 2
	// Input
	std::vector<std::pair<int, int>> flats = { {3,3},{5,5},{9,6},{13,7},{15,9},{16,10},{18,9},{21,10},{23,3},{25,4},{28,5},{29,7},{30,8},{34,7},{37,9},{39,7},{41,8},{42,10},{43,9},{47,10},{48,10},{50,6},{52,7},{53,10},{56,6},{57,4},{58,6},{59,2},{62,2} };
	std::vector < std::pair<int, int>> basisSprongen = { {0,0},{0,1},{0,2 },{0,3},{0,4},{1,0},{1,1},{1,2},{1,3},{2,0},{2,1},{2,2},{3,0},{3,1},{4,0} };


	// Maak map van alle hoogtes van de flats: KEY= positie x van flat, VALUE = hoogte
	std::map<int, int> hoogtes;
	for (auto p : flats) hoogtes[p.first] = p.second;

	// Bouw een tree met alle pathways (Node is een struct met alle relevante data per node)
	Node* root = new Node({ flats[0], {}, {}, 0 });
	
	// Vul de boom m.b.v. recursie
	VulBoom(root, flats, basisSprongen, hoogtes);
	
	// Haal de set op met de energie voor alle mogelijke uitkomsten
	std::set<int> res;
	TraverseTree(root, flats.back(), res);
	std::cout << "\nSet met de benodigde energie voor alle mogelijke routes: ";
	for (int v : res) std::cout << v << ",";
	std::cout << "\nMinimum energie om op eindflat te komen: " << *res.begin();
	std::cout << "\nDruk op toets..";
	std::cin.get();

}

int main()
{
	// Leuke puzzel!
	// Deze oplossing maakt gebruik van een Tree met alle mogelijke routes die succesvol eindigen. 
	// De nodes bevatten relevante data, waaronder de energie die nodig was om op de node te kommen.
	// De leaves van de Tree bevatten dus de energie tot het eindpunt van die unieke route.

	// Code kan nog veel simpeler, maar simpel = moeilijk en tijd: geen 
	// Ik wilde nog een mooie visualisatie van de tree maken, maar tijd: geen
	// groeten! Rogier

	Infi1(); // deel 1 van de puzzel
	Infi2(); // deel 2
	return 0;
}