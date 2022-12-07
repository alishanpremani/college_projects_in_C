/************************************************************************************************
 
 Purpose of this file: This file is used for defining and making functions.
 The function definitions and their respective parameter definitions have been defined before each function in the file.

 *************************************************************************************************/


#include "PremaniFlexList.h" // Want to include the file that contains all the function and struct declarations.


/*
    Insert newNode into the linked list as the first element in the list.
    Return failure if the parameter of NewNode is already in the list;
    Else return success.
    head - the head of the list; a dummy node we assume exists.
    newNode - the node to be inserted; assume it is not null.
 */
char addStudentRecord( studentRecord_t *head, studentRecord_t *newNode )
{
    if (findStudent(head, newNode->studentIDNumber) == NULL) //define what happens in findStudent!!!
    {
        newNode->next = head->next;
        head->next = newNode;
        
        return SUCCESS;
    }
    else
        return FAILURE;
}


/*
    Search for a part record containing pnum in the part number field.
    Return a pointer to the record, if found, otherwise return NULL
    head   - the head of the list; a dummy node not counted in the size.
    target - the part number for which we are searching
 */
studentRecord_t * findStudent( studentRecord_t *head, int target)
{
    studentRecord_t *ptr = head->next;
    
    while ( ptr != NULL )
    {
        if(ptr->studentIDNumber == target)
            return ptr;   // success!!!
        else
            ptr = ptr->next;
    }
    
    return NULL;  // didn't find the part
}


/*
    Search for the number of records existing in the list and return that value.
    head - the head of the list; the dummy node not counted by the size
 */
int size(const studentRecord_t *head)
{
    studentRecord_t *ptr = head->next;
    int count = 0;
    
    while (ptr != NULL) {
        count++;
        ptr = ptr->next;
    }
    return count;
}


/*
    Delete a student record in the list with the specified ID number.
    head - the head of the list; a dummy node we assume exists
    studentIDNumber - the part number of the record to be deleted
    Return SUCCESS if the student record was deleted, otherwise return FAILURE.
 */
int deleteStudentRecord(studentRecord_t *head, int studentIDNumber)
{
    studentRecord_t *prevptr = head, *ptr = head->next;
    
    while (ptr != NULL && (ptr->studentIDNumber != studentIDNumber))
    {
        prevptr = ptr;
        ptr = ptr->next;
    }
    if (ptr == NULL) {
        return FAILURE; // The search failed
    }
    prevptr->next = ptr->next;  // The search succeeded
    free(ptr);
    
    return SUCCESS;
}


/*
    Reduce the studentFlex count of the student record for studentIDNumber by the amount
    specified in count. Return failure if there is no such record in the list or if
    count is <= 0 or if the reduction would take the studentFlex count below 0.
    head   - the head of the list; a dummy node not counted in the size.
    studentIDNumber - the student ID for the record to be updated
    count - the amount by which the flex is to be reduced; assume count > 0
 */
int MakeWithdrawal(studentRecord_t *head, int studentIDNumber, int count)
{
    studentRecord_t *ptr = findStudent(head, studentIDNumber);
    
    if (ptr == NULL || count <= 0 || ptr->studentFlex < count)
        return FAILURE;
    
    ptr->studentFlex -= count;
    
    return SUCCESS;
}


/*
    Increase the studentFlex count of the student record for studentIDNumber by the amount specified in count.
    Return failure if there is no such record in the list or if count is <= 0.
    head   - the head of the list; a dummy node not counted in the size.
    studentIDNumber - the student ID for the record to be updated
    count - the count by which the flex is to be increased; assume count > 0
 */
int MakeDeposit(studentRecord_t *head, int studentIDNumber, int count)
{
    studentRecord_t *ptr = findStudent(head, studentIDNumber);
    
    if (ptr == NULL || count <= 0)
        return FAILURE;
    
    ptr->studentFlex += count;
    
    return SUCCESS;
}


/*
    Print information about the given student record to the file outfile specified.
    student - a reference to the student to print out
    FILE* - the file outfile to which to print the record information
 */
void printStudentRecord( FILE *outfile, const studentRecord_t *student)
{
    if ( outfile == NULL || student == NULL) return;
    fprintf(outfile, "Student Name: %s %s\nStudent ID: %d\nStudent Address: %s %d\nStudent Flex: $%.2f\n\n",
            student->studentFirstName, student->studentSecondName, student->studentIDNumber, student->studentAddressDorm, student->studentAddressRoomNumber, student->studentFlex/100.0);
}


/*
    Print information about each part record in the list to the file outfile specified.
    FILE* - the file outfile to which to print the record information
    head   - the head of the list; a dummy node not counted in the size.
 */
void printStudentRecordList( FILE *outfile, const studentRecord_t *head)
{
    const studentRecord_t *ptr = head->next;
    while ( ptr != NULL )
    {
        printStudentRecord(outfile, ptr);
        ptr = ptr->next;
    }
}


/*
    Get the amount of student flex for the student specified.
    head   - the head of the list; a dummy node not counted in the size.
    studentIDNumber - the student ID for the record whose flex we want to return.
    Return FAILURE if a record with the given studentIDNumber cannot be found; otherwise return student flex
 */
int getStudentFlex(studentRecord_t *head, int studentIDNumber)
{
    studentRecord_t *ptr = findStudent(head, studentIDNumber);
    
    if (ptr == NULL)
        return FAILURE;
    return ptr->studentFlex;
}
