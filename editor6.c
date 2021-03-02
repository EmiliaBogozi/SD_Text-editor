#include <stdio.h>
#include <stdlib.h>

typedef struct nod {

	char c;
	struct nod *next;
	struct nod *prev;
}nod;

void init (nod** head) {

    	*head =malloc(sizeof(nod));
	*head = NULL;
}

nod* adauga (nod **head, char new_char, nod **cursor) {

	nod *new =malloc (sizeof(nod));
	new->c = new_char;
    	new->next = NULL;
    	new->prev = NULL;
	if (*head == NULL) {
		*head = new;
		return new;
	}
	nod *aux = malloc (sizeof(nod));
	aux = *head;
	nod *auxc = *cursor;

	if(auxc->next == NULL) {
        	while (aux->next != NULL)
            		aux = aux->next;
        	aux->next = new;
        	new->prev = aux;
    	}
    	else {
        	while (aux->next != auxc->next)
            		aux = aux->next;
        	new->prev = aux;
        	new->next = auxc->next;
        	auxc->next->prev = new;
        	aux->next = new;
	}

    	return new;
}

typedef struct stiva {

    	char nume;
    	int nr_linie;
    	int nr_char;
    	struct stiva *next;
} stiva;

void init_stiva (stiva** head) {

    	*head =malloc(sizeof(stiva));
	*head = NULL;
}

void push(stiva **head, char c, int nrl, int nrc, int nr_caractere) {

	stiva *new = malloc(sizeof(stiva));
	new->nume = c;
	new->nr_char = nrc;
	new->nr_linie = nrl;
	new->next = NULL;
	if (*head == NULL) {
		*head = new;
		return;
	}
	new->next = *head;
	*head = new;
}

stiva* pop(stiva **head) {

	if (*head == NULL)
		return 0;
	stiva *aux =malloc (sizeof(stiva));
	aux = *head;
	*head = (*head)->next;
	return aux;
}

typedef struct stiva_text {

    	char nume;
    	struct stiva_text *next;
} stiva_text;

void init_stiva_text (stiva_text** head) {

    	*head =malloc(sizeof(stiva_text));
	*head = NULL;
}

void push_text(stiva_text **head, char c) {

	stiva_text *new = malloc(sizeof(stiva_text));
	new->nume = c;
	new->next = NULL;
	if (*head == NULL) {
		*head = new;
		return;
	}
	new->next = *head;
	*head = new;
}

stiva_text* pop_text(stiva_text **head) {

	if (*head == NULL)
		return 0;
	stiva_text *aux =malloc (sizeof(stiva_text));
	aux = *head;
	*head = (*head)->next;
	return aux;
}

nod* backspace (nod **head, int *contor) {

    	if((*head) == NULL ) //verificam daca lista e goala
        	return 0;
	nod *aux =malloc (sizeof(nod));
	aux = *head;
    	if(aux->c == '\n')
        	(*contor)++;
    	if(aux->next != NULL)
        	aux->next->prev = aux->prev;
    	aux->prev->next=aux->next;
     	aux=aux->prev;
    	return aux;
}

void show (nod *head) {

	while (head != NULL) {
		printf("%c", head->c);
		head = head->next;
	}
	printf("\n");
}

nod* goto_line(int nr_linie, nod **head) {

   	if((*head) == NULL )
            	return 0;

    	nod *aux =malloc (sizeof(nod));
    	aux = *head;
	int i;
    	for(i=1; i<nr_linie; i+=0) {
        	if( aux->c == '\n' )
            		i++;
        	aux = aux->next;
	}
    	if(nr_linie != 1)
      	 	return aux->prev;
    	else
        	return aux;
}

void date_cursor(nod **head, int *linie, int *poz, nod **cursor) {
 
   	if((*head) == NULL ) {
        	linie = 0;
        	poz = 0;
    	}
    	nod *aux =malloc (sizeof(nod));
    	aux = *head;
    	nod *auxc =malloc (sizeof(nod));
    	auxc = *cursor;
    	while( aux != auxc){
        	if(aux->c == '\n')
            		(*linie)++;
        	aux = aux->next;
    	}
	if(auxc->c == '\n')
        	(*linie)++;
	while( aux->c != '\n' && aux->prev != (*head)->prev ) {
        	(*poz)++;
        	aux = aux->prev;
    	}
    	if(aux->prev == (*head)->prev)
         	(*poz)++;
}

