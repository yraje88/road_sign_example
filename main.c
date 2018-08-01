#include "roadSideExample.h"

int roadSideExample();

void roadSideExample_I_colour(float);
void roadSideExample_I_shape(float);
void roadSideExample_I_content(float);

void roadSideExample_O_message(char **);

int main(void)
{
    roadSideExample();
    for(int i = 0; i < 2; i++)
    {
        roadSideExample_I_colour(2.0);
        roadSideExample_I_shape(1.0);
        roadSideExample_I_content(1.0);
        roadSideExample();
    }
}

void roadSideExample_O_message(char ** out)
{
    printf("ANN output: %s\n", out);
}