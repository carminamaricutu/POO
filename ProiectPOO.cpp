//Maricutu Carmina Cristina
//INFO AN II Semigrupa 2.1
//Proiect POO


/*
	Enunt proiect:
	Sa se realizeze un program care tine evidenta persoanelor dintr-o
scoala(ex. Angajati:profesori/personal auxiliar, elevi:liceu/scoala generala).
Pentru implementare se va construi un meniu cu urmatoarele comenzi:
0.Iesire.
1.Citire categorie dorita.(elev/angajat)
2.Incarcare informatii angajati din fisier.
3.Afisare categorie dorita.(elev/angajat)
4.Afisarea tuturor persoanelor in ordine alfabetica.
5.Afisarea tuturor persoanelor in ordine crescatoare in functie de varsta.
6.Stergerea unei persoane din lista dupa nume + adaugare in fisier cu persoane sterse.
7.Modificare date pentru o persoana cautata dupa nume.
8.Salvarea listei finale intr-un fisier apoi iesire din aplicatie.

			   Structura claselor:

				   Persoane
			  /   		      \
		Angajat			      	 Elev
		/      \		       /      \
	Profesori	Personal	Gimnaziu	Liceu
		    	auxiliar	
*/


#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
using namespace std;

unsigned long int object_counter;// variabila globala care tine nr obiectelor introduse in lista.


void MENIU() {
	cout << "0.\tIesire.\n";
	cout << "1.\tCitire categorie dorita.(elev / angajat).\n";
	cout << "2.\tIncarcare informatii angajati din fisier.\n";
	cout << "3.\tAfisare categorie dorita.(elev / angajat).\n";
	cout << "4.\tAfisarea tuturor persoanelor in ordine alfabetica.\n";
	cout << "5.\tAfisarea tuturor persoanelor in ordine crescatoare in functie de varsta.\n";
	cout << "6.\tStergerea unei persoane din lista dupa nume+adaugare in fisier cu persoane sterse.\n";
	cout << "7.\tModificare date pentru o persoana cautata dupa nume.\n";
	cout << "8.\tSalvarea listei finale intr - un fisier apoi iesire din aplicatie.\n";
	cout << "Introduceti optiunea dorita:\t";
}


class MyException {//clasa exceptie
public:
	string str_what;
	int what;
	string swhat;
	
	MyException() { str_what = " "; what = 0; }
	MyException(string s, int c) {//pentru int
		str_what = s;
		what = c;
	}
	MyException(string s, string d) {//pentru string
		str_what = s;
		swhat = d;
	}
};

class Lista;//prototip pentru clasa Lista

class PERSOANA { //clasa de baza
	int Tip_derivat1;
	string Nume, Prenume;
	int Varsta;
	PERSOANA *next;
public:
	PERSOANA(int tip1, string nume, string prenume, unsigned int varsta) {//Constructor
		Tip_derivat1 = tip1;
		Nume = nume;
		Prenume = prenume;
		Varsta = varsta;
		next = NULL;
	}
	virtual void afisare() {//functie firtuala pentru afisare
		cout << "_____________________________________" << endl;
		cout << "NUMELE:" << Nume << endl;
		cout << "PRENUME:" << Prenume << endl;
		cout << "VARSTA:" << Varsta << endl;

	}
	PERSOANA&operator=(const PERSOANA& sursa) {//supraincarcarea operatorului "="
		if (this != &sursa) {
			Nume = sursa.Nume;
			Prenume = sursa.Prenume;
			Varsta = sursa.Varsta;
			Tip_derivat1 = sursa.Tip_derivat1;
			next = sursa.next;
		}
		return *this;
	}
	friend class Lista;
};

class ANGAJAT :public PERSOANA {//clasa angajat:mosteneste public clasa persoana
	int Tip_derivat2;
	int Vechime, Salar;
public:
	ANGAJAT(int tip1, string nume, string prenume, unsigned int varsta, int tip2, 
		int vech, int sal) :PERSOANA(tip1, nume, prenume, varsta) {
		Tip_derivat2 = tip2;
		Vechime = vech;
		Salar = sal;
	}
	void afisare() {
		PERSOANA::afisare();
		cout << "VECHIME:" << Vechime << endl;
		cout << "SALAR:" << Salar << endl;
	}
	int getT2() { return Tip_derivat2; }
	friend class Lista;	
};

