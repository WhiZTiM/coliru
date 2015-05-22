#include<boost/version.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/isomorphism.hpp>
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/config.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/graph/copy.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <ctime>
#include <deque>
#include<math.h>
//#include <unordered_set>

//for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<cmath>


using namespace std;
using namespace boost;

//==========STRUCTURES==========
// vertex
struct VertexProperties {
    int id;
    int label;
    VertexProperties(unsigned i = 0, unsigned l = 0) : id(i), label(l) {}

    bool operator==(VertexProperties const& other) const {
        return tie(label) == tie(other.label);
    }
};

// edge
struct EdgeProperties {
    unsigned label;
    EdgeProperties(unsigned l = 0) :label(l) {}

    bool operator==(EdgeProperties const& other) const {
        return tie(label) == tie(other.label);
    }
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
float seuil=0.25;

deque<Graph> dataG;
deque<Graph> frequentslocal;
deque<Graph> frequentsglobal;

//=================callback used fro subgraph_iso=================================================================
// Default print_callback
template <typename Graph1,typename Graph2>

  struct my_callback {

    my_callback(const Graph1& graph1, const Graph2& graph2)
      : graph1_(graph1), graph2_(graph2) {}

    template <typename CorrespondenceMap1To2,
              typename CorrespondenceMap2To1>
    bool operator()(CorrespondenceMap1To2 , CorrespondenceMap2To1) const {
      return true;
    }

