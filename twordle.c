//Kevin suarez
//project 10

#include <stdio.h>
#include <stdbool.h>

#define MAX_GUESSES 6
#define WORD_LEN 5

//prototypes
void loadword(char word[]);
void tolowercase(char str[]);
bool validguess(char str[]);
bool isletter(char c);
void processguess(char guess[], char mystery[], char output[], char pointer[]);
void printboard(char guesses[MAX_GUESSES][WORD_LEN+1],
                char outputs[MAX_GUESSES][WORD_LEN+1],
                char pointers[MAX_GUESSES][WORD_LEN+1],
                int count);
bool win(char output[]);

int main() {
char mystery[WORD_LEN + 1];
char guesses[MAX_GUESSES][WORD_LEN + 1];
char outputs[MAX_GUESSES][WORD_LEN + 1];
char pointers[MAX_GUESSES][WORD_LEN + 1];
int guessCount = 0;
bool won = false;
loadword(mystery);
while (guessCount < MAX_GUESSES && !won){
char guess[100];
printf("GUESS %d! Enter your guess: ", guessCount + 1);
scanf("%s", guess);
tolowercase(guess);
while (!validguess(guess)){
printf("Your guess must be 5 letters long.\n");
printf("Please try again: ");
scanf("%s", guess);
tolowercase(guess);
}
//store guess
for (int i = 0; i < WORD_LEN; i++){
guesses[guessCount][i] = guess[i];
}
guesses[guessCount][WORD_LEN] = '\0';
//process guess
processguess(guess, mystery,
outputs[guessCount],
pointers[guessCount]);
printf("================================\n");
printboard(guesses, outputs, pointers, guessCount + 1);
won = win(outputs[guessCount]);
guessCount++;
}
if (won) {
printf("\t\t");
for (int i = 0; i < WORD_LEN; i++){
printf("%c", mystery[i] - 32); 
}
printf("\n\tYou won in %d guesses!\n\t\tNice!\n", guessCount);
}
else{
printf("Out of guesses! The word was: %s\n", mystery);
}
return 0;
}
//Load word from file
void loadword(char word[]){
FILE *file = fopen("word.txt", "r");
fscanf(file, "%s", word);
fclose(file);
}
//Converting to lowercase
void tolowercase(char str[]){
for (int i = 0; str[i] != '\0'; i++){
if (str[i] >= 'A' && str[i] <= 'Z'){
str[i] += 32;
}
}
}
//check if char is letter
bool isletter(char c) {
return (c >= 'a' && c <= 'z');
}

bool validguess(char str[]){
int length = 0;
while (str[length] != '\0'){
if (!isletter(str[length])){
return false;
}
length++;
}
    return (length == WORD_LEN);
}
//process guess into output
void processguess(char guess[], char mystery[],
char output[], char pointer[]){
for (int i = 0; i < WORD_LEN; i++){
output[i] = guess[i];
pointer[i] = ' ';
if (guess[i] == mystery[i]){
 output[i] = guess[i] - 32; // uppercase
}
else{
for (int j = 0; j < WORD_LEN; j++){
if (guess[i] == mystery[j]){
pointer[i] = '^';
}
}
}
}
output[WORD_LEN] = '\0';
pointer[WORD_LEN] = '\0';
}
//print all guesses
void printboard(char guesses[MAX_GUESSES][WORD_LEN+1],
                char outputs[MAX_GUESSES][WORD_LEN+1],
                char pointers[MAX_GUESSES][WORD_LEN+1],
                int count){
for (int i = 0; i < count; i++){
printf("%s\n", outputs[i]);
printf("%s\n", pointers[i]);
}
}
//check win condition
bool win(char output[]){
for (int i = 0; i < WORD_LEN; i++){
if (output[i] < 'A' || output[i] > 'Z'){
return false;
}
}
return true;
}
