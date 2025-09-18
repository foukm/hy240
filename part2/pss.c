/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr), John Petropoulos (johnpetr@csd.uoc.gr)
 * @Version 30-11-2022
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

/*csd4249
    Foukaki Maria*/
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"

struct Group G[MG];
struct SubInfo **T;
int a,b,tableSize,primeNumber;
void print_LO_BST(struct TreeInfo **root,int i);
/*dipla sundedemeno dentro, diadiko, taksinomimeno ws pros to iId*/
void BST_Insert(int itm,int iId, struct Info **root, int *gids_arr,int size_of_gids_arr)
{
    struct Info * p;
    struct Info *q;
    struct Info *prev = NULL;
    int j;
    p=*root;
    /*mexri na ftasw se null*/
    while (p!=NULL)
    {
        /*ean uparxei idio iId den kanei tipota*/
        if(p->iId==iId)
        {
            return ;
        }
        prev=p;
        /*ean to iId pou thelw na kataxwrisw einai mikrotero, proxoraw pros ta aristera*/
        if(iId<p->iId)
        {
            p=p->ilc;
        }else{ /*alliws pros ta deksia*/
            p=p->irc;
        }
    }

    q = (struct Info *)malloc(sizeof(struct Info));
    q->itm = itm;
    q->iId=iId;
    q->ilc=NULL;
    q->irc=NULL;
    q->ip = NULL;
    /*arxikopoiume me 0 dioti mporei na exoun meinei skoupidia, 0 simainei oti i pliroforia den susxetikzetai me tin omada i*/
    for(j=0; j<MG; j++)
    {
        q->igp[j]=0;
    }
    /*mesw tou pointer gids_arr kai to size_of_gids_arr vriskoume me poies omades susxetizetai i pliroforia kai thetoume 1*/
    for(j=0; j<size_of_gids_arr-1; j++)
    {
        q->igp[(*(gids_arr+j))]=1;
    }
    /*ftiaxnoume ti riza*/
    if(prev==NULL)
    {
        *root=q;
        return;
    }else if(iId<prev->iId) /*vlepoume ean tha mpei sto aristero h sto deksi podi tou prev*/
    {
        prev->ilc=q;
    }else{
        prev->irc=q;
    }
    /*o pateras*/
    q->ip = prev;
    return; 
}

/*ektipwnei ena dentro me endodiatetagmeni diasxisi gia na ta ektupwnei se auksousa diataksi*/
void print_BST(struct Info **root)
{
    struct Info *p;
    p=*root;
    if(p==NULL)
    {
        return;
    }
    print_BST(&(p->ilc));
    printf("%d ",p->iId);
    print_BST(&(p->irc));
}

/*elegxei ean uparxei komvos me pou na exei itm iso me itm*/
int BST_LookUp(struct Info **root, int itm)
{
    struct Info *p;
    p=*root;
    /*if(p->iId==iId && p->ilc==NULL &&p->irc==NULL)
    {
        /**root=NULL;*/
        /*return 1;*/
    /*}*/
    while(p!=NULL && p->itm!=itm)
    {
        if(itm<p->itm)
        {
            p=p->ilc;
        }else{
            p=p->irc;
        }
    }
    if(p->itm==itm)
    {
        return 1;
    }else{
        return 0;
    }
}

/*apo th fash a
einai mia mi taksinomimeni, apla sundedemeni lista, thn xrisimopoioume gia na eisagoume sundromites pou endiaferontai gia 
tin omada, gsub*/
void L_Insert(int x, struct Subscription **head)
{
    struct Subscription *p,*tmp;
    p=*head;
 
    /*diasxizoume ti lista gia na doume an uparxei eggrafi*/
    while(p!=NULL)
    {
        /*ean uparxei idi tetoia eggrafi kanoume return */
        if(p->sId==x)
        {
            return;
        }
        p=p->snext;
    }
    /*ean den uparxei tetoia eggrafi vazoume to neo stoixeio stin korfi tis listas*/
    tmp=(struct Subscription *)malloc(sizeof(struct Subscription));
    tmp->sId=x;
    tmp->snext=*head;
    *head=tmp;

}

