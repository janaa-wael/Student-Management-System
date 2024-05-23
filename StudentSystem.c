#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "STD_TYPES.h"
#include "StudentSystem.h"



 u32 num_students ;

void main_menu()
{
	int choice1;
	do{
		printf("\n-------------------------------------\nWelcome to the Student Management System :) !\n");
		printf("%cChoose from the menu:\n1-Add Student\n2-Delete Student\n3-View All Students\n4-Search for a student\n5-Edit Student Info\n6-Calculate GPA of student\n7-Sort students according to GPA\n8-Exit\n",7);
		scanf("%d",&choice1);
		switch(choice1)
		{
			case 1 :
				add_std();
				break;
			case 2 :
				delete_std();
				break;
			case 3 :
				view_students();
				break;
            case 4 :
                search_std();
                break;
            case 5 :
                edit_std();
                break;
            case 6 :
                get_std_gpa();
                break;
            case 7 :
                sort_std();
                break;
			case 8 :
				printf("\nExiting Program ...");
				break;
			default :
				printf("Invalid Input, Please try again :( \n");
		}
	}while(choice1!=8);
}


void add_std()
{
	num_students++;
	f32 gpa = 0;

	u8 name[100][100];
	u32 credit_pts = 0;
	printf("Enter student name\n");
	scanf(" %[^\n]s",student_names[num_students-1]);
	printf("Enter number of courses the student has registered\n");
	scanf(" %d",&num_courses[num_students-1]);
	printf("Enter Student Courses\n");
	for(u32 i = 0 ; i < num_courses[num_students-1] ; i++)
	{
		printf("\nEnter course %d:",i+1);
		scanf(" %[^\n]s",student_courses[num_students-1][i]);
		printf("\nEnter grade of %s course: ",student_courses[num_students-1][i]);
		scanf(" %f",&student_grades[num_students-1][i]);
		printf("\nEnter the number of CH of %s course\n",student_courses[num_students-1][i]);
		scanf(" %d",&credit_hrs[num_students-1][i]);
		gpa+= credit_hrs[num_students-1][i]*student_grades[num_students-1][i];
		credit_pts += credit_hrs[num_students-1][i]*4;;
	}
	printf("\nStudent successfully registered!%c\n",7);
	printf("\nStudent name : %s",student_names[num_students-1]);
	for(u32 i = 0 ; i < num_courses[num_students-1] ; i++)
	{
		printf("\nCourse %d : \n",i+1);
        printf("\nName : %s\nGrade : %.2f\nCH : %d\n",student_courses[num_students-1][i],student_grades[num_students-1][i],credit_hrs[num_students-1][i]);
	}
	std_gpa[num_students-1] = gpa_calc(student_names[num_students-1]) ;
}

void delete_std()
{
    u8 student_delete[100];
    u32 index,y;
    printf("\nEnter student name: ");
    scanf(" %[^\n]s",student_delete);
    index = int_search_id(student_delete);
    y = check_std_found(student_delete);

    if(y!=1 && index==-1)
        printf("\nStudent doesn't exist");
    else
    {
        for(u32 i = index; i < num_students ; i++)
        {
            strcpy(student_names[i],student_names[i+1]);
            num_courses[i] = num_courses[i+1];
			std_gpa[i] = std_gpa[i+1];
            for(u32 j = 0 ; j < 100 ; j++)
            {
                student_grades[i][j] = student_grades[i+1][j];
                credit_hrs[i][j] = credit_hrs[i+1][j];
                strcpy(student_courses[i][j],student_courses[i+1][j]);
            }
        }
		num_courses[num_students-1] = 0;
		std_gpa[num_students-1] = 0;
		num_courses[num_students-1] = 0;
		for(u32 j = 0 ; j < 100 ; j++)
		{
		student_grades[num_students-1][j] = 0;
		student_courses[num_students-1][j][0] = '\0';
		credit_hrs[num_students-1][j] = 0;
		}
        num_students--;
    }
}

void view_students()
{
	if(num_students == 0)
		printf("\nNo Students are registered on the system\n");
	else
	{
		printf("\nAll students registered on the system:\n------------------------------------\n");
		for(u32 i = 0 ; i < num_students ; i++)
		{
			printf("\nStudent Name: %s\n",student_names[i]);
			for(u32 j = 0 ; j < num_courses[i]; j++)
			{
				printf("Course %d:\n",j+1);
				printf("Name: %s\nGrade: %.2f\nCredit Hrs: %d\n",student_courses[i][j],student_grades[i][j],credit_hrs[i][j]);
				printf("------------------------------------\n");
			}
		}
	}
    
}


