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

nod* adauga (nod **head, char new_char) {
	nod *new =malloc (sizeof(nod));
	new->c = new_char;
	new->next = NULL;
	if (*head == NULL) {
		*head = new;
		return new;
	}
	nod *aux = *head;
	while (aux->next != NULL)
		aux = aux->next;
	aux->next = new;
    new->prev = aux;

    return new;
}

typedef struct stiva {
    char nume;
    int nr_linie;
    int nr_char;
    struct stiva *next;
}stiva;

void init_stiva (stiva** head) {
    *head =malloc(sizeof(stiva));
	*head = NULL;
}

void push(stiva **head, char c, int nrl, int nrc) {
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

	//push(s_redo, aux->nume, aux->nr_linie, aux->nr_char);
	return aux;
}

nod* backspace (nod **head, int *contor) {
    if((*head) == NULL )
        return 0;

	nod *aux =malloc (sizeof(nod));
	aux = *head;


  //  printf("\n%c\n", aux->c);
   // printf("%c%c%c", au)
	//while (aux->next != NULL)
    //    aux = aux->next;
    ///if cursor nu e la final

    if(aux->c == '\n')
        (*contor)++;

    if(aux->next != NULL)
        aux->next->prev = aux->prev;

    aux->prev->next=aux->next;

//    printf("%c%c%c", aux->prev->c, aux->c, aux->next->c);

     aux=aux->prev;
  //   printf("%c%c%c", aux->prev->c, aux->c, aux->next->c);
    ///SA ELIBERAM MEMORIA!!
    // free(aux->next);

    return aux;
}

void show (nod *head) {

	while (head != NULL) {
//        if(head->c < 'a' && head->c < 'z')
//            printf("#");
//        else
		printf("%c", head->c);

		head = head->next;
	}
	printf("\n");

}

nod* goto_line(int nr_linie, nod **head){

    if((*head) == NULL )
            return 0;

    nod *aux =malloc (sizeof(nod));
    aux = *head;

    int i;
    for(i=1; i<nr_linie; i+=0){
        if( aux->c == '\n' )
            i++;
        aux = aux->next;
    }

   // printf("%c", aux->c);

   return aux->prev;
}

