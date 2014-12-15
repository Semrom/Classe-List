/********************************
* @author   Alexy Torres (autre équipe)
*
* @file     CList_V2.hxx
*
* @date     02/12/2014
*
* @update   15/12/2014
*
* @synopsis Classe CList.hxx, version 2
*
* *******************************/

#ifndef __CLISTV2_HXX__
#define __CLISTV2_HXX__

#include <memory>	
#include <vector>   
#include <utility>	
#include <type_traits>  

#include "CList_V2.h" 		
#include "CNode.h" 		
#include "CIterator.h"	
#include "CRevIterator.h" 

#define TEMPL    template <class T>
#define TEMPLINL TEMPL inline
#define CLISTV2 nsSdD::CListV2 <T>
#define Ptr_t std::shared_ptr <nsSdD::CNode <T> >

 /******* Constructeurs CList V2 *******/

TEMPL
CLISTV2::CListV2 (void)
{
    m_Size = 0;

    m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
    m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

    m_Head->SetSuivant (m_Queue);

} 

TEMPL
CLISTV2::CListV2 (size_t N)
{
	m_Size = N;

	m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
	m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

	m_Head->SetSuivant (m_Queue);

    for (size_t i = 0; i < N; ++i)
    {
    	Ptr_t NewNode (new CNode <T> (T ()));

        NewNode->SetPrecedent (m_Head);
        NewNode->SetSuivant (m_Head->GetSuivant ());

        m_Head->GetSuivant ()->SetPrecedent (NewNode);
        m_Head->SetSuivant (NewNode);
    }

} 

TEMPL
CLISTV2::CListV2 (size_t N, const T &KValue)
{
    m_Size = N;

    m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
    m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

    m_Head->SetSuivant (m_Queue);

    for (size_t i = 0; i < N; ++i)
    {
    	  Ptr_t NewNode (new CNode <T> (KValue));

        NewNode->SetPrecedent (m_Head);
        NewNode->SetSuivant (m_Head->GetSuivant ());

        m_Head->GetSuivant ()->SetPrecedent (NewNode);
        m_Head->SetSuivant (NewNode);
    }

} 

TEMPL
CLISTV2::CListV2 (const CListV2 <T> &CListCopy)
{
	m_Size = CListCopy.m_Size;
	m_Head = CListCopy.m_Head;
	m_Queue = CListCopy.m_Queue;
}

 /******* Destructeur CList V2 *******/
 
TEMPL
CLISTV2::~CListV2 (void)
{
	if (m_Head->GetSuivant ()->GetSuivant ())
		for (Ptr_t Curseur = m_Head->GetSuivant ()->GetSuivant (); Curseur; Curseur = Curseur->GetSuivant ())
		{
			Curseur->GetPrecedent ().reset ();
		}
	m_Head.reset ();
	m_Queue.reset ();
	m_Size = 0;
} 

 /******* Méthodes CList V2 *******/

TEMPL
void CLISTV2::resize (size_t Value, const T &KValue /* = T () */)
{
	if (Value == m_Size)
		return;
	else if (Value < m_Size)
	{
		for (size_t i = 0;i < Value - m_Size; i++)
			pop_back ();
	}
	else if (Value > m_Size)
	{
		for (size_t i = 0; i < m_Size - Value; i++)
			push_back (KValue);
	}
}

TEMPL
void CLISTV2::swap (CListV2 <T> &ClistToSwap)
{
	Ptr_t TmpHead = ClistToSwap.m_Head;
	Ptr_t TmpQueue = ClistToSwap.m_Queue;
	size_t TmpSize = ClistToSwap.m_Size;

	ClistToSwap.m_Size =  m_Size;
	ClistToSwap.m_Head = m_Head;
	ClistToSwap.m_Queue = m_Queue;
	ClistToSwap.m_Cursor = m_Cursor;

	m_Size = TmpSize;
	m_Head = TmpHead;
	m_Queue = TmpQueue;
}

TEMPL
void CLISTV2::remove (const T &KValue)
{
	for (iterator It = begin (); It != end ();)
	{
		iterator TempIt = iterator (It->GetSuivant ());
		if (*It == KValue)
		{
			erase (It);
		}
		It = TempIt;
	}
} 

TEMPL template <class Predicate>
void CLISTV2::remove_if (Predicate Pred)
{
	for (iterator It = begin (); It != end ();)
	{
		iterator TempIt = iterator (It->GetSuivant ());
		if (Pred (*It))
		{
			erase (It);
		}
		It = TempIt;
	}
} 

TEMPL
void CLISTV2::unique (void)
{
	for (iterator It = begin (); It != end ();++It)
	{
		while (*It == It->GetSuivant ()->GetVal ())
		{
			erase (++It);
		}
	}
} 

TEMPL
nsSdD::CListV2 <T>& CLISTV2::operator= (const CListV2<T>& CListCopy)
{
	clear ();
	m_Head = CListCopy.m_Head;
	m_Queue = CListCopy.m_Queue;
	m_Size = CListCopy.m_Size;
	return *this;
} 

