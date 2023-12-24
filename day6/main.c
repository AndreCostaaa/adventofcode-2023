

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define BOAT_SPEED 1
typedef struct
{
    int race_time_ms;
    int distance_to_beat;
    int combinations_that_beat;
} race_t;

typedef struct node
{
    race_t race;
    struct node *next;
} node_t;
void append(node_t *head, node_t *node)
{
    if (!head)
    {
        return;
    }
    node_t *prev = NULL;
    node_t *curr = head;
    while (curr)
    {
        prev = curr;
        curr = curr->next;
    }
    prev->next = node;
}
int main(void)
{
    FILE *f = fopen("sample.txt", "r");

    char line[256];
    node_t *head;

    int i = 0;
    const char delimiter = ' ';
    while (fgets(line, 256, f))
    {

        char *token = strtok(line, &delimiter);
        int race = 0;
        while (token != NULL)
        {

            if (isdigit(*token))
            {
                if (i == 0)
                {
                    node_t *node = calloc(1, sizeof(node_t));

                    node->race.race_time_ms = atoi(token);
                    if (!head)
                    {
                        head = node;
                    }
                    else
                    {
                        append(head, node);
                    }
                }
                else
                {
                    node_t *node = head;
                    for (int i = 0; i < race && node; ++i)
                    {
                        node = node->next;
                    }

                    node->race.distance_to_beat = atoi(token);
                }

                ++race;
            }
            token = strtok(NULL, &delimiter);
        }
        ++i;
    }

    node_t *curr = head;
    int combinations = 1;
    while (curr)
    {

        for (int i = 0; i < curr->race.race_time_ms; ++i)
        {
            int speed = i * BOAT_SPEED;

            int distance = speed * (curr->race.race_time_ms - i);

            if (distance > curr->race.distance_to_beat)
            {
                ++curr->race.combinations_that_beat;
            }
        }
        combinations *= curr->race.combinations_that_beat;
        curr = curr->next;
    }
    printf("%d\n", combinations);
}