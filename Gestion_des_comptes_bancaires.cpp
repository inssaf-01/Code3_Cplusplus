#include <iostream>
using namespace std;

class CompteBancaire
{
protected:
	string numero;
	double solde;

public:
	// constructeurs
	CompteBancaire()
	{
		numero = "a00";
		solde = 0;
	}
	CompteBancaire(string n, double s)
	{
		numero = n;
		solde = s;
	}
	CompteBancaire(CompteBancaire &c)
	{
		numero = c.numero;
		solde = c.solde;
	}
	// getter de solde
	double get_solde() { return solde; }
	// getter de numero
	string get_numero() { return numero; }
	// setter de solde
	void set_solde(double s)
	{
		solde = s;
	}
	// methode deposer
	void deposer(double montant)
	{
		solde += montant;
	}
	// methode retirer
	void retirer(double montant)
	{
		solde -= montant;
	}
	// methode afficher
	virtual void afficher()
	{
		cout << "Numero : " << numero <<" | ";
		cout << "Solde  : " << solde ;
	}
};

class CompteCourant : public virtual CompteBancaire
{

protected:
	double decouvertAutorise;

public:
	// les constructeurs
	CompteCourant() : CompteBancaire() { decouvertAutorise = 0; }
	CompteCourant(string n, double s, double d) : CompteBancaire(n, s)
	{
		decouvertAutorise = d;
	}
	CompteCourant(CompteCourant &c) : CompteBancaire(c)
	{
		decouvertAutorise = c.decouvertAutorise;
	}
	// methode retirer
	void retirer(double montant)
	{

		double s = CompteBancaire::get_solde();
		if (montant <= (s + decouvertAutorise)) //. Le maximum qu?on peut retirer est solde + decouvert autorise.
			s -= montant;
		CompteBancaire::set_solde(s);
	}

	virtual void afficher()
	{
		CompteBancaire::afficher();
		cout << " | Decouvert Autorise : " << decouvertAutorise ;
	}
};
class CompteEpargne : public virtual CompteBancaire
{
protected:
	double tauxInteret;

public:
	// les constructeurs
	CompteEpargne() : CompteBancaire() { tauxInteret = 0; }
	CompteEpargne(string n, double s, double t) : CompteBancaire(n, s)
	{
		tauxInteret = t;
	}
	CompteEpargne(CompteEpargne &c) : CompteBancaire(c)
	{
		tauxInteret = c.tauxInteret;
	}
	// methode deposer
	void deposer(double montant)
	{
		solde = solde + montant * (1 + tauxInteret);
	}
	// methode afficher
	virtual void afficher()
	{
		CompteBancaire::afficher();
		cout << " | Taux d'interet : " << tauxInteret ;
	}
};
class CompteCourantEpargne : public CompteCourant, public CompteEpargne
{

public:
	// les constructeurs
	CompteCourantEpargne() : CompteCourant(), CompteEpargne() {}
	CompteCourantEpargne(string n, double s, double d, double t) : CompteBancaire(n, s), CompteCourant(n, s, d), CompteEpargne(n, s, t) {}
	CompteCourantEpargne(CompteCourantEpargne &c) : CompteCourant(c), CompteEpargne(c) {}
	// methode deposer
	void deposer(double montant)
	{
		double s = CompteBancaire::get_solde();
		s += montant * (1 + tauxInteret);
		CompteBancaire::set_solde(s);
	}
	// methode retirer
	void retirer(double montant)
	{
		CompteEpargne::retirer(montant);
	}
	// methode d'affichage
	virtual void afficher()

