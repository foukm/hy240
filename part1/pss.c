/***************************************************************
 *
 * file: pss.h
 *
 * @Author  Nikolaos Vasilikopoulos (nvasilik@csd.uoc.gr)
 * @Version 20-10-2020
 *
 * @e-mail       hy240-list@csd.uoc.gr
 *
 * @brief   Implementation of the "pss.h" header file for the Public Subscribe System,
 * function definitions
 *
 *
 ***************************************************************
 */

 /*Foukaki Maria 
 csd4249*/
#include <stdio.h>
#include <stdlib.h>

#include "pss.h"
struct Group G[MG]; 
struct SubInfo *headSI;
/**
 * @brief Optional function to initialize data structures that
 *        need initialization
 *
 * @return 0 on success
 *         1 on failure
 */

void print_GroupId_InfoList(int sublist);
int DL_LookUp(int x,struct  Info **head,struct Info **tail);
/* tin DL_Insert tin xrisimopoiume gia na eisagoume mia plhroforia stin lista plhroforiwn
    to x(itm) einai ekeino me vasi to opoio taksinomeitai kai einai taksinomimeni se auxousa seira,
    diladi sthn arxi tis lista paramenoun oi palaioteres plirofories
*/
void DL_Insert(int x, int iId, struct Info **head,struct Info **tail, int *gids_arr,int size_of_gids_arr)
{
    struct Info *q,*p,*tmp;
    int j;
    q=*head;
    /*eksetazoume ean i lista einai keni kai prepei na valoume to prwto stoixeio*/
    if(q==NULL)
    {
        q = (struct Info *)malloc(sizeof(struct Info));
        q->itm=x;
		q->iId=iId;
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
        /*ftiaxnoume tous pointer na deixnoun katalila kai ta head kai tail*/
        q->inext=NULL;
        q->iprev=*head;
        *head=q;
        *tail=q;
        return;
    }
    /*ean to neo itm pou tha erthei einai mikrotero apo ekeino p exei ekxwrithei stin arxi 
      allazw to head na deixnei se auto to neo 
      auto tha ginei mono ean den uparxei alli pliroforia me to idio iId
    */
    if(DL_LookUp(iId,head,tail)==0){
        if(q->itm>=x)
        {
        p = (struct Info *)malloc(sizeof(struct Info));
        p->iprev=*head;
        p->inext=q;
        q->iprev=p;
        p->itm=x;
        p->iId=iId;
        /*opws kai parapanw*/
        for(j=0; j<MG; j++)
            {
                p->igp[j]=0;
            }
            for(j=0; j<size_of_gids_arr-1; j++)
            {
                p->igp[(*(gids_arr+j))]=1;
            }
        *head=p;
        return;
        }
        /*se kathe alli periptwsi mexri psaxnw na vrw pou tha to ekxwrisw wste na einai taksinomimeni kata auksousa*/
        while(x>q->itm && q->inext!=NULL){
            q=q->inext;
        }
        /*stin periptwsi p ftasame sto teleutaio kai prepei na mpei to neo ws to epmeno tou ftiaxnw kai to tail*/
        if(q->inext==NULL && x>q->itm)
        {
            p = (struct Info *)malloc(sizeof(struct Info));
            p->itm=x;
            p->iId=iId;
            for(j=0; j<MG; j++)
            {
                p->igp[j]=0;
            }
            for(j=0; j<size_of_gids_arr-1; j++)
            {
                p->igp[(*(gids_arr+j))]=1;
            }
            q->inext=p;
            p->inext=NULL;
            p->iprev=q;
            *tail=p;
            return;
            
        }
        /*diaforetika*/
        p = (struct Info *)malloc(sizeof(struct Info));
        p->itm=x;
        p->iId=iId;
        for(j=0; j<MG; j++)
        {
            p->igp[j]=0;
        }
        for(j=0; j<size_of_gids_arr-1; j++)
        {
            p->igp[(*(gids_arr+j))]=1;
        }
        tmp=q->inext;
        p->iprev=q->iprev;
        q->iprev->inext=p;
        p->inext=q;
        q->iprev=p;  
        return; 
    } 
    return;
}

/*ektipwnei tin dipla taksinomimeni lista apo to head mexri na vrei null*/
 void DL_Print(struct Info **head)
 {
    struct Info *p ;
    p=*head;
    printf("INFOLIST = ");
    if(p!=NULL)
    {
        while (p!=NULL)
        {
            printf("%d ",p->iId);
            p=p->inext;
        }       
    }  
 }
