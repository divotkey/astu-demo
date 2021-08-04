/** 
 * Example Application: A Number guessing game
 * @file main.cpp
 * @version 1.0.0
 * @author Roman Divotkey
 * @copyright MIT License
 */

#include <AstUtils.h>

// Main entry point.
int main()
{
    int number = GetRandomInt(1, 101);
    int cnt = 0;
    int value;
    do {
        ++cnt;
        value = AskInt("Pick a number between 1 and 100: ");
        if (value < number) {
            SayText("Your guess is too low");
        } else if (value > number) {
            SayText("Your guess is too high");
        }
    } while (value != number);
    SayText("It took you ", false);
    SayInt(cnt, false);
    SayText(" turns to guess my number, which was ", false);
    SayInt(number);

    return 0;
}