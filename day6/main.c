

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

    int line_no = 0;
    long long race_time = 0;
    long long distance_to_beat = 0;
    const char delimiter = ' ';
    while (fgets(line, 256, f))
    {
        char buffer[256] = {0};
        for (int i = 0, j = 0; i < 256; ++i)
        {
            if (isdigit(line[i]))
            {
                buffer[j++] = line[i];
            }
        }
        long long number = atoll(buffer);

        if (line_no == 0)
        {
            race_time = number;
        }
        else
        {
            distance_to_beat = number;
        }
        line_no++;
    }

    long long combinations = 0;

    for (long long i = 0; i < race_time; ++i)
    {
        long long speed = i * BOAT_SPEED;

        long long distance = speed * (race_time - i);

        if (distance > distance_to_beat)
        {
            ++combinations;
        }
    }

    printf("%d\n", combinations);
}