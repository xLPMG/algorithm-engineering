# Algorithm Engineering

This repository contains my work for the Algorithm Engineering course at FSU Jena, completed during the Winter Semester 2025/26.

## Class and Repository Structure

The grading of this course is based on three components:

1. Weekly Exam Assignments (40%)
2. A C++ project (40%)
3. A paper on the C++ project (20%)

Ideally, all three components would be located in the same repository. However, since I have completed the exam assignments myself and the C++ project with a partner, I have chosen to separate them into two different repositories.
This repository contains my submissions for the weekly exam assignments, but I will explain the exact structure below.

### Weekly Exam Assignments

Each lecture includes a set of Exam Assignments (questions and programming tasks) related to the week’s topic.
All solutions are located in the `answers` directory, organized by lecture.
Each lecture folder typically includes:

* `report.md` — written answers and explanations
* `code/` — directory with corresponding source code files

It should be noted that I have not committed any binary or executable files to this repository, only source code. However, when a task required compiling and running code, I have included corresponding execution logs in the report files.

### C++ Project and Paper

For the C++ project, I chose the topic "Enhancer for Scanned Images". Since we were allowed to work in pairs for this part of the course, I collaborated with a fellow student. The project repository can be found here: [xlpmg/imgclean](https://github.com/xLPMG/imgclean). This repository contains all the source code, as well as the accompanying paper. You may check the README.md file in that repository for more details about the project structure and implementation.

The project itself is a CLI tool written in C++ that enhances scanned images by applying various filters and techniques to improve the readability of text. Since some users might have trouble compiling and using the tool, I went ahead and created MacOS GUI app using Swift, which can be found here: [xlpmg/TextCleaner](https://github.com/xLPMG/TextCleaner). This was simply a side project for myself to learn more about Swift and MacOS app development and does not incorporate any algorithm engineering concepts itself. I still wanted to share it here, as I think it serves its own purpose: even the most optimized algorithm will not help if the user cannot use it properly ;)