
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef struct NodoBinario {
    struct NodoBinario * sx;
    struct NodoBinario * dx;
    void * contenuto;
} alberobinario_NodoBinario;

typedef int (* alberobinario_pFunzioneComparazione)(const void *, const void *);
typedef void (* alberobinario_pFunzioneStampa)(const void *);
typedef int (* alberobinario_pFunzioneDistruzioneContenuto)(void *);

alberobinario_NodoBinario * alberobinario_nodo_inizializza(alberobinario_NodoBinario * nodo);
int alberobinario_contenuto_distruggi(const alberobinario_pFunzioneDistruzioneContenuto pFDisCont, void * distrutto);
alberobinario_NodoBinario * alberobinario_contenuto_assegna(alberobinario_NodoBinario * nodo, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneDistruzioneContenuto pFDC);
alberobinario_NodoBinario * alberobinario_contenuto_cerca(const alberobinario_NodoBinario * root, const void * cercato, const alberobinario_pFunzioneComparazione pFComp);
alberobinario_NodoBinario * alberobinario_nodo_trova_crea(alberobinario_NodoBinario * root, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC);
void alberobinario_stampa(const alberobinario_NodoBinario * root, const alberobinario_pFunzioneStampa pFStampa); 
int alberobinario_nodo_distruggi(alberobinario_NodoBinario * root, const void * contenuto, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC);

/*  DOCUMENTAZIONE 

Struttura della funzione di comparazione:

    int funzione_paragone(const void * contenuto1, const void * contenuto2);
    
    Valori di ritorno:
        - contenuto1 == contenuto2 => output == 0;
        - contenuto1 < contenuto2 => output < 0;
        - contenuto1 > contenuto2 => output > 0.
    
    Per garantire che:
        - contenuto del nodo di sx sempre < contenuto nel nodo padre;
        - contenuto del nodo di dx sempre > contenuto nel nodo padre.
    
Struttura della funzione di distruzione del contenuto:
    
    int funzione_distruzione_contenuto(void * contenuto);
    
    Valori di ritorno:
        - -1 se c'è stato un errore nell'input;
        - 0 se la distruzione è andata a buon fine;
        - 1 se si è verificato un errore durante la distruzione del contenuto.
*/

/* 

// alberobinario_NodoBinario * alberobinario_nodo_inizializza(alberobinario_NodoBinario * nodo) // Funzione di inizializzazione di un nodo, che imposta a 0 tutti i suoi valori.
        ritorna il nodo inizializzato se esiste
        ritorna null se il nodo è null, non inizializzandolo.
            
// int alberobinario_contenuto_distruggi(const alberobinario_pFunzioneDistruzioneContenuto pFDisCont, void * distrutto) // Un wrapper per la funzione di distruzione del contenuto.
    Ritorna -2 se:
        pFDisCont è NULL
        distrutto è NULL
    Altrimenti ritorna ciò che ritorna la funzione pFDisCont.

// alberobinario_NodoBinario * alberobinario_contenuto_assegna(alberobinario_NodoBinario * nodo, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneDistruzioneContenuto pFDC) // Distrugge il vecchio contenuto, copia il nuovo al suo posto.
    assegna il contenuto al nodo dato
    ritorna il nodo
    ritorna null se:
        nodo è NULL
        contenuto è NULL
        dimensioneContenutoByte è zero
        pFDC è NULL
        si sono verificati errori nella distruzione del contenuto

// alberobinario_NodoBinario * alberobinario_contenuto_cerca(const alberobinario_NodoBinario * root, const void * cercato, const alberobinario_pFunzioneComparazione pFComp) // Funzione per reperire il nodo a cui è associato del contenuto specifico, cercato con la funzione fornita dall'utente.
    ritorna puntatore a nodo binario 
        ritorna il nodo trovato se esiste
        ritorna NULL se non esiste
        ritorna NULL se uno qualunque dei tre argomenti è NULL
        
// alberobinario_NodoBinario * alberobinario_nodo_trova_crea(alberobinario_NodoBinario * root, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC) // Funzione per reperire il nodo a cui è associato del contenuto specifico, cercato con la funzione fornita dall'utente e, nel caso non esista, creare un nodo con quel contenuto.
    ritorna puntatore a nodo binario 
        ritorna il nodo creato se non esisteva
        ritorna il nodo trovato se esisteva
        ritorna null se uno qualunque dei quattro argomenti puntatore sono NULL o se dimensioneContenutoByte è uguale a zero, o se si sono verificati errori nella distruzione del contenuto vecchio
    
// int alberobinario_nodo_distruggi(alberobinario_NodoBinario * root, const void * contenuto, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC) // Funzione per distruggere un nodo dal contenuto specifico, cercandolo con la funzione di comparazione fornita dall'utente, ricostruendo l'albero per mantenere la sua integrità. L'utente fornisce, inoltre, un puntatore ad una funzione per l'eliminazione del contenuto del nodo.
    ritorna int
        ritorna -1 per errori di input
        ritorna 0 se non è stato trovato il nodo da eliminare
        ritorna -2 se ci sono stati problemi nel processo di eliminazione, non liberando il nodo

// alberobinario_stampa(const alberobinario_NodoBinario * root, const alberobinario_pFunzioneStampa pFStampa) // Funzione per la stampa il contenuto di tutti i nodi, traversandoli in ordine, usando la funzione di stampa fornita dall'utente.
    // ritorna void
*/
