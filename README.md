# sshs-datastructure

## 선형 리스트

* 아니 이거 그냥 배열임
* 구성 요소: 배열이라니깐 (`T*`)
* 삽입: k번째에 먼가를 삽입, 시간복잡도 $\Theta(n)$
* 삭제: k번째에 있는걸 삭제, 시간복잡도 $\Theta(n)$

### 이용

* 다항식: 계수 저장
* 행렬: 2차원 리스트에 저장하거나 sparse할 경우 (row, col, value)의 3-tuple의 1차원 리스트에 저장

## 연결 리스트

* 리스트의 각 원소에 다른 원소의 (메모리 상) 위치 정보가 있는 형태의 리스트
  * cf) C에서 배열은 메모리의 연속된 구간에 저장됨

### 단순 연결 리스트

* 구성 요소: `Node* head`
  * Node의 구성: `T data`, `Node* link`
  * `link`는 다음 노드를 가리키는 포인터
* 삽입: 어떤 노드 **뒤에** 먼가를 삽입
  * 맨 앞에 삽입할땐 `head` 수정
* 탐색: 그냥 `head`부터 `link`타면서 브루트포스, 시간복잡도 $\Theta(\text{size})$ 
* 삭제: **선행 노드 뒤를 삭제**, 시간복잡도 $\Theta(1)$
  * 맨 앞에 삭제할땐 `head` 수정
  * 삭제 이후 free

### 원형 연결 리스트

* 구성 요소: 단순 연결 리스트와 동일한데 마지막 노드를 가리키는 포인터 `Node* tail`을 대신 사용할 수 있음
* 연산의 변형은 자명함

### 이중 연결 리스트

* 구성 요소: 단순 연결 리스트와 동일한데 Node의 구성에서 `Node* llink`와 `Node* rlink`가 모두 존재함. `llink`는 이전 노드를 가리키며 `rlink`는 다음 노드를 가리킴
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
  * 1-based일 때, parent의 index가 k라고 하면 left child의 index은 2k이고, right child의 index는 2k + 1
* ~~구현이 어려운건 아닌데 예외 처리 같은게 좀 귀찮은 편~~
* 삽입
  * 배열의 마지막(즉, 완전 이진 트리를 유지하면서 추가할 수 있는 위치)에 노드 추가
  * 데이터의 저장 규칙을 만족시키기 위해 새로 삽입된 node가 parent보다 우선일 경우 parent와 swap
  * bottom-up 방식으로, swap되었을 경우 swap된 parent에 대해서 같은 과정을 재귀적으로 수행
* 삭제
  * 데이터의 저장 규칙에 의해 root가 무조건 우선: root 삭제
  * 빈 root를 채우기 위해 배열의 마지막을 임시로 root로 설정
  * 데이터의 저장 규칙을 만족시키기 위해 left child, right child, parent(=root) 중 parent가 가장 우선이 아니라면, left와 right 중 보다 우선인 것과 swap
  * top-down 방식으로, swap되었을 경우 swap된 child에 대해서 같은 과정을 재귀적으로 수행

## 정렬

* 정렬이 뭔지.. 말할 필요가 있을까?

### 선택 정렬

* 기준 위치에 맞는 원소를 선택하여 자리 교환

* 구현: `i`를 0부터 n-1까지 1씩 증가시키면서, `i`번째 원소와 `[i+1:]` 구간의 최소(혹은 최대) 원소와 교환
* 시간복잡도: $\Theta(n^2)$

### 버블 정렬

* 인접한 두 개의 원소를 비교하여 자리 교환
* 구현: `e`를 n-1부터 0까지 1씩 감소시키면서, `i`를 1부터 `e`까지 증가시키면서, `i-1`번째와 `i`번째를 비교하여 역순일 경우 교환
* 시간복잡도: $\Theta(n^2)$

### 삽입 정렬

* 정렬 대상 배열의 prefix?의 정렬된 상태를 관리하면서 확장
* 구현: `p`를 1부터 n까지 증가시키면서, 배열의 `[:p]` 구간 원소가 원본 배열의 `[:p]` 구간 원소의 정렬된 상태가 되도록 함
  * 정렬된 `[:p]` 구간에서 `p`번째 원소가 들어갈 위치를 찾고 해당 위치에 삽입하면 `p`를 1 증가시킬 수 있음