class PROFESOR :public ANGAJAT {//clasa profesor: mosteneste public clasa angajat
	string Disciplina;
	string Grad_profesoral;
public:
	PROFESOR(int tip1, string nume, string prenume, unsigned int varsta, int tip2,
		int vech, int sal, string disciplina, string grad) :ANGAJAT(tip1, nume, prenume, varsta, tip2, vech, sal) {
		Disciplina = disciplina;
		Grad_profesoral = grad;
	}
	void afisare() {
		ANGAJAT::afisare();
		cout << "DISCIPLINA:" << Disciplina << endl;
		cout << "GRAD PROFESORAL:" << Grad_profesoral << endl;
		cout << endl;
	}
	friend class Lista;
};

class P_AUXILIAR :public ANGAJAT {//clasa p_auxiliar(Personal auxiliar): mosteneste public clasa angajat
	string Functia;
	int Nr_legitimatie;
public:
	P_AUXILIAR(int tip1, string nume, string prenume, unsigned int varsta, int tip2,
		int vech, int sal, string functia, int nr_legit) :ANGAJAT(tip1, nume, prenume, varsta, tip2, vech, sal) {
		Functia = functia;
		Nr_legitimatie = nr_legit;
	}
	void afisare() {
		ANGAJAT::afisare();
		cout << "FUNCTIA:" << Functia << endl;
		cout << "NUMAR LEGITIMATIE:" << Nr_legitimatie << endl;
		cout << endl;
	}
	friend class Lista;
};


class ELEV :public PERSOANA {//clasa elev: mosteneste public clasa persoana
	int Tip_derivat3;
	int Bursier;
	string Sectia;
public:
	ELEV(int tip1, string nume, string prenume, unsigned int varsta, int tip3,
		int bursa, string sect) :PERSOANA(tip1, nume, prenume, varsta) {
		Tip_derivat3 = tip3;
		Bursier=bursa;
		Sectia = sect;
	}
	void afisare() {
	PERSOANA::afisare();
	if (Bursier)
		cout << "BURSA: DA" << endl;
	else
		cout << "BURSA: NU" << endl;
	cout << "SECTIA:" << Sectia << endl;
	}
	int getT3() { return Tip_derivat3; }
	friend class Lista;
};

class GIMNAZIU :public ELEV {//clasa gimnaziu: mosteneste public clasa elev
	int Clasa;
	int Nr_matricol;
public:
	GIMNAZIU(int tip1, string nume, string prenume, unsigned int varsta, int tip3,
		int bursa, string sect, int cls, int nr_mat) :ELEV(tip1, nume, prenume, varsta, tip3, bursa, sect) {
		Clasa = cls;
		Nr_matricol = nr_mat;
	}
	void afisare() {
		ELEV::afisare();
		cout << "CLASA:" << Clasa << endl;
		cout << "NUMAR MATRICOL:" << Nr_matricol << endl;
		cout << endl;

	}
	friend class Lista;
};


class LICEU :public ELEV {//clasa liceu: mosteneste public clasa elev
	int Clasa;
	int Nr_matricol;
public:
	LICEU(int tip1, string nume, string prenume, unsigned int varsta, int tip3,
		int bursa, string sect, int cls, int nr_mat) :ELEV(tip1, nume, prenume, varsta, tip3, bursa, sect) {
		Clasa = cls;
		Nr_matricol = nr_mat;
	}
	void afisare() {
		ELEV::afisare();
		cout << "CLASA:" << Clasa << endl;
		cout << "NUMAR MATRICOL:" << Nr_matricol << endl;
		cout << endl;
	}
	friend class Lista;
};

class Lista {//clasa Lista
public:
	PERSOANA *head;//Capul listei
	//functii care opereaza asupra clasei lista
	void adaugare(PERSOANA *a);
	void afisare_lista();
	void afisare_lista_(int all, int x, int y);
	void cautare_lista_UPDATE(string nume_cautat,string prenume_de_cautat);
	void sterge_din_lista(string nume_de_sters, string prenume_de_sters);
	void salvare_lista_in_fisier();
	void scrie_in_fisier(PERSOANA *z, string nume_fisier);
	PERSOANA *sortare_varsta();

};


