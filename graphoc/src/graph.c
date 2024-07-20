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
 *  \brief  Definitions of Graph functions
 *  \author Marco M. Mosca, email: marcomichele.mosca@gmail.com
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <mcheck.h>
#include <string.h>
#include <ctype.h>
#include "graph.h"
#define strmax 200

char* new_buff()
{
  char* s;
  s=malloc(strmax*sizeof(char));
  return s;
}

void copyword(char** s1, char * s2, int d)
{
    int h=0, i=0, j=0;
    char* prov;
    
    while (d > 0)
    {
		if (j==0) {prov=new_buff();};
		if ((s2[h] == '\0') || (s2[h] == ':') || (s2[h] == '$'))
		{
			prov[j]='\0';
			s1[i]=malloc((strlen(prov)) * sizeof(char)+1);
			memcpy(s1[i], prov, strlen(prov)+1); 
			i++; 
			free(prov);
			h++;
			j=0;
			d--;
		} else {
			prov[j] = s2[h];
			h++; j++;
		}
    }
}

void print_graph (graph_t* g)
{
	errno=EINVAL;
	if (g==NULL);
	else {
		int  i, tot=g->size; 
		node_t* node;
		edge_t* ag;
		char* s;

		node = g->node;
		printf("\n");
		for(i=0; i<tot; i++)
		{
			s=NULL; s=(node+i)->label;
			if (s != NULL)
			{
				fprintf(stdout, "%s ->", s);
				ag = (node+i)->adj;
				while (ag != NULL)
				{
					fprintf(stdout, " (%d)%s--%.1f -> ", ag->label,(node+(ag->label))->label, ag->weight);
					ag = ag->next;
				}
				printf("\n");
			}
		} printf("\n");
	}
}

graph_t * create_graph (unsigned int n, char **labels)
{
	graph_t* k;
	node_t* nodo;
	unsigned int i=0;
	int len=0;
	char* s;
	
	errno = EINVAL;
	if ((labels == NULL) || (n==0)) {return NULL;};
	errno = ENOMEM;
	if ((k=malloc(sizeof(graph_t))) == NULL) {return NULL;};
	nodo=malloc(n * sizeof(node_t));
	if (nodo == NULL) {free(k);return NULL;};
	k->size = n;
	
	while (i<n && labels[i] != NULL)
	{
		len = strlen((const char*) labels[i]); 
		s=malloc((len) * sizeof(char)+1);
		if (s== NULL) {return NULL;};
		strcpy(s,(const char*) labels[i]);
		(nodo+i)->label = s; 

		(nodo+i)->adj = NULL;
		i++; 
	}
	(nodo+i)->label=NULL;
	k->node = nodo;
	return k;
}

void free_graph (graph_t** g)
{
	errno = EINVAL;
	if ((g==NULL) || (*g==NULL)) g=NULL;
	else {
		int n=(*g)->size, i=0;
		node_t* nodo;
		edge_t* a, *anext;
		
		errno = EINVAL;
		if (*g == NULL) *g=NULL;
		errno = ECANCELED;
		nodo=(*g)->node;
		while (i<n)
		{
			free((nodo+i)->label);
			if ((nodo+i)->adj != NULL) 
			{
				a=(nodo+i)->adj;
				while (a != NULL) 
					{
						anext=a->next;
						free(a); 
						a=anext;
					}
			};
			i++;
		}
		free((*g)->node); (*g)->node=NULL;
		free(*g); *g = NULL;
	}
}


