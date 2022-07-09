/** Nom : EL YANBOUAI
    Prénom : Hanaâ
    N° d'apogée : 1903951   **/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef enum taille taille;
enum taille
{
    PETITE=4,MOYENNE=6,GRANDE=9
};

//strucuture du noeud
typedef struct Elem{
    int ligne;
    int colonne;
    int valeur;
    struct Elem* suivant;
}Element;

//structure de controle de la liste
typedef struct{
    Element* premier;
}Liste;

//fonction qui retourne le nombre des elements non nuls d'une matrice
int nbrValeurs(int** mat, int l, int c){
    int i, j, cpt=0;
    for(i=0;i<l;i++){
            for(j=0;j<c;j++){
                if(mat[i][j]!=0)
                    cpt++;
            }
        }
    return cpt;
}

//transformation d'une matrice en une liste chainée
Liste* transformation(int** mat, int l, int c){
    int i, j;
    Liste* li= malloc(sizeof(Liste));
    Element* e=malloc(sizeof(Element));
    li->premier=e;
    int nbr=0;
    for(i=0;i<l;i++){
        for(j=0;j<c;j++){
            if(mat[i][j]!=0){
                e->ligne=i;
                e->colonne=j;
                e->valeur=mat[i][j];
                nbr++;
                if(nbr==nbrValeurs(mat, l, c)){
                    e->suivant=NULL;
                    goto finish;
                }
                else{
                    e->suivant=malloc(sizeof(Element));
                    e=e->suivant;
                }
            }
        }
    }
    finish: return li;
}

//transformation d'une liste en une matrice
void transformationMatrice(Liste li, int** mat, int l, int c){
    int i, j;
    Element* e=malloc(sizeof(Element));
    e=li.premier;
    while(e!=NULL){
        for(i=0;i<l;i++){
            for(j=0;j<c;j++){
                if(i==e->ligne && j==e->colonne)
                    mat[i][j]=e->valeur;
            }
        }
        e=e->suivant;
    }
}

/**grille de base de sudoku**/
/*A partir de ces grilles on va générer des autres grilles qui vérifient les règles du sudoku.
Un zéro est équivalent à une case vide.
*/

int grid9[GRANDE][GRANDE]={
{3, 0, 6, 5, 0, 8, 4, 0, 0},
{5, 2, 0, 0, 0, 0, 0, 0, 0},
{0, 8, 7, 0, 0, 0, 0, 3, 1},
{0, 0, 3, 0, 1, 0, 0, 8, 0},
{9, 0, 0, 8, 6, 3, 0, 0, 5},
{0, 5, 0, 0, 9, 0, 6, 0, 0},
{1, 3, 0, 0, 0, 0, 2, 5, 0},
{0, 0, 0, 0, 0, 0, 0, 7, 4},
{0, 0, 5, 2, 0, 6, 3, 0, 0}
};

int grid6[MOYENNE][MOYENNE]={
{5,0,0,0,4,0},
{0,0,4,0,0,6},
{3,0,2,0,0,0},
{0,0,0,6,0,3},
{6,0,0,2,0,0},
{0,5,0,0,0,1}
};

int grid4[PETITE][PETITE]={
{2,0,1,0},
{0,4,0,0},
{0,0,3,0},
{0,2,0,1}
};

/**fonction qui retourne la grille choisie selon la difficulté**/
int** diff(int n){
    int i,j, **grid;

    grid=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
            *(grid+i)=(int*)malloc(n*sizeof(int));

    if (n==PETITE){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                grid[i][j]=grid4[i][j];
            }
        }
    }
    if (n==MOYENNE){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                grid[i][j]=grid6[i][j];
            }
        }
    }
    if (n==GRANDE){
        for(i=0;i<n;i++){
            for(j=0;j<n;j++){
                grid[i][j]=grid9[i][j];
            }
        }
    }

    return grid;
}

