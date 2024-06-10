
#include "fredalberobinario.h"

alberobinario_NodoBinario * alberobinario_nodo_inizializza(alberobinario_NodoBinario * nodo) {
    if(nodo) {
        nodo->sx = NULL;
        nodo->dx = NULL;
        nodo->contenuto = NULL;
        return nodo;
    }
    return NULL;
}

int alberobinario_contenuto_distruggi(const alberobinario_pFunzioneDistruzioneContenuto pFDisCont, void * distrutto) {
    if(pFDisCont == NULL) return -2;
    if(distrutto == NULL) return -2;
    int ret = pFDisCont(distrutto);
    return ret;
}

alberobinario_NodoBinario * alberobinario_contenuto_assegna(alberobinario_NodoBinario * nodo, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneDistruzioneContenuto pFDC) {
    if(nodo == NULL) return NULL;
    if(contenuto == NULL) return NULL;
    if(dimensioneContenutoByte == 0) return NULL;
    if(pFDC == NULL) return NULL;
    int ret = alberobinario_contenuto_distruggi(pFDC, nodo->contenuto);
    if(ret == 1) return NULL;
    nodo->contenuto = malloc(dimensioneContenutoByte);
    memcpy(nodo->contenuto, contenuto, dimensioneContenutoByte);
    return nodo;
}

alberobinario_NodoBinario * alberobinario_contenuto_cerca(const alberobinario_NodoBinario * root, const void * cercato, const alberobinario_pFunzioneComparazione pFComp) {
        
        if(cercato == NULL) return NULL;
        if(pFComp == NULL) return NULL;
        
        while(1) {
            if(root == NULL) return NULL;
            int ris = (*pFComp)(cercato, root->contenuto);
            if(ris == 0) return (alberobinario_NodoBinario *)root;
            if(ris < 0) {
                if(root->sx) root = root->sx;
                else return NULL;
            }
            if(ris > 0) {
                if(root->dx) root = root->dx;
                else return NULL;
            }
        }
}

alberobinario_NodoBinario * alberobinario_nodo_trova_crea(alberobinario_NodoBinario * root, const void * contenuto, size_t dimensioneContenutoByte, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC) {
    
        if(contenuto == NULL) return NULL;
        if(pFComp == NULL) return NULL;
        if(root == NULL) return NULL;
        if(dimensioneContenutoByte == 0) return NULL;
        
        while(1) {
            
            int ris = (*pFComp)(contenuto, root->contenuto);
            
            if(ris == 0) return root;
            
            if(ris < 0) {
                if(root->sx == NULL) {
                    root->sx = (alberobinario_NodoBinario *) malloc(sizeof(alberobinario_NodoBinario));
                    root->sx = alberobinario_nodo_inizializza(root->sx);
                    alberobinario_NodoBinario * ret = alberobinario_contenuto_assegna(root->sx, contenuto, dimensioneContenutoByte, pFDC);
                    if(ret == NULL) return NULL;
                    root->sx = ret;
                    return root->sx;
                } else {
                    root = root->sx;
                    continue;
                }
            }
            
            if(ris > 0) {
                if(root->dx == NULL) {
                    root->dx = (alberobinario_NodoBinario *) malloc(sizeof(alberobinario_NodoBinario));
                    root->dx = alberobinario_nodo_inizializza(root->dx);
                    alberobinario_NodoBinario * ret = alberobinario_contenuto_assegna(root->dx, contenuto, dimensioneContenutoByte, pFDC);
                    if(ret == NULL) return NULL;
                    root->dx = ret;
                    return root->dx;
                } else {
                    root = root->dx;
                    continue;
                }
            }
        }
}

void alberobinario_stampa(const alberobinario_NodoBinario * root, const alberobinario_pFunzioneStampa pFStampa) {
    if(root == NULL) return;
    if(root->contenuto) (*pFStampa)(root->contenuto);
    if(root->sx) alberobinario_stampa(root->sx, pFStampa);
    if(root->dx) alberobinario_stampa(root->dx, pFStampa);
    return;
}

int alberobinario_nodo_distruggi(alberobinario_NodoBinario * root, const void * contenuto, const alberobinario_pFunzioneComparazione pFComp, const alberobinario_pFunzioneDistruzioneContenuto pFDC) { // usare una funzione per gestire le eliminazioni user-implemented
    if(contenuto == NULL) return -1;
    if(pFComp == NULL) return -1;
    if(root == NULL) return -1;
    if(pFDC == NULL) return -1;
    
    alberobinario_NodoBinario * padre = NULL;
    int direzioneFiglioMorto = 0; // serve per segnalare al padre dove è il figlio morto quando lo si informa della sventura
    alberobinario_NodoBinario * rootCerca = root;
    alberobinario_NodoBinario * rootElimina = NULL;
    
    while(1) {
        int ris = (*pFComp)(contenuto, root->contenuto);
        if(ris == 0) {
            rootElimina = rootCerca;
            break;
        }
        padre = rootCerca;
        if(ris < 0) {
            if(rootCerca->sx) rootCerca = rootCerca->sx;
            else return 0; // non si è trovato ciò che si vuole eliminare
        }
        if(ris > 0) {
            if(rootCerca->dx) rootCerca = rootCerca->dx;
            else return 0; // non si è trovato ciò che si vuole eliminare
        }
    }
    // se rootElimina è null vuol dire che non è stato trovato il nodo che si desidera eliminare, quindi ritornare 0
    if(rootElimina == NULL) return 0;
    // tenere in considerazione che se padre è uguale a null allora saltare il passaggio di promozione del figlio, cioè invece eliminare direttamente il nodo root e ritornare 1, perché non ce ne sono di figli, perché se ce ne fossero padre non sarebbe uguale a NULL
    if(padre == NULL) {
        int ret = alberobinario_contenuto_distruggi(pFDC, root->contenuto);
        if(ret == 1) return -2; 
        // ret non dovrebbe mai essere uguale a -1
        free(root); 
        return 1; // tutto con successo
    }
    
    
    // Ora che abbiamo il padre e ciò che cerchiamo, dobbiamo procedere con l'eliminazione di ciò che abbiamo cercato.
    
    while(1) {
        if(rootElimina->sx) {
            rootElimina->contenuto = rootElimina->sx->contenuto;
            rootElimina = rootElimina->sx;
            direzioneFiglioMorto = 1;
            continue;
        }
        if(rootElimina->dx) {
            rootElimina->contenuto = rootElimina->dx->contenuto;
            rootElimina = rootElimina->dx;
            direzioneFiglioMorto = 2;
            continue;
        }
        // se non ci sono figli, si procede all'eliminazione del nodo dall'albero
        int ret = alberobinario_contenuto_distruggi(pFDC, rootElimina->contenuto);
        if(ret == 1) return -2;
        // ret non dovrebbe mai essere uguale a -1
        free(rootElimina);
        // informare il padre che il figlio è morto
        if(direzioneFiglioMorto == 1) padre->sx = NULL;
        if(direzioneFiglioMorto == 2) padre->dx = NULL;
        return 1;
    }
}






