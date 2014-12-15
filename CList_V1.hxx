/********************************
* @author   Alexy Torres (autre équipe)
*
* @file     CList_V1.hxx
*
* @date     24/11/2014
*
* @update   15/12/2014
*
* @synopsis Classe CList.hxx, version 1
*
* *******************************/

#ifndef __CLIST_HXX__
#define __CLIST_HXX__

#include <memory>	
#include <vector>  
#include <utility>

#include "CList.h" 
#include "CNode.h" 

#define TEMPL template <class T>
#define TEMPLINL TEMPL inline
#define CLIST nsSdD::CList <T>
#define Ptr_t std::shared_ptr <nsSdD::CNode <T> >

/******* Constructeurs CList *******/

TEMPL
CLIST::CList (void)
{
    // Modifier la taille de la liste
    m_Size = 0;

    // Création de deux sentinelles
    m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
    m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

    // Modifier les sentinelles
    m_Head->SetSuivant (m_Queue);

    // Modifier le curseur à la tête de liste
    m_Cursor = m_Head;

}

TEMPL
CLIST::CList (size_t N)
{
  // Modifier la taille de la liste
  m_Size = N;

  // Création de deux sentinelles
  m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
  m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

  // Modifier les sentinelles
  m_Head->SetSuivant (m_Queue);

  // Parcours de la liste avec n éléments
  for (size_t i = 0; i < N; ++i)
  {
      // Créer un nouvel objet CNode
    	Ptr_t NewNode (new CNode <T> (T ()));

      // Modifier ce nouvel objet
      NewNode->SetPrecedent (m_Head);
      NewNode->SetSuivant (m_Head->GetSuivant ());

      // Modifier la sentinelle de tête
      m_Head->GetSuivant ()->SetPrecedent (NewNode);
      m_Head->SetSuivant (NewNode);
  }

    // Modifier le curseur à Head
      m_Cursor = m_Head;

} 

TEMPL
CLIST::CList (size_t N, const T &KValue)
{
  // Modifier la taille de la liste
  m_Size = N;

  // Création de deux sentinelles
  m_Head = std::make_shared <CNode <T> > (CNode <T> (T ()));
  m_Queue = std::make_shared <CNode <T> > (CNode <T> (T (), m_Head));

  // Modifier les sentinelles
  m_Head->SetSuivant (m_Queue);

  // Parcours de la liste avec n éléments
  for (size_t i = 0; i < N; ++i)
  {
      // Créer un nouvel objet CNode
    	Ptr_t NewNode (new CNode <T> (T ()));

      // Modifier ce nouvel objet
      NewNode->SetPrecedent (m_Head);
      NewNode->SetSuivant (m_Head->GetSuivant ());

      // Modifier la sentinelle de tête
      m_Head->GetSuivant ()->SetPrecedent (NewNode);
      m_Head->SetSuivant (NewNode);
  }

  m_Cursor = m_Head;
} 

TEMPL
CLIST::CList (const CList <T> &CListCopy)
{
	// Copier les pointeurs et la taille de la liste
	m_Size = CListCopy.m_Size;
	m_Head = CListCopy.m_Head;
	m_Queue = CListCopy.m_Queue;
	m_Cursor = CListCopy.m_Cursor;
} 

TEMPL
CLIST::~CList (void)
{
	// Effacer la liste pour reset tous les smart pointers
	if (m_Head->GetSuivant ()->GetSuivant ())
		for (Ptr_t Curseur = m_Head->GetSuivant ()->GetSuivant (); Curseur; Curseur = Curseur->GetSuivant ())
		{
			// Libérer les pointeurs
			Curseur->GetPrecedent ().reset ();
		}
	m_Head.reset ();
	m_Queue.reset ();
	m_Cursor.reset ();
	m_Size = 0;
} 

/******* Fonctions CList *******/