/**Géneration d'une nouvelle grille en permuttant les valeurs de 4 nombres aléatoires entre eux **/
int** new_grid(int n){
    srand(time(NULL));
    int** matrice=NULL;
    int i, j, k=0, m=0, o=0, p=0, nbr1, nbr2, nbr3, nbr4;


    matrice=(int**)malloc(n*sizeof(int*));
        for(i=0;i<n;i++)
            *(matrice+i)=(int*)malloc(n*sizeof(int));

    matrice=diff(n);

    //creation de 4 nombres aléatoires

    nbr1=(rand()%(n))+1;

    do{
    nbr2=(rand()%(n))+1;
    }while(nbr1==nbr2);

    do{
    nbr3=(rand()%(n))+1;
    }while(nbr3==nbr1 || nbr3==nbr2);

    do{
    nbr4=(rand()%(n))+1;
    }while(nbr4==nbr1 || nbr4==nbr2 ||nbr4==nbr3);

    //sauvegarder chaque nombre est sa position dans un tableau

    int tab1[n][2];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrice[i][j]==nbr1){
                tab1[k][0]=i;
                tab1[k][1]=j;
                k++;
                }
        }
    }
    int tab2[n][2];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrice[i][j]==nbr2){
                tab2[m][0]=i;
                tab2[m][1]=j;
                m++;
                }
        }
    }

    int tab3[n][2];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrice[i][j]==nbr3){
                tab3[o][0]=i;
                tab3[o][1]=j;
                o++;
                }
        }
    }

    int tab4[n][2];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            if(matrice[i][j]==nbr4){
                tab4[p][0]=i;
                tab4[p][1]=j;
                p++;
                }
        }
    }

    //permutaion des quatres nombres

    for(i=0;i<k;i++){
                matrice[tab1[i][0]][tab1[i][1]]=nbr2;
        }

    for(i=0;i<m;i++){
                matrice[tab2[i][0]][tab2[i][1]]=nbr1;
        }

    for(i=0;i<o;i++){
                matrice[tab3[i][0]][tab3[i][1]]=nbr4;
        }

    for(i=0;i<p;i++){
                matrice[tab4[i][0]][tab4[i][1]]=nbr3;
        }

    return matrice;
}

//fonction d'affichage pour la taille GRANDE
void print_sudoku9(Liste* l){
    int i,j;
    int** matrice=NULL;
    matrice=(int**)malloc(9*sizeof(int*));
    for(i=0;i<9;i++)
        *(matrice+i)=(int*)malloc(9*sizeof(int));
    transformationMatrice(*l,matrice,9,9);
    for(i=0;i<9;i++){
        for(j=0;j<9;j++){
            if(matrice[i][j] == 0 || matrice[i][j] > 9) printf("-   ");
            else{
            printf("%d   ",matrice[i][j]);}
            if(j==2 || j==5 || j==8)
                printf("|   ");
        }
    if(i==2 || i==5 || i==8)
    printf("\n---------------------------------------------\n");
    else
    printf("\n");
    }
}

//fonction d'affichage pour la taille MOYENNE
void print_sudoku6(Liste* l){
    int i,j;
    int** matrice=NULL;
    matrice=(int**)malloc(6*sizeof(int*));
    for(i=0;i<6;i++)
        *(matrice+i)=(int*)malloc(6*sizeof(int));
    transformationMatrice(*l,matrice,6,6);

    for(i=0;i<6;i++){
        for(j=0;j<6;j++){
            if(matrice[i][j] == 0 || matrice[i][j] > 6) printf("-   ");
            else{
            printf("%d   ",matrice[i][j]);}
            if(j==2 || j==5)
                printf("|   ");
        }
    if(i==1 || i==3 || i==5)
    printf("\n-----------------------------\n");
    else
    printf("\n");
    }
}

//fonction d'affichage pour la taille PETITE
void print_sudoku4(Liste* l){
    int i,j;
    int** matrice=NULL;
    matrice=(int**)malloc(4*sizeof(int*));
    for(i=0;i<4;i++)
        *(matrice+i)=(int*)malloc(4*sizeof(int));
    transformationMatrice(*l,matrice,4,4);
    for(i=0;i<4;i++){
        for(j=0;j<4;j++){
            if(matrice[i][j] == 0 || matrice[i][j] > 4) printf("-   ");
            else{
            printf("%d   ",matrice[i][j]);}
            if(j==1 || j==3)
                printf("|   ");
        }
    if(i==1 || i==3)
    printf("\n---------------------\n");
    else
    printf("\n");
    }
}

/*verifie si c'est possible
    d'affecter le num à la
    ligne ou col donnée*/
int estValide(int** grid, int ligne,
					int col, int num, int taille)
{

	/*si on a le même num
	dans la ligne similaire, on retourne 0*/
	for (int x = 0; x <= taille-1; x++)
		if (grid[ligne][x] == num)
			return 0;

	/*si on a le même num
	dans la colonne similaire, on retourne 0*/
	for (int x = 0; x <= taille-1; x++)
		if (grid[x][col] == num)
			return 0;

	/*si on a le même num
	dans le carré 2*2 similaire, on retourne 0*/
	if(taille==PETITE){
	int lignedebut = ligne - ligne % 2,
        coldebut = col - col % 2;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			if (grid[i + lignedebut][j +
						coldebut] == num)
				return 0;

	return 1;}

	/*si on a le même num
	dans le rectangle 2*3 similaire, on retourne 0*/
	if(taille==MOYENNE){
	int lignedebut = ligne - ligne % 2,
        coldebut = col - col % 3;

	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i + lignedebut][j + coldebut] == num)
				return 0;

	return 1;}

	/*si on a le même num
	dans le carre 3*3 similaire, on retourne 0*/
	if(taille==GRANDE){
	int lignedebut = ligne - ligne % 3,
        coldebut = col - col % 3;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (grid[i + lignedebut][j + coldebut] == num)
				return 0;

	return 1;}
}

