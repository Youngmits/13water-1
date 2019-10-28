#include<bits/stdc++.h>
using namespace std;
static const int win_percent[10][3][14] = {
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   JUNK
      {  0,  0,  0,  0,  0,  0,  1,  1,  2,  2,  4,  7, 14, 33 },
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1 },
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   PAIR
      {  0, 46, 48, 50, 51, 54, 56, 60, 63, 68, 74, 81, 89, 97 },
      {  0,  2,  3,  4,  4,  5,  7,  8, 10, 12, 15, 19, 24, 33 },
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  2,  3 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   TWO_PAIRS
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,  0, 36, 37, 38, 40, 44, 46, 49, 54, 57, 62, 64,  0 },
      {  0,  0,  2,  3,  4,  4,  6,  7,  8, 10, 11, 13, 13,  0 } },
      { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   TWO_PAIRS
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,  0, 36, 37, 38, 40, 44, 46, 49, 54, 57, 62, 64,  0 },
      {  0,  0,  2,  3,  4,  4,  6,  7,  8, 10, 11, 13, 13,  0 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   TRIPLE
      {  0, 99, 99,100,100,100,100,100,100,100,100,100,100,100 },
      {  0, 63, 65, 69, 71, 72, 73, 73, 73, 74, 74, 75, 75, 75 },
      {  0, 11, 12, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   STRAIGHT
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,  0,  0,  0, 77, 78, 81, 83, 85, 87, 88, 90, 91, 92 },
      {  0,  0,  0,  0, 16, 17, 20, 22, 24, 26, 28, 32, 33, 36 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   FLUSH
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,  0,  0,  0,  0,  0, 93, 93, 93, 93, 94, 95, 97, 98 },
      {  0,  0,  0,  0,  0,  0, 36, 36, 37, 38, 40, 44, 49, 61 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   FULL_HOUSE
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0, 98, 98, 99, 99, 99,100,100,100,100,100,100,100,100 },
      {  0, 64, 67, 70, 71, 73, 75, 77, 80, 82, 85, 88, 91, 94 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   FOUR_OF_A_KIND
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,100,100,100,100,100,100,100,100,100,100,100,100,100 },
      {  0, 93, 94, 95, 95, 96, 96, 96, 97, 97, 98, 98, 98, 98 } },
    { // 1   2   3   4   5   6   7   8   9   10   J   Q   K   A   STRAIGHT_FLUSH
      {  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
      {  0,  0,  0,  0,100,100,100,100,100,100,100,100,100,  0 },
      {  0,  0,  0,  0, 98, 98, 99, 99, 99, 99, 99, 99,100,  0 } }
  };
