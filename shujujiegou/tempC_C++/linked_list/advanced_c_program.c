#define _POSIX_C_SOURCE 200809L // Required for strdup

#include <stdio.h>   // Standard input/output library for printf, fprintf, etc.
#include <stdlib.h>  // Standard library for malloc, free, exit, etc.
#include <string.h>  // String manipulation functions for strcmp, strdup, etc.

// --- Function Pointer Type Definitions ---
// These typedefs make the code more readable and define the "interface"
// for how different data types will interact with our generic list.

// Function to print data. Takes a void pointer to the data.
typedef void (*PrintDataFunc)(void *data);

// Function to compare two data items. Returns 0 if equal, non-zero otherwise.
// Similar to strcmp or integer comparison.
typedef int (*CompareDataFunc)(const void *data1, const void *data2);

// Function to free data. Useful for dynamically allocated data (like strings).
typedef void (*FreeDataFunc)(void *data);

// --- Generic Linked List Node Structure ---
// This structure holds a pointer to the actual data and a pointer to the next node.
// The 'data' member is a 'void *', making the list generic (can store any type).
typedef struct Node {
    void *data;         // Pointer to the actual data (can be int*, char*, struct*, etc.)
    struct Node *next;  // Pointer to the next node in the list
} Node;

// --- Generic Linked List Structure ---
// This structure holds the head of the list and function pointers for data handling.
// This allows the list to manage different data types without knowing their specifics.
typedef struct LinkedList {
    Node *head;             // Pointer to the first node in the list
    PrintDataFunc print;    // Function pointer to print the data stored in nodes
    CompareDataFunc compare; // Function pointer to compare data stored in nodes
    FreeDataFunc free_data; // Function pointer to free dynamically allocated data
} LinkedList;

// --- Linked List Operations ---

/**
 * @brief Creates a new generic linked list.
 *
 * @param print_func Function to print data.
 * @param compare_func Function to compare data.
 * @param free_func Function to free data.
 * @return A pointer to the newly created LinkedList, or NULL if allocation fails.
 */
LinkedList *createLinkedList(PrintDataFunc print_func, CompareDataFunc compare_func, FreeDataFunc free_func) {
    // Allocate memory for the LinkedList structure itself.
    LinkedList *list = (LinkedList *)malloc(sizeof(LinkedList));
    if (list == NULL) {
        perror("Failed to allocate memory for LinkedList");
        return NULL; // Return NULL on allocation failure
    }

    // Initialize the head of the list to NULL (empty list).
    list->head = NULL;
    // Assign the provided function pointers for data handling.
    list->print = print_func;
    list->compare = compare_func;
    list->free_data = free_func;

    return list; // Return the newly created list
}

/**
 * @brief Creates a new node for the generic linked list.
 *
 * @param data A void pointer to the data to be stored in the node.
 * @return A pointer to the newly created Node, or NULL if allocation fails.
 */
Node *createNode(void *data) {
    // Allocate memory for a new Node.
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        perror("Failed to allocate memory for Node");
        return NULL; // Return NULL on allocation failure
    }

    // Assign the provided data and set the next pointer to NULL.
    newNode->data = data;
    newNode->next = NULL;
    return newNode; // Return the new node
}

/**
 * @brief Adds a new node to the beginning of the linked list.
 *
 * @param list A pointer to the LinkedList structure.
 * @param data A void pointer to the data to be added.
 * @return 0 on success, -1 on failure (e.g., memory allocation failure).
 */
int addNodeAtBeginning(LinkedList *list, void *data) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in addNodeAtBeginning.\n");
        return -1;
    }

    // Create a new node with the given data.
    Node *newNode = createNode(data);
    if (newNode == NULL) {
        return -1; // Return -1 if node creation failed
    }

    // Link the new node to the current head of the list.
    newNode->next = list->head;
    // Update the head of the list to be the new node.
    list->head = newNode;
    return 0; // Return 0 on success
}

/**
 * @brief Prints all elements in the linked list using the list's print function.
 *
 * @param list A pointer to the LinkedList structure.
 */
void printList(const LinkedList *list) {
    if (list == NULL) {
        fprintf(stderr, "Error: List is NULL in printList.\n");
        return;
    }
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node *current = list->head; // Start from the head of the list
    printf("List elements: [");
    while (current != NULL) {
        // Call the specific print function for the data type.
        list->print(current->data);
        current = current->next; // Move to the next node
        if (current != NULL) {
            printf(", ");
        }
    }
    printf("]\n");
}

