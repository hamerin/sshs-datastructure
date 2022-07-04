# sshs-datastructure

## 선형 리스트

* 아니 이거 그냥 배열임
* 구성 요소: 배열이라니깐 (`T*`)
* 삽입: k번째에 먼가를 삽입, 시간복잡도 $\Theta(\text{size})$
* 삭제: k번째에 있는걸 삭제, 시간복잡도 $\Theta(\text{size})$

### 이용

* 다항식: 계수 저장
* 행렬: 2차원 리스트에 저장하거나 sparse할 경우 (row, col, value)의 3-tuple의 1차원 리스트에 저장

## 연결 리스트

* 리스트의 각 원소에 다른 원소의 (메모리 상) 위치 정보가 있는 형태의 리스트
  * cf) C에서 배열은 메모리의 연속된 구간에 저장됨

### 단순 연결 리스트

* 구성 요소: `Node* head`
  * Node의 구성: `T data`, `Node* link`
* 삽입: 어떤 노드 **뒤에** 먼가를 삽입
  * 맨 앞에 삽입할땐 `head` 수정
* 탐색: 그냥 `head`부터 `link`타면서 브루트포스, 시간복잡도 $\Theta(\text{size})$ 
* 삭제: 어떤 노드(선행 노드) **뒤를** 삭제, 시간복잡도 $\Theta(1)$
  * 맨 앞에 삭제할땐 `head` 수정
  * 삭제 이후 free

### 원형 연결 리스트

* 구성 요소: 단순 연결 리스트와 동일한데 마지막 노드를 가리키는 포인터 `Node* tail`을 대신 사용할 수 있음
* 연산의 변형은 자명함

### 이중 연결 리스트

* 구성 요소: 단순 연결 리스트와 동일한데 Node의 구성에서 `Node* llink`와 `Node* rlink`가 모두 존재
* **선행 노드의 정보 없이도 삭제 가능**
* 나머지 연산의 변형은 자명함

## 스택

* 넣었다 뺐다 하는 건데 LIFO
* 이때 스택에서 제일 먼저 빠질(제일 늦게 들어온) 애를 top이라고 지칭
* 모든 연산 $\Theta(1)$

### 리스트 이용 구현

* 구성 요소: 배열, top의 인덱스
* 연산: push, pop인데 자명함

### 연결 리스트 이용 구현

* 구성 요소: 연결 리스트와 동일한데 **`head`가 top을 가리킴**
* 연산: push, pop인데 연결 리스트에서 했던 거의 부분집합

### 이용

* 역순 문자열 만들기: 다 넣었다가 다 빼기
* 함수의 call stack
* 괄호 검사: 문자열을 순차적으로 탐색하면서 여는 괄호는 push, 닫는 괄호는 top과 비교. 이때 mismatch가 있거나, 스택이 먼저 비거나, 탐색이 끝났는데도 스택이 비지 않으면 괄호가 맞지 않음
* 중위 -> 후위 표기 변환: 연산자를 스택에 순차적으로 push, top보다 우선순위가 낮은 연산자가 push되어야 하거나 중위표기식 탐색이 종료되었을 때 pop

## 큐

* 넣었다 뺐다 하는 건데 FIFO
* 이때 큐에서 제일 먼저 빠질(제일 먼저 들어온) 애를 front, 제일 늦게 들어온(제일 늦게 빠진) 애를 rear라고 지칭
* cf) Deque: 앞뒤에서 넣었다 뺐다 다 가능한거.. 인데 cyclic queue의 구현과 doubly linked list의 구현을 생각해보면 구현이 자명함
* 모든 연산 $\Theta(1)$

### 리스트 이용 구현

* 구성 요소: 배열, front와 rear의 인덱스
* 연산: enqueue, dequeue인데 자명함
* 이때 front 이전 메모리 공간은 낭비됨: **큐의 표류현상**
  * 해결: cyclic queue. enqueue와 dequeue를 modulo n으로 하면 됨

### 연결 리스트 이용 구현

* 구성 요소: 연결 리스트와 동일한데 `head`와 `tail`이 모두 존재, **`head`는 front를 가리키고 `tail`은 rear를 가리킴**
* 연산: enqueue, dequeue인데 연결 리스트에서 했던 거의 부분집합

## 트리 개요

* 드디어 비선형
* 트리의 정의: 사이클이 없는 그래프
* root가 있을 경우 level / parent-child 관계 등을 정의가능함
* 트리에서 임의의 edge를 제거하면 tree 2개가 나옴(당연함 왜냐하면 없는 사이클이 갑자기 생길 리가 없음)
  * 그래서 rooted tree에서는 parent-child 관계를 끊음으로써 형성되는 child를 root로 한 트리인 subtree 개념이 등장
* 트리의 분류: 이진 트리, 편향 이진 트리, 포화 이진 트리 등...
* rooted binary tree의 순회
  * 전위 순회: (root) - (left subtree) - (right subtree) 재귀적 반복
  * 중위 순회: (left subtree) - (root) - (right subtree) 재귀적 반복
  * 후위 순회: (left subtree) - (right subtree) - (root) 재귀적 반복
  * 레벨 순회: root로부터의 거리(node의 depth) 오름차순으로 순회하되, left subtree가 우선하여 순회함
    * 레벨 순회의 경우 rooted binary tree의 1d 표현에도 활용 가능

## 이진 탐색 트리

