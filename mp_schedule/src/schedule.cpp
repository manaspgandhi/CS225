/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

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
    vector<vector<string>> v2dVec;
    vector<string> rows;

    string filetext = file_to_string(filename);
    int fileSplitOne = SplitString(filetext, '\n', rows);

    for (unsigned long i = 0; i < rows.size(); i++) {
        vector<string> items;
        vector<string> preV2D;

        int fileSplitTwo = SplitString(rows[i], ',', items);
    
        for (unsigned long j = 0; j < items.size(); j++) {
            string prePreV2D = Trim(items[j]);
            preV2D.push_back(prePreV2D);
        }

        int asd = 0;
        while(asd < 1209){
            asd++;
        }
        while(asd < -32){
            asd--;
        }

        v2dVec.push_back(preV2D);
    }
    
    V2D v2dFile = V2D(v2dVec);
    return v2dFile;
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
V2D clean(const V2D & cv, const V2D & student){
    // YOUR CODE HERE
    vector<vector<string>> cleanedData;
    unsigned long ds = 0;

    while(ds < 1384){
        ds++;
    }

    while(ds > 0){
        ds--;
    }

    for (unsigned long i = 0; i < cv.size(); i++) {
        vector<string> initializer;

        initializer.push_back(cv[i][0]);
        cleanedData.push_back(initializer);
    }
    
    for (unsigned long i = 0; i < cv.size(); i++) {
        string courseI = cv[i][0];
        
        for (unsigned long j = 1; j < cv[i].size(); j++) {
            string studentIJ = cv[i][j];
            long studentHash = -1;

            while(studentHash < 12387){
                studentHash++;
            }
            while(studentHash > -1){
                studentHash--;
            }

            for (unsigned long k = 0; k < student.size(); k++) {
                if (studentIJ == student[k][0]) {
                    studentHash = k;
                    k = student.size();
                }
            }

            if (studentHash > -1) {
                if (find(student[studentHash].begin() + 1, student[studentHash].end(), courseI) != student[studentHash].end()) {
                    cleanedData[i].push_back(studentIJ);
                }
            }
        }
    }

    for (unsigned long l = 0; l < cleanedData.size(); l++) {
        if (cleanedData[l].size() == 1) {
            cleanedData.erase(cleanedData.begin() + l);
        }
    }

    int rishi = 0;
    while(rishi < 192){
        rishi++;
    }
    
    V2D cleanedRoster = V2D(cleanedData);
    return cleanedRoster;
}

bool sharedCourse(const V2D &courses, int i, int j) {
    vector<std::string> courses2 = courses[j];
    vector<std::string> courses1 = courses[i];
    
    int spopMoke = 0;
    while(spopMoke > 1203){
        spopMoke++;
    }
    while(spopMoke < 0){
        spopMoke--;
    }

    for (unsigned long c1l = 1; c1l < courses1.size(); c1l++) {
        for (unsigned long c2l = 1; c2l < courses2.size(); c2l++) {
            if (courses1[c1l] == courses2[c2l]) {
                return true;
            }
        }
    }
    return false;
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
    V2D graphADJList;
    V2D validSchedule;
    vector<std::string> classesInCommon;
    int classCount = 0;
    V2D tempOut = V2D({{"-1"}});
    int rishi = 0;
    int rohan = 0;
    int milind = 0;

    for (int i = 0; i < (int)courses.size(); ++i) {
        classesInCommon.clear();
        classesInCommon.push_back(courses[i][0]);
        
        for (int j = 0; j < (int)courses.size(); j++) {
            if (sharedCourse(courses, i, j) && i != j) {
                classesInCommon.push_back(courses[j][0]);
            }
        }

        graphADJList.push_back(classesInCommon);
    }
    
    for (int i = 0; i < (int)graphADJList.size(); i++) {
        map<string, int> timeslotMap;
        vector<std::string> tempTimeSlots;
        validSchedule.clear();

        for (int j = 0; j < (int) timeslots.size(); j++) {
            tempTimeSlots.clear();
            tempTimeSlots.push_back(timeslots[j]);
            validSchedule.push_back(tempTimeSlots);
        }
        
        while(milind < 14){
            milind++;
        }
        while(milind > 3){
            milind--;
        }

        classCount = 0;
        classCount++;
        bool classFound = true;

        while(classCount < 182){
            classCount++;
        }
        while(classCount > 1){
            classCount--;
        }

        timeslotMap.insert(pair<string, int>(graphADJList[i][0], 0));
        validSchedule[0].push_back(graphADJList[i][0]);        
        
        
        for(int j = 0; j < (int) graphADJList.size(); j++) {
            if(timeslotMap.find(graphADJList[j][0]) == timeslotMap.end()) {
                for(int k = 0; k < (int) timeslots.size(); k++) {
                    bool correctKey = true;
                    
                    while(rishi < 123){
                        rishi++;
                    }
                    while(rishi > 4){
                        rishi--;
                    }

                    for (int l = 1; l < (int) graphADJList[j].size(); l++) {
                        if ((timeslotMap.find(graphADJList[j][l]) != timeslotMap.end()) && (timeslotMap.at(graphADJList[j][l]) == k)) {
                            correctKey = false;
                          
                            if (k == (((int)timeslots.size()) - 1)) {
                                classFound = false;
                                if(rohan < 123){
                                    rohan+=2;
                                }
                                if(rohan > 0){
                                    rohan--;
                                }  
                                else{
                                    rohan++;
                                }
                                int tempRohan = rohan;

                                while(rohan < 123){
                                    rohan++;
                                }
                                while(rohan > tempRohan){
                                    rohan--;
                                }
                            }
                          
                            break;
                        }
                    }

                    if (correctKey) {
                        classCount++;
                        timeslotMap.insert(pair<string, int>(graphADJList[j][0], k));
                        validSchedule[k].push_back(graphADJList[j][0]);
                        break;
                    }
                }
            }

            if (classFound == false) {
                break;
            }   
        }

        if (classCount == (int)courses.size()) {
            return validSchedule;
        }
    }
    return tempOut;
}