  private:
    const Graph1& graph1_;
    const Graph2& graph2_;
  };

//========test vf2_subgraph_iso with labels=================
template <typename Graph1, typename Graph2>
bool my_bundled_vf2_subgraph_iso(Graph1 const& small, Graph2 const& large) {
    auto const vos = boost::copy_range<std::deque<Graph::vertex_descriptor>>(vertices(small));

    return  vf2_subgraph_mono(small, large, my_callback<Graph1, Graph2>(small, large), vos,
            edges_equivalent   (make_property_map_equivalent(boost::get(edge_bundle,   small), boost::get(edge_bundle,   large))).
            vertices_equivalent(make_property_map_equivalent(boost::get(vertex_bundle, small), boost::get(vertex_bundle, large)))
        );
}
//========test vf2_graph_iso with labels=================
template <typename Graph1, typename Graph2>
bool my_bundled_vf2_graph_iso(Graph1 const& small, Graph2 const& large) {
    auto const vos = boost::copy_range<std::deque<Graph::vertex_descriptor>>(vertices(small));

    return vf2_graph_iso(small, large, my_callback<Graph1, Graph2>(small, large), vos,
            edges_equivalent   (make_property_map_equivalent(boost::get(edge_bundle,   small), boost::get(edge_bundle,   large))).
            vertices_equivalent(make_property_map_equivalent(boost::get(vertex_bundle, small), boost::get(vertex_bundle, large)))
        );
}
//==========handle_error==========
void handle_error(const char *msg) {
    perror(msg);
    exit(255);
}

//test the equality with epsilon as difference
bool isAlmostEqual(float a, float b, float epsilon)
{
    return (fabs(a - b) <= epsilon)||(fabs(b - a) <= epsilon);
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
deque<string> splitstringtolines(string const& str) {

    std::deque<string> split_deque;
    split(split_deque, str, is_any_of("\n"));

    return split_deque;
}

//============Get a string starting from pos============
string getpos(int const& pos, string const& yy) {
    size_t i = pos;
    string str;
    for (; ((yy[i] != ' ') && (i < yy.length())); i++) {str += yy[i];}
    return str;
}
//==================read string deque and return graphs deque===================
std::deque<Graph> creategraphs(std::deque<string> const& fichlines) {

    for (string yy : fichlines) {
        switch (yy[0]) {
            case 't': {
                string str2 = getpos(4, yy);
                unsigned gid = atoi(str2.c_str());
                dataG.emplace_back(GraphProperties(gid, gid));

            } break;
            case 'v': {
                assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false

                int vId, vLabel;
                string vvv = getpos(2, yy);
                vId = atoi(vvv.c_str());
                string vvvv = getpos((int)vvv.length() + 3, yy);

                vLabel = atoi(vvvv.c_str());
                boost::add_vertex(VertexProperties(vId, vLabel), dataG.back());
            }

                break;

            case 'e': { // cout<<yy<<endl;
                assert(!dataG.empty()); // assert will terminate the program  if its argument turns out to be false

                int fromId, toId, eLabel;
                string eee = getpos(2, yy);

                fromId = atoi(eee.c_str());
                string eee2 = getpos((int)eee.length() + 3, yy);

                toId = atoi(eee2.c_str());
                int c = (int)eee.length() + (int)eee2.length() + 4;
                //    cout<<c<<endl;
                string eee3 = getpos(c, yy);

                eLabel = atoi(eee3.c_str());
                for (size_t i = 0; i < num_vertices(dataG.back()); ++i) // size_t vertice number in the graph
                {
                    if(dataG.back()[i].id==fromId) fromId=i;
                    else if(dataG.back()[i].id==toId) toId=i;
                }

                boost::add_edge(fromId, toId, EdgeProperties(eLabel), dataG.back());

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
bool graphconnexe(Graph const& g)
{
    return (num_edges(g) >= (num_vertices(g)-1));
}

//=================test if the given vertice exist in the graph========================= i have modified this
bool verticeexist(Graph const& g, int const& vlabel) {


    for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
    {
        if ((g[i].label == vlabel))  { return true;}
    }

    return false;
}

//=============test if the given edge exist in the graph===========================i have modified this
bool edgeexistlabels(Graph const& g, int const& fromlab, int const& tolab, unsigned const& elabel) {


    if (num_edges(g) != 0) {
        edge_pair ep;
        for (ep = edges(g); ep.first != ep.second; ++ep.first) // ep edge number
        {
            vertex_t from = source(*ep.first, g);
            vertex_t to = target(*ep.first, g);
            edge_t edg = edge(from, to, g);

            if (      (g[edg.first].label == elabel)&&
                    (

                    (    (g[from].label == fromlab) && (g[to].label == tolab))
                    ||
                    (   (g[from].label == tolab) && (g[to].label == fromlab))
                    )
                ) { return true;}

        }
    }

    return false;
}
//=======================================================================
bool edgeexist(Graph const& g, unsigned const& elabel) {


    if (num_edges(g) != 0) {
        edge_pair ep;
        for (ep = edges(g); ep.first != ep.second; ++ep.first) // ep edge number
        {
            vertex_t from = source(*ep.first, g);
            vertex_t to = target(*ep.first, g);
            edge_t edg = edge(from, to, g);

            if (g[edg.first].label == elabel) {return true;}

        }
    }

    return false;
}


//==========count the frequency of the graph============================================
float countfrequency(Graph const& g1)
{
    float iso=0;
    if(emptygraph(g1)){return 1;}
    else
    {
        for (Graph g2: dataG)
        {
            if(my_bundled_vf2_subgraph_iso(g1,g2)){iso++;}
        }
    }

 return (iso/dataG.size());
}
//=====test if the graph is frequent=================================================
bool frequent(Graph const& g1)
{
    if(emptygraph(g1)){return true;}
    else
    {
        return ( (isAlmostEqual(countfrequency(g1),seuil,0.001)) || (countfrequency(g1)*dataG.size() >= floor(seuil*dataG.size())) );
        //return (countfrequency(g1)*dataG.size() > floor(seuil*dataG.size()));

    }
}

//====================print the graph information========================================================
void printgraph(Graph const& gr)
{
    typedef std::pair<edge_iter, edge_iter> edge_pair;
    std::cout <<"__________x"<<countfrequency(gr)*dataG.size()<<"__________"<<endl;
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
                std::cout << "   e(" << gr[from].id << "," << gr[to].id << "), Label: " << gr[edg.first].label << std::endl;
            }
        }
        std::cout<<endl;
    } else {
        cout << "Please check this graph connectivity." << endl;
    }
}

//========test if this id of the vertice exist in the graph====================================================
bool idverticeexist(Graph const& g, int const& vId)
{
    if (num_edges(g) != 0)
    {
        for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
        {
            if (g[i].id == vId)
            {
                return true;
            }
        }
    }
    return false;
}

//=======get vertice label label============================

int getvlabel(Graph const& M,int const& id)
{
    for (size_t i = 0; i < num_vertices(M); ++i)
    {
        if (M[i].id == id)
        {
            return M[i].label;
        }
    }
}


//==========test if the edge is connexe with the graph=============
bool graphconnexewithedge(Graph g, int const& fromid, int const& toid) {

    return (emptygraph(g)) != (idverticeexist(g,fromid) != idverticeexist(g,toid));
}

//============================================
int getpositionverticeexist(Graph const& g, int const& vId) {
    if (num_edges(g) != 0) {
        for (size_t i = 0; i < num_vertices(g); ++i) // size_t vertice number in the graph
        {
            if (g[i].id == vId) {
                return i;
            }
        }
    }
}
//========aumentation of a subgraph g from the original graph M=================================
void augmentation(Graph &M, Graph &g, int const& fromid, int const& toid, unsigned const& edgeid, unsigned const& elabel) {

    int newfromid=0, newtoid=0;
    if(!idverticeexist(g,fromid)){
        int vlabel=getvlabel(M,fromid);
        boost::add_vertex(VertexProperties(fromid, vlabel), g);
        newfromid=num_vertices(g)-1;
    } else newfromid=getpositionverticeexist(g,fromid);

    if(!idverticeexist(g,toid)){
        int vlabel=getvlabel(M,toid);
        boost::add_vertex(VertexProperties(toid, vlabel), g);
        newtoid=num_vertices(g)-1;

    } else newtoid=getpositionverticeexist(g,toid);


    boost::add_edge(newfromid, newtoid, EdgeProperties(elabel), g);

}
//=========return edges of g1 minus g2===========================
std::deque<std::array<int, 3>>  edgesdiff(Graph const& g1,Graph const& g2){



    std::deque<std::array<int, 3>> res;

    edge_pair ep;
    for (ep = edges(g1); ep.first != ep.second; ++ep.first) // ep edge number
    {   std::array<int, 3> t;
        vertex_t from = source(*ep.first, g1);
        int froml=g1[from].label;
        t[0]=g1[from].id;

        vertex_t to = target(*ep.first, g1);
        int tol=g1[to].label;
        t[1]=g1[to].id;

        edge_t edg = edge(from, to, g1);
        t[2]=g1[edg.first].label;

        if(!edgeexistlabels(g2,froml,tol,t[2])){res.push_back(t);}
    }

 return res;
}

//=====test if the graph exist in the deque=============
bool existein(std::deque<Graph> in,Graph w)
{

    for(Graph g:in){
        if(my_bundled_vf2_graph_iso(w,g)){return true;}
    }

 return false;
}

//===========generate frequent graph by one edge augmentation===========================
//for this we use a set of graphs
std::deque<Graph> genererLesInduictifs(Graph G, std::deque<Graph> vec){
 std::deque<Graph> in;
 std::deque<std::array<int, 3>> ef;

    for(auto v:vec)
    {
        ef=edgesdiff(G,v);

        for(auto e:ef)
        {
         Graph w;
         if(graphconnexewithedge(v,e[0],e[1]))
         {
            boost::copy_graph(v,w);
            augmentation(G,w,e[0],e[1],num_edges(v)+1,e[2]);
            if( frequent(w) && !existein(in,w) ){in.push_back(w);}
         }

        }
    }

    return in;
}
/*===========new version with while: Faster but sometimes there is problems ===========================================

std::deque<Graph> genererLesInduictifs(Graph G, std::deque<Graph> vec){
    std::deque<Graph> in;
    bool stop=false;
    std::deque<std::array<int, 3>> ef;

    for(auto v:vec)
    {

        unsigned cpt=0;
        ef=edgesdiff(G,v);

        while(!stop)
        {
            auto e=ef.front();
            ef.pop_front();
            Graph w;// W is an empty Graph
            if(graphconnexewithedge(v,e[0],e[1])&&(!edgeexist(v,e[2])))
             {
                boost::copy_graph(v,w);
                augmentation(G,w,e[0],e[1],num_edges(v)+1,e[2]);
                cpt=0;
                if( frequent(w) && !existein(in,w) ){in.push_back(w);}
             }else{
                    ef.push_back(e);
                    cpt++;
                    }
            if(ef.size()<=cpt){stop=true;}
        }
    }

    return in;
}
*/

//=====retourn les singleton d un graphe
std::deque<Graph> singnleton(Graph const& gr)
{
std::deque<Graph> sin;
Graph s;
for (size_t i = 0; i < num_vertices(gr); ++i)
            {

                boost::add_vertex(VertexProperties(num_vertices(s), gr[i].label),s);
                if(!existein(sin,s)){sin.push_back(s);}
                s.clear();
            }
return sin;

}
//=======list all the frequent subgraphs of a graph using augmentation==========
std::deque<Graph> listsubgraphs(Graph G){
    std::deque<Graph> gen0,in,freqs;
    Graph vide;
    std::deque<std::array<int, 3>> ef;
    std::deque<Graph> singls;

    ef=edgesdiff(G,vide);
    gen0.push_back(vide);
    in=genererLesInduictifs(G,gen0);

    //--add single vertices to

        singls=singnleton(G);
        while(!singls.empty())
        {
            auto s=singls.front();
            if((frequent(s))&& (!existein(frequentsglobal,s))) {freqs.push_back(s);}
            singls.pop_front();
        }

    while(in.size()!=0){
        for(auto x:in){
            if(!existein(freqs,x)){freqs.push_back(x);
     }
        }
        in=genererLesInduictifs(G,in);

    }

    return freqs;
}


//===return the difference between local and global==================================================
void filtring(deque<Graph> local){
//    std::deque<Graph> singls;

    for(Graph g:local)
    {
        /*--add single vertices to
        singls=singnleton(g);
        while(!singls.empty())
        {
            auto s=singls.front();
            if(!existein(frequentsglobal,s)) {frequentsglobal.push_back(s);}
            singls.pop_front();
        }
        */
        if(!existein(frequentsglobal,g)) {frequentsglobal.push_back(g);}

    }

}
//==============================M A I N   P R O G R A M =======================================
int main()
{
    //std::cout <<"BOOST_VERSION="<< BOOST_VERSION <<endl;
    clock_t start = std::clock();
    size_t length;

    std::deque<Graph> dataG =creategraphs(splitstringtolines(readfromfile("graphs.txt", length)));

    cout << "File Graphs=" << dataG.size() << endl;
    cout << "Seuil=" << seuil <<endl;
    for(Graph g:dataG)
    {
        std::deque<Graph> local=listsubgraphs(g);
        filtring(local);
    }

    cout<<"frequentsglobal="<<frequentsglobal.size()<<endl;

    for(Graph l:frequentsglobal){printgraph(l);}


    cout<<"TIME: " << (std::clock() - start) / (double)CLOCKS_PER_SEC<< "s" << endl; // fin du programme.

}
