#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CARD_NUMBERS 5
#define WINNING_NUMBERS 8
typedef struct
{
    int numbers[CARD_NUMBERS];
    int winning_numbers[WINNING_NUMBERS];
    int won;
    int copies;
} card_t;

typedef struct node
{
    card_t card;
    struct node *next;
} node_t;
int main(void)
{
    FILE *f = fopen("sample.txt", "r");

    char line[256];
    node_t *head;
    67 while (fgets(line, 256, f))
    {
        node_t *node = malloc(sizeof(node_t));

        char *begin = strchr(line, ':') + 2;
        for (int i = 0; i < CARD_NUMBERS; ++i)
        {
            node->card.numbers[i] = atoi(begin);
            begin += 3;
        }
        begin = strchr(line, '|') + 2;
        for (int i = 0; i < WINNING_NUMBERS; ++i)
        {
            node->card.winning_numbers[i] = atoi(begin);
            begin += 3;
        }
        node->card.copies = 1;
        node->card.won = 0;
        node->next = head;
        head = node;
    }
    node_t *ptr = head;
    int sum = 0;

    while (ptr)
    {
        int num = 0;
        for (int i = 0; i < CARD_NUMBERS; ++i)
        {
            for (int j = 0; j < WINNING_NUMBERS; ++j)
            {
                if (ptr->card.numbers[i] == ptr->card.winning_numbers[j])
                {
                    num++;
                    break;
                }
            }
        }
        ptr->card.won = num;
        sum += ptr->card.won * ptr->card.copies;
        node_t *optr = ptr->next;

        while (optr && num--)
        {
            optr->card.copies++;
            optr = optr->next;
        }
        ptr = ptr->next;
    }
    printf("%d\n", sum);
}