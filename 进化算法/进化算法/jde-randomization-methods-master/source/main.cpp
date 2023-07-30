#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sys/time.h>
#include <cassert>
#include <cmath>
#include <chrono>

#include "jDE.h"

#include "Benchmarks.h"
#include "F1.h"
#include "F2.h"
#include "F3.h"
#include "F4.h"
#include "F5.h"
#include "F6.h"
#include "F7.h"
#include "F8.h"

#include "../gnuplot-iostream/gnuplot-iostream.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;

double diversityCalc(vDouble pop, int NP, int n_dim) {
	std::vector<double> ci;
	for( int d = 0; d < n_dim; d++ ){
	  double _ci = 0.0;
	  for( int p = 0; p < NP; p++ ){
	    _ci += pop[(p * n_dim) + d] / (double) NP;
	  }
	  ci.push_back(_ci);
	}

	double Isd = 0.0, _t1, _t2;
	for( int d = 0; d < n_dim; d++ ){
	  _t1 = 0.0;
	  for( int p = 0; p < NP; p++ ){
	    _t2 = pop[(p * n_dim) + d] - ci[d];
	    _t1 += (_t2 * _t2);
	  }
	  Isd += sqrt(_t1 / (NP - 1));
	}

	Isd /= (double) n_dim;
	return Isd;
}

double stime(){
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    double mlsec = 1000.0 * ((double)tv.tv_sec + (double)tv.tv_usec/1000000.0);
    return mlsec/1000.0;
}

void show_params(
        uint n_runs,
        uint NP,
        uint n_evals,
        uint n_dim,
        std::string FuncObj,
        std::string distName
){
    printf(" | Number of Executions:                    %d\n", n_runs);
    printf(" | Population Size:                         %d\n", NP);
    printf(" | Number of Dimensions:                    %d\n", n_dim);
    printf(" | Number of Function Evaluations:          %d\n", n_evals);
    printf(" | Optimization Function:                   %s\n", FuncObj.c_str());
    printf(" | Distribution:                            %s\n", distName.c_str());
}

std::string toString(uint id){
    switch( id ){
        case 1:
            return "Schaffer";
		case 2:
		    return "Rastrigin";
		case 3:
		    return "Griewank";
		case 4:
		    return "Rosenbrock";
        case 5:
            return "Sphere";
        case 6:
            return "Ackley";
        case 7:
            return "Schwefel";
        case 8:
            return "Zakharov";
        default:
            return "Unknown";
    }
}

std::string toStringDist(uint id){
    switch( id ){
        case 1:
            return "Uniform";
        case 2:
        	return "Gaussian";
        case 3:
        	return "Logistic";
        default:
            return "Unknown";
    }
}

Benchmarks * getFunction(uint id, uint n_dim){
    Benchmarks * n;

    if( id == 1 ){
        n = new F1(n_dim);
        return n;
    } else if( id == 2 ){
        n = new F2(n_dim);
        return n;
    } else if( id == 3 ){
        n = new F3(n_dim);
        return n;
    } else if( id == 4 ){
        n = new F4(n_dim);
        return n;
    } else if( id == 5 ){
        n = new F5(n_dim);
        return n;
    } else if( id == 6 ){
        n = new F6(n_dim);
        return n;
    } else if( id == 7 ){
        n = new F7(n_dim);
        return n;
    } else if( id == 8 ){
        n = new F8(n_dim);
        return n;
    }

    return NULL;
}

