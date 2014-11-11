#include <wiringPi.h>
#include <cs50.h>
#include <stdio.h>

int main (void)
{
   unsigned int m_sec[4], freq[4];
//   printf("How many ports do you want to activate?:\n");
   int i = 0;
   for (i = 0; i < 4; i++)
   {
      printf("Pls input a freq:\n");
      freq[i] = GetInt();
      printf("Frequency: %d Hz\n", freq[i]);
      m_sec[i] = 500/freq[i];
      printf("Time is %d ms\n", m_sec[i]);
   }

//   printf("time is %.1f mili second.\n", m_sec);
   

   printf("GPIO now is active!\n");
   wiringPiSetup () ;
   pinMode (0, OUTPUT) ;

   while(1)
   {
      digitalWrite (0, HIGH);
      //delay (m_sec[2]) ;
      digitalWrite (0,  LOW);
      //delay (m_sec[2]) ;
   }

    return 0 ;
}
