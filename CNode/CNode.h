/********************************
* @author   Romain Semler, Yon Vidal,
*           Jérémy Rossignol, Kévin Rozotte
*           Manon Saillard
*
* @file     CNode.h
*
* @date     28/11/2014
*
* @update   05/12/2014
*
* @synopsis Définitions de fonctions
*           implémentées dans CNode.hxx
* *******************************/

#ifndef __CNODE_H__
#define __CNODE_H__

#include <memory>

template <class T>

class CNode
{
    private:
        //Variable pour la position de l'élément (T)
        T& m_Data;

        //Varaible pour l'élément précédent (smart pointeur)
        std::shared_ptr <CNode <T> > m_Prev;

        //Varaible pour l'élément suivant (smart pointeur)
        std::shared_ptr <CNode <T> > m_Next;

    public:
        /******* Constructeurs CNode *******/
        CNode();
        CNode (const T &valeur = T (), const std::shared_ptr <CNode <T> > precedent = 0,
               const std::shared_ptr <CNode <T>> suivant = 0);

        /******* Destructeur CNode *******/
        ~CNode();

        /******* Getter & Setter *******/

        //Récupérer la position de l'élément
        T GetData(void) const;

        //Récupérer l'élément suivant
        std::shared_ptr <CNode <T> > GetNextNode(void) const;

        //Récupérer l'élément précédent
        std::shared_ptr <CNode <T> > GetPrevNode(void) const;

        //Modifier la position d'un élément
        void SetData(const T &valeur);

        //Modifier l'élément suivant
        void SetNextNode(std::shared_ptr <CNode <T> >);

        //Modifier l'élément précédent
        void SetPrevNode(std::shared_ptr <CNode <T> >);

}; // CNode

#include "CNode.hxx"
#endif // __CNODE_H__
