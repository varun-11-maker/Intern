#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Student {
    string name;
    int id;
    vector<double> assignments;
    vector<double> exams;
    double overallGrade;
};

// Function to calculate the overall grade for a student
double calculateOverallGrade(const vector<double>& assignments, const vector<double>& exams) {
    double assignmentAverage = 0, examAverage = 0;

    for(double grade : assignments) {
        assignmentAverage += grade;
    }
    assignmentAverage /= assignments.size();

    for(double grade : exams) {
        examAverage += grade;
    }
    examAverage /= exams.size();

    return (assignmentAverage * 0.4) + (examAverage * 0.6); // Example weightage
}

// Function to display student information
void displayStudent(const Student& student) {
    cout << "Name: " << student.name << ", ID: " << student.id << ", Overall Grade: " << fixed << setprecision(2) << student.overallGrade << endl;
}

// Function to calculate class average
double calculateClassAverage(const vector<Student>& students) {
    double total = 0;
    for(const Student& student : students) {
        total += student.overallGrade;
    }
    return total / students.size();
}

// Function to perform basic statistical analysis
void performStatisticalAnalysis(const vector<Student>& students) {
    double highest = -1, lowest = 101, total = 0;
    vector<double> grades;
    for(const Student& student : students) {
        double grade = student.overallGrade;
        grades.push_back(grade);
        if (grade > highest) highest = grade;
        if (grade < lowest) lowest = grade;
        total += grade;
    }
    sort(grades.begin(), grades.end());
    double median = grades.size() % 2 == 0 ? (grades[grades.size()/2 - 1] + grades[grades.size()/2]) / 2 : grades[grades.size()/2];

    cout << "Highest Grade: " << highest << endl;
    cout << "Lowest Grade: " << lowest << endl;
    cout << "Median Grade: " << median << endl;
}

// Function to display the top 3 students
void displayTopStudents(vector<Student>& students) {
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.overallGrade > b.overallGrade;
    });
    cout << "Top 3 Students:" << endl;
    for(int i = 0; i < min(3, (int)students.size()); ++i) {
        displayStudent(students[i]);
    }
}

int main() {
    vector<Student> students;
    int numberOfStudents;

    cout << "Enter the number of students: ";
    cin >> numberOfStudents;

    for(int i = 0; i < numberOfStudents; ++i) {
        Student student;
        cout << "Enter name for student " << i+1 << ": ";
        cin >> student.name;
        cout << "Enter ID for student " << i+1 << ": ";
        cin >> student.id;

        int numberOfAssignments, numberOfExams;
        cout << "Enter number of assignments for student " << i+1 << ": ";
        cin >> numberOfAssignments;
        cout << "Enter number of exams for student " << i+1 << ": ";
        cin >> numberOfExams;

        cout << "Enter grades for assignments: ";
        for(int j = 0; j < numberOfAssignments; ++j) {
            double grade;
            cin >> grade;
            student.assignments.push_back(grade);
        }

        cout << "Enter grades for exams: ";
        for(int j = 0; j < numberOfExams; ++j) {
            double grade;
            cin >> grade;
            student.exams.push_back(grade);
        }

        student.overallGrade = calculateOverallGrade(student.assignments, student.exams);
        students.push_back(student);
    }

    cout << "\nStudent Grades:" << endl;
    for(const Student& student : students) {
        displayStudent(student);
    }

    double classAverage = calculateClassAverage(students);
    cout << "\nClass Average: " << fixed << setprecision(2) << classAverage << endl;

    cout << "\nStatistical Analysis:" << endl;
    performStatisticalAnalysis(students);

    displayTopStudents(students);

    return 0;
}
