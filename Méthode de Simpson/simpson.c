#include "stdio.h"
#include "math.h"

double functionToIntegrate(float x);
void displayResult(float a, float b, float epsilon, double resultat, float nbDiscret);
double calculHauteur(float nbDiscret, float a, float b);
double calculIntegralApproximative(float a, float b, float nbDiscret);
double integrate(float a, float b, float epsilon);

int main() {
	printf("Integration par la methode de Simpson");
	
///Donnees
	float a=0, b=1;                                 //Borne de l'intégrale
	float epsilon=1E-8;                           //Limite
	double resultat=25;                              //Resultat
	float nbDiscret=2;                              //Nombre de discreditation

///Traitements
	resultat=integrate(a, b, epsilon);              //Calcul de l'intégrale
	
///Resultats
	displayResult(a,b,epsilon,resultat, nbDiscret); //Affichage
	
	return 0;
}

double functionToIntegrate(float x) {
///Fonction à intégrer
	return exp(sin(5*x));
}

double calculHauteur(float nbDiscret, float a, float b) {
///Calcul de la taille de chaque discreditation
	float result=(b-a)/nbDiscret;
	return result;
}

double calculIntegralApproximative(float a, float b, float nbDiscret) {
///Calculer l'intégrale avec un nombre de discreditation
	double hauteur=calculHauteur(nbDiscret, a, b);          //Hauteur
	double fDeA=functionToIntegrate(a),                     //F(a) et F(b)
	fDeB=functionToIntegrate(b);
	double somme1=0, somme2=0;                              //Somme de milieu et des extremités
	double xiPlus=0, xiMoins=0;                             //Les bornes
	somme2=(xiPlus+xiMoins)/2;
	for(int i=1; i<nbDiscret; i++) {
		xiPlus=a+i*hauteur;
		xiMoins=a+(i-1+0.5)*hauteur;
		somme1=somme1+functionToIntegrate(xiPlus);
		somme2=somme2+functionToIntegrate(xiMoins);
	}
	somme1=somme1*2;
	somme2=(somme2+a+functionToIntegrate((nbDiscret-1+0.5)*hauteur))*4;
	return (hauteur/6)*(fDeA+fDeB+somme1+somme2);
}

double integrate(float a, float b, float epsilon) {
///Intégration avec limite
	float nbDiscret=20;
	double aire=calculIntegralApproximative(a, b, nbDiscret);
	nbDiscret+=20;
	double aire2=calculIntegralApproximative(a, b, nbDiscret);
	while(fabs(aire-aire2)>epsilon) {
		printf("%g", nbDiscret);
		aire=aire2;
		nbDiscret+=20;
		aire2=calculIntegralApproximative(a, b, nbDiscret);
	}
	return aire2;
}

void displayResult(float a, float b, float epsilon, double resultat, float nbDiscret) {
	printf("\n\n\n\tL'integrale de la fonction e^sin(5x) de %g a %g ", a, b);
	printf("est %g", resultat);
	printf("\n\tNous avons choisis comme epsilon %g avec un nombre de discreditation de %g", epsilon, nbDiscret);
}