nod* goto_char(int nr_linie, int nr_char, nod **head, nod **cursor){

    	if((*head) == NULL )
            	return 0;
    	nod *aux =malloc (sizeof(nod));
    	aux = *head;
    	nod *auxc = malloc(sizeof(nod));
    	auxc = *cursor;
	if(nr_linie == 1) {
        	int i;
       		for(i=0; i<nr_char; i++)
        		aux=aux->next;
        	return aux->prev;
    	}
    	int i;
    	for(i=1; i<nr_linie; i+=0) {
        	if( aux->c == '\n' )
            		i++;
        	aux = aux->next;
    	}
    	aux=aux->prev;
	for(i=0; i<nr_char; i++)
        	aux=aux->next;
    	return aux->prev;
}

void save(nod *head, FILE *fp) {

	if(head == NULL)
		return;
    	nod *aux =malloc (sizeof(nod));
    	aux=head;
    	while(aux!=NULL) {
        	fprintf(fp,"%c",aux->c);
        	aux=aux->next;
    	}
}

nod* del_line(int k, nod **head, int nr_linii) { 

    	if((*head) == NULL )
            	return 0;
	nod *aux =malloc (sizeof(nod)); //aux e cel de la care plecam
    	aux = *head;
    	int i;
    	for(i=1;i<k;i+=0) {
        	if( aux->c == '\n' )
            		i++;
        	aux = aux->next;
    	}                                     
    	nod *aux2 = malloc (sizeof(nod)); //aux2 e cel care ajunge la final
    	aux2 = aux;                         
   	while(aux2->c != '\n' && aux2->next != NULL){
        	aux2 = aux2->next;
    	}
    	if (k==1) {  ///sterge prima linie
        	aux2 = aux2->next;
        	aux2->prev=NULL;
        	*head = aux2;
		//aux3 si aux4 sunt facuti ca sa stergem ce e de la aux pana la aux2
        	nod *aux3 = malloc (sizeof(nod));
        	aux3 = aux;
		nod *aux4 = malloc (sizeof(nod));
        	aux4 = aux->next;

        	while(aux3 != aux2 ) {
            		free(aux3);
            		aux3 = aux4;
            		aux4 = aux4 ->next;
        	}
        	return aux2;
    	}
    	else {
        	if(k == nr_linii) {  //stergem ultima linie
            		nod *aux3 = malloc (sizeof(nod));
            		aux3 = aux;
            		aux=aux->prev;
            		aux->next = NULL;
            		nod *aux4 = malloc (sizeof(nod));
            		aux4 = aux3->next;
			while(aux4 != NULL ) {
               			free(aux3);
                		aux3 = aux4;
                		aux4 = aux4 ->next;
            		}
            		free(aux3);
            		return aux;
        	}
        	else {
            		aux->prev->next = aux2->next;
            		aux2->prev = aux->prev;
           		nod *aux3 = malloc (sizeof(nod));
            		aux3 = aux;
            		nod *aux4 = malloc (sizeof(nod));
            		aux4 = aux->next;
            		while(aux3 != aux2 ) {
                		free(aux3);
                		aux3 = aux4;
                		aux4 = aux4 ->next;
            		}
			return aux2;
        	}
    	}
}


