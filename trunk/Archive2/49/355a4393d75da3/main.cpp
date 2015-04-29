#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/graph/mcgregor_common_subgraphs.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/config.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/graph/graph_utility.hpp>

#include <fstream>
#include <iostream>
#include <vector>

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;
using namespace boost;

//==========STRUCTURES==========
// vertex
struct VertexProperties {
    int id;
    int label;
    VertexProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// edge
struct EdgeProperties {
    unsigned label;
    EdgeProperties(unsigned l = 0) : label(l) {}
};

// Graph
struct GraphProperties {
    unsigned id;
    unsigned label;
    GraphProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

// adjency list
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, VertexProperties, EdgeProperties,
                              GraphProperties> Graph;

// descriptors

typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef std::pair<boost::graph_traits<Graph>::edge_descriptor, bool> edge_t;
// iterators
typedef graph_traits<Graph>::vertex_iterator vertex_iter;
typedef graph_traits<Graph>::edge_iterator edge_iter;
typedef std::pair<edge_iter, edge_iter> edge_pair;

//*********global variables*************

vector<Graph> dataG;

//=================callback used fro subgraph_iso=================================================================
// Default print_callback
template <typename Graph1, typename Graph2>
struct my_callback {

    my_callback(const Graph1 &graph1, const Graph2 &graph2) : graph1_(graph1), graph2_(graph2) {}

    template <typename CorrespondenceMap1To2, typename CorrespondenceMap2To1>
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1) const {
        // vf2_graph_iso
        return true;
    }

    template <typename CorrespondenceMap1To2, typename CorrespondenceMap2To1, typename X>
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1, X) const {
        // mcgregor_common_subgraphs
        return true;
    }

  private:
    const Graph1 &graph1_;
    const Graph2 &graph2_;
};

//==========handle_error==========
void handle_error(const char *msg) {
    perror(msg);
    exit(255);
}

//============READ ALL THE FILE AND RETURN A STRING===================
const char *readfromfile(const char *fname, size_t &length) {
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char *addr = static_cast<const char *>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO close fd at some point in time, call munmap(...)
    return addr;
}
//==========SPLIT THE STRING BY NEWLINE (\n) ==========
vector<string> splitstringtolines(string const &str) {

    std::vector<string> split_vector;
    split(split_vector, str, is_any_of("\n"));

    return split_vector;
}

//============Get a string starting from pos============
string getpos(int const &pos, string const &yy) {
    size_t i = pos;
    string str;
    for (; ((yy[i] != ' ') && (i < yy.length())); i++) {
        str += yy[i];
    }
    return str;
}
//==================read string vector and return graphs vector===================
std::vector<Graph> creategraphs(std::vector<string> const &fichlines) {

    for (string yy : fichlines) {
        switch (yy[0]) {
        case 't': {
            string str2 = getpos(4, yy);
            unsigned gid = atoi(str2.c_str());
            dataG.emplace_back(GraphProperties(gid, gid));

        } break;
        case 'v': {
            assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false
            // cout<<yy<<endl;
            int vId, vLabel;
            string vvv = getpos(2, yy);
            vId = atoi(vvv.c_str());
            string vvvv = getpos((int)vvv.length() + 3, yy);
            // cout<<vvvv<<endl;
            vLabel = atoi(vvvv.c_str());
            boost::add_vertex(VertexProperties(vId, vLabel), dataG.back());
        }

        break;

        case 'e': {                 // cout<<yy<<endl;
            assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false

            int fromId, toId, eLabel;
            string eee = getpos(2, yy);
            // cout<<eee<<endl;
            fromId = atoi(eee.c_str());
            string eee2 = getpos((int)eee.length() + 3, yy);
            // cout<<eee2<<endl;
            toId = atoi(eee2.c_str());
            int c = (int)eee.length() + (int)eee2.length() + 4;
            //    cout<<c<<endl;
            string eee3 = getpos(c, yy);
            //  cout<<eee3<<endl;
            eLabel = atoi(eee3.c_str());
            for (size_t i = 0; i < num_vertices(dataG.back()); ++i) // size_t vertice number in the graph
            {
                if (dataG.back()[i].id == fromId)
                    fromId = i;
                else if (dataG.back()[i].id == toId)
                    toId = i;
            }

            boost::add_edge(fromId, toId, EdgeProperties(eLabel), dataG.back());

        } break;
        }
    }

    return dataG;
}

//==============================M A I N   P R O G R A M =======================================
int main() {

    size_t length;

    std::vector<Graph> dataG = creategraphs(splitstringtolines(readfromfile("3test.txt", length)));

    cout << "***PS***\n dataG[0] is a subgraph of dataG[1]\n dataG[2] is the same as dataG[0]\n dataG[3] is the same "
            "as dataG[0] but with other labels.\n" << endl;

    my_callback<Graph, Graph> my_callback(dataG[0], dataG[3]);
    cout << "equal(dataG[0], dataG[3],my_callback)=" << vf2_graph_iso(dataG[0], dataG[3], my_callback) << endl;
    mcgregor_common_subgraphs(dataG[0], dataG[3], true, my_callback);
}
