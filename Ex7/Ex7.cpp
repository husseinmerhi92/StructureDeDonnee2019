#include <iostream>

using namespace std;

typedef struct charfreq
{
    char c = NULL;
    int freq = 0;
} charfreq;

typedef struct arbre
{
    char c;
    int freq;
    arbre* gauche = NULL;
    arbre* droite = NULL;
} arbre;

typedef struct list
{
    arbre* a = new arbre;
    list* suivant = NULL;
} list;

void printBinaryTree(arbre* root, int space, int height)
{
    if (root == nullptr)
        return;

    space += height;

    printBinaryTree(root->droite, space, height);
    cout << endl;

    for (int i = height; i < space; i++)
        cout << ' ';
    cout << root->c << ":" << root->freq;

    cout << endl;
    printBinaryTree(root->gauche, space, height);
}

void Afficher2D(arbre* a) {
    cout << "## start ##";
    printBinaryTree(a, 0, 4);
    cout << "## end ##" << endl;
}

void AfficherList(list* l)
{
    if (l != NULL)
    {
        cout << l->a->c << ":" << l->a->freq << endl;
        AfficherList(l->suivant);
    }
    else
    {
        cout << "## list ##" << endl;
    }
}

list* empiler(list* l, arbre* a)
{
    list* nouveau = new list;
    nouveau->a = a;
    nouveau->suivant = l;
    return nouveau;
}

list* depiler(list* l)
{
    return l->suivant;
}

arbre* peek(list* l)
{
    arbre* nouveau = new arbre;
    nouveau->c = l->a->c;
    nouveau->freq = l->a->freq;
    nouveau->droite = l->a->droite;
    nouveau->gauche = l->a->gauche;
    return nouveau;
}

int charAt(charfreq T[100], int n, char c)
{
    for (int i = 0; i < n; i++)
    {
        if (T[i].c == c)
        {
            return i;
        }
    }

    return -1;
}

void Frequence(const char* s, charfreq T[100])
{
    int taille = 0;
    
    for (int i = 0; i < strlen(s); i++)
    {
        int charIndex = charAt(T, taille, s[i]);

        if (charIndex != -1)
        {
            T[charIndex].freq++;
        }
        else
        {
            T[taille].c = s[i];
            T[taille].freq = 1;
            taille++;
        }
    }
}

list* ListeAPartirDuTableau(charfreq T[100])
{
    list* l = NULL;
    list* curr = NULL;
    for (int i = 0; T[i].freq > 0; i++)
    {
        if (l == NULL)
        {
            l = new list;
            l->a->c = T[i].c;
            l->a->freq = T[i].freq;
            curr = l;
        }
        else
        {
            curr->suivant = new list;
            curr = curr->suivant;
            curr->a->c = T[i].c;
            curr->a->freq = T[i].freq;
        }
    }

    return l;
}

list* TrierParCroissant(list* l)
{
    list* nouveau = NULL;
    list* curr = l;
    while (curr != NULL)
    {
        if (nouveau == NULL)
        {
            nouveau = new list;
            nouveau->a->c = curr->a->c;
            nouveau->a->freq = curr->a->freq;
            nouveau->a->gauche = curr->a->gauche;
            nouveau->a->droite = curr->a->droite;
        }
        else
        {
            list* tmp = nouveau;
            list* pre = NULL;
            while (tmp != NULL && curr->a->freq >= tmp->a->freq)
            {
                pre = tmp;
                tmp = tmp->suivant;
            }

            list* q = new list;
            q->a->c = curr->a->c;
            q->a->freq = curr->a->freq;
            q->a->gauche = curr->a->gauche;
            q->a->droite = curr->a->droite;

            if (pre == NULL)
            {
                q->suivant = tmp;
                tmp = q;
                nouveau = tmp;
            }
            else
            {
                q->suivant = tmp;
                pre->suivant = q;
            }
        }
        curr = curr->suivant;
    }

    return nouveau;
}

arbre* max(arbre* a1, arbre* a2)
{
    return (a1->freq >= a2->freq ? a1 : a2);
}

int max(int a1, int a2)
{
    return (a1 >= a2 ? a1 : a2);
}

arbre* min(arbre* a1, arbre* a2)
{
    return (a1->freq < a2->freq ? a1 : a2);
}

arbre* HauffmanArbre(list* l)
{
    while (l->suivant != NULL)
    {
        arbre* a1 = peek(l);
        l = depiler(l);
        arbre* a2 = peek(l);
        l = depiler(l);

        arbre* racine = new arbre;
        racine->c = '$';
        racine->freq = a1->freq + a2->freq;
        racine->gauche = max(a1, a2);
        racine->droite = min(a1, a2);

        l = empiler(l, racine);
        l = TrierParCroissant(l);
    }

    return l->a;
}

int NbInternes(arbre* a)
{
    if (a->gauche != NULL && a->droite != NULL)
    {
        return 1 + NbInternes(a->gauche) + NbInternes(a->droite);
    }
    else
    {
        return 0;
    }

}

int Height(arbre* a)
{
    if (a == NULL)
    {
        return 0;
    }
    else
    {
        int hauteurGauche = Height(a->gauche);
        int hauteurDroite = Height(a->droite);
        return 1 + (hauteurGauche >= hauteurDroite ? hauteurGauche : hauteurDroite);
    }
}

int Maximum(arbre* a)
{
    if (a != NULL)
    {
        int maxGauche = Maximum(a->gauche);
        int maxDroite = Maximum(a->droite);
        int maximum = max(maxGauche, maxDroite);
        if (a->c != '$')
        {
            return max(a->freq, maximum);
        }
        else
        {
            return maximum;
        }
    }
    else
    {
        return 0;
    }
}

void CodeBinaire(arbre* a, string code)
{
    if (a != NULL)
    {
        if (a->c == '$')
        {
            CodeBinaire(a->gauche, code + (string)"0");
            CodeBinaire(a->droite, code + (string)"1");
        }
        else
        {
            cout << a->c << ": " << code << endl;
        }
    }
}

int main()
{
    charfreq T[100];
    Frequence("structures", T);
    list* l = ListeAPartirDuTableau(T);
    list* q = TrierParCroissant(l);
    cout << "les char avec sont frequence: " << endl; 
    AfficherList(q);
    arbre* hauffman = HauffmanArbre(q);
    cout << "Arbre de Hauffman" << endl;
    Afficher2D(hauffman);
    cout << "Hauteur: " << Height(hauffman) << endl;
    cout << "Maximum frequency: " << Maximum(hauffman) << endl;
    cout << "Code Binaire: " << endl;
    CodeBinaire(hauffman, "");
}
