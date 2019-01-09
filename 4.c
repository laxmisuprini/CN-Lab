#include<stdio.h>
#define infinity 999
#define max 10
int dij(int G[max][max],int n,int startnode);
int main()
{
	int G[max][max],i,j,n,source;
	printf("Enter no.of vertices:");
	scanf("%d",&n);
	printf("\n enter the adjacency matrix:\n");
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	scanf("%d",&G[i][j]);
	printf("enter the starting node:");
	scanf("%d",&source);
	dij(G,n,source);
	return 0;
}
int dij(int G[max][max],int n,int startnode)
{
	int cost[max][max],distance[max],pred[max];//pred stores predessor of each node
	int visited[max],count,mindistance,nextnode,i,j;
	//creating cost matrix
	for(i=1;i<=n;i++)
	for(j=1;j<=n;j++)
	if(G[i][j]==0)
	cost[i][j]=infinity;
	else
	cost[i][j]=G[i][j];
	//initialise pred[],distance[],visited[]
	for(i=1;i<=n;i++)
	{
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}
	distance[startnode]=0;
	visited[startnode]=1;
	count=1;
	while(count<=n-1)
	{
		mindistance=infinity;
		//nextnode gives the node at minimum distance
		for(i=1;i<=n;i++)
		if(distance[i]<mindistance&&!visited[i])
		{
			mindistance=distance[i];
			nextnode=i;
		}
		//check if a better path exists through nextnode
		visited[nextnode]=1;
		for(i=1;i<=n;i++)
		if(mindistance+cost[nextnode][i]<distance[i]&&!visited[i])
		{
			distance[i]=mindistance+cost[nextnode][i];
			pred[i]=nextnode;
			}
			count++;	
	}
	//print the path and distance of each node
	for(i=1;i<=n;i++)
	if(i!=startnode)
	{
		printf("\n distance of node %d is %d",i,distance[i]);
		printf("\n path is %d",i);
		j=i;
		do{
			j=pred[j];
			printf("<--%d",j);
		}while(j!=startnode);
	}
}
