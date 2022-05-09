/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * School of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int key; //key값 저장
	struct node *left; //왼쪽 자식 노드를 가리키는 포인터 변수
	struct node *right; //오른쪽 자식 노드를 가리키는 포인터 변수
} Node;

int initializeBST(Node** h); //트리 초기화하는 함수

/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //명령어 입력받을 변수
	int key; //값을 잠시 저장할 변수
	Node* head = NULL; //head 노드 (root를 가리킴)
	Node* ptr = NULL;	/* temp */
	printf("[----- 김주훈 2020039027 -----]\n\n"); //이름 학번 출력

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Leaf Node             = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key);
			if(ptr != NULL)
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left);
			break;
		case 'p': case 'P':
			preorderTraversal(head->left);
			break;
		case 't': case 'T':
			postorderTraversal(head->left);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL)
		freeBST(*h);
	//head 노드가 비어있지 않으면 free를 해서 모든 노드를 초기화 시킨다.

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	//head 노드에 메모리 할당
	(*h)->left = NULL;	/* root */
	//left는 root를 가리킨다.
	(*h)->right = *h; //자기 자신을 가리키게 초기화
	(*h)->key = -9999; //-9999로 초기화
	return 1;
}



void inorderTraversal(Node* ptr)
//왼쪽 자식 노드, 노드, 오른쪽 자식 노드 순서로 출력
//recursive 형태
{
	if(ptr) { //노드가 비었을 때까지 반복
		inorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
		printf(" [%d] ", ptr->key); //노드의 값 출력
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr)
//노드, 왼쪽 자식 노드, 오른쪽 자식 노드 순서로 출력
//recursive 형태
{
	if(ptr) { //노드가 비었을 때까지 반복
		printf(" [%d] ", ptr->key); //노드의 값 출력
		preorderTraversal(ptr->left); //왼쪽 자식 노드로 이동
		preorderTraversal(ptr->right); //오른쪽 자식 노드로 이동
	}
}

void postorderTraversal(Node* ptr)
//왼쪽 자식 노드, 오른쪽 자식 노드, 노드 순서로 출력
//recursive 형태
{
	if(ptr) { //노드가 비었을 때까지 반복
		postorderTraversal(ptr->left); //왼쪽 자식노드로 이동
		postorderTraversal(ptr->right); //오른쪽 자식노드로 이동
		printf(" [%d] ", ptr->key); //노드의 값 출력
	}
}


int insert(Node* head, int key)
//key 값의 크기에 따라 크면 오른쪽 서브트리 쪽으로, 작으면 왼쪽 서브트리 쪽으로 이동해서 삽입하는 함수
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	//새로운 노드 생성(동적할당)
	newNode->key = key;
	//매개변수로 받은 값을 저장
	newNode->left = NULL;
	newNode->right = NULL;
	//포인터는 NULL로 초기화

	if (head->left == NULL) { //트리가 비었을 때
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	//부모 노드를 가리킬 포인터 생성
	while(ptr != NULL) {

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1;

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
			ptr = ptr->right;
			//key 값이 더 크면 오른쪽 서브트리로 이동
		else
			ptr = ptr->left;
			//key 값이 더 작으면 왼쪽 서브트리로 이동
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //key 값이 더 작으면 왼쪽, 크면 오른쪽에 삽입
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}

int deleteLeafNode(Node* head, int key)
//key 값을 가진 자식이 없는 노드를 삭제하는 함수
{
	if (head == NULL) { //head 노드가 초기화가 안되었을 때
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) { //트리가 비어있을 때
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* head->left is the root */
	Node* ptr = head->left;
	//root를 가리키는 포인터


	/* we have to move onto children nodes,
	 * keep tracking the parent using parentNode */
	Node* parentNode = head;
	//부모 노드를 가리키는 포인터

	while(ptr != NULL) { //자식 노드가 없을 때까지 반복

		if(ptr->key == key) { //key 값을 가진 노드일 때
			if(ptr->left == NULL && ptr->right == NULL) {
				//자식 노드가 없으면

				/* root node case */
				if(parentNode == head)
				//root 노드일 때
					head->left = NULL;

				/* left node case or right case*/
				if(parentNode->left == ptr)
					parentNode->left = NULL; //부모 노드가 가리키지 못하게 NULL로 초기화
				else
					parentNode->right = NULL; //부모 노드가 가리키지 못하게 NULL로 초기화

				free(ptr); //free 시킨다.
			}
			else {
				printf("the node [%d] is not a leaf \n", ptr->key);
				//아니면 자식 노드가 있으므로 이렇게 출력
			}
			return 1;
		}

		/* keep the parent node */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key)
		// key 값이 더 크면 오른쪽에 있으므로 오른쪽 자식노드로 이동
			ptr = ptr->right;
		else
		// 아니면 반대이므로 왼쪽 자식노드로 이동
			ptr = ptr->left;


	}

	printf("Cannot find the node for key [%d]\n ", key);

	return 1;
}

Node* searchRecursive(Node* ptr, int key)
//recursive 방식으로 key 값을 가진 노드를 찾는 함수
{
	if(ptr == NULL)
		return NULL;

	if(ptr->key < key)
		ptr = searchRecursive(ptr->right, key);
		//key 값이 크면 오른쪽으로 이동해서 다시 찾고
	else if(ptr->key > key)
		ptr = searchRecursive(ptr->left, key);
		// 작으면 왼쪽으로 이동

	/* if ptr->key == key */
	return ptr;

}
Node* searchIterative(Node* head, int key)
//itertive 방식으로 key 값을 가진 노드를 찾는 함수
{
	/* root node */
	Node* ptr = head->left;
	//root 노드를 가리키는 포인터

	while(ptr != NULL)
	{
		if(ptr->key == key)
		//key 값을 가진 노드일 때
			return ptr; //노드 리턴

		if(ptr->key < key) ptr = ptr->right;
		//key 값이 크면 오른쪽으로 이동
		else // 반대
			ptr = ptr->left;
	}

	return NULL;
}

void freeNode(Node* ptr)
//노드 전체를 free 시키는 함수
//recursive 방식
{
	if(ptr) {//ptr이 NULL이 될때까지
		freeNode(ptr->left);
		//왼쪽 자식노드 free
		freeNode(ptr->right);
		//오른쪽 자식노드 free
		free(ptr);
		//노드 free
	}
}

int freeBST(Node* head)
{

	if(head->left == head)
	//비었을 때
	{
		free(head);//head노드 free
		return 1;
	}

	Node* p = head->left;
	//root를 가리키는 포인터

	freeNode(p);
	//root의 자식노드들을 free

	free(head);
	//head노드 free
	return 1;
}





