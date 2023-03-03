#include<bits/stdc++.h>
using namespace std;

//vector<int> adj[V];
class Graph
{
public:
  vector < int >bfsofgraph (int source, vector < int >adj[]);
    vector < int >dfsofgraph (int source, vector < int >adj[]);
private:
  void dfs (int node, vector < int >&res, vector < int >&vis,
	    vector < int >adj[]);
};

class Undirectedgraph
{
private:
  bool cycledetection (int node, int par, vector < int >&vis,
		       vector < int >adj[]);
public:
    bool isCycleundirected (int V, vector < int >adj[]);
    vector <int> dijiktras(int V, vector<vector<int>> adj2[], int S);
    
};

class directedgraph
{
public:
  vector < int >topoSort (int V, vector < int >adj1[]);
  bool isCycledirected (int V, vector < int >adj1[]);
  int kosaraju(int V, vector<int> adj1[]);
private:
  void revdfs(int node, vector<int> &vist , vector<int> transpose[]);
  void dfsofkosaraju(int node, vector<int> &vist, stack<int> &s, vector<int> adj[]);

};

void directedgraph::dfsofkosaraju(int node, vector<int> &vist, stack<int> &s, vector<int> adj[])
{
    vist[node]=1;
	for(auto it: adj[node])
	{
	    if(!vist[it])
	    {
	        dfsofkosaraju(it,vist,s,adj);
	    }
	}
	s.push(node);
}

void directedgraph::revdfs(int node, vector<int> &vist , vector<int> transpose[])
{
    vist[node]=1;
	for(auto it: transpose[node])
	{
	    if(!vist[it])
	    {
	        revdfs(it,vist,transpose);
	    }
	}
	//s.push(node);
}

int directedgraph::kosaraju(int V, vector<int> adj1[])
{
    vector<int> vist(V,0);
    stack<int> s;
    vector<int> transpose[V];
    for(int i=0;i<V;i++)
    {
        if(!vist[i])
        {
            dfsofkosaraju(i,vist,s,adj1);
        }
    }
    for(int i=0;i<V;i++)
    {
        vist[i]=0;
        for(auto it : adj1[i])
        {
            transpose[it].push_back(i);
        }
    }
    int component=0;
    while(!s.empty())
    {
        int temp=s.top();
        s.pop();
        if(!vist[temp])
        {
            component++;
            revdfs(temp,vist,transpose);
        }
    }
    return component;
}

vector <int> Undirectedgraph::dijiktras(int V, vector<vector<int>> adj2[], int S)
{
    // Code here
    priority_queue<pair<int,int> , vector<pair<int,int> >, greater<pair<int,int> > > pq;
    vector<int> dist(V,INT_MAX);
    dist[S]=0;
    pq.push(make_pair(0,S));//push node , distance into priority queue
    while(!pq.empty())
    {
        int distance = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        //vector<pair<int,int> > :: iterator it;
        for(auto it :adj2[node])
        {
            int v=it[0];
            int weight=it[1];
            if(dist[node] + weight < dist[v]){
            dist[v]=dist[node] + weight;
            pq.push(make_pair(dist[v] , v));
            }
        }
    }
    return dist;
}

bool directedgraph ::isCycledirected(int N, vector<int> adj1[]) {
    queue<int> q; 
	vector<int> indegree(N, 0); 
	for(int i = 0;i<N;i++) {
	   for(auto it: adj1[i]) {
	       indegree[it]++;
	   }
	}
	    
	for(int i = 0;i<N;i++) {
        if(indegree[i] == 0) {
	        q.push(i); 
	    }
	}
	int cnt = 0;
	while(!q.empty()) {
	    int node = q.front(); 
	    q.pop(); 
	    cnt++; 
	    for(auto it : adj1[node]) {
	        indegree[it]--;
	        if(indegree[it] == 0) {
	           q.push(it); 
	        }
	    }
	}
	if(cnt == N) return false; 
	return true; 
}

vector < int > directedgraph::topoSort (int V, vector < int >adj1[])
{
  vector < int >res;
  vector < int >indegree (V, 0);
  queue < int >q;
  for (int i = 0; i < V; i++)
    {
        for (auto it:adj1[i])
	    {
	       indegree[it]++;
	    }
    }

  for (int i = 0; i < V; i++)
    {
        if (indegree[i] == 0)
	    q.push (i);
    }
  while (!q.empty ())
    {
        int temp = q.front ();
        q.pop ();
        res.push_back (temp);
        for (auto it:adj1[temp])
	    {
	    indegree[it]--;
	    if (indegree[it] == 0)
	    q.push (it);
	    }
    }
  return res;
}

vector < int > Graph::bfsofgraph (int V, vector < int >adj[])
{
  vector < int >res;
  vector < int >vis (V + 1, 0);
  queue < int >q;
  q.push (0);
  vis[0] = 1;
  while (!q.empty ())
    {
        int temp = q.front ();
        q.pop ();
        res.push_back (temp);
        for (auto it:adj[temp])
	    {
	        if (!vis[it])
	        {
	            q.push (it);
	            vis[it] = 1;
	        }
	    }
    }
  return res;
}

