//====if语句
if(表达式)语句;

if(表达式)
	语句1;
else
	语句2;

if(表达式1)			语句1;
else if(表达式2)	语句2;
else if(表达式3)	语句3;
......
else				语句n;

//====switch语句
switch(表达式)
{
	case 常量1:语句1;break;
	case 常量2:语句2;break;
	......
	case 常量n:语句n;break;
	default:   语句n+1;break;
}

//====循环语句
for(i=i0;i<=imax;i++)

while(条件)

break		跳出条件（循环）体
continue;	跳出循环体的本次循环