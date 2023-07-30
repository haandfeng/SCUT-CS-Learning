#include "jDE.h"

jDE::jDE( uint _s ):
  size(_s)
{
  rng.seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());
  F.assign(size, 0.5);
  CR.assign(size, 0.9);

  T_F.assign(size, 0.5);
  T_CR.assign(size, 0.9);

  f_lower = 0.1;
  f_upper = 0.9;
  T = 0.1;

  gsl_rng_env_setup();
 
  const gsl_rng_type * ti = gsl_rng_default;
  r = gsl_rng_alloc (ti);
}

jDE::~jDE(){
  gsl_rng_free (r);
}

double jDE::getFLower(){
  return f_lower;
}

double jDE::getFUpper(){
  return f_upper;
}

double jDE::getT(){
  return T;
}

void jDE::setFLower( const double FL ){
  f_lower = FL;
}

void jDE::setFUpper( const double FU ){
  f_upper = FU;
}

void jDE::setT( const double _T){
  T = _T;
}

void jDE::reset( void ){
  F.assign(size, 0.5);
  CR.assign(size, 0.9);

  T_F.assign(size, 0.5);
  T_CR.assign(size, 0.9);
}

void jDE::update(uint dist_id, double &last){
  assert( T_F.size() > 0 || T_CR.size() > 0);
  assert( T_F.size() == T_CR.size() );
  
  std::uniform_real_distribution<double> random(0, 1);
  //Return random value with uniform distribution [0, 1)

  double r1, r2, r3, r4;

  for( uint i = 0; i < size; i++ ){

  	if(dist_id == 1) {
    	r1 = random(rng);
	    r2 = random(rng);
	    r3 = random(rng);
	    r4 = random(rng);
    } else if(dist_id == 2) {
      r1 = gsl_ran_gaussian(r, 0.5) + 0.5;
      if(r1 < 0) {
        r1 = 0.0;
      } 
      if(r1 > 1) {
        r1 = 1.0;
      }
	    r2 = gsl_ran_gaussian(r, 0.5) + 0.5;
      if(r2 < 0) {
        r2 = 0.0;
      } 
      if(r2 > 1) {
        r2 = 1.0;
      }
      r3 = gsl_ran_gaussian(r, 0.5) + 0.5;
      if(r3 < 0) {
        r3 = 0.0;
      } 
      if(r3 > 1) {
        r3 = 1.0;
      }
      r4 = gsl_ran_gaussian(r, 0.5) + 0.5;
      if(r4 < 0) {
        r4 = 0.0;
      } 
      if(r4 > 1) {
        r4 = 1.0;
      }
    } else if(dist_id == 3) {
    	r1 = last = logisticMap(last, 4.0);
      r2 = last = logisticMap(last, 4.0);
      r3 = last = logisticMap(last, 4.0);
      r4 = last = logisticMap(last, 4.0);
    }

    //printf("r1: %lf r2: %lf r3: %lf r4: %lf\n", r1, r2, r3, r4);

    if( r2 < T )
      T_F[i] = f_lower + (r1 * f_upper);
    else
      T_F[i] = F[i];

    if( r4 < T )
      T_CR[i] = r3;
    else
      T_CR[i] = CR[i];
  }
}

void jDE::showF(){
  std::cout << "# F:" << std::endl;
  uint i = 0;
  for( auto it = F.begin(); it != F.end(); it++, i++ )
    std::cout << i << ": " << *it << std::endl;
}

void jDE::showCR(){
  std::cout << "# CR:" << std::endl;
  uint i = 0;
  for( auto it = CR.begin(); it != CR.end(); it++, i++ )
    std::cout << i << ": " << *it << std::endl;
}