* 시간복잡도: $\Theta(n^2)$

### 셸 정렬

* 일정한 간격으로 떨어져있는 원소들끼리 묶어서 삽입 정렬을 여러 번 수행
  * 주어진 `h`에 대해 배열을 `[0::h]`부터 `[h-1::h]`까지 `h`개로 분할하여 각각을 삽입 정렬한 후 다시 (`h`만큼 떨어진) 원래 위치로 삽입하는 것을 `h`-sorting이라고 하자.
    * 예를 들어, 1-sorting을 수행하면 전체 배열이 정렬됨
  * `h`를 특정한 방식으로 1까지 줄여가면서 `h`-sorting을 수행하는 정렬을 셸 정렬이라고 함
* 구현: straightforward함
* 시간복잡도
  * (자명하지만) 사용하는 `h`의 값들에 따라 다름
  * `h`를 n부터 반씩 줄여나갈 경우 worst case $\Theta(n^2)$, average case는 $o(n^2)$
    * 사실 average case $O(n^{1.5})$이라는 말이 있는데 자료를 못 찾겠어
  * cf) worst case $\Omega(N(\lg N/\lg\lg N)^2)$은 증명되어 있음

### 퀵 정렬

* pivot을 기준으로 pivot보다 작은 집합과 큰 집합으로 나누고, 각 집합에 대해 재귀적으로 다시 퀵 정렬을 수행하는 알고리즘
* 구현: pivot을 설정한 후 (pivot보다 작은 집합) - pivot - (pivot보다 큰 집합)으로 배열을 재구성한뒤 부분 배열에 대한 재귀 호출
  * 근데 inplace로 구현하려면 조금 난해함.. inplace로 구현할 경우 pivot보다 작은 집합을 관리하는 변수 하나랑 pivot보다 큰 집합을 관리하는 변수 하나를 선언하여 투 포인터 방식으로 전체 집합이 분할될 때까지 진행하여야 함
  * inplace로 구현할 경우 pivot을 먼저 구간의 마지막 원소로 보내놓고 하면 간편하지만, 근데 학교 자료에는 중앙에 있는 원소로 잡았음

```c
int partition(int a[], int l, int r) {
    int p = l + r >> 1;
    int s = l, e = r - 1;

    // 투 포인터로 집합을 확장하는 과정
    // 대충 s 이전은 작은 집합, e 이후는 큰 집합
    while (s < e) {
        // 왼쪽의 pivot보다 큰 원소를 오른쪽의 pivot보다 작은 원소와 교환 
        while (a[s] <= a[p] && s < e) s++;
        while (a[e] >= a[p] && s < e) e--;
        // while문의 등호 때문에 이 시점에서 s, e는 절대 p가 아님
        if (s < e) {
            int temp = a[s];
            a[s] = a[e];
            a[e] = temp;
        }
    }
    
    // 이 시점에서 s는 e와 같음
    // s를 먼저 이동시켰기에, s와 e는 큰 집합의 가장 왼쪽을 가리킴
    // 따라서 pivot을 제자리로 만드는 교환은 pivot이 작은 집합 쪽에 있을 경우 s-1과 해야 함
    // a[s] > a[p] 조건은 모든 원소가 pivot보다 작을 때에 대한 예외 처리
    if (a[s] > a[p] && p < s) s--;

    int temp = a[p];
    a[p] = a[s];
    a[s] = temp;

    return s;
}

void quickSort(int a[], int l, int r) {
    if (r - l <= 1) return;

    int p = partition(a, l, r);

    quickSort(a, l, p);
    quickSort(a, p + 1, r);
}
```

* 시간복잡도: $\Theta(n\lg n)$

### 병합 정렬

* 부분집합으로 분할하여 재귀적으로 병합 정렬한 다음에 정렬된 부분 배열들을 병합하는 방법
* 구현
  * (배열 길이가 1이면 정렬 끝)
  * 중앙을 기준으로 두 개의 배열로 나누어, 재귀 호출
  * 두 개의 정렬된 배열의 병합은 큐 2개를 관리하는 방식을 생각하여 구현. 두 배열의 병합되지 않은 최소의 원소(즉, 가장 왼쪽의 원소) 중 작은 것을 병합 결과 배열에 추가

