#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
int specializati1,specializati2,specializati3,ab1,ab2,ab3,nrg,n,nra;
int (*p[5])(int,int,int);

typedef struct client
{
    int id_client;
    char nume [20];
    char prenume [20];
    unsigned tip_abonament :2;
    int grupa;
};

typedef struct abonament
{
    int id_abonament;
    int zile_active;
    int pret;
};

typedef struct antrenor
{
    int id_antrenor;
    char nume_antrenor [20];
    char prenume_antrenor [20];
    unsigned specializare :2;
};

typedef struct grupa
{
    int nr_grupa;
    unsigned int tip_grupa:2;
};

typedef struct bonus
{
    _Bool antrenor_personal;
    int reducere;
};

struct client clienti[30];
struct abonament abonamente[30];
struct antrenor antrenori[15];
struct grupa grupe[15];
struct bonus bonusuri[30];

int nr_antrenori_specializati (int a, int g,int specializati) //Functie ce determina numarul de antrenori cu o anumita specializare
{
    if (a==g)
        specializati++;
    return specializati;
}

int calculeaza_pret_abonament (int a, int ap,int pret_antrenor) //Functie ce calculeaza pretul pe care trebuie sa il plateasca un client,
//in functie de tipul de abonament si daca are antrenor personal
{
    if (a==1)
        return 40+ ap*pret_antrenor;
    else if (a==2)
        return 50 + ap*pret_antrenor;
    return 65+ ap*pret_antrenor;
}

int calculeaza_pret_cartela(int a, int ap,int pret_antrenor) //In cazul in care un client nu doreste abonament lunar,
// isi poate procura o cartela cu nr limitat de intrari,
//iar aceasta functie calculeaza pretul cartelei
{
    return a*10+ap*pret_antrenor;
}

int reducere(int pret,int procent,int zile) // Clientii Stay Fit pot beneficia de o reducere de 15% daca au cartela cu mai mult de 15 intrari
{
    float x;
    if (zile > 15)
    {
        x=procent*pret/100;
        pret=(int)x;
    }
    return pret;
}

int nr_abonamente (int a,int tip,int nr) // Functie cu ajutorul careia numar abonamentele de un anumit tip
{
    if (a==tip)
        nr++;
    return nr;
}

int verificare(char s[30]) // Verific daca numele contine doar litere
{
    int i,ok=1;
    for (i=0; i<strlen(s); i++)
        if (!((s[i]>=65 && s[i]<=90) || (s[i]>=97 && s[i]<=122)))
            ok=0;
    return ok;
}

void introducere_grupe() //Citirea datelor despre grupe
{
    int i,aux;
    printf ("Introduceti nr de grupe pe care doriti sa le creati: \n");
    scanf ("%d", &nrg);
    for (i=1; i<=nrg; i++)
    {
        printf ("Introduceti nr grupei: \n");
        scanf ("%d", &grupe[i].nr_grupa);
        printf ("Introduceti tipul grupei : 1) grupa light  2) grupa medium   3)grupa hard  \n");
        scanf ("%d", &aux);
        grupe[i].tip_grupa=aux;
    }
}

void introducere_antrenori() //Citirea datelor despre antrenori
{
    int i,aux;
    printf("Introduceti nr de antrenori disponibili: \n");
    scanf ("%d", &nra);
    for (i=1; i<=nra; i++)
    {
        printf ("Introduceti id_antrenor: \n");
        scanf ("%d", &antrenori[i].id_antrenor);
        printf ("Introduceti numele antrenorului: \n");
        scanf("%s", &antrenori[i].nume_antrenor);
        while(verificare(antrenori[i].nume_antrenor)==0)
        {
            printf("Numele a fost introdus incorect. Va rugam sa introduceti corect informatiile:\n");
            scanf("%s", &antrenori[i].nume_antrenor);
        }
        printf ("Introduceti prenumele antrenorului: \n");
        scanf ("%s", &antrenori[i].prenume_antrenor);
        while(verificare(antrenori[i].prenume_antrenor)==0)
        {
            printf("Prenumele a fost introdus incorect. Va rugam sa introduceti corect informatiile:\n");
            scanf("%s", &antrenori[i].prenume_antrenor);
        }
        printf ("Introduceti specializarea antrenorului : 1) light  2) medium   3)hard  \n");
        scanf ("%d", &aux);
        antrenori[i].specializare=aux;
        specializati1= (*p[0])(aux,1,specializati1); //Numar cati antrenori au o anumita specializare
        specializati2= (*p[0])(aux,2,specializati2);
        specializati3= (*p[0])(aux,3,specializati3);
    }

}