void search_std()
{
    u8 target_std[100];
    u32 y;
    printf("\nEnter the name of student : ");
    scanf(" %[^\n]s",target_std);

    for(u32 i = 0 ; i < num_students ; i++)
    {
        y = strcmp(strlwr(target_std),strlwr(student_names[i]));
        if(y==0)
        {
            int index = i;
            printf("\nStudent Found :)\nStudent Info:\n---------------\n");
            view_student(index);
            break;
        }

    }
    if(y!=0)
        printf("\nStudent not found :(");
}


u32 int_search_id(u8 search_student[100])
{
    u32 y,index;
     for(int i = 0 ; i < num_students ; i++)
     {
        y = strcmp(strlwr(search_student),strlwr(student_names[i]));
        if(y==0)
        {
            index = i;
            break;
        }
        else
            index=-1;
     }
    return index;
}

u32 check_std_found(u8 search_student[100])
{
    u32 y;
     for(u32 i = 0 ; i < num_students ; i++)
    {
        y = strcmp(strlwr(student_names[i]),strlwr(search_student));
        if(y==0)
        {
            return 1;
        }
        else
        {
    
            return -1;
        }
    }
}

void view_student(u32 id)
{
    printf("\nStudent Name: %s\n",student_names[id]);
    for(u32 j = 0 ; j < num_courses[id]; j++)
        {
            printf("Course %d:\n",j+1);
            printf("Name: %s\nGrade: %.2f\nCredit Hrs: %d\n",student_courses[id][j],student_grades[id][j],credit_hrs[id][j]);
            printf("------------------------------------\n");
        }
}
void get_std_gpa()
{
	u8 student_gpa[100];
	printf("\nEnter Student Name: ");
	scanf(" %[^\n]s",student_gpa);
	u32 index = int_search_id(student_gpa);
	u32 y = check_std_found(student_gpa);
	if(y!= 1 && index == -1)
		printf("\nStudent doesn't exist\n");
	else
	{
		std_gpa[index] = gpa_calc(student_gpa);
		printf("GPA of %s = %.3f",student_names[index],std_gpa[index]);
	}
}

f32 gpa_calc(u8 std_gpa[100])
{
    u32 sum_credit_hrs = 0;
    f32 credit_pts = 0 ;
    u32 index = int_search_id(std_gpa);
    u32 y = check_std_found(std_gpa);
    for(u32 i = 0 ; i < num_courses[index] ; i++)
        {
            credit_pts += credit_hrs[index][i]*student_grades[index][i];
            sum_credit_hrs += credit_hrs[index][i];
        }
        return credit_pts/sum_credit_hrs;
}


void edit_std()
{
    u8 search_student[100],user_input[100];
    u32 y,index,choice,crs_index;
    f32 grade_edit;
    u32 credit_hr;
    printf("\nEnter student name: ");
    scanf(" %[^\n]s",search_student);
    y = check_std_found(search_student);
    index = int_search_id(search_student); 
	
	if(y!=1 && index==-1)
	{
		printf("\nStudent hasn't regsitered any courses yet.\n");
	}
	else
	{
		printf("\n1-Edit Student Name\n2-Edit Course Name\n3-Edit Course Grade\n4-Edit Course Credit Hours\n5-Edit All Student Info\n6-Add Course\n7-Drop Course\n8-Exit\n");
		scanf(" %d",&choice);
			switch(choice)
			{
				case 1: 
					printf("\nEdit student's name: ");
					scanf(" %[^\n]s",user_input);
					strcpy(student_names[index],user_input);
					printf("\nName successfully edited\n");
					break;
				case 2:
					printf("\nEnter student course name to be edited");
					scanf(" %[^\n]s",user_input);
					crs_index = find_course_index(user_input,index);
					printf("\nEnter the updated course name : ");
					scanf(" %[^\n]s",user_input);
					strcpy(student_courses[index][crs_index],user_input);
					break;
				case 3:
					printf("\nEnter student course name to be edited");
					scanf(" %[^\n]s",user_input);
					crs_index = find_course_index(user_input,index);
					printf("\nEnter the updated course grade : ");
					scanf(" %f",&grade_edit);
					student_grades[index][crs_index] = grade_edit;
					break;
				case 4:
					printf("\nEnter student course name to be edited");
					scanf(" %[^\n]s",user_input);
					crs_index = find_course_index(user_input,index);
					printf("\nEnter the updated %s's credit hours weight: ",student_courses[index][crs_index]);
					scanf(" %d",&credit_hr);
					credit_hrs[index][crs_index] = credit_hr;
					break;
					
				case 5 : 
				    edit_all_std_info(index);
					break;
				case 6 :
					add_course(index);
					break;
				case 7 :
					drop_course(index);
					break;
				case 8 : 
					printf("\nExiting Sub-Menu ... \n");
					break;
			}	
	}
}


