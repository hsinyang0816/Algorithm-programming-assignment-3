// **************************************************************************
//  File       [MST_prim.h]
//  Author     [Hsin-Yang Chang]
//  Synopsis   [The header file for the Maximum Planar Subset Class]
//  Modify     [2021/1/16 Hsin-Yang Chang]
// **************************************************************************

#include<vector>
#include<fstream>
#include<algorithm>
using namespace std;

class MST_v{
friend class MST;
friend class MST_e;
    public:
        MST_v(int ID) : id(ID), d(-101), p(NULL), inQ(true), inQ_position(ID){};
        void connect(MST_v*, MST_v*, int);
        ~MST_v(){}; 
	static void setGlobalref(){++global_ref;}
	void settoGlobalref(){ref = global_ref;}
    private:
        int id;
	bool inQ;
	int inQ_position;
        int d;
	size_t ref;
        MST_v* p;
        vector<MST_v*> Adj;
	vector<int> weight; 
	static size_t global_ref;
};

class MST_e{
friend class MST;
    public:
        MST_e(MST_v* i, MST_v* j, int W) : s(i), t(j), w(W){};
        ~MST_e(){}; 
    private:
	MST_v* s;
        MST_v* t;
        int w;
};

class MST {
    public:
	MST(int, int); // constructor
	~MST(); //destructor
	void connect_edges(int, int, int);
	void connect_edges_direct(int, int, int);
	void QuickSort();
	void prim();
	void write_file(fstream&);
	void write_file_direct(fstream&);
	void create_graph();
    private:
	void dfs_visit(MST_v*);
	void QSsubvector(int, int);
	int Partition(int, int);
	void maxHeapify(int);
	void BuildMaxHeap();
	MST_v* heapExtractMax();
	void heapIncreasekey(int, int);
	vector<MST_v*> Q;
	vector<MST_v*> vertices;
	vector<MST_e> edges;
	vector<MST_e> result;
	int heapsize;
	int V;
	int E;
	int cost;
        MST_v* temp_s;
	bool cycle_exist;
};
