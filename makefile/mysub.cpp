#include<iostream>
using namespace std;
void Sumtop(int &sum,int &top)
{
  for(int i =0;i<top;++i)
  {
    sum += i;
  }
}
int main()
{
  int sum = 0;
  int top = 100;
  Sumtop(sum,top);
  cout<<sum<<endl;
}
