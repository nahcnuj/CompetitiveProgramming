CC      = g++
CFLAGS  = -std=gnu++17 -Wall -Wextra -Wno-unknown-pragmas -O2 -I/opt/boost/gcc/include -I/opt/ac-library
LDFLAGS = -L/opt/boost/gcc/lib
LIBS    =
OBJS    = ./main.o
PROGRAM = ./a.out

.PHONY: all
all:		compile bench compare-score

.PHONY: compile
compile:	$(PROGRAM)

$(PROGRAM):	$(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) $(LIBS) -o $(PROGRAM)

%.o:		%.cpp
	@$(CC) $(CFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@rm -rfv *.o *~ $(PROGRAM)


TOOL_DIR = ./tools

IN_DIR   = $(TOOL_DIR)
IN_FILES = $(wildcard $(IN_DIR)/input_*.txt)
TEST_IN  = $(firstword $(IN_FILES))

.PHONY: test
test:	$(PROGRAM)
	time -p $(PROGRAM) <$(TEST_IN) >out.txt


OUT_DIR        = ./out
OUT_FILES      = $(addprefix $(OUT_DIR)/,$(patsubst $(IN_DIR)/input_%,%,$(IN_FILES)))
ERR_DIR        = ./err
ERR_FILES      = $(addprefix $(ERR_DIR)/,$(patsubst $(IN_DIR)/input_%,%,$(IN_FILES)))
SCORE_FILE     = ./scores.csv
OLD_SCORE_FILE = ./_scores.csv

.PHONY: bench
bench:
	@$(MAKE) --no-print-directory pre-bench
	@$(MAKE) --no-print-directory run-bench

pre-bench:
	@rm -rf $(OUT_DIR)/* $(ERR_DIR)/*

run-bench:	$(PROGRAM) $(OUT_FILES)

compare-score:	$(SCORE_FILE)
	@if [ -f $(OLD_SCORE_FILE) ]; then\
		bash bin/diff-score.bash $(OLD_SCORE_FILE) $(SCORE_FILE) ; \
	fi

SCORE_CALCULATOR_BIN = python3 $(TOOL_DIR)/judge.py
$(SCORE_FILE):	$(ERR_FILES)
	@echo 'seed,score,real,user,sys,' >$@
	@for err_file in $(ERR_FILES); do \
		basename="$$(basename $$err_file)" ; \
		seed="$$(echo -n $$(echo "$$basename" | sed "s|\([0-9]\+\)\.txt|\1|" ))" ; \
		\
		sed -i "s|Score = .*||g" $$err_file ; \
		echo -n "Score = " >>$$err_file ; \
		$(SCORE_CALCULATOR_BIN) $(IN_DIR)/input_$$basename $(OUT_DIR)/$$basename \
			| sed "s|score:||" >>$$err_file ; \
		\
		echo $$err_file | xargs -I{} sh -c ' \
			echo -n "$$seed," ; \
			grep -e "^Score = " {} | sed "s/^Score = \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^real " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^user " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			grep -e "^sys " {} | sed "s/^.* \(.*\)$$/\1,/" | tr -d "\n" ; \
			echo \
		' >>$@ ; \
	done

$(OUT_DIR)/%.txt:	$(IN_DIR)/input_%.txt $(PROGRAM) $(OUT_DIR) $(ERR_DIR)
	@time -p $(PROGRAM) <$< >$@ 2>$(ERR_DIR)/$$(basename $@)

$(OUT_DIR) $(ERR_DIR):
	@mkdir -p $@
