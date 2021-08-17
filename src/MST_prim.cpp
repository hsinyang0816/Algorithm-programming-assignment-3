// **************************************************************************
//  File       [MST_prim.cpp]
//  Author     [Hsin-Yang Chang]
//  Synopsis   [The implementation of the Maximum Planar Subset Class]
//  Modify     [2021/1/16 Hsin-Yang Chang]
// **************************************************************************

#include "MST_prim.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
// Constructor
size_t MST_v::global_ref = 0;

MST::MST(int n, int m) {
    cost = 0;
    Q.reserve(n);
    vertices.reserve(n);
    edges.reserve(m);
    V = n;
    heapsize = n;
    E = m;
    for (int i = 0; i < n; ++i){
	MST_v* u = new MST_v(i);
	vertices.push_back(u);
    }
}

MST::~MST(){
    for(int i = 0; i < V; ++i)
        delete vertices[i];
}

void MST_v::connect(MST_v* u, MST_v* v, int w){
    u -> Adj.push_back(v);
    u -> weight.push_back(w);
}

void MST::connect_edges(int i, int j, int w){
    vertices[i] -> connect(vertices[i], vertices[j], w);
    vertices[j] -> connect(vertices[j], vertices[i], w);
}

void MST::maxHeapify(int root){
    int l = 2*(root+1) - 1;
    int r = 2*(root+1);
    int max = root;
    if(l < heapsize && Q[l] -> d > Q[root] -> d)
        max = l;
    if(r < heapsize && Q[r] -> d > Q[max] -> d)
        max = r;
    if(max != root){
	Q[max] -> inQ_position = root;
	Q[root] -> inQ_position = max;
	swap(Q[root], Q[max]);
        maxHeapify(max);
    }
} 

MST_v* MST::heapExtractMax(){
    MST_v* max = Q[0];
    Q[0] -> inQ = false;
    Q[0] = Q[heapsize-1];
    heapsize = heapsize - 1;
    maxHeapify(0);
    return max;
}

void MST::heapIncreasekey(int i, int key){
    if(key < Q[i] -> d)
        cout << "new key is smaller" << endl;
    Q[i] -> d = key;
    while(i > 0 && Q[(i-1)/2] -> d < Q[i] -> d){
	Q[i] -> inQ_position = (i-1)/2;
	Q[(i-1)/2] -> inQ_position = i;
        swap(Q[i], Q[(i-1)/2]);
	i = (i-1)/2;
    }
}

void MST::prim(){
    Q.assign(vertices.begin(), vertices.end());
    Q[0] -> d = 0;
    while(heapsize != 0){
        MST_v* u = heapExtractMax();
        for(int i = 0; i < u -> Adj.size(); ++i){
	    MST_v* v = u -> Adj[i];
	    if(u -> p == v)
		continue;
	    if(v -> inQ && u -> weight[i] > v -> d){
		v -> p = u;
		heapIncreasekey(v -> inQ_position, u -> weight[i]);
	    }
	    else if(!v -> inQ){
		//cout << u -> id << " " << v -> id << " "<< u -> weight[i] << endl;
		MST_e e(u, v, u -> weight[i]);
		edges.push_back(e);
		cost += u -> weight[i];
	    }
	}
    } 
}

void MST::write_file(fstream& fout){
    fout << cost << endl;
    for(int i = 0; i < edges.size(); ++i){
	fout << edges[i].s -> id << " " << edges[i].t -> id << " " << edges[i].w << endl;
    } 
}
 
void MST::connect_edges_direct(int i, int j, int w){
    //vertices[i] -> connect(vertices[i], vertices[j], w);
    MST_e e(vertices[i], vertices[j], w);
    edges.push_back(e);
}

void MST::QuickSort(){
    srand(time(NULL));
    QSsubvector(0, edges.size() - 1);
}

void MST::QSsubvector(int low, int high){
    if(low < high){
	int middle = Partition(low, high);
	QSsubvector(low, middle - 1);
	QSsubvector(middle + 1, high);
    }
}

int MST::Partition(int low, int high){
    int random = rand() % (high - low + 1) + low;
    swap(edges[random],edges[high]);
    int i = low - 1;
    for(int j = low; j < high; ++j){
	if(edges[j].w >= edges[high].w){
	    ++i;
	    swap(edges[i], edges[j]);
	}
    }
    swap(edges[i + 1], edges[high]);
    return (i+1);
}

void MST::dfs_visit(MST_v* u){
    u -> settoGlobalref();
    for(int i = 0; i < u -> Adj.size(); ++i){
	MST_v* v = u -> Adj[i];
	if(v == temp_s){
	    cycle_exist = true;
	    //cout << v -> id << " " << u -> id
	}
	if(v -> ref != v -> global_ref){
	    v -> p = u;
	    dfs_visit(v);
        }
    }
}

void MST::create_graph(){
    cost = 0;
    for(int i = 0; i < E; ++i){
	cycle_exist = false;
	edges[i].t -> setGlobalref();
	temp_s = edges[i].s;
	dfs_visit(edges[i].t);
	if(cycle_exist){
	    //cout << edges[i].s -> id << " " << edges[i].t -> id << " " << edges[i].w << endl;
            //edges[i].s -> Adj.pop_back();
            //edges[i].s -> weight.pop_back();
	    cost += edges[i].w;
	    result.push_back(edges[i]); 
	}
	else
	    edges[i].s -> connect(edges[i].s, edges[i].t, edges[i].w);
    }
    //cout << "cost: " << cost << endl;
}

void MST::write_file_direct(fstream& fout){
    fout << cost << endl;
    for(int i = 0; i < result.size(); ++i){
	fout << result[i].s -> id << " " << result[i].t -> id << " " << result[i].w << endl;
    }
}