void sort_std()
{
	for(u32 i = 0 ; i < 100-1 ; i++)
	{
		for(u32 j = 0 ; j < num_students - i - 1 ; j++)
		{
			if(std_gpa[j] > std_gpa[j+1])
			{
				u32 temp;
				u8 std_name_temp[100];
				
				temp = std_gpa[j];
				std_gpa[j] = std_gpa[j+1];
				std_gpa[j+1] = temp;
				
				temp = num_courses[j];
				num_courses[j] = num_courses[j+1];
				num_courses[j+1] = temp;
				
				strcpy(std_name_temp,student_names[j]);
				strcpy(student_names[j],student_names[j+1]);
				strcpy(student_names[j+1],std_name_temp);
				
				for(u32 k = 0 ; k < 100; k++)
				{
					u8 std_course_temp[100];
					u32 credit_hours_temp;
					f32 std_grade_temp;
					
					credit_hours_temp = credit_hrs[j][k];
					credit_hrs[j][k] = credit_hrs[j+1][k];
					credit_hrs[j+1][k] = credit_hours_temp;
					
					strcpy(std_course_temp,student_courses[j][k]);
					strcpy(student_courses[j][k],student_courses[j+1][k]);
					strcpy(student_courses[j+1][k],std_course_temp);
					
					std_grade_temp = student_grades[j][k];
					student_grades[j][k] = student_grades[j+1][k];
					student_grades[j+1][k] = std_grade_temp;
				}
			}
		}
	}
	view_students();
}

u32 find_course_index(u8 edit_std_info[100],u32 std_index)
{
	u32 y;
	for(u32 i = 0 ; i < num_courses[std_index] ; i++)
	{
		y = strcmp(strlwr(student_courses[std_index][i]),strlwr(edit_std_info));
		if(y==0)
		{
			return i;
		}
	}
	if(y)
	{
		printf("\nStudent hasn't registered this course yet");
		return -1;
	}
}

void add_course(u32 index)
{
	u8 user_input[100];
	f32 course_grade;
	u32 credit_hr;
	printf("\nAdd a new course name : ");
	scanf(" %[^\n]s",user_input);
	printf("\nEnter course grade : ");
	scanf(" %f",&course_grade);
	printf("\nEnter number of credit hours of the course : ");
	scanf(" %d",&credit_hr);
	num_courses[index]++;
	strcpy(student_courses[index][num_courses[index]-1],user_input);
	student_grades[index][num_courses[index]-1] = course_grade;
	credit_hrs[index][num_courses[index]-1] = credit_hr;
}

void drop_course(u32 index)
{
	u8 user_input[100];
	u32 student_num_courses = num_courses[index];
	f32 course_grade;
	u32 credit_hr,y,course_index;
	printf("\nEnter the name of the course to be deleted : ");
	scanf(" %[^\n]s",user_input);
	course_index = find_course_index(user_input,index);
	for(u32 i = course_index ; i < student_num_courses ; i++)
	{
		student_grades[index][i] = student_grades[index][i+1];
		credit_hrs[index][i] = credit_hrs[index][i+1];
		strcpy(student_courses[index][i],student_courses[index][i+1]);
	}
	student_grades[index][student_num_courses-1] = 0;
	student_courses[index][student_num_courses-1][0] = '\0';
	credit_hrs[index][student_num_courses-1] = 0;
    num_courses[index]--;
}

void edit_all_std_info(u32 index)
{
	u8 user_input[100];
    f32 grade_edit;
    u32 credit_hr;
	for(u32 j = 0 ; j < num_courses[index] ; j++)
		{
		printf("\nEdit course %d:",j+1);
		scanf(" %[^\n]s",user_input);
		strcpy(student_courses[index][j],user_input);
		printf("\nEnter grade of %s course: ",student_courses[index][j]);
		scanf(" %f",&grade_edit);
		student_grades[index][j] = grade_edit;
		printf("\nEnter the number of CH of %s course\n",student_courses[index][j]);
		scanf(" %d",&credit_hr);
		credit_hrs[index][j] = credit_hr;
		}
}