/*psaxnei na dei an uparxei pliroforia me to sId
    ean uparxei epistredei 1 alliws 0*/
 int DL_LookUp(int x,struct  Info **head,struct Info **tail)
 {
    struct Info *p ;
    p=*head;
    if(p!=NULL)
    {
        while (p!=NULL)
        {
            if(p->iId==x)
            {
                return 1;
            }
            p=p->inext;
        }
        
    }
    return 0;
}

/*ean uparxei i pliroforia me to anagnwristiko iId, tin diagrafei */
void DL_Delete(int x, struct Info **head, struct Info **tail)
{
    struct Info *p,*tmp;
    p=*head;
    if(DL_LookUp(x,head,tail)==1)
    {
        while(p->iId!=x && p->inext!=NULL)
        {
            p=p->inext;
        }
        if(p==*head)
        {
            *head=p->inext;
            p->inext=NULL;
            free(p);
            return;
        }
        
        if(p->inext!=NULL)
        {
            tmp=p->iprev;
            tmp->inext=p->inext;
            p->inext->iprev=tmp;
        }else{
            tmp=p->iprev;
            *tail=tmp;
            p->iprev=NULL;
            tmp->inext=NULL;
        }
        free(p);
    }  
}

/*einai mia mi taksinomimeni, apla sundedemeni lista, thn xrisimopoioume gia na eisagoume sundromites pou endiaferontai gia 
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

/*psaxnei na dei an uparxei tetoios sundromitis sti lista sundmitwn*/
int SL_LookUp(int x, struct SubInfo **head)
{
    struct SubInfo *q;
    q=*head;
    while(q!=NULL)
    {
        if(q->sId==x)
        {
            return 1;
        }
        q=q->snext;
    }
    return 0;
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
    struct SubInfo *q;
    q=*head;
    while(q!=NULL)
    {
        printf("%d ",q->sId);
        q=q->snext;
    }
}
/*eisagei enan sindromiti stin lista sundromitvn taksinomimena mono ean den uparxei allos sundromitis me to idio sId*/
void SL_Insert(int x, int sId, struct SubInfo **head,int* gids_arr, int size_of_gids_arr)
{

    struct SubInfo *q;
    struct SubInfo *pq;
    struct SubInfo *p;
    int i;
    q=*head;
    p=NULL;
    if(SL_LookUp(sId,&headSI)==0){
        while(q!=NULL && q->stm<x)
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
            pq->sgp[i]=(struct Info*)1;
        }
        /*gia tin omades pou endiaferetai*/
        for(i=0; i<size_of_gids_arr-1; i++)
        {   
            /*ean paei na eggrafei se omada pou den uparxei proxwraei na dei tis epomenes*/
            if(*(gids_arr+i)>=MG)
            {
                continue;
            }
            pq->sgp[*(gids_arr+i)]= NULL;/*G[*(gids_arr+i)].gfirst;*/
            L_Insert(sId,&(G[*(gids_arr+i)]).ggsub);
        }
        pq->snext=q;
        if(p==NULL){
            *head=pq;
        }else{
            p->snext=pq;
        }
    }
}



/*arxikopoioume ton pinaka G na exei ws sId apo to 0 ews to MG-1
  oi pointers pou deixnoun stin arxi kai sto telos tis diplas sundedemenis listas, me tis plirofories tous arxikopoioyme me null
  akoma, ton pointer gia th lista sundromitwn ton arxikopoioume me null */
