#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];
    people[0].name = "Carter";
    people[0].number = "+1-512-435-3256";

    people[1].name = "David";
    people[1].number = "+1-987-412-1256";

    string s = get_string("Name: ");
    for (int i = 0; i < 2; i++) // no segmentation fault tripped over
    {
        if (strcmp(people[i].name, s) == 0) // will compare strings and s arrays
        {
            printf("Found: %s\n", people[i].number);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
