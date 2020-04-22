/*
The Ananas software house needs to release a new version of Contacts. Specifically, Contacts 10.0 must provide the user with the following features:
1. Insert new contact. Each contact is characterized by a (progressive) code, a cogno, and a name, a date of birth and a list of telephone numbers. A telephone number is instead characterized by a number and a description (e.g., mobile phone, work, home). Each contact will have one or more telephone numbers (max 10).
The functionality must be implemented as follows: the program asks the user for the surname, name and date of birth; the number of telephone numbers to add to the contact; the telephone numbers to be assigned to the contact (number and description).
After generating the code, the program inserts the new contact in the archive.
2. New telephone number added. The program takes the contact code as input; check its presence in the archive; if so, print the contact data on the screen and ask the user for the data of the new telephone number, i.e. number and description.
3. Search for number. The program takes the surname as input and prints all the contacts whose surname coincides with that specified in the input.
4. View address book. The program prints the entire phone book on the screen, showing the surname, first name, date of birth and the list of telephone numbers (number and description) for each contact.
*/

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
* File:   AddressBook.c
* Author: dtfabio96
*
* Created on 18 gennaio 2016, 20.59
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//dichiarazione costanti
#define DIM_NOMI 21
#define DIM_DATA 11
#define DIM_RECAPITI 10
#define DIM_CONTATTI 200
#define DIM_NUMERO_TELEFONICO 14
#define OK -1
#define NOT_OK -2

//dichiarazione strutture

typedef struct {
    char numero[DIM_NUMERO_TELEFONICO];
    char descrizione[DIM_NOMI];
} recapito;

typedef struct {
    int codice_contatto;
    char nome_contatto[DIM_NOMI];
    char cognome_contatto[DIM_NOMI];
    char data_nascita_contatto[DIM_DATA];
    recapito elenco_recapiti[DIM_RECAPITI];
    int num_recapiti;
} contatto;

typedef struct {
    contatto elenco_contatti[DIM_CONTATTI];
    int num_contatti;
} archivio_contatti;

typedef struct {
    int elenco_cognomi[DIM_CONTATTI];
    int num_cognomi;
} archivio_cognomi;

//dichiarazione funzioni
void init_archivio_contatti(archivio_contatti*);
void init_elenco_recapiti(contatto*);
void init_archivio_cognomi(archivio_cognomi*);
contatto inserimento_dati_contatto(char[], char[], char[], int, recapito[], archivio_contatti);
int cerca_contatto(contatto, archivio_contatti);
void inserimento_nuovo_contatto(archivio_contatti*, contatto);
int cerca_codice_contatto(archivio_contatti, int);
void stampa_dati_contatto(archivio_contatti, int);
void stampa_recapiti_contatto(archivio_contatti, int);
int aggiunta_nuovo_recapito_telefonico(archivio_contatti*, int);
int cerca_cognomi(char[], archivio_contatti, archivio_cognomi*);
void stampa_contatti_cognome_uguale(archivio_cognomi, archivio_contatti);
void stampa_rubrica(archivio_contatti);

int main(int argc, char** argv) {
    //dichiarazione variabili
    int scelta, esito, esito_due, i, num_rec, codice_cercare;
    char cognome_cercare[DIM_NOMI];
    char risposta;
    contatto nuovo_contatto;
    archivio_contatti contatti;
    recapito nuovo_recapito;
    archivio_cognomi cognomi;

    //inizio programmma
    init_archivio_contatti(&contatti);
    init_elenco_recapiti(&nuovo_contatto);
    init_archivio_cognomi(&cognomi);

    do {
        system("cls");
        printf("***APPLE CONTATTI 10.0***\n");
        printf("-------------------------\n");
        printf("1.Inserimento nuovo contatto\n");
        printf("2.Aggiunta nuovo recapito telefonico\n");
        printf("3.Cerca numero\n");
        printf("4.Visualizza rubrica\n");
        printf("0.Esci\n");
        printf("\n\tScelta: ");
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                system("cls");
                printf("Inserimento nuovo contatto\n");
                printf("--------------------------\n");
                nuovo_contatto = inserimento_dati_contatto(nuovo_contatto.cognome_contatto, nuovo_contatto.nome_contatto, nuovo_contatto.data_nascita_contatto, nuovo_contatto.num_recapiti, nuovo_contatto.elenco_recapiti, contatti);
                esito = cerca_contatto(nuovo_contatto, contatti);
                if (esito == NOT_OK) {
                    inserimento_nuovo_contatto(&contatti, nuovo_contatto);
                } else {
                    printf("Contatto gia` esistente\n");
                    stampa_recapiti_contatto(contatti, esito);
                    printf("Aggiungere nuovi recapiti telefonici (S|N)? ");
                    scanf("%s", &risposta);
                    if (risposta == 'S') {
                        printf("Quanti recapiti vuoi aggiungere? ");
                        scanf("%d", &num_rec);
                        for (i = 0; i < num_rec; i++) {
                            esito_due = aggiunta_nuovo_recapito_telefonico(&contatti, esito);
                            switch (esito_due) {
                                case OK:
                                    printf("Recapito inserito con successo\n");
                                    break;
                                case NOT_OK:
                                    printf("Errore!Raggiunta dimensione massima recapiti\n");
                                    break;
                            }
                        }
                    }
                }
                system("pause");
                break;

            case 2:
                system("cls");
                printf("Aggiunta nuovo recapito telefonico\n");
                printf("----------------------------------\n");
                printf("Inserisci il codice del contatto: ");
                scanf("%d", &codice_cercare);
                esito = cerca_codice_contatto(contatti, codice_cercare);
                if (esito == NOT_OK)
                    printf("Errore!Codice contatto non esistente\n");
                else {
                    stampa_dati_contatto(contatti, esito);
                    esito = aggiunta_nuovo_recapito_telefonico(&contatti, esito);
                    switch (esito) {
                        case OK:
                            printf("Recapito inserito con successo\n");
                            break;
                        case NOT_OK:
                            printf("Errore!Raggiunta dimensione massima recapiti\n");
                            system("pause");
                            break;
                    }
                }
                break;

            case 3:
                system("cls");
                printf("Cerca numero\n");
                printf("------------\n");
                printf("Inserisci il cognome del contatto da cercare: ");
                scanf("%s", cognome_cercare);
                esito = cerca_cognomi(cognome_cercare, contatti, &cognomi);
                switch (esito) {
                    case OK:
                        stampa_contatti_cognome_uguale(cognomi, contatti);
                        break;
                    case NOT_OK:
                        printf("Errore!Cognome non esistente\n");
                        system("pause");
                        break;
                }
                break;

            case 4:
                system("cls");
                printf("Visualizza rubrica\n");
                printf("------------------\n");
                stampa_rubrica(contatti);
                system("pause");
                break;

            case 0:
                system("cls");
                printf("Chiusura programma...\n");
                break;

            default:
                system("cls");
                printf("Scelta non valida\n");
                system("pause");
        }
    } while (scelta != 0);
    return (EXIT_SUCCESS);
}

