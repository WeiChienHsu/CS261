/* CS261- Assignment 1 - Q.1*/
/* Name: Wei-Chien Hsu
 * Date: 07/01/18
 * Solution description:
 * 1. Write a function struct student* allocate () that allocates memory for 
 * ten students and returns the pointer.
 * 
 * 2. Write a function void generate (struct student* students) that generates random 
 * IDs and scores for each of the ten students and stores them in the array of students. 
 * Ensure that IDs are unique also and between 1 and 10 (both inclusive) and scores are 
 * between 0 and 100 (both inclusive). To generate unique IDs you can either use the 
 * brute-force random/check/repeat (generate a random integer between 1- 10 and then
 * confirm that it hasn't been used yet for a student ID) or you can use the Fisher 
 * Yates shuffle -(https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle).
 * 
 * 3. Write a function void output (struct student* students) that prints the IDs and scores 
 * of all the students. The output of the function needs not to be sorted.
 * 
 * 4. Write a function void summary (struct student* students) that prints the minimum score, 
 * maximum score and average score of the ten students.
 * 
 * 5. Write a function void deallocate (struct student* stud) that frees the memory allocated 
 * to students. Check that students is not NULL (NULL== 0) before you attempt to free it.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct student{
	int id;
	int score;
};

struct student* allocate(){
     /*Allocate memory for ten students*/
     struct student *students = malloc(10 * sizeof(struct student));
     /*Return the pointer*/
     return students;
}

void generate(struct student* students){
     /*Generate random and unique IDs and random scores for ten students, 
     IDs being between 1 and 10, scores between 0 and 100*/
    /* Give a random seed by current TIME */
     srand(time(0));
     
     // Loop through the student array
     for(int i = 0; i < 10; i++) {
         // Get a random number [1, 10] (Both inclusive)
         int tempRandomId = (rand() % 10) + 1;
         // Check if tempRandomId has already existed in students array by looping original array
         for(int j = 0; j < 10; j++) {
             // If there is a tempRandomId inside, give a new random number and re-use the loop for checking
             if(students[j].id == tempRandomId ) {
                tempRandomId = (rand() % 10) + 1;
                // Re-start the loop to check duplicated id
                j = -1;
             }
         }
         // Assign the unique number into students array and specified to the id property
         students[i].id = tempRandomId;
         // Get a random number [0, 100] (Both inclusive)
         int randomScore = (rand() % 101);
         // Assign the score into students array and specified to the score property
         students[i].score = randomScore;
     }
}

void output(struct student* students){
     /*Output information about the ten students in the format:
              ID1 Score1
              ID2 score2
              ID3 score3
              ...
              ID10 score10*/
    // Print information about the ten students
    for(int i = 0; i < 10; i++) {
        printf("ID%d Score%d \n", students[i].id, students[i].score);
    }
}

void summary(struct student* students){
     /*Compute and print the minimum, maximum and average scores of the 
    ten students*/
    int min = 100;
    int max = 0;
    int sum = 0;
    double average = 0.0;

    // Get the min and max of students array and count the sum
    for(int i = 0; i < 10; i++) {
        // Get the current student socre
        int currentStudentScore = students[i].score;
        sum += currentStudentScore;
        // Compare the current value with the current min value
        if(min > currentStudentScore) {
            min = currentStudentScore;
        }
        // Compare the current value with the current max value
        if(max < currentStudentScore) {
            max = currentStudentScore;
        }
    }

    average = sum / 10.0;

    // Print the results
    printf("Minimum score : %d \n", min);
    printf("Maximum score : %d \n", max);
    printf("Average score : %f \n", average);
}

void deallocate(struct student* stud){
     /*Deallocate memory from stud*/
     free(stud);
}

int main(){
    struct student* st = 0;
    
    /*Call allocate*/
    st = allocate();
    /*Call generate*/
    generate(st);
    /*Call output*/
    output(st);
    /*Call summary*/
    summary(st);
    /*Call deallocate*/
    deallocate(st);
    return 0;
}

