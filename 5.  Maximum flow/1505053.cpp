#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

using namespace std ;

class HeapItem
{
public:
    int data; //actual data that is stored
    float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * map;

    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }

    ~MinHeap() //destructor
    {
        if(map) delete [] map;
        if(A) delete [] A;
        map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
        }
    }

    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(int data, float key)
    {
        //Write your codes here
        A[heapLength+1].data=data;
        A[heapLength+1].key=key;
        map[heapLength+1] = heapLength+1; //map tracks which vertex is stored at which heap node
        heapLength++;
        buHeapify( heapLength );
        return;

    }

    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        //write your codes here
        HeapItem obj=A[1];
        if(heapLength>=1)
        {
            A[1]=A[heapLength];
            heapLength--;
            heapify(1);

            return obj;

        }
        else
        {
            printf("no item to be removed\n\n");
            return A[0];
        }
    }


    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(int data, float key)
    {
        //Write your codes here.
        int i = map[data];
        float f= A[i].key;
        //  printf("index of data %d\n",i);
        // printf("old key %.2f\n",f);
        // printf("new key  %.2f\n",key);
        A[i].key=key;
        if(key<f) buHeapify(i);
        else if(key>f) heapify(i);
        return;
    }

    //This function returns the key value of a data stored in heap
    float getKey(int data)
    {
        int i = map[data];
        return A[i].key;
    }

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                map[A[i].data]=i;
                A[smallest]=t;
                map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {

        if(i>=2)
        {
            int parent=i/2;
            while(parent>=1)
            {
                heapify(parent);
                parent--;
            }
        }
        return;
    }
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
};











class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
    int * list;
    int length ;
    int listMaxSize ;
    int listInitSize ;
public:
    ArrayList() ;
    ~ArrayList() ;
    int searchItem(int item) ;
    void insertItem(int item) ;
    void removeItem(int item) ;
    void removeItemAt(int item);
    int getItem(int position) ;
    int getLength();
    bool empty();
    void printList();
} ;


ArrayList::ArrayList()
{
    listInitSize = 2 ;
    listMaxSize = listInitSize ;
    list = new int[listMaxSize] ;
    length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
    int * tempList ;
    if (length == listMaxSize)
    {
        //allocate new memory space for tempList
        listMaxSize = 2 * listMaxSize ;
        tempList = new int[listMaxSize] ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };

    list[length] = newitem ; //store new item
    length++ ;
}

int ArrayList::searchItem(int item)
{
    int i = 0;
    for (i = 0; i < length; i++)
    {
        if( list[i] == item ) return i;
    }
    return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
    if ( position < 0 || position >= length ) return ; //nothing to remove
    list[position] = list[length-1] ;
    length-- ;
}


void ArrayList::removeItem(int item)
{
    int position;
    position = searchItem(item) ;
    if ( position == NULL_VALUE ) return ; //nothing to remove
    removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
    if(position < 0 || position >= length) return NULL_VALUE ;
    return list[position] ;
}

int ArrayList::getLength()
{
    return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0; i<length; i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    ArrayList  * adjList ;
    int *color,*parent,*dist,*distance;
    int *dfs_color,*dfs_parent,*dfs_start,*dfs_finish;
    int time;
    int **weight,**resiG;
    MinHeap heap ;

    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    //void dfs(int source); //will run dfs in the graph
    void dfs_visit(int u);
    void dfs();
    void dijkstra();
    void fordfulkerson(int s,int t);
    void mincut(int s);
    void printres();

};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    adjList = 0 ;
    directed = dir ; //set direction of the graph
    //define other variables to be initialized
    color=0;
    parent=0;
    dist=0;
    time = 0;
    distance=0;
    weight=0;
    resiG = 0;
    dfs_color=0;
    dfs_parent=0;
    dfs_start=0;
    dfs_finish=0;


}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;
    if(adjList!=0) delete[] adjList ; //delete previous list
    adjList = new ArrayList[nVertices] ;
    weight = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        weight[i] = new int[nVertices];
    }

    resiG = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        resiG[i] = new int[nVertices];
    }
    for(int i=0;i<nVertices;i++)
    {
        for(int j=0;j<nVertices;j++)
        {
            weight[i][j]=0;
            resiG[i][j]=0;
        }
    }











}