/*mas ektupwnei ta sId tis mona ataksinomitis listas*/
void L_Print(struct Subscription **head)
{
    struct Subscription *p;
    p=*head;
    printf("SUBLIST = ");
    while(p!=NULL)
    {
        printf("%d ",p->sId);
        p=p->snext;
    }
}
/*psaxnei na dei an uparxei stoixeio me sId to x, an uparxei epistrefei 1 alliws epistrefei 0*/
int L_LookUp(int x, struct Subscription **head)
{
    struct Subscription *p;
    p=*head;
    while(p!=NULL)
    {
        if(p->sId==x)
        {
            return 1;
        }
        p=p->snext;
    }
    return 0 ;
}
/*ean uparxei sundromitis me sId == x, ton svinei */
void L_Delete(int x, struct Subscription **head)
{
    struct Subscription *p,*tmp,*q;
    p=*head;
    if(L_LookUp(x,head)==1)
    {
        if(p->sId==x && p==*head)
        {
            tmp=p->snext;
            p->snext=NULL;
            *head=tmp;
            free(p);
            return;
        }
        q=p;
        p=p->snext;
        while(p->sId!=x && p->snext!=NULL)
        {
            p=p->snext;
            q=q->snext;
        }
        if(p->sId==x && p->snext!=NULL)
        {
            tmp=p->snext;
            p->snext=NULL;
            q->snext=tmp;
            free(p);
            return;
        }
        if(p->sId==x && p->snext==NULL)
        {
            q->snext=NULL;
            free(p);
            return;
        }
    }
    return;
}   


/*psaxnei na dei an uparxei tetoios sundromitis sti lista sundmitwn kai ton epistfei alliws epistrefei null*/
struct SubInfo * SL_LookUp(int x, struct SubInfo **head)
{
    struct SubInfo *q;
    q=*head;
    while(q!=NULL)
    {
        if(q->sId==x)
        {
            return q;
        }
        q=q->snext;
    }
    return NULL;
}
/*epistrefei to mikrotero kataxwrimeno stoixeio sto dentro, dld terma aristera*/
struct Info *minV(struct Info *node)
{
    struct Info *cur=node;
    while(cur && cur->ilc !=NULL)
    {
        cur=cur->ilc;
    }
    return cur;
}

/*tin xrisimopoiume gia na svisoume enan sundromikiti apo tin mona sundedemeni taksinomimeni lista*/
void SL_Delete(int x, struct SubInfo **head)
{
    struct SubInfo *q;
    struct SubInfo *p;
    q=*head;
    if(q!=NULL){
        if(q->sId==x && q==*head)
        {
            *head=q->snext;
            q->snext=NULL;
            free(q);
            return;
        }
        p=q->snext;
        while(p->sId!=x && p!=NULL)
        {
            q=q->snext;
            p=p->snext;
        }
        if(p->sId==x){
            q->snext=p->snext;
            free(p);
        }
        return;
    }   
}
/*ektupwnei tin lista sundromitwn*/
void SL_Print(struct SubInfo **head)
{
    int i;
    struct SubInfo *q;
    q=*head;
    while(q!=NULL)
    {
        printf("\n\tSUBSCRIBERID = %d, GROUPLIST = ",q->sId);
        for(i=0; i<MG; i++)
        {
            printf("\n\t%d ,TREELIST = ",G[i].gId);
            if(q->tgp[i]!=(struct TreeInfo*)1)
            {
                print_LO_BST(&(q->tgp[i]),i);
            }
        }
        q=q->snext;
        printf("\n");
    }
}
/*kanei print gia to gegonos s*/
void SL_PRINT_FOR_S(struct SubInfo **head)
{
    int i;
    struct SubInfo *q;
    q=*head;
    while(q!=NULL)
    {
        printf("%d ",q->sId);
        q=q->snext;
    }
}

