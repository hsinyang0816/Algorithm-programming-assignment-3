#include <iostream>
#include <fstream>
#include "MST_prim.h"
#include "../lib/tm_usage.h"

using namespace std;

void help_message() {
    cout << "usage: cb <input_file_name> <output_file_name>" << endl;
}

int main(int argc, char* argv[])
{
    if(argc != 3) {
       help_message();
       return 0;
    }
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    //////////// read the input file /////////////
    fstream fin(argv[1]);
    fstream fout;
    fout.open(argv[2],ios::out);
    int n,m;
    int i,j,w;
    char type;
    fin >> type;
    fin >> n >> m;
    tmusg.periodStart();
    MST NTUMST(n, m);
    if (type == 'u'){ 
    	while (fin >> i >> j >> w){
	    //cout << i << " " << j << " " << w << endl;
	    NTUMST.connect_edges(i, j, w);
        }
        NTUMST.prim();
        NTUMST.write_file(fout);
    }
    else{
    	while (fin >> i >> j >> w){
	    //cout << i << " " << j << " " << w << endl;
	    NTUMST.connect_edges_direct(i, j, w);
        }
	NTUMST.QuickSort();
	NTUMST.create_graph();
        NTUMST.write_file_direct(fout);
    }
    tmusg.getPeriodUsage(stat);
    cout <<"The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl;
    cout <<"memory: " << stat.vmPeak << "KB" << endl; // print peak memory
    fin.close();
    fout.close();
}