void introducere_clienti() //Citirea datelor despre clienti
{
    int i,aux,t,aux2,conditie,j,pr;
    printf ("Introduceti nr de clienti: \n");
    scanf ("%d", &n);
    for (i=1; i<=n; i++)
    {
        printf ("Introduceti id_client: \n");
        scanf ("%d", &clienti[i].id_client);
        abonamente[i].id_abonament=clienti[i].id_client;
        printf ("Introduceti numele clientului: \n");
        scanf ("%s", &clienti[i].nume);
        while(verificare(clienti[i].nume)==0)
        {
            printf("Numele a fost introdus incorect. Va rugam sa introduceti corect informatiile:\n");
            scanf ("%s", &clienti[i].nume);
        }
        printf ("Introduceti prenumele clientului: \n");
        scanf ("%s", &clienti[i].prenume);
        while(verificare(clienti[i].prenume)==0)
        {
            printf("Prenumele a fost introdus incorect. Va rugam sa introduceti corect informatiile:\n");
            scanf ("%s", &clienti[i].prenume);
        }
        printf ("Pentru abonament lunar apasati tasta 1 sau tasta 2 pentru cartela cu nr limitat de intrari: \n");
        scanf ("%d", &t);
        if (t==1)
        {
            abonamente[i].zile_active=0;
            printf ("Introduceti tipul de abonament: 1) abonament light(40 de lei)  2) abonament medium(50 de lei)   3)abonament hard(65 de lei) \n");
            scanf("%d", &aux);
            ab1=(*p[4])(aux,1,ab1); // Numar abonamentele in functie de tipul lor
            ab2=(*p[4])(aux,2,ab2);
            ab3=(*p[4])(aux,3,ab3);
            clienti[i].tip_abonament=aux;
            printf ("Introduceti 1 pt antrenor personal sau 0 in caz contrar (Beneficiati de antrenor personal achitand o taxa de 30 de lei): \n");
            scanf ("%d", &aux2);
            bonusuri[i].antrenor_personal=aux2;
            abonamente[i].pret=(*p[1]) (aux,aux2,30);
            bonusuri[i].reducere=0;
        }
        else
        {
            printf ("Introduceti nr de zile active ale cartelei (10lei/zi). : \n");
            scanf ("%d", &abonamente[i].zile_active);
            printf ("Introduceti 1 pt antrenor personal sau 0 in caz contrar (Beneficiati de antrenor personal achitand o taxa de 10 de lei): \n");
            scanf ("%d", &aux);
            bonusuri[i].antrenor_personal=aux;
            abonamente[i].pret=(*p[2]) (abonamente[i].zile_active,aux,10);
            pr=(*p[3])(abonamente[i].pret,15,abonamente[i].zile_active);
            if (pr!=abonamente[i].pret)
                abonamente[i].pret=abonamente[i].pret-pr; // In cazul in care clientul are mai mult de 15 zile active
            //  pe cartela va beneficia de o reducere de 15%.
        }
        printf ("Introduceti grupa: \n");
        printf ("Grupe disponibile:\n");
        for (j=1; j<=nrg; j++)
        {
            printf ("Grupa %d cu specializarea  ", grupe[j].nr_grupa);
            if (grupe[j].tip_grupa==1)
                printf("light\n");
            else if (grupe[j].tip_grupa==2)
                printf("medium\n");
            else printf("hard\n");

        }
        scanf ("%d", &clienti[i].grupa);
    }

}