//definizione funzioni

void init_archivio_contatti(archivio_contatti* _contatti) {
    _contatti->num_contatti = 0;
}

void init_elenco_recapiti(contatto* _nuovo_contatto) {
    _nuovo_contatto->num_recapiti = 0;
}

void init_archivio_cognomi(archivio_cognomi* _cognomi) {
    _cognomi->num_cognomi = 0;
}

contatto inserimento_dati_contatto(char _cognome_contatto[], char _nome_contatto[], char _data_nascita_contatto[], int _num_recapiti, recapito _elenco_recapiti[], archivio_contatti _contatti) {
    contatto _nuovo_contatto;
    int i, _esito;

    printf("Inserisci il cognome del contatto: ");
    scanf("%s", _nuovo_contatto.cognome_contatto);
    printf("Inserisci il nome del contatto: ");
    scanf("%s", _nuovo_contatto.nome_contatto);
    printf("Inserisc la data di nascita del contatto (**/**/****): ");
    scanf("%s", _nuovo_contatto.data_nascita_contatto);
    _esito = cerca_contatto(_nuovo_contatto, _contatti);
    if (_esito == NOT_OK) {
        _nuovo_contatto.codice_contatto = _contatti.num_contatti;
        printf("Codice contatto=%d\n", _nuovo_contatto.codice_contatto);
        do {
            printf("Inserisci il numero dei recapiti del contatto: ");
            scanf("%d", &_nuovo_contatto.num_recapiti);
            if (_nuovo_contatto.num_recapiti > DIM_RECAPITI)
                printf("Errore, puoi inserire max 10 recapiti per contatto\n");
        } while (_nuovo_contatto.num_recapiti > DIM_RECAPITI);
        for (i = 0; i < _nuovo_contatto.num_recapiti; i++) {
            printf("Inserisci il numero di telefono del %d recapito: ", i + 1);
            scanf("%s", _nuovo_contatto.elenco_recapiti[i].numero);
            printf("Inserisci la descrizione del %d recapito: ", i + 1);
            scanf("%s", _nuovo_contatto.elenco_recapiti[i].descrizione);
        }
        return _nuovo_contatto;
    } else
        return _nuovo_contatto;
}

int cerca_contatto(contatto _nuovo_contatto, archivio_contatti _contatti) {
    int i;

    i = 0;
    while ((i < _contatti.num_contatti)&&(strcmp(_nuovo_contatto.data_nascita_contatto, _contatti.elenco_contatti[i].data_nascita_contatto) != 0)) {
        i++;
    }
    if (i == _contatti.num_contatti)
        return NOT_OK;
    else {
        while ((i < _contatti.num_contatti)&&(strcmp(_nuovo_contatto.cognome_contatto, _contatti.elenco_contatti[i].cognome_contatto) != 0)) {
            i++;
        }
        if (i == _contatti.num_contatti)
            return NOT_OK;
        else {
            while ((i < _contatti.num_contatti)&&(strcmp(_nuovo_contatto.nome_contatto, _contatti.elenco_contatti[i].nome_contatto) != 0)) {
                i++;
            }
            if (i == _contatti.num_contatti)
                return NOT_OK;
            else
                return i;
        }
    }
}