/**
 * @brief Finds a node in the linked list that matches the given data.
 *
 * @param list A pointer to the LinkedList structure.
 * @param data_to_find A void pointer to the data to search for.
 * @return A pointer to the data found, or NULL if not found or list is invalid.
 */
void *findNode(const LinkedList *list, const void *data_to_find) {
    if (list == NULL || list->head == NULL) {
        return NULL; // List is empty or invalid
    }

    Node *current = list->head;
    while (current != NULL) {
        // Use the list's compare function to check for a match.
        if (list->compare(current->data, data_to_find) == 0) {
            return current->data; // Data found
        }
        current = current->next;
    }
    return NULL; // Data not found
}

/**
 * @brief Deletes the first node found that matches the given data.
 *
 * @param list A pointer to the LinkedList structure.
 * @param data_to_delete A void pointer to the data to delete.
 * @return 0 on success, -1 if data not found or list is invalid.
 */
int deleteNode(LinkedList *list, const void *data_to_delete) {
    if (list == NULL || list->head == NULL) {
        return -1; // List is empty or invalid
    }

    Node *current = list->head;
    Node *prev = NULL;

    // Case 1: Node to delete is the head
    if (list->compare(current->data, data_to_delete) == 0) {
        list->head = current->next; // Update head
        if (list->free_data != NULL) {
            list->free_data(current->data); // Free the data if a free function is provided
        }
        free(current); // Free the node itself
        return 0;
    }

    // Case 2: Node to delete is in the middle or end
    prev = current;
    current = current->next;
    while (current != NULL) {
        if (list->compare(current->data, data_to_delete) == 0) {
            prev->next = current->next; // Bypass the node to be deleted
            if (list->free_data != NULL) {
                list->free_data(current->data); // Free the data
            }
            free(current); // Free the node
            return 0;
        }
        prev = current;
        current = current->next;
    }

    return -1; // Data not found
}

/**
 * @brief Frees all nodes in the linked list and the list structure itself.
 *        Uses the list's free_data function for each node's data.
 *
 * @param list A pointer to the LinkedList structure.
 */
void destroyLinkedList(LinkedList *list) {
    if (list == NULL) {
        return;
    }

    Node *current = list->head;
    Node *next_node;

    while (current != NULL) {
        next_node = current->next;
        // If a free_data function is provided, use it to free the actual data.
        if (list->free_data != NULL) {
            list->free_data(current->data);
        }
        free(current); // Free the node itself
        current = next_node;
    }
    free(list); // Finally, free the LinkedList structure
    printf("Linked list destroyed and memory freed.\n");
}

// --- Data-Specific Helper Functions (for integers) ---

/**
 * @brief Prints an integer.
 * @param data A void pointer to an integer.
 */
void printInt(void *data) {
    // Cast the void pointer back to an int pointer and dereference it.
    printf("%d", *(int *)data);
}

/**
 * @brief Compares two integers.
 * @param data1 A void pointer to the first integer.
 * @param data2 A void pointer to the second integer.
 * @return 0 if equal, non-zero otherwise.
 */
int compareInt(const void *data1, const void *data2) {
    // Cast void pointers to int pointers and compare their values.
    return *(const int *)data1 - *(const int *)data2;
}

/**
 * @brief Frees an integer (if it was dynamically allocated).
 *        For simple integers, this might just be 'free(data)'.
 *        Here, we assume the int itself was dynamically allocated.
 * @param data A void pointer to an integer.
 */
void freeInt(void *data) {
    // For dynamically allocated integers, free the memory.
    // If integers were stored directly (e.g., int value; addNode(&value);),
    // this function would be NULL or do nothing.
    free(data);
}

// --- Data-Specific Helper Functions (for strings) ---

/**
 * @brief Prints a string.
 * @param data A void pointer to a string (char *).
 */
void printString(void *data) {
    // Cast the void pointer back to a char pointer (string).
    printf("%s", (char *)data);
}

/**
 * @brief Compares two strings.
 * @param data1 A void pointer to the first string.
 * @param data2 A void pointer to the second string.
 * @return 0 if equal, non-zero otherwise (using strcmp).
 */
int compareString(const void *data1, const void *data2) {
    // Cast void pointers to char pointers and use strcmp.
    return strcmp((const char *)data1, (const char *)data2);
}

/**
 * @brief Frees a dynamically allocated string.
 * @param data A void pointer to a string.
 */
void freeString(void *data) {
    // Free the memory allocated for the string.
    free(data);
}