TEMPL
void CLISTV2::reverse (void)
{
	CListV2 Temp;
	for (iterator It = begin (); It != end (); ++It)
	{
		Temp.push_front (*It);
	}
	*this = Temp;
} 

TEMPL
void CLISTV2::merge (CListV2& CListToMerge)
{
	for (iterator It2 = CListToMerge.begin (); It2 != CListToMerge.end (); ++It2)
	{
		for (iterator It = begin (); It != end (); ++It)
		{
			if (*It2 < *It)
			{
				insert (It, *It2);
				CListToMerge.erase (It2);

				break;
			}
			else if (It.operator->() == end ()->GetPrecedent ())
			{
				push_back (*It2);
				break;
			}
		}
	}
	CListToMerge.clear ();
} 

TEMPL
template <class Compare>
void CLISTV2::merge (CListV2& CListToMerge, Compare Comparator)
{
	for (iterator It2 = CListToMerge.begin (); It2 != CListToMerge.end (); ++It2)
	{
		for (iterator It = begin (); It != end (); ++It)
		{
			if (Comparator (*It2, *It))
			{
				insert (It, *It2);

				CListToMerge.erase (It2);

				break;
			}
			else if (It.operator->() == end ()->GetPrecedent ())
			{
				push_back (*It2);
				break;
			}
		}
	}

	CListToMerge.clear ();
} 

 /******* Fonctions "sort" CList V2 *******/

TEMPL
void CLISTV2::sort (void)
{
	std::vector <T> TmpVec;

	for (Ptr_t Curseur = m_Head->GetSuivant (); Curseur->GetSuivant (); Curseur = Curseur->GetSuivant ())
		TmpVec.push_back (Curseur->GetVal ());

	QuickSort (TmpVec, TmpVec.size (), 0);

	clear ();

	for (size_t i = 0; i < TmpVec.size (); ++i)
		push_back (TmpVec[i]);
}

TEMPL
void CLISTV2::QuickSort (std::vector <T> &Vect, int Left, int Right /* = 0 */)
{
	while(Left > Right)
	{
		int i = Right;
		int j = Left;

		do
		{
			while (Vect[i] < Vect[Right] && i < j)
				i++;

			while (Vect[Right] < Vect[--j]);

			if(i < j)
				std::swap(Vect[i], Vect[j]);

		}while(i < j);

		std::swap (Vect[Right], Vect[j]);

		if (j - Right > Left - (j + 1))
		{
		   QuickSort(Vect, j-1, Right);
		   Right = j + 1;
		}
		else
		{
		   QuickSort(Vect, Left, j + 1);
		   Left= j - 1;
		}
	}
}

TEMPL
nsSdD::CIterator <T> CLISTV2::erase (iterator Position)
{
	std::shared_ptr <CNode <T> > NextNode;

	for (iterator It = begin (); It != end (); ++It)
	{

		// If we reached the position
		if (It == Position)
		{
			NextNode = It->GetSuivant ();
			// Link the next and previous Node
			It->GetPrecedent ()->SetSuivant (It->GetSuivant ());
			It->GetSuivant ()->SetPrecedent (It->GetPrecedent ());

			// Free the node (clean the memory)
			It->GetSuivant ()->GetPrecedent().reset ();

			--m_Size;

			return iterator (NextNode);
		}

	}
	return iterator (NextNode);
} 

TEMPL
nsSdD::CIterator <T> CLISTV2::erase (iterator First, iterator Last)
{
	iterator It = First;

	for (; It != Last; ++It)
	{
		erase (It);
	}
	return It;
} 

TEMPL
nsSdD::CIterator <T>  CLISTV2::insert (iterator Position, const T &KValue)
{
	std::shared_ptr <CNode <T> > NewNode (new CNode <T> (KValue));

	// If inserting at the begining
	if (Position == begin ())
	{
		NewNode->SetSuivant (m_Head->GetSuivant ());
		NewNode->SetPrecedent (m_Head);

		NewNode->GetPrecedent ()->SetSuivant (NewNode);
		NewNode->GetSuivant ()->SetPrecedent (NewNode);

	}
	else if (Position == end ())
	{
		NewNode->SetSuivant (m_Queue);
		NewNode->SetPrecedent (m_Queue->GetPrecedent ());

		NewNode->GetPrecedent ()->SetSuivant (NewNode);
		NewNode->GetSuivant ()->SetPrecedent (NewNode);
	}
	else
	{
		for (iterator It = begin(); It != end (); ++It)
		{
			if (Position == It)
			{
				NewNode->SetSuivant (It.operator->());
				NewNode->SetPrecedent (It->GetPrecedent ());

				NewNode->GetPrecedent ()->SetSuivant (NewNode);
				NewNode->GetSuivant ()->SetPrecedent (NewNode);

				++ m_Size;
				return iterator (NewNode);
			}
		}
	}
    ++ m_Size;
    return iterator (NewNode);
}

 /*******Fonctions "inline" CList V2 *******/

