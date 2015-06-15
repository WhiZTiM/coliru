/**
@brief Struct Node
     -> Structure que représente chaque noeud de l'arbre
*/
typedef struct Node{
    char letter;                /*!< valeur du noeud. */
    // pour l’arbre
    struct Node* parent;        /*!<référence au père du noeud. */
    struct Node * left;         /*!<référence au fils gauche du noeud. */
    struct Node * right;        /*!<référence au fils droite du noeud. */
    // pour la liste
    struct Node * next ;        /*!<référence pour la liste. */
} Node;

/**
@brief Struct ListNode
     -> Structure qui représente une liste de noeuds de chaque niveau de l'arbre.
     L'ensemble de ce type est stocké dans une pile
*/
typedef struct ListNode {
    struct Node * start;       /*!<référence au premier noeud de la liste. */
    int number ;               /*!<montant de noeuds sur la liste. */
    struct Node * end;         /*!<référence au dernier noeud. */
    struct ListNode * next;    /*!<référence pour la pile. */
} ListNode;
