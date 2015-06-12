
#define BOOST_TEST_MODULE ms_sort_with_tests
#include <boost/test/included/unit_test.hpp>
#include <iostream>

class Node {
public:
    int data;
	Node* next;
};
/*
 * return a pointer to one element from head1 or head2 depending on the value of "data".
 * Moves head1 or head2 to the next element in the corresponding list.
 * If one list is empty, returns the other list.
 */
Node* getLowerElementAndAdvance(Node*& head1, Node*& head2) {
	//handle termination case: add the elements left in one of the two lists to the tail of the merged list.
	Node* lowerValueNode;
	if (head1 == NULL) {
		lowerValueNode = head2;
		head2 = NULL;
	} else if (head2 == NULL) {
		lowerValueNode = head1;
		head1 = NULL;
	} else {
		if (head1->data < head2->data) {
			lowerValueNode = head1;
			head1 = head1->next;
		} else {
			lowerValueNode = head2;
			head2 = head2->next;
		}
	}
	return lowerValueNode;
}

/**
 * This function merge two ordered lists into one.
 * WARNING: the two lists head1 and head2 shouldn't be used after the Merge call.
 */
Node* Merge(Node* head1, Node* head2) {

	Node* mergedListHead = getLowerElementAndAdvance(head1, head2);
	Node* currentNode = mergedListHead;
	while (head1 != NULL || head2 != NULL) {
		currentNode->next = getLowerElementAndAdvance(head1, head2);
		currentNode = currentNode->next;
	}
	return mergedListHead;
}

//_____________________ below here are utilities for tests
using namespace std;

class NodeList {
	Node* head;
public:

	NodeList(Node* head1) {
		head = head1;
	}

	static NodeList makeNodeList(const vector<int>& elements) {
		Node* localHead = NULL;
		Node* current = NULL;
		for (int data : elements) {
			Node* node = new Node();
			node->data = data;
			node->next = NULL;
			if (localHead == NULL) {
				localHead = node;
			} else {
				current->next = node;
			}
			current = node;
		}
		return NodeList(localHead);
	}

	bool operator ==(const NodeList &list2) const {
		bool equals = true;
		Node* list1Iter = head;
		Node* list2Iter = list2.head;
		while (equals) {
			if (list1Iter == NULL && list2Iter == NULL) {
				break;
			} else if (list1Iter == NULL || list2Iter == NULL) {
				equals = false;
			} else {
				equals = list1Iter->data == list2Iter->data;
				list1Iter = list1Iter->next;
				list2Iter = list2Iter->next;
			}
		}
		return equals;
	}

	bool operator !=(const NodeList &list2) const {
		return !(*this == list2);
	}

	operator Node*() const {
		return head;
	}

	static void emptyNodeList(NodeList& listToFree) {
		Node* currentElement = listToFree.head;
		Node* dummy;
		while (currentElement != NULL) {
			dummy = currentElement;
			currentElement = currentElement->next;
			free(dummy);
		}
		listToFree.head = NULL;
	}
};

std::ostream& operator<<(std::ostream& os, const NodeList& nodeList) {
	Node* currentElement = nodeList;
	while (currentElement != NULL) {
		os << currentElement->data << ",";
		currentElement = currentElement->next;
	}
	return os;
}

BOOST_AUTO_TEST_CASE(null_list) {
	Node * list = Merge(NULL, NULL);
	BOOST_ASSERT_MSG(list == NULL, "list is null");
}

BOOST_AUTO_TEST_CASE(test_equals) {
	NodeList list1 = NodeList::makeNodeList( { 1, 2, 3 });
	NodeList list2 = NodeList::makeNodeList( { 1, 2, 3 });
	BOOST_ASSERT_MSG(list1 == list2, "list are equals");
	NodeList::emptyNodeList(list1);
	NodeList::emptyNodeList(list2);

	NodeList list3 = NodeList::makeNodeList( { 1 });
	NodeList list4 = NodeList::makeNodeList( { 1, 2, 3 });
	BOOST_ASSERT_MSG(list3 != list4, "list are different");
	NodeList::emptyNodeList(list3);
	NodeList::emptyNodeList(list4);

	NodeList list5 = NodeList::makeNodeList( { 1, 3, 3 });
	NodeList list6 = NodeList::makeNodeList( { 1, 2, 3 });
	BOOST_ASSERT_MSG(list5 != list6, "list are different");
	NodeList::emptyNodeList(list5);
	NodeList::emptyNodeList(list6);
}

BOOST_AUTO_TEST_CASE(test_merge) {
	NodeList list1 = NodeList::makeNodeList( { 1, 5, 7 });
	NodeList list2 = NodeList::makeNodeList( { 1, 2, 3 });
	NodeList expected = NodeList::makeNodeList( { 1, 1, 2, 3, 5, 7 });
	NodeList result(Merge(list1, list2));
	BOOST_ASSERT_MSG(result == expected, "list are equals");
	NodeList::emptyNodeList(result);
	NodeList::emptyNodeList(expected);

}

BOOST_AUTO_TEST_CASE(test_merge_with_empty) {
	NodeList list1 = NodeList::makeNodeList( { 1, 5, 7 });
	NodeList expected = NodeList::makeNodeList( { 1, 5, 7 });
	NodeList result(Merge(list1, NULL));
    cout << result << endl;
	BOOST_ASSERT_MSG(result == expected, "list are equals");
	NodeList::emptyNodeList(result);
	NodeList::emptyNodeList(expected);
}