PERSOANA* Lista::sortare_varsta()//functie care sorteaza elementele listei in functie de varsta
{
	int num_nodes = object_counter;
	int counter;

	for (counter = 0; counter < num_nodes; counter++) {
		PERSOANA*current = head;
		PERSOANA*next_n = current->next;
		PERSOANA*previous = NULL;
		
		while (next_n != NULL) {//atata timp cat nodul urmator nu este null

			if (current->Varsta > next_n->Varsta) {//daca inf din nodul precedent este  
												   //mai mare decat cea din nodul urmator
				//se vor face interschimbarile intre noduri
				if (current == head) {
					head = next_n;
				}
				else {
					previous->next = next_n;
				}
				current->next = next_n->next;
				next_n->next = current;

				previous = next_n;
				next_n = current->next;
			}
			else {
				previous = current;
				current = current->next;
				next_n = current->next;
			}
		}
	}
	return head;
}

bool validateString(const std::string& s)//funtie booleana care valideaza un string(poate contine doar litere mari sau mici).
{
	for (const char c : s) {
		if (!isalpha(c))
			return false;
	}

	return true;
}

class Supraincarcare {//clasa supraincarcare
	string Nume, Prenume;
	int Varsta;
public:
	friend ostream&operator<<(ostream&out, Supraincarcare &a);
	friend istream&operator>>(istream&in, Supraincarcare&a);
	string getNume() { return Nume; }
	string getPrenume() { return Prenume; }
	int getVarsta() { return Varsta; }
};

ostream &operator<<(ostream&out, Supraincarcare &a) {//supraincarcarea operatorului "<<"
	cout << "Se citesc datele generale pentru persoana.\n";
	cout << endl;
	return out;
}


istream &operator>>(istream&in, Supraincarcare &a) {//supraincarcarea operatorului ">>"
	cin.get();
	int ok=1;

	do {//tratarea exceptiilor(in caz in care utilizatorul introduce alte caractere decat litere in nume
		try {
			cout << "Introduceti nume:"; getline(cin, a.Nume);
			if (!validateString(a.Nume)) {
				ok = 0;
				throw MyException("\n\tNUMELE NU POATE CONTINE CARACTERE SAU NUMERE!\n\n", a.Nume);
			}
			else ok = 1;
		}
		catch (MyException&nrins) {
			cout << nrins.str_what << "ERROR:";
			cout << nrins.swhat << endl;
		}
	} while (!ok);

	do {//tratarea exceptiilor(in caz in care utilizatorul introduce alte caractere decat litere in prenume
		try {
			cout << "Introduceti prenume:"; getline(cin, a.Prenume);
			if (!validateString(a.Prenume)) {
				ok = 0;
				throw MyException("\n\tPRENUMELE NU POATE CONTINE CARACTERE SAU NUMERE!\n\n", a.Prenume);
			}
			else ok = 1;
		}
		catch (MyException&nrins) {
			cout << nrins.str_what << "ERROR:";
			cout << nrins.swhat << endl;
		}
	} while (!ok);

	do {//tratarea exceptiilor(in caz in care utilizatorul introduce un numar negativ pentru varsta
		try {
			cout << "Introduceti varsta:"; cin >> a.Varsta;
			if (a.Varsta <= 0)
				throw MyException("NR PREA MIC", a.Varsta);
		}
		catch (MyException&e) {
			cout << e.str_what << endl;
			cout << e.what << endl;
		}
	} while (a.Varsta <= 0);
	return in;
}




void Lista::adaugare(PERSOANA *a) {//adaugare ordonata alfabetic dupa nume
	PERSOANA *p;
	p = head;
	if (p) {
		if (a->Nume < p->Nume) {
			a->next = head;
			head = a;
		}
		else
		{
			while (p->next &&p->next->Nume < a->Nume)
				p = p->next;
			a->next = p->next;
			p->next= a;
		}
	}
	else
		head = a;
	object_counter++;
}