void jDE::runDE(uint ndim, uint ps, const vDouble& genes, vDouble& n_gen, const double x_min, const double x_max, uint dist_id, double &last){
  assert( ndim > 0 );
  assert( (ndim * ps) == genes.size() );
  assert( ps == size );

  //printf("ps: %d, ndim: %d, x_min: %.2lf, x_max: %.2lf\n", ps, ndim, x_min, x_max);
  std::uniform_real_distribution<double> random(0, 1); //[0, 1)
  std::uniform_int_distribution<int> random_i(0, ps-1); //[0, ps-1]

  int n1, n2, n3, k;
  double myCR, myF, rand_num;

  uint i = 0, j = 0;
  for( ; i < ps; i++ ){

  	if(dist_id == 1) {
    	/* Get three mutually different indexes */
	    do n1 = random_i(rng); while (n1 == i);
	    do n2 = random_i(rng); while (n2 == i || n2 == n1 );
	    do n3 = random_i(rng); while (n3 == i || n3 == n1 || n3 == n2);
    } else if(dist_id == 2) {
    	/* Get three mutually different indexes */
	    do {
        n1 = (int)gsl_ran_gaussian(r, ps-1-((ps-1)/2)) + (ps-1)/2;
        if(n1 < 0) {
          n1 = 0.0;
        }
        if(n1 > ps-1) {
          n1 = ps-1;
        }
      } while (n1 == i);
	    do {
        n2 = (int)gsl_ran_gaussian(r, ps-1-((ps-1)/2)) + (ps-1)/2;
        if(n2 < 0) {
          n2 = 0.0;
        }
        if(n2 > ps-1) {
          n2 = ps-1;
        }
      } while (n2 == i || n2 == n1);
	    do {
        n3 = (int)gsl_ran_gaussian(r, ps-1-((ps-1)/2)) + (ps-1)/2;
        if(n3 < 0) {
          n3 = 0.0;
        }
        if(n3 > ps-1) {
          n3 = ps-1;
        }
      } while (n3 == i || n3 == n1 || n3 == n2);
    } else if(dist_id == 3) {
    	/* Get three mutually different indexes */  
      do {
        last = logisticMap(last, 4.0); 
        n1 = (int)remap(last, 0.0, 1.0, 0.0, ps-1);
      } while (n1 == i);
      do {
        last = logisticMap(last, 4.0); 
        n2 = (int)remap(last, 0.0, 1.0, 0.0, ps-1);
      } while (n2 == i || n2 == n1);
      do {
        last = logisticMap(last, 4.0); 
        n3 = (int)remap(last, 0.0, 1.0, 0.0, ps-1);
      } while (n3 == i || n3 == n1 || n3 == n2);
    }

    //printf("n1: %d n2: %d n3: %d\n", n1, n2, n3);

    myCR = T_CR[i];
    myF  = T_F[i];

    for( j = 0; j < ndim; j++ ){

      if(dist_id == 1) {
        rand_num = random(rng);
      } else if(dist_id == 2) {
        rand_num = gsl_ran_gaussian(r, 0.5) + 0.5;
        if(rand_num < 0) {
          rand_num = 0.0;
        }
        if(rand_num > 1) {
          rand_num = 1.0;
        }
      } else if(dist_id == 3) {
        last = rand_num = logisticMap(last, 4.0);
      }

      //printf("rand_num: %lf\n", rand_num);      

      if( (rand_num <= myCR) || ( j == (ndim-1) ) ){
        n_gen[i * ndim + j] = genes[n1 * ndim + j] + myF * ( genes[ n2 * ndim + j] - genes[n3 * ndim + j]);

        //boundary constraint handling strategy :: Projection
        //n_gen[i * ndim + j] = std::min(x_max, n_gen[i * ndim + j]);
        //n_gen[i * ndim + j] = std::max(x_min, n_gen[i * ndim + j]);

        //check bound
        if( n_gen[i * ndim + j] < x_min ){
          n_gen[i*ndim+j] = (x_min + genes[i*ndim+j]) / 2.0;
        } else if( n_gen[i * ndim + j] > x_max ){
          n_gen[i*ndim+j] = (x_max + genes[i*ndim+j]) / 2.0;
        }

        //n_gen[i * ndim + j] = bound_handle(n_gen[i * ndim + j], genes[i * ndim + j], x_min, x_max);

      } else {
        n_gen[i*ndim+j] = genes[i*ndim+j];
      }
    }
  }

}

//jde->selection(n_dim, NP, gen, n_gen, fitness, n_fitness);
void jDE::selection(
  uint ndim, uint ps,
  vDouble & genes, const vDouble & n_gen,
  vDouble & fitness, const vDouble & n_fitness
){
  assert( ndim > 0 );
  assert( ps > 0 );
  assert( genes.size() == n_gen.size() );
  assert( fitness.size() == n_fitness.size() );
  assert( genes.size() == (ndim * ps) );
  assert( fitness.size() ==  ps );

  for( uint i = 0; i < ps; i++ ){
    if( n_fitness[i] <= fitness[i] ){

      for( uint j = 0; j < ndim; j++ )
        genes[i * ndim + j] = n_gen[i * ndim + j];

      fitness[i] = n_fitness[i];
      F[i]  = T_F[i];
      CR[i] = T_CR[i];
    }
  }
}

double jDE::bound_handle(
  double t,
  const double p,
  const double min,
  const double max
){

  if( t < min ){
    t = (min + p) / 2.0;
  } else if( t > max ){
    t = (max + p) / 2.0;
  }

  return t;
}

double jDE::logisticMap(double randomNum, double r) {
	randomNum = r * randomNum * (1 - randomNum);
	return randomNum;
}

double jDE::remap(double from, double fromMin, double fromMax, double toMin,  double toMax) {
    double fromAbs  =  from - fromMin;
    double fromMaxAbs = fromMax - fromMin;      
   
    double normal = fromAbs / fromMaxAbs;

    double toMaxAbs = toMax - toMin;
    double toAbs = toMaxAbs * normal;

    double to = toAbs + toMin;
   
    return to;
}