#include <iostream>

const double pi = 3.1415;

typedef struct list
{
	int valeur;
	list* suivant;
} list;

// a-
int XnRec(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return x * XnRec(x, n - 1);
	}
}

int FacRec(int n)
{
	if (n == 0 || n == 1)
	{
		return 1;
	}
	else
	{
		return n * FacRec(n - 1);
	}
}

int DeriveeXn(int x, int n)
{
	return n * XnRec(x, n - 1);
}

// b-
double S1(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return pi * (pow(x, n) / FacRec(n)) + S1(x, n - 1);
	}
}

double S2(int x, int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return pow(x, n) / pow(x + 1, n) + S2(x, n - 1);
	}
}

// c-
double Px(int x, int a[], int n)
{
	if (n == 0)
	{
		return 1;
	}
	else
	{
		return (double)a[n] * (XnRec(x, n) / FacRec(n)) + Px(x, a, n - 1);
	}
}

// d-
void Afficherlist(list* tete)
{
	if (tete == NULL)
	{
		std::cout << "la list est vide" << std::endl;
	}
	else
	{
		list* tmp = tete;
		while (tmp != NULL)
		{
			std::cout << " " << tmp->valeur;
			tmp = tmp->suivant;
		}
		std::cout << std::endl;
	}
}

list* ListAPartirDeTableau(int a[], int n)
{
	list* tete = new list;
	tete->valeur = a[0];
	tete->suivant = NULL;

	list* tmp = tete;
	for (int i = 1; i < n; i++)
	{
		tmp->suivant = new list;
		tmp = tmp->suivant;
		tmp->valeur = a[i];
		tmp->suivant = NULL;
	}

	return tete;
}

// e-
void GetReplaceThird(list* tete)
{
	if (tete != NULL)
	{
		list* tmp = tete;
		while (tmp != NULL)
		{
			if (tmp->valeur % 2 == 0)
			{
				list* nouveau = new list;
				int moitie = tmp->valeur / 2;
				tmp->valeur = moitie;
				nouveau->valeur = moitie;
				nouveau->suivant = tmp->suivant;
				tmp->suivant = nouveau;
				tmp = nouveau->suivant;
			}
			else
			{
				tmp = tmp->suivant;
			}
		}
	}
}

// f-
void RemplacerPairAvecImpairIndex(list* tete)
{
	list* tmp = tete;
	while (tmp != NULL && tmp->suivant != NULL)
	{
		int temp = tmp->valeur;
		tmp->valeur = tmp->suivant->valeur;
		tmp->suivant->valeur = temp;
		tmp = tmp->suivant->suivant;
	}
}

int main()
{
	int x, n, * a;
	double r;
	std::cout << "donner le valeureur de x : ";
	std::cin >> x;
	std::cout << "donner le valeur de n (taille d'un tableau des entiers): ";
	std::cin >> n;
	a = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		std::cout << "donner le valeur de a[" << i << "]: ";
		std::cin >> a[i];
	}
	std::cout << x << "^" << n << "= " << XnRec(x, n) << std::endl;
	std::cout << n << "!= " << FacRec(n) << std::endl;
	std::cout << "S1(" << x << "," << n << ")= " << S1(x, n) << std::endl;
	std::cout << "S2(" << x << "," << n << ")= " << S2(x, n) << std::endl;
	std::cout << "P(" << x << ")= " << Px(x, a, n - 1) << std::endl;
	list* tete1 = ListAPartirDeTableau(a, n);
	std::cout << "liste a partir du tableau:";
	Afficherlist(tete1);
	GetReplaceThird(tete1);
	std::cout << "liste apres divise les noeuds containent valeur paires en deux noeuds:";
	Afficherlist(tete1);
	RemplacerPairAvecImpairIndex(tete1);
	std::cout << "liste apres alterer les valeurs des noeuds d'indice pair et impair:";
	Afficherlist(tete1);
}
