#include <iostream>
#include <array>
#include <algorithm>
static const int num_students = 5;

int comparison_count;

struct student {
    int classID;
    bool operator==(const student&rhs) const {++comparison_count; return classID==rhs.classID;}
    bool operator!=(const student&rhs) const {++comparison_count; return classID!=rhs.classID;}
    friend std::ostream& operator<<(std::ostream& o,const student&s) {return o<<s.classID;}
};

void _find_largeclass_recursion(std::array<student,num_students>::const_iterator begin, 
                                std::array<student,num_students>::const_iterator end, 
                                student& first, 
                                student& second)
{
    std::array<student,num_students> promotions={-1,-1};
    auto endpromote = promotions.begin();
    auto it = begin;
    for(; it<end-1; ++it) {
        student s = *it;
        if (s == *++it)
            *endpromote++ = *it;
    }
    if (it!=end)
        *endpromote++ = *it;
    if (endpromote == promotions.begin()) {
        auto firsttwo = begin;
        *endpromote++ = *firsttwo++;
        *endpromote++ = *firsttwo;
    }
    if (std::distance(promotions.begin(),endpromote) <= 2) {
        auto results = promotions.begin();
        first = *results++;
        second = *results;
    } else
        _find_largeclass_recursion(promotions.begin(), endpromote, first, second);
}

student find_largeclass(std::array<student,num_students>::const_iterator begin, std::array<student,num_students>::const_iterator end) {
    const int target = (num_students+1)/2;
    student first{-1};
    student second{-1};
    _find_largeclass_recursion(begin, end, first, second);
    int count = 0;
    for(auto it=begin; it!=end; ++it) {
        if (*it == first)
            ++count;
    }
    if (count>=target)
        return first;
    if (second != student{-1}) {
        count = 0;
        for(auto it=begin; it!=end; ++it) {
            if (*it == second)
                ++count;
        }
        if (count>=target)
            return second;
    }
    return student{-1};
}

const char* confirm(student large,std::array<student,num_students>::const_iterator begin, std::array<student,num_students>::const_iterator end) {
    const int target = (num_students+1)/2;
    if (large.classID>=0) {
        int count = std::count(begin,end,large);
        if (count >= target)
            return "TRUE";
        else
            return "FALSE";
    } else {
        std::array<int,num_students> counts={};
        for(auto it=begin; it!=end; ++it)
            counts[it->classID]++;
        for(int i=0; i<num_students; ++i) {
            if (counts[i] >= target)
                return "FALSE";
        }
        return "TRUE";
    }
}

auto compStudents = [](const student&l,const student&r){return l.classID<r.classID;};

int main() {
    try {
        int max_comparisons = 0;
        for(int class_distribution=0; class_distribution<(1<<num_students); ++class_distribution) {
            std::array<student,num_students> students={};
            students[0].classID = 0;
            for(int s=1; s<num_students; ++s) {
                if (class_distribution & (1<<(s-1)))
                    students[s].classID = students[s-1].classID+1;
                else
                    students[s].classID = students[s-1].classID;
            }
            do {
                comparison_count = 0;
                student largeclass =  find_largeclass(students.begin(), students.end());
                for(int s=0; s<num_students; ++s)
                    std::cout << char(students[s].classID+'0');
                const char* c = confirm(largeclass, students.begin(), students.end());
                std::cout << '\t' << largeclass << '\t' << comparison_count << '\t' << c << '\n';
                if (*c=='F') throw std::logic_error("FALSE");
                if (comparison_count > max_comparisons) max_comparisons = comparison_count;
            } while (std::next_permutation(students.begin(), students.end(),compStudents));
        }
        std::cout << "max comparisons = " << max_comparisons << '\n';
        return 0;
    } catch(std::logic_error) {
        return 1;
    }
}