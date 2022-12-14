#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROGRAM_ERROR (-1)									
#define MALLOC_ERROR (0)									
#define LINE_LENGTH 128		

struct tree_node;
typedef struct tree_node* Tree;
typedef struct tree_node* Position;

typedef struct tree_node
{
	int val;
	Tree left;
	Tree right;
}Node;

Position TraziMin(Tree S);
Position TraziMax(Tree S);
Position Trazi(int X, Tree S);
Tree Dodaj(int X, Tree S);
Tree Brisi(int X, Tree S);
int InorderIspis(Tree S);
int PreorderIspis(Tree S);
int PostorderIspis(Tree S);
int Visina(Tree S);
int TrenutniLevel(Tree S, int level);
int LevelorderIspis(Tree S);
int BrisiSve(Tree S);

int main(void) {
	int rval = 0;
	printf("Unesi vrijednost root-a (veci od nula)>");
	scanf_s(" %d", &rval);
	while (rval <= 0) {
		printf("\nA brate ne gnjavi nego napravi kako valja>");
		scanf_s(" %d", &rval);
	}
	int op = 0;
	Node Root = {
		.val = rval,
		.left = NULL,
		.right = NULL
	};

	do{
	op = 0;
	printf(
		"*\t*\t*\t*\n"
		"Odaberite zeljenu operaciju:\n"
		"1) Unos elementa\n"
		"2) Inorder ispis\n"
		"3) Preorder ispis\n"
		"4) Postorder ispis\n"
		"5) Level order ispis\n"
		"6) Briši element\n"
		"7) Traži element\n"
		"0) Izlaz\n"
		"*\t*\t*\t*\n");
	scanf_s(" %d", &op);

		switch (op) {
		case 1:
			printf("Unos elementa...\nVrijednost>");
			scanf_s(" %d", &rval);
			Dodaj(rval, &Root);
			break;
		case 2:
			printf("Inorder ispis...\n");
			InorderIspis(&Root);
			printf("\n");
			break;
		case 3:
			printf("Preorder ispis...\n");
			PreorderIspis(&Root);
			printf("\n");
			break;
		case 4:
			printf("Postorder ispis...\n");
			PostorderIspis(&Root);
			printf("\n");
			break;
		case 5:
			printf("Level order ispis...\n");
			LevelorderIspis(&Root);
			printf("\n");
			break;
		case 6:
			printf("Brisi elemement...\nVrijednost>");
			scanf_s(" %d", &rval);
			Brisi(rval, &Root);
			printf("\n");
			break;
		case 7:
			printf("Trazi element...\nVrijednost>");
			scanf_s(" %d", &rval);
			Trazi(rval, &Root);
			printf("\n");
			break;
		case 0:
			printf("Izlaz...\n");
			break;
		}
	} while (op != 0);

	BrisiSve(Root.left);
	BrisiSve(Root.right);
	return EXIT_SUCCESS;
}

Position TraziMin(Tree S) {
	if (NULL == S) {
		return NULL;
	}
	if (NULL == S->left) {
		return S;
	}
	return TraziMin(S->left);
}

Position TraziMax(Tree S) {
	if (NULL == S) {
		return NULL;
	}
	if (NULL == S->right) {
		return S;
	}
	return TraziMin(S->right);
}

Position Trazi(int X, Tree S) {
	if (NULL == S) {
		printf("Nije pronaden\n");
		return NULL;
	}
	if (X < S->val) {
		printf("%d->", S->val);
		Trazi(X, S->left);
	}
	else if (X > S->val) {
		printf("%d->", S->val);
		Trazi(X, S->right);
	}
	else {
		printf("%d", S->val);
		return S;
	}
}

Tree Dodaj(int X, Tree S) {
	if (NULL == S) {
		S = (Tree)malloc(sizeof(Node));
		S->val = X;
		S->left = NULL;
		S->right = NULL;
		if (S == NULL) {
			printf("Pogreska prilikom alociranja, alociranje neuspjesno.\n");
			return MALLOC_ERROR;
		}
	}
	if (X < S->val) {
		S->left = Dodaj(X, S->left);
	}
	else if (X > S->val) {
		S->right = Dodaj(X, S->right);
	}
	return S;
}

Tree Brisi(int X, Tree S) {
	if (NULL == S) {
		printf("A brate nemos, nema ga\n");
		return NULL;
	}
	if (X < S->val) {
		S->left = Brisi(X, S->left);
	}
	else if (X > S->val) {
		S->right = Brisi(X, S->right);
	}
	else if (S->left != NULL && S->right != NULL) {
		Position temp = TraziMin(S->right);
		S->val = temp->val;
		S->right = Brisi(S->val, S->right);
	}
	else {
		Position temp = S;
		if (NULL == S->left) {
			S = S->right;
			free(temp);
		}
		else {
			S = S->left;
			free(temp);
		}

	}

	return S;
}

int InorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	InorderIspis(S->left);
	printf("%d ", S->val);
	InorderIspis(S->right);
	return EXIT_SUCCESS;
}

int PreorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	printf("%d ", S->val);
	PreorderIspis(S->left);
	PreorderIspis(S->right);
	return EXIT_SUCCESS;
}

int PostorderIspis(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}
	PostorderIspis(S->left);
	PostorderIspis(S->right);
	printf("%d ", S->val);
	return EXIT_SUCCESS;
}

int Visina(Tree S)
{
	if (S == NULL)
		return EXIT_SUCCESS;
	else {
		int lvisina = Visina(S->left);
		int rvisina = Visina(S->right);

		if (lvisina > rvisina)
			return (lvisina + 1);
		else
			return (rvisina + 1);
	}
}

int TrenutniLevel(Tree S, int level)
{
	if (S == NULL)
		return EXIT_SUCCESS;
	if (level == 1)
		printf("%d ", S->val);
	else if (level > 1) {
		TrenutniLevel(S->left, level - 1);
		TrenutniLevel(S->right, level - 1);
	}
	return EXIT_SUCCESS;
}

int LevelorderIspis(Tree S) {
	int h = Visina(S);
	int i = 0;
	for (i = h; i > 0; i--)
		TrenutniLevel(S, i);
}

int BrisiSve(Tree S) {
	if (S == NULL) {
		return EXIT_SUCCESS;
	}

	BrisiSve(S->left);
	BrisiSve(S->right);
	free(S);
}