void Lista::scrie_in_fisier(PERSOANA *p, string nume_fisier) {//functie care scrie in fisier datele 
															  //din obiectul pasat ca argument in fisierul
															  //al carui nume a fost dat ca argument
	ofstream fisier_output;
	fisier_output.open(nume_fisier, ios::app);
	if (p) {
		if (fisier_output.is_open()) {
			fisier_output << "NUME: " << p->Nume << endl;;
			fisier_output << "PRENUME: " << p->Prenume << endl;
			fisier_output << "VARSTA: " << p->Varsta << endl;
			if (p->Tip_derivat1 == 0) {
				ANGAJAT *x;
				x = (ANGAJAT*)p;
				fisier_output << "VECHIME: " << x->Vechime << endl;
				fisier_output << "SALAR: " << x->Salar << endl;
				if (x->Tip_derivat2 == 0)
				{
					PROFESOR *prof;
					prof = (PROFESOR*)x;
					fisier_output << "DISCIPLINA: " << prof->Disciplina << endl;
					fisier_output << "GRAD PROFESORAL: " << prof->Grad_profesoral << endl << endl;
				}
				else if (x->Tip_derivat2 == 1)
				{
					P_AUXILIAR *auxiliar;
					auxiliar = (P_AUXILIAR*)x;
					fisier_output << "FUNCTIE: " << auxiliar->Functia << endl;
					fisier_output << "NUMAR LEGITIMATIE: " << auxiliar->Nr_legitimatie << endl << endl;
				}
			}
			else
			{
				ELEV *y;
				y = (ELEV*)p;
				fisier_output << "BURSIER:(1-DA / 0-NU) " << y->Bursier << endl;
				fisier_output << "SECTIA: " << y->Sectia << endl;
				if (y->Tip_derivat3 == 0) {
					GIMNAZIU *gim;
					gim = (GIMNAZIU*)y;
					fisier_output << "CLASA: " << gim->Clasa << endl;
					fisier_output << "NUMAR MATRICOL: " << gim->Nr_matricol << endl << endl;
				}
				else if (y->Tip_derivat3 == 1) {
					LICEU *liceu;
					liceu = (LICEU*)y;
					fisier_output << "CLASA: " << liceu->Clasa << endl;
					fisier_output << "NUMAR MATRICOL: " << liceu->Nr_matricol << endl << endl;
				}

			}
		}

	}
}


void Lista::sterge_din_lista(string nume_de_sters, string prenume_de_sters) {
	//functie care sterge din lista un obiect in functie de nume si prenume dar inainte de aceasta salveaza 
	//datele obiectului intr-un fisier
	ofstream fis_S;
	fis_S.open("STERSE.txt", ios::app);
	PERSOANA *a, *p, *q;
	a = head;
	if (!a)
		cout << "Lista este vida. Nu este nimic de sters.";
	else {
		if (a->Nume == nume_de_sters && a->Prenume == prenume_de_sters) {
			p = a;
			scrie_in_fisier(p, "STERSE.txt");
			a = a->next;
			delete(p);
			head = a;
		}
		else {
			q = a;
			while (q->next != NULL && q->next->Nume != nume_de_sters && q->next->Prenume != prenume_de_sters)
				q = q->next;
			if (q->next->Nume == nume_de_sters && q->next->Prenume == prenume_de_sters) {
				p = q->next;
				scrie_in_fisier(p, "STERSE.txt");
				q->next = q->next->next;
				delete(p);
			}
			
		}
	}
}

void Lista::salvare_lista_in_fisier() {//functie care salveaza lista curenta intr-un fisier
	ofstream fis_FINAL;
	fis_FINAL.open("FINAL.txt", ios::app);
	PERSOANA *p;
	p = head;
	if (!p)
		cout << "Lista este vida!";
	else
	{
		while (p) {
			if (fis_FINAL.is_open()) {
				Lista::scrie_in_fisier(p, "FINAL.txt");
				p = p->next;
			}
			else
			{
				cout << "\n\tFISIERUL NU A PUTUT FI DESCHIS PENTRU OPERATIA SOLICITATA.\n\n";
				return;
			}
		}
	}
}


void Lista::afisare_lista() {//functie pentru afisarea listei
	PERSOANA *a;
	a = head;
	if (!a)
		cout << "Lista este vida!\n";
	else
		while (a) {
			a->afisare();
			a = a->next;
		}
}