/*diagrafei ena komvo apo to dentro me itm, itm kai epistrefei ti riza tou dentrou, o algorithos akoloythei tin logikh pou didaxthikame 
sto mathima */
struct Info *BSI_Delete(struct Info **root, int itm)
{
    struct Info *p;
    struct Info *tmp;
    struct Info *y;
    struct Info *x;
    /*ean uparxei,mono totw mporw na to diagrapsw*/
    if(BST_LookUp(root,itm)==1)
    { 
        p=*root;
        while(p!=NULL && itm!=p->itm)
        {
            if(itm<p->itm)
            {
                p=p->ilc;
            }else{
                p=p->irc;
            }
        }
        if(p->ilc==NULL || p->irc==NULL)
        {
            y=p;
        }else{
            y=minV(p->irc);
        }
        if(y->ilc!=NULL)
        {
            x=y->ilc;
        }else
        {
            x=y->irc;
        }
        if(x!=NULL)
        {
            x->ip=y->ip;
        }
        if(y->ip==NULL)
        {
            *root=x;
            return x;
        }else if(y==y->ip->ilc)
        {
            y->ip->ilc=x;
        }else{
            y->ip->irc=x;
        }
        if(y!=p)
        {
            p->itm=y->itm;
            p->iId=y->iId;
        }
        return *root;
    }
}

/*eisagei enan sindromiti stin lista sundromitvn taksinomimena mono ean den uparxei allos sundromitis me to idio sId*/
void SL_Insert(int x, int sId, struct SubInfo **head,int *gids_arr,int size_of_gids_arr)
{

    struct SubInfo *q;
    struct SubInfo *pq;
    struct SubInfo *p;
    int i;
    q=*head;
    p=NULL;
    if(SL_LookUp(sId,head)==0){
        while(q!=NULL && q->sId<sId)
        {
            p=q;
            q=q->snext;
        }
        pq = (struct SubInfo *)malloc(sizeof(struct SubInfo));
        pq->stm=x;
        pq->sId=sId;
        /*gia tis omades pou den endiafretai*/
        for(i=0; i<MG; i++)
        {
            pq->sgp[i]=(struct TreeInfo*)1;
        }
        /*gia tin omades pou endiaferetai*/
        for(i=0; i<size_of_gids_arr-1; i++)
        {   
            /*ean paei na eggrafei se omada pou den uparxei proxwraei na dei tis epomenes*/
            if(*(gids_arr+i)>MG || *(gids_arr+i)<1)
            {
                continue;
            }
            pq->sgp[*(gids_arr+i)-1]= NULL;
            L_Insert(sId,&(G[*(gids_arr+i)-1].gsub));
        }
        /*gia tis omades pou den endiafretai*/
        for(i=0; i<MG; i++)
        {
            pq->tgp[i]=(struct TreeInfo*)1;
        }
        /*gia tin omades pou endiaferetai*/
        for(i=0; i<size_of_gids_arr-1; i++)
        {   
            /*ean paei na eggrafei se omada pou den uparxei proxwraei na dei tis epomenes*/
            if(*(gids_arr+i)>MG || *(gids_arr+i)<1)
            {
                continue;
            }
            pq->tgp[*(gids_arr+i)-1]= NULL;
        }
        pq->snext=q;
        if(p==NULL){
            *head=pq;
        }else{
            p->snext=pq;
        }
    }
}

