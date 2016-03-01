data = LOAD 'grade.txt' 
       USING PigStorage(',')
       AS (name:chararray, hw1:int, hw2:int, hw3:int);

describe data;
dump data;

hw1 = FOREACH data GENERATE name, 'hw1', hw1;
hw2 = FOREACH data GENERATE name, 'hw2', hw2;
hw3 = FOREACH data GENERATE name, 'hw3', hw3;

grades = UNION hw1, hw2, hw3;
grades_order = ORDER grades BY name ASC, $1 ASC;
describe grades;

students = GROUP grades BY name;
describe students;
results = FOREACH students GENERATE group AS name, SUM(grades.$2)-MIN(grades.$2) AS high2;

describe results;
dump results;