void Graph::addEdge(int u, int v, int w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
    adjList[u].insertItem(v) ;
    if(!directed) adjList[v].insertItem(u) ;

    weight[u][v]=w;
    resiG[u][v] =w;
}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges-- ;
    adjList[u].removeItem(v) ;
    if(!directed) adjList[v].removeItem(u) ;


}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    if(directed)
    {
        if(adjList[u].searchItem(v)!=NULL_VALUE)return true;
        else return false;
    }
    else
    {
        if(adjList[u].searchItem(v)!=NULL_VALUE||adjList[v].searchItem(u)!=NULL_VALUE)return true;
        else return false;
    }

}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0||u>nVertices)return NULL_VALUE;
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    int i,j;
    for(i=0; i<adjList[u].getLength(); i++)
    {
        for(j=0; j<adjList[v].getLength(); j++)
            if(adjList[u].getItem(i)==adjList[v].getItem(j)) return true;
    }

    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    int u;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        //complete this part
        u=q.dequeue();
        for(int j=0; j<nVertices; j++)
        {
            if(resiG[u][j]>0)
            {
                if(color[j]==WHITE)
                {
                    dist[j]=dist[u]+1;
                    parent[j]=u;
                    color[j]=GREY;
                    q.enqueue(j);
                }
            }
        }
        //printf("Inside BFS\n");
        color[u]=BLACK;
    }
}


void Graph::dfs_visit(int u)
{

    time=time+1;
    dfs_start[u]=time;
    dfs_color[u]=GREY;

    for(int j=0; j<nVertices; j++)
    {
        if(isEdge(u,j))
        {
            if(dfs_color[j]==WHITE)
            {
                dfs_parent[j]=u;
                dfs_visit(j);
            }
        }
    }
    time=time+1;
    dfs_finish[u]=time;
    dfs_color[u]=BLACK;

}


//void Graph::dfs(int source)
void Graph::dfs()

{
    //write this function
    dfs_color=new int[nVertices];
    dfs_parent=new int[nVertices];
    dfs_finish=new int[nVertices];
    dfs_start=new int[nVertices];
    int i,u;
    for(i=0; i<nVertices; i++)
    {
        dfs_color[i]=WHITE;
        dfs_start[i]=dfs_finish[i]=INFINITY;
        dfs_parent[i]=NULL_VALUE;
    }
    i=0;
    for(i=0; i<nVertices; i++)
    {
        if(dfs_color[i]==WHITE) dfs_visit( i);

    }
    for(int p=0; p<nVertices; p++)
    {
        printf("%d:\t%d\t%d\n",p,dfs_start[p],dfs_finish[p]);
    }


}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return  INFINITY;
    bfs(u);
    return dist[v];

    return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength(); j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
    printf("\n\n\n");


}
void Graph :: fordfulkerson(int s,int t)
{
    //resiG=weight;
    int maxflow=0;
    int cflow;
    int temp;
    bfs(s);
    while(1)
    {
        //printf("Inside 1st while");
        if( parent[t]==-1) break;
        temp=t;
        cflow=INFINITY;
        while (1)
        {
            if(temp == s) break;
            //printf("Inside 2nd while  ");
            //printf("%d %d\n",parent[temp],temp);
            // printf("vejal is here");
            if(cflow>resiG[parent[temp]][temp])
            {
                cflow=resiG[parent[temp]][temp];
            }
            temp = parent[temp];
        }
        maxflow+=cflow ;
        temp = t;
        //printf("Outside 2nd while");
        while(1)
        {
            if(temp == s) break;
            //printf("Inside 3rd while");
            resiG[parent[temp]][temp]-=cflow;
            resiG[temp][parent[temp]]+=cflow;
            temp = parent[temp];
        }
        bfs(s);
    }
    printf("maximum flow is %d\n",maxflow);

    for (int i=0; i<nVertices; i++)
    {
        for (int j=0; j<nVertices; j++)
        {
            if ( weight[i][j]>0)
            {
                printf("%d\t",weight[i][j]-resiG[i][j]);

            }
            else printf("%d\t",0);

        }
        printf("\n");
    }
    printf("*********************************************\n");
}