/*epistrefei enan akeraio , to x edw einai to Id to diko mas */
int Universal_Hash_Function( int x)
{
    return (((a*x+b)%primeNumber)%tableSize);
}
/*gia insert sto hash "sumvouleuomaste" prwta tin UHF se pio index tou pinaka pou deixnei se lista prepei na mpei kai to vazoume meta sti lista */
void HT_Insert(int sId, int stm,int *gids_arr,int size_of_gids_arr)
{
    int index = Universal_Hash_Function(sId);
    SL_Insert(stm, sId, (T+index),gids_arr,size_of_gids_arr);
}
/*"sumvouleuomaste" thn UHF se poio index tou hash table pou deixnei se lista vrisketai ayto to sId kai meta pame sti lista kai to diagrafoyme*/
void HT_Delete(int sId)
{
    int index = Universal_Hash_Function(sId);
    SL_Delete(sId, (T+index));
}
/*"sumvouleuomaste" thn UHF se poio index tou hash table vrisketai pou deixnei se lista ayto to sId , psaxnoume ti lista kai epistrefoume ton sub ean vrethei alliws 
epistrefoume null*/
struct SubInfo *  HT_LookUp(int sId)
{
    int index = Universal_Hash_Function(sId);
    return SL_LookUp(sId, (T+index));
}


/*voithitiki sunartisi gia print*/
void HT_Print()
{
    int i;
    printf("\nSUBSCRIBERLIST = ");
    for(i=0; i<tableSize; i++)
    {
        SL_PRINT_FOR_S((T+i));
    }
    printf("\n");
    for(i=0; i<MG; i++)
    {
        printf("\tGROUPID = %d, ", G[i].gId);
        L_Print(&(G[i].gsub));
        printf("\n");
    }
}
/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @param m Size of the hash table.
 * @param p Prime number for the universal hash functions.
 *
 * @return 0 on success
 *         1 on failure
 */
int initialize(int m, int p){
    int i;
    tableSize=m;
    primeNumber=p;
    T = (struct SubInfo **)malloc(m*sizeof(struct SubInfo *));
    /*onomata omadwn 0-MG,roots dentrou kai head listas na deixnoun se null*/
    for(i=0;i<MG; i++)
    {
        G[i].gId=i+1;
        G[i].gr=NULL;
        G[i].gsub=NULL;
                
    }
    /*oi listes pou deixnei to hash table megethous m na deixnoun se null*/
    for(i=0; i<m; i++)
    {
        *(T+i)=NULL;
    }
    /*a,b pou tha xreiastoume gia thn UHF*/
    a = (rand()%(p-1))+1;
    b = rand()%(p);

    return EXIT_SUCCESS;
}
FREE_POST_ORDER_INFO(struct Info *root)
{
    if((root)==NULL)
    {
        return;
    }
    FREE_POST_ORDER_INFO(((root)->ilc));
    FREE_POST_ORDER_INFO(((root)->irc));
    free(root);
}
FREE_POST_ORDER_TREE_INFO(struct TreeInfo *root)
{
    if((root)==NULL)
    {
        return;
    }
    FREE_POST_ORDER_TREE_INFO(((root)->tlc));
    FREE_POST_ORDER_TREE_INFO(((root)->trc));
    free(root);
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    int i,j;
    struct Subscription *r;
    struct SubInfo *head;
    for(i=0; i<MG; i++)
    {
        FREE_POST_ORDER_INFO((G[i].gr));
        while(G[i].gsub!=NULL)
        {
            r=G[i].gsub;
            G[i].gsub=G[i].gsub->snext;
            free(r);
        }
    }
    for(i=0; i<tableSize; i++)
    {
        while(T[i]!=NULL)
        {
            head=T[i];
            T[i]=T[i]->snext;
            for(j=0; j<MG;j++)
            {
                if(head->tgp[j]!=(struct TreeInfo*)1)
                {
                    FREE_POST_ORDER_TREE_INFO((head->tgp[j]));
                }
            }
            free(head); 
        }
    }
    for(i=0; i<tableSize; i++)
    {
        free(T[i]);
    }
    return EXIT_SUCCESS;
}

/*voiithitikh sunasrtisi gia print*/
void print_GroupID_Info()
{
    int i;
    for(i=0; i<MG; i++)
	{
		printf("\tGROUPID = %d, INFOLIST = ", G[i].gId);
		print_BST(&(G[i].gr));
		printf("\n");
	}
}