TEMPL
void CLIST::pop_back (void)
{
	// Bouger le curseur avant la valeur que l'on veut supprimer (si c'est possible)
	Ptr_t Cursor = m_Queue->GetPrecedent ()->GetPrecedent ();
	if (Cursor)
	{
		// Libération de la mémoire par suppression du smart pointer
		Cursor->GetSuivant ().reset ();

		// Changer la valeur suivante du Node
		Cursor->SetSuivant (m_Queue);

		// Changer la valeur précédente de la queue de la liste
		m_Queue->GetPrecedent ().reset ();
		m_Queue->SetPrecedent (Cursor);
	}

	//Redimensionner la liste
	--m_Size;

} 

TEMPL
void CLIST::pop_front (void)
{
	// Créer un curseur sur Head
	Ptr_t Cursor = m_Head->GetSuivant ()->GetSuivant ();

	// Bouger le curseur après la valeur que l'on veut supprimer
	if (Cursor)
	{
		// Libérer la mémoire en supprimant le smart pointer
		Cursor->GetPrecedent ().reset ();

		// Modifier la valeur précédente du Node
		Cursor->SetPrecedent (m_Head);

		// Modifier la valeur suivant de Head
		m_Head->GetSuivant ().reset ();
		m_Head->SetSuivant (Cursor);
	}

	//Redimensionner la liste
	--m_Size;

} 

TEMPLINL
size_t CLIST::size (void) const noexcept
{
  return m_Size;
} 

TEMPLINL
bool CLIST::empty (void) const noexcept
{
  // Vrai si la taille de la liste = 0
  return (m_Size == 0);
}

TEMPL
void CLIST::resize (size_t Value, const T &KValue /* = T () */)
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
void CLIST::assign (size_t N, const T &KValue)
{
	clear ();
	for (size_t i = 0; i < N; ++i)
		push_back (KValue);
} 

TEMPL
void CLIST::swap (CList <T> &ClistToSwap)
{
	Ptr_t TmpHead = ClistToSwap.m_Head;
	Ptr_t TmpQueue = ClistToSwap.m_Queue;
	Ptr_t TmpCursor = ClistToSwap.m_Cursor;
	size_t TmpSize = ClistToSwap.m_Size;

	ClistToSwap.m_Size =  m_Size;
	ClistToSwap.m_Head = m_Head;
	ClistToSwap.m_Queue = m_Queue;
	ClistToSwap.m_Cursor = m_Cursor;

	m_Size = TmpSize;
	m_Head = TmpHead;
	m_Queue = TmpQueue;
	m_Cursor = TmpCursor;
} 

TEMPL
void CLIST::remove (const T &KValue)
{
	for (Ptr_t Curseur = m_Head->GetSuivant (); Curseur->GetSuivant ();)
	{
		if (Curseur->GetVal () == KValue)
		{

			// Délier le node
			Curseur = Curseur->GetSuivant ();
			Curseur->SetPrecedent (Curseur->GetPrecedent ()->GetPrecedent ());

			// Libérer la mémoire
			Curseur->GetPrecedent ()->GetSuivant ().reset ();

			Curseur->GetPrecedent ()->SetSuivant (Curseur);

			--m_Size;
		}
		else
		{
			Curseur = Curseur->GetSuivant ();
		}
	}
} 

TEMPL template <class Predicate>
void CLIST::remove_if (Predicate Pred)
{
	for (Ptr_t Curseur = m_Head->GetSuivant (); Curseur->GetSuivant (); Curseur = Curseur->GetSuivant ())
	{
		//std::cout << Pred (Curseur->GetVal ()) << " | " << Curseur->GetVal () << std::endl;
		if (Pred (Curseur->GetVal ()))
		{
			// Délier le node
			Curseur = Curseur->GetSuivant ();
			Curseur->SetPrecedent (Curseur->GetPrecedent ()->GetPrecedent ());

			// Libérer la mémoire
			Curseur->GetPrecedent ()->GetSuivant ().reset ();

			Curseur->GetPrecedent ()->SetSuivant (Curseur);

			Curseur = Curseur->GetPrecedent ();
			--m_Size;
		}
	}
} 