// --- Main Function: Demonstrating the Generic Linked List ---
int main() {
    printf("--- Demonstrating Generic Linked List with Integers ---\n");

    // Create a linked list for integers.
    // We pass the specific helper functions for integer handling.
    LinkedList *intList = createLinkedList(printInt, compareInt, freeInt);
    if (intList == NULL) {
        return EXIT_FAILURE;
    }

    // Dynamically allocate integers to store in the list.
    // This is crucial because the list stores pointers to data, not the data itself.
    int *num1 = (int *)malloc(sizeof(int)); *num1 = 10;
    int *num2 = (int *)malloc(sizeof(int)); *num2 = 20;
    int *num3 = (int *)malloc(sizeof(int)); *num3 = 30;
    int *num4 = (int *)malloc(sizeof(int)); *num4 = 40;

    // Add integers to the list.
    addNodeAtBeginning(intList, num1); // List: [10]
    addNodeAtBeginning(intList, num2); // List: [20, 10]
    addNodeAtBeginning(intList, num3); // List: [30, 20, 10]
    addNodeAtBeginning(intList, num4); // List: [40, 30, 20, 10]

    printList(intList); // Expected: List elements: [40, 30, 20, 10]

    // Find an integer
    int search_val_int = 20;
    int *found_int = (int *)findNode(intList, &search_val_int);
    if (found_int != NULL) {
        printf("Found integer: %d\n", *found_int);
    } else {
        printf("Integer %d not found.\n", search_val_int);
    }

    // Delete an integer
    int delete_val_int = 30;
    if (deleteNode(intList, &delete_val_int) == 0) {
        printf("Deleted integer: %d\n", delete_val_int);
    } else {
        printf("Integer %d not found for deletion.\n", delete_val_int);
    }
    printList(intList); // Expected: List elements: [40, 20, 10]

    // Delete the head
    int delete_head_int = 40;
    if (deleteNode(intList, &delete_head_int) == 0) {
        printf("Deleted integer: %d (head)\n", delete_head_int);
    } else {
        printf("Integer %d not found for deletion.\n", delete_head_int);
    }
    printList(intList); // Expected: List elements: [20, 10]

    // Destroy the integer list, freeing all allocated memory.
    destroyLinkedList(intList);
    printf("\n");

    printf("--- Demonstrating Generic Linked List with Strings ---\n");

    // Create a linked list for strings.
    // We pass the specific helper functions for string handling.
    LinkedList *stringList = createLinkedList(printString, compareString, freeString);
    if (stringList == NULL) {
        return EXIT_FAILURE;
    }

    // Dynamically allocate strings using strdup (which allocates memory).
    // This is important because the list will manage freeing this memory.
    char *str1 = strdup("Apple");
    char *str2 = strdup("Banana");
    char *str3 = strdup("Cherry");
    char *str4 = strdup("Date");

    // Add strings to the list.
    addNodeAtBeginning(stringList, str1); // List: ["Apple"]
    addNodeAtBeginning(stringList, str2); // List: ["Banana", "Apple"]
    addNodeAtBeginning(stringList, str3); // List: ["Cherry", "Banana", "Apple"]
    addNodeAtBeginning(stringList, str4); // List: ["Date", "Cherry", "Banana", "Apple"]

    printList(stringList); // Expected: List elements: [Date, Cherry, Banana, Apple]

    // Find a string
    char *search_str = "Banana";
    char *found_string = (char *)findNode(stringList, search_str);
    if (found_string != NULL) {
        printf("Found string: %s\n", found_string);
    } else {
        printf("String \"%s\" not found.\n", search_str);
    }

    // Delete a string
    char *delete_str = "Cherry";
    if (deleteNode(stringList, delete_str) == 0) {
        printf("Deleted string: %s\n", delete_str);
    } else {
        printf("String \"%s\" not found for deletion.\n", delete_str);
    }
    printList(stringList); // Expected: List elements: [Date, Banana, Apple]

    // Delete the head string
    char *delete_head_str = "Date";
    if (deleteNode(stringList, delete_head_str) == 0) {
        printf("Deleted string: %s (head)\n", delete_head_str);
    } else {
        printf("String \"%s\" not found for deletion.\n", delete_head_str);
    }
    printList(stringList); // Expected: List elements: [Banana, Apple]

    // Destroy the string list, freeing all allocated memory.
    destroyLinkedList(stringList);

    return EXIT_SUCCESS; // Indicate successful execution
}
