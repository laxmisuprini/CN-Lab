#include<stdio.h>
#include<string.h>
//for encoding
int checksum1()
{
char in[100];
int buf[25];
int i,sum1=0,n,temp;
scanf("%s",in);
if(strlen(in)%2!=0)
        n=(strlen(in)+1)/2;
else
        n=(strlen(in))/2;
for(i=0;i<n;i++)
    {
temp=in[i*2];
temp=(temp*256)+in[(i*2)+1];
sum1=sum1+temp;
    }

if(sum1%65536!=0)
    {
        n=sum1%65536;
		sum1=(sum1/65536) + n;
    }
sum1=65535-sum1;
//printf("%x\n",sum1);
return sum1;
}

//for decoding
int checksum2()
{
char in[100];
int buf[25];
int i,sum2=0,n,temp;
scanf("%[^\n]s",in);
if(strlen(in)%2!=0)
        n=(strlen(in)+1)/2;
else
        n=(strlen(in))/2;
for(i=0;i<n;i++)
    {
		temp=in[i*2];
		temp=(temp*256)+in[(i*2)+1];
		sum2=sum2+temp;
    }
    
if(sum2%65536!=0)
    {
        n=sum2%65536;
		sum2=(sum2/65536) + n;
    }
sum2=65535-sum2;
//printf("Syndrome bit is: %x\n",sum2);
return sum2;
}


int main()
{
int ch,sum1,sum2;
do{
printf("1.Encode \n2.Decode \n3.Exit \n");
scanf("%d",&ch);
switch(ch)
        {

case 1: printf("Enter the string \n");
sum1=checksum1();
printf("Checksum to append is:%x \n",sum1);
break;
case 2: printf("Enter the string \n");
sum2=checksum2();
	if(sum1!=sum2){
		printf("The data has been tampered with or invalid checksum\n");
		printf("The syndrome bit is %x\n",sum2);	
	}
	else
		printf("The checksum is valid %x \n",sum2);
break;
case 3: break;
default: printf("Invalid option, try again \n");
        }
    }while(ch!=3);
}
