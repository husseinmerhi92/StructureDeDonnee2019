#include <iostream>
#include <iostream>

using namespace std;

typedef struct arbre
{
    char cle;
    arbre* gauche = NULL;
    arbre* droite = NULL;
} arbre;

bool AAucuneFeuilles(arbre* a)
{
    if (a->gauche == NULL && a->droite == NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool ADeuxFeuilles(arbre* a)
{
    if (a->gauche != NULL && a->droite != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool EstNumero(char c)
{
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        return true;
    default:
        return false;
    }
}

bool EstOperation(char c)
{
    switch (c)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        return true;
    default:
        return false;
    }
}

// 1-
void AfficherInfix(arbre* a, bool premiere)
{
    if (a != NULL)
    {
        bool avoirParenthese = !premiere && ADeuxFeuilles(a);
        if (avoirParenthese)
        {
            cout << "(";
        }
        AfficherInfix(a->gauche, false);
        cout << a->cle;
        AfficherInfix(a->droite, false);
        if (avoirParenthese)
        {
            cout << ")";
        }
    }
}

void AfficherPrefix(arbre* a)
{
    if (a != NULL)
    {
        cout << a->cle;
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
        cout << a->cle;
    }
}

// 2-
double Eval(arbre* a)
{
    if (AAucuneFeuilles(a))
    {
        return (double)a->cle - 48;
    }
    else
    {
        switch (a->cle)
        {
        case '+':
            return Eval(a->gauche) + Eval(a->droite);
        case '-':
            return Eval(a->gauche) - Eval(a->droite);
        case '*':
            return Eval(a->gauche) * Eval(a->droite);
        case '/':
            return Eval(a->gauche) / Eval(a->droite);
        }
    }
}

// 3-
bool ValiderArbre(arbre* a)
{
    if (a != NULL)
    {
        if (EstOperation(a->cle) && ADeuxFeuilles(a))
        {
            return true && ValiderArbre(a->gauche) && ValiderArbre(a->droite);
        }
        else if (EstNumero(a->cle) && AAucuneFeuilles(a))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// 4-
void ParcoursProfondeur(arbre* a)
{
    if (a != NULL)
    {
        cout << a->cle;
        ParcoursProfondeur(a->gauche);
        ParcoursProfondeur(a->droite);
    }
}

// 5-
arbre* RotationGauche(arbre* a)
{
    if (a->droite != NULL)
    {
        arbre* tmp = a->droite;
        a->droite = NULL;
        a->droite = tmp->gauche;
        tmp->gauche = a;
        return tmp;
    }
    else
    {
        return a;
    }
}

int main()
{
    // construire ((A - B) * (C + D / E)) - F
    // ((9 - 5) * (2 + 6 / 3)) - 7 = 13
    
    arbre* a = new arbre;
    arbre* curr = a;
    curr->cle = '-';

    curr->droite = new arbre;
    curr->gauche = new arbre;
    curr->droite->cle = '7';
    curr->gauche->cle = '*';

    curr = curr->gauche;
    curr->gauche = new arbre;
    curr->droite = new arbre;
    curr->gauche->cle = '-';
    curr->droite->cle = '+';

    curr->gauche->gauche = new arbre;
    curr->gauche->droite = new arbre;
    curr->gauche->gauche->cle = '9';
    curr->gauche->droite->cle = '4';
    
    curr = curr->droite;
    curr->gauche = new arbre;
    curr->droite = new arbre;
    curr->gauche->cle = '2';
    curr->droite->cle = '/';

    curr = curr->droite;
    curr->gauche = new arbre;
    curr->droite = new arbre;
    curr->gauche->cle = '6';
    curr->droite->cle = '3';

    cout << "Infix: "; AfficherInfix(a, true); cout << endl;
    cout << "Prefix: "; AfficherPrefix(a); cout << endl;
    cout << "Postfix: "; AfficherPostfix(a); cout << endl;

    if (ValiderArbre(a))
    {
        cout << "cet arbre est valide" << endl;
    }
    else
    {
        cout << "cet arbre n'est pas valide" << endl;
    }

    AfficherInfix(a, true); cout << " = " << Eval(a) << endl;
    cout << "Parcours Par Profondeur "; ParcoursProfondeur(a); cout << endl;

    cout << "Arbre Initial : "; AfficherInfix(a, true); cout << endl;
    a->gauche = RotationGauche(a->gauche);
    cout << "Apres Rotation : "; AfficherInfix(a, true); cout << endl;
}