void date_cursor(nod **head, int *linie, int *poz, nod **cursor){
///a fi apelat cu (lista, 1, ,cursor)
    if((*head) == NULL ){
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

    while( aux->c != '\n' && aux->prev != (*head)->prev ){
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

    if(nr_linie == 1){
        int i;
        for(i=0; i<nr_char; i++)
        aux=aux->next;

        printf("%c", aux->prev->c);

        return aux->prev;
    }
    int i;
    for(i=1; i<nr_linie; i+=0){
        if( aux->c == '\n' )
            i++;
        aux = aux->next;
    }
    aux=aux->prev;

    for(i=0; i<nr_char; i++)
        aux=aux->next;

    printf("%c", aux->c);

    return aux;
}

void save(nod *head, FILE *fp) {
    nod *aux =malloc (sizeof(nod));
    aux=head;
  //  fclose(fp);
  //  fp=fopen("Textfile","w");
    while(aux!=NULL)
    {
        fprintf(fp,"%c",aux->c);
        aux=aux->next;
    }
   // fclose(fp);
}

//void quit(nod *head) {
//    if(fp==NULL)
//    return;
//    fclose(fp);
//    fp=NULL;
//}

nod* del_line(int k, nod **head, int nr_linii){ ///atentiee!!! k-ul din main este nr_linii,
                                                ///iar k-ul de aici este linia de sters
    if((*head) == NULL )
            return 0;

    nod *aux =malloc (sizeof(nod));
    aux = *head;

    int i;
    for(i=1;i<k;i+=0){
        if( aux->c == '\n' )
            i++;
        aux = aux->next;
    }

    //printf("%c\n", aux->c);
                                        ///aux e cel de la care plecam
    nod *aux2 = malloc (sizeof(nod));   ///aux2 e cel care ajunge la final
    aux2 = aux;                         ///aux3 si aux4 sunt facuti ca sa stergem ce e de la aux pana la aux2

    while(aux2->c != '\n' && aux2->next != NULL){
        aux2 = aux2->next;
    }

    // printf("aux2 e la %c\n", aux2->next->c);
    ///in mare, e acealasi lucru la fiecare if, doar ca pt mici chicite a trebuit sa le impart asa

    if (k==1) {  ///sterge prima linie
        aux2 = aux2->next;
        aux2->prev=NULL;
        *head = aux2;
        nod *aux3 = malloc (sizeof(nod));
        aux3 = aux;

        nod *aux4 = malloc (sizeof(nod));
        aux4 = aux->next;

        while(aux3 != aux2 ) {
            //printf("%c ", aux3->c);
            free(aux3);
            aux3 = aux4;
            aux4 = aux4 ->next;
        }
        return aux2;
    }
    else {
        if(k == nr_linii){        ///stergem ultima linie
           // printf("Caz ultima linie Nr linii:%d %c %c",nr_linii, aux->prev->c, aux->c);

            nod *aux3 = malloc (sizeof(nod));
            aux3 = aux;

           // printf("Aux3: %c", aux3 ->c);
            //aux->prev->next = NULL;
            aux=aux->prev;
            aux->next = NULL;


            nod *aux4 = malloc (sizeof(nod));
            aux4 = aux3->next;

            while(aux4 != NULL ) {
                //printf("%c ", aux3->c);
                free(aux3);
                aux3 = aux4;
                aux4 = aux4 ->next;
            }
            free(aux3);
            //printf("Aux: %c\n Aux->prev->c: %c\n", aux ->c, aux->prev->c);
            return aux;
        }
        else{
           // printf("Nr linii:%d %c %c", nr_linii, aux->prev->c, aux->c);
            aux->prev->next = aux2->next;
            aux2->prev = aux->prev;
            nod *aux3 = malloc (sizeof(nod));
            aux3 = aux;

            nod *aux4 = malloc (sizeof(nod));
            aux4 = aux->next;

            while(aux3 != aux2 ) {
                //printf("%c ", aux3->c);
                free(aux3);
                aux3 = aux4;
                aux4 = aux4 ->next;
            }

        return aux2;
        }
    }
}

int main(int argc, char *argv[])
{
    FILE *fp=NULL;
   // fp = fopen("Textfile.txt","w");


    nod *lista;
    init(&lista);
    nod *cursor;
    cursor = lista;
   // cursor->next=NULL;

    stiva *s_undo;
    stiva *s_redo;

    init_stiva(&s_undo);
    init_stiva(&s_redo);

    int ok=1; /// ok=1 - text; ok=0 - comanda
    char c;
    char copie;
    copie = 'a'; ///orice diferit de ':'
    int k=0;
    int salveaza=0;



    while(ok != 0 || c != 'q'){

        if(ok == 0){
            //getchar();
            scanf("%c", &c);

            if(c == ':' && copie == ':' && ok==0) {
                ok=1;
            }

            switch(c){
                case 's' :
                   // printf("Salvam\n");
                    //fp = fopen("Textfile.txt","w");
                    fp = fopen(argv[1],"w");
                    save(lista, fp);
                    fclose(fp);
                    getchar();
                break;
                case 'b' :
                    {
                    int ok=0;

                    cursor = backspace(&cursor,&ok); ///Merge GATA!!
                  //  printf("Backspace\n");
                    salveaza++;
                    push(&s_undo,'b',0,0);
                    k = k - ok;
                    getchar();

                    }
                break;
                case 'd' :
                    scanf("%c", &c);
                    if(c == 'l'){
                        scanf("%c", &c);
                        if(c !='\n') {
                            int nr_linie;
                            scanf("%d", &nr_linie);
                            // printf("%d", nr_linie);
                            salveaza++;
                            push(&s_undo,'e',nr_linie,0); /// tinem minte 'e' pt delete line
                            printf("Nr linii: %d\n", k);

                            if(nr_linie == k)
                                k++;


                            cursor = del_line(nr_linie,&lista,k);
                            k--;

                            //int lin=1, poz=0;
                            //date_cursor(&lista,&lin,&poz,&cursor);


                            if(nr_linie != 1 && cursor->next != NULL){
                                int ok=0;
                                cursor = backspace(&cursor,&ok);
                             //   printf("ok: %d\n", ok);
                            }

                            //printf("1:%c 2:%c\n", cursor->c, cursor->next->c);
                            // system("pause");
                            //show(lista);
                            //printf("DFQ\n");
                            getchar();
                           // printf("mok");
                            }
                        else {
                            salveaza++;
                            ///trebuie sa punem linia curenta
                            int lin=1, poz=0;
                            date_cursor(&lista,&lin,&poz,&cursor);
                            //printf("Cursor->c %c\n", cursor->c);

                            if(cursor->c == '\n' && cursor->next == NULL)
                                lin--;

                            if(lin == k)
                                k++;

                            push(&s_undo,'e',lin,0);
                           // printf("%d",lin);
                            cursor = del_line(lin,&lista,k);
                            if(lin != 1 && cursor->next != NULL){
                                int ok=0;
                                cursor = backspace(&cursor,&ok);
                             //   printf("ok: %d\n", ok);
                            }
                            k--;
                        }
                    }
                    else {
                        if(c !='\n'){
                            int nr_char;
                            scanf("%d", &nr_char);
                            salveaza++;
                            push(&s_undo,'d',0,nr_char);
                            getchar();
                        }
                        else {
                            salveaza++;
                            push(&s_undo,'d',0,1);
                        }
                    }
                break;
                case 'g' :
                    scanf("%c", &c);
                    if(c == 'l'){
                        //printf("Go to line\n");
                        int nr_linie;
                        scanf("%d", &nr_linie);

                        salveaza++;
                        push(&s_undo,'l',nr_linie,0); /// tinem minte 'e' pt delete line
                        cursor = goto_line(nr_linie,&lista);
                        getchar();
                    }
                    else
                    if(c == 'c'){
                        int nr_char;
                        scanf("%d", &nr_char);

                        scanf("%c", &c);
                        if(c !='\n') {
                            int nr_linie;
                            scanf("%d", &nr_linie);

                            salveaza++;
                            push(&s_undo,'g',nr_linie,nr_char); /// tinem minte 'e' pt delete line

                            cursor = goto_char(nr_linie,nr_char,&lista,&cursor);

                            getchar();
                        }
                        else{
                            salveaza++;
                            push(&s_undo,'e',1,0);
                            int lin=1, poz=0;
                            date_cursor(&lista,&lin,&poz,&cursor);
                            cursor = goto_char(lin,nr_char,&lista,&cursor); ///ceva ca sa fie cea curenta
                        }
                    }
                break;
                default:
                copie = c;
                if(c!='i' && c != ':' && c != 'q')
                    printf("Comanda inexistenta\n");
            }
            if(ok==1)
                {getchar();
                 getchar();
                 getchar();
                }
            ///ceva cu s%5 si cate undo-uri am face

            if(salveaza == 5){
                fp = fopen(argv[1],"w");
                save(lista, fp);
                fclose(fp);
                salveaza = 0;
            }
//            printf("Cursor la : %c\n", cursor->c);
//            int lin=1, poz=0;
//            date_cursor(&lista,&lin,&poz,&cursor);
//            printf("Numar linii: %d\nLinie cursor:%d\nPoz cursor%d\n", k,lin,poz);
        }
        else{
            scanf("%c",&c);

            cursor = adauga(&lista, c);
            //cursor = adauga(c,&cursor);
            if(c == '\n')
                k++;

            if(c == ':' && copie == ':' && ok==1) {
                ok=0;
            }

            copie = c;
            if(ok==0) {
                getchar();
                getchar();
                k++;
                nod *aux2 = malloc (sizeof(nod));
                aux2 = cursor->prev;

                cursor = cursor->prev->prev;
                cursor->next = NULL;

                aux2->prev = NULL;
                free(aux2->next);
                free(aux2);
            }
        }
    }

    //int lin=1, poz=0;
    // printf("%c\n", cursor->c);
    // date_cursor(&lista,&lin,&poz,&cursor);

    //  printf("%d %d\n", lin, poz);


    while(s_undo!=NULL){
        printf("%c %d %d\n", s_undo->nume, s_undo->nr_linie, s_undo->nr_char);
        s_undo = s_undo->next;
    }

   show(lista);
   printf("Nr linii: %d",k);

   // fprintf(fp,"%d",55);
   // fclose(fp);
    return 0;
}
///sa scadeam randuri la backspace daca e nevoie
///funcita save
///adauga!!!!!!!!!
///delete simplu
///fisier