	{
		CompteEpargne::afficher();
		cout << " | decouvert autorise : " << decouvertAutorise << endl;
	}
};
class Banque
{
	CompteBancaire *comptesBancaires[10];
	int N;

public:
	// constructeurs
	Banque()
	{
		N = 0;
	}
	// fct de recherche qui retoune la position de l'element du tableau
	int position(string num)
	{   int x=-1;
		for (int i = 0; i < N; i++)
		{
				if (comptesBancaires[i]->get_numero() == num)
				x=i;
		}
		return x;
	}
	// fc d'ajout
	void ajouterCompte(CompteBancaire *compte)
	{
		comptesBancaires[N] = compte;
		N++;
	}
	// fct de suppression
	void supprimerCompte(string numero)
	{   
		int x = position(numero);
		if (x==-1)
		cout<<"Le compte "<<numero<<" n'existe pas "<<endl;
		else {
		
		for (int i = x; i < N-1 ; i++) // on va stocker la position dans la var x
		{    
			comptesBancaires[i] = comptesBancaires[i + 1];
			
		}
		N--;
		}
	}
	// fct d'affichage
	void afficherComptes()
	{   if (N>0)
     	{
	
		for (int i = 0; i < N; i++)
		{   cout<<" compte num : "<<i+1<<" : " ;
			comptesBancaires[i]->afficher();
			cout<<endl;
		}
		}
		else  cout<<"Vous devez creer au moins un compte "<<endl;
	}
	// fct de calcul de total des soldes
	double getTotalSoldes()
	{
		double s = 0;//var dont on va stocker le total 
		for (int i = 0; i < N; i++)
		{
			s += comptesBancaires[i]->get_solde();
		}
		return s;
	}
	//depot et retrait 
	void deposer_b(string num,double m)
	{  
		int x=position(num);
		 if (x==-1)
			cout<<"Le compte "<<num<<" n'existe pas "<<endl;
		else comptesBancaires[x]->deposer(m);
		
	}
	void retirer_b(string num,double m)
	{
		 int x=position(num);
		  if (x==-1)
		cout<<"Le compte "<<num<<" n'existe pas "<<endl;
		else comptesBancaires[x]->retirer(m);
	}
};

main()
{ // les tests
    double total;
    //test sur compte bancaire 
    CompteBancaire *cb1 = new CompteBancaire("CB1", 1000);
	// test sur compte courant
	CompteCourant *cc1 = new CompteCourant("CC1", 2000, 400);
	CompteCourant *cc2 = new CompteCourant("CC2", 3000, 500);
	// Test sur compte epargne:
	CompteEpargne *ce1 = new CompteEpargne("CE1", 4000, 0.2);
	CompteEpargne *ce2 = new CompteEpargne("CE2", 5000, 0.3);
	// test sur CompteCourantEpargne
	CompteCourantEpargne *cce1 = new CompteCourantEpargne("CCE", 6000, 400, 0.1);
	Banque b = Banque();
	b.afficherComptes();
	//ajout des compte a la classe banque
	b.ajouterCompte(cb1);
	b.ajouterCompte(cc1);
	b.ajouterCompte(cc2);
	b.ajouterCompte(ce1);
	b.ajouterCompte(ce2);
	b.ajouterCompte(cce1);
	//test d'affichage 
	b.afficherComptes();
	total = b.getTotalSoldes();
	cout<<"Le total des soldes est : "<<total<<endl<<endl;
	//depot et retrait de l'argent des comptes 
    b.retirer_b("CC1",500);
    b.retirer_b("CE2",500);
    b.deposer_b("CE1",1000);
    b.retirer_b("abc",120);
	//test d'affichage 
	cout<<"Affichage apres retrait de 500 DH pour CC1 et CE2 / depot de 1000 DH pour CE1"<<endl;
	b.afficherComptes();
	total = b.getTotalSoldes();
	cout<<"Le total des soldes est : "<<total<<endl<<endl;
	//test sur suppression 
	b.supprimerCompte("CC2");
	b.supprimerCompte("CE1");
	//affichage apres suppression
	cout<<"Affichage apres suppression de CE1 et CC2 "<<endl;
	b.afficherComptes();
	//test du total des soldes
    total = b.getTotalSoldes();
	cout<<" Le total des soldes est : "<<total;
	
}

