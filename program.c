//***************************************************
//* Programmer: Emil Gram Jensen
//* Class: Software (Gruppe 8)
//* Programming Assignment: Eksamensopgave 3
//* Date: 28/11/21
//***************************************************

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

// CONSTANTS
#define MATCHES 132
#define TEAMS 12

//PROTOTYPES
void clear_console();
void get_matches_from_file();
int exits_in_array();
int add_match_to_array();

// STRUCTS
typedef struct
{
    char *name[1];
    int goals;
    int goals_against;
    int point;
} Team;

typedef struct
{
    int goals;
    char name[4];
} MatchTeam;

typedef struct
{
    char weekday[5];
    char date[10];
    char time[10];
    MatchTeam home_team;
    MatchTeam away_team;
    int viewers;
} Match;

int main(void)
{
    srand(time(NULL));
    Match matches[MATCHES];
    Team teams[TEAMS];

    clear_console();
    get_matches_from_file(matches, teams);
}

/************************************************************
 * Function: get_matches_from_file()					     
 * Description: Gets the match history from the data-file.
 * Input parameters: 			 
 * Returns: 
 *************************************************************/
void get_matches_from_file(Match matches[], Team teams[])
{

    FILE *fp = fopen("kampe-2020-2021.txt", "r");

    if (fp)
    {

        Match m;
        int i = 0, team = 0;

        while (fscanf(fp, "%s %s %s %s - %s %d - %d %d", m.weekday, m.date, m.time, m.home_team.name, m.away_team.name, &m.home_team.goals, &m.away_team.goals, &m.viewers) == 8)
        {

            team += add_match_to_array(matches, m, i, team, teams);
            i++;
        }

        fclose(fp);
    }
}

/************************************************************
 * Function: add_match_to_array()					     
 * Description: Adds the match to the array over matches.
 * Description: Adds the team to the array of teams if not exits.
 * Input parameters: 			 
 * Returns: 
 *************************************************************/
int add_match_to_array(Match matches[], Match m, int i, int team, Team teams[])
{

    matches[i] = m;

    int exits = exits_in_array(teams, matches[i].home_team.name, team);

    if (exits == -1)
    {
        teams[team].name[0] = matches[i].home_team.name;
        teams[team].goals = matches[i].home_team.goals;
        teams[team].goals_against = matches[i].away_team.goals;

        return 1;
    }

    teams[exits].goals += m.home_team.goals;
    teams[exits].goals_against += m.away_team.goals;

    return 0;
}

/************************************************************
 * Function: exits_in_array()					     
 * Description: Check if the teams already exits
 * Input parameters: 			 
 * Returns: 
 *************************************************************/
int exits_in_array(Team teams[], char *name, int team)
{

    for (int i = 0; i < team; i++)
    {

        if (strcmp(teams[i].name[0], name) == 0)
        {
            return i;
        }
    }

    return -1;
}

/************************************************************
 * Function: clear_console()					     
 * Description: Clears the console
 * Input parameters: none			 
 * Returns: none
 *************************************************************/
void clear_console()
{
#ifdef _WIN32
    system("cls");
#else //In any other OS
    system("clear");
#endif
}