/* Prend une matrice creuse et essaie
d'attribuer des valeurs à tous les emplacements non remplis de manière que
la solution soit adequate à la solution du Sudoku */
int resoutSudoku(int** grid, int ligne, int col, int taille)
{
	/* Verifie si on a atteint la (taille-1)eme ligne
	 et (taille)eme colonne , on retourne vrai pour eviter
	 le backtracking */
	if (ligne == taille - 1 && col == taille)
		return 1;

	/*Si la valeur de la colonne est n ,
	 on passe à la ligne suivante et la
	 colonne commence de 0 */
	if (col == taille)
	{
		ligne++;
		col = 0;
	}

	/* Si la position actuelle
	 de la grille contient une
	 valeur >0, on itère pour la colonne suivante*/
	if (grid[ligne][col] > 0)
		return resoutSudoku(grid, ligne, col + 1,taille);

	for (int num = 1; num <= taille; num++)
	{

		/* Si c'est possible de remplacer
		 le num (de 1 à taille) dans la
		 ligne ou col donnée on passe à la colonne suivante*/
		if (estValide(grid, ligne, col, num,taille)==1)
		{
			/* affectation du num dans la
            position (ligne,col)
			actuelle de la grille
			et considérer notre num affecté
			dans la position
			est correct (pour l'instant) */
			grid[ligne][col] = num;

			/* verifier la possibilité suivante pour la colonne
			suivante */
			if (resoutSudoku(grid, ligne, col + 1,taille)==1)
				return 1;
		}

		/* retirer le num affecté,
		puisque notre supposition est fausse ,
		et on part pour une autre supposition avec
        une différente valeur de num */
		grid[ligne][col] = 0;
	}
	return 0;
}

/**Fonction main**/

int main(){
//declaration des variables
int i, n;
char choix[4];
char choice[4];
int** matrice;
Liste* l=(Liste*)malloc(sizeof(Liste));

//choix du niveau de difficulté
do{
printf("Les niveaux :\n4 : Facile (4x4).\n6 : Moyen (6x6).\n9 : Difficile (9x9).\nVeuiller choisir un niveau :  ");
do{
scanf("%d",&n);
if(n!=4 && n!=6 && n!=9)
    printf("Mauvais choix!\nVeuillez choisir soit 4 soit 6 soit 9 : ");
}while(n!=4 && n!=6 && n!=9);


//matrice pour stocker le résultat de new_grid()
matrice=NULL;
matrice=(int**)malloc(n*sizeof(int*));
    for(i=0;i<n;i++)
        *(matrice+i)=(int*)malloc(n*sizeof(int));
matrice=new_grid(n);

//menu du choix du niveau
switch (n){
    case 4:
    printf("La grille du sudoku :\n");
    print_sudoku4(transformation(matrice,4,4));
    printf("\nSouhaitez-vous voir la solution ?(O/n)\t");
    scanf("%s",choice);
    if(strcmp(choice,"O")==0 || strcmp(choice,"o")==0 || strcmp(choice,"oui")==0){
        printf("\nLa solution du sudoku :\n");
            if (resoutSudoku(matrice, 0, 0, n)==1)
                print_sudoku4(transformation(matrice,4,4));
            else
                printf("Aucune solution possible !");
    }
    break;

    case 6:
    printf("La grille du sudoku :\n");
    print_sudoku6(transformation(matrice,6,6));
    printf("\nSouhaitez-vous voir la solution ?(O/n)\t");
    scanf("%s",choice);
    if(strcmp(choice,"O")==0 || strcmp(choice,"o")==0 || strcmp(choice,"oui")==0){
        printf("\nLa solution du sudoku :\n");
            if (resoutSudoku(matrice, 0, 0, n)==1)
                print_sudoku6(transformation(matrice,6,6));
            else
                printf("Aucune solution possible !");
    }
    break;

    case 9:
    printf("La grille du sudoku :\n");
    print_sudoku9(transformation(matrice,9,9));
    printf("\nSouhaitez-vous voir la solution ?(O/n)\t");
    scanf("%s",choice);
    if(strcmp(choice,"O")==0 || strcmp(choice,"o")==0 || strcmp(choice,"oui")==0){
        printf("\nLa solution du sudoku :\n");
            if (resoutSudoku(matrice, 0, 0, n)==1)
                print_sudoku9(transformation(matrice,9,9));
            else
                printf("Aucune solution possible !");
    }
    break;
}

//desallocation dynamique pour matrice
for(i=0;i<n;i++)
    free(matrice[i]);
free(matrice);

//on rejoue tant que choix est O ou o
printf("voulez vous rejouer ? (O/n)\n");
scanf("%s",choix);
}while(strcmp(choix,"O")==0 || strcmp(choix,"o")==0 || strcmp(choix,"oui")==0);

//desallocation de la liste
free(l);
return 0;
}
