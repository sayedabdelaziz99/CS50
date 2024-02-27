#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
    int margin;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count = 0;
int candidate_count = 0;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count ; i++)
    {
        if (!strcmp(name, candidates[i]))
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        //getting candidate i rank in the ranks[] array and storing it in i_rank
        int i_rank = 0;
        while (i != ranks[i_rank])
        {
            i_rank++;
        }
        for (int j = 0; j < candidate_count; j++)
        {
            //getting candidate j rank in the ranks[] array and storing it in j_rank
            int j_rank = 0;
            while (j != ranks[j_rank])
            {
                j_rank++;
            }
            if (i_rank < j_rank)
            {
                preferences[i][j]++;
            }
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    int pair_num = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            while (i == j)
            {
                j++;
            }
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_num].winner = i;
                    pairs[pair_num].loser  = j;
                    pairs[pair_num].margin = preferences[i][j] - preferences[j][i];
                    pair_count++;
                    pair_num++;
                }
                else if(preferences[i][j] < preferences[j][i])
                {
                    pairs[pair_num].winner = j;
                    pairs[pair_num].loser  = i;
                    pairs[pair_num].margin = preferences[j][i] - preferences[i][j];
                    pair_count++;
                    pair_num++;
                }
            }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    int current_winner, current_loser, currnet_margin, new_winner, new_loser, new_margin;
    for (int i = 0; i < pair_count; i++)
    {
        int current_margin = pairs[i].margin;
        for (int j = i; j < pair_count; j++)
        {
            if (pairs[j].margin > current_margin)
            {
                new_winner = pairs[j].winner;
                new_loser  = pairs[j].loser;
                new_margin = pairs[j].margin;
                pairs[j]   = pairs[i];
                pairs[i].winner = new_winner;
                pairs[i].loser  = new_loser;
                pairs[i].margin = new_margin;
            }
        }
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        while (pairs[i].margin == 0)
        {
            i++;
        }
        if (i == (pair_count - 1) && pairs[i].loser == pairs[0].winner)
        {
            i++;
        }
        else
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int j = 0; j < pair_count; j++)
    {
        int true_count = 0;
        for (int i = 0; i < pair_count; i++)
        {
            if (locked[i][j] == true)
            {
                true_count++;
            }
            if (true_count == 0 && i == pair_count - 1)
            {
                printf("%s\n", candidates[j]);
            }
        }
    }
    return;
}