void Lista::cautare_lista_UPDATE(string nume_cautat, string prenume_cautat) {
	//finctie care rescrie datele unei persoane cautata dupa nume si prenume
	PERSOANA *a;
	a = head;
	int ok=0;
	if(!a)
		cout << "Lista este vida!\n";
	else
		while (a)
		{
			if (a->Nume == nume_cautat && a->Prenume == prenume_cautat)
			{
				cout << "INTRODUCETI NOILE DATE ALE PERSOANEI:\n";

				do {//tratarea exceptiilor: validare nume
					try {
						cout << "UPDATE NUME:"; getline(cin, a->Nume);
						if (!validateString(a->Nume)) {
							ok = 0;
							throw MyException("\n\tNUMELE NU POATE CONTINE CARACTERE SAU NUMERE!\n\n", a->Nume);
						}
						else ok = 1;
					}
					catch (MyException&nrins) {
						cout << nrins.str_what << "ERROR:";
						cout << nrins.swhat << endl;
					}
				} while (!ok);
				
				do {//tratarea exceptiilor: validare prenume
					try {
						cout << "UPDATE PRENUME:"; getline(cin, a->Prenume);
						if (!validateString(a->Prenume)) {
							ok = 0;
							throw MyException("\n\tNUMELE NU POATE CONTINE CARACTERE SAU NUMERE!\n\n", a->Prenume);
						}
						else ok = 1;
					}
					catch (MyException&nrins) {
						cout << nrins.str_what << "ERROR:";
						cout << nrins.swhat << endl;
					}
				} while (!ok);
				
				do {//tratarea exceptiilor: validare varsta
					try {
						cout << "UPDATE VARSTA:";
						cin >> a->Varsta;
						if (a->Varsta < 5)
							throw MyException("\n\tVARSTA NU POATE FI MAI MICA SAU EGALA CU 5(cinci)!\n\n", a->Varsta);
					}
					catch (MyException e) {
						cout << e.str_what << "ERROR:";
						cout << e.what << endl;
					}
				} while (a->Varsta <=5);
				cout << "UPDATE TIP: (0-ANGAJAT/1-ELEV)";
				cin >> a->Tip_derivat1;
				if (a->Tip_derivat1 == 0) {
					ANGAJAT *x;
					x = (ANGAJAT*)a;
					cout << "UPDATE VECHIME ANGAJAT:";
					cin >> x->Vechime;

					do {
						try {
							cout << "UPDATE SALAR ANGAJAT:"; cin >> x->Salar;
							if (x->Salar <= 0)
								throw MyException("\n\tVALOAREA NU POATE FI MAI MICA SAU EGALA CU 0(zero)!\n\n", x->Salar);
						}
						catch (MyException e) {
							cout << e.str_what << "ERROR:";
							cout << e.what << endl;
						}
					} while (x->Salar <= 0);
					cout << "UPDATE TIP ANGAJAT:(0-PROFESOR/1-PERSONAL AUXILIAR)";
					cin >> x->Tip_derivat2;
					if (x->Tip_derivat2 == 0) {
						PROFESOR *m;
						m = (PROFESOR*)x;
						cout << "UPDATE DISCIPLINA PREDATA:";
						getline(cin, m->Disciplina);
						cout << "UPDATE GRAD PROFESORAL";
						cin >> m->Grad_profesoral;
					}
					else if (x->Tip_derivat2 == 1) {
							cin.get();
							P_AUXILIAR *n;
							n = (P_AUXILIAR*)x;
							cout << "UPDATE FUNCTIE:";
							getline(cin, n->Functia);
							cout << "UPDATE NUMAR LEGITIMATIE:";

							do {//tratarea exceptiilor: validare numar legitimatie
								try {
									cin >> n->Nr_legitimatie;
									if (n->Nr_legitimatie <= 0)
										throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", n->Nr_legitimatie);
								}
								catch (MyException e) {
									cout << e.str_what << "ERROR:";
									cout << e.what << endl;
								}
							} while (n->Nr_legitimatie <= 0);
					}
				
				}
				else if (a->Tip_derivat1 == 1) {
					ELEV *y;
					y = (ELEV*)a;
					cout << "UPDATE SECTIE:";
					cin >> y->Sectia;
					cout << "UPDATE BURSIER:(1-DA/0-NU)";
					cin >> y->Bursier;
					cout << "UPDATE TIP ELEV:(0-GIMNAZIU/1-LICEU)";
					cin >> y->Tip_derivat3;
					if (y->Tip_derivat3 == 0) {
						GIMNAZIU *d;
						d= (GIMNAZIU*)y;

						do {//tratarea exceptiilor: validare clasa
							try {
								cout << "UPDATE CLASA:"; cin >> d->Clasa;
								if (d->Clasa < 0)
									throw MyException("\n\tCLASA NU POATE FI MAI MICA DECAT 0(zero)!\n\n", d->Clasa);
							}
							catch (MyException e) {
								cout << e.str_what << "ERROR:";
								cout << e.what << endl;
							}
						} while (d->Clasa< 0);

						do {//tratarea exceptiilor: validare numar matricol
							try {
								cout << "UPDATE CLASA:"; cin >> d->Nr_matricol;
								if (d->Nr_matricol <= 0)
									throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", d->Nr_matricol);
							}
							catch (MyException e) {
								cout << e.str_what << "ERROR:";
								cout << e.what << endl;
							}
						} while (d->Nr_matricol <= 0);
					}
					else if (y->Tip_derivat3 == 1) {
						LICEU *f;
						f = (LICEU*)y;

						do {//tratarea exceptiilor: validare clasa
							try {
								cout << "Introduceti clasa:"; cin >> f->Clasa;
								if (f->Clasa < 0)
									throw MyException("\n\tCLASA NU POATE FI MAI MICA DECAT 0(zero)!\n\n", f->Clasa);
							}
							catch (MyException e) {
								cout << e.str_what << "ERROR:";
								cout << e.what << endl;
							}
						} while (f->Clasa< 0);

						do {//tratarea exceptiilor: validare numar matricol
							try {
								cout << "Introduceti numarul matricol:"; cin >> f->Nr_matricol;
								if (f->Nr_matricol <= 0)
									throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", f->Nr_matricol);
							}
							catch (MyException e) {
								cout << e.str_what << "ERROR:";
								cout << e.what << endl;
							}
						} while (f->Nr_matricol <= 0);
					}

				}
				cout << "UPDATE PERSOANA:\n";
				a->afisare();
				return;
			}
			else
			{
				a = a->next;
			}
		}
}

