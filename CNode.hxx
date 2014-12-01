/********************************
 * @author	Romain Semler, Yon Vidal, 
 * 		Jérémy Rossignol, Kévin Rozotte
 * 		Manon Saillard
 * 
 * @file	CNode.hxx
 * 
 * @date	28/11/2014
 * 
 * @update	01/12/2014
 * 
 * @synopsis	Implémentation des fonctions 
 * 		définies dans CNode.h
 * *******************************/

#ifndef __CNODE_HXX__
#define __CNODE_HXX__

#include "CNode.h"
#define TEMPLATE template <class T>

#include <iostream>
#include <memory>

TEMPLATE
CNode<T>::CNode ()
{
	
}

TEMPLATE
CNode<T>::CNode (const T &valeur = T (), const std::shared_ptr <CNode <T> > precedent = 0, const std::shared_ptr <CNode <T> > suivant = 0)
{
	m_Data = valeur;
	m_Prev = precedent;
	m_Next = suivant;
}

TEMPLATE
CNode<T>::~CNode()
{

}

TEMPLATE
T CNode<T>::GetData()
{
    return m_Data;
}

TEMPLATE
void CNode<T>::SetData (const T &valeur)
{
    m_Data = valeur;
}

TEMPLATE
std::shared_ptr <CNode <T> > CNode<T>::GetNextNode()
{
    return m_Next;
}

TEMPLATE
void CNode<T>::SetNextNode(std::shared_ptr <CNode <T> > * next)
{
    m_Next = next;
}

#endif // CNODE_HXX_INCLUDED