TEMPLINL
void CLISTV2::push_back  (const T &KValue)
{
	emplace_back (KValue);
} 

TEMPLINL
void CLISTV2::push_front(const T &KValue)
{
	emplace_front (KValue);
} 

TEMPLINL
void CLISTV2::assign (size_t N, const T &KValue)
{
	clear ();
	for (size_t i = 0; i < N; ++i)
		push_back (KValue);
}

TEMPLINL
void CLISTV2::pop_back (void)
{
	iterator ItToDel (end ()->GetPrecedent ());
	erase (ItToDel);
} 

TEMPLINL
void CLISTV2::pop_front (void)
{
	erase (begin ());
} 

TEMPLINL
size_t CLISTV2::size (void) const noexcept
{
    return m_Size;
} 

TEMPLINL
bool CLISTV2::empty (void) const noexcept
{
    return (m_Size == 0);
}

TEMPL
template <class... Args>
inline
nsSdD::CIterator <T> CLISTV2::emplace (const_iterator Position, Args&&... args)
{
	return insert (Position, T (args...));
}

TEMPL
template <class... Args>
inline
nsSdD::CIterator <T> CLISTV2::emplace_back (Args&&... args)
{
	return insert (end (), T (args...));
}

TEMPL
template <class... Args>
inline
nsSdD::CIterator <T> CLISTV2::emplace_front (Args&&... args)
{
	return insert (begin (), T (args...));
}

TEMPLINL
T& CLISTV2::back (void)
{
	return (m_Queue->GetPrecedent ()->GetVal ());
} 

TEMPLINL
T& CLISTV2::front (void)
{
	return (m_Head->GetSuivant ()->GetVal ());
} 

TEMPLINL
const T& CLISTV2::back (void) const
{
	return *(m_Queue->GetPrecedent ()->GetVal ());
} 

TEMPLINL
const T& CLISTV2::front (void) const
{
	return *(m_Head->GetSuivant ()->GetVal ());
} 

TEMPLINL
void CLISTV2::clear (void)
{
	for (; m_Size;)
		pop_back ();
	m_Head->SetSuivant (m_Queue);
	m_Queue->SetPrecedent (m_Head);
} 

TEMPLINL
nsSdD::CIterator <T> CLISTV2::end (void)
{

	return iterator (m_Queue);
}

TEMPLINL
const nsSdD::CIterator <T> CLISTV2::cend (void) const
{
	return const_iterator (m_Queue);
}

TEMPLINL
nsSdD::CRevIterator <T> CLISTV2::rend()
{
	return reverse_iterator (m_Head);
}

TEMPLINL
const nsSdD::CRevIterator <T> CLISTV2::crend() const noexcept
{
	return const_reverse_iterator (m_Head);
}

TEMPLINL
nsSdD::CIterator <T> CLISTV2::begin (void)
{
	return iterator (m_Head->GetSuivant ());
}

TEMPLINL
const nsSdD::CIterator <T> CLISTV2::cbegin (void) const
{

	return const_iterator (m_Head->GetSuivant ());
}

TEMPLINL
nsSdD::CRevIterator <T> CLISTV2::rbegin()
{
	return reverse_iterator (m_Queue->GetPrecedent ());
}

TEMPLINL
const nsSdD::CRevIterator <T> CLISTV2::crbegin() const noexcept
{
	return const_reverse_iterator (m_Queue->GetPrecedent ());
}

TEMPLINL
void CLISTV2::insert (iterator Position, size_t N, const T &KValue)
{
    for (unsigned i = 0; i < N; ++i)
    {
        insert (Position, KValue);
    }
}

TEMPL
template <class InputIterator>
void CLISTV2::insert (iterator Position,InputIterator First, InputIterator Last)
{
	if (! std::is_integral<InputIterator>::value)
	{
		for(InputIterator It = First; It != Last; ++It)
		{
			insert (Position, *It);
		}
	}
}

TEMPL
template <class InputIterator>
inline
void CLISTV2::assign (InputIterator First, InputIterator Last)
{
	clear ();
	for(InputIterator It = First; It != Last; ++It)
		push_back (*It);
}

TEMPLINL
void CLISTV2::splice (iterator Position, CListV2 &CListToSplice)
{
	insert (Position, CListToSplice.begin (), CListToSplice.end ());
	CListToSplice.clear ();
}

TEMPLINL
void CLISTV2::splice (iterator Position, CListV2 &CListToSplice, iterator i)
{
	insert (Position, *i);
	CListToSplice.erase(i);
}

TEMPLINL
void CLISTV2::splice (iterator Position, CListV2 &CListToSplice, iterator first, iterator last)
{
	insert (Position, first, last);
	CListToSplice.erase (first, last);
}

#undef Ptr_t
#undef TEMPL
#undef TEMPLINL
#undef CLISTV2

#endif // __CLISTV2_HXX__