int main(int argc, char *argv[]) {
    	FILE *fp=NULL;
    	nod *lista;
    	init(&lista);
    	nod *cursor;
    	cursor = lista;

	stiva *c_undo;
    	init_stiva(&c_undo);
    	stiva_text *t_undo;
    	init_stiva_text(&t_undo);

    	stiva *c_redo;
    	init_stiva(&c_redo);
    	stiva_text *t_redo;
    	init_stiva_text(&t_redo);

    	int ok=1; /// ok=1 - text; ok=0 - comanda
    	char c;
    	char copie;
    	copie = 'a'; ///orice diferit de ':'
    	int k=0;
    	int salveaza=0;
    	int e_la_1=0;
    	while(ok != 0 || c != 'q') {
        	if(ok == 0) {
            		scanf("%c", &c);
            		if(c == ':' && copie == ':' && ok==0) {
                		ok=1;
                		k--;
            		}
            		switch(c) {
               			case 's' :
                    			fp = fopen(argv[1],"w");
                    			if(lista != NULL) {
						if(lista->c == ' ') {
                            				lista=lista->next;
                            				lista->prev=NULL;
                        			}
						//nod *aux3 = malloc (sizeof(nod));
						//nod *aux4 = malloc (sizeof(nod));
						//aux3 = lista;
						//aux4 = lista->next;
						//while(aux4 != NULL) {
						//	if(aux3->c == ' ') {
						//		aux3->prev->next = aux4;
						//		aux4->prev = aux3->prev;
						//		free(aux3);
						//	}
						//	aux3 = aux4;
						//	aux4 = aux4->next;
						//}
		    			}
                    			save(lista, fp);
                    			fclose(fp);
                    			getchar();
                		break;
                		case 'b' : {
                    			int ok=0;
					int lin=1, poz=0;
                                	date_cursor(&lista,&lin,&poz,&cursor);
                                	push(&c_undo,'b',poz,lin,0);
                                	push_text(&t_undo,cursor->c);
                    			cursor = backspace(&cursor,&ok);
                    			salveaza++;
                    			k = k - ok;
                    			getchar();
                    		}
                		break;
                		case 'd' :
                    			scanf("%c", &c);
                    			if(c == 'l') {
                        			scanf("%c", &c);
                        			if(c !='\n') {
                            				int nr_linie;
                            				scanf("%d", &nr_linie);
                            				salveaza++;
                            				push(&c_undo,'e',0,nr_linie,0); /// tinem minte 'e' pt delete line
                            				if(nr_linie == k)
                                				k++;
                            				cursor = del_line(nr_linie,&lista,k);
                            				k--;
                            				if(nr_linie != 1 && cursor->next != NULL) {
                                				int ok=0;
                                				cursor = backspace(&cursor,&ok);
							}
                            				getchar();
						}
                        			else {
                            				salveaza++;
                            				//trebuie sa punem linia curenta
                            				int lin=1, poz=0;
                            				date_cursor(&lista,&lin,&poz,&cursor);
                            				if(cursor->c == '\n' && cursor->next == NULL)
                                				lin--;
                            				if(lin == k)
                                				k++;
                            				push(&c_undo,'e',0,lin,0);
                            				cursor = del_line(lin,&lista,k);
                            				if(lin != 1 && cursor->next != NULL) {
                                				int ok=0;
                                				cursor = backspace(&cursor,&ok);
                            				}
                            				k--;
                        			}
                    			}
                    			else {
                        			if(c !='\n') {
                            				int nr_char, i;
                            				scanf("%d", &nr_char);
                            				salveaza++;
							int lin=1, poz=0;
                                            		date_cursor(&lista,&lin,&poz,&cursor);
                                            		push(&c_undo,'d',poz,lin,nr_char);
                            				int ok;
                            				for(i=0; i<nr_char; i++) {
                                				ok=0;
                                				cursor = cursor->next;
                                				cursor = backspace(&cursor,&ok);
                                				k = k - ok;
                            				}
                            				push(&c_undo,'d',0,nr_char,0);
                           				getchar();
                        			}
                        			else {
                            				salveaza++;
                            				int ok=0;
							int lin=1, poz=0;
                                            		date_cursor(&lista,&lin,&poz,&cursor);
                                            		push(&c_undo,'d',poz,lin,1);
                            				cursor = cursor->next;
                            				cursor = backspace(&cursor,&ok);
                            				k = k - ok;
                            				push(&c_undo,'d',0,1,0);
                        			}
                    			}
                		break;
                		case 'g' :
                    			scanf("%c", &c);
                    			if(c == 'l') {
                        			int nr_linie;
                        			scanf("%d", &nr_linie);
                        			salveaza++;
                        			push(&c_undo,'l',0,nr_linie,0); /// tinem minte 'e' pt delete line
                        			if(nr_linie == 1) {
                            				nod *auxh =malloc(sizeof(nod));
                            				auxh->c = ' ';
                            				lista->prev = auxh;
                            				auxh->next = lista;
                            				auxh->prev = NULL;
                            				lista = lista->prev;
                            				cursor = goto_line(nr_linie,&lista);
                        			}
                        			else
                            				cursor = goto_line(nr_linie,&lista);
                        			getchar();
                    			}
                    			else
                    				if(c == 'c') {
                        				int nr_char;
                        				scanf("%d", &nr_char);
                       		 			scanf("%c", &c);
                        				if(c !='\n') {
                            					int nr_linie;
                            					scanf("%d", &nr_linie);
                            					salveaza++;
                            					push(&c_undo,'g',nr_char,nr_linie,0); // tinem minte 'e' pt delete line
                            					if(nr_linie == 1) {
                                					nod *auxh =malloc(sizeof(nod));
                                					auxh->c = ' ';
                                					lista->prev = auxh;
                                					auxh->next = lista;
                                					auxh->prev = NULL;
                                					lista = lista->prev;
                                					cursor = goto_char(nr_linie,nr_char,&lista,&cursor);
                            					}
                            					else
                                					cursor = goto_char(nr_linie,nr_char,&lista,&cursor);
                            					getchar();
                        				}
                        				else {
                            					salveaza++;
                            					int lin=1, poz=0;
                            					date_cursor(&lista,&lin,&poz,&cursor);
                            					push(&c_undo,'e',poz,lin,0);
                            					cursor = goto_char(lin,nr_char,&lista,&cursor); 
                        				}
                    				}
                		break;
				case 'u' :
					if(c_undo == NULL) {
                        nod *aux=malloc(sizeof(nod));
                        aux=lista;
                        lista->next = NULL;
                        lista=NULL;
                        printf("c");

//                        while(aux->next != NULL) {
//                            free(aux);
//                            aux=aux->next;
//                        }
                    }
                    if(c_undo->nume == 'b') {
                        nod *aux=malloc(sizeof(nod));
                        aux->c = t_undo->nume;
                       // if()
                        cursor=goto_char(c_undo->nr_linie-1,c_undo->nr_char-1,&lista,&cursor);
                        int nr=0;

                        printf("%c", cursor->c);
                        cursor = cursor->prev;

                        aux->next = cursor->next;
                        aux->prev = cursor;
                        //cursor->next->prev=aux;
                        cursor->prev = aux;

                        printf("aux:%c",aux->c);
                        printf("%c", cursor->c); }
				break;

				//case 'r' :

                		//default :
                			//copie = c;
                			//if(c!='i' && c != ':' && c != 'q')
                    			//printf("Comanda inexistenta\n");
            		}
            		if(ok==1) {
				getchar();
                 		getchar();
                 		getchar();
                	}
            		if(salveaza == 5) {
                		fp = fopen(argv[1],"w");
                		if(lista->c == ' ') {
                            		lista=lista->next;
                            		lista->prev=NULL;
				}
                		save(lista, fp);
                		fclose(fp);
                		salveaza = 0;
            		}
        	}
        	else {
            		scanf("%c",&c);
            		cursor = adauga(&lista, c, &cursor);
            		if(c == '\n')
                		k++;
            		if(c == ':' && copie == ':' && ok==1)
                		ok=0;
            		copie = c;
            		if(ok==0) {
                		getchar();
                		getchar();
                		k++;
                		nod *aux2 = malloc (sizeof(nod));
                		aux2 = cursor->prev;
				if(cursor->prev->prev == NULL) {
					lista = NULL;
					cursor = lista;
				}
				else {	                
					nod *auxc = cursor;
        	       	 		if(auxc->next == NULL) {
        	            			cursor = cursor->prev->prev;
        	           		 	cursor->next = NULL;
        	            			aux2->prev = NULL;
        	            			free(aux2->next);
        	            			free(aux2);
        	        		}
        	        		else {		
        	            			int mok=0;
        	            			cursor = backspace(&cursor,&mok);
        	            			cursor = backspace(&cursor,&mok);
        	        		}
				}
            		}
        	}
    	}
    	return 0;
}