```c
void merge(int a[], int l, int p, int r) {
    int *const res = (int *const)malloc(sizeof(int) * (r - l));
    int it1 = l, it2 = p, itr = 0;
    while (it1 < p || it2 < r) {
        while (it1 == p && it2 < r) res[itr++] = a[it2++];
        while (it1 < p && it2 == r) res[itr++] = a[it1++];
        res[itr++] = a[it1] < a[it2] ? a[it1++] : a[it2++];
    }
    for (int i = l; i < r; i++) a[i] = res[i - l];
    free(res);
}

void mergeSort(int a[], int l, int r) {
    if (r - l <= 1) return;

    int m = l + r >> 1;
    mergeSort(a, l, m);
    mergeSort(a, m, r);
    merge(a, l, m, r);
}
```

* 시간복잡도: $\Theta(n\lg n)$

### 기수 정렬

* 원리 및 구현
  * 어떤 함수 $f$에 대해, 정렬 대상 배열의 원소의 집합을 $X$라 할 때, $f(X)$가 적당히 유계이고 이산적인 경우 $f(X)$의 범위에 비례하는 만큼의 큐를 사용하여 각 원소를 함숫값 순으로 정렬하면서, 함숫값이 같을 경우 원래 순서를 유지하도록 할 수 있음
    * 배열을 순차적으로 탐색하면서 $x$를 $f(x)$번째 큐에 enqueue
    * 1번째 큐부터 빌 때까지 dequeue하여 새로운 배열에 순차적으로 삽입
  * 만약 $X \in \mathbb{Z}^+$인 경우 $f_{r,k}$를 $r$진법으로 표현했을 때 $k$번째 자리의 숫자로 정의한다면, $f(X) \in \mathbb{Z} \cap [0,r)$이며, 함숫값이 같을 경우 원래 순서를 유지하므로 $k$을 1부터 충분히 큰 수까지 증가시키면 전체 배열을 정렬 가능
* 시간복잡도: $\Theta(n\log_r\sup X)$
* 공간복잡도: $\Theta(\log_r\sup X)$

## 그래프 개요

* 수학에서의 그 그래프랑 동일함: $G=(V,E)$, $E$의 각 원소는 보통 $V$의 원소의 pair와 가중치로 구성됨
* 그래프의 표현
  * 인접 행렬: 2차원 배열 `M`에서 `M[i][j]`는 `i`번째와 `j`번째 정점을 연결하는 간선의 가중치(물론 간선이 없으면 미리 약속된 어떤 값)
  * 인접 리스트: 연결 리스트의 1차원 배열인데, `i`번째 리스트는 `i`번째 정점과 연결된 모든 정점의 (번호, 가중치) pair로 구성
  * 간선 리스트: 모든 간선을 (정점, 정점, 가중치)의 tuple로 만들어 그냥 1d에 저장

## 그래프 순회

* DFS; 깊이 우선 탐색
  * 갈 수 있는 (방문하지 않은) 정점이 없을 때까지 탐색한 다음, 없을 경우 갈 수 있는 정점이 있을 때까지 갈림길을 역순으로 되짚는 과정을 반복
  * 역순으로 되짚는 과정을 위해 시작 정점으로부터의 경로 정보를 저장하는 스택을 이용하거나 재귀 호출을 이용해야 함
  * 구현은 straightforward함.
* BFS; 너비 우선 탐색
  * 시작 정점으로부터 거쳐야 하는 간선의 수가 적은 간선부터 방문
  * 구현은 큐에서 dequeue되는 순서대로 정점을 방문하는 건데, 초기에 시작 정점을 enqueue한 다음, 각 정점을 방문할 때마다 그 정점에서 갈 수 있는 아직 enqueue되지 않은 정점을 enqueue

## 최소 비용 신장 트리

* 원본 그래프의 subgraph이고, 트리이며, 모든 정점을 포함하고, 모든 간선의 가중치의 합을 최소화하는 트리

### Kruskal 알고리즘

