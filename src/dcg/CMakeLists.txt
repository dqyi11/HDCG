# GENGETOPT FILES
set(GGOS
   dcg_test_hdcg.ggo
   dcg_demo_hdcg.ggo
   )
 
# HEADER FILES
set(HDRS
    h2sl_hdcg/dcg.h)

# QT HEADER FILES
set(QT_HDRS )

# SOURCE FILES
set(SRCS
    dcg.cc)

# BINARY SOURCE FILES
set(BIN_SRCS
   dcg_test_hdcg.cc
   dcg_demo_hdcg.cc 
   )

# LIBRARY DEPENDENCIES
set(DEPS h2sl-symbol-hdcg h2sl-llm-hdcg ${H2SL_LIBRARIES} ${LIBXML2_LIBRARIES})

# LIBRARY NAME
set(LIB h2sl-dcg-hdcg)

# process the headers
process_hdrs(HDRS ${HDRS} QT_HDRS ${QT_HDRS})

# process the library
process_lib(LIB ${LIB} QT_HDRS ${QT_HDRS} SRCS ${SRCS} DEPS ${DEPS})

# process the binaries
process_bin_srcs(LIB ${LIB} BIN_SRCS ${BIN_SRCS} GGOS ${GGOS} DEPS ${DEPS})
