/********************************
* @author   Romain Semler, Yon Vidal,
*           Jérémy Rossignol, Kévin Rozotte
*           Manon Saillard
*
* @file     CIterator.h
*
* @date     28/11/2014
*
* @update   05/12/2014
*
* @synopsis Classe itérateur pour
            la version 2 de CList
* *******************************/

#ifndef __CITERATOR_H__
#define __CITERATOR_H__

template <class T>

class CIterator
{
    private:
        std::shared_ptr <CNode <T> > m_Node;

    public:
        /******* Constructeurs CIterator *******/
        CIterator(std::shared_ptr <CNode <T> > Node);
        CIterator (const CIterator &Iterateur);

        /******* Destructeur CIterator *******/
        ~CIterator();

        /******* Operateurs *******/

         const T& operator*(void) const;
         std::shared_ptr <CNode <T> > operator->(void) const;

         CIterator& operator++(void) const; // PreIncrement
         CIterator operator++(int) const;   // PostIncrement

         CIterator& operator=(CIterator Cit) const;

         bool operator==(CIterator Cit) const;
         bool operator!=(CIterator Cit) const;

         bool operator<(CIterator Cit)  const;
         bool operator>(CIterator Cit)  const;

         bool operator<=(CIterator Cit) const;
         bool operator>=(CIterator Cit) const;

};

#include "CIterator.hxx"
#endif // __CITERATOR_H__
