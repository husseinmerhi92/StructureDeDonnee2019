#include <iostream>

using namespace std;

// 1-
typedef struct date
{
	int jour, mois, annee;
} date;

typedef struct personne
{
	char nom[100];
	int telephone[8];
	date inscription;
	personne* suivant;
} personne;

void AfficherPersonne(personne* tete)
{
	if (tete != NULL)
	{
		cout << " " << tete->nom;
		AfficherPersonne(tete->suivant);
	}
	else
	{
		cout << endl;
	}
}

// 2-
personne* AllouerPersonne()
{
	return (personne*)malloc(sizeof(personne));
}

// 3-
void SaisieDate(date* date)
{
	std::cout << "jour: "; std::cin >> date->jour;
	std::cout << "mois: "; std::cin >> date->mois;
	std::cout << "annee: "; std::cin >> date->annee;
}

// 4-
personne* RecherchePersonne(personne* tete, char nom[])
{
	if (tete == NULL)
	{
		return NULL;
	}
	else
	{
		personne* tmp = tete;
		while (tmp != NULL)
		{
			if (strcmp(nom, tmp->nom) == 0)
			{
				return tmp;
			}
			else
			{
				tmp = tmp->suivant;
			}
		}
		return NULL;
	}

}

// 5-
personne* InsererPersonne(personne* tete, personne* nouvellePersonne)
{
	if (tete == NULL)
	{
		personne* curr = AllouerPersonne();
		strcpy_s(curr->nom, nouvellePersonne->nom);
		curr->suivant = NULL;
		return curr;
	}
	else if (strcmp(nouvellePersonne->nom, tete->nom) < 0)
	{
		personne* curr = AllouerPersonne();
		strcpy_s(curr->nom, nouvellePersonne->nom);
		curr->suivant = tete;
		return curr;
	}
	else
	{
		personne* tmp = tete->suivant, * precedent = tete;
		while (tmp != NULL)
		{
			if (strcmp(nouvellePersonne->nom, tmp->nom) < 0)
			{
				personne* curr = AllouerPersonne();
				strcpy_s(curr->nom, nouvellePersonne->nom);
				curr->suivant = tmp;
				precedent->suivant = curr;
				return tete;
			}
			else
			{
				precedent = tmp;
				tmp = tmp->suivant;
			}
		}
		precedent->suivant = nouvellePersonne;

		return tete;
	}
}

// 6-
personne* FusionnePersonne(personne* tete1, personne* tete2)
{
	personne* tmp1 = tete1, * tmp2 = tete2;
	personne* tete = NULL;
	while (tmp1 != NULL)
	{
		tete = InsererPersonne(tete, tmp1);
		tmp1 = tmp1->suivant;
	}
	while (tmp2 != NULL)
	{
		tete = InsererPersonne(tete, tmp2);
		tmp2 = tmp2->suivant;
	}

	return tete;
}

int main()
{
	// 3-
	date d;
	SaisieDate(&d);
	cout << d.jour << "-" << d.mois << "-" << d.annee << endl;

	// construire une liste des personnes
	personne* tete = AllouerPersonne();
	strcpy_s(tete->nom, "hussein");
	tete->suivant = AllouerPersonne();
	personne* curr = tete->suivant;
	strcpy_s(curr->nom, "ali");
	curr->suivant = AllouerPersonne();
	curr = curr->suivant;
	strcpy_s(curr->nom, "mohamad");
	curr->suivant = NULL;

	// 4-
	char nom[100];
	strcpy_s(nom, "ali");
	personne* recherche = RecherchePersonne(tete, nom);
	if (recherche != NULL)
	{
		cout << recherche->nom << " is found" << endl;
	}
	else
	{
		cout << nom << "is not found" << endl;
	}
	strcpy_s(nom, "abbas");
	recherche = RecherchePersonne(tete, nom);
	if (recherche != NULL)
	{
		cout << recherche->nom << " is found" << endl;
	}
	else
	{
		cout << nom << " is not found" << endl;
	}

	//5-
	personne* tete2 = NULL;
	personne* tmp = AllouerPersonne();
	strcpy_s(tmp->nom, "zeinab");
	tmp->suivant = NULL;
	tete2 = InsererPersonne(tete2, tmp);
	personne* tmp2 = AllouerPersonne();
	strcpy_s(tmp2->nom, "batoul");
	tete2 = InsererPersonne(tete2, tmp2);
	AfficherPersonne(tete2);

	//6-
	personne* tete3 = FusionnePersonne(tete, tete2);
	AfficherPersonne(tete3);
}
