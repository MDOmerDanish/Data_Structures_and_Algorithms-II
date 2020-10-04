#include<bits/stdc++.h>
#include<windows.h>
#include<algorithm>
#include<ctime>
#include<cstdio>
#include<cstdlib>

#define LIST_INITIAL_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

#define MAXIMUM_SIZE 10000
#define CHARACTER_LENGTH 5
using namespace std ;


class ArrayList{
public:
    int LISTMAXIMUMSIZE;
    int * list;
    int length;

    ArrayList();

    void initializeList();
    int searchItem(int item);
    int insertItem(int newitem);
    int deleteItemAt(int position);
    int deleteItem(int item);
    void printList();
    int deleteLast();
    int getLength();
    void Clear();

};

    void ArrayList::initializeList()
    {
        LISTMAXIMUMSIZE = LIST_INITIAL_SIZE;
        list = (int*)malloc(sizeof(int)*LISTMAXIMUMSIZE) ;
        length = 0 ;
    }

    ArrayList::ArrayList()
    {
        LISTMAXIMUMSIZE = LIST_INITIAL_SIZE;
        list = (int*)malloc(sizeof(int)*LISTMAXIMUMSIZE) ;
        length = 0 ;
    }

    int ArrayList::searchItem(int item)
    {
        int i = 0;
        for (i = 0; i < length; i++)
        {
            if( list[i] == item ) return i;
        }
        return -1;
    }

    int ArrayList::insertItem(int newitem)
    {
        if(LISTMAXIMUMSIZE == 0)initializeList();

        int * tempList ;
        if (length == LISTMAXIMUMSIZE)
        {
            //allocate new memory space for tempList
            LISTMAXIMUMSIZE = 2 * LISTMAXIMUMSIZE ;
            tempList = (int*) malloc (LISTMAXIMUMSIZE*sizeof(int)) ;
            int i;
            for( i = 0; i < length ; i++ )
            {
                tempList[i] = list[i] ; //copy all items from list to tempList
            }
            free(list) ; //free the memory allocated before
            list = tempList ; //make list to point to new memory
        };

        list[length] = newitem ; //store new item
        length++ ;
        return SUCCESS_VALUE ;
    }


    int ArrayList::deleteItemAt(int position) //version 2, do not preserve order of items
    {
        if ( position >= length ) return NULL_VALUE;
        list[position] = list[length-1] ;
        length-- ;
        return SUCCESS_VALUE ;
    }



    int ArrayList::deleteItem(int item)
    {
        int position;
        position = searchItem(item) ;
        if ( position == -1 ) return NULL_VALUE;
        deleteItemAt(position) ;
        return SUCCESS_VALUE ;
    }

    void ArrayList::printList()
    {
        int i;
        for(i=0;i<length;i++)
            printf("%d ", list[i]);
        printf("Current size: %d, current length: %d\n", LISTMAXIMUMSIZE, length);
    }


    int ArrayList::deleteLast()
    {
        if(length>1) length--;
    }

    int ArrayList::getLength()
    {
        return length ;
    }

    void ArrayList::Clear()
    {
        length = 0;
        LISTMAXIMUMSIZE = 0;
        free(list);
    }



//*******************************************************************************************************************************************

class Hash{
private:
    int collision;
    int *array;
    bool *flag;
    ArrayList *linkarray ;
public:
    int Hash_function_1(string str);
    int Hash_function_2(string str);
    int Hash_function_3(string str);

    Hash();
    void HASH_INITIALIZE();

    void insert_Linear(int n, int h);
    int search_Linear(int n, int h);
    void delete_Linear(int n, int h);
    void insrt_chn(int n, int h);
    int srch_in_chain(int n, int h);
    void delete_Chain(int n, int h);

    int getCollision(){return collision ;};
};

Hash::Hash(){
    array = new int[MAXIMUM_SIZE];
    flag = new bool[MAXIMUM_SIZE];
    linkarray = new ArrayList[MAXIMUM_SIZE];
}
void Hash::HASH_INITIALIZE(){
    collision = 0 ;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        flag[i] = false ;
        array[i] = 0 ;
    }
}

int Hash::Hash_function_1(string str){
    int hss = 0;
    for (int i = 0; i < CHARACTER_LENGTH; i++)
        hss = (5 * hss + str[i]) % MAXIMUM_SIZE;
    return hss%MAXIMUM_SIZE ;
}

int Hash::Hash_function_2(string str){
    int hss = 0;
    for(int i=0; i<CHARACTER_LENGTH; i++)
        hss += str[i]- 'A' ;
    return (hss%MAXIMUM_SIZE);
}

int Hash::Hash_function_3(string str){
    int hss = 0;
    for(int i=0; i<CHARACTER_LENGTH; i++)
        hss += ((str[i]- 'A')%13)*(i+1) ;
    return (hss%MAXIMUM_SIZE);
}

void Hash::insert_Linear(int n, int h){
    int counter = 0;
    if(array[h]!=0)collision++;
    while(array[h] != 0){
        h++;
        //collision++;
        counter++;
        if(h==MAXIMUM_SIZE) h = 0;
        if(counter>MAXIMUM_SIZE) return ;
    }
    array[h] = n;
    return ;
}

int Hash::search_Linear(int n, int h){
    int counter = 0;
    while(array[h] != n){
        h++;
        counter++;
        if(array[h] == 0 && !(flag[h])) return -1;
        if(h==MAXIMUM_SIZE) h = 0;
        if(counter>MAXIMUM_SIZE) return -1;
        //if(array[h] == n) break;
    }
    return h ;
}

