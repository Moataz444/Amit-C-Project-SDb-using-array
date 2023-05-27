#include <stdio.h>
#include <stdlib.h>
#include "SDB.h"
#define max_size 10 // database maximum size
uint32 id; // to store current id to be used
uint8 count= 0; // start database with 0 elements
uint32 list[10]; // list to contain all students id's
uint32 position; // a temporary used to give wanted position in database

student Students_db[max_size] ; // main database an array of structs

uint32 Enter_Id() // a function scan id from user
{
    printf("\nEnter Student_ID\n");
    scanf("%d",&id);
    return id;
}

bool isGrade_Ok(uint32 grade) // check if course grade is to store it
{
    if(grade>=0 && grade <=100)
        return true;
    else
    {
        printf("\nWrong Grade try again\n");
        return false;
    }
}

bool SDB_IsFull ()
//Description: check if the database is full or not.
//Return: if the database is full return true else return false
{
    if(count==max_size) // check if full (max = 10)
    {
        printf("\nDatabase is Full\n");
        return true;
    }
    else
    {
        return false;
    }
}

uint8 SDB_GetUsedSize()
//Description: get how many students in your database have added
//Return: Return the number of students in the database.
 {
    printf("\nNumber of Students in database = %d\n", count);
 }

 bool SDB_AddEntry() // add to linked list
// Description: this function asks user to add one student to the database with the required data
//(Student_ID, Student_year, Course1_ID,Course1_grade, Course2_ID, Course2_grade, Course3_ID,  Course3_grade)

//check if the database is full or not

//Return:
//return 1 if the data is added successfully
//return 0 if the data entered by user is not correct
{
    // bool success=true; //used to indicate if data is correct or not
    uint32 Student_ID;// to store id to check it
    uint32 grade; // to store grade and check it

    if(SDB_IsFull()!=true) // if database is not full to add entry
    {
        Student_ID=Enter_Id();
        while(1) // check if id already exists
        {
            if(SDB_IsIdExist(Student_ID)!= true) // if id doesn't exists
            {
                Students_db[count].Student_ID = Student_ID; // then store id and data
                printf("Pass\n");
                break; // stops the loop
            }
            else // else re-enter id
            {
                printf("ERROR : Invalid ID enter a valid id\n");
                Student_ID=Enter_Id();
            }
        }
        printf("\nEnter Student year\n");
        scanf("%d",&Students_db[count].Student_year);

        printf("\nEnter Course1 ID\n");
        scanf("%d",&Students_db[count].Course1_ID);

        while(1) // check Course1 grade
        {
            printf("\nEnter Course1 grade\n");
            scanf("%d",&grade);
            if(isGrade_Ok(grade))
            {
                Students_db[count].Course1_grade= grade;
                break;
            }

        }

        printf("\nEnter Course2 ID\n");
        scanf("%d",&Students_db[count].Course2_ID);

        while(1) // check Course2 grade
        {
            printf("\nEnter Course2 grade\n");
            scanf("%d",&grade);
            if(isGrade_Ok(grade))
            {
                Students_db[count].Course2_grade= grade;
                break;
            }

        }

        printf("\nEnter Course3 ID\n");
        scanf("%d",&Students_db[count].Course3_ID);

        while(1) // check Course3 grade
        {
            printf("\nEnter Course3 grade\n");
            scanf("%d",&grade);
            if(isGrade_Ok(grade))
            {
                Students_db[count].Course3_grade= grade;
                break;
            }

        }

        count++; // increase count of students
        return true; //Added Successfully
    }

    else // if not successfull
    {
        return false;
    }
}


 void SDB_DeletEntry (uint32 id)
//Description: delete the student data with the given id.
{

    if(SDB_IsIdExist(id)) // check if id exist store it's position to delete it
    {
        // free(Students_db[position]);   // can be used but it will also delete the struct and its name

        Students_db[position].Student_ID = NULL; // delete the wanted by = null id cause we search by id and the rest = garbage

        uint32 i;
        for(i=0; (i<count-1 ) ; i++) // loop reorder database after deletion
        {
            Students_db[position]=Students_db[position+1];  // make deleted position = next to fill the gap
            Students_db[position+1].Student_ID = NULL; // then delete next to not duplicate
            position++;
        }

        printf("\nDeleted Successfully\n");
        count--;  // decrease count of students
    }
}

 bool SDB_ReadEntry (uint32 id)
//Description: print the data of the user by searching on his data by the given id
//Return: return 1 if the data is existed return 0 if this id not your database.
 {
     if(SDB_IsIdExist(id))// check if realy exists then print
     {
        printf("\nStudent ID = %d \n",Students_db[position].Student_ID);
        printf("Student year = %d \n",Students_db[position].Student_year);
        printf("Course1 ID = %d \n",Students_db[position].Course1_ID);
        printf("Course1 grade = %d \n",Students_db[position].Course1_grade);
        printf("Course2 ID = %d \n",Students_db[position].Course2_ID);
        printf("Course2 grade = %d \n",Students_db[position].Course2_grade);
        printf("Course3 ID = %d \n",Students_db[position].Course3_ID);
        printf("Course3 grade = %d \n",Students_db[position].Course3_grade);

        return true; // data exists
     }
     else
     {
         return false; //data does'nt exist
     }
 }

 void SDB_GetList (uint8 * count, uint32 * list) //using pointers
//Description: it gets the number of ids in the
//count and the list of all ids in list array that’s you get his base address.
 {
     if(count>0) // check if database is not empty
     {
         printf("\nList of Students id = {");
         uint32 i;
         for( i=0 ; i<count ; i++)
           {
               printf(" %d"  , Students_db[i].Student_ID );
               if(i<count-1)
               {
                   printf(",");
               }
           }
         printf(" }\n");
     }
 }

 bool SDB_IsIdExist (uint32 id)
//Description: Checks if the given id realy is Exists
//Return: return 1 if the id is existed and return 0 if the id not found.
{
    if(count!=0) // check id database is not empty
    {
        uint32 j;
        for(j=0 ; (j<count ) ; j++)
      {
        if(Students_db[j].Student_ID == id)
        {
            printf("\nId Exists\n");
            position = j; // store found position
            return true; // found
        }
        else if(j == count-1) // if reached end and still not found
        {
            printf("\nId Not Found\n");
            return false; // not found
        }
      }
    }

    else
    {
        printf("\nId Not Found\n");
        return false; // not found
    }
}

