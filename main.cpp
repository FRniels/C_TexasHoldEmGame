
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
        if (table[0] == nullptr)
        {
            return 26; // ALWAYS BLUFFING ON AN EMPTY TABLE, UNLESS THE HAND IS GOOD BY CHANCE
        }

        return 5; //Raise 5
        break;
    case LUC:
        return -1; //Fold
        break;
    case NIELS:
    {
        PokerRank rank = getMyHandRank(player->hand);

        if (rank.category < TWO_PAIR)
        {
            return -1;
        }
        else if (rank.category <= STRAIGHT)
        {
            // If some one raises with more than 25 while the table is empty, he could be bluffing or has a good hand
            // => Take a random chance to fold or raise half of what that player raised without caring about your own hand.
            if (game->highestBet > 25 && game->highestBet < 50 && table[0] == nullptr)
            {
                // printf("A player placed a bet >25 on an empty table\n");

                // Generate a random number between 0 and 1
                srand((unsigned int)time(NULL));
                if (rand() % (2) == 0)
                {
                    return -1; //Fold
                }
                else
                {
                    // printf("Placing half his bet: %d\n", (game->highestBet / 2));
                    return (game->highestBet / 2);
                }
            }
            else
            {
                return 0;
            }
        }
        // Place a higher bid when the hand is decent to very good, table empty or not empty
        else if (rank.category >= STRAIGHT && rank.category <= FLUSH)
        {
            return 10;
        }
        else if (rank.category > FLUSH)
        {
            return 25;
        }
    }
    default:
        return 1;
    }
}

int main(void)
{
    Game game;

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
    addPlayerToGame(&game, &veerle);
    addPlayerToGame(&game, &ine);
    addPlayerToGame(&game, &luc);
    addPlayerToGame(&game, &niels);

    // Create a new card deck and start the game.
    makeNewDeck(&game);
    playGame(&game, 2);

    std::cout << "The winner is = " << game.players[0]->name << std::endl;

    std::cout << "Press a key + enter to quit the game" << std::endl;
    getchar();
}
