#ifndef STUDENT_MANAGEMENT_SYSTEM_H
#define STUDENT_MANAGEMENT_SYSTEM_H

#include "STD_TYPES.h"

extern u32 num_students = 0;
u8 student_names[100][100]; //
u8 student_courses[100][100][100]; //
f32 student_grades[100][100]; //
u32 num_courses[100]; //
u32 credit_hrs[100][100]; //
f32 std_gpa[100]; //

void main_menu();
void add_std();
void view_students();
void view_student(u32 id);
void search_std();
void delete_std();
void edit_std();
void drop_course(u32 index);
void add_course(u32 index);
void edit_all_std_info(u32 index);
u32 int_search_id(u8 search_student[100]);
u32 check_std_found(u8 search_student[100]);
u32 find_course_index(u8 edit_std_info[100],u32 std_index);
f32 gpa_calc(u8 std_gpa[100]);
void get_std_gpa();
void sort_std();

#endif