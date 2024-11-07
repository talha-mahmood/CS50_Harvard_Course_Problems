// problem statement:Take name input from the user and then greet the user mentioning user's name
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string user_name = get_string("What is your name ");

    printf("hello, world %s\n", user_name);
}