void Hash::delete_Linear(int n, int h){
    int t = search_Linear(n, h);
    if(t<0) return ;
    array[t] = 0;
    flag[t] = true ;
}

void Hash::insrt_chn(int n, int h)
{
    //if(isDuply(str)) return;
    if(linkarray[h].length>0)collision++;
    linkarray[h].insertItem(n);
}

int Hash::srch_in_chain(int n, int h){
    return linkarray[h].searchItem(n);
}

void Hash::delete_Chain(int n, int h){
    linkarray[h].deleteItem(n);
}

//int Hash::getCollision(){return collision;}


void Generator(string s[]){
    char tr[CHARACTER_LENGTH+1];
    char t;
    srand(time(NULL));
    for(int i=0; i<MAXIMUM_SIZE; i++){
        for(int j=0; j<CHARACTER_LENGTH; j++){
            t = rand()%26 + 'A' ;
            tr[j] = t ;
        }tr[CHARACTER_LENGTH] = '\0';
        s[i] = tr ;
    }
}


//**********************************************main function*********************************************************

int main()
{
    clock_t ct ;
    //result container
    int cc1,cc2,cc3,lc1,lc2,lc3;
    float cs1,cs2,cs3,ls1,ls2,ls3;
    //LINEAR PROBING
    string str[MAXIMUM_SIZE];
    Generator(str);

    Hash hsh;
    int h;

    //for linear & Hash_function_1
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_1(str[i]);
        hsh.insert_Linear(i,h);
    }
    lc1 = hsh.getCollision() ;
    ct = clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_1(str[i]);
        hsh.search_Linear(i,h);
    }
    ls1 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

     //for linear & Hash_function_2
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_2(str[i]);
        hsh.insert_Linear(i,h);
    }
    lc2 = hsh.getCollision() ;
    ct = clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_2(str[i]);
        hsh.search_Linear(i,h);
    }
    ls2 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

     //for linear & Hash_function_3
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_3(str[i]);
        hsh.insert_Linear(i,h);
    }
    lc3 = hsh.getCollision() ;
    ct= clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_3(str[i]);
        hsh.search_Linear(i,h);
    }
    ls3 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

     //for Chain & Hash_function_1
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_3(str[i]);
        hsh.insrt_chn(i,h);
    }
    cc1 = hsh.getCollision() ;
    ct = clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_1(str[i]);
        hsh.srch_in_chain(i,h);
    }
    cs1 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

     //for Chain & Hash_function_2
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_2(str[i]);
        hsh.insrt_chn(i,h);
    }
    cc2 = hsh.getCollision() ;
    ct = clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_2(str[i]);
        hsh.srch_in_chain(i,h);
    }
    cs2 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

     //for Chain & Hash_function_3
    hsh.HASH_INITIALIZE();
    //cout<<hsh.getCollision()<<endl;
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_3(str[i]);
        hsh.insrt_chn(i,h);
    }
    cc3 = hsh.getCollision() ;
    ct = clock();
    for(int i=0; i<MAXIMUM_SIZE; i++){
        h = hsh.Hash_function_3(str[i]);
        hsh.srch_in_chain(i,h);
    }
    cs3 = 1.0*(clock()-ct)/1000;
    hsh.HASH_INITIALIZE();
    //***************************

    cout<<"\t\t"<<"\tHash_func1\t"<<"\tHash_func 2"<<"\tHash_func 3\t"<<endl;
    cout<<"Linear\t"<<"\tSearch Time :"<<ls1<<"\tSearch Time :"<<ls2<<"\tSearch Time :"<<ls3<<endl;
    cout<<"Probing\t"<<"\tCollision :"<<lc1<<"\t\tCollision :"<<lc2<<"\t\tCollision :"<<lc3<<endl;
    cout<<endl;
    cout<<"Chaining"<<"\tSearch Time :"<<cs1<<"\t\tSearch Time :"<<cs2<<"\tSearch Time :"<<cs3<<endl;
    cout<<"\t"<<"\tCollision :"<<cc1<<"\t\tCollision :"<<cc2<<"\t\tCollision :"<<cc3<<endl;

    return 0;
}

//**********************************************main function*********************************************************

/*/




int main ()
{
    clock_t ct = clock();
    string str[MAXIMUM_SIZE];
    Generator(str);
    ct = clock()-ct;
    cout<<"It took me "<<ct<<" clicks and "<<ct/CLOCKS_PER_SEC <<"seconds to generate"<<endl;
   // for(int i=0; i<MAXIMUM_SIZE; i++) cout<<str[i]<<endl;
    for(int i=0; i<100; i++) cout<<str[i]<<endl;

    ct = clock()-ct;
    cout<<"And "<<ct<<" clicks and "<<ct/CLOCKS_PER_SEC <<"seconds to write"<<endl;
    return 0;
}
/*
int main ()
{
  clock_t t;
  int f;
  t = clock();
  printf ("Calculating...\n");
  f = frequency_of_primes (99999);
  printf ("The number of primes lower than 100,000 is: %d\n",f);
  t = clock() - t;
  printf ("It took me %d clicks (%f seconds).\n",t,((float)t)/CLOCKS_PER_SEC);
  return 0;
}
*/

