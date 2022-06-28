#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>>

typedef struct node *nd;

struct node{
	nd n;
	nd p;
	nd u;
	nd d;
	nd par;
	int key;
	int w;
	int i;
	int j;
};

struct min_heap_nodes{
    int v;
    int key;
};

struct min_heap{
    struct min_heap_nodes *min_heap_array ; // dynamically allocated matrix of size size(number of nodes)
    int H_size; // number of node currently present
    int size; // number of nodes in the heap at the start
};

int pos[31]; // auxiliary array to keep track of the nodes

void print1(nd h); //kata seira
void minimum_spanning_tree(nd R[31],int value);
void insert(nd h,nd temp,int b);
void deletenode(nd h,int k,int b);
int  find_heap_array_size(nd R[31]);
void create_dynamic_array(nd R[31],struct min_heap *min_heap_ptr);
void MST_prim(nd R[31],int root,struct min_heap *min_heap_ptr);
struct min_heap_nodes extract_min(struct min_heap *min_heap_ptr);
void heapify(struct min_heap *min_heap_ptr,int i);
void put_in_position(struct min_heap_nodes *arr,int v_heap);
bool IsMinHeapEmpty(struct min_heap *min_heap_ptr);
void print_min_span_tree(nd R[31]);

int main()
{
    int INPUT_in,data;
    FILE* fp;
    printf("Program Starting\n");
    printf("Select 0 for INPUT from terminal\n");
    printf("Select 1 for INPUT from file\n");
    scanf("%d",&INPUT_in);
    getchar();
    if (INPUT_in == 1){
        fp = fopen("text.txt" , "r");

         if (fp == NULL)
        {
            printf("file not opened");
            exit(101);
        }
    }
	int i,j,w,value,S;
	nd R[31],C[31]; // to R[0] kai to C[0] den xrisimopoiounte
	for (j=0; j<=30; j++)
	{
		nd temp =(nd) malloc(sizeof(struct node));
		temp->n=NULL;
		temp->p=NULL;
		temp->u=NULL;
		temp->d=NULL;
		temp->par=NULL;
		temp->i=0;
		temp->j=j+1;
		C[j]=temp;
	}
	for (i=0; i<=30; i++)
		{
            nd temp =(nd) malloc(sizeof(struct node));
			temp->n=NULL;
			temp->p=NULL;
			temp->u=NULL;
			temp->d=NULL;
			temp->par=NULL;
			temp->j=0;
			temp->i=i;
			R[i]=temp;
		}
    printf("MAIN MENU:\n");
	printf("Select '1' to Add new node\n");
	printf("Select '2' to Print the Sparse Array\n");
	printf("Select '3' to Delete node\n");
	printf("Select '0' to Quit:\n");
	if (INPUT_in==0){
	  scanf("%d",&S);
	  getchar();
	}
	if (INPUT_in == 1 ){
        fscanf(fp, "%d",&data);
        S=data;
	}
	while (S!=0){
	if (S == 2)
	{
		bool flag=false;
		for (i=1; i<=30; i++)
		{
			if (R[i]->n!=NULL)
			{
			print1(R[i]);//emfanisi kata seira
			flag=true;
			}
		}
		if (flag==false)
					printf ("The sparse array is empty\n");
	}
	else if (S == 1)
	{
		if (INPUT_in==0)
        {
            printf("Give row i and column j\n");
            printf("i=");
            scanf("%d",&i);
            getchar();
            printf("j=");
            scanf("%d",&j);
            getchar();
            scanf("%d",&w);
            getchar();
        }
		if (INPUT_in==1)
        {
            fscanf(fp, "%d",&data);
            i= data;
            fscanf(fp, "%d",&data);
            j= data;
            fscanf(fp, "%d",&data);
            w= data;
        }
        nd temp =(nd) malloc(sizeof(struct node));
        temp->n=NULL;
        temp->p=NULL;
        temp->d=NULL;
        temp->u=NULL;
        temp->par=NULL;
        temp->i=i;
        temp->j=j;
        temp->w=w;
		if (i!=j){
			insert(R[i],temp,0);   //passing 0 for connecting rows
			insert(C[j],temp,1);   //passing 1 for connecting columns
			nd temp =(nd) malloc(sizeof(struct node));
			temp->n=NULL;
			temp->p=NULL;
			temp->d=NULL;
			temp->u=NULL;
			temp->par=NULL;
			temp->i=j;
			temp->j=i;
			temp->w=w;
			insert(R[j],temp,0);  // for undirected graphs
			insert(C[i],temp,1);
		}
		if (i==j){
			insert(R[i],temp,0);
			insert(C[j],temp,1);
		}
	}
	else if (S == 3)
		{
		printf("Give position of node to delete:\n");
		printf("i=");
		scanf("%d",&i);
		getchar();
		printf("j=");
		scanf("%d",&j);
		getchar();
		if (i!=j)
        {
            deletenode(R[i],j,0);
            deletenode(C[j],i,1);
            deletenode(R[j],i,0);
            deletenode(C[i],j,1);
        }
        if (i==j)
        {
            deletenode(R[i],j,0);
            deletenode(C[j],i,1);
        }
		}
	else if (S == 4)
	{
		printf("Give root\n");
		printf("root=") ;
		scanf("%d",&value) ;
		getchar();
		minimum_spanning_tree(R,value);
	}
	printf("\nMAIN MENU:\n");
	printf("Select '1' to Add new node \n");
	printf("Select '2' to Print the Sparse Array\n");
	printf("Select '3' to Delete node\n");
	printf("Select '4  to create minimum spanning tree\n");
	printf("Select '0' to Quit:\n");
    if (INPUT_in==1)
    {
        if((fscanf(fp, "%d",&data))==1)
            S=data;
            if (S == 0 ){
                fclose(fp);
            }
    }
    if (INPUT_in==0)
    {
        scanf("%d",&S);
        getchar();
    }
	}
	printf("EXIT");
	return 0;
}


