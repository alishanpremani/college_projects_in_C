
/*--------------------------------------------------------------------------------------------------------------------------------
 Project 3 - Multiple Choice Grader

 Author: Alishan Premani
 Date: 09/04/2015

 Purpose: The purpose of this project is to grade Science quizzes that Professor Proton's students complete and assign a score to each of the students, and also to see which questions were missed by the most students.
 
 Input: The input file should include the following in order
 1) the total number of questions followed by a space
 2) the answer key
 3) the ID numbers and answers of each of the students listed on a separate line
 
 Sample Input:
    5 dbbac
    111 dabac
    102 dcbdc
    251 dbbac
 
 Output: The output file would contain in that order
 1) The name of the one who has made the program followed by two carriage returns
 2) The words 'Quiz Report'
 3) The word 'Question' followed by the integers 1 to the number of questions
 4) The answer key listed below their respective question numbers
 5) The IDs and Scores of each of the students
 6) The word 'Question' followed by the integers 1 to the number of questions
 7) The words 'Missed by' followed by the respective number of total questions missed under their question number
 
 Sample Output:
    Simon Gray
 
            Quiz Report
    Question 1  2  3  4  5
    Answer   d  b  b  a  c
 
    ID     Score(%)
    111      80
    102      60
    251     100
 
    Question   1  2  3  4  5
    Missed by  0  2  0  1  0
 
 Description for the variables and arrays used:
    int studentID: represents the student Id for the students
    int numberOfQs: represents the total number of questions in the quiz
    int numberOfAnswersCorrect: the total number of correct answers in a student's completed quiz
    int scores: The scores in percentage achieved by each student in their quiz
 
    char * key: An array representing the answer key
    char * studentAnswers: An array of the answers of each student
    int * missedQuestions: An array of the questions missed by all students in total for each question in the quiz
 
 Descriptions for the functions used:
    getAnswers: reads in the answers for one student
    gradeQuiz: 'grades' the students based on their answers and gives a value for how many correct answers each student has achieved
--------------------------------------------------------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PERCENTAGE 100

void getAnswers(FILE * infile, int numberOfQs, char studentAnswers[]);
int gradeQuiz(char key[], char studentAnswers[], int missedQuestions[], int numberOfQs);


int main(int argc, const char * argv[]) {
   
    int studentID;
    int numberOfQs;
    int numberOfAnswersCorrect;
    int scores;
    
    char * key;
    char * studentAnswers;
    int * missedQuestions;
    
    FILE * infile;
    FILE * outfile;
    
    if ((infile = fopen("quizdata.txt", "r")) == NULL) {
        printf("Error in opening input file for reading.\n");
        return EXIT_FAILURE;
    }
        // File is open for reading
    
    if ((outfile = fopen("PremaniReport.txt", "w")) == NULL){
        printf("Error in opening output file for writing.\n");
        fclose(infile);  // The infile successfully opened, so we have to close it
        return EXIT_FAILURE;
    }
        // File is open for writing
    
    // read in the number of questions
    fscanf(infile, "%d " ,&numberOfQs);

    // now we dynamically allocate memory for each of the arrays as we do not know how much memory will be needed by the user
    key = (char *) malloc(sizeof(char) * numberOfQs);
    studentAnswers = (char *) malloc(sizeof(char) * numberOfQs);
    missedQuestions = (int *) malloc(sizeof(int) * numberOfQs);
    
    // initializing the arrays
    for (int i = 0; i < numberOfQs; i++)
    {
        key[i] = ' ';
        studentAnswers[i] = ' ';
        missedQuestions[i] = 0;
    }
    
    // read in the answer key and store it in an array
    for (int i = 0; i < numberOfQs; i++) {
        fscanf(infile, " %c", &key[i]);
    }
    
    // printing the header
    fprintf(outfile, "Alishan Premani\n\n\t  Quiz Report\nQuestion ");
    
    // printing the line for the number of questions
    for (int i = 0; i < numberOfQs; i++) {
        fprintf(outfile, "%d  ", i + 1);
    }
    
    // printing the answer key
    fprintf(outfile, "\nAnswer   ");
    for (int i = 0; i < numberOfQs; i++) {
        fprintf(outfile, "%c  ", key[i]);
    }
    
    fprintf(outfile, "\n\n");
    
    fprintf(outfile, "ID\t\tScore(%%)\n");
    
    // read in the student id and create a loop that stays keep runnning till file is empty
     while ((fscanf(infile, "%d", &studentID)) != EOF) {
         
         // call function getAnswers
         getAnswers(infile, numberOfQs, studentAnswers);
         
         // call function gradeQuiz
         numberOfAnswersCorrect = gradeQuiz(key, studentAnswers, missedQuestions, numberOfQs);
         
         // calculate the score for each student
         scores = (numberOfAnswersCorrect * PERCENTAGE) / (float)numberOfQs ;
         
         // output the ID and the score
         fprintf(outfile, "%d\t\t  %d\n", studentID, scores);
     }
    
    // printing the line for the number of questions
    fprintf(outfile, "\nQuestion   ");
    for (int i = 0; i < numberOfQs; i++) {
        fprintf(outfile, "%d  ", i + 1);
    }
    
    // printing the number of times each question was missed by all students
    fprintf(outfile, "\nMissed by ");
    for (int i = 0; i < numberOfQs; i++) {
        fprintf(outfile, " %d ", missedQuestions[i]);
    }
    
    // the program was successful, now closing both the files
    fclose(infile);
    fclose(outfile);
    
    return EXIT_SUCCESS;
}

void getAnswers(FILE * infile, int numberOfQs, char studentAnswers[]){
    
    // reading in the answers for one student
    for (int i = 0; i < numberOfQs; i++) {
        fscanf(infile, " %c", &studentAnswers[i]);
    }
}

int gradeQuiz(char key[], char studentAnswers[], int missedQuestions[], int numberOfQs){
    
    int numberOfAnswersCorrect = 0;
    
    for (int i = 0; i < numberOfQs; i++) {
        
        if(studentAnswers[i] != key[i]){ // statement to evaluate 'points' to each student for their correct answers
            missedQuestions[i]++;
        }
        else{
            numberOfAnswersCorrect++;
        }
    }
    return numberOfAnswersCorrect;
}