graph_t* copy_graph (graph_t* g)
{
	char** labels;
	int 	tot, i;
	unsigned int len; 
	graph_t* p;
	node_t* nodeg, *nodep;
	char* s;
	edge_t* ag, *tail;
		
	errno=EINVAL;
	if (g == NULL) {return NULL;};
	errno=ENOMEM;
	tot=g->size;
	labels = malloc(sizeof(char*) * tot);
	if (labels==NULL){return NULL;};
	i=0;
	while(i<tot){labels[i]=malloc(sizeof(char) * MAXLABEL);i++;}
	nodeg=g->node;
	
	i=0;
	while((nodeg+i)->label != NULL)
	{
		len = strlen((const char*) ((nodeg+i)->label));
		s = malloc((len) * sizeof(char)+1);
	/**     labels[i]=malloc((len+1) * sizeof(char));*/
		if (s == NULL) {return NULL;};
		strcpy(s,(const char*) ((nodeg+i)->label));
		strcpy(labels[i],s);
		free(s);
		i++;
	}
	
	p = create_graph(tot, labels);
	i=0;
	while(i<tot){free(labels[i]);i++;}
	free(labels);
	nodep = p->node; 
	i=0;
	while((nodeg+i)->label != NULL)
	{
		ag = (nodeg+i)->adj;
		while(ag != NULL)
		{
		tail=malloc(sizeof(edge_t));
		tail->label = ag ->label;
		tail->weight = ag ->weight;
		tail->next = (nodep+i)->adj;
		(nodep+i)->adj = tail;
		ag = ag->next;
		}
		i++;
	}
	p->node = nodep;
	return p;
}


int add_edge (graph_t * g, char* e) 
{
	int j=0;
	unsigned int f;
	int i=0;
	double d;
	node_t* node;
	edge_t* a, *tail; 
	char *source, *dest, *weight, **dati; 
	bool_t found=FALSE;
	
	errno=EINVAL;
	if (g == NULL) {return -1;};
	if (e == NULL) {return -1;};
	node = g->node;
	
	dati=malloc(3 * sizeof(char*));
	copyword(dati, e , 3);
	source=dati[0];
	dest=dati[1];
	weight=dati[2];
	i=0;
	while(weight[i] != '\0') 
	{
		if (weight[i]== '.') {found=TRUE;i++;}
		else i++;
	}
	if(found == FALSE) {free(source); free(dest);free(weight); free(dati);return -1;};
	d = atof(weight);
	free(weight);
	i=0;
	
	while((node+i)->label != NULL)
	{
		if (strcmp((node+i)->label, source) == 0) 
		{
			j=0;
			while((node+j)->label != NULL) 
			{
				if (strcmp((node+j)->label, dest) == 0) 
				{
					f=j;
					tail = (node+i)->adj;
					while (tail != NULL) 
					{
						if (tail->label == f) {errno=ECANCELED;free(source); free(dest);free(dati); return -1;};
						tail=tail->next;
					}
					a=malloc(sizeof(edge_t));
					if (a == NULL) {free(source), free(dest); free(dati);return -1;};
					a ->label = f;
					a ->weight = d;
					a ->next=(node+i)->adj;
					(node+i)->adj = a;
					free(source);
					free(dest);
					free(dati);
					return 0;
				};
				j++;
			}
			errno=EINVAL;free(source); free(dest); free(dati); return -1;
		} ;
		i++;
	}
	errno = EINVAL;free(source); free(dest); free(dati);
	return -1;
}

int is_node(graph_t* g, char* ss)
{
	int i;
	node_t* nodo;
	
	errno=EINTR;
	if (g==NULL) return -1;
	nodo=g->node;
	i=0;
	while ((nodo+i)->label != NULL)
	{
		if (strcmp((nodo+i)->label, ss)==0) return i;
		i++;
	}
	return -1;
}

bool_t is_edge(graph_t* g, unsigned int n1, unsigned int n2)
{
	bool_t nfound=FALSE;
	unsigned int i;
	node_t* nodo;
	edge_t* ag;
	
	errno=EINTR;
	if(g==NULL) {return -1;};
	i=0;
	nodo = g->node;
	while ((i != n1) && (i<g->size)) {i++;}
	if (i == g->size-1) {return nfound;};
	ag = (nodo+i)->adj;
	while(ag != NULL)
	{
		if (ag->label==n2) return nfound=TRUE;
		ag= ag->next;
	}
	return nfound;
}

