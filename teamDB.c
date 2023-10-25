#include <stdio.h>
#include <string.h>

/*
 * Author: Maya Al Hourani
 * Program that stores team data in a structure and manipulates it differently based on user input.
 */

//Team structure
struct team {
    int teamCode;
    char teamName[25];
    char teamSeeding[3];
    char teamUniform[8];
} teams[32];

void updateTeam(int x, struct team *teamPointer);

int main() {

    char userInput;

    //This is a counter variable which will be used as a master index in the structure, every time a team is made this is incremented.
    int teamsMade = 0;


    printf("******************\n* 2211 World Cup *\n******************\n");

    askOperation:;
    printf("Enter operation code:");
    scanf(" %c",&userInput);

    while (userInput != 'q') {

        //INSERT NEW TEAM COMMAND
        if (userInput == 'i') {
            //If structure is full
            if (teamsMade == 32){
                printf("Data base is full!\n");
                goto askOperation;
            }


            //****** TEAM CODE ********

            //Prompting for team code
            askTeamCode:;
            int teamCode; //placeholder variable to store team code and compare, before adding to structure.
            printf("\nEnter team code:");
            scanf(" %d%*c", &teamCode);

            //If the team code entered is not between 0-31, try again.
            if (teamCode > 31 || teamCode < 0){
                printf("Team code must be less than 31, try again. \n");
                goto askTeamCode;
            }

            //If the team code has already been used, try again.
            for (int i = 0; i < 31; i++) {
                if (teams[i].teamCode == teamCode && teamCode == 0 && i < teamsMade) {
                    printf("This code has already been used, enter a different code\n");
                    goto askTeamCode;
                } else if (teams[i].teamCode == teamCode && teamCode != 0) {
                    printf("This code has already been used, enter a different code\n");
                    goto askTeamCode;
                }
            }

            //inserting team if no errors occur.
            teams[teamsMade].teamCode = teamCode;


            //****** TEAM NAME ********

            askTeamName:;
            char teamName[25]; //placeholder variable to store team name and compare, before adding to structure.
            
            //Takes in a team name no longer than 25 characters.
            printf("Enter a team name: ");
            fgets(teamName, 25, stdin);


            //fgets function adds a new line character to the end of the string it scans, this for loop replaces the \n with a null character.
            for (int i = 0; i < strlen(teamName); i++){
                if (teamName[i] == '\n'){
                    teamName[i] = '\0';
                }
            }


            //Making sure team name doesn't already exist
            for (int i = 0; i < teamsMade; i++){
                if(strcmp(teams[i].teamName, teamName) == 0){
                    printf("This name is already use, try again.\n");
                    goto askTeamName;
                }
            }

            //inserting name if no errors occur.
            strcpy(teams[teamsMade].teamName, teamName);

            //****** TEAM SEEDING ********
            askTeamSeeding:;

            //placeholder variables to store team seeding and compare, before adding to structure.
            char seedingChar;
            char seedingInt;

            //Validity variables to make sure seeding is from A-H and between 1-4. It begins by assuming its false, meaning its invalid.
            int validChar = 0;
            int validInt = 0;

            //Array with letters and numbers seeding can be.
            char validNumbers[5] = "1234";
            char validCharacters[9] = "ABCDEFGH";

            //Takes in a team group seeding.
            printf("Enter group seeding:");
            scanf(" %c%c", &seedingChar,&seedingInt);

            //Checking to see if character is valid.
            for(int i = 0; i < 8; i++){
                if (seedingChar == validCharacters[i]){
                    validChar = 1;
                }
            }

            //Checking to see if number is valid.
            for(int i = 0; i < 4; i++){
                if (seedingInt == validNumbers[i]){
                    validInt = 1;
                }
            }

            //If seeding character or number is outside range A-H or 1-4.
            if (validChar == 0){
                printf("Invalid character for seeding, must be from A-H.\n");
                goto askTeamSeeding;
            }

            if(validInt == 0){
                printf("Invalid number for seeding, must be from 1-4.\n");
                goto askTeamSeeding;
            }


            //if the seeding is valid and unique, it stores it in structure.
            if (validInt == 1 && validChar == 1){
                char teamSeeding[3] = {seedingChar, seedingInt};
                strcpy(teams[teamsMade].teamSeeding, teamSeeding);
            }

            //****** TEAM UNIFORM COLOR ********

            askTeamUniform:;
            char teamColor; //placeholder variable to store team uniform to make sure its valid, before adding to structure.

            //Variables to ensure color is ROYGBIV. Valid starts as false until a match is found.
            char availableColors[5] = "ROYGBIV";
            int validColor = 0;


            //Takes in a character and stores it in team color.
            printf("Enter the kit colour:");
            scanf(" %c", &teamColor);

            for (int i = 0; i < 5; i++){
                if (teamColor == availableColors[i]){
                    validColor = 1;
                }
            }

            //If color entered is not valid
            if (validColor == 0){
                printf("The character you entered is not a colour, try again.\n");
                goto askTeamUniform;
            }

            //If color entered is valid
            if (validColor == 1){

                //Turning character to string equivalent to store in structure.
                if (teamColor == 'R'){
                    strcpy(teams[teamsMade].teamUniform,"Red");
                }

                if (teamColor == 'O'){
                    strcpy(teams[teamsMade].teamUniform,"Orange");
                }

                if (teamColor == 'Y'){
                    strcpy(teams[teamsMade].teamUniform,"Yellow");
                }

                if (teamColor == 'G'){
                    strcpy(teams[teamsMade].teamUniform,"Green");
                }

                if (teamColor == 'B'){
                    strcpy(teams[teamsMade].teamUniform,"Blue");
                }

                if (teamColor == 'I'){
                    strcpy(teams[teamsMade].teamUniform,"Indigo");
                }

                if (teamColor == 'V'){
                    strcpy(teams[teamsMade].teamUniform,"Violet");
                }
            }

            //Loops back to start when done, and increments index to track number of teams made.
            teamsMade++;
            goto askOperation;
        }


        //SEARCH COMMAND
        else if (userInput == 's'){
            //User inputted team code variable and and boolean integer variable to exit if team is not found(starts at false).
            int userCode;
            int codeFound = 0;

            printf("Enter team code:");
            scanf(" %d", &userCode);

            //Searching for team code in structure, if found its printed otherwise it returns user to operation page.
            for(int i = 0; i < teamsMade; i++){
                if (teams[i].teamCode == userCode){
                    codeFound = 1;
                    printf("\nTeam Code\t\tTeam Name\t\tGroup Seeding\t\tPrimary Kit Colour\n");
                    printf("%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\n",teams[i].teamCode,teams[i].teamName,teams[i].teamSeeding,teams[i].teamUniform);
                }
            }

            //If not found
            if (codeFound == 0){
                printf("No team with the entered team code was found.\n");
                goto askOperation;
            }

            //Loops back to start when done
            goto askOperation;
        }

        //UPDATE COMMAND
        else if (userInput == 'u'){
            //User inputted team code variable and boolean integer variable to exit if team is not found(starts at false).
            int teamFound = 0;
            int userCode;

            printf("Enter team code:");
            scanf(" %d", &userCode);
            scanf("%*c"); //this is to remove white space that might accidentally be scanned by updateTeam function.

            //If team is found, it calls the update function to update it.
            for(int i = 0; i < teamsMade; i++){
                if (teams[i].teamCode == userCode){
                    updateTeam(i,teams);
                    teamFound = 1;
                }
            }

            //if team is not found, user is told error and returned to main page.
            if (teamFound == 0){
                printf("No team with the entered team code was found.\n");
                goto askOperation;
            }
            //Loops back to start when done
            goto askOperation;
        }

        //PRINT COMMAND
        else if (userInput == 'p'){
            printf("\nTeam Code\t\tTeam Name\t\tGroup Seeding\t\tPrimary Kit Colour\n");

            for(int i = 0; i < teamsMade; i++){
                printf("%d\t\t\t%s\t\t\t%s\t\t\t%s\t\t\n",teams[i].teamCode,teams[i].teamName,teams[i].teamSeeding,teams[i].teamUniform);
            }

            //Loops back to start when done
            goto askOperation;
        }

        else {

        }
    }


    return 0;
}
    //This function is used in the update command, it is basically the same format as the insert command,
    //just put into a function to be called when a team needs to be updated.
    void updateTeam(int x, struct team teams[32]) {
        askTeamName:;
        char teamName[25]; //placeholder variable to store team name and compare, before adding to structure.

        //Takes in a team name no longer than 25 characters.
        printf("\nEnter a team name: ");
        fgets(teamName, 25, stdin);

        //fgets function adds a new line character to the end of the string it scans, this for loop replaces the \n with a null character.
        for (int i = 0; i < strlen(teamName); i++) {
            if (teamName[i] == '\n') {
                teamName[i] = '\0';
            }
        }


        //Making sure team name doesn't already exist
        for (int i = 0; i < x; i++) {
            if (strcmp(teams[i].teamName, teamName) == 0) {
                printf("This name is already use, try again.\n");
                goto askTeamName;
            }
        }

        //inserting name if no errors occur.
        strcpy(teams[x].teamName, teamName);

        //****** TEAM SEEDING ********
        askTeamSeeding:;

        //placeholder variables to store team seeding and compare, before adding to structure.
        char seedingChar;
        char seedingInt;

        //Validity variables to make sure seeding is from A-H and between 1-4. It begins by assuming its false, meaning its invalid.
        int validChar = 0;
        int validInt = 0;

        //Array with letters and numbers seeding can be.
        char validNumbers[5] = "1234";
        char validCharacters[9] = "ABCDEFGH";

        //Takes in a team group seeding.
        printf("Enter group seeding:");
        scanf(" %c%c", &seedingChar, &seedingInt);

        //Checking to see if character is valid.
        for (int i = 0; i < 8; i++) {
            if (seedingChar == validCharacters[i]) {
                validChar = 1;
            }
        }

        //Checking to see if number is valid.
        for (int i = 0; i < 4; i++) {
            if (seedingInt == validNumbers[i]) {
                validInt = 1;
            }
        }

        //If seeding character or number is outside range A-H or 1-4.
        if (validChar == 0) {
            printf("Invalid character for seeding, must be from A-H.\n");
            goto askTeamSeeding;
        }

        if (validInt == 0) {
            printf("Invalid number for seeding, must be from 1-4.\n");
            goto askTeamSeeding;
        }


        //if the seeding is valid and unique, it stores it in structure.
        if (validInt == 1 && validChar == 1) {
            char teamSeeding[3] = {seedingChar, seedingInt};
            strcpy(teams[x].teamSeeding, teamSeeding);
        }

        //****** TEAM UNIFORM COLOR ********

        askTeamUniform:;
        char teamColor; //placeholder variable to store team uniform to make sure its valid, before adding to structure.

        //Variables to ensure color is ROYGBIV. Valid starts as false until a match is found.
        char availableColors[5] = "ROYGBIV";
        int validColor = 0;


        //Takes in a character and stores it in team color.
        printf("Enter the kit colour:");
        scanf(" %c", &teamColor);

        for (int i = 0; i < 5; i++) {
            if (teamColor == availableColors[i]) {
                validColor = 1;
            }
        }

        //If color entered is not valid
        if (validColor == 0) {
            printf("The character you entered is not a colour, try again.\n");
            goto askTeamUniform;
        }

        //If color entered is valid
        if (validColor == 1) {

            //Turning character to string equivalent to store in structure.
            if (teamColor == 'R') {
                strcpy(teams[x].teamUniform, "Red");
            }

            if (teamColor == 'O') {
                strcpy(teams[x].teamUniform, "Orange");
            }

            if (teamColor == 'Y') {
                strcpy(teams[x].teamUniform, "Yellow");
            }

            if (teamColor == 'G') {
                strcpy(teams[x].teamUniform, "Green");
            }

            if (teamColor == 'B') {
                strcpy(teams[x].teamUniform, "Blue");
            }

            if (teamColor == 'I') {
                strcpy(teams[x].teamUniform, "Indigo");
            }

            if (teamColor == 'V') {
                strcpy(teams[x].teamUniform, "Violet");
            }
        }
    }
