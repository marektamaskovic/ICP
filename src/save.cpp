#include "save.h"


int save(std::string &filename, Game &g){
	std::cout << "save" << std::endl;
	json j;
	// datum?
	j["m"] = g.m;
	j["decks"] = json::array();

	for(int i = 0; i < 13; ++i){
		Deck &deck = *(g.decks[i]);
		json tmp;
		tmp["permissions"] = deck.permissions;
		tmp["cards"] = json::array();
	
		for(auto card = deck.cards.begin(); card != deck.cards.end(); card++){
			json c = {
				json::array({"color",card->color}),
				json::array({"number", card->number}),
				json::array({"visible", card->visible})
			};
			tmp["cards"] += c;
		}
		j["decks"] += tmp;

	}
	std::cout << ">" << filename << "<" << std::endl;
	std::ofstream save_file(filename);
	save_file << std::setw(2) << j << std::endl;

	save_file.close();

	return 0;
}