void Graph::printres(){
    for (int i=0; i<nVertices; i++)
    {
        for (int j=0; j<nVertices; j++)
        {
            //if ( weight[i][j]!=0)
            //{
                printf("%d\t",resiG[i][j]);

            //}
        }
        printf("\n");
    }
    printf("*********************************************\n");
}
void Graph::mincut(int s)
{
    bfs(s);
    printf("MinimumCut Edges :\n");
    for (int i=0; i<nVertices; i++)
    {
        if (parent[i]!=-1)
        {
            for(int j=0; j<nVertices; j++)
            {

                if (parent[j]==-1 && weight[i][j]>0)

                    printf("%d     %d\n",i+1,j+1);
            }
        }
    }

}

void Graph::dijkstra()
{
    distance = new int[nVertices];
    parent = new int[nVertices];

    distance[0] = 0;
    heap.insertItem(0,0);
    parent[0] = -2 ;
    printf("%d\n",nVertices);

    for(int i=1; i<nVertices; i++)
    {
        heap.insertItem(i, INFINITY);
        distance[i]=INFINITY;
        parent[i]=-2;
    }

    heap.printHeap();
    // for(int i=0; i<nVertices; i++) cout<<distance[i]<<endl;

    HeapItem tmp;
    int k,l;

    while(!heap.Empty())
    {
        tmp = heap.removeMin();
        l = adjList[tmp.data].getLength();
        //cout<<" min removed with length "<<l<<endl;

        for(int j=0; j<l; j++)
        {
            k = adjList[tmp.data].getItem(j);
            if(distance[k]>distance[tmp.data]+weight[tmp.data][k])
            {
                distance[k] = distance[tmp.data]+weight[tmp.data][k] ;
                parent[k] = tmp.data ;
                // cout<<" relaxing"<<endl;
                heap.updateKey(k,distance[k]);
            }

        }
    }
    cout<< "vertex "<<"distance "<<" parent"<<endl;
    for(int i=0; i<nVertices; i++)
    {
        cout<<i+1<<"  \t"<<distance[i]<<"   \t"<<parent[i]+1<<endl;
    }

}

Graph::~Graph()
{
    //write your destructor here
    int j;
    if(adjList!=0) delete[] adjList;
    if(color) delete[] color;
    if(parent)delete [] parent;
    if(dist)delete [] dist;
    if(dfs_color) delete[] dfs_color;
    if(dfs_parent)delete [] dfs_parent;
    if(dfs_start)delete [] dfs_start;
    if(dfs_finish)delete[]dfs_finish;
    dfs_color=0;
    dfs_parent=0;
    dfs_start=0;
    dfs_finish =0;
    color=0;
    parent=0;
    dist=0;
}



int main(void)
{
    int n,m;
    //Graph g;
    Graph g = new Graph(true);
    FILE *fp ;
    fp=fopen("inp1.txt","r") ;
    printf("Enter number of vertices: ");
    //fscanf(fp,"%d", &n);
    scanf("%d", &n);
    printf("Enter number of edges: ");
    //fscanf(fp,"%d", &m);
    scanf("%d", &m);
    g.setnVertices(n);
    int u, v, w;
    for (int i=0; i<m; i++)
    {
        //fscanf(fp,"%d%d%d", &u, &v, &w);
        scanf("%d%d%d", &u, &v, &w);
        g.addEdge(u-1, v-1, w);

    }
    // g.printGraph();
    int s,t;
    scanf("%d%d",&s,&t);
    //g.printres();
    g.fordfulkerson(s-1,t-1);
    // g.dijkstra( );
    g.mincut(s-1);
}
