#include <iostream>

using namespace std;

typedef struct pile
{
    int val;
    pile* suivant = NULL;
} pile;

typedef struct arbre
{
    int val;
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
	cout << root->val;

	cout << endl;
	printBinaryTree(root->gauche, space, height);
}

void Afficher2D(arbre* a) {
	cout << "## start ##";
	printBinaryTree(a, 0, 4);
	cout << "## end ##" << endl;
}

void AfficherInfix(arbre* a)
{
	if (a != NULL)
	{
		AfficherInfix(a->gauche);
		cout << " " << a->val;
		AfficherInfix(a->droite);
	}
}

void AfficherPrefix(arbre* a)
{
	if (a != NULL)
	{
		cout << " " << a->val;
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
		cout << " " << a->val;
	}
}

void inverserArbre(arbre* a)
{
    if (a != NULL)
    {
        arbre* tmp = a->gauche;
        a->gauche = a->droite;
        a->droite = tmp;
        inverserArbre(a->gauche);
        inverserArbre(a->droite);
    }
}

arbre* insererValeur(arbre* a, int val)
{
	if (a == NULL)
	{
		a = new arbre;
		a->val = val;
		return a;
	}
	else if (a->val > val)
	{
		if (a->gauche == NULL)
		{
			arbre* n = new arbre;
			n->val = val;
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
			n->val = val;
			a->droite = n;
		}
		else
		{
			insererValeur(a->droite, val);
		}
	}
}

arbre* creeArbre(int T[], int n)
{
	arbre* a = NULL;
	for (int i = 0; i < n; i++)
	{
		if (a == NULL)
		{
			a = insererValeur(a, T[i]);
		}
		else
		{
			insererValeur(a, T[i]);
		}
	}
	return a;
}

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

void NoeudParNiveau(arbre* a, int niveau, int* nb)
{
	if (a != NULL)
	{
		nb[niveau]++;
		niveau++;
		NoeudParNiveau(a->gauche, niveau, nb);
		NoeudParNiveau(a->droite, niveau, nb);
	}
}

int SommeArbre(arbre* a)
{
	if (a != NULL)
	{
		return a->val + SommeArbre(a->gauche) + SommeArbre(a->droite);
	}
	else
	{
		return 0;
	}
}

void TotalArbre(arbre* a)
{
	if (a != NULL)
	{
		int gaucheSomme = SommeArbre(a->gauche);
		int droiteSomme = SommeArbre(a->droite);
		cout << "la somme a gauche est " << gaucheSomme << endl;
		cout << "la somme a droite est " << droiteSomme << endl;
		cout << "la somme de l'arbre est " << gaucheSomme + droiteSomme << endl;
	}
}

int main()
{
	//construire l'arbre
	arbre* a = new arbre;
	a->val = 15;

	a->droite = new arbre;
	a->droite->val = -31;

	a->droite->gauche = new arbre;
	a->droite->gauche->val = 17;

	a->gauche = new arbre;
	a->gauche->val = 8;

	a->gauche->gauche = new arbre;
	a->gauche->gauche->val = 23;
	a->gauche->droite = new arbre;
	a->gauche->droite->val = -6;

	Afficher2D(a);

	cout << "Infix: "; AfficherInfix(a); cout << endl;
	cout << "Prefix: "; AfficherPrefix(a); cout << endl;
	cout << "Postfix: "; AfficherPostfix(a); cout << endl;

	int n = Hauteur(a);
	int* nb = new int[n];
	cout << "nb noeuds par niveau" << endl;
	for (int i = 0; i < n; i++) { nb[i] = 0; }
	NoeudParNiveau(a, 0, nb);
	for (int i = 0; i < n; i++) { cout << "niveau " << i << " :" << nb[i] << endl; }

	TotalArbre(a);

	int T[] = { 23, -6, 8, 17, -31, 15 };
	arbre* b = creeArbre(T, 6);
	Afficher2D(b);
}