void print1(nd h)
{
	nd temp=h;
	if (temp->n!=NULL)
	{
		printf("ROW %d :",temp->i) ;
		do {
			temp=temp->n;
			printf("  [%d,%d] " ,temp->i,temp->j) ;
		}
		while (temp->n!=NULL);
	}
	printf("\n");
}


void insert(nd h,nd temp, int b)
{
	nd aux,h1;
	if (b==0)//topothetisi se stili
	{
	 	h1=h->n;
	 	if (h1!=NULL)
        {
            if (h1->j==temp->j)
                printf("Input already exists\n");
        }
	 	if ((h1!=NULL) && (temp->j<h1->j))
	 		{
	 			temp->n=h1;
	 			h1->p=temp;
	 			h1=temp;
	 			h1->p=h;
	 			h->n=h1;
	 		}
        if ((h1!=NULL) && (temp->j>h1->j))
	 		{
	 			aux=h1;
	 			while((aux->n!=NULL) && (aux->n->j <= temp->j))
	 				aux=aux->n;
	 			if (aux->j!=temp->j)
	 			{
                    if (aux->n!=NULL)
                    {
                    temp->n=aux->n;
                    aux->n->p=temp;
                    aux->n=temp;
                    temp->p=aux;
                    }
                    else
                    {
                        aux->n=temp;
                        temp->n=NULL;
                        temp->p=aux;
                    }
	 			}
	 			else
                    printf("Input already exists\n");
	 		}
        if (h1==NULL)
        {
	 			h1=temp;
	 			h1->p=h;
	 			h->n=h1;
        }
	 }
	if (b==1)//topothetisi se grammi
		{
			h1=(h)->d;
		 	if ((h1!=NULL) && (temp->i<h1->i))
            {
		 			temp->d=h1;
		 			h1->u=temp;
		 			h1=temp;
		 			h1->u=h;
		 			h->d=h1;
            }
            if ((h1!=NULL) && (temp->i>h1->i) )
            {
                aux=h1;
                while( (aux->d!=NULL) && (aux->d->i <= temp->i) )
                    aux=aux->d;
                if (aux->i!=temp->i)
                {
                    if (aux->d!=NULL)
                    {
                    temp->d=aux->d;
                    aux->d->u=temp;
                    aux->d=temp;
                    temp->u=aux;
                    }
                    else
                    {
                        aux->d=temp;
                        temp->d=NULL;
                        temp->u=aux;
                    }
                }
		 		}
		 		if (h1==NULL)
		 		{
		 			h1=temp;
		 			h1->u=h;
		 			h->d=h1;
		 		}
		 }

 }