int get_degree(graph_t * g, char* label)
{
	int i=0, n=0;
	
	node_t* nodo;
	edge_t* ag;
	
	errno=EINTR;
	if (g == NULL) {return -1;};
	if (label == NULL) {return -1;};
	nodo = g->node;
	while((nodo+i)->label != NULL)
	{
		if (strcmp((nodo+i)->label, label) == 0) 
		{
			ag = (nodo+i)->adj; 
			while(ag != NULL) {ag = ag->next; n++;}
			return n;
		}
		else {i++;}
	}  
	return -1;
}

int get_node_count(graph_t* g)
{
	errno= EINTR;
	if (g == NULL) {return -1;};
	return g->size;
}

int get_edge_count(graph_t* g)
{
	int i, e;
	node_t* nodo;
	edge_t* ag;
	
	errno=EINTR;
	if(g==NULL) {return -1;};
	nodo = g->node;
	i=0; e=0;
	while((nodo+i)->label != NULL)
	{
		ag = (nodo+i)->adj;
		while(ag != NULL) {e++;ag = ag->next;}
		i++;
	}
	return e;
}

int check_label(char* label)
{
	int i=0, bool=1;

	while(label[i] != '\0')
	{
		if (!(isupper(label[i])) && !(isspace(label[i]))) {return bool=0;}
		i++;
	}
	return bool;
}

int check_weight(char* s)
{
	int i=0, estratto=0, colons=0;
	while (s[i] != '\0')
	{
		if (colons==2)
		{
			estratto= atof(s+i);
			break;
		};
		if (s[i] == ':')
		{
			colons++;
		};
		i++;
	}
	if (colons<2) return 0;
	return estratto;
}

char* get_input_f(FILE* fd_n)
{
	char* input;
	int i=0;
	
	input=malloc(MAXLABEL * sizeof(char));
	fgets( input, MAXLABEL, fd_n );
	if (feof(fd_n)) {free(input);return NULL;}
	while(input[i] != '\n') i++;
	input[i]='\0';
	return input;
}


graph_t* load_graph (FILE * nodefile, FILE * edgefile)
{
	int i, b;
	unsigned int c;
	char** snod, *s, *a;
	graph_t* grf;
	
	errno=ENOMEM;
	if ((nodefile == NULL) || (edgefile == NULL)) {errno=EINVAL;return NULL;};
	if((snod = malloc(sizeof(char*) *MAXLABEL))==NULL) return NULL;
	
	i=0; 
	
	while((s=get_input_f(nodefile)) != NULL) 
	{
		if ((check_label(s)) == 0) 
		{     
			free(s);
			return NULL;
		};
		snod[i]=malloc(sizeof(char) * (strlen(s))+1);
		memcpy(snod[i],s, strlen(s)+1);
		i++;
		free(s);
	}
	free(s);
	c=i;
	grf = create_graph(c, snod); 
	
	i--;
	while(i>=0) {free(snod[i]);i--;}
	free(snod);
	
	while ((a=get_input_f(edgefile)) != NULL)
	{
		b=check_weight(a);
		if ((b == -1) || (b == 0)) exit(EXIT_FAILURE);
		add_edge(grf, a);
		free(a);
	}
	free(a);
	return grf;  
}


int save_graph (FILE * nodefile, FILE * edgefile, graph_t* g)
{
	int i=0, len;
	node_t* node;
	edge_t* ag;
	double d;
	unsigned int j;
	char* s;
	
	if((nodefile==NULL) || (edgefile==NULL) || g==NULL) {errno=EINTR;return -1;};
	
	s=malloc(3 * sizeof(char));
	errno=EIO;
	node = g->node;
	while((node+i)->label != NULL)
	{
		if ((fprintf(nodefile, "%s\n" ,(node+i)->label)) < 0) {return -1;};
		ag = (node+i)->adj;
		while(ag != NULL)
		{
			d=ag->weight;
			sprintf(s,"%f",d);
			j=ag->label;
			len = strlen((node+i)->label)+strlen((node+j)->label)+strlen(s);
			if((fprintf(edgefile, "%s:%s:%.1f\n", (node+i)->label,(node+j)->label,d))<0) {return -1;};
			ag=ag->next;
		}
		i++;
	} 
	free(s);
	return 0;
}
