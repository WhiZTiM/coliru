#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_set>

//for mmap:
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
    unsigned id;
    unsigned label;
    EdgeProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}
};

namespace boost {
template <> struct hash<VertexProperties> {
    size_t operator()(VertexProperties const &v) const {
        using namespace boost;
        auto seed = hash_value(v.id);
        hash_combine(seed, v.label);
        return seed;
    }
};
template <> struct hash<EdgeProperties> {
    size_t operator()(EdgeProperties const &e) const {
        using namespace boost;
        auto seed = hash_value(e.id);
        hash_combine(seed, e.label);
        return seed;
    }
};
}

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

float seuil;
vector<Graph> dataG;

//oprators over edges-------------------------------------------------------------------------------unorderdset
struct hashedge {
    hashedge(Graph const &g) : _g(g) {}
    size_t operator()(const edge_iter e, Graph const &g) const {
        using namespace boost;
        size_t seed = 42;
        hash_combine(seed, g[source(*e, g)]);
        hash_combine(seed, g[*e].label);
        hash_combine(seed, g[target(*e, g)]);
        return seed;
    }

  private:
    Graph const &_g;
};

std::unordered_set<edge_iter, hashedge> edgehash(std::less<edge_iter>(), hashedge(dataG));

//=================callback used fro subgraph_iso=================================================================
struct my_callback {
    template <typename CorrespondenceMap1To2, typename CorrespondenceMap2To1>
    bool operator()(CorrespondenceMap1To2 f, CorrespondenceMap2To1 g) const {
        return false;
    }
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
vector<string> splitstringtolines(string const& str) {

    std::vector<string> split_vector;
    split(split_vector, str, is_any_of("\n"));

    return split_vector;
}

//============Get a string starting from pos============
string getpos(int const& pos, string const& yy) {
    size_t i = pos;
    string str;
    for (; ((yy[i] != ' ') && (i < yy.length())); i++) {str += yy[i];}
    return str;
}
//==================read string vector and return graphs vector===================
std::vector<Graph> creategraphs(std::vector<string> const& fichlines) {

    int compide = 0; // compteur de id edge
    for (string yy : fichlines) {
        switch (yy[0]) {
            case 't': {
                string str2 = getpos(4, yy);
                unsigned gid = atoi(str2.c_str());
                dataG.emplace_back(GraphProperties(gid, gid));
                compide = 0;
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

            case 'e': { // cout<<yy<<endl;
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
                boost::add_edge(fromId, toId, EdgeProperties(compide, eLabel), dataG.back());
                compide++;
            } break;
        }
    }

    return dataG;
}
//============test if the graph is empty========================================================
bool emptygraph(Graph const& g) {
    return ((num_edges(g)==0)&&(num_vertices(g)==0));//using only the number of edges match
}
//============test if the graph connectivity========================================================
bool graphconnexe(Graph const& g) {
    return (num_edges(g) >= (num_vertices(g)-1));
}
//====================print the graph information========================================================
void printgraph(Graph const& gr) {
    typedef std::pair<edge_iter, edge_iter> edge_pair;
    std::cout <<"=================================="<<endl;
    std::cout <<" contains " << num_vertices(gr) << " vertices, and " << num_edges(gr) << " edges " << std::endl;
    if (graphconnexe(gr)) {

        // Vertex list
        if (num_vertices(gr) != 0) {
            std::cout << "  Vertex list: " << std::endl;
            for (size_t i = 0; i < num_vertices(gr); ++i) // size_t vertice number in the graph
            {
                std::cout << " ID: " << gr[i].id << ", Label: " << gr[i].label << std::endl;
            }
        }
        // Edge list
        if (num_edges(gr) != 0) {
            std::cout << "  Edge list: " << std::endl;
            edge_pair ep;
            for (ep = edges(gr); ep.first != ep.second; ++ep.first) // ep edge number
            {
                vertex_t from = source(*ep.first, gr);
                vertex_t to = target(*ep.first, gr);
                edge_t edg = edge(from, to, gr);
                std::cout << "   e(" << gr[from].id << "," << gr[to].id << ")   ID: " << gr[edg.first].id
                << " ,  Label: " << gr[edg.first].label << std::endl;
            }
        }
        std::cout<<endl;
    } else {
        cout << "Please check this graph connectivity." << endl;
    }
}

//=================test if the given vertice exist in the graph========================= i have modified this
bool verticeexist(Graph const& g, int const& vId, int const& vlabel) {


    for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
    {
        if ((g[i].id == vId) && (g[i].label == vlabel))  return true;
    }

    return false;
}
//========test if this id of the vertice exist in the graph====================================================
bool idverticeexist(Graph const& g, int const& vId) {
    if (num_edges(g) != 0) {
        for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
        {
            if (g[i].id == vId) {
                return true;
            }
        }
    }
    return false;
}
//=======get vertice label label============================

int getvlabel(Graph const& M,int const& id){
    int cpt;
    for (size_t i = 0; i < num_vertices(M); ++i){
        if (M[i].id == id) {
            cpt=M[i].label;
            return cpt;
            //there is a problem if we can't find the id (to get the label) what should we return
            //we call this function only when we are sure that the id exist by using idverticeexist() function

        }
    }
    return (num_vertices(M)+1);
}
//=============test if the given edge exist in the graph===========================i have modified this
bool edgeexist(Graph const& g, int const& fromid, int const& toid, unsigned const& elabel) {


    if (num_edges(g) != 0) {
        edge_pair ep;
        for (ep = edges(g); ep.first != ep.second; ++ep.first) // ep edge number
        {
            vertex_t from = source(*ep.first, g);
            vertex_t to = target(*ep.first, g);
            edge_t edg = edge(from, to, g);

            if ((g[from].id == fromid) && (g[to].id == toid) && (g[edg.first].label == elabel)) {
                return true;
            }

        }
    }

    return false;
}

/*===============test if edges are equal============================= ??????
 bool edgesareequal(Graph const& g1,edge_iter const& e1,Graph const& g2,edge_iter const& e2){

 vertex_t frome1 = source(*e1, g1);
 vertex_t toe1 = target(*e1, g1);
 edge_t edg1 = edge(frome1, toe1, g1);
 int label1 =g1[edg1.first].label;

 vertex_t frome2 = source(*e2, g2);
 vertex_t toe2 = target(*e2, g2);
 edge_t edg2 = edge(frome2, toe2, g2);
 int label2 =g2[edg2.first].label;


 return((frome1==frome2)&&(toe1==toe2)&&(label1==label2));
 }
 */

//======================================================
float countfrequency(Graph const& g1,std::vector<Graph> dataG){
    int iso=0;
    if(emptygraph(g1)){return 1;}
    else{
        for (Graph g2: dataG){
            if(vf2_subgraph_iso(g1,g2,my_callback())){iso++;}
        }
    }
    return (iso/dataG.size());
}
//======================================================!!!!!!!!
bool frequent(Graph const& g1,std::vector<Graph> dataG){
    if(emptygraph(g1)){return true;}
    else{
        return countfrequency(g1, dataG)*dataG.size()>=seuil;
    }

}
//==========test if the edge is connexe with the graph=============
bool graphconnexewithedge(Graph g, int const& fromid, int const& toid) {
    return (idverticeexist(g,fromid)|| idverticeexist(g,toid));
}
//=========aumentation of a subgraph g from the original graph M=================================
void augmentation(Graph &M, Graph &g, int const& fromid, int const& toid, unsigned const& edgeid, unsigned const& elabel) {


    if(!idverticeexist(g,fromid)){
        int vlabel=getvlabel(M,fromid);
        boost::add_vertex(VertexProperties(fromid, vlabel), g);
    }

    if(!idverticeexist(g,toid)){
        int vlabel=getvlabel(M,toid);
        boost::add_vertex(VertexProperties(toid, vlabel), g);
    }

    boost::add_edge(fromid, toid, EdgeProperties(edgeid, elabel), g);

}

//=========================================================== this is very complex, it must be modifed
//edgesdiff result is a vector or un order set
//i have modifed this
std::vector<std::array<int, 3>>  edgesdiff(Graph const& g1,Graph const& g2){


    std::array<int, 3> t;
    std::vector<std::array<int, 3>> res;

    edge_pair ep;
    for (ep = edges(g1); ep.first != ep.second; ++ep.first) // ep edge number
    {
        vertex_t from = source(*ep.first, g1);
        t[0]=g1[from].id;
        vertex_t to = target(*ep.first, g1);
        t[1]=g1[to].id;
        edge_t edg = edge(from, to, g1);
        t[2]=g1[edg.first].label;

        if(!edgeexist(g2,t[0],t[1],t[2])){res.push_back(t);}
    }

    return res;
}

//==============================M A I N   P R O G R A M =======================================
int main() {
    clock_t start = std::clock();
    size_t length;
    std::vector<Graph> dataG =creategraphs(splitstringtolines(readfromfile("10000.data", length)));
    cout << "FILE Contains " << dataG.size() << " graphs."<<endl;



    cout<<"TIME: " << (std::clock() - start) / (double)CLOCKS_PER_SEC<< "s" << endl; // fin du programme.

}
