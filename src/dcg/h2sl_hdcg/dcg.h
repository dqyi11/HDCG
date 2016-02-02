/**
 * @file    dcg.h
 * @author  Thomas M. Howard (tmhoward@csail.mit.edu)
 *          Matthew R. Walter (mwalter@csail.mit.edu)
 * @version 1.0
 *
 * @section LICENSE
 *
 * This file is part of h2sl.
 *
 * Copyright (C) 2014 by the Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or (at
 * your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see
 * <http://www.gnu.org/licenses/gpl-2.0.html> or write to the Free
 * Software Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 * @section DESCRIPTION
 *
 * The interface for a class used to represent a Distributed Correspondence
 *   Graph
 */

#ifndef H2SL_DCG_H_HDCG
#define H2SL_DCG_H_HDCG

#include "h2sl/dcg.h"

namespace h2sl_hdcg {
  class DCG : public h2sl::DCG {
  public:
    DCG();
    virtual ~DCG();
    DCG( const DCG& other );
    DCG& operator=( const DCG& other );

    virtual void fill_search_spaces( const h2sl::World* world );

  protected:

  private:

  };
  std::ostream& operator<<( std::ostream& out, const DCG& other );
}

#endif /* H2SL_DCG_H_HDCG */