int main(int argc, char * argv[]){
    srand((unsigned)time(NULL));
    uint n_runs, NP, max_evals, n_dim, f_id, dist_id;
    double rand_num, biggestDiversity, mean, worst;
    const gsl_rng_type *T;
  	gsl_rng *r;

    /* Gnuplot stuff */
    Gnuplot gp, gp2;
    std::vector< std::pair<double, double> > graph, bestGraph, worstGraph, meanGraph, diversityGraph;

  	gsl_rng_env_setup();
 
  	T = gsl_rng_default;
  	r = gsl_rng_alloc (T);

    try{
        po::options_description config("Opções");
        config.add_options()
                ("runs,r"    , po::value<uint>(&n_runs)->default_value(10)    , "Number of Executions" )
                ("pop_size,p", po::value<uint>(&NP)->default_value(30)       , "Population Size"      )
                ("dim,d"     , po::value<uint>(&n_dim)->default_value(20)    , "Number of Dimensions" )
                ("func_obj,o", po::value<uint>(&f_id)->default_value(8)      , "Function to Optimize" )
                ("dist_name,m", po::value<uint>(&dist_id)->default_value(2)      , "Distribution" )
                ("max_eval,e", po::value<uint>(&max_evals)->default_value(30000), "Number of Function Evaluations")
                ("help,h", "Help");

        po::options_description cmdline_options;
        cmdline_options.add(config);
        po::variables_map vm;
        store(po::command_line_parser(argc, argv).options(cmdline_options).run(), vm);
        notify(vm);
        if( vm.count("help") ){
            std::cout << cmdline_options << "\n";
            return 0;
        }
    } catch( std::exception& e ){
        std::cout << e.what() << "\n";
        return 1;
    }

    printf(" +==============================================================+ \n");
    printf(" |                      EXECUTION PARAMETERS                    | \n");
    printf(" +==============================================================+ \n");
    show_params(n_runs, NP, max_evals, n_dim, toString(f_id), toStringDist(dist_id));
    printf(" +==============================================================+ \n");

    Benchmarks * B = NULL;
    B = getFunction(f_id, n_dim);

    if( B == NULL ){
        std::cout << "Unknown function! Exiting...\n";
        return 0;
    }

    std::vector< std::pair<double, double> > stats;

    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::mt19937 rng(seed);
    std::uniform_real_distribution<double> random(0, 1);//[0, 1)

    const double x_min = B->getMin();
    const double x_max = B->getMax();

    std::uniform_real_distribution<double> random2(x_min, x_max);//[0, 1)

    jDE * jde = new jDE(NP);

    double tini, tend, best, ultBest;
    for( int go = 1; go <= n_runs; go++ ){
        vDouble gen(NP * n_dim);
        vDouble n_gen(NP * n_dim);
        vDouble fitness(NP, 0.0);
        vDouble n_fitness(NP, 0.0);
        mean = 0;

        double last = random(rng);
        if(dist_id == 1) {
        	//randomly init genes
	        for( uint i = 0; i < gen.size(); i++)
	            gen[i] = (( x_max - x_min) * random(rng)) + x_min;
        } else if(dist_id == 2) {
        	for( uint i = 0; i < gen.size(); i++) {
        		rand_num = gsl_ran_gaussian(r, 0.5) + 0.5;
                 //z = \mu + x
                //rand_num += mean;
	            gen[i] = (( x_max - x_min) * rand_num) + x_min;
        	}
        } else if(dist_id == 3) {
        	//randomly init genes
            for( uint i = 0; i < gen.size(); i++) {
                last = rand_num = jde->logisticMap(last, 4.0);
                gen[i] = (( x_max - x_min) * rand_num) + x_min;
            }
        }
      
        //evaluate the initial population
        for( uint i = 0; i < NP; i++ ) {
            fitness[i] = B->compute(gen, i * n_dim);
        	mean += fitness[i];
        }
        mean /= NP;

        best = *std::min_element(fitness.begin(),fitness.end());
        worst = *std::max_element(fitness.begin(),fitness.end());

        uint nfes = 0, ger = 0;
        tini = stime();

        if(go == 1) {
            bestGraph.push_back(std::make_pair(ger, best));
            worstGraph.push_back(std::make_pair(ger, worst));
            meanGraph.push_back(std::make_pair(ger, mean));
            diversityGraph.push_back(std::make_pair(ger, diversityCalc(gen, NP, n_dim)));
        } else {
            bestGraph[ger].second += best;
            worstGraph[ger].second += worst;
            meanGraph[ger].second += mean;
            diversityGraph[ger].second += diversityCalc(gen, NP, n_dim);
        }

        //start the evolutive process;

        while(nfes < max_evals){
        	ger++;
            mean = 0;
            jde->update(dist_id, last);
            jde->runDE(n_dim, NP, gen, n_gen, x_min, x_max, dist_id, last);

            for( int i = 0; i < NP; i++ ){
                n_fitness[i] = B->compute(n_gen, i * n_dim);
                nfes++;
                mean += fitness[i];
                if( nfes >= max_evals ) break;
            }
            mean /= NP;
            jde->selection(n_dim, NP, gen, n_gen, fitness, n_fitness);
                
            best = *std::min_element(fitness.begin(),fitness.end());
            worst = *std::max_element(fitness.begin(),fitness.end());
            
            if(go == 1) {
                bestGraph.push_back(std::make_pair(ger, best));
                worstGraph.push_back(std::make_pair(ger, worst));
                meanGraph.push_back(std::make_pair(ger, mean));
                diversityGraph.push_back(std::make_pair(ger, diversityCalc(gen, NP, n_dim)));
            } else {
                bestGraph[ger].second += best;
                worstGraph[ger].second += worst;
                meanGraph[ger].second += mean;
                diversityGraph[ger].second += diversityCalc(gen, NP, n_dim);
            }
        }

        graph.clear();

        best = *std::min_element(fitness.begin(),fitness.end());
        tend = stime();

        jde->reset();
        printf(" | Execution: %-2d Overall Best: %+.8lf Time(s): %.8f\n", go, best, tend-tini);
        stats.push_back(std::make_pair(best, tend-tini));
    }

    
    for(int i = 0; i < bestGraph.size(); i++) {
        bestGraph[i].second /= n_runs;
        worstGraph[i].second /= n_runs;
        meanGraph[i].second /= n_runs;
        diversityGraph[i].second /= n_runs;
    }

    gp << "set yrange [0:"<< 5000 <<"]\nset xrange [0: 1000]\n";
    gp << "set xlabel 'Iterations' font 'Times-Italic,14'\n";
    gp << "set ylabel 'Fitness Value' font 'Times-Italic,14'\n";
    gp << "plot '-' with lines title 'graphBest' lw 3, '-' with lines title 'graphMean' lw 3, '-' with lines title 'graphWorst' lw 3\n";
    gp.send1d(bestGraph);
    gp.send1d(meanGraph);
    gp.send1d(worstGraph);

    gp2 << "set yrange [0: 15]\nset xrange [0: 1000]\n";
    gp2 << "set xlabel 'Iterations' font 'Times-Italic,14'\n";
    gp2 << "set ylabel 'Diversity' font 'Times-Italic,14'\n";
    gp2 << "plot '-' with lines title 'graphDiversity' lw 3\n";
    gp2.send1d(diversityGraph);

    gsl_rng_free (r);
    
    /* Statistics of the Runs */
    double FO_mean  = 0.0f, FO_std  = 0.0f;
    double T_mean   = 0.0f, T_std   = 0.0f;
    for( auto it = stats.begin(); it != stats.end(); it++){
        FO_mean += it->first;
        T_mean  += it->second;
    }
    FO_mean /= n_runs;
    T_mean  /= n_runs;
    for( auto it = stats.begin(); it != stats.end(); it++){
        FO_std += (( it->first - FO_mean )*( it->first  - FO_mean ));
        T_std  += (( it->second - T_mean )*( it->second - T_mean  ));
    }
    FO_std /= n_runs;
    FO_std = sqrt(FO_std);
    T_std /= n_runs;
    T_std = sqrt(T_std);
    printf(" +==============================================================+ \n");
    printf(" |                     EXPERIMENTS RESULTS                      | \n");
    printf(" +==============================================================+ \n");
    printf(" | Objective Function:\n");
    printf(" | \t mean:         %+.20E\n", FO_mean);
    printf(" | \t std:          %+.20E\n", FO_std);
    printf(" | Execution Time (ms): \n");
    printf(" | \t mean:         %+.3lf\n", T_mean);
    printf(" | \t std:          %+.3lf\n", T_std);
    printf(" +==============================================================+ \n");

    //delete jde;
    return 0;
}
