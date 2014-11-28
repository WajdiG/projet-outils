/**
 * \file	fonction.h
 * \brief	projet de Black Jack
 * \author	 GUEDOUAR Wajdi
 * \author	 THIEULART Godefroy  
 * \author   OKROU PODA
 * \version	0.1
 * \date	22 Octobre 2014
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "fonction.h"
#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "CUnit/Console.h"


/**
*\fn void test_tirer_carte(void)
*\brief Test qui verifie que la carte tirée est comprise entre 0 et 52
*/
void test_tirer_Carte(){
	
	CU_ASSERT(tirer_carte(JOUEUR)<52 && tirer_carte(JOUEUR)>=0);
	CU_ASSERT(tirer_carte(BANQUE)<52 && tirer_carte(BANQUE)>=0);
	CU_ASSERT(tirer_carte(BANQUE_CACHEE)<52 && tirer_carte(BANQUE_CACHEE)>=0);
	
}

/**
*\fn void test_tirer_carte(void)
*\brief Test qui verifie que la carte tirer n'appartient pas déjà à un autre joueur
*/
void test_affectationCarteMultiple(){
	
	srand(time(NULL));
	short random = rand()%(52-1)+1;
	
	if(cartes[random]==BANQUE){
		CU_ASSERT(cartes[random]!=JOUEUR && cartes[random]!=BANQUE_CACHEE);
	}
	else if(cartes[random]==JOUEUR){
		CU_ASSERT(cartes[random]!=BANQUE && cartes[random]!=BANQUE_CACHEE);
	}
	else if(cartes[random]==BANQUE_CACHEE){
		CU_ASSERT(cartes[random]!=BANQUE && cartes[random]!=JOUEUR);
	}
}


/**
*\fn void test_tirer_carte(void)
*\brief test qui verifie que la valeur de la carte est bien comprise entre 1 et 12
*/
void test_valeurCarte(){
	
	srand(time(NULL));
	short carte = rand()%(52-1)+1;
	short valeur=donner_valeur_carte(JOUEUR,carte);
	valeur=valeur%13;
	
	CU_ASSERT(valeur<=12 && valeur>0);
	
}

/**
*\fn int main
*\brief la fonction principale permettant de réaliser les différents test
*\return int renvoie un résultat en cas d'erreur dans l'un des tests
*/
int main(int argc, const char * argv[]){
	
	CU_pSuite pSuite = NULL;
	
	if(CUE_SUCCESS != CU_initialize_registry()){
		return CU_get_error();
	}
	
	pSuite = CU_add_suite("Suite_1", 0, 0);
	
	if(!pSuite){
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(!CU_add_test(pSuite, "test du tirage de carte", test_tirer_Carte)){
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(!CU_add_test(pSuite, "test de possession des cartes", test_affectationCarteMultiple)){
		CU_cleanup_registry();
		return CU_get_error();
	}
	if(!CU_add_test(pSuite, "test de la valeur des cartes", test_valeurCarte)){
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();		
}
