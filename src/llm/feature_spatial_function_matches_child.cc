#include <sstream>

#include "h2sl_hdcg/spatial_function.h"
#include "h2sl_hdcg/feature_spatial_function_matches_child.h"

using namespace std;
using namespace h2sl_hdcg;

Feature_Spatial_Function_Matches_Child::
Feature_Spatial_Function_Matches_Child( const bool & invert ) : h2sl::Feature( invert ) {

}

Feature_Spatial_Function_Matches_Child::
~Feature_Spatial_Function_Matches_Child() {

}

Feature_Spatial_Function_Matches_Child::
Feature_Spatial_Function_Matches_Child( const Feature_Spatial_Function_Matches_Child& other ) : h2sl::Feature( other ) {

}

Feature_Spatial_Function_Matches_Child&
Feature_Spatial_Function_Matches_Child::operator=( const Feature_Spatial_Function_Matches_Child& other ) {

  _invert = other._invert;
  return (*this);
}

bool Feature_Spatial_Function_Matches_Child
::value( const unsigned int& cv,
         const h2sl::Grounding* grounding,
         const vector< pair< const h2sl::Phrase*, vector< h2sl::Grounding* > > >& children,
         const h2sl::Phrase* phrase,
         const h2sl::World* world ) {
  const Spatial_Function * spatial_function = dynamic_cast< const Spatial_Function* >( grounding );
  if( spatial_function != NULL ){
    for( unsigned int i = 0; i < children.size(); i++ ){
      for( unsigned int j = 0; j < children[ i ].second.size(); j++ ){
        const Spatial_Function * child = dynamic_cast< const Spatial_Function* >( children[ i ].second[ j ] );
        if( child != NULL ){
          if( *child == *spatial_function ){
            return !_invert;
          }
        }
      }
    }
    return _invert;
  }
  return false;
}

void
Feature_Spatial_Function_Matches_Child::
to_xml( xmlDocPtr doc, xmlNodePtr root )const{
  xmlNodePtr node = xmlNewDocNode( doc, NULL, ( xmlChar* )( "feature_spatial_function_matches_child" ), NULL );
  stringstream invert_string;
  invert_string << _invert;
  xmlNewProp( node, ( const xmlChar* )( "invert" ), ( const xmlChar* )( invert_string.str().c_str() ) );
  xmlAddChild( root, node );
  return;
}

void
Feature_Spatial_Function_Matches_Child::
from_xml( xmlNodePtr root ){
  _invert = false;
  if( root->type == XML_ELEMENT_NODE ){
    xmlChar * tmp = xmlGetProp( root, ( const xmlChar* )( "invert" ) );
    if( tmp != NULL ){
      string invert_string = ( char* )( tmp );
      _invert = ( bool )( strtol( invert_string.c_str(), NULL, 10 ) );
      xmlFree( tmp );
    }
  }
  return;
}

namespace h2sl_hdcg {
  ostream&
  operator<<( ostream& out,
              const Feature_Spatial_Function_Matches_Child& other ) {
    out << "Feature_Spatial_Function_Matches_Child:(invert:(" << other.invert() << "))";
    return out;
  }
}
