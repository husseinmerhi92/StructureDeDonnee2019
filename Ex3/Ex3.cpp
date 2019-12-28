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

typedef struct PI
{
    double operand;
    char operation;
    bool estOperand;
    PI* suivant;
} PI;

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

void AfficherPile(pile* p)
{
    if (p != NULL)
    {
        cout << " " << p->valeur;
        AfficherPile(p->suivant);
    }
    else
    {
        cout << endl;
    }
}

PI* EmpilerOperand(PI* p, double valeur)
{
    PI* p1 = new PI;
    p1->operand = valeur;
    p1->estOperand = true;
    p1->suivant = p;
    return p1;
}

PI* EmpilerOperation(PI* p, char op)
{
    PI* p1 = new PI;
    p1->operation = op;
    p1->estOperand = false;
    p1->suivant = p;
    return p1;
}

PI* DepilerPI(PI* p)
{
    return p->suivant;
}

double PeekOperand(PI* p)
{
    return p->operand;
}

char PeekOperation(PI* p)
{
    return p->operation;
}

void AfficherPI(PI* p)
{
    if (p != NULL)
    {
        if (p->estOperand)
        {
            cout << " " << p->operand;
        }
        else
        {
            cout << " ";
            cout << p->operation;
        }
        AfficherPI(p->suivant);
    }
    else
    {
        cout << endl;
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

int TailleDList(dlist* dl)
{
    if (dl != NULL)
    {
        return 1 + TailleDList(dl->suivant);
    }
    else
    {
        return 0;
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

void TrierCroissant(dlist* dl)
{
    dlist* curr = dl;
    int taille = TailleDList(dl);
    for (int i = 0; i < taille - 1; i++)
    {
        dlist* tmp = dl;
        for (int j = 0; j < i; j++)
        {
            tmp = tmp->suivant;
        }
        while (tmp != NULL)
        {
            if (curr->valeur > tmp->valeur)
            {
                double vtmp = curr->valeur;
                curr->valeur = tmp->valeur;
                tmp->valeur = vtmp;
            }
            tmp = tmp->suivant;
        }
        curr = curr->suivant;
    }
}

// 2- 
void getReplaceHalf(dlist* dl)
{
    dlist* curr = dl;
    double temp;
    while (curr != NULL)
    {
        if (modf(curr->valeur, &temp) == 0 && (int)curr->valeur % 2 == 0)
        {
            dlist* nouveau = new dlist;
            double moitie = curr->valeur / 2;
            curr->valeur = moitie;
            nouveau->valeur = moitie;
            nouveau->suivant = curr->suivant;
            curr->suivant = nouveau;
            curr = curr->suivant;
        }
        curr = curr->suivant;
    }
}

// 3-
void SeparerPairEtImpair(dlist* dl, pile** p1, pile** p2)
{
    dlist* curr = dl;
    double temp;
    while (curr != NULL)
    {
        if (modf(curr->valeur, &temp) == 0 && (int)curr->valeur % 2 == 0)
        {
            *p1 = Empiler(*p1, curr->valeur);
        }
        else
        {
            *p2 = Empiler(*p2, curr->valeur);
        }
        curr = curr->suivant;
    }
}

// 4-
double Calculer(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        if (b == 0)
        {
            return NULL;
        }
        else
        {
            return a / b;
        }
    default:
        return NULL;
    }
}

double CalculerPI(PI* exp)
{
    PI* curr = exp;
    PI* memoire = NULL;
    while (curr != NULL)
    {
        if (curr->estOperand)
        {
            double operand = PeekOperand(curr);
            curr = DepilerPI(curr);
            memoire = EmpilerOperand(memoire, operand);
        }
        else
        {
            char op = PeekOperation(curr);
            curr = DepilerPI(curr);
            double a = PeekOperand(memoire);
            memoire = DepilerPI(memoire);
            double b = PeekOperand(memoire);
            memoire = DepilerPI(memoire);
            double resulat = Calculer(a, b, op);
            memoire = EmpilerOperand(memoire, resulat);
        }
    }
    return memoire->operand;
}

int operandsPI(PI* p)
{
    int operandNB = 0;
    PI* curr = p;
    while (curr != NULL)
    {
        if (curr->estOperand)
        {
            operandNB++;
        }
        curr = curr->suivant;
    }
    return operandNB;
}

int operationsPI(PI* p)
{
    int operationsNB = 0;
    PI* curr = p;
    while (curr != NULL)
    {
        if (!curr->estOperand)
        {
            operationsNB++;
        }
        curr = curr->suivant;
    }
    return operationsNB;
}

bool ValiderPI(PI* p)
{
    if (operandsPI(p) != (operationsPI(p) + 1))
    {
        return false;
    }
    else
    {
        int indice = 0;
        PI* curr = p;
        while (curr != NULL)
        {
            if (curr->estOperand)
            {
                indice++;
            }
            else
            {
                indice--;
            }
            if (indice < 0)
            {
                return false;
            }
            curr = curr->suivant;
        }
        if (indice != 1)
        {
            return false;
        }
        return true;
    }
}

void CompterOperandEtOperation(PI* p)
{
    int operandNB = 0;
    int operationNB = 0;
    PI* curr = p;
    while (curr != NULL)
    {
        if (curr->estOperand)
        {
            operandNB++;
        }
        else
        {
            operationNB++;
        }
        curr = curr->suivant;
    }
    cout << operandNB << " operands" << endl;
    cout << operationNB << " operations" << endl;
}

int main()
{
    pile* p1 = NULL;
    pile *p2 = NULL;
    dlist* racines = ListeDeRacineDeNewton(7);
    dlist* rationals = ListeDeRationals(5, 2);
    dlist* alternance = ListeParAlternance(racines, rationals);
    AfficherDList(racines);
    AfficherDList(rationals);
    AfficherDList(alternance);
    TrierCroissant(alternance);
    AfficherDList(alternance);
    getReplaceHalf(alternance);
    AfficherDList(alternance);
    SeparerPairEtImpair(alternance, &p1, &p2);
    AfficherPile(p1);
    AfficherPile(p2);

    // Notation Polonaise Inversee
    PI* expression = NULL;
    expression = EmpilerOperation(expression, '*');
    expression = EmpilerOperation(expression, '+');
    expression = EmpilerOperation(expression, '*');
    expression = EmpilerOperation(expression, '+');
    expression = EmpilerOperand(expression, 4);
    expression = EmpilerOperand(expression, 6);
    expression = EmpilerOperation(expression, '+');
    expression = EmpilerOperand(expression, 8);
    expression = EmpilerOperand(expression, 9);
    expression = EmpilerOperand(expression, 7);
    expression = EmpilerOperand(expression, 5);
    AfficherPI(expression);
    cout << CalculerPI(expression) << endl;
    if (ValiderPI(expression))
    {
        cout << "Expression est valide" << endl;
    }
    else
    {
        cout << "Expression n'est pas valide" << endl;
    }
    CompterOperandEtOperation(expression);
}