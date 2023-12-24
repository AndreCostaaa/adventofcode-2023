#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#define CARDS_PER_GAME 5
typedef struct
{
    char cards[CARDS_PER_GAME];
    int bid;
} game_t;

typedef struct
{
    game_t game;
    node_t *next;
} node_t;

typedef enum
{
    FiveOfAKind,
    FourOfAKind,
    FullHouse,
    ThreeOfAKind,
    TwoPair,
    OnePair,
    HighCard
} GameRank;

GameRank getGameRank(const game_t *game)
{
    int num_of_similar_cards[CARDS_PER_GAME] = {1};
    for (int i = 0; i < CARDS_PER_GAME; ++i)
    {
        for (int j = i + 1; j < CARDS_PER_GAME; ++j)
        {

            if (game->cards[i] == game->cards[j])
            {
                ++num_of_similar_cards[i];
                ++num_of_similar_cards[j];
            }
        }
    }
    GameRank curr_rank = FiveOfAKind;
    if (num_of_similar_cards[0] == CARDS_PER_GAME)
    {
        return FiveOfAKind;
    }
    if (num_of_similar_cards[0] == 4 || num_of_similar_cards[1] == 4)
    {
        return FourOfAKind;
    }
    int max = 1;
    for (int i = 0; i < CARDS_PER_GAME; ++i)
    {
        if (num_of_similar_cards[i] > max)
        {
            max = num_of_similar_cards[i];
        }
    }
    if (max == 1)
    {
        return HighCard;
    }
    if (max == 2)
    {
        int count = 0;
        for (int i = 0; i < num_of_similar_cards; ++i)
        {
            if (num_of_similar_cards[i] == 2)
            {
                count++;
            }
        }
        assert(count == 2 || count == 4);
        if (count == 2)
        {
            return OnePair;
        }
        return TwoPair;
    }
    if (max == 3)
    {
        int two_pair
    }
}
compare_games(const void *gameA, const void *gameB)
{
}
int main()
{
    char line[256];

    FILE *f = fopen("sample.txt", "r");

    node_t *head = NULL;
    int nolines = 0;
    for (char c = getc(f); c != EOF; c = getc(fp))
    {
        if (c == '\n')
        {
            ++nolines;
        }
    }

    game_t *games = malloc(sizeof(game_t) * nolines);
    rewind(f);
    int i = 0;
    while (fgets(line, 256, f))
    {
        memcpy(games[i].cards, line, CARDS_PER_GAME);
        games[i].bid = atoi(line + CARDS_PER_GAME + 1);
        ++i;
    }

    qsort((void *)games, nolines, sizeof(game_t), compare_games);

    int sum = 0;
    for (int i = 0; i < nolines; ++i)
    {
        int game_score = games[i].bid * (nolines - i);
        sum += game_score;
    }
    printf("%d\n", sum);
}