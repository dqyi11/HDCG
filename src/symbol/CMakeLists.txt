# GENGETOPT FILES
set(GGOS
    grounding_set_demo_hdcg.ggo 
   )


# HEADER FILES
set(HDRS
    h2sl_hdcg/spatial_function.h
    h2sl_hdcg/grounding_set.h
   )

# SOURCE FILES
set(SRCS
    spatial_function.cc
    grounding_set.cc
    )

# BINARY SOURCE FILES 
set(BIN_SRCS
    grounding_set_demo_hdcg.cc
    )

# LIBRARY DEPENDENCIES
set(DEPS ${LBFGS_LIBRARY} ${LIBXML2_LIBRARIES} ${H2SL_LIBRARIES})

# LIBRARY NAME
set(LIB h2sl-symbol-hdcg)

# process the headers
process_hdrs(HDRS ${HDRS})

# process the library
process_lib(LIB ${LIB} SRCS ${SRCS} DEPS ${DEPS}) 

# process the binaries
process_bin_srcs(LIB ${LIB} BIN_SRCS ${BIN_SRCS} GGOS ${GGOS} DEPS ${DEPS})