/**
 * @brief Insert info
 *
 * @param iTM Timestamp of arrival
 * @param iId Identifier of information
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Insert_Info(int iTM,int iId,int* gids_arr,int size_of_gids_arr){
    int i;
    /*opws fasi a mono p twra tis eisagw se BSI */
	for(i=0; i<size_of_gids_arr-1; i++)
	{
	    BST_Insert(iTM, iId, &(G[*(gids_arr+i)-1].gr), gids_arr ,size_of_gids_arr);
	}
	printf("\nI %d %d DONE\n",iTM,iId);
	print_GroupID_Info();
    return EXIT_SUCCESS;
}
/**
 * @brief Subsriber Registration
 *
 * @param sTM Timestamp of arrival
 * @param sId Identifier of subscriber
 * @param gids_arr Pointer to array containing the gids of the Event.
 * @param size_of_gids_arr Size of gids_arr including -1
 * @return 0 on success
 *          1 on failure
 */
int Subscriber_Registration(int sTM,int sId,int* gids_arr,int size_of_gids_arr){
    HT_Insert(sId, sTM, gids_arr, size_of_gids_arr);
    HT_Print();
    return EXIT_SUCCESS;
}

/*elegxw ean to x uparxei to LO_BST kai epistrefw 1 ean uparxei kai 0 an den uparxei, x==ttm*/
int LO_BST_LookUp(struct TreeInfo **root,int x)
{
    struct TreeInfo *p;
    p=*root;
    if(p->ttm==x && p->tlc==NULL &&p->trc==NULL)
    {
        *root=NULL;
        return 1;
    }
    while(p!=NULL && x!=p->ttm)
    {
        if(x<p->ttm)
        {
            p=p->tlc;
        }else{
            p=p->trc;
        }
    }
    if(p!=NULL)
    {
        return 1;
    }else{
        return 0;
    }
}

/*ektypwnw to LO_BST me endodiatetagmeni gia na ta emfanizei se auksousa
wstoso tsekarw ean i riza kai ena paidi einai to idio , na min ta amfanizei duo fores,ousiasistika ektypwnei mono ta fulla*/
void print_LO_BST(struct TreeInfo **root, int i)
{
    struct TreeInfo *p;
    int prev_id;
    p=*root;
    if(p==NULL)
    {
        return;
    }
    prev_id=p->tId;
    print_LO_BST(&(p->tlc),i);
    /*na ta emfanizei mono mia fora*/
    if(p->tlc==NULL && p->trc==NULL)
    {
        printf("%d ",p->tId);
        printf("(%d), ",G[i].gId);
    }
    print_LO_BST(&(p->trc),i);
}

