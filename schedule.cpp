/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <vector>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
using namespace std;

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    vector<vector<std::string>> out;
    std::string filetext = file_to_string(filename);
    vector<std::string> rows;
    int done = SplitString(filetext, '\n', rows);
    for (unsigned long r = 0; r < rows.size(); r++) {
        vector<std::string> items;
        vector<std::string> push;
        int done2 = SplitString(rows[r], ',', items);
        for (unsigned long i = 0; i < items.size(); i++) {
            std::string put = Trim(items[i]);
            push.push_back(put);
        }
        out.push_back(push);
    }
    V2D output = V2D(out);
    return output;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & student) {
    // YOUR CODE HERE
    vector<vector<std::string>> out;
    for (unsigned long c = 0; c < cv.size(); c++) {
        vector<std::string> start;
        start.push_back(cv[c][0]);
        out.push_back(start);
    }
    
    for (unsigned long c = 0; c < cv.size(); c++) {
        std::string currClass = cv[c][0];
        for (unsigned long r = 1; r < cv[c].size(); r++) {
            std::string currStudent = cv[c][r];
            long studentInd = -1;
            for (unsigned long s = 0; s < student.size(); s++) {
                if (student[s][0] == currStudent) {
                    studentInd = s;
                    s = student.size();
                }
            }

            if (studentInd > -1) {
                if (std::find(student[studentInd].begin() + 1, student[studentInd].end(), currClass) != student[studentInd].end()) {
                    out[c].push_back(currStudent);
                }
            }
        }
    }

    for (unsigned long o = 0; o < out.size(); o++) {
        if (out[o].size() == 1) {
            out.erase(out.begin() + o);
        }
    }

    V2D output = V2D(out);
    return output;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    // Your code here!
    vector<vector<std::string>> out;
    V2D output = V2D(out);
    return output;
}