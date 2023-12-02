#include <stdio.h>
#include <cs50.h>

string getName(void);
int getAge(void);
long getPhNum(void);
void cout(string a, int b, long c);

int main (void)
{
    string name = getName();
    int age = getAge();
    long ph = getPhNum();
    cout(name, age, ph);
}

string getName(void)
{
    string a = get_string("Enter name: ");
    return a;
}

int getAge(void)
{
    int a = get_int("Enter age: ");
    return a;
}

long getPhNum(void)
{
    long a = get_long ("Enter phone number: ");
    return a;
}

void cout(string a, int b, long c)
{
    printf("One entry\nName: %s\nAge: %i\nPhone: %li\n",a,b,c);
}