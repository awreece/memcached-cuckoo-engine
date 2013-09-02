AUTOMAKE_OPTIONS = foreign
lib_LTLIBRARIES = cuckoo_engine.la

cuckoo_engine_la_CFLAGS= ${NO_ERROR}
cuckoo_engine_la_LDFLAGS= -module -dynamic
cuckoo_engine_la_SOURCES= src/cuckoo_engine.c \
                          src/cuckoo_engine.h \
                          src/cuckoo_engine_cache.c \
                          src/cuckoo_engine_items.c \
                          src/cuckoo_engine_memory.c \
                          src/cuckoo_engine_stats.c \
                          src/cuckoo_engine_tap.c

.PHONY: pretty
pretty: $(SOURCES)
	@# Check to make sure we have the proper version of indent.
	$(if $(findstring GNU,$(shell indent --version 2>/dev/null)),, $(error Install GNU indent))
	@echo "Running GNU indent on source files"
	@# Note - If we have any typedefs, we need to explicitly tell indent
	@# about our typedefs via
	@# 	-T type_t
	@indent \
	  -T item_t \
	  -T engine_t \
	  -T ENGINE_HANDLE \
	  --no-tabs \
	  --indent-level2 \
	  --continue-at-parentheses \
	  --line-length80 \
	  --honour-newlines  \
	  --blank-lines-after-procedures \
	  --break-before-boolean-operator \
	  --braces-on-if-line \
	  --braces-on-func-def-line \
	  --braces-on-struct-decl-line \
	  --cuddle-else \
	  --cuddle-do-while \
	  --case-brace-indentation0 \
	  --case-indentation0 \
	  --no-space-after-function-call-names \
	  --space-after-cast \
	  --no-space-after-parentheses \
	  --start-left-side-of-comments  \
	  --left-justify-declarations \
	  --space-after-for \
	  --space-after-while \
	  --dont-break-procedure-type \
	  $^
