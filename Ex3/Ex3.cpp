#include <iostream>

using namespace std;

typedef struct pile
{
    double valeur;
    pile* suivant;
} pile;

typedef struct rational
{
    int a;
    int b;
} rational;

typedef struct dlist
{
    double valeur;
    dlist* suivant;
    dlist* precedent;
} dlist;

pile* Empiler(pile* p, double valeur)
{
    pile* p1 = new pile;
    p1->valeur = valeur;
    p1->suivant = p;
    return p1;
}

pile* Depiler(pile* p)
{
    return p->suivant;
}

double Peek(pile* p)
{
    return p->valeur;
}

bool EstVide(pile* p)
{
    if (p != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void AfficherDList(dlist* dl)
{
    if (dl != NULL)
    {
        cout << " " << dl->valeur;
        AfficherDList(dl->suivant);
    }
    else
    {
        cout << endl;
    }
}

// 1-
double RacineDeNewton(int a, int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return (RacineDeNewton(a, n - 1) + a / RacineDeNewton(a, n - 1)) / 2;
    }
}

dlist* ListeDeRacineDeNewton(int n)
{
    dlist* dl = NULL;
    dlist* curr = NULL;
    for (int i = 1; i <= n; i++)
    {
        if (dl != NULL)
        {
            curr->suivant = new dlist;
            curr->suivant->precedent = curr;
            curr = curr->suivant;
            curr->valeur = RacineDeNewton(i, 10);
            curr->suivant = NULL;
        }
        else
        {
            dl = new dlist;
            dl->valeur = RacineDeNewton(i, 10);
            dl->precedent = NULL;
            dl->suivant = NULL;
            curr = dl;
        }
    }
    return dl;
}

dlist* ListeDeRationals(int a, int b)
{
    dlist* dl = NULL;
    dlist* curr = NULL;
    for (double i = 1; i <= a; i++)
    {
        if (dl != NULL)
        {
            curr->suivant = new dlist;
            curr->suivant->precedent = curr;
            curr = curr->suivant;
            curr->valeur = pow(i/b,i);
            curr->suivant = NULL;
        }
        else
        {
            dl = new dlist;
            dl->valeur = pow(i / b, i);
            dl->precedent = NULL;
            dl->suivant = NULL;
            curr = dl;
        }
    }
    return dl;
}

dlist* ListeParAlternance(dlist* Dlist1, dlist* Dlist2)
{
    dlist* dl = NULL;
    dlist* curr = NULL;
    dlist* precedent = NULL;
    dlist* curr1 = Dlist1;
    dlist* curr2 = Dlist2;
    if (curr1 == NULL && curr2 == NULL)
    {
        return NULL;
    }
    else {
        while (curr1 != NULL || curr2 != NULL)
        {
            if (dl == NULL)
            {
                dl = new dlist;
                precedent = NULL;
                curr = dl;
            }
            else
            {
                curr->suivant = new dlist;
                precedent = curr;
                curr = curr->suivant;
            }
            if (curr1 != NULL && curr2 != NULL)
            {
                curr->valeur = curr1->valeur;
                curr->precedent = precedent;
                curr->suivant = new dlist;
                curr->suivant->valeur = curr2->valeur;
                curr->suivant->precedent = curr;
                curr->suivant->suivant = NULL;

                curr1 = curr1->suivant;
                curr2 = curr2->suivant;
                precedent = curr;
                curr = curr->suivant;
            }
            else if (curr1 == NULL)
            {
                curr->valeur = curr2->valeur;
                curr->suivant = NULL;
                curr2 = curr2->suivant;
            }
            else if (curr2 == NULL)
            {
                curr->valeur = curr1->valeur;
                curr->suivant = NULL;
                curr1 = curr1->suivant;
            }
        }
    }
    return dl;
}

dlist* TrierCroissant(dlist* Dlist)
{

}

int main()
{
    dlist* racines = ListeDeRacineDeNewton(7);
    dlist* rationals = ListeDeRationals(5, 2);
    dlist* alternance = ListeParAlternance(racines, rationals);
    AfficherDList(racines);
    AfficherDList(rationals);
    AfficherDList(alternance);
    
}
asdawdasdawsdawdsada