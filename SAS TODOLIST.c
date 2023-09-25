#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


int count ;
typedef struct{
    int jour;
    int mois;
    int annee;
}dead;

int complete = 0, incomplete = 0;
 typedef struct {
    int id;
    char statut[30];
    char title[100];
    char description[200];
    dead deadline;

} task;



int z,i,j;
task LIST[20];

int choix;
int joursrestant(dead deadline) {
    struct tm now;
    time_t currentTime;
    time(&currentTime);
    now = *localtime(&currentTime);

    struct tm dueDate;
    dueDate.tm_year = deadline.annee - 1900;
    dueDate.tm_mon = deadline.mois - 1;
    dueDate.tm_mday = deadline.jour;
    dueDate.tm_hour = 0;
    dueDate.tm_min = 0;
    dueDate.tm_sec = 0;

    time_t timeRemaining = difftime(mktime(&dueDate), mktime(&now));
    return (int)(timeRemaining / (60 * 60 * 24));
}
//************************************************1-ajouter une tache***************************************************************************

void une_tache() {
    if (count >= 20) {
        printf("\t\tvotre liste est pleine!\n");
        return;
    }

    task temp;
    temp.id = count + 1;
    printf("\nID : %d\n",temp.id);
    printf("Entrer un Titre : ");
    scanf(" %[^\n]",temp.title);
        printf("description: ");
        scanf(" %[^\n]", temp.description);


    printf("Entrer un Deadline au Format (JJ/MM/AAAA): ");
    scanf("%d/%d/%d", &temp.deadline.jour, &temp.deadline.mois, &temp.deadline.annee);

      printf("Statut : a realiser (1), en cours de realisation (2), finalisee (3): ");
    int statut;

     scanf("%d",&statut);

        switch (statut) {
            case 1:
                strcpy(temp.statut,"a realiser");
                incomplete++;
                break;
            case 2:
                strcpy(temp.statut,"en cours de realisation");
                incomplete++;
                break;
            case 3:
                strcpy(temp.statut,"finalisee");
                complete++;
                break;
            default:
                printf("Invalid status, please enter 1, 2, or 3.\n");}
                //continue; // Continue the loop if status is invalid}

    LIST[count] = temp;
    count++;

    printf("Tache ajoutee avec succes!\n");
}


//*******************************************2-ajouter plusieurs taches*********************************************************************************
void plus_taches(){
    int key ;
    do
    {
        une_tache();
        printf("Pour continuer (1), pour sortir (0) ");
        scanf("%d", &key);
    } while (key != 0);
}
//****************************************************3-Affichage*******************************************************************************************
void affichage() {
    printf("\n************************************************************\n");
    printf("\n                       AFFICHAGE                            \n");
    printf("\n************************************************************\n");
    for (int i = 0; i < count; i++) {
        printf("\nID : %d", LIST[i].id);
        printf("\nTitre : %s",LIST[i].title);
        printf("\nDescription : %s",LIST[i].description);
        printf("\nDeadline : %d/%d/%d",LIST[i].deadline.jour, LIST[i].deadline.mois, LIST[i].deadline.annee);
        printf("\nStatut : %s",LIST[i].statut);


}}