void inserimento_nuovo_contatto(archivio_contatti* _contatti, contatto _nuovo_contatto) {
    _contatti->elenco_contatti[_contatti->num_contatti] = _nuovo_contatto;
    _contatti->num_contatti++;
}

int cerca_codice_contatto(archivio_contatti _contatti, int _codice_cercare) {
    int i;

    i = 0;
    while ((i < _contatti.num_contatti)&&(_codice_cercare != _contatti.elenco_contatti[i].codice_contatto)) {
        i++;
    }
    if (i == _contatti.num_contatti)
        return NOT_OK;
    else
        return i;
}

void stampa_dati_contatto(archivio_contatti _contatti, int indice_contatto) {
    int i;

    printf("Il contatto ha cognome=%s nome=%s data di nascita=%s e ha %d recapiti\n", _contatti.elenco_contatti[indice_contatto].cognome_contatto, _contatti.elenco_contatti[indice_contatto].nome_contatto, _contatti.elenco_contatti[indice_contatto].data_nascita_contatto, _contatti.elenco_contatti[indice_contatto].num_recapiti);
    for (i = 0; i < _contatti.elenco_contatti[indice_contatto].num_recapiti; i++) {
        printf("Il %d recapito e' %s %s\n", i + 1, _contatti.elenco_contatti[indice_contatto].elenco_recapiti[i].numero, _contatti.elenco_contatti[indice_contatto].elenco_recapiti[i].descrizione);
    }
}

void stampa_recapiti_contatto(archivio_contatti _contatti, int indice_contatto) {
    int i;

    for (i = 0; i < _contatti.elenco_contatti[indice_contatto].num_recapiti; i++) {
        printf("Il %d recapito del contatto e' %s %s\n", i + 1, _contatti.elenco_contatti[indice_contatto].elenco_recapiti[i].numero, _contatti.elenco_contatti[indice_contatto].elenco_recapiti[i].descrizione);
    }
}

int aggiunta_nuovo_recapito_telefonico(archivio_contatti* _contatti, int indice_contatto) {
    if (_contatti->elenco_contatti[indice_contatto].num_recapiti == DIM_RECAPITI)
        return NOT_OK;
    else {
        printf("Inserisci il numero del nuovo recapito: ");
        scanf("%s", _contatti->elenco_contatti[indice_contatto].elenco_recapiti[_contatti->elenco_contatti[indice_contatto].num_recapiti].numero);
        printf("Inserisci la descrizione del nuovo recapito: ");
        scanf("%s", _contatti->elenco_contatti[indice_contatto].elenco_recapiti[_contatti->elenco_contatti[indice_contatto].num_recapiti].descrizione);
        _contatti->elenco_contatti[indice_contatto].num_recapiti++;
        return OK;
    }
}

int cerca_cognomi(char _cognome_cercare[], archivio_contatti _contatti, archivio_cognomi* _cognomi) {
    int i;

    i = 0;
    init_archivio_cognomi(_cognomi);
    do {
        while ((i < _contatti.num_contatti)&&(strcmp(_cognome_cercare, _contatti.elenco_contatti[i].cognome_contatto) != 0)) {
            i++;
        }
        if (i < _contatti.num_contatti) {
            _cognomi->elenco_cognomi[_cognomi->num_cognomi] = i;
            _cognomi->num_cognomi++;
            i++;
        }
    } while (i < _contatti.num_contatti);
    if (_cognomi->num_cognomi == 0)
        return NOT_OK;
    else
        return OK;
}

void stampa_contatti_cognome_uguale(archivio_cognomi _cognomi, archivio_contatti _contatti) {
    int i, j;

    for (i = 0; i < _cognomi.num_cognomi; i++) {
        printf("Il %d contatto con cognome uguale a quello inserito precedentemente e' %s nato il %s con codice %d e ha %d recapiti\n", i + 1, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].nome_contatto, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].data_nascita_contatto, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].codice_contatto, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].num_recapiti);
        for (j = 0; j < _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].num_recapiti; j++) {
            printf("Il %d recapito e' %s %s\n", j + 1, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].elenco_recapiti[j].numero, _contatti.elenco_contatti[_cognomi.elenco_cognomi[i]].elenco_recapiti[j].descrizione);
        }
    }
}

void stampa_rubrica(archivio_contatti _contatti) {
    int i, j;

    for (i = 0; i < _contatti.num_contatti; i++) {
        printf("Il %d contatto ha cognome=%s nome=%s data di nascita=%s\n", i + 1, _contatti.elenco_contatti[i].cognome_contatto, _contatti.elenco_contatti[i].nome_contatto, _contatti.elenco_contatti[i].data_nascita_contatto);
        for (j = 0; j < _contatti.elenco_contatti[i].num_recapiti; j++) {
            printf("Il %d recapito e' %s %s\n", j + 1, _contatti.elenco_contatti[i].elenco_recapiti[j].numero, _contatti.elenco_contatti[i].elenco_recapiti[j].descrizione);
        }
    }
}
