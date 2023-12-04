#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_R 12
#define MAX_G 13
#define MAX_B 14
typedef struct
{
    int r, g, b;
} cubes_shown_t;

typedef struct
{
    int id;
    cubes_shown_t max_cubes;
} game_t;

typedef struct node
{
    game_t game;
    struct node *next;
} node_t;

int get_game_id(const char *buf)
{
    char *begin = strchr(buf, ' ') + 1;
    return atoi(begin);
}
void get_max_cubes_shown(const char *buf, game_t *game)
{
    char *begin = strchr(buf, ':') + 2;
    while (1)
    {
        int shown = atoi(begin);
        begin = strchr(begin, ' ') + 1;

        int *data_to_change;
        switch (*begin)
        {
        case 'r':
            data_to_change = &game->max_cubes.r;

            break;
        case 'b':
            data_to_change = &game->max_cubes.b;
            break;
        case 'g':
            data_to_change = &game->max_cubes.g;
            break;
        default:
            assert(0);
        }

        if (*data_to_change < shown)
        {
            *data_to_change = shown;
        }
        char *poss_begin = strchr(begin, ',');
        char *other_poss_begin = strchr(begin, ';');
        if (poss_begin && other_poss_begin)
        {
            begin = poss_begin < other_poss_begin ? poss_begin : other_poss_begin;
        }
        else if (poss_begin)
        {
            begin = poss_begin;
        }
        else if (other_poss_begin)
        {
            begin = other_poss_begin;
        }
        else
        {
            break;
        }
        begin += 2;
    }
}
int main(void)
{

    FILE *f = fopen("sample.txt", "r");
    char line[256];
    node_t *head;
    while (fgets(line, sizeof(line), f))
    {
        node_t *node = malloc(sizeof(node_t));
        memset(node, 0, sizeof(node));
        node->game.id = get_game_id(line);
        get_max_cubes_shown(line, &node->game);
        node->next = head;
        head = node;
    }

    node_t *ptr = head;
    int sum = 0;
    int power_sum = 0;
    while (ptr)
    {
        int is_valid = ptr->game.max_cubes.r <= MAX_R && ptr->game.max_cubes.b <= MAX_B && ptr->game.max_cubes.g <= MAX_G;
        if (is_valid)
        {
            sum += ptr->game.id;
        }
        int max_sum = ptr->game.max_cubes.r * ptr->game.max_cubes.g * ptr->game.max_cubes.b;
        power_sum += max_sum;
        ptr = ptr->next;
    }
    printf("Sum: %d\n", sum);
    printf("Min Power: %d", power_sum);
    fclose(f);
}