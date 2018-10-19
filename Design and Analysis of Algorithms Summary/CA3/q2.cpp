#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#define ll long long
#define N 210000
using namespace std;
struct node{int x,y,v,id;}e[N];
int n,m,i,id[N],ans[N],v[N],fa[N],size[N],a,b,maxx;
ll sum;
bool cmp(node x,node y){return x.v<y.v;}
int read()
{
	int x=1;char ch=getchar();
	while (ch<'0'||ch>'9') ch=getchar();
	while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}
int main()
{
	scanf("%d %d",&n,&m);
	for (i=1;i<=m;i++)
	{
		scanf("%d %d %d",&e[i].x,&e[i].y,&e[i].v);
		e[i].id=i;
	}
	sort(e+1,e+1+m,cmp);
	for (i=1;i<=n;i++) fa[i]=i,size[i]=1;
	for (i=1;i<=m;i++)
	{
		a=e[i].x,b=e[i].y,maxx=0;
		while ((a!=fa[a]||b!=fa[b])&&a!=b)
		{
			if (b==fa[b]||(a!=fa[a]&&size[a]<size[b])) maxx=max(v[a],maxx),a=fa[a];
			else maxx=max(maxx,v[b]),b=fa[b];
		}
		if (a==b)
		{
			ans[e[i].id]=e[i].v-maxx;
			continue;
		}
		if (size[a]>size[b]) swap(a,b);
		fa[a]=b;v[a]=e[i].v;size[b]+=size[a];sum+=e[i].v;
	}
	for (i=1;i<=m;i++) printf("%lld ",sum+ans[i]);
}
