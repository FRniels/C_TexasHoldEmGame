
#include <iostream>
#include <string.h>
#include "texasholdem.h"

enum WHO
{
    VEERLE,
    INE,
    LUC,
    NIELS
};

int willYouRaise(struct Game *game, struct Player *player, unsigned int totalBet)
{
    switch (player->ID)
    {
    case VEERLE:
        return 0; //Call
        break;
    case INE:
        return 5; //Raise 5
        break;
    case LUC:
        return -1; //Fold
        break;
    case NIELS:
    {
        PokerRank myRank = getMyHandRank(player->hand);
        if (myRank.category >= TWO_PAIR) //Heb NIELS een TWO PAIR of meer vast ?
        {
            return 10; //Raise 10
        }
        if (player->bet > 0 && table[0] == nullptr) //Ligt er nog niets op tafel ?
        {
            return 0; //Call
        }
        return -1; //Fold
        break;
    }
    }
    return 0;
}

int main(void)
{
    Game gg;

    Player veerle;
    veerle.ID = VEERLE;
    strcpy(veerle.name, "veerle");
    Player ine;
    ine.ID = INE;
    strcpy(ine.name, "ine");
    Player luc;
    luc.ID = LUC;
    strcpy(luc.name, "luc");
    Player niels;
    niels.ID = NIELS;
    strcpy(niels.name, "niels");

    // Add players to the game before starting a game.
    addPlayerToGame(&gg, &veerle);
    addPlayerToGame(&gg, &ine);
    addPlayerToGame(&gg, &luc);
    addPlayerToGame(&gg, &niels);

    // Create a new card deck and start the game.
    makeNewDeck(&gg);
    playGame(&gg, 1);

    std::cout << "The winner is = " << gg.players[0]->name << std::endl;
}