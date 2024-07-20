/**
 *  This program is free software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation, either version 3
 *  of the License, or (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
 *  GNU General Public License for more details.
 * 
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see https://www.gnu.org/licenses/.
 *  
 *  \brief  Definitions of shortest path functions
 *  \author Marco M. Mosca, email: marcomichele.mosca@gmail.com
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "spaths.h"
#define INFINITY (-1.0)
#define UNDEF ((unsigned int) -1)

struct dijkstra_queue
{
    unsigned int indice;
    struct dijkstra_queue *next;
};
typedef struct dijkstra_queue coda_t;

/*
	Find the minimum distance node.
*/
unsigned int find_min_distance(double *d, coda_t* lista)
{
	double min;
	unsigned int ind=0;
	coda_t* tail=lista;
	
	min=d[tail->indice];
	ind = tail->indice;
	while(tail != NULL)
	{
		if (min > d[tail->indice]) {min = d[tail->indice]; ind=tail->indice;};
		tail=tail->next;
	}
	return ind;
}

/**
  Find the minimum distance node and remove it from the queue.
*/
coda_t* extractmin(coda_t* lista,double *d,unsigned int *mind)
{
	coda_t *tailnx, *tail, *head;
	
	*mind = find_min_distance(d,lista);
	tail = lista;
	head = lista;
	
	if ((*mind == tail->indice) && (tail != NULL)) 
	{
		tailnx=tail->next; 
		free(tail);
		tail = tailnx;
		return tail;
	};
		
	while((tail != NULL) && (tail->indice != *mind))
	{
		tailnx=tail;
		tail=tail->next;
	}
	if (tail != NULL) {tailnx->next = tail->next; free(tail);}
	else printf("mind non trovato\n");
	return lista;
}

coda_t* insertesta(coda_t* head, unsigned int ind)
{
	coda_t* a;
	
	a=malloc(sizeof(coda_t));
	a->indice = ind;
	a->next = head;
	head = a;
	return head;
}

/**
  Start from the destination and return the minimum path.
*/
char * mems(unsigned int n1, unsigned int n2,unsigned int * prec, char * s, node_t* nodo)
{
	int len=0;
	if (n1==n2) {sprintf(s,"%s%c", (nodo+n2)->label, '$'); return s;};
	mems(n1,prec[n2],prec,s, nodo);
	s = strcat(s, (const char*) (nodo+n2)->label);
	len = strlen(s);
	sprintf(s+len,"%c",'$');
	return s;
}

char * spath_to_string(graph_t * g, unsigned int n1, unsigned int n2,  unsigned int * prec)
{
	int len;
	char* s;
	node_t* nodo=g->node;
	
	if (prec[n2] == UNDEF) {return NULL;};
	s=malloc(sizeof(char) * MAXLABEL);
	s=mems(n1, n2, prec,s,nodo);
	len=strlen(s);
	s[len-1]=0;
	return s;
}

/**
  - Initialize predecessors and distance vector
  - Get the minimum path from the queue to keep traversing outgoing edges
  - If a distance from the source to any other node is modified, insert the node in list...
	because since the distance has been modified, all outgoing edges might be updated
*/
double* dijkstra (graph_t* g, unsigned int source, unsigned int** predecessors)
{
	double *d;
	unsigned int mind=0, i;
	node_t* nodeg;
	edge_t* ag;
	coda_t* a; 
	
	if ((g==NULL) &&(source==0)) {return NULL;};
	if (predecessors != NULL)
	{
		if((*predecessors=malloc(sizeof(unsigned int) * g->size))==NULL) {return NULL;};
	};
	d=malloc(g->size * sizeof(double));
	
	nodeg = g->node;
	a=NULL;
	
	if (predecessors != NULL) {(*predecessors)[source] = UNDEF;}; 
	d[source] = 0; 
	a = insertesta(a, source);
	for(i=0;(i<g->size) && ((nodeg+i)->label != NULL);i++) 
	{
		if (i != source) {
			if (predecessors != NULL) {(*predecessors)[i] = UNDEF;}; 
			d[i] = INFINITY;
		}
	}

	while(1)
	{
		if (a == NULL) break;
		a = extractmin(a,d, &mind); if (mind==UNDEF) {errno=EINVAL; return NULL;};
		ag = (nodeg+mind)->adj;
		while(ag != NULL)
		{
			if (d[ag->label] == INFINITY) 
			{
				d[ag->label] = (d[mind] + ag->weight);
				if (predecessors != NULL) ((*predecessors)[ag->label])=mind;
				a = insertesta(a, ag->label);
				ag=ag->next;
			}
			else {
				if ((d[mind] + ag->weight) < d[ag->label])
				{
					d[ag->label] = (d[mind] + ag->weight);
					if (predecessors!=NULL) (*predecessors)[ag->label] = mind;
					a = insertesta(a, ag->label);
				};
				ag=ag->next;
			}
		}
	}
	return d;
}
