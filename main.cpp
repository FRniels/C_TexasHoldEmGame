
#include <iostream>
#include <string.h>
#include "texasholdem.h"

enum WHO
{
    BLOB,
    SHREK,
    STEVEN,
    IK
};

int willYouRaise(struct Game *game, struct Player *player, unsigned int totalBet)
{
    switch (player->ID)
    {
    case BLOB:
        return 0; //Call
        break;
    case SHREK:
        return 5; //Raise 5
        break;
    case STEVEN:
        return -1; //Fold
        break;
    case IK:
    {
        PokerRank myRank = getMyHandRank(player->hand);
        if (myRank.category >= TWO_PAIR) //Heb ik een TWO PAIR of meer vast ?
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

    Player blob;
    blob.ID = BLOB;
    strcpy(blob.name, "Blob");
    Player shrek;
    shrek.ID = SHREK;
    strcpy(shrek.name, "Shrek");
    Player steven;
    steven.ID = STEVEN;
    strcpy(steven.name, "Steven");
    Player ikke;
    ikke.ID = IK;
    strcpy(ikke.name, "DIT BEN IK !!!");

    addPlayerToGame(&gg, &blob);
    addPlayerToGame(&gg, &shrek);
    addPlayerToGame(&gg, &steven);
    addPlayerToGame(&gg, &ikke);

    makeNewDeck(&gg);
    playGame(&gg, 1);

    std::cout << "The winner is = " << gg.players[0]->name << std::endl;
}