
#include <iostream>
#include <string.h>
#include "texasholdem.h"

#define FOLD -1
#define CALL 0

enum WHO
{
    VEERLE,
    INE,
    LUC,
    NIELS
};

// Note: Veerle seems the one to be winning most of the time!
int willYouRaise(struct Game *game, struct Player *player, unsigned int totalBet)
{
    PokerRank rank = getMyHandRank(player->hand);

    switch (player->ID)
    {
    case VEERLE: // Quick folder
        if (rank.category < STRAIGHT)
        {
            return FOLD;
        }
        else if (rank.category >= STRAIGHT && rank.category < FULL_HOUSE)
        {
            return CALL;
        }
        else
        {
            return 25;
        }
    case INE: // Bluffer: A high raise on an empty table, otherwise follow the high bet in all situations unless the hand is actually a good hand.
        if (table[0] == nullptr)
        {
            return 25; // ALWAYS BLUFFING ON AN EMPTY TABLE, UNLESS THE HAND IS GOOD BY CHANCE
        }
        else
        {
            if (rank.category >= FLUSH)
            {
                return 25;
            }

            return CALL;
        }
    case LUC: // Incremental better
        switch (rank.category)
        {
        case HIGH_CARD:
            return CALL;
        case ONE_PAIR:
            return 1;
        case TWO_PAIR:
            return 2;
        case THREE_OF_A_KIND:
            return 3;
        case STRAIGHT:
            return 4;
        case FLUSH:
            return 5;
        case FULL_HOUSE:
            return 6;
        case FOUR_OF_A_KIND:
            return 7;
        case STRAIGHT_FLUSH:
            return 8;
        default:
            return CALL;
        }
    case NIELS: // Semi random strategy
    {
        // PokerRank rank = getMyHandRank(player->hand);

        if (rank.category < TWO_PAIR)
        {
            return FOLD;
        }
        else if (rank.category <= STRAIGHT)
        {
            // If some one raises with more than 25 while the table is empty, he could be bluffing or has a good hand
            // => Take a random chance to fold or raise half of what that player raised without caring about your own hand.
            if (game->highestBet > 25 && game->highestBet < 50 && table[0] == nullptr)
            {
                // printf("A player placed a bet >25 on an empty table\n");

                // Generate a random number, 0 or 1
                srand((unsigned int)time(NULL));
                if (rand() % (2) == 0)
                {
                    return FOLD;
                }
                else
                {
                    // printf("Placing half his bet: %d\n", (game->highestBet / 2));
                    return (game->highestBet / 2);
                }
            }
            else
            {
                return CALL;
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
        return FOLD;
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