/*voithitiki sunartiis gia na vroume ton prwigoume mikrotero stin endo diasxisi */
struct TreeInfo * FIND_PREV_MIN(struct TreeInfo **p)
{
    struct TreeInfo *r;
    struct TreeInfo *q;
    struct TreeInfo *prev_q;
    prev_q=NULL;
    /*int find=0;*/
    q=*p;
    if(q->tp!=NULL)
    {
        prev_q=q;
        q=q->tp;
    }
    while(q->tp!=NULL)
    {
        if(prev_q==q->tlc)
        {
            prev_q=q;
            q=q->tp;
        }else{
            break;
        }
    }
    /*aristerotero || trigwno*/
    if(prev_q==q->tlc || prev_q==NULL )
    {
        return NULL;
    }
    q=q->tlc;
    while(q->trc!=NULL)
    {
        q=q->trc;
    }
    return q;     
}
/*kanoume insert sto LO_BST. Xrisimopoume ton kwdika apo to aplo BST kai ulopoioume tautoxrona tin lista metaksu twn fulwn tou dentrou*/
void LO_BST_Insert(struct TreeInfo **root, int x,int tId)
{
   
    struct TreeInfo * p;
    struct TreeInfo *q;
    struct TreeInfo *prev = NULL;
    struct TreeInfo *list_prev;
    p=*root;

    while (p!=NULL)
    {
        if(p->ttm==x)
        {
            return ;
        }
        prev=p;
        if(x<p->ttm)
        {
            p=p->tlc;
        }else{
            p=p->trc;
        }
    }
    
    if(prev==NULL)
    {
        q = (struct TreeInfo *)malloc(sizeof(struct TreeInfo));
        q->ttm=x;
        q->tId=tId;
        q->tlc=NULL;
        q->trc=NULL;
        q->next=NULL;
        q->tp=NULL;
        *root=q;
        return;
    }
    /*ean exoume prev ftiaxnoume duo paidia kai ta gemizoume katallila*/
    prev->tlc=(struct TreeInfo *)malloc(sizeof(struct TreeInfo));
    prev->tlc->next=NULL;
    prev->tlc->tlc=NULL;
    prev->tlc->trc=NULL;
    prev->trc=(struct TreeInfo *)malloc(sizeof(struct TreeInfo));
    prev->trc->next=NULL;
    prev->trc->tlc=NULL;
    prev->trc->trc=NULL;
    /*elegxoume p tha mpei ti*/
    if(x<prev->ttm)
    {
        prev->tlc->tId=tId;
        prev->tlc->ttm=x;
        prev->trc->ttm=prev->ttm;
        prev->trc->tId=prev->tId;
        prev->ttm=prev->tlc->ttm;
        prev->tId=prev->tlc->tId;
    }else{
        prev->tlc->ttm=prev->ttm;
        prev->tlc->tId=prev->tId;
        prev->trc->ttm=x;
        prev->trc->tId=tId;
    }
    /*pateras twn neon paidwn o prev*/
    prev->tlc->tp=prev;
    prev->trc->tp=prev;
    /*ftiaxnoume tin alisida*/
    prev->tlc->next=prev->trc; 
    prev->trc->next=prev->next;
    prev->next=NULL;
    list_prev = FIND_PREV_MIN(&(prev));
    if(list_prev!=NULL)
    {
        list_prev->next=prev->tlc;
    }
    return;     
}

/*voithitiki gia to prune*/
void visitInfo(struct Info **r,int tm,int i)
{
    struct Subscription *head;
    struct SubInfo *subsc;
    /*ean to itm<=tm*/
    if((*r)->itm<=tm)
    {
        head=G[i].gsub;
        while(head!=NULL)
        {
            /*gia kathe sundromiti p einai eggegrammenos stin omada*/
            subsc=HT_LookUp(head->sId);
            if(subsc!=NULL)
            {
                /*prosthetw sto dentro katanalwsis tou autin tin pliroforia, to dentro katanalwseis einai to LO_BST*/
                LO_BST_Insert(&(subsc->tgp[i]),(*r)->itm,(*r)->iId);
            }
            head=head->snext;
        }
        /*otan tha ta exw perasei se olous tous undromites p endiaferontai, svinw tin pliroforia apo to dentro pliroforiwn*/
       BSI_Delete(r,(*r)->itm);
    }
}

/*kanw postOrder gia na eimai sigouri oti ola ta apo katw fila kathe fora einai swsta kai den tha xreiastei na ksana kanw diasxisi*/
void postOrder(struct Info **r, int tm, int i)
{
    if((*r)==NULL)
    {
        return;
    }
    postOrder(&((*r)->ilc),tm,i);
    postOrder(&((*r)->irc),tm,i);
    visitInfo(r,tm,i);
}

void PRINT_SUBLIST(int i)
{
    struct Subscription *head;
    head=G[i].gsub;
    while(head!=NULL)
    {
        printf("%d ",head->sId);
        head=head->snext;
    }
}

/**
 * @brief Prune Information from server and forward it to client
 *
 * @param tm Information timestamp of arrival
 * @return 0 on success
 *          1 on failure
 */

