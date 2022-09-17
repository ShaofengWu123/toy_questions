#include <iostream>
#include <string>

//using namespace std;

class Student
{
    public: 
    // constructor function
        Student(int s = 0){
                std::cout << "Student Constructor called" << std::endl;
                score = s;
        }
    
    // polymorphism
        void ChangeScore(int s1, int s2, int s3){
            score = 0.1*s1 + 0.6*s2 + 0.3*s3;
        }

        void ChangeScore(double s){
            score = s;
        }
    // member function  
        void PirntScore(){
            std::cout << score << std::endl;
        }

    // public/private/protected members
        std::string name; 
        int ID;
    private: 
        double score;
    protected:
        int student_type = 0;
};

class PhDStudent: private Student
{
    public:
        PhDStudent(){
                std::cout << "PhDStudent Constructor called" << std::endl;
                std::cout << "Student Type: "<< student_type << std::endl;
        }

        std::string department;
};


int main(){

    Student stu1;
    stu1.ID = 12345;
    stu1.ChangeScore(1,2,3);
    std::cout << stu1.ID << std::endl;

    PhDStudent phdstu1;
    return 0;
}