int ma,L,M,N;
class Card
{
	public:
		int color;
		int num;
		Card()
		{
			color=num=0;
		 } 
};
bool cmp(Card a,Card b)
{
	return a.num>b.num;
}
class Player
{
	public:
		vector<Card> card,C;
		vector<int> V5;
		vector<int> V3;
		vector<pair<int,int> > V;
	public:
		Player(){
		}
		void card_out()
		{
			int i;
			for(i=0;i<13;i++)
			cout<<card[i].num<<" ";
			cout<<endl;
			for(i=0;i<13;i++)
			cout<<card[i].color<<" ";
		}
		inline int count(int x)
		{
			int cnt=0;
			while(x)
			{
				cnt+=x&1;
				x>>=1;
			}
			return cnt;
		}
		void group_card()
		{
			int i,j;
			for(i=1;i<(1<<13)-1;i++)
			{
				if(count(i)==5)
				V5.push_back(i);
				if(count(i)==3)
				V3.push_back(i);
			}
			pair<int,int> p;
			for(i=0;i<V5.size();i++)
			{
				for(j=0;j<V3.size();j++)
				{
					if((V5[i]&V3[j])==0)
					{
						p.first=V5[i];
						p.second=V3[j];
						//cout<<p.first<<" "<<p.second<<endl;
						V.push_back(p);
					}
				}
			}
		}
		void Calculate_Card()
		{
			int i,f,s,t;
			pair<int,int> v1,v2,v3;
			for(i=0;i<V.size();i++)
			{
				int sum=0;
				f=V[i].first;s=V[i].second;t=(f|s)^((1<<13)-1);
				//if(f==4&&t==2&&s==1)
				//cout<<f<<" "<<t<<" "<<s;
				//f=1840;t=206;s=6145;
				v1=evaluate5(f);
				//cout<<v1.first<<" "<<v1.second<<endl;
				v2=evaluate5(t);
				//cout<<v2.first<<" "<<v2.second<<endl;
				v3=evaluate3(s);
				//cout<<v3.first<<" "<<v3.second<<endl;
				if(v1.first<v2.first||v2.first<v3.first)
				continue;
				if((v1.first==v2.first&&v1.second<=v2.second)||(v2.first==v3.first&&v2.second<=v3.second))
				continue;
				sum+=win_percent[v1.first][2][v1.second-1]+win_percent[v2.first][1][v2.second-1]+win_percent[v3.first][0][v3.second-1];
				//cout<<win_percent[v1.first][2][v1.second-1]<<" "<<win_percent[v2.first][1][v2.second-1]<<" "<<win_percent[v3.first][0][v3.second-1]<<endl;
				if(sum>ma)
				{
					//cout<<sum<<endl;
					ma=sum;
					L=f,M=t,N=s;
				}
			}
			player_out();
		 } 
		pair<int,int> evaluate5(int x)
		{
			int i,value;
			C.clear();
			for(i=0;i<13;i++)
			{
				if(x>>i&1)
				{
					C.push_back(card[i]);
				}
			}
			if(value=THS(C))
			return make_pair(9,value);
			if(value=ZD(C))
			return make_pair(8,value);
			if(value=HL(C))
			return make_pair(7,value);
			if(value=TH(C))
			return make_pair(6,value);
			if(value=SZ(C))
			return make_pair(5,value);
			if(value=ST(C))
			return make_pair(4,value);
			if(value=LD(C))
			return make_pair(3,value);
			if(value=ED(C))
			return make_pair(2,value);
			if(value=DZ(C))
			return make_pair(1,value);
			if(value=ZP(C))
			return make_pair(0,value);
		}
		pair<int,int> evaluate3(int x)
		{
			int i,value;
			C.clear();
			for(i=0;i<13;i++)
			{
				if(x>>i&1)
				{
					C.push_back(card[i]);
				}
			}
			if(value=ST(C))
			return make_pair(3,value);
			if(value=DZ(C))
			return make_pair(1,value);
			if(value=ZP(C))
			return make_pair(0,value);
		}
		int THS(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			int i;
			for(i=0;i<C.size()-1;i++)
			if(C[i].num-C[i+1].num!=1||C[i].color!=C[i+1].color)
			return 0;
			return C[0].num;
		}
		int ZD(vector<Card> &C)
		{
			int cnt[15]={0},i;
			for(i=0;i<C.size();i++)
			{
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++){
				if(cnt[i]==4)
				return i;
			}
			return 0;
		}
		int HL(vector<Card> &C)
		{
			int cnt[15]={0},i,f1=0,f2=0;
			for(i=0;i<C.size();i++)
			{
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++){
				if(cnt[i]==3)
				f1=i;
				if(cnt[i]==2)
				f2=i;
			}
			if(f1&&f2)
			return f1;
			return 0;
		}
		int TH(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			int i;
			for(i=0;i<C.size()-1;i++)
			if(C[i].color!=C[i+1].color)
			return 0;
			return C[0].num;
		}
		int SZ(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			int i;
			for(i=0;i<C.size()-1;i++)
			if(C[i].num-C[i+1].num!=1)
			return 0;
			return C[0].num;
		}
		int ST(vector<Card> &C)
		{
			int cnt[15]={0},i;
			for(i=0;i<C.size();i++){
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++)
			if(cnt[i]==3)
			return i;
			return 0;
		}
		int LD(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			int cnt[15]={0},i;
			vector<int> f;
			for(i=0;i<C.size();i++){
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++){
				if(cnt[i]==2)
				f.push_back(i);
			}
			if(f.size()==2&&f[1]-f[0]==1)
			return f[1];
			return 0;
		}
		int ED(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			int cnt[15]={0},i;
			vector<int> f;
			for(i=0;i<C.size();i++){
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++){
				if(cnt[i]==2)
				f.push_back(i);
			}
			if(f.size()==2)
			return f[1];
			return 0;
		}
		int DZ(vector<Card> &C)
		{
			int cnt[15]={0},i;
			for(i=0;i<C.size();i++){
				int k=C[i].num;
				cnt[k]++;
			}
			for(i=2;i<15;i++)
			if(cnt[i]==2)
			return i;
			return 0;
		}
		int ZP(vector<Card> &C)
		{
			sort(C.begin(),C.end(),cmp);
			return C[0].num;
		}
		void player_out()
		{
			//cout<<L<<" "<<M<<" "<<N<<" "<<ma<<endl;
			make_card(N);
			make_card(M);
			make_card(L);
		}
		void make_card(int x)
		{
			int i;
			//cout<<x<<endl;
			C.clear();
			for(i=0;i<13;i++)
			{
				if(x>>i&1)
				{
					C.push_back(card[i]);
				}
			}
			sort(C.begin(),C.end(),cmp);
			for(i=0;i<C.size();i++)
			{
				char A,B;
				if(C[i].num==11)
				A='J';
				else if(C[i].num==12)
				A='Q';
				else if(C[i].num==13)
				A='K';
				else if(C[i].num==14)
				A='A';
				else
				A=C[i].num+48;
				if(C[i].color==1)
				B='$';
				else if(C[i].color==2)
				B='&';
				else if(C[i].color==3)
				B='*';
				else
				B='#';
			   if(i==C.size()-1)
				{
					if(C[i].num==10)
					cout<<B<<10<<endl;
					else
					cout<<B<<A<<endl;
				}
				else
				{
					if(C[i].num==10)
					cout<<B<<10<<" ";
					else
					cout<<B<<A<<" ";
				}
			}
		}
};

int main(int argc, char *argv[])
{
	int i;
	Player P;
	for(i=0;i<strlen(argv[1]);i++)
	{
		Card c;
		if(argv[1][i]=='$')
		c.color=1;
		else if(argv[1][i]=='&')
		c.color=2;
		else if(argv[1][i]=='*')
		c.color=3;
		else
		c.color=4;
		i++;
		if(argv[1][i]=='1')
		{
			c.num=10;i++;
		}
		else if(argv[1][i]=='A')
		c.num=14;
		else if(argv[1][i]=='J')
		c.num=11;
		else if(argv[1][i]=='Q')
		c.num=12;
		else if(argv[1][i]=='K')
		c.num=13;
		else
		c.num=int(argv[1][i]-48);
		P.card.push_back(c);
	}
	//P.card_out();
	P.group_card();
	P.Calculate_Card();
	return 0;
}
 