void Graph::dfs (int node, vector < int >&res, vector < int >&vis,vector < int >adj[])
{
  res.push_back (node);
  vis[node] = 1;
    for (auto it:adj[node])
    {
        if (!vis[it])
	    dfs (it, res, vis, adj);
    }
}

vector < int > Graph::dfsofgraph (int V, vector < int >adj[])
{
  vector < int >res;
  vector < int >vis (V + 1, 0);
  dfs (0, res, vis, adj);
  return res;
}

bool Undirectedgraph::cycledetection (int node, int par, vector < int >&vis,
				 vector < int >adj[])
{
  vis[node] = 1;
for (auto it:adj[node])
    {
        if (!vis[it])
	    {
	        if (cycledetection (it, node, vis, adj))
	        return true;
	    }
        else if (vis[it] == 1 && it != par)
	    return true;
    }
  return false;

}

bool Undirectedgraph::isCycleundirected(int V, vector < int >adj[])
{
  vector < int >vis (V, 0);
  for (int i = 0; i < V; i++)
    {
        if (!vis[i])
	    {
	    if (cycledetection (i, -1, vis, adj))
	    return true;
	    }
    }
  return false;
}

int main ()
{
    Graph *graph;
    Undirectedgraph *g;
    directedgraph *g1;
    int choice;
    int V,E;
    vector < int >adj[1000];
    vector < int >adj1[1000];
    vector<vector<int>> adj2[1000];
    vector<vector<int>> adj3[1000];
    int source;
    while(1){
        cout<<endl<<"Enter 1 for BFS Traversal of Graph "<<endl;
        cout<<"Enter 2 for DFS Traversal of Graph "<<endl;
        cout<<"Enter 3 to find the cycle in undirected graph"<<endl;
        cout<<"Enter 4 for Topological sort of Graph "<<endl;
        cout<<"Enter 5 to find the cycle in directed Graph"<<endl;
        cout<<"Enter 6 for dijiktras algorith"<<endl;
        cout<<"Enter 7 for kosaraju algorithm to find no of strong components in the graph"<<endl;
        cout<<"Enter 8 to exit"<<endl;
        cout<<"Enter your choice"<<endl;
        cin>>choice;     
        
        if(choice==1||choice==2||choice==3||choice==4||choice==5||choice==7)
        {
            cout << "Enter the no of vertices";
            cin >> V;
            cout << "Enter the no of Edges";
            cin >> E;
            for (int i = 0; i < E; i++)
            {
                int u, v;
                cout << "enter u and v";
                cin >> u;
                cin >> v;
                //cin>>w;
                //graph->addEdge(adj,u,v);
                adj[u].push_back (v);
                adj[v].push_back (u);

                adj1[u].push_back (v);
            }            
        }
        else if(choice==8){
            exit(1);
            break;           
        }
        else if(choice==6) {
            cout << "Enter the no of vertices";
            cin >> V;
            cout << "Enter the no of Edges";
            cin >> E;
            for (int i = 0; i < E; i++)
            {
                int u, v,w;
                cout << "enter u and v and w";
                cin >> u;
                cin >> v;
                cin >> w;
                //cin>>w;
                //graph->addEdge(adj,u,v);
                adj2[u].push_back ({v,w});//undirected weighted graph
                adj2[v].push_back ({u,w});

               // adj3[u].push_back ({v,w});//directed weighted graph
            }                    
            
        }
        else{
            cout<<"Invalid choice"<<endl;
            exit(1);
            break;           
        }
        switch(choice){
            case 1:{
                //bfs  
                vector < int >ans = graph->bfsofgraph (V, adj);
                cout<<"Bfs traversal is:";
                for (int i = 0; i < ans.size (); i++)
                cout << ans[i];
                cout << endl;
                break;
            }
            
            case 2:{
                //dfs
                vector < int >res = graph->dfsofgraph (V, adj);
                cout<<"dfs traversal is:";
                for (int i = 0; i < res.size (); i++)
                cout << res[i];
                cout << endl;
                break;
            }
            
            case 3:{
                //is cyclic for Undirectedgraph
                bool b = g->isCycleundirected (V, adj);
                if (b)
                cout << "Yes there is a cycle in the graph ";
                else
                cout << "No there is no cycle in the graph";
                cout<<endl;
                break;
            }
            
            case 4:{
                vector < int >r = g1->topoSort (V, adj1);
                cout<<"Toposort is:";
                for (int i = 0; i < r.size (); i++)
                cout << r[i];
                cout << endl; 
                break;
            }
            
            case 5:{
                bool b1=g1->isCycledirected(V,adj1);
                if(b1) cout<<"Yes there is a cycle in the graph";
                else cout<<"No there is no cycle in the graph";
                cout<<endl;
                break;
            }
            
            case 6:{
                cout<<"Enter source Node"<<endl;
                cin>>source;
                vector<int> r4=g->dijiktras(V,adj2,source);
                cout<<"Dijiktras distance is:";
                for (int i = 0; i < r4.size (); i++)
                cout << r4[i];
                cout << endl;             
                break;
            }
            
            case 7:{
                int ans1=g1->kosaraju(V,adj1);
                cout<<"No of stringly connected components are:";
                cout<<ans1;
                cout<<endl;
                break;
            }
            case 8:{
                exit(1);
                break;
            }
        }
    }
}
