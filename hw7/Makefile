CPU := $(shell uname -p)
ifeq ($(CPU),arm)
export LD_LIBRARY_PATH=/opt/homebrew/lib/:$LD_LIBRARY_PATH
INCD = -I /opt/homebrew/include/
LIBD = -L /opt/homebrew/lib/
endif

CC := gcc
SRCD := src
TSTD := tests
AUXD := tests_aux
BLDD := build
BIND := bin
INCD += -I include

ALL_SRCF := $(shell find $(SRCD) -type f -name '*.c')
ALL_OBJF := $(patsubst $(SRCD)/%,$(BLDD)/%,$(ALL_SRCF:.c=.o))
TEST_SRC := $(shell find $(TSTD) -type f -name '*.c')
TEST_OBJ := $(patsubst $(TSTD)/%,$(BLDD)/%,$(TEST_SRC:.c=.o))
AUX_SRC := $(shell find $(AUXD) -type f -name '*.c')

TEST := unit_tests
EXEC := hw6

AUX_OBJS := $(patsubst $(AUXD)/%,$(BLDD)/%,$(AUX_SRC:.c=.o))
AUX_PGMS := $(patsubst $(AUXD)/%,$(BIND)/%,$(AUX_SRC:.c=))

CFLAGS := -Wall -Wextra -Wshadow -Wdouble-promotion -Wformat=2 -Wundef -pedantic -g
DFLAGS := -g -DDEBUG
PRINT_STATEMENTS := -DERROR -DSUCCESS -DWARN -DINFO

STD := -std=c99
TEST_LIB := -lcriterion
LIBS := -lm

CFLAGS += $(STD)
CFLAGS += $(DFLAGS)

TEST_RESULTS := "test_results.json"

MAKEFLAGS := -j

all: setup $(BIND)/$(TEST) $(AUX_PGMS) $(ALL_OBJF)

debug: CFLAGS += $(DFLAGS) $(PRINT_STATEMENTS) 
debug: all

setup: 
	@mkdir -p $(BIND)
	@mkdir -p $(BLDD)
	
$(BIND)/$(TEST): $(ALL_OBJF) $(TEST_OBJ) 
	$(CC) $(ALL_OBJF) $(TEST_OBJ) $(INCD) $(TEST_LIB) $(LIBD) -o $@ $(LIBS)

$(AUX_PGMS): % : $(AUX_OBJS) $(ALL_OBJF) 
	$(CC) $(BLDD)/$(@F).o $(ALL_OBJF) -o $@ $(LIBS)

$(BLDD)/%.o: $(AUXD)/%.c 
	$(CC) $(CFLAGS) $(INCD) -I $(TSTD) -c -o $@ $<

$(BLDD)/%.o: $(TSTD)/%.c
	$(CC) $(CFLAGS) $(INCD) -c -o $@ $<

$(BLDD)/%.o: $(SRCD)/%.c 
	$(CC) $(CFLAGS) $(INCD) -c -o $@ $<

$(BIND)/$(EXEC): $(ALL_OBJF)
	$(CC) $(BLDD)/$(EXEC).o -o $@ $(LIBS)

test: 
	@rm -fr $(TSTD).out
	@mkdir -p $(TSTD).out
	@$(BIND)/$(TEST) --full-stats --verbose --json=$(TEST_RESULTS)

clean:
	rm -fr $(BLDD) $(BIND) $(AUXD)/*.o $(TSTD).out *.out $(TEST_RESULTS)

.PHONY: all clean debug setup test