void deletenode (nd h,int k,int b)
{
	nd h1,aux;
	if (b==0)
	{
	h1 = h->n;
	aux=h1;
	if (h1==NULL)
			printf("Input doesn't exist in the array\n");
	else
	{
		    while (aux->j!= k && aux->n!=NULL)
		    	aux=aux->n;
		    if (aux==h1 && aux->j==k)
		    {
		    	if (aux->n!=NULL)
		    	{
		    	h1= aux->n;
		    	h1->p=h;
		    	}
		    	else
		    		h1=NULL;
		    	h->n=h1;
		    }
		    else if (aux->n==NULL && aux->j==k)
		    	aux->p->n=NULL;
		    else if ((aux->n==NULL && aux->j!=k) ||  (aux==h1 && aux->j!=k))
		    	printf("Input doesn't exist in the array\n");
		    else
		    {
		    	aux->p->n=aux->n;
		    	aux->n->p=aux->p;
		    }
}
}
	if (b==1)
	{
		h1 = h->d;
		aux=h1;
		if (h1!=NULL)
		{
			    while (aux->i!= k && aux->d!=NULL)
			    	aux=aux->d;
			    if (aux==h1)
			    {
			    	if (aux->d!=NULL)
			    	{
			    	h1= aux->d;
			    	free(aux);
			    	h1->u=h;
			    	}
			    	else
			    		{
			    		free(aux);
			    		h1=NULL;
			    		}
			    	h->d=h1;
			    }
			    else if (aux->d==NULL && aux->i==k )
			    {
			    	aux->u->d=NULL;
			    	free(aux);
			    }
			    else if ((aux->d==NULL && aux->i!=k) || (aux==h1 && aux->i!=k))
			    {
			    	printf("Input doesn't exist in the array");
			    }
			    else
			    {
			    	aux->u->d=aux->d;
			    	aux->d->u=aux->u;
			    	free(aux);
			    }

	}
	}
}

void minimum_spanning_tree(nd R[31],int root)
{
    struct min_heap *min_heap_ptr; // pointer for the heap array
    int size;
    size= find_heap_array_size(R);
    min_heap_ptr->min_heap_array=calloc(size,sizeof(struct min_heap_nodes));
    min_heap_ptr->size=size;
    min_heap_ptr->H_size=size;
    create_dynamic_array(R,min_heap_ptr);
    for (int i=0; i<=(size-1); i++){
        printf("arr[%d]=%d\n",i,min_heap_ptr->min_heap_array[i].v);
        //printf("auxiliary_arr[%d]=%d\n",min_heap_array[i].v,pos[min_heap_array[i].v]);
    }
    MST_prim(R,root,min_heap_ptr);
    print_min_span_tree(R);
}

int find_heap_array_size(nd R[31])
{
    int count=0;
    for (int i=1; i<=30; i++){
        if (R[i]->n!=NULL){
            count++;
        }
    }
    return count;
}

void create_dynamic_array(nd R[31],struct min_heap *min_heap_ptr)
{
    struct min_heap_nodes *arr;
    arr=min_heap_ptr->min_heap_array;
    int k=0;
     for (int i=1; i<=30; i++){
        if (R[i]->n!=NULL){
            arr[k].v=R[i]->i;
            arr[k].key=INT_MAX;
            pos[i]=k;
            k++;
        }
    }
}

