//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section A - Linked List Questions
Purpose: Implementing the required functions for Question 1 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

//You should not change the prototype of this function
int insertSortedLL(LinkedList *ll, int item);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode *findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


//////////////////////////// main() //////////////////////////////////////////////

int main()
{
	LinkedList ll;
	int c, i, j;
	c = 1;

	//Initialize the linked list 1 as an empty linked list
	ll.head = NULL;
	ll.size = 0;

	printf("1: Insert an integer to the sorted linked list:\n");
	printf("2: Print the index of the most recent input value:\n");
	printf("3: Print sorted linked list:\n");
	printf("0: Quit:");

	while (c != 0)
	{
		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to the linked list: ");
			scanf("%d", &i);
			j = insertSortedLL(&ll, i);
			printf("The resulting linked list is: ");
			printList(&ll);
			break;
		case 2:
			printf("The value %d was added at index %d\n", i, j);
			break;
		case 3:
			printf("The resulting sorted linked list is: ");
			printList(&ll);
			removeAllItems(&ll);
			break;
		case 0:
			removeAllItems(&ll);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}


	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int insertSortedLL(LinkedList *ll, int item)
{
	/*
	노드를 삽입하고, 정렬된 노드로 생성하기
	노드를 하나씩 삽입할 때마다 item값 기준으로 정렬이 이루어짐
	삽입한 노드 값이 이미 존재할 경우 해당 함수 종료함	
	*/
	

	//step 01: 중복 제거
	//중복 item이 들어왔을 경우, 삽입하지 않고 종료함
	ListNode* temp = ll->head;
	int ll_size = ll->size;
	for (int i = 0; i < ll_size; i++)
	{
		if (temp->item == item) 
			return -1;  //중복 값의 인덱스를 -1로 반환(요구사항)
		temp = temp->next;
	}
	 	 
	/*
	step 02: 입력 값 삽입
	insertNode()를 이용하여 0번 인덱스에 입력 값 삽입
	//ll이 비어 있는 경우에 생길 수 있는 오류 등의 예외를 최소화 하기 위해 특정 인덱스 지정
	*/	
	insertNode(ll, 0, item);	
	
	//첫 번째 노드에 접근하기 위해 head의 주소값 대입
	temp = ll->head;


	//step 03: 반복을 통한 정렬
	//반복문을 통해 값의 크기를 비교하고 값을 바꿔 오름차순 정렬
	while (temp != NULL && temp->next != NULL)
	{
		if (temp->item > temp->next->item) {
			//값 교환용 임시변수 tempV 선언 및 초기화
			int tempV = temp->item;
			temp->item = temp->next->item;
			temp->next->item = tempV;
			temp = temp->next;
		} else {
			break;  //불필요한 연산 제거
		}
	}

	//step 04: 정렬 이후 입력한 item의 인덱스 반환 위한 탐색
	temp = ll->head;    //temp 포인터 초기화
	ll_size = ll->size;
	for (int i = 0; i < ll_size; i++)
	{
		if (temp->item == item) 
			return i;
		temp = temp->next;
	}
	return 0;
}

///////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;

	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode *findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1) // 연결리스트가 null이거나 음수 인덱스이거나 리스트 크기를 초과하는 인덱스이면
		return -1;  // -1을 반환하고 삽입 실패라고 해줌

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){  // head가 null(리스트가 비어 있거나)이거나 첫 번째 인덱스라면
		cur = ll->head;  // head 값을 cur에 대입하고
		ll->head = malloc(sizeof(ListNode)); // ListNode의 사이즈는 아마도 멤버들 각각의 크기의 합이겠지만(구조체의 크기) 여기서 중요한 것은 그 크기만큼 새로운 리스트가 동적으로 할당된다는 것이 중요하다
		//malloc으로 동적 할당을 한 것은 새로운 맛집 세움 + 표지판을 만들었다!

		ll->head->item = value;
		ll->head->next = cur;  //사실상 지금 원소 개수 하나라서 nextpointer를 null로.
		ll->size++;
		return 0;			// 민영 화이팅!!! 아자아자 화이팅!!!! 빠샤빠샤 화이팅~!!!!!!!! -다현-
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next; // 이전 노드의 다음 노드 주소값을 대입
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