//----------------------------------------------------------3-1-MENU AFFICHAGE-----------------------------------------------------------------------------
void list_taches() {
    int trie;

    printf("\n\n###############--Choisir un Affichage--#############\n\n");
    printf("\n 1.Trier les taches par ordre alphabetique   \n");
    printf("\n 2.Trier les taches par deadline   \n");
    printf("\n 3.Afficher les tâches dont le deadline est dans 3 jours ou moins  \n");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &trie);

    switch(trie){
    case 1: tri_alpha();
           break;
    case 2: tri_deadline();
           break;
    case 3: affich_3jdead();
           break;
    case 4:break;
    default:
    printf("Choix Invalide. Ressayer.\n");
    }



}
//-------------------------------------------------------------Trie alphabetique-------------------------------------------------------------------------
void tri_alpha(){
    int i,j;
    task temp ;

    for (i=0;i<count-1;i++){
        for (j=i+1;j<count;j++){
            if  (strcmp(LIST[i].title,LIST[j].title)>0){
                temp=LIST[i];
                LIST[i]=LIST[j];
                LIST[j]=temp ;

            }

        }

    }
       affichage();
}
//--------------------------------------------------------------Trie par deadline---------------------------------------------------------------------------
void tri_deadline(){
    task temp;
    for (i=0;i<count-1;i++){
        for (j=i+1;j<count;j++){
            if  (LIST[i].deadline.annee>LIST[j].deadline.annee || LIST[i].deadline.annee ==LIST[j].deadline.annee && LIST[i].deadline.mois>LIST[j].deadline.mois || LIST[i].deadline.mois ==LIST[j].deadline.mois && LIST[i].deadline.jour>LIST[j].deadline.jour || LIST[i].deadline.jour == LIST[j].deadline.jour)
                {
                temp=LIST[i];
                LIST[i]=LIST[j];
                LIST[j]=temp ;
                }

        }
    }
    affichage();
}
//-------------------------------------------------------------------Affichage 3jours deadline-------------------------------------------------------------------------
void affich_3jdead(){

    time_t currentTime;
    struct tm *localTimeInfo;
    currentTime = time(NULL);

    localTimeInfo = localtime(&currentTime);

    int year = localTimeInfo->tm_year + 1900;
    int month = localTimeInfo->tm_mon + 1;
    int day = localTimeInfo->tm_mday;
    printf("Les taches qui ont un dealai moins de 3 jours  :\n");
    for(i=0;i<count;i++){
        if(LIST[i].deadline.annee == year && LIST[i].deadline.mois == month && (LIST[i].deadline.jour - day)<= 3 && (LIST[i].deadline.jour - day)>=0){
        printf("\nID : %d",LIST[i].id);
        printf("\ntitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);
    } }
}

//**************************************************4-Menu Modification ************************************************************

void modification() {
    int modifier;

    printf("\n\n\###############--Modification--#############\n\n");
    printf("\n 1.Modifier la description d'une tache   \n");
    printf("\n 2.Modifier le statut d une tache   \n");
    printf("\n 3.Modifier le deadline d une tâche  \n");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &modifier);

    switch(modifier){
    case 1:  modifier_description();
           break;
    case 2:  modifier_statut();
          break;
    case 3:  modifier_deadline();
           break;
    case 4: break;
    default:
    printf("Choix Invalide. Ressayer.\n");
    }



}
//------------------------------------------------------4-1-Modifier description------------------------------------------------------
void  modifier_description() {
    int i, verifyID;
    printf("Entrer l'ID du tache :");
    scanf("%d", &verifyID);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == verifyID) {
            printf("Entrer votre nouvelle description  :");
            scanf(" %[^\n]", LIST[i].description);
            printf("Description modifie avec succes\n");
            break;
        }
    }
}
//-------------------------------------------------------4-2-modifier_statut-----------------------------------------------------
void modifier_statut() {
    int i, verifyID;
    char new_stat[15];
    printf("Entrer l'ID de la tache : ");
    scanf("%d", &verifyID);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == verifyID) {
            printf("Statut : a realiser (1), en cours de realisation (2), finalisee (3): ");
            int stat;
            scanf("%d", &stat);

            switch (stat) {
                case 1:
                    strcpy(LIST[i].statut, "a realiser");
                    break;
                case 2:
                    strcpy(LIST[i].statut, "en cours de realisation");
                    break;
                case 3:
                    strcpy(LIST[i].statut, "finalisee");
                    break;
                default:
                    printf("Statut invalide, veuillez entrer 1, 2 ou 3.\n");
                    return;  // Return from the function if status is invalid
            }
            printf("Statut modifie avec succes\n");
            return;  // Return from the function after updating the status
        }
    }
    printf("Tache avec l'ID %d non trouvee.\n", verifyID);
}
//---------------------------------------------------------4-3-Modifier_deadline-------------------------------------------------------------------
void modifier_deadline() {
    int i, verifyID;
    printf("Entrer l'ID du tache :");
    scanf("%d", &verifyID);

    for (i = 0; i < count; i++) {
        if (LIST[i].id == verifyID) {
            printf("Entrer votre nouveau deadline (JJ/MM/AAAA) :");
            scanf("%d/%d/%d", &LIST[i].deadline.jour, &LIST[i].deadline.mois, &LIST[i].deadline.annee);
            printf("Deadline modifie avec succes\n");
            break;
        }
    }
}

//************************************************5-SUPPRIMER**************************************************************************
void supprimer_tache() {
    int i, j, x, conf;

    // Afficher la liste des tâches pour que l'utilisateur puisse choisir l'ID à supprimer
    for (i = 0; i < count; i++) {
        printf("ID %d\n Titre : %s\n", LIST[i].id, LIST[i].title);
    }

    printf("Entrer l'ID de la tache que vous voulez supprimer :");
    scanf("%d", &x);

    for (i = 0; i < count; i++) {
        if (x == LIST[i].id) {
            // Supprimer la tâche en déplaçant les tâches suivantes
            for (j = i; j < count - 1; j++) {
                LIST[j] = LIST[j + 1];
            }
            count--;
            // Update IDs of tasks after the deleted one
            for (j = i; j < count; j++) {
                LIST[j].id = j + 1;
            }
            printf("Tache supprimee avec succes\n");
            break;
        }
    }
}



