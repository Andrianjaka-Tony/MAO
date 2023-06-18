#include "stdio.h"
#include "math.h"

double functionToIntegrate(float x);
double calculHauteur(int nbTrapeze, float a, float b);
double integraleApproximative(float a, float b, int nbTrapeze);
int lookForEpsilon(float a, float b);

int main() {
/// Données
	float a=0; 
	float b=1;

/// Problème
	printf("Calcul de l'integrale de %g a %g de e^sin(5x) par la methode de trapeze\n\n", a, b);

/// Traitements
	int nbTrapeze=lookForEpsilon(a, b);
	//float nbTrapeze=100;
	float resultat=integraleApproximative(a, b, nbTrapeze);

/// Resultat
	printf("L'integrale approchee de la fonction e^sin(5x) de %g a %g par la methode de trapeze est %g, ", a, b, resultat); 
	printf("\navec un nombre de hauteur de %i pour epsilon suffisament petit\n", nbTrapeze);

	return 0;
}

double functionToIntegrate(float x) {
	return exp(sin(5*x));
}

double calculHauteur(int nbTrapeze, float a, float b) {
	return(b-a)/nbTrapeze;
}

double integraleApproximative(float a, float b, int nbTrapeze) {
	double hauteur=calculHauteur(nbTrapeze, a, b);
	double fDeA=functionToIntegrate(a);
	double fDeB=functionToIntegrate(b);
	double somme=functionToIntegrate(a+1*hauteur);
	for(int i=2; i<nbTrapeze; i++) {
		somme=somme+functionToIntegrate(a+i*hauteur);
	}
	somme=somme*2;
	return (hauteur/2)*(fDeA+fDeB+somme);
}

int lookForEpsilon(float a, float b) {
	double epsilon=1;
	int nbTrapeze=1;
	while(epsilon>1E-8) {
		epsilon=integraleApproximative(a, b, nbTrapeze+1)-integraleApproximative(a, b, nbTrapeze);
		nbTrapeze++;
	}
	return nbTrapeze;
}
