#include<intrins.h>
void delayms(unsigned int t)
{
	unsigned int i,j;
	for(i=0;i<t;i++)
	{
		for(j=0;j<=100;j++)
		{
			_nop_();
		}
	}
}