* 어떤 (well-ordered) 집합에 대해 트리를 이용하여 부분집합을 구현한다고 생각하면 편함
* 탐색, 삽입, 삭제 $\Theta(\text{depth})$인데, (보편적인 경우에) $o(n)$
  * self-balancing 기법이 적용된 BST는 $O(\lg n)$으로 fix 가능 

* 기본 원리: 이진 트리 + **데이터의 저장 규칙**
  * **left subtree의 모든 값 < root의 값 < right subtree의 모든 값**

### 구현

* 구성 요소: `Node* root`
  * Node의 구성: `T key`, `Node* left`, `Node* right`
* 탐색: root와 탐색하고자 하는 값을 비교하여 left/right subtree에 전달하는 과정을 생각하면 재귀적 구조가 straightforward하게 보임
  * 비재귀 구현: 현재 노드를 가리키는 포인터 변수를 잡고 while문으로 열심히 그 변수를 왼쪽 또는 오른쪽으로 옮기기
  * 재귀 구현: 현재 노드를 가리키는 포인터 변수를 함수의 parameter로 설정
* 삽입: 탐색하고 없으면 그냥 마지막 노드에서 방향 맞게 넣으면 됨 (부모 노드의 링크 수정)
* 삭제: 꽤 귀찮음
  * 해당 node의 child 0개: 행복함. 그냥 삭제하고 부모 노드의 링크 수정
  * 해당 node의 child 1개: 여전히 행복함.
    * 해당 node의 parent와 child를 연결해주면 됨
  * 해당 node의 child 2개: 그지같음
    * 생각: 삭제되는 node의 subtree에서 'BST의 저장 규칙'을 유지할 수 있는 새로운 root는? - left subtree의 max나 right subtree의 min
    * max 찾는(오른쪽으로만 가는) 함수와 min 찾는(왼쪽으로만 가는) 함수 미리 구현해놓았다고 하자
    * wlog candidate = (maximum of the left subtree)
    * 현재 node를 candidate로 치환하자
    * 그러면 left subtree에서 candidate는 삭제되는 효과: 삭제 함수를 재귀호출
  * 구현 상의 유의점: root가 바뀔 수 있기 때문에 node를 삭제하는 함수는 **삭제 후의 root를 return해야 함**
  * 재귀 구현시 parent의 정보도 같이 parameter로 넘겨줘야 함

구현 예시 (비재귀):

```c
TreeNode *maxNode(TreeNode *here) {
    while (here != NULL && here->right != NULL) here = here->right;
    return here;
}

TreeNode *deleteNode(TreeNode *root, char x) {
    TreeNode *here = root, *par = NULL;
    while (here != NULL && here->key != x) {
        par = here;
        here = x < here->key ? here->left : here->right;
    }

    if (here == NULL) return root;

    if (here->left == NULL && here->right == NULL) {
        if (par != NULL) {
            if (par->left == here) par->left = NULL;
            if (par->right == here) par->right = NULL;
        }

        if (here == root) root = NULL;
        free(here);
    } else if ((here->left == NULL) ^ (here->right == NULL)) {
        TreeNode *ret = NULL;
        if (here->left != NULL) ret = here->left;
        if (here->right != NULL) ret = here->right;

        if (par != NULL) {
            if (par->left == here) par->left = NULL;
            if (par->right == here) par->right = NULL;
        }

        if (here == root) root = ret;
        free(here);
    } else {
        TreeNode *candidate = maxNode(here->left);
        here->key = candidate->key;
        deleteNode(here->left, candidate->key);
    }

    return root;
}
```

## 힙

* 완전 이진 트리를 이용한 일종의 우선순위를 가지는 큐 형태

* 스택 / 큐 정도의 인터페이스를 가지고 있지만 안에서 자동으로 정렬되어서 최댓값 또는 최솟값을 동적으로 뽑을 수 있다고 생각하면 편함

* 기본 원리: 완전 이진 트리 + **데이터의 저장 규칙**

  * **parent가 child보다 우선** (예를 들어, max heap의 경우 parent > child)

* 놀랍게도 삽입, 삭제가 모두 $\Theta(\lg n)$

### 구현

* 기본적으로, 완전 이진 트리의 1d 표현을 이용
  * level order대로 배열에 저장
  * 1-based일 때, parent의 index가 n이라고 하면 left child의 index은 2n이고, right child의 index는 2n + 1
* ~~구현이 어려운건 아닌데 예외 처리 같은게 좀 귀찮은 편~~
* 삽입
  * 배열의 마지막(즉, 완전 이진 트리를 유지하면서 추가할 수 있는 위치)에 노드 추가
  * 데이터의 저장 규칙을 만족시키기 위해 새로 삽입된 node가 parent보다 우선일 경우 parent와 swap
  * bottom-up 방식으로, swap되었을 경우 swap된 parent에 대해서 같은 과정을 재귀적으로 수행
* 삭제
  * 데이터의 저장 규칙에 의해 root가 무조건 우선: root 삭제
  * 빈 root를 채우기 위해 배열의 마지막을 임시로 root로 설정
  * 데이터의 저장 규칙을 만족시키기 위해 left child, right child, parent(=root) 중 parent가 가장 우선이 아니라면, left와 right 중 보다 우선인 것과 swap
  * top-down 방식으로, swap되었을 경우 swap된 child에 대해서 같은 과정을 재귀적으로 수