void Lista::afisare_lista_(int all, int x, int y) {
	//afisare obiecte din lista in functie de categoria dorita
	PERSOANA *p;
	ANGAJAT *a;
	ELEV *e;
	p = head;
	if (!p) {
		cout << "Lista este vida!\n";
		return;
	}else
	if (p&&all) {
		afisare_lista();
	}
	else
	{
		while (p) {
			if (p->Tip_derivat1 == x) {
				if (x == 0) {
					a = (ANGAJAT*)p;
					if (a->getT2() == y)
					{
						p->afisare();
						p = p->next;
					}
					else
						p = p->next;
				}
				else if (x == 1)
				{
					e = (ELEV*)p;
					if (e->getT3() == y) {
						p->afisare();
						p = p->next;
					}
					else
						p = p->next;
				}
			}
			else
				p = p->next;
		}
	}
	
		
}

void introducere(Lista &l, int x, int y) {//introducere manuala a obiectelor in lista
	string nume, prenume;
	int varsta;
	int vechime, salar;
	int bursier;
	string sectia;
	string disciplina, grad;
	string functie;
	int nr_legitimatie;
	int clasa_g, nr_mat_g;
	int clasa_l, nr_mat_l;
	PERSOANA *pers;
	Supraincarcare supr;
	cout << supr;
	cin >> supr;
	if (x == 0) {
		ANGAJAT *angajati;
		cout << "Introduceti vechime:"; cin >> vechime;

		do {//tratarea exceptiilor: validare numar ani vechime
			try {
				cout << "Introduceti salar:"; cin >> salar;
					if (salar <= 0)
						throw MyException("\n\tVALOAREA NU POATE FI MAI MICA SAU EGALA CU 0(zero)!\n\n", salar);
			}
			catch (MyException e) {
				cout << e.str_what << "ERROR:";
				cout << e.what << endl;
			}
		} while (salar <=0);
		
		cin.get();
		angajati = new ANGAJAT(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y, vechime, salar);
		if (y == 0) {
			PROFESOR *prof;
			cout << "Introduceti disciplina predata:";
			getline(cin, disciplina);
			cout << "Introduceti gradul profesoral:";
			getline(cin, grad);
			prof = new PROFESOR(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y, vechime, salar, disciplina, grad);
			pers = prof;
			l.adaugare(pers);
		}
		else if (y == 1)
		{
			P_AUXILIAR *auxiliar;
			cout << "Introduceti functia:";
			getline(cin, functie);

			do {//tratarea exceptiilor: validare numar legitimatie
				try {
					cout << "Introduceti numarul legitimatiei:"; cin >> nr_legitimatie;
					if (nr_legitimatie <= 0)
						throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", nr_legitimatie);
				}
				catch (MyException e) {
					cout << e.str_what << "ERROR:";
					cout << e.what << endl;
				}
			} while (nr_legitimatie <= 0);
			cin.get();
			auxiliar = new P_AUXILIAR(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y,vechime, salar, functie, nr_legitimatie);
			pers = auxiliar;
			l.adaugare(pers);
		}
	}
	else if (x == 1) {
		ELEV *elevi;
		cout << "Elevul este bursier?(1-DA/0-NU):";
		cin >> bursier;
		cin.get();
		cout << "Sectia:";
		getline(cin, sectia);
		elevi = new ELEV(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y, bursier, sectia);
		if (y == 0) {
			GIMNAZIU *gimnaziu;

			do {//tratarea exceptiilor: validare clasa
				try {
					cout << "Introduceti clasa:"; cin >> clasa_g;
					if (clasa_g < 0)
						throw MyException("\n\tCLASA NU POATE FI MAI MICA DECAT 0(zero)!\n\n", clasa_g);
				}
				catch (MyException e) {
					cout << e.str_what << "ERROR:";
					cout << e.what << endl;
				}
			} while (clasa_g < 0);

			do {//tratarea exceptiilor: validare numar matricol
				try {
					cout << "Introduceti numarul matricol:"; cin >> nr_mat_g;
					if (nr_mat_g <= 0)
						throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", nr_mat_g);
				}
				catch (MyException e) {
					cout << e.str_what << "ERROR:";
					cout << e.what << endl;
				}
			} while (nr_mat_g <= 0);
			gimnaziu = new GIMNAZIU(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y, bursier, sectia, clasa_g, nr_mat_g);
			pers = gimnaziu;
			l.adaugare(pers);
		}
		else if (y == 1)
		{
			LICEU *liceu;

			do {//tratarea exceptiilor: validare clasa
				try {
					cout << "Introduceti clasa:"; cin >> clasa_l;
					if (clasa_l <= 0)
						throw MyException("\n\tCLASA NU POATE FI MAI MICA decat 9(noua)!\n\n", clasa_l);
				}
				catch (MyException e) {
					cout << e.str_what << "ERROR:";
					cout << e.what << endl;
				}
			} while (clasa_l <= 0);

			do {//tratarea exceptiilor: validare numar matricol
				try {
					cout << "Introduceti numarul matricol:"; cin >> nr_mat_l;
					if (nr_mat_l <= 0)
						throw MyException("\n\tNUMARUL NU POATE FI MAI MIC SAU EGAL CU 0(zero)!\n\n", nr_mat_l);
				}
				catch (MyException e) {
					cout << e.str_what << "ERROR:";
					cout << e.what << endl;
				}
			} while (nr_mat_l <= 0);
			liceu = new LICEU(x, supr.getNume(), supr.getPrenume(), supr.getVarsta(), y, bursier, sectia, clasa_l, nr_mat_l);
			pers = liceu;
			l.adaugare(pers);
		}
	}
}
//