TEMPL
void CLIST::push_back  (const T &Value)
{
	Ptr_t NewNode (new CNode <T> (Value));

	NewNode->SetPrecedent (m_Queue->GetPrecedent ());
	NewNode->SetSuivant (m_Queue);

	m_Queue->SetPrecedent (NewNode);
	NewNode->GetPrecedent ()->SetSuivant (NewNode);

	++m_Size;
} 

TEMPL
void CLIST::push_front(const T &Value)
{
	Ptr_t NewNode (new CNode <T> (Value));

	NewNode->SetPrecedent (m_Head);
	NewNode->SetSuivant (m_Head->GetSuivant ());

	m_Head->SetSuivant (NewNode);
	NewNode->GetSuivant ()->SetPrecedent (NewNode);

	++m_Size;
} 

TEMPL
void CLIST::unique (void)
{
	for (Ptr_t CurrentNode = m_Head->GetSuivant ();
		 CurrentNode->GetSuivant ()->GetSuivant ();
		 CurrentNode = CurrentNode->GetSuivant ())
	{
		while (CurrentNode->GetVal () == CurrentNode->GetSuivant ()->GetVal ())
		{
			CurrentNode->SetSuivant (CurrentNode->GetSuivant ()->GetSuivant ());

			CurrentNode->GetSuivant ()->GetPrecedent ().reset ();

			CurrentNode->GetSuivant ()->SetPrecedent (CurrentNode);

			--m_Size;

			if (! CurrentNode->GetSuivant ()->GetSuivant ())
				return;
		}
	}
} 

TEMPL
nsSdD::CList <T>& CLIST::operator= (const CList<T>& CListCopy)
{
	clear ();
	m_Cursor = CListCopy.m_Cursor;
	m_Head = CListCopy.m_Head;
	m_Queue = CListCopy.m_Queue;
	m_Size = CListCopy.m_Size;

	return *this;
} 

/******* Accesseurs CList *******/

TEMPL
Ptr_t CLIST::GetSuivant (void)
{
	// Tester si le suivant n'est pas la queue
	if (m_Cursor->GetSuivant ()->GetSuivant ())
	{
		// Sauvegarder le pointeur à retourner
		Ptr_t ReturnPtr = m_Cursor->GetSuivant ();

		// Bouger le curseur
		m_Cursor = ReturnPtr;

		// Retourner le pointeur
		return ReturnPtr;
	}
	else
	{
		m_Cursor = m_Head;
		return nullptr;
	}
} 

TEMPL
Ptr_t CLIST::GetPrecedent (void)
{
	// tester si le précédent n'est pas la tête
	if (m_Cursor->GetPrecedent ()->GetPrecedent ())
	{
		std::shared_ptr <CNode <T> > ReturnPtr = m_Cursor->GetPrecedent ();

		m_Cursor = m_Cursor->GetPrecedent ();

		return ReturnPtr;
	}
	else
	{
		m_Cursor = m_Head;
		return nullptr;
	}
} 

TEMPL
void CLIST::reverse (void)
{
	CList Temp;

	for (Ptr_t CurrentNode = m_Queue->GetPrecedent ();
		 CurrentNode->GetPrecedent ();
		 CurrentNode = CurrentNode->GetPrecedent ())
	{
		Temp.push_back (CurrentNode->GetVal ());
	}

	*this = Temp;
} 

