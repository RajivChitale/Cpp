#include<iostream>
#include<unistd.h>

#define W 50
#define H 20
#define T 30

using namespace std;

char randomchar()
{
 return (rand()%77) +48;
}


int oncein(int n)
{
  if ( ( rand()%n ) <1 ) return 1;
  else return 0;
}


int fillArray(char arr[W][H][T], int t, char c)
{
	for(int y=0; y<H; y++)
	{
		for(int x=0; x<W; x++)
		{
			arr[x][y][t] = c;
		}
	}
	return 0;
}

int enterMessage(char arr[W][H][T], string message)
{
	int y = H/2;
	int offset = (W-message.length() )/2;
	 ;
	for(int x=0; x<message.length(); x++)
	{
		arr[x+offset][y][0] = message[x];
	}	
	return 0;
}

int displayArrayInstance(char arr[W][H][T], int t)
{
	for(int y=0; y<H; y++)
	{
		for(int x=0; x<W; x++)
		{
			cout<< arr[x][y][t];
		}
		cout<<endl;
	}
	return 0;
}

int scrambleArray(char arr[W][H][T], int t)
{
	if(t<=0 || t>=T){return 1;}
	for(int y=0; y<H; y++)
	{
		for(int x=0; x<W; x++)
		{
			arr[x][y][t] = arr[x][y][t-1] ;
			if(oncein(T+t) == 1){arr[x][y][t] = ' ';}	//near t=0 there are more spaces-> oncein(x) where x is small
			if(oncein(2*T-2*t) == 1){arr[x][y][t] = randomchar();}	//near t=T there are more characters-> oncein(x) where x is small
		}
		cout<<endl;
	}
	return 0;	

}

int main()
{

	string message = "THIS IS JUST A DEMONSTRATION";

	char arr[W][H][T];
	fillArray(arr, 0, ' ');
	enterMessage(arr, message);
	
	//displayArrayInstance(arr, 0);
	
	for(int t=1; t<T; t++)
	{
		scrambleArray(arr, t);
	}

	for(int t=T-1; t>=0; t--)
	{
		system("clear");
		displayArrayInstance(arr, t);
		usleep(50000);
	}
		
	return 0;
}