int Prune(int tm){
    int i;
    printf("\nR DONE\n");
    for(i=0; i<MG; i++)
    {
        postOrder(&(G[i].gr),tm,i);
        printf("\n\tGROUPID = %d, ",G[i].gId);
        printf("INFOLIST = ");
        print_BST(&(G[i].gr));
        printf(", SUBLIST = ");
        PRINT_SUBLIST(i);
    }
    for(i=0; i<tableSize; i++)
    {
        SL_Print(T+i);
    }
    return EXIT_SUCCESS;
}
/**
 * @brief Consume Information for subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Consume(int sId){

    int i;
    struct TreeInfo *prev_sgp=NULL;
    struct SubInfo * s;
    printf("\nC %d DONE",sId);
    s = HT_LookUp(sId);
    if(s!=NULL)
    {
        for(i=0; i<MG; i++)
        {
            printf("\n\tGROUPID = %d, TREELIST = ", G[i].gId);
            /*prepei na endiaferetai o sundromitis gia autin tin pliroforia kai t root tou dentrou katanalwseis na min einai null*/
            if(s->tgp[i]!=(struct TreeInfo*)1 && s->tgp[i]!=NULL)
            {
                prev_sgp = s->sgp[i];
                /*ean o sgp einai null simainei oti den exw kanei akoma katanalwsi kapoias pliroforias*/
                if(s->sgp[i]==NULL)
                {
                    s->sgp[i]=s->tgp[i];
                }               
                while(s->sgp[i]->tlc!=NULL)
                {
                    s->sgp[i]=s->sgp[i]->tlc;
                }
                if(s->sgp[i]->next!=NULL || prev_sgp==NULL)
                {
                    if(prev_sgp!=NULL)
                    {
                        s->sgp[i]=s->sgp[i]->next;
                    }
                    while(s->sgp[i]->next!=NULL)
                    {
                        printf("%d ",s->sgp[i]->tId);
                        s->sgp[i]=s->sgp[i]->next;
                    }
                    printf("%d ",s->sgp[i]->tId);

                }
                /*deixnei panta sto deksiotero fullo, dld sto telos tis listas*/
                printf(", NEWSGP = %d",s->sgp[i]->tId);
            }
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
/**
 * @brief Delete subscriber
 *
 * @param sId Subscriber identifier
 * @return 0 on success
 *          1 on failure
 */
int Delete_Subscriber(int sId){
    int i;
    /*ton diagrafw kai apo to hash table */
    HT_Delete(sId);
    /*kai apo tis omades p endiaferetai kai htan eggegramenos*/
    for(i=0; i<MG; i++)
    {
        L_Delete(sId,&(G[i].gsub));
    }
    HT_Print();
    return EXIT_SUCCESS;
}
/*voititiki gia na metrousiume tous subs*/
int every_list_sub(struct SubInfo **head)
{
    struct SubInfo *h;
    int subs=0;
    h=*head;
    while(h!=NULL)
    {
        subs = subs + 1;
        h=h->snext;
    }
    return subs;
}
/*voithitiki gia na metrisoume tous subs*/
int numberOfSubscriber()
{
    int i;
    int every_list=0;
    for(i=0; i<tableSize; i++)
    {
        every_list=every_list + every_list_sub((T+i));
    }
    return every_list;
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){

    int no_sub,i;
    printf("\nP DONE\n");
    for(i=0; i<MG; i++)
    {
        printf("\n\tGROUPID = %d, INFOLIST = ",G[i].gId);
        print_BST(&(G[i].gr));
        L_Print(&(G[i].gsub));
    }
    for(i=0; i<tableSize; i++)
    {
        SL_Print(T+i);
    }
    no_sub = numberOfSubscriber();
    printf("\nNO_GROUPS = %d",MG);
    printf(" NO_SUBSCRIBERS = %d \n",no_sub);
    return EXIT_SUCCESS;
}