int initialize(void){
    int i=0;
    int j;
    headSI = NULL;
    for(i=0;i<MG; i++)
    {
        G[i].gId=i;
        G[i].gfirst=NULL;
        G[i].glast=NULL;
        G[i].ggsub=NULL;        
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Free resources
 *
 * @return 0 on success
 *         1 on failure
 */
int free_all(void){
    
    int i;
    struct SubInfo *q;
    struct Info *p;
    struct Subscription *r;
    while(headSI!=NULL){
        q=headSI;
        headSI=headSI->snext;
        free(q);
    }
    for(i=0; i<MG; i++)
    {
        while(G[i].gfirst!=NULL)
        {
            p=G[i].gfirst;
            G[i].gfirst=G[i].gfirst->inext;
            free(p);
        }
        while(G[i].ggsub!=NULL)
        {
            r=G[i].ggsub;
            G[i].ggsub=G[i].ggsub->snext;
            free(r);
        }
    }
    return EXIT_SUCCESS;
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
	for(i=0; i<size_of_gids_arr-1; i++)
	{
		DL_Insert(iTM, iId, &(G[*(gids_arr+i)].gfirst), &(G[*(gids_arr+i)].glast), gids_arr ,size_of_gids_arr);
	}
	printf("\nI %d %d DONE\n",iTM,iId);
	print_GroupId_InfoList(0);
    return EXIT_SUCCESS;
}

void print_GroupId_InfoList(int sublist)
{
    int i;
    for(i=0; i<MG; i++)
	{
		printf("\tGROUPID = %d, ", G[i].gId);
		DL_Print(&(G[i].gfirst));
        if(sublist)
        {
            L_Print(&(G[i].ggsub));
        }
		printf("\n");
	}
}

void sublist_group_prints()
{
    int i;
    printf("DONE\n");
    printf("\tSUBSCRIBERLIST = ");
    SL_Print(&headSI);
    printf("\n");
    for(i=0; i<MG; i++)
    {
        printf("\tGROUPID = %d, ", i);
        L_Print(&(G[i].ggsub));
        printf("\n");
    }
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
    int i;
    SL_Insert(sTM, sId, &headSI, gids_arr, size_of_gids_arr);
    printf("\nS %d %d ",sTM,sId);
    for(i=0; i<size_of_gids_arr-1; i++)
    {
        printf("%d ",*(gids_arr+i));
    } 
    sublist_group_prints();
    return EXIT_SUCCESS;
}

void print_subs(struct SubInfo **headSI)
{
    struct SubInfo *q;
    int i;
    q=*headSI;
    while (q!=NULL)
    {
        printf("\tSUBSCRIBERID = %d , GROUPLIST = ",q->sId);
        for(i=0; i<MG; i++)
        {
            if(q->sgp[i]!=(struct Info*)1)
            {
                printf("%d ",i);
            }
        }
        printf("\n");
        q=q->snext;
    }
    
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
    /*diasxisi listas*/
    struct SubInfo *q;
    q=headSI;
    if(SL_LookUp(sId,&headSI)==1){
        while(q!=NULL)
        {
            if(q->sId==sId)
            {
                break;
            }
            q=q->snext;
        }
        /*ean exei vrethei kapoios me sId */
        if(q!=NULL)
        {
            for(i=0; i<MG; i++)
            {
                if(q->sgp[i]!=(struct Info*)1 && q->sgp[i]!=G[i].glast)
                {
                    printf("GROUPID = %d, " ,i);
                    if(q->sgp[i]==NULL)
                    {
                        DL_Print(&(G[i].gfirst));
                    } else {
                        DL_Print(&(q->sgp[i]->inext));
                    }
                    q->sgp[i] = G[i].glast;
                    printf(", NEWSGP = %d\n",q->sgp[i]->iId);
                }   
            }
        }
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
    if(SL_LookUp(sId,&headSI)==1)
    {
        SL_Delete(sId,&headSI);
        for(i=0; i<MG; i++)
        {
            L_Delete(sId,&(G[i].ggsub));
        }
        printf("D %d ",sId);
        sublist_group_prints();
    }  
    return EXIT_SUCCESS;
}

/*epistrefei to athroisma ton eggegramenwn sundromitwn*/
int ret_sum_of_sub()
{
    struct SubInfo *p;
    int sum=0;
    p=headSI;
    if(p==NULL)
    {
        return 0;
    }else{
        while(p!=NULL)
        {
            sum=sum+1;
            p=p->snext;
        }
        return sum;
    }
}
/**
 * @brief Print Data Structures of the system
 *
 * @return 0 on success
 *          1 on failure
 */
int Print_all(void){
    printf("P DONE\n");
    print_GroupId_InfoList(1);
    printf("\tSUBSCRIBERLIST = ");
    SL_Print(&headSI);
    printf("\n");
    print_subs(&headSI);
    printf("\tNO_GROUPS = %d",MG);
    printf(" NO_SUBSCRIBERS = %d\n",ret_sum_of_sub());
    return EXIT_SUCCESS;
}

