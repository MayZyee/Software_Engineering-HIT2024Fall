#include "read.cpp"
#include "graph.cpp"
#include <sstream>
int main()
{
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> C4
=======
=======
>>>>>>> b000edef1180efd9a16eeae5e222f3e3362996bf
>>>>>>> master
    read file = read("input.txt");
    std::vector<std::string> words = file.processedLines;
    Graph graph(words);
    graph.todo();
}
