/************************************************************************************************
 
 Purpose of this file: This file is used for defining the structure of the nodes in the struct and declaring functions.
 STUDENT_FIRST_NAME_LENGTH - The maximum number of characters a student's first name can have
 STUDENT_SECOND_NAME_LENGTH - The maximum number of characters a student's second name can have
 STUDENT_ADDRESS_LENGTH - - The maximum number of characters a student's building address can have
 
*************************************************************************************************/
#ifndef PREMANIFLEXLIST_H
#define PREMANIFLEXLIST_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STUDENT_FIRST_NAME_LENGTH 61
#define STUDENT_SECOND_NAME_LENGTH 61
#define STUDENT_ADDRESS_LENGTH 16

#define SUCCESS 1
#define FAILURE 0

/*  
    Declaring and giving structure for nodes in the list
    studentFirstName - The student's first name.
    studentFirstName - The student's second name.
    studentIDNumber - The student's ID number
    studentAddressDorm - The name of the building in which the student resides
    studentAddressRoomNumber - The room number of the dorm in which which the students resides
    studentFlex - The amount of money a student has in his/her account in dollars. This will be input as cents but output as dollars.
 */
typedef struct nodeLink
{
    char studentFirstName[STUDENT_FIRST_NAME_LENGTH];
    char studentSecondName[STUDENT_SECOND_NAME_LENGTH];
    int studentIDNumber; //we assume that the IDs entered will be 5 digit numbers. We will not do data validation.
    char studentAddressDorm[STUDENT_ADDRESS_LENGTH];
    int studentAddressRoomNumber;
    unsigned int studentFlex;
    
    struct nodeLink *next;
    //Invariant: next is either null or points to the next node in the list
} studentRecord_t;


/*
    Insert newNode into the linked list as the first element in the list.
    Return failure if the parameter of NewNode is already in the list;
    else return success.
    head - the head of the list; a dummy node we assume exists.
    newNode - the node to be inserted; assume it is not null.
 */

//  adding a new node in the list
char addStudentRecord( studentRecord_t *head, studentRecord_t *newNode);



/*
    Search for a student record containing studentIDNumber in the student ID field.
    Return a pointer to the record, if found, otherwise return NULL
    head   - the head of the list; a dummy node not counted in the size.
    target - the student ID for which we are searching
 */
studentRecord_t * findStudent( studentRecord_t *head, int target);


/*
    Search for the number of records existing in the list and return that value.
    head - the head of the list; the dummy node not counted by the size
 */
int size(const studentRecord_t *head);


/*
    Delete a student record in the list with the specified ID number.
    head - the head of the list; a dummy node we assume exists
    studentIDNumber - the part number of the record to be deleted
    Return SUCCESS if the student record was deleted, otherwise return FAILURE.
 */
int deleteStudentRecord(studentRecord_t *head, int studentIDNumber);


/*
    Reduce the flex of the student record for studentNumber by the amount
    specified in count. Return failure if there is no such record in the list or if
    count is <= 0 or if the reduction would take the flex count below 0.
    head   - the head of the list; a dummy node not counted in the size.
    studentNumber - the student ID for the record to be updated
    count - the amount by which the flex is to be reduced; assume count > 0
 */
int MakeWithdrawal(studentRecord_t *head, int studentIDNumber, int count);


/*
    Increase the studentFlex count of the student record for studentIDNumber by the amount specified in count.
    Return failure if there is no such record in the list or if count is <= 0.
    head   - the head of the list; a dummy node not counted in the size.
    studentIDNumber - the student ID for the record to be updated
    count - the amount by which the flex is to be increased; assume count > 0
 */
int MakeDeposit(studentRecord_t *head, int studentIDNumber, int count);


/*
    Print information about the given student record to the file outfile specified.
    student - a reference to the student to print out
    FILE* - the file outfile to which to print the record information
 */
void printStudentRecord( FILE *outfile, const studentRecord_t *student);


/*
    Print information about each student record in the list to the file outfile specified.
    FILE* - the file outfile to which to print the record information
    head   - the head of the list; a dummy node not counted in the size.
 */
void printStudentRecordList( FILE *outfile, const studentRecord_t *head);


/*
    Get the amount of student flex for the student specified.
    head   - the head of the list; a dummy node not counted in the size.
    studentIDNumber - the student ID for the record whose flex we want to return.
    Return FAILURE if a record with the given studentIDNumber cannot be found; otherwise return student flex
 */
int getStudentFlex(studentRecord_t *head, int studentIDNumber);


#endif