void incarcare_angajati_fisier(Lista &l) {
	//incarcare automata a obiectelor din fisier in lista
	//aici nu am mai folosit functiile de tratare a exceptilor. Am presupus ca datele sunt corecte.
	int t1, t2;
	string nume, prenume;
	int varsta, vechime, salar;
	string disciplina, grad;
	string functie;
	int nr_legitimatie;
	PERSOANA *pers;
	ifstream angajati;
	angajati.open("Angajati.txt");
	if (angajati.is_open()) {
		while (!angajati.eof()) {
			angajati >> nume;
			angajati >> prenume;
			angajati >> varsta;
			angajati >> t1;
				if (t1 == 0) {
					angajati >> vechime;
					angajati >> salar;
					angajati >> t2;
					if (t2 == 0) {
						angajati >> disciplina;
						angajati >> grad;
						PROFESOR *prof;
						prof = new PROFESOR(t1, nume, prenume, varsta, t2, vechime, salar, disciplina, grad);
						pers = prof;
						l.adaugare(pers);
					}
					else if (t2 == 1)
					{
						angajati >> functie;
						angajati >> nr_legitimatie;
						P_AUXILIAR *aux;
						aux = new P_AUXILIAR(t1, nume, prenume, varsta, t2, vechime, salar, functie, nr_legitimatie);
						pers = aux;
						l.adaugare(pers);
					}
				}
		}
		angajati.close();
	}
	else {
		cout << "Fisierul nu a putut fi deschis pentru operatia solicitata.\n";
		angajati.close();
	}
	
}

