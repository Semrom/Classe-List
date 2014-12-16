/********************************
* @author   Alexy Torres (autre équipe)
*
* @file     CList_V2.h
*
* @date     02/12/2014
*
* @update   15/12/2014
*
* @synopsis Classe CList.h, version 2
*
* *******************************/

#ifndef __CLISTV2_H__
#define __CLISTV2_H__

#include <memory>   	
#include <vector>   		
#include <utility>		
#include <type_traits>  

#include "CNode.h"  	
#include "CIterator.h"	
#include "CRevIterator.h"

template <class T>
class CListV2
{
    protected:
            size_t m_Size;

            std::shared_ptr <CNode <T> > m_Cursor;

            std::shared_ptr <CNode <T> > m_Head;

            std::shared_ptr <CNode <T> > m_Queue;

    private:
            void QuickSort (std::vector <T> &Vect, int Left, int Right = 0);
    
    public:
    	typedef T& reference;
	typedef const T& const_reference;
	typedef const CIterator <T> const_iterator;
	typedef const CRevIterator <T> const_reverse_iterator;
	typedef CRevIterator <T> reverse_iterator;

      explicit CListV2 (void);
      explicit CListV2 (size_t N);
      explicit CListV2 (size_t N, const T &KValue);

      CListV2 (const CListV2 &CListCopy);
      ~CListV2 (void);

      void push_back  (const T &KValue);
      void push_front (const T &KValue);
      void pop_back   (void);
      void pop_front  (void);
      void remove     (const T &KValue);
      size_t size     (void) const noexcept;
      bool empty      (void) const noexcept;
      void clear (void);
      reference back (void);
      reference front (void);
      const_reference back (void) const;
      const_reference front (void) const;
      CListV2& operator= (const CListV2& CListCopy);
      void swap   (CListV2 &CListToSwap);
      void unique (void);
      void resize     (size_t Value, const T &KValue = T ());
      void assign (size_t N, const T &KValue);
      void sort   (void);
      
      template <class Predicate>
            void remove_if (Predicate Pred);
            void reverse    (void);
            void merge (CListV2& CListToMerge);

      template <class Compare>
	    void merge (CListV2& CListToMerge, Compare Comparator);
      
      iterator end (void);
      const_iterator cend (void) const;
      reverse_iterator rend();
      const_reverse_iterator crend() const noexcept;
      iterator begin (void);
      const_iterator cbegin (void) const;
      reverse_iterator rbegin();
      const_reverse_iterator crbegin() const noexcept;

      template <class InputIterator>
            void assign (InputIterator First, InputIterator Last);

      iterator insert (iterator Position, const T &KValue);
      void insert (iterator Position, size_t N, const T &KValue);
      
      template <class InputIterator>
            void insert (iterator Position, InputIterator First, InputIterator Last);
      
      template <class... Args>
            iterator emplace (const_iterator Position, Args&&... args);

      template <class... Args>
			      iterator emplace_back (Args&&... args);

      template <class... Args>
			      iterator emplace_front (Args&&... args);
            iterator erase (iterator Position);
            iterator erase (iterator First, iterator Last);
            void splice (iterator Position, CListV2 &CListToSplice);
            void splice (iterator Position, CListV2 &CListToSplice, iterator i);
            void splice (iterator Position, CListV2 &CListToSplice, iterator first, iterator last);
};

#include "CListV2.hxx"    

#endif // __CLISTV2_H__

