#include <iostream>

#include "h2sl/grammar.h"
#include "h2sl/object.h"
#include "h2sl/region.h"
#include "h2sl/cv.h"
#include "h2sl_hdcg/feature_set.h"
#include "feature_set_demo_hdcg_cmdline.h"

using namespace std;
using namespace h2sl;
using namespace h2sl_hdcg;

int
main( int argc,
      char* argv[] ) {
  int status = 0;
  cout << "start of Feature_Set class demo program" << endl;
  
  gengetopt_args_info args;
  if( cmdline_parser( argc, argv, &args ) != 0 ){
    exit(1);
  }

  h2sl_hdcg::Feature_Set * feature_set = new h2sl_hdcg::Feature_Set();

  if( args.input_given ){
    cout << "reading feature_set from " << args.input_arg << endl;
    feature_set->from_xml( args.input_arg );
  }

  cout << "feature_set->size(): " << feature_set->size() << endl;
    
  if( args.output_given ){
    cout << "writing feature_set to " << args.output_arg << endl;
    feature_set->to_xml( args.output_arg );
  }

  if( feature_set != NULL ){
    delete feature_set;
    feature_set = NULL;
  }

  cout << "end of Feature_Set class demo program" << endl;
  return status;
}
