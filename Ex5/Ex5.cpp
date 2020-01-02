#include <iostream>

using namespace std;

typedef struct arbre
{
	int valeur;
	arbre* gauche = NULL;
	arbre* droite = NULL;
} arbre;

void printBinaryTree(arbre* root, int space, int height)
{
	if (root == nullptr)
		return;

	space += height;

	printBinaryTree(root->droite, space, height);
	cout << endl;

	for (int i = height; i < space; i++)
		cout << ' ';
	cout << root->valeur;

	cout << endl;
	printBinaryTree(root->gauche, space, height);
}

void Afficher2D(arbre* a) {
	cout << "## start ##";
	printBinaryTree(a, 0, 4);
	cout << "## end ##" << endl;
}

// 2-
void AfficherPrefix(arbre* a)
{
	if (a != NULL)
	{
		cout << " " << a->valeur;
		AfficherPrefix(a->gauche);
		AfficherPrefix(a->droite);
	}
}

void AfficherPostfix(arbre* a)
{
	if (a != NULL)
	{
		AfficherPostfix(a->gauche);
		AfficherPostfix(a->droite);
		cout << " " << a->valeur;
	}
}

// 3- 
arbre* insererValeur(arbre* a, int val)
{
	if (a == NULL)
	{
		a = new arbre;
		a->valeur = val;
		return a;
	}
	else if (a->valeur > val)
	{
		if (a->gauche == NULL)
		{
			arbre* n = new arbre;
			n->valeur = val;
			a->gauche = n;
		}
		else
		{
			insererValeur(a->gauche, val);
		}
	}
	else
	{
		if (a->droite == NULL)
		{
			arbre* n = new arbre;
			n->valeur = val;
			a->droite = n;
		}
		else
		{
			insererValeur(a->droite, val);
		}
	}
}

// 4-
void SupprimerR(arbre* a, int val)
{
	if (val < a->valeur)
	{
		SupprimerR(a->gauche, val);
	}
	else if (val > a->valeur)
	{
		SupprimerR(a->droite, val);
	}
	else
	{
		arbre* curr = a->droite;
		arbre* pre = a;
		while (curr->gauche != NULL)
		{
			pre = curr;
			curr = curr->gauche;
		}

		a->valeur = curr->valeur;
		if (pre == a)
		{
			pre->droite = curr->droite;
		}
		else
		{
			pre->gauche = curr->droite;
		}
	}
}

// 5-
void Between(arbre* a, int inf, int sup)
{
	if (a != NULL)
	{
		if (a->valeur >= inf && a->valeur <= sup)
		{
			cout << " " << a->valeur;
		}
		Between(a->gauche, inf, sup);
		Between(a->droite, inf, sup);
	}
}

// 6-
int Hauteur(arbre* a)
{
	if (a == NULL)
	{
		return 0;
	}
	else
	{
		int hauteurGauche = Hauteur(a->gauche);
		int hauteurDroite = Hauteur(a->droite);
		return 1 + (hauteurGauche >= hauteurDroite ? hauteurGauche : hauteurDroite);
	}
}

bool EstEquilibre(arbre* a)
{
	if (a == NULL)
	{
		return true;
	}

	else
	{
		int hauteurGauche = Hauteur(a->gauche);
		int hauteurDroite = Hauteur(a->droite);
		return (abs(hauteurGauche - hauteurDroite) <= 1) && EstEquilibre(a->gauche) && EstEquilibre(a->droite);
	}
}

// 7-
int Maximum(arbre* a)
{
	arbre* curr = a;
	arbre* pre = a;
	while (curr->droite != NULL)
	{
		pre = curr;
		curr = curr->droite;
	}
	int max = curr->valeur;
	if (pre == a)
	{
		a = a->gauche;
	}
	else
	{
		pre->droite = NULL;
	}
	return max;
}

// 8-
void Divise(arbre* a, int val, arbre** SAG, arbre** SAD)
{
	if (a != NULL)
	{
		if (a->valeur < val)
		{
			if (*SAG == NULL)
			{
				*SAG = insererValeur(*SAG, a->valeur);
			}
			else
			{
				insererValeur(*SAG, a->valeur);
			}
		}
		else
		{
			if (*SAD == NULL)
			{
				*SAD = insererValeur(*SAD, a->valeur);
			}
			else
			{
				insererValeur(*SAD, a->valeur);
			}
		}
		Divise(a->gauche, val, SAG, SAD);
		Divise(a->droite, val, SAG, SAD);
	}
}

int main()
{
	arbre* a = NULL;
	int T[] = { 10, 5, 13, 12, 4, 8, 17, 6, 9, 14, 18, 20 };
	a = insererValeur(a, T[0]);
	for (int i = 1; i < 12; i++)
	{
		insererValeur(a, T[i]);
	}

	cout << "Prefix: ";  AfficherPrefix(a); cout << endl;
	cout << "Postfix: "; AfficherPostfix(a); cout << endl;

	cout << "Avant Supprimer 13: " << endl; Afficher2D(a);
	SupprimerR(a, 13);
	cout << "Apres Supprimer 13: " << endl; Afficher2D(a);

	cout << "Valeurs entre 10 et 17: ";  Between(a, 10, 17); cout << endl;

	if (EstEquilibre(a))
	{
		cout << "cet arbre est equilibre" << endl;
	}
	else
	{
		cout << "cet arbre n'est pas equilibre" << endl;
	}

	arbre* SAG = NULL;
	arbre* SAD = NULL;
	Divise(a, 12, &SAG, &SAD);
	cout << "Arbre gauche du a: "; Afficher2D(SAG);
	cout << "Arbre droite du a: "; Afficher2D(SAD);
}
