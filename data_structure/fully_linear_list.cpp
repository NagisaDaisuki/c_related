#include <iostream>

using namespace std;

int OK = 0;
int ERROR = 1;

#define MAXSIZE 1000
typedef struct Book {
  string no;
  string name;
  int price;
} ElemType;

int cmp(ElemType a, ElemType b) {
  if (a.name == b.name && a.no == b.no && a.price == b.price)
    return 1;
  else
    return 0;
}

struct SqList {
  ElemType *elem;
  int length;

  int readinfo();

  int Init();

  // 获得第 i 个元素的值，i从1..length
  int GetElem(int i, ElemType &e);

  // 获得e的位置，0号元素返回1，length - 1号元素返回length
  int LocateElem(ElemType e);

  // 在第i个元素处插入，插入元素成为 i - 1 号
  int ListInsert_Sq(int i, ElemType e);

  // 删除第i个元素位置，对应 i - 1 号元素
  int ListDelete_Sq(int i);

  void Destroy();
};

int SqList::readinfo() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    ElemType e;
    cin >> e.no;
    cin >> e.name;
    cin >> e.price;

    if (ListInsert_Sq(i + 1, e) == ERROR)
      return ERROR;
  }

  return OK;
}

int SqList::Init() {
  // length需要清零，用new生成，内存分配失败返回ERROR
  length = 0;
  elem = new ElemType[MAXSIZE];
  if (elem == NULL)
    return ERROR;
  return OK;
}

int SqList::GetElem(int i, ElemType &e) {
  // 返回 i - 1 号元素

  if (i < 1 || i > length) {
    return ERROR;
  }
  e = elem[i - 1];
  return OK;
}

// 返回与 e 信息相同的元素所在位置，第几号位，范围为 1~length
int SqList::LocateElem(ElemType e) {
  // 遍历整个顺序表
  for (int j = 0; j < length; j++) {
    if (cmp(elem[j], e) == 1) {
      return j + 1; // 返回位置加下标
    }
  }
  return 0;
}

int SqList::ListInsert_Sq(int i, ElemType e) {
  // length需要加1
  // 安全检查
  if (i < 1 || i > length + 1)
    return ERROR;
  // 容量检查
  if (length >= MAXSIZE)
    return ERROR;
  // 从后往前遍历把 i - 1 以及后面的元素往后挪一格
  for (int j = length - 1; j >= i - 1; j--) {
    elem[j + 1] = elem[j];
  }
  elem[i - 1] = e;
  length++;
  return OK;
}

int SqList::ListDelete_Sq(int i) {
  // length 需要改变
  if (i < 1 || i > length + 1)
    return ERROR;
  // 从前往后遍历把i + 1以及后面的元素往前挪一格
  for (int j = i; j < length; j++) {
    elem[j] = elem[j + 1];
  }
  length--;
  return OK;
}

void SqList::Destroy() {
  if (elem != NULL) {
    delete[] elem;
    elem = NULL; // 指针置空，同时作为判断数组是否为空
  }
  length = 0;
}

int main() {

  SqList booklist;

  // 初始化
  booklist.Init();

  // 整体读入信息
  booklist.readinfo();

  // 获得一个元素，根据其位置确定查找的新位置
  ElemType e1;
  // int loc1 = rand()%booklist.length
  int loc1;
  cin >> loc1;
  if (booklist.GetElem(loc1, e1) == OK) {
    e1.price--;
    int iloc = booklist.LocateElem(e1);
    if (booklist.ListDelete_Sq(iloc) == OK)
      cout << "SUCCESS" << endl;
    else
      cout << "FAIL" << endl;
  }

  booklist.Destroy();

  if (booklist.elem == NULL)
    cout << "SUCCESS" << endl;

  return 0;
}