int compara(const void *a, const void *b) // Functie folosita la ordonarea alfabetica
{
    int r;
    struct client *ia=(struct client *)a;
    struct client *ib=(struct client *)b;
    r= strcmp(ia->nume,ib->nume);
    return r;
}

void meniu(int operatie)
{


    int i,j,specializare,tip_ab;
    switch (operatie)
    {
    case 1:



        qsort( clienti,n+1, sizeof(struct client),compara);
        for (i=1; i<=n; i++)

            printf ("%s\n", clienti[i].nume);

        break;
    case 2:
        printf ("Introduceti specializarea pt care doriti sa afisati antrenorii: 1)light   2)medium   3)hard\n");
        scanf("%d", &specializare);
        if (specializare==1)
        {
            printf (" Sunt %d antrenori cu aceasta specializare \n",specializati1);
            for (i=1; i<=nra; i++)
                if (antrenori[i].specializare==specializare)
                    printf ("%s  %s\n", antrenori[i].nume_antrenor,antrenori[i].prenume_antrenor );
        }

        else if (specializare==2)
        {
            printf (" Sunt %d antrenori cu aceasta specializare \n",specializati2);
            for (i=1; i<=nra; i++)
                if (antrenori[i].specializare==specializare)
                    printf ("%s  %s\n", antrenori[i].nume_antrenor,antrenori[i].prenume_antrenor );
        }

        else
        {

            printf (" Sunt %d antrenori cu aceasta specializare: \n",specializati3);
            for (i=1; i<=nra; i++)
                if (antrenori[i].specializare==specializare)
                    printf ("%s  %s\n", antrenori[i].nume_antrenor,antrenori[i].prenume_antrenor );
        }
        break;

    case 3:
        printf ("Introduceti tipul de abonament pt care doriti sa afisati clientii: 1)light   2)medium   3)hard \n");
        scanf ("%d", &tip_ab);
        if (tip_ab==1)
            printf ("Numarul clientilor cu acest tip de abonament este : %d \n", ab1);
        else if (tip_ab==2)
            printf ("Numarul clientilor cu acest tip de abonament este : %d \n", ab2);
        else printf ("Numarul clientilor cu acest tip de abonament este : %d \n", ab3);
        break;
    case 4:
        for (i=1; i<=n; i++)
        {
            printf("Suma pe care trebuie sa o plateasca  %s %s este:  ", clienti[i].nume,clienti[i].prenume);
            for (j=1; j<=n; j++)
                if (abonamente[j].id_abonament==clienti[i].id_client)
                    printf("%d\n", abonamente[j].pret);
        }
    }
}
int main()
{
    p[0]=nr_antrenori_specializati;
    p[1]=calculeaza_pret_abonament;
    p[2]=calculeaza_pret_cartela;
    p[3]=reducere;
    p[4]=nr_abonamente;
    int operatie;

    printf ("Bine ati venit la sala de aerobic Stay Fit! \n");
    system ("pause");
    system ("cls");
    printf ("\n");

    introducere_grupe();
    system ("pause");
    system ("cls");

    introducere_antrenori();
    system ("pause");
    system ("cls");

    introducere_clienti();
    system ("pause");
    system("cls");

    int ok=1;
    while (ok)

    {
        printf("Apasati tasta corespunzatoare operatiei pe care doriti sa o efectuati:\n");
        printf ("1) Afisati clientii Stay Fit ordonati alfabetic dupa nume\n");
        printf ("2) Afisati antrenorii cu o anumita specializare\n");
        printf ("3) Afisati numarul clientilor cu un anumit tip de abonament\n");
        printf ("4) Afisati suma pe care trebuie sa o plateasca fiecare client\n");

        scanf ("%d",&operatie);
        meniu(operatie);
        printf("Doriti sa mai efectuati o operatie?\n ");
        printf ("1)Da  0)Nu\n");
        scanf("%d", &ok);
        system("cls");

    }
    return 0;
}