//*****************************************************6-Menu recherhe****************************************************
void recherche_tache() {
    int recherche;

    printf("\n\n\###############--Recherche une tache--#############\n\n");
    printf("\n 1.Rechercher une tache par son Identifiant   \n");
    printf("\n 2.Rechercher une tâche par son Titre   \n");
    printf("\n 3.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &recherche);

    switch(recherche){
    case 1:
    rechercher_par_id();
           break;

    case 2:
    rechercher_par_titre();
           break;

    case 3:
    break;
    default:
    printf("Choix Invalide. Ressayer.\n");
    }}
//-------------------------------------6-1-Rechercher une tâche par son Identifiant-------------------------------------------
 void rechercher_par_id(){
    int i, verifyID;
    printf("Entrer l'ID du tache:");
    scanf("%d",&verifyID);
    for(i=0;i<count;i++){
            if(LIST[i].id == verifyID){
        printf("\nVous avez chercher :\n");
        printf("\nID : %d",LIST[i].id);
        printf("\nTitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);

            }


    }

}
//---------------------------------------------------6-2-Rechercher une tâche par son Titre----------------------------------
void rechercher_par_titre() {
    int i;
    char verifyT[100];
    printf("Entrer le titre de votre tache :");
    scanf("%s", verifyT);

    for (i = 0; i < count; i++) {
        if (strcmp(LIST[i].title, verifyT) == 0) {
            printf("vous avez cherche :");
        printf("\nID : %d",LIST[i].id);
        printf("\nTitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);
        }
    }
}
//*************************************************7-statestiques****************************************************


//--------------------------------------7-1-Menu statistiques----------------------------------------
void afficher_les_statistiques() {
    int statistique;

    printf("\n\n\###############--STATISTIQUES--#############\n\n");
    printf("\n 1.Afficher le nombre total des taches   \n");
    printf("\n 2.Afficher le nombre de taches completes et incompletes  \n");
    printf("\n 3.Afficher le nombre de jours restants jusqu au delai de chaque tache \n  ");
    printf("\n 4.Retournez au Menu  ");
    printf("\n\n entrez votre choix :");
        scanf("%d", &statistique);

    switch(statistique){
    case 1:  nombres_des_taches();
           break;

    case 2:  t_completes_et_incompletes();
           break;

    case 3:  t_jours_restants();
           break;

    case 4: break;
    default:

    printf("Choix Invalide. Ressayer.\n");
    }}
//-----------------------------------------------------7-2-Afficher le nombre total des tâches-----------------------------------


    void nombres_des_taches(){
    printf("L'ensemble total des taches est: %d\n",count);
    }


//------------------------------------------------------7-3-Afficher le nombre de tâches complètes et incomplètes.------------
     void t_completes_et_incompletes(){

                printf("L'ensemble total des taches incomplete est:   %d\n",incomplete);
                printf("L'ensemble total des taches complete est:: %d\n",complete);
     }
//--------------------------------------------7-4-Afficher le nombre de jours restants jusqu'au délai de chaque tâche---------------------
void t_jours_restants() {
    printf("\nListe des Taches avec les Jours Restants:\n");
    for (int i = 0; i < count; i++) {
        int daysLeft = joursrestant(LIST[i].deadline);
        printf("\nID : %d",LIST[i].id);
        printf("\nTitre :%s",LIST[i].title);
        printf("\nDescrption :%s",LIST[i].description);
        printf("\nDeadline :%d/%d/%d",LIST[i].deadline.jour,LIST[i].deadline.mois,LIST[i].deadline.annee);
        printf("\nStatuts :%s",LIST[i].statut);


        printf("\nJours Restants: %d\n", daysLeft);
        printf("------------------------\n");
    }
}
//*******************************************************MAIN MENU***************************************************************
int main()
{
    int choice;
    do
    {
        printf("\n\n############### To-Do List Menu ###############\n");
        printf("1. Ajouter une nouvelle tache \n");
        printf("2. Ajouter plusieurs nouvelles taches\n");
        printf("3. Afficher la liste de toutes les taches\n");
        printf("4. Modifier une tache\n");
        printf("5. Supprimer une tache par identifiant.\n");
        printf("6. Rechercher les Taches \n");
        printf("7. Statistiques \n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: une_tache();
            break;

        case 2: plus_taches();
            break;

        case 3: list_taches();
            break;

        case 4: modification();
            break;

        case 5: supprimer_tache();
            break;

        case 6: recherche_tache();
            break;

        case 7:afficher_les_statistiques();
            break;

        case 8:
            printf("Exiting the program.\n");
            break;

        default:
            printf("Choix Invalide. Ressayer.\n");
        }
    } while (choice != 8);

    return 0;
}
