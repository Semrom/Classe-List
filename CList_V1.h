/********************************
* @author   Alexy Torres (autre équipe)
*
* @file     CList.h
*
* @date     24/11/2014
*
* @update   15/12/2014
*
* @synopsis Classe CList.h, version 1
*
* *******************************/

#ifndef __CLIST_H__
#define __CLIST_H__

#include <memory>   // std::shared_ptr
#include <vector>   // std::vector
#include <utility>	// std::swap

#include "CNode.h"  

template <class T>
class CList
{
  private:
      void QuickSort (std::vector <T> &Vect, int Left, int Right = 0);
  
  protected:
      size_t m_Size;
      std::shared_ptr <CNode <T> > m_Cursor;
      std::shared_ptr <CNode <T> > m_Head;
      std::shared_ptr <CNode <T> > m_Queue;
      
  public:
      /******* Constructeurs CList *******/
			typedef T& reference;
			typedef const T& const_reference;
      explicit CList (void);
      explicit CList (size_t N);
      explicit CList (size_t N, const T &KValue);
      CList (const CList &CListCopy);
      
      /******* Destructeur CList *******/
      ~CList (void);
      
      /******* Fonctions de CList *******/
      void push_back  (const T &KValue);
      void push_front (const T &KValue);
      void pop_back   (void);
      void pop_front  (void);
      void remove     (const T &KValue);
      size_t size     (void) const noexcept;
      bool empty      (void) const noexcept;
      void clear      (void);
      reference back  (void);
      reference front (void);
      const_reference back (void) const;
      const_reference front (void) const;
      CList& operator= (const CList& CListCopy);
      void swap   (CList &CListToSwap);
      void unique (void);
      
      std::shared_ptr <CNode <T> > GetSuivant (void);
      std::shared_ptr <CNode <T> > GetPrecedent (void);
      
      void resize     (size_t Value, const T &KValue = T ());
      void assign (size_t N, const T &KValue);
      void sort   (void);
      
      template <class Predicate>
          void remove_if (Predicate Pred);
          void reverse    (void);
          void merge (CList& CListToMerge);

	template <class Compare>
	  void merge (CList& CListToMerge, Compare Comparator);

};

#include "CList.hxx"  

#endif 
