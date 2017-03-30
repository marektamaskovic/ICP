#include <iostream>
#include <regex>

#include "core.h"

command_t* parseCMD(std::string &cmdBuffer){

	command_t *cmd = new command_t;

	std::string::size_type n,l;
	std::string arg_buff = "";

	n = cmdBuffer.find_first_of("(");
	l = cmdBuffer.find_first_of(")");

	n++;

	if( (n-l) > 1){
		arg_buff = cmdBuffer.substr(n, l-n);

		std::regex words_regex("[^,\\ ]+");
		auto words_begin =
			std::sregex_iterator(arg_buff.begin(), arg_buff.end(), words_regex);
		auto words_end = std::sregex_iterator();

		std::cout << "Found "
			  << std::distance(words_begin, words_end)
			  << " words:\n";

		for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
			std::smatch match = *i;
			std::string match_str = match.str();
			cmd->args.push_back(match_str);
			std::cout << match_str << '\n';
		}

	}

	std::regex show_regex("show([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, show_regex) > 0){
		cmd->type = show;
		return cmd;
	}

	std::regex moveC_regex("moveCard([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, moveC_regex) > 0){
		cmd->type = moveCard;
		return cmd;
	}

	std::regex popQD_regex("popQueueDeck([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, popQD_regex) > 0){
		cmd->type = popQueueDeck;
		return cmd;
	}

	std::regex moveD_regex("moveDeck([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, moveD_regex) > 0){
		cmd->type = moveDeck;
		return cmd;
	}

	std::regex switchG_regex("switchGame([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, switchG_regex) > 0){
		cmd->type = switchGame;
		return cmd;
	}

	std::regex save_regex("save([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, save_regex) > 0){
		cmd->type = save;
		return cmd;
	}

	std::regex load_regex("load([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, load_regex) > 0){
		cmd->type = load;
		return cmd;
	}

	std::regex createGame_regex("createGame([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, createGame_regex) > 0){
		cmd->type = createGame;
		return cmd;
	}

	std::regex quitG_regex("quitGame([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, quitG_regex) > 0){
		cmd->type = quitGame;
		return cmd;
	}

	std::regex quit_regex("quit([A-z,\\ ]*)", std::regex::grep);
	if(std::regex_match(cmdBuffer, quit_regex) > 0){
		cmd->type = quit;
		return cmd;
	}

	cmd->type = noCMD;

	return cmd;
}

int resolveCmd(std::string &cmdBuffer){

	command_t *cmd = parseCMD(cmdBuffer);

	switch(cmd->type){
		case(createGame):
			std::cout << "CMD: createGame()," << std::endl;
			break;
		case(show):
			std::cout << "CMD: Show()," << std::endl;
			break;
		default:
			std::cout << "Command '" << cmdBuffer << "' is not valid command!\n";
			break;
	}

	delete(cmd);

	return 0;
}