TEMPL
void CLIST::merge (CList& CListToMerge)
{
	Ptr_t TempCnode;

	for (Ptr_t CurrentNode = CListToMerge.m_Head->GetSuivant ();
		 CurrentNode->GetSuivant ();
		 CurrentNode = TempCnode)
	{
		CListToMerge.m_Head->SetSuivant (CListToMerge.m_Queue);

		TempCnode = CurrentNode->GetSuivant ();
		for (Ptr_t CurrentNodeThis = m_Head->GetSuivant ();
			 CurrentNodeThis->GetSuivant ();
			 CurrentNodeThis = CurrentNodeThis->GetSuivant ())
		{
			if (CurrentNode->GetVal () < CurrentNodeThis->GetVal ())
			{
				CurrentNode->SetSuivant (CurrentNodeThis);
				CurrentNode->SetPrecedent (CurrentNodeThis->GetPrecedent ());

				CurrentNode->GetPrecedent ()->SetSuivant (CurrentNode);

				CurrentNodeThis->SetPrecedent (CurrentNode);

				--CListToMerge.m_Size;
				++m_Size;
				break;
			}
			// Si le suivant est la queue
			else if (! CurrentNodeThis->GetSuivant ()->GetSuivant ())
			{
				// Modifier le nouveau Node
				CurrentNode->SetSuivant (m_Queue);
				CurrentNode->SetPrecedent (CurrentNodeThis);

				// Modifier le Node précédent
				CurrentNodeThis->SetSuivant (CurrentNode);

				// Modifier la queue de la liste
				m_Queue->SetPrecedent (CurrentNode);

				--CListToMerge.m_Size;
				++m_Size;

				break;
			}
		}
	}

	CListToMerge.m_Queue->SetPrecedent (CListToMerge.m_Head);

	TempCnode.reset ();
} 

TEMPL
template <class Compare>
void CLIST::merge (CList& CListToMerge, Compare Comparator)
{
	Ptr_t TempCnode;

	for (Ptr_t CurrentNode = CListToMerge.m_Head->GetSuivant ();
		 CurrentNode->GetSuivant ();
		 CurrentNode = TempCnode)
	{
		CListToMerge.m_Head->SetSuivant (CListToMerge.m_Queue);

		TempCnode = CurrentNode->GetSuivant ();
		for (Ptr_t CurrentNodeThis = m_Head->GetSuivant ();
			 CurrentNodeThis->GetSuivant ();
			 CurrentNodeThis = CurrentNodeThis->GetSuivant ())
		{
			if (Comparator (CurrentNode->GetVal (), CurrentNodeThis->GetVal ()))
			{
				CurrentNode->SetSuivant (CurrentNodeThis);
				CurrentNode->SetPrecedent (CurrentNodeThis->GetPrecedent ());

				CurrentNode->GetPrecedent ()->SetSuivant (CurrentNode);

				CurrentNodeThis->SetPrecedent (CurrentNode);

				--CListToMerge.m_Size;
				++m_Size;
				break;
			}
			else if (! CurrentNodeThis->GetSuivant ()->GetSuivant ())
			{
				CurrentNode->SetSuivant (m_Queue);
				CurrentNode->SetPrecedent (CurrentNodeThis);

				CurrentNodeThis->SetSuivant (CurrentNode);

				m_Queue->SetPrecedent (CurrentNode);

				--CListToMerge.m_Size;
				++m_Size;

				break;
			}
		}
	}

	CListToMerge.m_Queue->SetPrecedent (CListToMerge.m_Head);

	TempCnode.reset ();
} 

/******* Fonctions "sort" CList *******/

TEMPL
void CLIST::sort (void)
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
void CLIST::QuickSort (std::vector <T> &Vect, int Left, int Right /* = 0 */)
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

/******* Fonctions "inline" CList *******/

TEMPLINL
T& CLIST::back (void)
{
	return m_Queue->GetPrecedent ()->GetVal ();
} 

TEMPLINL
T& CLIST::front (void)
{
	return m_Head->GetSuivant ()->GetVal ();
} 

TEMPLINL
const T& CLIST::back (void) const
{
	return m_Queue->GetPrecedent ()->GetVal ();
}

TEMPLINL
const T& CLIST::front (void) const
{
	return m_Head->GetSuivant ()->GetVal ();
} 


TEMPLINL
void CLIST::clear (void)
{
	for (; m_Size;)
		pop_back ();
	m_Head->SetSuivant (m_Queue);
	m_Queue->SetPrecedent (m_Head);
} 

#undef Ptr_t
#undef TEMPL
#undef TEMPLINL
#undef CLIST

#endif // __CLIST_HXX__