void heapify(struct min_heap *min_heap_ptr,int i)

{
	int l,r,smallest,pos1,pos2;
	struct min_heap_nodes *arr,temp1;
	arr=min_heap_ptr->min_heap_array;
	int Hsize = min_heap_ptr->H_size-1;

	l=2*i+1;      //l=2i
	r=l+1;        //r=2i+1
	if((l<=Hsize)&&(arr[l].key<arr[i].key))
		smallest=l;
	else
		smallest=i;
	if((r<=Hsize)&&( arr[r].key < arr[smallest].key))
		smallest=r;
	if(smallest!=i)
	{
        //swap nodes
        temp1=arr[i];
		arr[i]=arr[smallest];
		arr[smallest]=temp1;

		//swap positions
		pos[arr[i].v]=i;
		pos[temp1.v]=smallest;

		heapify(min_heap_ptr,smallest);

}
}
void MST_prim(nd R[31],int root,struct min_heap *min_heap_ptr)
{
    struct min_heap_nodes u,temp_first,*arr;
    nd temp,v;
    int adj,v_heap;
    arr=min_heap_ptr->min_heap_array;
    arr[pos[root]].key=0;

    // put root in the first place of the heap

    temp_first=arr[0];
    arr[0]=arr[pos[root]];
    arr[pos[root]]=temp_first;

    // swap the positions of the nodes
    pos[temp_first.v]=pos[root];
    pos[root]=0;

    while (!IsMinHeapEmpty(min_heap_ptr)){
            u=extract_min(min_heap_ptr);    // u is a struct min_nodes_heap so u.v is an integer
            printf("\nNode extracted=%d\n",u.v);
            temp=R[u.v];
            while (temp->n!=NULL)
            {
            temp=temp->n;  // edges
            adj=temp->j;   // int
            v=R[adj]; //using R[i] to define n
            v_heap=pos[adj]; // position of node in the heap using the auxiliary matrix

            if ((min_heap_ptr->H_size >= v_heap) && (temp->w < arr[v_heap].key)){
                        v->par=R[u.v];
                        int weight=temp->w;
                        arr[v_heap].key = weight;
                        put_in_position(arr,v_heap);
                    }
            }
    }
}

bool IsMinHeapEmpty(struct min_heap *min_heap_ptr)
{
        return min_heap_ptr->H_size==0;
}

struct min_heap_nodes extract_min(struct min_heap *min_heap_ptr)
{
    struct min_heap_nodes first,*arr;
    arr=min_heap_ptr->min_heap_array;
    first = arr[0];

    //swap the first with the last node

    arr[0]=arr[min_heap_ptr->H_size-1];
    arr[min_heap_ptr->H_size-1]=first;

    // swap the positions of the nodes
    pos[first.v]=min_heap_ptr->H_size-1;
    pos[arr[0].v]=0;


    min_heap_ptr->H_size--;
    heapify(min_heap_ptr,0);

    return first ;

}

void put_in_position(struct min_heap_nodes *arr,int v_heap)
{
    int i=v_heap,x,y,temp_pos;
    struct min_heap_nodes temp;
    x=arr[i].key;
    y=arr[(i-1)/2].key;
    while (arr[i].key<arr[(i-1)/2].key ){
        temp_pos=pos[arr[i].v];
        //swap
        temp=arr[i];
        arr[i]=arr[(i-1)/2];
        arr[(i-1)/2]=temp;
        // swap the positions of the nodes
        pos[arr[i].v]=temp_pos;
        pos[arr[(i-1)/2].v]=(i-1)/2;

         i=(i-1)/2;
    }
}

void print_min_span_tree(nd R[31])
{
    for (int i=1; i<=30; i++){
        if(R[i]->par!=NULL){
            printf("\n [%d,%d]",i,R[i]->par->i);
        }
    }
}
