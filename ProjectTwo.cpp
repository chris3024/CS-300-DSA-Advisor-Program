// ProjectTwo.cpp
// Christopher Sharp
// CS-300: DSA: Analysis and Design
// Michael Susalla


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <cctype>
#include <set>


using namespace std;

struct CourseData {
    string courseID;
    string courseName;
    vector<string> preReqNames;
};

/// ==================================================
/// function to convert user input to capital letters
/// ==================================================
string convertCase(string userCourseID) {
    string results;

    // Looping through string with for loop to capitalize letters
    for (char& c : userCourseID) {
        results += toupper(c);
    }
    return results;
}

// Function printing the courses 
void printAllCourses(const CourseData& course) {
    
    cout << course.courseID << ", " << course.courseName << endl;

}

// Function parsing the file and loading into data structure
vector<CourseData> parseFile(const string& fileName) {

    cout << "\nLoading CSV file " << fileName << endl;

    ifstream file(fileName);
    string line;
    vector<CourseData> courses;

    while (getline(file, line)) {

        try {
            
            //initital intializing structure and vector to hold tokens
            CourseData course;
            vector<string> tokens;

            // initialize stringstream
            istringstream iss(line);
            string token;

            // while loop to parse file into tokens then put into temp vector
            while (getline(iss, token, ',')) {
                tokens.push_back(token);
            }

            // Check that there are at least two items on the line
            if (tokens.size() < 2) {
                throw runtime_error("Error: Invalid line format in file");
                
            }

            // Check that the first two tokens are the courseID and courseName
            course.courseID = tokens[0];
            course.courseName = tokens[1];
            if (course.courseID.empty()) {
                throw runtime_error("Error: Course Number Missing");
                
            }
            else {
                if (course.courseName.empty()) {
                    throw runtime_error("Error: Course Discription Missing");
                }
            }

            // Store any remaining tokens as prerequisites
            for (int i = 2; i < tokens.size(); i++) {
                course.preReqNames.push_back(tokens[i]);
            }

            courses.push_back(course);
            
        }
        catch (runtime_error& excpt) {
            cout << excpt.what() << endl;
            system("PAUSE");
            
            continue;
            
    }
    

    }

    file.close();
    return courses;
}


// Searching the structure for the course from the user input and printing the course data and prerequisites if present
void PrintCourseInformation(const vector<CourseData>& courses, string convertedInput) {
    
    // Looping through the stucts with a for-each loop
    for (const auto& course : courses) {

        // if the user input matches a courseID
        if (course.courseID == convertedInput) {
            cout << course.courseID << ", " << course.courseName << endl;
            cout << "Prerequisite: ";
            
            // If the prerequisite vector has a size greater than one
            if (course.preReqNames.size() > 1) {

                // for-each loop through vector
                for (const auto& preRequisite : course.preReqNames) {

                    // if there is more than one prerequisite
                    if (course.preReqNames.size() > 1) {
                        cout << preRequisite << ", ";
                    }
                    else {
                        cout << preRequisite;
                    }

                }
                cout << endl;
            }

            // if no prerequisite exists
            else {
                cout << "None";
            }
        }    
    }
}

// Partitioning function to aid in the sorting of the data structure
int partition(vector<CourseData>& courseLists, int begin, int end) {

    int low = begin;
    int high = end;

    int midpoint = low + (high - low) / 2;
    string pivot = courseLists[midpoint].courseID;

    bool done = false;

    // while loop that is partitioning the structure based on midpoint
    while (!done) {
        while (courseLists.at(low).courseID < pivot) {
            low++;
        }
        while (pivot < courseLists.at(high).courseID) {
            high--;
        }

        if (low >= high) {
            done = true;
        }
        else {
            swap(courseLists.at(low), courseLists.at(high));
            low++;
            high--;
        }

    }
    return high;
}

// Function using quickSort to sort the data structure in Alphanumeric order
void quickSort(vector<CourseData>& courseLists, int begin, int end) {
    int midpoint = 0;

    // if the stucture is already sorted
    if (begin >= end) {
        return;
    }
    int dataPartition = partition(courseLists, begin, end);

    quickSort(courseLists, begin, dataPartition);
    quickSort(courseLists, dataPartition + 1, end);
}

   

int main() {
    // setting initial variables
    int choice = 0;
    string fileName;
    string courseNumber;
    string convertedInput;
    vector<CourseData> courses;

    // while loop holding menu system
    while (choice != 9) {
        try {

            // menu
            cout << "\nMenu:\n";
            cout << "1. Load Data Structure\n";
            cout << "2. Print Course List\n";
            cout << "3. Print Course Information\n";
            cout << "9. Quit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            cout << endl;
            
            // Error checking for valid entry from user
            if (cin.fail()) {
                throw runtime_error("Please Enter A Valid Menu Selection");
            }
            

            switch (choice) {

                // getting the filename from the user
                case 1:
                    cout << "Enter the name of the courses file: ";
                    cin >> fileName;
                    fileName = fileName; //+ ".csv"; // assuming filename is a csv
                    courses = parseFile(fileName);

                    cout << "Number of Courses Loaded " << courses.size() << endl;
                    break;

                // Printing alphanumeric list of all courses in the file
                case 2:
                    if (courses.empty()) {
                        throw runtime_error("Data Structure is Empty...Please Select Option 1 First");
                        break;
                    }
                    quickSort(courses, 0, courses.size() - 1);
                    for (const auto& course : courses) {
                        printAllCourses(course);
                    }
                    break;
                // searching for the user supplied course and returning the data
                case 3:
                    if (courses.empty()) {
                        throw runtime_error("Data Structure is Empty...Please Select Option 1 First");
                        break;
                    }
                    
                    cout << "What Course Do You Want to Know About?" << endl;
                    cin >> courseNumber;
                    convertedInput = convertCase(courseNumber);
                    PrintCourseInformation(courses, convertedInput);

                    break;

                // Exiting program
                case 9:
                    cout << "Goodbye!\n";
                    break;

                // Error for wrong input type
                default:
                    cout << "Error: Invalid choice\n";
                    break;
            }

        }
        catch (runtime_error& excpt) {
            cout << excpt.what() << endl;
        }

    }
}

    