* 간선을 가중치가 낮은 것부터 MST에 추가하거나, 가중치가 높은 것부터 MST에서 삭제하는 알고리즘 (보통 전자를 씀)
* 가중치가 낮은 간선부터 MST에 추가할 때, MST를 tree로 유지하여야 하므로 간선이 연결하는 두 정점이 같은 컴포넌트에 있는지 검사하여야 함
* union-find 알고리즘: 두 정점이 같은 컴포넌트에 있는지 검사하는 알고리즘
  * 각 정점의 parent를 관리하는 배열 하나로 정의되는 일종의 forest를 관리
  * 초기화: 각 정점에 대해 미리 약속된 값 혹은 자기 자신을 parent로 설정
  * 탐색: 트리 루트 찾는 과정처럼 parent에 대해 재귀 호출하면서 찾으면 됨
  * 병합: 어떤 트리의 루트를 다른 트리의 루트의 child로 설정
  * 최적화 방법
    * path compression: 탐색 과정에서 탐색 대상 정점에서 루트로 가는 경로의 모든 정점의 parent를 루트로 재설정 (트리를 평탄화?)
    * rank optimization: 각 트리의 높이를 저장한 다음 병합 과정에서 높이가 낮은 쪽을 높은 쪽의 child로 하기
  * 시간복잡도: 대충 $o(\lg n)$
* 시간복잡도: $O(V + E\lg V)$

### Prim 알고리즘

* MST의 정점 집합을 관리하며 확장시키는데, 현재 MST에 속한 정점과 그렇지 않은 정점을 연결하는 간선 중 가장 가중치가 낮은 간선을 가지고 확장
* 시간복잡도: $\Theta(VE)$
  * cf) MST의 정점 집합 내의 각 정점과 연결된 모든 간선의 집합의 합집합을 관리하는 간선의 가중치에 대한 최소 힙을 사용하면 $O((V+E)\lg E)$ 정도로 줄일 수 있음

## 최단 경로 알고리즘

* 최단 경로 알고리즘.. 이 뭔지 설명해야할까

### Dijkstra 알고리즘

* 어떤 하나의 정점으로부터 출발하여 다른 모든 정점까지의 최단 경로의 길이를 구하는 알고리즘
* 원리 및 구현
  * 시작 정점 `s`로부터 다른 모든 정점까지의 최단 경로의 길이를 저장하는 infinity로 초기화된 배열 `D` 선언, `D[s] = 0` 수행
  * 아직 방문하지 않은 정점 중 `D[v]`가 최소인 정점 `v` 선택, `v`와 연결된 모든 방문하지 않은 정점 `u`에 대해 `D[u] = min(D[u], D[v] + w)` 수행 (단, `w`는 `u`와 `v`를 연결하는 간선의 가중치)

* 시간복잡도: $O(V^2)$
  * cf) (`D[u]`, `u`)를 관리하는 일종의 힙을 사용하면 $O((V+E)\lg E)$로 줄일 수 있음
  * 진짜 cf) fibonacci heap을 사용하면 $O(V+E\lg E)$ 가능

### Floyd 알고리즘

* 모든 정점 쌍의 최단 거리를 구하는 알고리즘
* 원리

  * 정점 집합 $S$와 정점 $u$, $v$에 대해, 사용된 정점의 집합이 $S \cup \{u, v\}$의 부분집합이 되는 경로 중 최단 경로의 길이를 $D_S(u, v)$로 정의하자.

  * 이때 $w \notin S$에 대해:

    * $D_{S\cup\{w\}}(u, v)$는 다음 2가지 경우 중 하나
      * $w$를 거칠 경우: $D_S(u, w) + D_S(w, v)$
      * 그렇지 않은 경우: $D_S(u,v)$
    * 따라서 $D_{S\cup\{w\}}(u, v)=\min(D_S(u, w) + D_S(w, v), D_S(u,v))$

* 구현: $S$를 $\phi$부터 확장하면서 $D_S$를 2차원 배열에 저장
* 시간복잡도: $O(V^3)$

## AVL 트리

* self-balancing binary search tree
* BST의 연산 시간을 줄이기 위해, BST가 스스로 구조를 변형하여 depth를 낮게 유지(즉, 왼쪽 서브트리와 오른쪽 서브트리의 depth를 비슷하게 유지; rebalance)
* 구현: BST와 동일한데 root에서 바뀐 부분까지의 모든 경로에 대해서 depth가 높은 것부터 rebalance 해주면 됨. 근데 삽입할 때도 rebalance 과정에서 root가 바뀔 수 있으니 root 포인터를 return하면서 관리해 줘야 함
  * ~~구현에 대해 더 말하고 싶지만 자료와 기출의 구현이 너무 그지같아서 그걸 따라할 수 없음.. 알아서 보기~~

