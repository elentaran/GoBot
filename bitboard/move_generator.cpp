
#include "move_generator.h"


const string move_generator::name() {
    return "Gobit";
}

const string move_generator::version() {
    return "0.1";
}


move_generator::move_generator() {

}

move_generator::move_generator(int nb_args, char* args[]) {

    _gameGoban = bitboard();
    _komi = DEFAULT_KOMI;
    clear();
    handleArguments(nb_args, args);
}

void move_generator::handleArguments(int nb_args, char* args[]) {
}


// Bot can think while waiting a command (opponent thinking)
void move_generator::ponder() {

    return ;
}


string move_generator::genmove(string player) {
    int iplayer=_gameGoban.playerToInt(player);
    return _gameGoban.genmove(iplayer);
}




void move_generator::play(string player, string move) {
    int iplayer=_gameGoban.playerToInt(player);
    int imove=_gameGoban.moveToInt(move);
    _gameGoban.play(lbit(imove),iplayer);
}


void move_generator::setSize(int boardsize) {
    //_gameGoban.setSize(boardsize);
}

void move_generator::show() {
    _gameGoban.showBoard();

}

void move_generator::clear() {
        _gameGoban.init();
        _gameGoban.setKomi(_komi);

}


void move_generator::setKomi(float komi) {
    _komi=komi;
    _gameGoban.setKomi(_komi);
}

void move_generator::setTimeLeft(int timeLeft) {
    _timeLeft = timeLeft;
}

void move_generator::undo() {

}