int main(){
	int opt, user_input;
	int x, y, all;
	string nume_cautat, prenume_cautat;
	Lista L;
	L.head = NULL;
	do
	{
		MENIU();
		cin >> opt;
		switch (opt)
		{
		case 0:exit(0); break;
		case 1:cout << "\n\tCITIRE PERSOANA NOUA:\n\n";
			cout << "PENTRU ANGAJAT APASATI '0'.\nPENTRU ELEV APASATI '1':\t";
			cin >> x;
			cin.get();
			if (x == 0)
			{
				cout << "PENTRU PROFESOR APASATI '0'.\nPENTRU PERSONAL AUXILIAR APASATI '1':\t";
				cin >> y;
			//	cin.get();
			}
			else if (x == 1) {
				cout << "PENTRU ELEV GIMNAZIU APASATI '0'.\nPENTRU ELEV LICEU APASATI '1':\t";
				cin >> y;
				//cin.get();
			}
			introducere(L, x, y);
		break;
		case 2: incarcare_angajati_fisier(L);
		break;
		case 3:
			cout << "DORITI AFISAREA TUTUROR PERSOANELOR?1-DA/0-NU\n";
			cin >> all;
			if (all == 1)
			{
				x = 0; y = 0;
			}
			else {
				cout << "DACA DORITI AFISAREA ANGAJATILOR-0/ELEVILOR-1.\n";
				cin >> x;
				if (x == 0)
				{
					cout << "DACA DORITI AFISAREA PROFESORILOR-0/PERSONAL AUXILIAR-1.\n";
					cin >> y;
				}
				else if (x==1)
				{
					cout << "DACA DORITI AFISAREA ELEVILOR DE GIMNAZIU-0/LICEU-1.\n";
					cin >> y;
				}				
			}
			L.afisare_lista_(all, x, y); 
		break;
		case 4:L.afisare_lista();
		break;
		case 5: {
			L.sortare_varsta();
			L.afisare_lista();
		}
		break;
		case 6: {cin.get();
			cout << "Introduceti numele cautat:";
			getline(cin, nume_cautat);
			cout << "Introduceti prenumele cautat:";
			getline(cin, prenume_cautat);
			L.sterge_din_lista(nume_cautat, prenume_cautat);
		}
		break;
		case 7: {cin.get();
			cout << "Introduceti numele cautat pentru modificare date:";
			getline(cin, nume_cautat);
			cout << "Introduceti prenumele cautat pentru modificare date:";
			getline(cin, prenume_cautat);
			L.cautare_lista_UPDATE(nume_cautat, prenume_cautat); 
		}
		break;
		case 8: 
			L.salvare_lista_in_fisier();
			exit(0);
		break;
		default:printf("\n\n\tOPTIUNEA INTRODUSA NU EXISTA!\n\n");
		break;
		}
	} while (opt!=0);

	system("pause");
	return 0;
}