### BF

* BF(balance factor): (left subtree의 높이) - (right subtree의 높이)
* **AVL 트리는 BF의 절댓값을 1 이하로 유지**

### rotate

* BST의 구조를 변경하는 기본적인 방법

* (x에 대한) left rotate: x의 BF가 음수인 경우 증가시킴![](https://cdn.programiz.com/cdn/farfuture/-azcNvOPWv7wEnEzT3h227dYtZBlAL8CXtHdwXenr1c/mtime:1590639276/sites/tutorial2program/files/avl-tree-leftright-rotate-1.png)

* (x에 대한) right rotate: x의 BF가 양수인 경우 감소시킴![](https://cdn.programiz.com/cdn/farfuture/flq1MTO6SBcWdXIUda_BY4yhf9BLPRf7MT4Ip79vYF4/mtime:1590639294/sites/tutorial2program/files/avl-tree-rightleft-rotate-1.png)

### rebalance

* 하나의 연산은 BF를 최대 1 변화시키므로 BF가 2나 -2인 경우에 대해 고려해주면 됨
* 정점 x의 BF가 2인 경우
  * x의 left의 BF가 -1인 경우: x의 left에 left rotate 수행 (LR)
    * 이러면 y의 left의 BF가 0 이상
  * x에 right rotate 수행 (LR, RR)

* 정점 x의 BF가 -2인 경우
  * x의 right의 BF가 1인 경우: x의 right에 right rotate 수행 (RL)
    * 이러면 x의 right의 BF가 0 이하

  * x에 left rotate 수행 (LL)

* height와 BF 재계산

## 해싱

* 어떤 함수 $h$에 대해, 자료 $x$를 해시 테이블의 $h(x)$번째 버킷에 넣는 방법

  * 충돌: $h$가 one-to-one일 수 없기에 $h(x)$가 겹침
  * 오버플로우: 해시 테이블의 용량이 부족할 수 있음

* 해시 함수의 예시 

  * 제산 함수: $h(x) = x\ \%\ M$
  * 승산 함수: $h(x) = \lfloor M\{\alpha x\}\rfloor$
  * 폴딩 함수: 키의 사이즈가 너무 클 때
    * 이동 폴딩: 각 분할 부분을 이동시켜 맞추고 더함
      Ex) $h(12320324111220)=123+203+241+112+20$ 
    * 경계 폴딩: 각 분할 부분을 기준으로 접으면서 맞추고 더함
      Ex) $h(12320324111220)=123+302+241+211+20$
  * 중간 제곱 함수: 키의 제곱에서 중간 몇자리 추출
  * 숫자 분석 함수: 키들을 적당한 진수로 변환환 후 각 자릿수의 분포를 분석, 가장 고르게 분포된 자릿수부터 뽑아 만든 수를 사용
  * 진법 변환 함수: 10진수로 변환 후 자릿수 추출
  * 비트 추출 함수: 2진수로 변환 후 자릿수 추출

* 충돌의 해결

  * 선형 조사법: $h(x)$가 겹치면 대신 $h(x)+1$, 이것도 겹치면 $h(x)+2$... 등 선형으로 조사하여 빈 위치에 저장
    * 데이터가 많아지면 연속적으로 존재하는 데이터가 많아져(군집화) 시간이 오래 걸리고, 유사한 $h(x)$를 가지는 데이터끼리는 서로 모여서 구분이 어렵게 된다.(결합)
  * 이차 조사법: $h(x)$가 겹치면 대신 $h(x)+1^2$, 이것도 겹치면 $h(x)+2^2$... 등 이차식을 이용해 조사하여 빈 위치에 저장
  * 이중 해싱법(aka 재해싱):  $h(x)$가 겹치면 새로운 해시 함수 $h'(x)$를 가지고 $h(x)+h'(x)$, 이것도 겹치면 $h(x)+2h'(x)$... 등을 조사하여 빈 위치에 저장
  * 체이닝: 그냥 각 버킷을 링크드 리스트로 만들면 됨

* 시간복잡도: 최선의 경우 $O(1)$이지만 최악의 경우 $O(n)$



  

