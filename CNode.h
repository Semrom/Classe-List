#ifndef __CNODE_H__
#define __CNODE_H__

#include <memory>

template <typename T>

	class CNode
	{
		private:
			//Variable pour la position de l'élément (T)
			T m_Data;

			//Varaible pour l'élément suivant (smart pointeur)
			std::shared_ptr <CNode <T> > m_Next;

		public:
				/******* Constructeur CNode *******/

				CNode (int i = 0, std::shared_ptr <CNode <T> > ptr = nullptr);

				/******* Destructeur CNode *******/

				~CNode();

				/******* Getter & Setter *******/

				//Récupérer la position de l'élément
				int GetData() const;

				//Récupérer l'élément suivant
				std::shared_ptr <CNode <T> > GetNextNode() const;

				//Modifier la position d'un élément
				void SetData(int value);

				//Modifier l'élément suivant
				void SetNextNode(std::shared_ptr <CNode <T> >);

	}; // CNode

#endif // CNODE_H
