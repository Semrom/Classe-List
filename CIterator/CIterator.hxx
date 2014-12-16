/********************************
* @author   Alexy Torres (autre équipe)
*
* @file     CIterator.hxx
*
* @date     02/12/2014
*
* @update   15/12/2014
*
* @synopsis Implémentation des fonctions
*           de CIterator.h
*
* *******************************/

#ifndef __CITERATOR_HXX__
#define __CITERATOR_HXX__

#include <memory>	
#include "CNode.h"	
#include "CIterator.h"

#define TEMPL    template <class T>
#define TEMPLINL TEMPL inline
#define CITER nsSdD::CIterator <T>
#define Ptr_t std::shared_ptr <nsSdD::CNode <T> >

/******* Constructeurs Citerator *******/

TEMPL
CITER::CIterator (Ptr_t Node)
{
	m_Node = Node;
}

TEMPL
CITER::CIterator (const CIterator &CIterToCopy)
{
	m_Node = CIterToCopy.m_Node;
}

/******* Opérateurs Citerator *******/

TEMPLINL
const T& CITER::operator* (void) const
{
	return m_Node->GetVal ();
}

TEMPLINL
Ptr_t CITER::operator-> (void) const
{
	return m_Node;
}

TEMPLINL
nsSdD::CIterator <T> & CITER::operator++ (void)
{
	m_Node = m_Node->GetSuivant ();
	return *this;
}

TEMPLINL
nsSdD::CIterator <T> CITER::operator++ (int)
{
	CIterator <T> Temp (*this);
	m_Node = m_Node->GetSuivant ();
	return Temp;
}

TEMPLINL
nsSdD::CIterator <T> & CITER::operator= (CIterator CIterToCopy)
{
	m_Node = CIterToCopy.m_Node;
	return *this;
}

TEMPLINL
bool CITER::operator== (CIterator CIterToTest) const
{
	return m_Node == CIterToTest.operator->();
}

TEMPLINL
bool CITER::operator!= (CIterator CIterToTest) const
{
	return m_Node != CIterToTest.operator->();
}

TEMPLINL
bool CITER::operator< (CIterator CIterToTest) const
{
	return m_Node < CIterToTest.operator->();
}

TEMPLINL
bool CITER::operator> (CIterator CIterToTest) const
{
	return m_Node > CIterToTest.operator->();
}

TEMPLINL
bool CITER::operator>= (CIterator CIterToTest) const
{
	return !(operator< (CIterToTest));
}

TEMPLINL
bool CITER::operator<= (CIterator CIterToTest) const
{
	return !(operator> (CIterToTest));
}


#undef Ptr_t
#undef TEMPL
#undef TEMPLINL
#undef CITER

#endif // __CITERATOR_HXX__

