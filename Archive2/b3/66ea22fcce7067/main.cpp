/**
 * Базовый класс для всех контейнеров
 */
 
#include <string.h>
#include <stdlib.h>
#include <iostream>
 
using namespace std;
 
/**
 * Базовый класс для всех абстрактных контейнеров
 */
class Container {
protected:
  //MemoryManager &_memory;
 
public:
  /**
   * Базовый класс для исключений, которые запускает контейнер
   */
  struct Error {
    char msg[256];
    Error(const char *err_msg) { strcpy(msg, err_msg); }
  };
 
  class Iterator {
  public:
    /**
     * Возврашает явно указатель на элемент, на который указывает итератор в
     * данный момент.
     * Неявно возвращает размер данных
     */
    virtual void *getElement(size_t &size) = 0;
 
    /**
     * Возвращает true, если есть следующий элемент, иначе false.
     */
    virtual bool hasNext() = 0;
 
    /**
     * Переход к следующему элементу.
     */
    virtual void goToNext() = 0;
 
    /**
     * Проверка на равенство итераторов.
     */
    virtual bool equals(Iterator *right) = 0;
  };
 
  Container() {}
 
  /**
   * Функция возвращает значение, равное количеству элементов в контейнере.
   */
  virtual int size() = 0;
 
  /**
   * Функция возвращает значение, равное максимальной вместимости контейнера в
   * байтах.
   */
  virtual size_t max_bytes() = 0;
 
  /**
   * Функция возвращает указатель на итератор, указывающий на первый найденный в
   * контейнере элемент. Если элемент не найден, возвращается пустой указатель.
   */
  virtual Iterator *find(void *elem, size_t size) = 0;
 
  /**
   * Удаление всех элементов из контейнера.
   */
  virtual void clear() = 0;
 
  /**
   * Создание итератора, соответствующего данному типу контейнера.
   */
  virtual Iterator *newIterator() = 0;
 
  /**
   * Функция возвращает указатель на итератор, указывающий на первый элемент
   * контейнера. Если контейнер пустой, возвращается нулевой указатель.
   */
  virtual Iterator *begin() = 0;
 
  /**
   * Функция возвращает указатель на итератор, указывающий позицию за последним
   * элементом контейнера. Если контейнер пустой, возвращается нулевой
   * указатель.
   */
  virtual Iterator *end() = 0;
 
  /**
   * Eсли контейнер пуст возвращает true, иначе false
   */
  virtual bool empty() = 0;
 
  /**
   * Удаление элемента из позиции, на которую указывает итератор iter.
   * После удаления итератор указывает на следующий за удаленным элемент.
   */
  virtual void remove(Iterator *iter) = 0;
};

/**
 * Базовый класс для некоторой группы абстрактных контейнеров.
 */
class GroupContainer : public Container {
public:
  GroupContainer() : Container() {}
};

/**
 * Абстрактный класс: дерево
 */
class AbstractTree : public GroupContainer {
public:
  class Iterator : public Container::Iterator {
  public:
    /**
     * Переход к родительской вершине. Возвращает false если текущая вершина -
     * корень или end().
     */
    virtual bool goToParent() = 0;
 
    /**
     * Переход к дочерней вершине № child_index. Возвращает false если дочерней
     * вершины с таким номером нет.
     */
    virtual bool goToChild(int child_index) = 0;
  };
 
  /**
   * конструктор
   */
  AbstractTree() : GroupContainer() {}
 
  /**
   * деструктор
   */
  virtual ~AbstractTree() {}
 
  /**
   * Добавление элемента как дочернюю вершину № child_index вершины, на которую
   * указывает итератор. В случае успешного добавления функция возвращает
   * значение 0, в случае неудачи 1.
   */
  virtual int insert(Iterator *iter, int child_index, void *elem,
                     size_t size) = 0;
 
  /**
   * Удаление вершины, на которую указывает итератор. Если leaf_only==1 и
   * вершина не является листом, возвращает false
   * !!! Примечание: метод remove удаляет вершину вместе со всеми ее потомками
   */
  virtual bool remove(Iterator *iter, int leaf_only) = 0;
};


enum color { RED, BLACK };
 
class Node {
  int *data;
  color color;
  Node *left;
  Node *right;
  Node *parrent;
 
public:
  Node(int *data)
      : left(NULL), right(NULL), parrent(NULL), color(RED), data(data){};
  ~Node() { delete data; };
 
public:
  friend class RBtree;
};
 
class RBtree : public AbstractTree {
public:
  class Iterator : public AbstractTree::Iterator {
    RBtree *Rbtree;
 
  public:
    Node *cur;
 
  public:
    Iterator(Node *n) : cur(n){};
    ~Iterator(){};
 
    /**
     * Виртуальные функции
     */
 
  public:
    void *getElement(size_t &size); // done!
    bool hasNext();                 // done!
    void goToNext();                // done!
    bool equals(Iterator *right);   // done!
 
    bool goToParent();               // done!
    bool goToChild(int child_index); // done!
  };
 
private:
  Node *root;
  Node *NIL;
 
public:
  RBtree();
  ~RBtree(){};
 
  /**
   * Пользовательские функции
   */
public:
  void tree_insert(Node *n);
  void left_rotate(Node *n);
  void right_rotate(Node *n);
  void rb_insert(Node *n);
  Node *rb_delete(Node *n);
  void rb_delete_fixup(Node *n);
  Node *tree_successor(Node *n);
  Node *tree_predecessor(Node *n);
  void inorder_tree_walk(Node *n);
  void inorder_tree_walk_count(Node *n, int *count);
  void inorder_tree_walk_delete(Node *n);
  Node *iterative_tree_search(Node *n, int *data);
  Node *tree_minimum(Node *n);
  Node *tree_maximum(Node *n);
 
  /**
   * Виртуальные функции
   */
  int size();                              // done!
  size_t max_bytes();                      // ???
  Iterator *find(void *elem, size_t size); // ???
  void clear();                            // done!
  Iterator *newIterator();                 // ???
  Iterator *begin();                       // ???
  Iterator *end();                         // ???
  bool empty();                            // done!
  void remove(Iterator *iter){};
 
  int insert(Iterator *iter, int child_index, void *elem, size_t size);
  bool remove(Iterator *iter, int leaf_only);
};

int main()
{
}
