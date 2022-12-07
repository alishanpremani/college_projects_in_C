/************************************************************************************************
 
 PROJECT 4 : FLEX CARD MANAGEMENT
 AUTHOR : ALISHAN PREMANI
 CLASS : CS 110
 PROFESSOR: DR. GRAY
 DATE : APRIL 30, 2015
 
 Purpose of this project: To make, store and implement different operations on a student record holding each student's details such as their name, ID number, address and the flex in their account. The operations are specified in the command definition.
 
 Purpose of this file: This file is used for giving the structure of the different cases and calling the functions appropriately to carry out the tasks.
 
 int command : The integer values that represent each case given in the description below. It is used to call and hence use the different specifications of the program.
    0 : Display information from all records in the list
    1 : Add a record - the information for the record fields will be provided, given in the order specified in the struct
    2 : Delete a record - the Student ID of the record to delete will be provided
    3 : Search for a record - the student ID of the record to search will be provided
    4 : Withdraw - the student ID and the amount of flex to be withdrawn will be provided
    5 : Deposit - the student ID and the amount of flex to be deposited will be provided
    6 : Get balance - the student ID of the account will be provided
    7 : Size: Display the number of records in the list
    8 : Quit the program.
 
 int done = 0 : a variable for command 8 to quit the program when the user is done using it.
 
 int count : a variable representing the amount of flex a student needs deposited or withdrawn depending upon the user's needs.
 
 int result : A variable representing the current flex balance of a student.
 
 studentRecord_t *head : This pointer with type studentRecord_t is the head of the list; a dummy node not counted in the size.

 studentRecod_t *student : This pointer with type studentRecord_t is a function return value pointer in those functions, which return the whole record of any student. It is used to access the record details of the student.
 
 FILE *infile - A file from which the input commands will be taken
 FILE *outfile - The file to which the input from infile will be processed and shown as output
 
 *************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "PremaniFlexList.h"

int main(int argc, const char * argv[]) {
    
    studentRecord_t *head = (studentRecord_t *)malloc(sizeof(studentRecord_t)); // Dynamically allocating memory to head as per the need of the size of the record.
    
    int command, done = 0, count, result;
    head->next = NULL;
    int studentIDNumber;
    
    studentRecord_t *student;
    
    FILE *infile;
    FILE *outfile;
    
    if ((infile = fopen("FlexData.txt", "r")) == NULL){
        printf("Error in opening input file for reading.\n");
        return EXIT_FAILURE;
    }
    // File is open for reading
    
    if ((outfile = fopen("PremaniReport.txt", "w")) == NULL){
        printf("Error in opening output file for writing.\n");
        fclose(infile);
        return EXIT_FAILURE;
    }
    // File is open for writing
    
    while (!done) {
        //printf("Please enter command number (8 to quit): \n");
        fscanf(infile, "%d", &command);
        
        switch (command) { // To allow for the choice to choose whichever operation the user wants to implement in the program
            case 0 :
                printStudentRecordList(outfile, head);
                break;
                
            case 1 : //add a new student record
                student = (studentRecord_t *)malloc(sizeof(studentRecord_t));
                fscanf(infile, "%s %s %d %s %d %d", student->studentFirstName, student->studentSecondName, &(student->studentIDNumber), student->studentAddressDorm, &(student->studentAddressRoomNumber), &(student->studentFlex));
                student->next = NULL;
                if (addStudentRecord(head, student)) {
                    fprintf(outfile, "Student with ID %d added in the record!\n\n", student->studentIDNumber);
                }
                else{
                    fprintf(outfile, "Error: the student with ID %d is already in the list.\n\n", student->studentIDNumber);
                }
                break;
                
            case 2 : //delete a part record
                fscanf(infile, "%d", &studentIDNumber);
                if (deleteStudentRecord(head, studentIDNumber) == SUCCESS)
                    fprintf(outfile, "Successfully deleted record for student with ID %d!\n\n", studentIDNumber);
                else
                    fprintf(outfile, "Error: student not in the list.\n\n");
                break;
            
            case 3 : // Search for a student record
                fscanf(infile, "%d", &studentIDNumber);
                student = findStudent(head, studentIDNumber); // Successfully found the student
                printStudentRecord(outfile, student);
                break;
                
            case 4 : // Make a withdrawal
                fscanf(infile, "%d %d", &studentIDNumber, &count);
                if (MakeWithdrawal(head, studentIDNumber, count) == SUCCESS)
                    fprintf(outfile, "Student flex for %d reduced by $%.2f.\n\n",
                            studentIDNumber, count/100.0);
                else
                    fprintf(outfile, "Error: the student is not in the list or there is a problem with the student flex\n\n");
                break;
                
            case 5 : // Make a deposit
                fscanf(infile, "%d %d", &studentIDNumber, &count);
                if (MakeDeposit(head, studentIDNumber, count) == SUCCESS)
                    fprintf(outfile, "Student flex for %d increased by $%.2f.\n\n",
                            studentIDNumber, count/100.0);
                else
                    fprintf(outfile, "Error: the student is not in the list or there is a problem with the student flex!\n\n");
                break;
                
            case 6 : // Get the balance of a student
                fscanf(infile, "%d", &studentIDNumber);
                result = getStudentFlex(head, studentIDNumber);
                if (result != FAILURE) {
                    fprintf(outfile, "The student flex for student %d is $%.2f\n\n.", studentIDNumber, result/100.0);
                }
                else fprintf(outfile, "Error: The student is not in the list!\n\n");
                break;
                
            case 7 : //Get the size of the list
                fprintf(outfile, "The number of students in the record is %d.\n\n", size(head));
                break;
                
            case 8:
                done = 1;
                break;
                
            default : fprintf(outfile, "Error: Invalid command!\n\n");
                break;
        }
    }
    fclose(infile);
    fclose(outfile);
    }
